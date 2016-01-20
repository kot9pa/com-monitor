/****************************************************************************
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** As a special exception, The Qt Company gives you certain additional
** rights. These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingsdialog.h"
#include "console.h"

#include <QMessageBox>
#include <QDateTime>
#include <QFile>
#include <QTimer>
#include <QFileDialog>
#include <QSettings>
#include <QClipboard>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qRegisterMetaType<QVector<int> >("QVector<int>");

    warningCount = 0;
    errorCount = 0;
    infoCount = 0;

    console = new Console;
    serial = new QSerialPort(this);
    settings = new SettingsDialog;
    menu = new QMenu(this);
    timer = new QTimer(this);
    timer->start(1000);
    refresh = new QTimer(this);
    refresh->setSingleShot(true);
    pause = new QTimer(this);
    pause->setSingleShot(true);

    progressBar = new QProgressBar(ui->statusBar);
    progressBar->setAlignment(Qt::AlignRight);
    progressBar->setFixedHeight(15);
    progressBar->setFixedWidth(150);
    progressBar->setValue(0);
    progressBar->setMinimum(0);
    progressBar->setTextVisible(true);
    progressBar->hide();

    ui->statusBar->addPermanentWidget(progressBar);

    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionQuit->setEnabled(true);
    ui->actionConfigure->setEnabled(true);
    ui->actionRefresh->setEnabled(false);
    ui->actionClear->setEnabled(false);
    ui->actionCopy->setEnabled(false);
    ui->readButton->setEnabled(false);
    ui->writeButton->setEnabled(false);

    ui->logBoxExport->addItem(tr("All (AA)"));
    ui->logBoxExport->addItem(tr("Info (II)"));
    ui->logBoxExport->addItem(tr("Warning (WW)"));
    ui->logBoxExport->addItem(tr("Error (EE)"));

    ui->dataBoxSet->addItem(QStringLiteral("0"), 0);
    ui->dataBoxSet->addItem(QStringLiteral("1"), 1);
    ui->dataBoxSet->addItem(QStringLiteral("2"), 2);
    ui->dataBoxSet->addItem(QStringLiteral("3"), 3);
    ui->dataBoxSet->addItem(QStringLiteral("8"), 8);
    ui->dataBoxSet->addItem(QStringLiteral("9"), 9);
    ui->dataBoxSet->addItem(QStringLiteral("10"), 10);
    ui->dataBoxSet->addItem(QStringLiteral("11"), 11);

    ui->warningCount->setText(QString::number(warningCount));
    ui->warningCount->setStyleSheet("QLabel {font:bold; color:yellow;}");
    ui->warningCount->installEventFilter(this);
    ui->errorCount->setText(QString::number(errorCount));
    ui->errorCount->setStyleSheet("QLabel {font:bold; color:red;}");
    ui->errorCount->installEventFilter(this);
    ui->infoCount->setText(QString::number(infoCount));
    ui->infoCount->setStyleSheet("QLabel {font:bold; color:green;}");
    ui->infoCount->installEventFilter(this);

    ui->tableWidget->setColumnHidden(0, true);
    ui->dateTimeFrom->setDate(QDate::currentDate());
    ui->dateTimeTo->setDate(QDate::currentDate());
    ui->sensorCheckAllSet->setChecked(true);
    ui->sensorCheckAllExport->setChecked(true);

    msgLast = QByteArray();
    msgQueue = QByteArray();
    msgRequest = QByteArray();
    msgRead = QByteArray("02\r");
    msgReadAll = QByteArray("01\r");
    msgWrite = QByteArray("05\r");
    msgWriteAll = QByteArray("04\r");
    bytes = QByteArray(65536, 0);
    format = ("dd.MM.yy HH:mm:ss");
    settingsFile = QApplication::applicationDirPath() + "/com-monitor.ini";

    loadSettings();

    initActionsConnections();
    initSerialPort();
    initTable();

    fillDataInfo();

}

MainWindow::~MainWindow()
{
    db.close();
    saveSettings();

    delete settings;
    delete console;
    delete ui;
}

bool MainWindow::eventFilter(QObject *object, QEvent *event)
{
    if(event->type()==QEvent::MouseButtonRelease) {

        if(object==ui->warningCount) qDebug()<<"warningCount = "<<warningCount;
        if(object==ui->errorCount) qDebug()<<"errorCount = "<<errorCount;
        if(object==ui->infoCount) qDebug()<<"infoCount = "<<infoCount;

    }

    return QMainWindow::eventFilter( object, event );
}

void MainWindow::currentDateTime()
{
    ui->dateCurrent->display(QDate::currentDate().toString("dd.MM.yyyy"));
    ui->timeCurrent->display(QTime::currentTime().toString("HH:mm:ss"));

    progressBar->setTextVisible(true);
    progressBar->setFormat("Time remaining: " + QString::number(pause->remainingTime()/1000));

}

void MainWindow::customMenuRequest(const QPoint &pos)
{
    menu->addAction(ui->actionRefresh);
    menu->addAction(ui->actionCopy);
    menu->addAction(ui->actionClear);
    menu->exec(ui->tableWidget->viewport()->mapToGlobal(pos));

}

void MainWindow::buttonRRequest()
{
    QString readAddress;
    address = ui->sensorBoxSet->currentText();
    int idx1 = address.toInt();
    //int idx2;

    if(ui->sensorCheckAllSet->isChecked()) {

        msgQueue.append(msgReadAll);
        address.clear();

        console->putData(QString("Read all address"));

    } else { //for(int i=0; i<5; i++) {

            //idx2 = i+(idx1-1)*5;
            //readAddress = QString::number(idx2).rightJustified(2,'0');
            readAddress = QString::number(idx1).rightJustified(2,'0');

            msgQueue.append(msgRead);
            msgQueue.append(readAddress.at(0));
            msgQueue.append('\r');
            msgQueue.append(readAddress.at(1));
            msgQueue.append('\r');

            qDebug()<<"read address = "<<readAddress;
            console->putData("Read address: "+readAddress);

        //}
    }

    if(!refresh->isActive()) refreshData();

    ui->readButton->setEnabled(false);
    ui->writeButton->setEnabled(false);

}

void MainWindow::buttonWRequest()
{
    QString writeAddress;
    address = ui->sensorBoxSet->currentText();
    int dataRequest = ui->dataBoxSet->currentData().toInt();
    int idx1 = address.toInt();

    if(ui->sensorCheckAllSet->isChecked()) {
        /*for(int i=0; i<listSensor.count(); i++) {

            writeAddress = QString::number(i*5).rightJustified(2,'0');

            msgQueue.append(msgWriteAll);
            msgQueue.append(writeAddress.at(0));
            msgQueue.append('\r');
            msgQueue.append(writeAddress.at(1));
            msgQueue.append('\r');
            msgQueue.append(dataRequest);
            msgQueue.append('\r');

        }*/

        msgQueue.append(msgWriteAll);
        msgQueue.append(dataRequest);
        msgQueue.append('\r');

        address.clear();
        console->putData("Write all address\rData = "+QString::number(dataRequest));

    } else {

        writeAddress = QString::number(idx1).rightJustified(2,'0');
        //writeAddress = QString::number((idx1-1)*5).rightJustified(2,'0');

        msgQueue.append(msgWrite);
        msgQueue.append(writeAddress.at(0));
        msgQueue.append('\r');
        msgQueue.append(writeAddress.at(1));
        msgQueue.append('\r');
        msgQueue.append(dataRequest);
        msgQueue.append('\r');

        qDebug()<<"write address = "<<address<<" data = "<<QString::number(dataRequest);
        console->putData("Write address: "+address+"\rData = "+QString::number(dataRequest));

    }

    if(!refresh->isActive()) refreshData();

    ui->writeButton->setEnabled(false);
    ui->readButton->setEnabled(false);

}

void MainWindow::initTimer()
{
    SettingsDialog::Settings p = settings->settings();

    int interval = p.refresh*1000;

    if (serial->isOpen() && interval!=0) {
        refresh->start(interval);

    }

    //ui->statusBar->showMessage(tr("Refresh Data.."));

    qDebug()<<"interval = "<<refresh->interval();

}

void MainWindow::initSerialPort()
{
    SettingsDialog::Settings p = settings->settings();
    if(p.autoconnect) openSerialPort();

    connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError)));
    connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));
}

void MainWindow::initActionsConnections()
{
    connect(this, SIGNAL(writeRequest(QByteArray)), this, SLOT(writeData(QByteArray)));
    connect(console, SIGNAL(getData(QByteArray)), this, SLOT(writeData(QByteArray)));
    connect(refresh, SIGNAL(timeout()), this, SLOT(refreshData()));
    connect(pause, SIGNAL(timeout()), this, SLOT(verifyData()));
    connect(timer, SIGNAL(timeout()), this, SLOT(currentDateTime()));
    connect(ui->tableWidget, SIGNAL(customContextMenuRequested(QPoint)), this,
            SLOT(customMenuRequest(QPoint)));
    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(fillDataInfo()));
    //connect(ui->sensorBoxSet, SIGNAL(activated(int)), this, SLOT(fillDataInfo()));
    //connect(ui->dateTimeFrom, SIGNAL(dateChanged(QDate)), this, SLOT(fillDataInfo()));
    //connect(ui->dateTimeTo, SIGNAL(dateChanged(QDate)), this, SLOT(fillDataInfo()));
    //connect(ui->logBoxSet, SIGNAL(activated(int)), this, SLOT(fillDataInfo()));
    connect(ui->exportButton, SIGNAL(pressed()), this, SLOT(exportData()));
    connect(ui->actionConnect, SIGNAL(triggered()), this, SLOT(openSerialPort()));
    connect(ui->actionDisconnect, SIGNAL(triggered()), this, SLOT(closeSerialPort()));
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionConfigure, SIGNAL(triggered()), settings, SLOT(show()));
    connect(ui->actionClear, SIGNAL(triggered()), console, SLOT(clear()));
    connect(ui->actionCopy, SIGNAL(triggered()), this, SLOT(copyData()));
    connect(ui->actionClear, SIGNAL(triggered()), this, SLOT(clearData()));
    connect(ui->actionConsole, SIGNAL(triggered()), console, SLOT(show()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(about()));
    connect(ui->actionRefresh, SIGNAL(triggered()), this, SLOT(refreshData()));
    connect(ui->readButton, SIGNAL(clicked()), this, SLOT(buttonRRequest()));
    connect(ui->writeButton, SIGNAL(clicked()), this, SLOT(buttonWRequest()));

}

void MainWindow::initTable()
{
    if(db.databaseName().isEmpty()) {
        QString path = QFileDialog::getSaveFileName(this, tr("Data file:"),
                                                    QApplication::applicationDirPath()+"/com-monitor.sqlite",
                                                    "SQLite files (*.sqlite)");
        db.setDatabaseName(path);
    }
    if(db.open()) {
        QSqlQuery query;
        query.exec("CREATE TABLE tabMain ("
                   "id INTEGER PRIMARY KEY, "
                   "datetime DATETIME, "
                   "address INTEGER, "
                   "data INTEGER, "
                   "sensor INTEGER, "
                   "status INTEGER, "
                   "message VARCHAR(255)"
                   ")");
    } else QMessageBox::critical(0, qApp->tr("Cannot open database"),
                                 qApp->tr("Unable to establish a database connection.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);

    console->putData(db.lastError().text());

    qDebug()<<"db = "<<db.databaseName();

}

void MainWindow::openSerialPort()
{
    SettingsDialog::Settings p = settings->settings();
    serial->setPortName(p.name);
    serial->setBaudRate(p.baudRate);
    serial->setDataBits(p.dataBits);
    serial->setParity(p.parity);
    serial->setStopBits(p.stopBits);
    serial->setFlowControl(p.flowControl);
    serial->setReadBufferSize(65536);

    if (serial->open(QIODevice::ReadWrite)) {
        ui->actionConnect->setEnabled(false);
        ui->actionDisconnect->setEnabled(true);
        ui->actionConfigure->setEnabled(false);
        ui->actionRefresh->setEnabled(true);
        ui->readButton->setEnabled(true);
        ui->writeButton->setEnabled(true);
        ui->statusBar->showMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                                   .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
                                   .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));

        initTimer();
        bytes.clear();

    } else {
        QMessageBox::critical(this, tr("Error"), serial->errorString());
        ui->statusBar->showMessage(tr("Open error"));

    }

    console->putData(ui->statusBar->currentMessage());
}

void MainWindow::closeSerialPort()
{
    if (serial->isOpen())
        serial->close();
    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionConfigure->setEnabled(true);
    ui->actionRefresh->setEnabled(false);
    ui->readButton->setEnabled(false);
    ui->writeButton->setEnabled(false);
    ui->statusBar->showMessage(tr("Disconnected"));

    console->putData(ui->statusBar->currentMessage());

    refresh->stop();
    bytes.clear();

}

void MainWindow::writeData(const QByteArray &data)
{
    serial->write(data);
    qDebug()<<"write = " << data;
    msgLast.clear();

    if(data==msgReadAll.left(2)) {
        pause->start(5000);
        msgLast.append(data);
        qDebug()<<"delay = " << pause->interval();

    }

    if(data==msgRead.left(2) ||
            data==msgWrite.left(2) ||
            data==msgWriteAll.left(2)) {
        pause->start(2000);
        msgLast.append(data);
        qDebug()<<"delay = " << pause->interval();
    }

    else if(!msgQueue.isEmpty()) refresh->start(1000);

    else if(!pause->isActive()) pause->start(1000);

    console->putData("Write: "+QString::fromLocal8Bit(data));
    //console->putData("Time remaining: " + QString::number(pause->remainingTime()/1000));

    ui->statusBar->showMessage(tr("Write Data.."));
    qDebug()<<"msgLast = "<<msgLast;

}

void MainWindow::refreshData()
{
    if(serial->isOpen()) {
        initTimer();

        if(!msgQueue.isEmpty()) {
            msgRequest.clear();

            qDebug()<<"queue = "<<msgQueue;

            for(int i=0; i<msgQueue.size(); i++) {

                if(msgQueue.at(i) != '\r') msgRequest.append(msgQueue.at(i));
                else break;
            }

            qDebug()<<"request = "<<msgRequest;

            msgQueue = msgQueue.remove(0, msgRequest.length()+1);
            emit writeRequest(msgRequest);

        } else writeRequest(msgReadAll.left(2));

    }

    //ui->statusBar->showMessage(tr("Refresh Data.."));
    //console->putData("Refresh Data()\rQueue = "+QString::fromLocal8Bit(msgQueue));

}

void MainWindow::readData()
{
    bytes.append(serial->readAll());

    ui->statusBar->showMessage(tr("Read Data.."));
    progressBar->show();

    //console->putData(bytes);
    //qDebug()<<"read = " << bytes;

}

void MainWindow::verifyData()
{
    if(!bytes.isNull() && bytes.length()>3) {
        if(bytes.startsWith("48\r\n")) {
            bytes.remove(0,4);

            qDebug()<<"48 OK"<<bytes;
        }
        else if(bytes.endsWith("48\r\n")) {
            bytes.resize(bytes.size()-4);

            qDebug()<<"48 OK"<<bytes;
        }
        else {
            msgQueue.append(msgLast);
            msgLast.clear();
            bytes.clear();

            qDebug()<<"48 ERROR"<<bytes;            

        }
    }

    if(!msgQueue.isEmpty()) refreshData();
    else processData();

}

void MainWindow::processData()
{
    ui->statusBar->showMessage(tr("Process Data.."));
    console->putData("Read: "+QString::fromLocal8Bit(bytes.simplified()));

    qDebug()<<"read = " << bytes;

    QByteArray addressData(0);
    QByteArray statusData(0);
    QByteArray messageData(0);
    QSqlQuery query;

    int idx1 = 0;
    int idx2 = 0;
    int sensor = 1;
    int adress = 0;
    int i = 0;
    int j = 2;

    if(!address.isEmpty()) {
        sensor = address.toInt();
        adress = address.toInt();
    }

    if(!bytes.isNull()) {

        for( ; i < bytes.size(); i++ ) {

            if(bytes.at(i) != '\r' && bytes.at(i) != '\n')
                statusData.append(bytes.at(i));

            else if(i<bytes.size()-8) {

                while(idx1<8 && idx2<bytes.size()) {
                    if(bytes.at(i+j) != '\r' && bytes.at(i+j) != '\n')
                        messageData.append(bytes.at(i+j));
                    else {
                        messageData.append(' ');
                        idx1++;
                    }
                    j++;
                    idx2=i+j;
                }
                i=idx2-1;
                j=2;
                idx1=0;
            }

            if(!statusData.isEmpty() && !messageData.isEmpty()) {

                query.prepare("INSERT INTO tabMain (id, datetime, sensor, status, message) "
                              "VALUES (null, :datetime, :sensor, :status, :message)");
                query.bindValue(":datetime", QDateTime::currentDateTime());
                qDebug()<<"sensor = " << sensor;
                query.bindValue(":sensor", sensor++);
                qDebug()<<"status = " << statusData.toInt();
                query.bindValue(":status", statusData.toInt());
                qDebug()<<"message = " << messageData;
                query.bindValue(":message", messageData);
                query.exec();

                //int status = statusData.toInt();

                switch(statusData.toInt()){
                case 8:
                    infoCount++;
                    break;
                case 9:
                    errorCount++;
                    break;

                }

                //if (status==8) infoCount++;
                //if (status==9) errorCount++;
                //else infoCount++;

                statusData.clear();
                messageData.clear();

            }
        }

        for(int a=0;a<bytes.size();a++) {

            if(bytes.at(a) != '\r' && bytes.at(a) != '\n')
                addressData.append(bytes.at(a));

            else if(!addressData.isEmpty()) {
                query.prepare("INSERT INTO tabMain (id, datetime, address, data) "
                              "VALUES (null, :datetime, :address, :data)");
                query.bindValue(":datetime", QDateTime::currentDateTime());
                query.bindValue(":address", adress++);
                query.bindValue(":data", addressData.toInt());
                query.exec();

                addressData.clear();
            }
        }
    }

    recordData();
    fillDataInfo();

    ui->readButton->setEnabled(true);
    ui->writeButton->setEnabled(true);

    progressBar->hide();
    bytes.clear();

}

void MainWindow::fillDataInfo()
{
    clearData();
    fillSensorInfo();

    int tabIDX = ui->tabWidget->currentIndex();
    QString date = QDate::currentDate().toString("yyyy-MM-dd");
    QString data;

    if(tabIDX==1) {
        foreach(QString address, listAddress) {

            data = "SELECT id, datetime, address, data "
                   "FROM tabMain "
                   "WHERE date(datetime) = '%1' "
                   "AND address = %2 "
                   "ORDER BY id DESC LIMIT 1"; //ALL
            viewData(data.arg(date).arg(address));

            //qDebug()<<"address = " << address;

        }
    } else {
        foreach(QString sensor, listSensor) {

            data = "SELECT id, datetime, sensor, status, message "
                   "FROM tabMain "
                   "WHERE date(datetime) = '%1' "
                   "AND sensor = %2 "
                   "ORDER BY id DESC LIMIT 1"; //ALL
            viewData(data.arg(date).arg(sensor));

            //qDebug()<<"sensor = " << sensor;

        }
    }

}

void MainWindow::fillSensorInfo()
{
    listSensor.clear();
    listAddress.clear();

    QString last = ui->sensorBoxSet->currentText();
    QString date = QDate::currentDate().toString("yyyy-MM-dd");
    QSqlQuery query;
    query.prepare(QString("SELECT DISTINCT sensor FROM tabMain "
                          "WHERE date(datetime)='%1'").arg(date));
    query.exec();
    while(query.next()) {

        if(!query.value(0).isNull()) listSensor.append(query.value(0).toString());

    }
    //listSensor.removeLast();
    //listSensor = QStringList(list.join(", "));    

    for(int i=0;i<=listSensor.size()*5;i++) listAddress.append(QString::number(i));

    qDebug()<<"listSensor = " << listSensor;
    qDebug()<<"listAddress = " << listAddress;

    ui->sensorBoxSet->clear();
    ui->sensorBoxSet->addItems(listAddress);
    //ui->sensorBoxSet->addItem(tr("All"), listSensor);
    ui->sensorBoxSet->setCurrentText(last);

    ui->sensorBoxExport->clear();
    ui->sensorBoxExport->addItems(listSensor);
    //ui->sensorBoxExport->addItem(tr("All"), listSensor);
    ui->sensorBoxExport->setCurrentText(last);

}

void MainWindow::viewData(QString data)
{
    int tabIDX = ui->tabWidget->currentIndex();
    QTableWidgetItem *item = new QTableWidgetItem();

    QSqlQuery query;
    query.exec(data);
    while (query.next())
    {
        ui->tableWidget->insertRow(0);
        //ui->tableWidget->setRowHeight(0, 20);
        ui->tableWidget->setItem(0, 0, new QTableWidgetItem(query.value(0).toInt()));
        ui->tableWidget->setItem(0, 1, new QTableWidgetItem(query.value(1).toDateTime().toString()));
        item->setData(Qt::DisplayRole, query.value(2).toInt());
        ui->tableWidget->setItem(0, 2, item);
        ui->tableWidget->setItem(0, 3, new QTableWidgetItem(query.value(3).toString()));
        ui->tableWidget->setItem(0, 4, new QTableWidgetItem(query.value(4).toString()));
        ui->tableWidget->resizeColumnsToContents();

        if(tabIDX!=1) {

            int status = query.value(3).toInt();

            switch(status) {
            case 8:
                ui->tableWidget->item(0, 3)->setText("OK");
                ui->infoCount->setText(QString::number(infoCount));
                break;
            case 9:
                ui->tableWidget->item(0, 3)->setText("NOT OK");
                ui->errorCount->setText(QString::number(errorCount));
                break;

            }
        }

        /*if (status=="8") {
            for ( int j = 0; j < 5; j++) ui->tableWidget->item(0, j)->setBackground(Qt::red);
            ui->errorCount->setText(QString::number(errorCount));


        }
        if (status=="9") {
            for ( int j = 0; j < 5; j++) ui->tableWidget->item(0, j)->setBackground(Qt::yellow);
            ui->warningCount->setText(QString::number(warningCount));

        }
        else {
            for ( int j = 0; j < 5; j++) ui->tableWidget->item(0, j)->setBackground(Qt::green);
            ui->infoCount->setText(QString::number(infoCount));

        }*/

    }

    //qDebug()<<query.isValid();
    //qDebug()<<query.lastError();
    //qDebug()<<query.lastQuery();

    if(ui->tableWidget->rowCount()!=0) {
        //ui->tableWidget->scrollToBottom();
        ui->actionClear->setEnabled(true);
        ui->actionCopy->setEnabled(true);

    }
    ui->tableWidget->setSortingEnabled(true);
    ui->tableWidget->sortByColumn(2, Qt::AscendingOrder);
    ui->tableWidget->setSortingEnabled(false);

    ui->statusBar->showMessage(tr("Process Data.. Done"));

}

void MainWindow::clearData()
{
    int n = ui->tableWidget->rowCount();
    for( int i = 0; i < n; i++ ) ui->tableWidget->removeRow(0);

    qDebug()<<"clear = "<<n;

    ui->actionClear->setEnabled(false);
    ui->actionCopy->setEnabled(false);

    //QSqlQuery query;
    //query.exec("DELETE FROM tabMain");

}

void MainWindow::copyData()
{
    QClipboard *clipboard = QApplication::clipboard();
    QList<QTableWidgetItem *> selected(ui->tableWidget->selectedItems());
    QTableWidgetItem *item;
    QString itemSelect;

    foreach (item, selected) {
        itemSelect.append(item->text());

    }

    clipboard->setText(itemSelect);

}

void MainWindow::recordData()
{
    QString date = QDateTime::currentDateTime().toString(format);
    QFile file("com-monitor.log");
    if (file.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream out(&file);
        out << date << endl << bytes << endl;
        qDebug()<< "record = " << bytes;
        file.close();
    }
    else
    {
        qWarning("Can not open file.");
    }
}

void MainWindow::exportData()
{
    ui->statusBar->showMessage(tr("Export Data.."));

    QString filename = QFileDialog::getSaveFileName(this, tr("Export to:"), "com-monitor.csv",
                                                    "CSV files (*.csv)", 0, 0);
    QFile file(filename);
    if(file.open(QFile::WriteOnly |QFile::Truncate)) {

        QString dateFrom = ui->dateTimeFrom->date().toString("yyyy-MM-dd");
        QString dateTo = ui->dateTimeTo->date().toString("yyyy-MM-dd");
        QString level;
        QString sensor;
        int idxLevel = ui->logBoxExport->currentIndex();
        switch(idxLevel) {
        case 0: level = "";
            break;
        case 1: level = "NOT IN (6,7,8,9)";
            break;
        case 2: level = "IN (8,9)";
            break;
        case 3: level = "IN (6,7)";
            break;
        }

        if(ui->sensorCheckAllExport->isChecked()) {
            //ui->sensorBoxExport->setCurrentIndex(ui->sensorBoxExport->findText("All"));
            //sensor = ui->sensorBoxExport->itemData(ui->sensorBoxExport->currentIndex()).toString();
            sensor = listSensor.join(",");
        } else  {
            //ui->sensorBoxExport->removeItem(ui->sensorBoxExport->findText("All"));
            sensor = ui->sensorBoxExport->currentText();
        }

        //qDebug()<<"sensor = "<<sensor;

        QSqlQuery query;
        QString data = QString("SELECT * FROM tabMain "
                               "WHERE status %4 "
                               "AND date(datetime) between '%1' and '%2' "
                               "AND sensor IN (%3) ").arg(dateFrom).arg(dateTo).arg(sensor).arg(level);

        QSqlRecord recordCount;
        query.prepare(QString("SELECT COUNT(*) FROM (%1) AS subquery").arg(data));
        query.exec();
        query.next();
        recordCount = query.record();

        int value = 0;
        int qSize = query.value(0).toInt();

        progressBar->show();
        progressBar->setMaximum(qSize);

        qDebug()<<"count = "<<qSize;

        query.exec(data);
        while(query.next()) {
            QTextStream output(&file);
            QStringList strList;
            strList.clear();

            for(int i=1; i<5; i++) strList.append(query.value(i).toString());
            output << strList.join(";")+"\n";

            progressBar->setValue(value++);

            qDebug()<<"export = "<<strList;

        }

        file.close();

        //qDebug()<<query.lastError();
        qDebug()<<query.lastQuery();

    }

    progressBar->reset();
    progressBar->hide();

}

void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
        closeSerialPort();
    }
}

void MainWindow::saveSettings()
{
    QSettings settings(settingsFile, QSettings::IniFormat);

    qDebug()<<"settingsFile2"<<settingsFile;

    settings.setValue("LogLevel", ui->logBoxExport->currentText());
    settings.setValue("LogLevelIndex", ui->logBoxExport->currentIndex());
    settings.setValue("SensorControl", ui->sensorBoxSet->currentText());
    settings.setValue("SensorExport", ui->sensorBoxExport->currentText());
    settings.setValue("DataBaseName", db.databaseName());

}

void MainWindow::loadSettings()
{
    QSettings settings(settingsFile, QSettings::IniFormat);

    ui->logBoxExport->setCurrentText(settings.value("LogLevel").toString());
    ui->logBoxExport->setCurrentIndex(settings.value("LogLevelIndex").toInt());
    ui->sensorBoxSet->setCurrentText(settings.value("SensorControl").toString());
    ui->sensorBoxExport->setCurrentText(settings.value("SensorExport").toString());

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(settings.value("DataBaseName").toString());

}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About COM Monitor"),
                       tr("The <b>Com Monitor</b> (c) 2015."));
}

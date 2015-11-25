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

    console = new Console;
    serial = new QSerialPort(this);
    settings = new SettingsDialog;
    menu = new QMenu(this);
    timer = new QTimer(this);
    timer->start(1000);
    refresh = new QTimer(this);
    refresh->setSingleShot(true);

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

    ui->logBoxExport->addItem(tr("All (AA)"));
    ui->logBoxExport->addItem(tr("Info (II)"));
    ui->logBoxExport->addItem(tr("Warning (WW)"));
    ui->logBoxExport->addItem(tr("Error (EE)"));

    ui->tableWidget->setColumnHidden(0, true);
    ui->dateTimeFrom->setDate(QDate::currentDate());
    ui->dateTimeTo->setDate(QDate::currentDate());
    ui->sensorCheckAllSet->setChecked(true);
    ui->sensorCheckAllExport->setChecked(true);

    msg = ("AT^MONP\r");
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

void MainWindow::currentDateTime()
{
    ui->dateCurrent->display(QDate::currentDate().toString("dd.MM.yyyy"));
    ui->timeCurrent->display(QTime::currentTime().toString("HH:mm:ss"));
}

void MainWindow::customMenuRequest(const QPoint &pos)
{
    menu->addAction(ui->actionRefresh);
    menu->addAction(ui->actionCopy);
    menu->addAction(ui->actionClear);
    menu->exec(ui->tableWidget->viewport()->mapToGlobal(pos));

}

void MainWindow::initTimer()
{
    int interval = refresh->interval();
    if (serial->isOpen() && interval!=0) {
        refresh->setInterval(interval);
        refresh->start();
    }

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
    connect(timer, SIGNAL(timeout()), this, SLOT(currentDateTime()));
    connect(ui->tableWidget, SIGNAL(customContextMenuRequested(QPoint)), this,
            SLOT(customMenuRequest(QPoint)));
    //connect(ui->sensorCheckAll, SIGNAL(toggled(bool)), this, SLOT(fillDataInfo()));
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
               "sensor INTEGER, "
               "status INTEGER, "
               "message VARCHAR(255)"
               ")");
    } else QMessageBox::critical(0, qApp->tr("Cannot open database"),
           qApp->tr("Unable to establish a database connection.\n"
           "This example needs SQLite support. Please read "
           "the Qt SQL driver documentation for information how "
           "to build it.\n\n"
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
        refresh->setInterval(p.refresh*1000);
        ui->actionConnect->setEnabled(false);
        ui->actionDisconnect->setEnabled(true);
        ui->actionConfigure->setEnabled(false);
        ui->actionRefresh->setEnabled(true);
        ui->statusBar->showMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                                   .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
                                   .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));

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
    ui->statusBar->showMessage(tr("Disconnected"));

    console->putData(ui->statusBar->currentMessage());

    refresh->stop();

}

void MainWindow::writeData(const QByteArray &data)
{    
    serial->write(data);
    qDebug()<<"write = " << data;

    bytes.clear();

}

void MainWindow::refreshData()
{
    if(!bytes.isEmpty())
        processData();

    if(serial->isOpen())
        emit writeRequest(msg);

    initTimer();

    //bytes.clear();

}

void MainWindow::readData()
{
    //serial->waitForReadyRead(500);

    bytes.append(serial->readAll());

    console->putData(bytes);

    qDebug()<<"read = " << bytes;

}

void MainWindow::processData()
{
    //console->putData(bytes);

    QBitArray bits(bytes.count()*8);

    // Convert from QByteArray to QBitArray
    for(int i=0; i<bytes.count(); ++i) {
        for(int b=0; b<8; ++b) {
            bits.setBit( i*8+b, bytes.at(i)&(1<<(7-b)) );
        }
    }

    //qDebug()<<bits;

    if(bytes.at(0)=='\r' && bytes.at(1)=='\n') {

        QSqlQuery query;
        query.prepare("INSERT INTO tabMain (id, datetime, sensor, status, message) "
                      "VALUES (null , :datetime, :sensor, :status, :message)");
        query.bindValue(":datetime", QDateTime::currentDateTime());
        query.bindValue(":sensor", bytes.mid(39, 2).toInt());
        qDebug()<<"sensor = " << bytes.mid(39, 2);
        query.bindValue(":status", bytes.mid(44, 1).toInt());
        qDebug()<<"status = " << bytes.mid(44, 1);
        query.bindValue(":message", bytes.mid(47, 23));
        qDebug()<<"message = " << bytes.mid(47, 23);
        query.exec();

        recordData();

    }

    fillDataInfo();

    //bytes.clear();

}

void MainWindow::fillDataInfo()
{
    clearData();
    fillSensorInfo();

    //QString dateFrom = ui->dateTimeFrom->date().toString("yyyy-MM-dd");
    //QString dateTo = ui->dateTimeTo->date().toString("yyyy-MM-dd");
    QString date = QDate::currentDate().toString("yyyy-MM-dd");
    //QString sensor;
    QString data;

    /*if(ui->sensorCheckAll->isChecked()) {
        ui->sensorBoxSet->setCurrentIndex(ui->sensorBoxSet->findText("All"));
        sensor = ui->sensorBoxSet->itemData(ui->sensorBoxSet->currentIndex()).toString();
    } else  {
        ui->sensorBoxSet->removeItem(ui->sensorBoxSet->findText("All"));
        sensor = ui->sensorBoxSet->currentText();
    }*/

    foreach(QString sensor, listSensor) {
        //listSensor.removeOne(sensor);
        data = "SELECT * FROM tabMain "
               "WHERE date(datetime) = '%1' "
               "AND sensor = %2 "
               "ORDER BY id DESC LIMIT 1"; //ALL
        viewData(data.arg(date).arg(sensor));

        qDebug()<<"sensor = " << sensor;

    }

    /*switch (level) {
    case 0:
        data = "SELECT * FROM tabMain "
               "WHERE date(datetime) between '%1' and '%2' "
               "AND sensor IN (%3) "
               "ORDER BY id DESC LIMIT %4"; //ALL
        viewData(data.arg(dateFrom).arg(dateTo).arg(sensor).arg(limit));
        ui->loglevelStatus->setStyleSheet("QLabel {color:black;}");
        break;

    case 1:
        data = "SELECT * FROM tabMain "
               "WHERE status NOT IN (6,7,8,9) "
               "AND date(datetime) between '%1' and '%2' "
               "AND sensor IN (%3) "
               "ORDER BY id DESC LIMIT %4"; //INFO
        viewData(data.arg(dateFrom).arg(dateTo).arg(sensor).arg(limit));
        ui->loglevelStatus->setStyleSheet("QLabel {color:green;}");
        break;

    case 2:
        data = "SELECT * FROM tabMain "
               "WHERE status IN (8,9) "
               "AND date(datetime) between '%1' and '%2' "
               "AND sensor IN (%3) "
               "ORDER BY id DESC LIMIT %4"; //WARNING
        viewData(data.arg(dateFrom).arg(dateTo).arg(sensor).arg(limit));
        ui->loglevelStatus->setStyleSheet("QLabel {color:yellow;}");
        break;

    case 3:
        data = "SELECT * FROM tabMain "
               "WHERE status IN (6,7) "
               "AND date(datetime) between '%1' and '%2' "
               "AND sensor IN (%3) "
               "ORDER BY id DESC LIMIT %4"; //ERROR
        viewData(data.arg(dateFrom).arg(dateTo).arg(sensor).arg(limit));
        ui->loglevelStatus->setStyleSheet("QLabel {color:red;}");
        break;

    }*/

}

void MainWindow::fillSensorInfo()
{
    listSensor.clear();
    QString last = ui->sensorBoxSet->currentText();
    QString date = QDate::currentDate().toString("yyyy-MM-dd");
    QSqlQuery query;
    query.prepare(QString("SELECT DISTINCT sensor FROM tabMain "
                          "WHERE date(datetime)='%1'").arg(date));
    query.exec();
    while(query.next()) {
        listSensor.append(query.value(0).toString());

    }
    //listSensor = QStringList(list.join(", "));
    qDebug()<<"listSensor = " << listSensor;

    ui->sensorBoxSet->clear();
    ui->sensorBoxSet->addItems(listSensor);
    ui->sensorBoxSet->addItem(tr("All"), listSensor);
    ui->sensorBoxSet->setCurrentText(last);

    ui->sensorBoxExport->clear();
    ui->sensorBoxExport->addItems(listSensor);
    ui->sensorBoxExport->addItem(tr("All"), listSensor);
    ui->sensorBoxExport->setCurrentText(last);

}

void MainWindow::viewData(QString data)
{
    QSqlQuery query;
    QSqlRecord recordCount;
    query.prepare(QString("SELECT COUNT(*) FROM (%1) AS subquery").arg(data));
    query.exec();
    query.next();    
    recordCount = query.record();

    int value = 0;
    int qSize = query.value(0).toInt();

    qDebug()<<"count = "<<qSize;

    progressBar->setMaximum(qSize);
    progressBar->show();

    query.exec(data);
    while (query.next())
    {
        ui->tableWidget->insertRow(0);
        ui->tableWidget->setRowHeight(0, 20);
        ui->tableWidget->setItem(0, 0, new QTableWidgetItem(query.value(0).toInt()));
        ui->tableWidget->setItem(0, 1, new QTableWidgetItem(query.value(1).toDateTime().toString()));
        ui->tableWidget->setItem(0, 2, new QTableWidgetItem(query.value(2).toString()));
        ui->tableWidget->setItem(0, 3, new QTableWidgetItem(query.value(3).toString()));
        ui->tableWidget->setItem(0, 4, new QTableWidgetItem(query.value(4).toString()));

        progressBar->setValue(++value);

        QString status = query.value(3).toString();

        if (status=="6" || status=="7") {
            for ( int j = 0; j < 5; j++) ui->tableWidget->item(0, j)->setBackground(Qt::red);
            //ui->errorCount->setText();

        }
        else if (status=="8" || status=="9") {
            for ( int j = 0; j < 5; j++) ui->tableWidget->item(0, j)->setBackground(Qt::yellow);
            //ui->warningCount->setText();

        }
        else {
            for ( int j = 0; j < 5; j++) ui->tableWidget->item(0, j)->setBackground(Qt::green);
            //ui->infoCount->setText();

        }

    }

    //qDebug()<<query.isValid();
    //qDebug()<<query.lastError();
    qDebug()<<query.lastQuery();

    if(ui->tableWidget->rowCount()!=0) {
        //ui->tableWidget->scrollToBottom();
        ui->actionClear->setEnabled(true);
        ui->actionCopy->setEnabled(true);

    }

    progressBar->reset();
    progressBar->hide();

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
    progressBar->show();
    progressBar->setMaximum(ui->tableWidget->rowCount());

    QString filename = QFileDialog::getSaveFileName(this, tr("Export to:"), "com-monitor.csv",
                                                    "CSV files (*.csv)", 0, 0);
    QFile file(filename);
    if(file.open(QFile::WriteOnly |QFile::Truncate)) {
        QTextStream output(&file);
        QStringList strList;
        //strList <<"\" " +ui->tableWidget->horizontalHeaderItem(0)->data(Qt::DisplayRole).toString() +"\" ";

        for( int r = 0; r < ui->tableWidget->rowCount(); ++r ) {
            progressBar->setValue(r);

            strList.clear();
            for( int c = 0; c < ui->tableWidget->columnCount(); ++c ) {
                strList << "\" "+ui->tableWidget->item( r, c )->text()+"\" ";
            }
            output << strList.join( ";" )+"\n";
        }
        file.close();
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

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
#include <QtConcurrent/QtConcurrent>
#include <QtConcurrent/QtConcurrentMap>
#include <QSettings>

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
    refresh = new QTimer(this);

    progressBar = new QProgressBar(ui->statusBar);
    progressBar->setAlignment(Qt::AlignRight);
    progressBar->setFixedHeight(15);
    progressBar->setFixedWidth(150);
    //progressBar->setRange(0,100);
    progressBar->setValue(0);
    progressBar->setTextVisible(true);
    progressBar->setMinimum(0);
    //progressBar->setMaximum(100);
    progressBar->hide();

    ui->statusBar->addPermanentWidget(progressBar);

    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionQuit->setEnabled(true);
    ui->actionConfigure->setEnabled(true);
    ui->actionRefresh->setEnabled(false);

    ui->logLevelBox->addItem(tr("All (AA)"));
    ui->logLevelBox->addItem(tr("Info (II)"));
    ui->logLevelBox->addItem(tr("Warning (WW)"));
    ui->logLevelBox->addItem(tr("Error (EE)"));

    ui->tableWidget->setColumnHidden(0, true);
    ui->dateTimeEdit->setDate(QDate::currentDate());

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

void MainWindow::initTimer(int interval)
{    
    if (serial->isOpen() && interval!=0) {
    refresh->setInterval(interval*1000);
    refresh->start();
    }
}

void MainWindow::initSerialPort()
{
    connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError)));
    connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));
}

void MainWindow::initActionsConnections()
{
    connect(console, SIGNAL(getData(QByteArray)), this, SLOT(writeData(QByteArray)));
    connect(refresh, SIGNAL(timeout()), this, SLOT(refreshData()));
    connect(ui->sensorCheck, SIGNAL(toggled(bool)), this, SLOT(fillDataInfo()));
    connect(ui->sensorBox, SIGNAL(activated(int)), this, SLOT(fillDataInfo()));
    connect(ui->dateTimeEdit, SIGNAL(dateChanged(QDate)), this, SLOT(fillDataInfo()));
    connect(ui->logLevelBox, SIGNAL(activated(int)), this, SLOT(fillDataInfo()));
    connect(ui->exportButton, SIGNAL(pressed()), this, SLOT(exportData()));
    connect(ui->actionConnect, SIGNAL(triggered()), this, SLOT(openSerialPort()));
    connect(ui->actionDisconnect, SIGNAL(triggered()), this, SLOT(closeSerialPort()));
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionConfigure, SIGNAL(triggered()), settings, SLOT(show()));
    connect(ui->actionClear, SIGNAL(triggered()), console, SLOT(clear()));
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
               "id INTEGER primary key, "
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

    //qDebug()<<db.lastError().text();
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
    if (serial->open(QIODevice::ReadWrite)) {            
            ui->actionConnect->setEnabled(false);
            ui->actionDisconnect->setEnabled(true);
            ui->actionConfigure->setEnabled(false);
            ui->actionRefresh->setEnabled(true);
            initTimer(p.refresh);
            console->putData("Connected");
            ui->statusBar->showMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                                       .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
                                       .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));

    } else {
        QMessageBox::critical(this, tr("Error"), serial->errorString());        
        ui->statusBar->showMessage(tr("Open error"));        
        console->putData("Error opened port");

    }
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
    console->putData("Disconnected");
    refresh->stop();

}

void MainWindow::writeData(const QByteArray &data)
{    
    serial->write(data);
    qDebug()<<"write = " << data;

}

void MainWindow::readData()
{
    serial->waitForReadyRead(500);

    QByteArray bytes = serial->readAll();
    console->putData(bytes);

    qDebug()<<"read = " << bytes;

    QByteArray dataArray(65536, 0);
    dataArray.insert(0, bytes);

    QBitArray bits(bytes.count()*8);

    // Convert from QByteArray to QBitArray
    for(int i=0; i<bytes.count(); ++i) {
        for(int b=0; b<8; ++b) {
            bits.setBit( i*8+b, bytes.at(i)&(1<<(7-b)) );
        }
    }

    //qDebug()<<bytes<<" = "<<bits;

    if(dataArray.at(0)=='\r' && dataArray.at(1)=='\n') {
        processData(dataArray);
        recordData(dataArray);
        }
    dataArray = 0;

}

void MainWindow::processData(QByteArray data)
{
    QSqlQuery query;
    query.prepare("INSERT INTO tabMain (id, datetime, sensor, status, message) "
                  "VALUES (null , :datetime, :sensor, :status, :message)");
    query.bindValue(":datetime", QDateTime::currentDateTime());
    query.bindValue(":sensor", data.mid(39, 2).toInt());
    qDebug()<<"sensor = " << data.mid(39, 2);
    query.bindValue(":status", data.mid(44, 1).toInt());
    qDebug()<<"status = " << data.mid(44, 1);
    query.bindValue(":message", data.mid(47, 23));
    qDebug()<<"message = " << data.mid(47, 23);
    query.exec();    

    fillDataInfo();
}

void MainWindow::fillDataInfo()
{

    int level = ui->logLevelBox->currentIndex();
    QString date = ui->dateTimeEdit->date().toString("yyyy-MM-dd");
    QString sensor;
    QString data;

    fillSensorInfo();

    if(ui->sensorCheck->isChecked()) {
        ui->sensorBox->setCurrentIndex(ui->sensorBox->findText("All"));
        sensor = ui->sensorBox->itemData(ui->sensorBox->currentIndex()).toString();
    } else  {
        ui->sensorBox->removeItem(ui->sensorBox->findText("All"));
        sensor = ui->sensorBox->currentText();
    }

    qDebug()<<"logLevel = " << level;
    qDebug()<<"sensor = " << sensor;

    switch (level) {
    case 0:
        data = "SELECT * FROM tabMain "
               "WHERE date(datetime) = '%1' AND sensor IN (%2)"; //ALL
        viewData(data.arg(date).arg(sensor));
        break;

    case 1:
        data = "SELECT * FROM tabMain WHERE status NOT IN (6,7,8,9) "
               "AND date(datetime) = '%1' AND sensor IN (%2)"; //INFO
        viewData(data.arg(date).arg(sensor));
        break;

    case 2:
        data = "SELECT * FROM tabMain WHERE status IN (8,9) "
               "AND date(datetime) = '%1' AND sensor IN (%2)"; //WARNING
        viewData(data.arg(date).arg(sensor));
        break;

    case 3:
        data = "SELECT * FROM tabMain WHERE status IN (6,7) "
               "AND date(datetime) = '%1' AND sensor IN (%2)"; //ERROR
        viewData(data.arg(date).arg(sensor));
        break;

    }

}

void MainWindow::fillSensorInfo()
{
    QStringList list;    
    QString last = ui->sensorBox->currentText();
    QString date = ui->dateTimeEdit->date().toString("yyyy-MM-dd");
    QSqlQuery query;
    query.prepare(QString("SELECT DISTINCT sensor FROM tabMain WHERE date(datetime) = '%1'").arg(date));
    query.exec();
    qDebug()<<query.lastQuery();
    while(query.next()) {
        list.append(query.value(0).toString());

    }
    ui->sensorBox->clear();
    ui->sensorBox->addItems(list);
    ui->sensorBox->addItem(tr("All"), list.join(", "));
    ui->sensorBox->setCurrentText(last);

}

void MainWindow::viewData(QString data)
{
    int i = 0;
    int n = ui->tableWidget->rowCount();
    for( int i = 0; i < n; i++ ) ui->tableWidget->removeRow( 0 );

    QSqlQuery query;
    query.prepare(QString("SELECT COUNT(*) FROM (%1) AS subquery").arg(data));
    query.exec();
    query.next();
    QSqlRecord recordCount;
    recordCount = query.record();
    //int qSize = query.value(recordCount.indexOf("subquery")).toInt();
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

        progressBar->setValue(++i);

        QString status = query.value(3).toString();

        if (status=="6" || status=="7") {
            for ( int j = 0; j < 5; j++) ui->tableWidget->item(0, j)->setBackground(Qt::red);
            }
        else if (status=="8" || status=="9") {
            for ( int j = 0; j < 5; j++) ui->tableWidget->item(0, j)->setBackground(Qt::yellow);
            }
        else for ( int j = 0; j < 5; j++) ui->tableWidget->item(0, j)->setBackground(Qt::green);

    }

    //qDebug()<<query.isValid();
    //qDebug()<<query.lastError();
    //qDebug()<<query.lastQuery();
    console->putData(query.lastQuery());

    progressBar->reset();
    progressBar->hide();

}

void MainWindow::clearData()
{
    QSqlQuery query;
    query.exec("DELETE FROM tabMain");

    fillDataInfo();
}

void MainWindow::refreshData()
{
    if (serial->isOpen())
        writeData("AT^MONP\r");

}

void MainWindow::recordData(QString data)
{
    QString date = QDateTime::currentDateTime().toString(format);
    QFile file("com-monitor.log");
    if (file.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream out(&file);
        out << date << endl << data << endl;
        qDebug()<< "record = " << data;
        file.close();
    }
    else
    {
        qWarning("Can not open file.");
    }
}

void MainWindow::exportData()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Export to:"), "com-monitor.csv",
                                                    "CSV files (*.csv)", 0, 0);
    QFile file(filename);
    if(file.open(QFile::WriteOnly |QFile::Truncate)) {
        QTextStream output(&file);
        QStringList strList;
        //strList <<"\" " +ui->tableWidget->horizontalHeaderItem(0)->data(Qt::DisplayRole).toString() +"\" ";

        for( int r = 0; r < ui->tableWidget->rowCount(); ++r ) {
            strList.clear();
            for( int c = 0; c < ui->tableWidget->columnCount(); ++c ) {
                strList << "\" "+ui->tableWidget->item( r, c )->text()+"\" ";
            }
            output << strList.join( ";" )+"\n";
        }
        file.close();

    }

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

    settings.setValue("LogLevel", ui->logLevelBox->currentText());
    settings.setValue("LogLevelIndex", ui->logLevelBox->currentIndex());
    settings.setValue("Sensor", ui->sensorBox->currentText());
    settings.setValue("SensorCheckAll", ui->sensorCheck->isChecked());
    settings.setValue("DataBaseName", db.databaseName());

}

void MainWindow::loadSettings()
{
    QSettings settings(settingsFile, QSettings::IniFormat);

    ui->logLevelBox->setCurrentText(settings.value("LogLevel").toString());
    ui->logLevelBox->setCurrentIndex(settings.value("LogLevelIndex").toInt());
    ui->sensorBox->setCurrentText(settings.value("Sensor").toString());
    ui->sensorBox->setDisabled(settings.value("SensorCheckAll").toBool());
    ui->sensorCheck->setChecked(settings.value("SensorCheckAll").toBool());

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(settings.value("DataBaseName").toString());

}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About COM Monitor"),
                       tr("The <b>Com Monitor</b> (c) 2015."));
}

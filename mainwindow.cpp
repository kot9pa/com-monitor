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
#include <QLayout>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    console = new Console;
    serial = new QSerialPort(this);
    settings = new SettingsDialog;

    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionQuit->setEnabled(true);
    ui->actionConfigure->setEnabled(true);
    ui->actionRefresh->setEnabled(false);

    /*QWidget *ui_console = new QWidget;
    QHBoxLayout *console_layout = new QHBoxLayout;
    console_layout->addWidget(console);    

    ui_console->setLayout(console_layout);
    ui_console->show();*/

    initActionsConnections();
    initSerialPort();

}

MainWindow::~MainWindow()
{
    delete settings;
    delete console;
    delete ui;
}


void MainWindow::initSerialPort()
{
    connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError)));
    connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));
}

void MainWindow::initActionsConnections()
{
    connect(console, SIGNAL(getData(QByteArray)), this, SLOT(writeData(QByteArray)));
    connect(ui->actionConnect, SIGNAL(triggered()), this, SLOT(openSerialPort()));
    connect(ui->actionDisconnect, SIGNAL(triggered()), this, SLOT(closeSerialPort()));
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionConfigure, SIGNAL(triggered()), settings, SLOT(show()));
    connect(ui->actionClear, SIGNAL(triggered()), console, SLOT(clear()));
    connect(ui->actionConsole, SIGNAL(triggered()), console, SLOT(show()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(about()));
    connect(ui->actionRefresh, SIGNAL(triggered(bool)), this, SLOT(refreshData()));

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
            printData("Connected");
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
        printData("Connected");

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
    printData("Disconnected");

}

void MainWindow::writeData(const QByteArray &data)
{    
    serial->write(data);
    qDebug()<<"write = " << data;    

}

void MainWindow::readData()
{
    QByteArray data = serial->readAll();
    console->putData(data);
    //printData(data);
    qDebug()<<"read = " << data;

}

void MainWindow::printData(QString data)
{
    ui->console->textCursor().insertText(data+'\r');
    ui->console->moveCursor(QTextCursor::End);
    qDebug()<<"print = " << data;

}

void MainWindow::refreshData()
{
    /*char buffer[] = "AT";

    int numWrite = serial->write(buffer);
    QByteArray numRead = serial->readAll();

    printData(QString::number(numWrite));
    printData(numRead);

    qDebug()<<"numWrite = " << numWrite;
    qDebug()<<"numRead = " << numRead;*/

    writeData("AT\r");
    readData();

}

void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
        closeSerialPort();
    }
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About COM Monitor"),
                       tr("The <b>Com Monitor</b> (c) 2015."));
}

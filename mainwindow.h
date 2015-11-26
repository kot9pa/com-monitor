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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QtGlobal>
#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSql>
#include <QProgressBar>

QT_BEGIN_NAMESPACE

namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE

class Console;
class SettingsDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void writeRequest(const QByteArray &data);

private slots:
    void openSerialPort();
    void closeSerialPort();
    void customMenuRequest(const QPoint &pos);
    void initTimer();
    void currentDateTime();
    void writeData(const QByteArray &data);
    void fillDataInfo();
    void readData();
    void clearData();
    void viewData(QString data);
    void recordData();
    void refreshData();
    void processData();
    void exportData();
    void copyData();
    void handleError(QSerialPort::SerialPortError error);
    void about();

private:    
    void initActionsConnections();
    void initSerialPort();
    void initTable();
    void fillSensorInfo();
    void loadSettings();
    void saveSettings();

private:
    Ui::MainWindow *ui;
    QProgressBar *progressBar;
    SettingsDialog *settings;
    QSerialPort *serial;
    Console *console;
    QMenu *menu;
    QTimer *refresh;
    QTimer *timer;
    QByteArray bytes;
    QByteArray msg;
    QString format;
    QString settingsFile;
    QStringList listSensor;
    QSqlDatabase db;
    int warningCount;
    int errorCount;
    int infoCount;

};

#endif // MAINWINDOW_H

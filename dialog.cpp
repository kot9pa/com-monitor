#include "dialog.h"
#include "ui_dialog.h"
#include <QSettings>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    QString settingsFile = QApplication::applicationDirPath() + "/com-monitor.ini";
    QSettings settings(settingsFile, QSettings::IniFormat);

    db = QSqlDatabase::cloneDatabase(db, settings.value("DataBaseName").toString());
    db.open();

}

void Dialog::viewData(QString data)
{

    int n = ui->tableWidget->rowCount();
    for( int i = 0; i < n; i++ ) ui->tableWidget->removeRow(0);
    ui->tableWidget->setColumnHidden(0, true);

    QSqlQuery query;
    query.exec(data);
    while (query.next()) {

        ui->tableWidget->insertRow(0);
        ui->tableWidget->setRowHeight(0, 20);
        ui->tableWidget->setItem(0, 0, new QTableWidgetItem(query.value(0).toInt()));
        ui->tableWidget->setItem(0, 1, new QTableWidgetItem(query.value(1).toDateTime().toString()));
        ui->tableWidget->setItem(0, 2, new QTableWidgetItem(query.value(2).toString()));
        ui->tableWidget->setItem(0, 3, new QTableWidgetItem(query.value(3).toString()));
        ui->tableWidget->setItem(0, 4, new QTableWidgetItem(query.value(4).toString()));

    }

    qDebug()<<query.lastQuery();

    ui->tableWidget->resizeColumnsToContents();

}

Dialog::~Dialog()
{
    db.close();
    delete ui;
}

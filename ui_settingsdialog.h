/********************************************************************************
** Form generated from reading UI file 'settingsdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSDIALOG_H
#define UI_SETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_SettingsDialog
{
public:
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout;
    QPushButton *saveButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *applyButton;
    QGroupBox *parametersBox;
    QGridLayout *gridLayout_2;
    QLabel *parityLabel;
    QLabel *baudRateLabel;
    QComboBox *dataBitsBox;
    QComboBox *parityBox;
    QLabel *dataBitsLabel;
    QComboBox *baudRateBox;
    QLabel *flowControlLabel;
    QComboBox *stopBitsBox;
    QComboBox *flowControlBox;
    QLabel *stopBitsLabel;
    QGroupBox *selectBox;
    QGridLayout *gridLayout;
    QLabel *descriptionLabel;
    QLabel *manufacturerLabel;
    QLabel *serialNumberLabel;
    QLabel *locationLabel;
    QLabel *vidLabel;
    QLabel *pidLabel;
    QGroupBox *additionalOptionsGroupBox;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *searchButton;
    QComboBox *serialPortInfoListBox;
    QGroupBox *refreshOption;
    QHBoxLayout *horizontalLayout_2;
    QLabel *refreshLabel;
    QComboBox *refreshBox;

    void setupUi(QDialog *SettingsDialog)
    {
        if (SettingsDialog->objectName().isEmpty())
            SettingsDialog->setObjectName(QStringLiteral("SettingsDialog"));
        SettingsDialog->resize(415, 268);
        SettingsDialog->setMinimumSize(QSize(415, 268));
        SettingsDialog->setMaximumSize(QSize(16777215, 268));
        gridLayout_3 = new QGridLayout(SettingsDialog);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        saveButton = new QPushButton(SettingsDialog);
        saveButton->setObjectName(QStringLiteral("saveButton"));

        horizontalLayout->addWidget(saveButton);

        horizontalSpacer = new QSpacerItem(96, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        applyButton = new QPushButton(SettingsDialog);
        applyButton->setObjectName(QStringLiteral("applyButton"));

        horizontalLayout->addWidget(applyButton);


        gridLayout_3->addLayout(horizontalLayout, 3, 0, 1, 2);

        parametersBox = new QGroupBox(SettingsDialog);
        parametersBox->setObjectName(QStringLiteral("parametersBox"));
        gridLayout_2 = new QGridLayout(parametersBox);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        parityLabel = new QLabel(parametersBox);
        parityLabel->setObjectName(QStringLiteral("parityLabel"));

        gridLayout_2->addWidget(parityLabel, 2, 0, 1, 1);

        baudRateLabel = new QLabel(parametersBox);
        baudRateLabel->setObjectName(QStringLiteral("baudRateLabel"));

        gridLayout_2->addWidget(baudRateLabel, 0, 0, 1, 1);

        dataBitsBox = new QComboBox(parametersBox);
        dataBitsBox->setObjectName(QStringLiteral("dataBitsBox"));

        gridLayout_2->addWidget(dataBitsBox, 1, 1, 1, 1);

        parityBox = new QComboBox(parametersBox);
        parityBox->setObjectName(QStringLiteral("parityBox"));

        gridLayout_2->addWidget(parityBox, 2, 1, 1, 1);

        dataBitsLabel = new QLabel(parametersBox);
        dataBitsLabel->setObjectName(QStringLiteral("dataBitsLabel"));

        gridLayout_2->addWidget(dataBitsLabel, 1, 0, 1, 1);

        baudRateBox = new QComboBox(parametersBox);
        baudRateBox->setObjectName(QStringLiteral("baudRateBox"));

        gridLayout_2->addWidget(baudRateBox, 0, 1, 1, 1);

        flowControlLabel = new QLabel(parametersBox);
        flowControlLabel->setObjectName(QStringLiteral("flowControlLabel"));

        gridLayout_2->addWidget(flowControlLabel, 4, 0, 1, 1);

        stopBitsBox = new QComboBox(parametersBox);
        stopBitsBox->setObjectName(QStringLiteral("stopBitsBox"));

        gridLayout_2->addWidget(stopBitsBox, 3, 1, 1, 1);

        flowControlBox = new QComboBox(parametersBox);
        flowControlBox->setObjectName(QStringLiteral("flowControlBox"));

        gridLayout_2->addWidget(flowControlBox, 4, 1, 1, 1);

        stopBitsLabel = new QLabel(parametersBox);
        stopBitsLabel->setObjectName(QStringLiteral("stopBitsLabel"));

        gridLayout_2->addWidget(stopBitsLabel, 3, 0, 1, 1);


        gridLayout_3->addWidget(parametersBox, 1, 1, 1, 1);

        selectBox = new QGroupBox(SettingsDialog);
        selectBox->setObjectName(QStringLiteral("selectBox"));
        gridLayout = new QGridLayout(selectBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        descriptionLabel = new QLabel(selectBox);
        descriptionLabel->setObjectName(QStringLiteral("descriptionLabel"));

        gridLayout->addWidget(descriptionLabel, 1, 0, 1, 1);

        manufacturerLabel = new QLabel(selectBox);
        manufacturerLabel->setObjectName(QStringLiteral("manufacturerLabel"));

        gridLayout->addWidget(manufacturerLabel, 2, 0, 1, 1);

        serialNumberLabel = new QLabel(selectBox);
        serialNumberLabel->setObjectName(QStringLiteral("serialNumberLabel"));

        gridLayout->addWidget(serialNumberLabel, 3, 0, 1, 1);

        locationLabel = new QLabel(selectBox);
        locationLabel->setObjectName(QStringLiteral("locationLabel"));

        gridLayout->addWidget(locationLabel, 4, 0, 1, 1);

        vidLabel = new QLabel(selectBox);
        vidLabel->setObjectName(QStringLiteral("vidLabel"));

        gridLayout->addWidget(vidLabel, 5, 0, 1, 1);

        pidLabel = new QLabel(selectBox);
        pidLabel->setObjectName(QStringLiteral("pidLabel"));

        gridLayout->addWidget(pidLabel, 6, 0, 1, 1);


        gridLayout_3->addWidget(selectBox, 1, 0, 1, 1);

        additionalOptionsGroupBox = new QGroupBox(SettingsDialog);
        additionalOptionsGroupBox->setObjectName(QStringLiteral("additionalOptionsGroupBox"));
        horizontalLayout_3 = new QHBoxLayout(additionalOptionsGroupBox);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        searchButton = new QPushButton(additionalOptionsGroupBox);
        searchButton->setObjectName(QStringLiteral("searchButton"));

        horizontalLayout_3->addWidget(searchButton);

        serialPortInfoListBox = new QComboBox(additionalOptionsGroupBox);
        serialPortInfoListBox->setObjectName(QStringLiteral("serialPortInfoListBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(serialPortInfoListBox->sizePolicy().hasHeightForWidth());
        serialPortInfoListBox->setSizePolicy(sizePolicy);
        serialPortInfoListBox->setMaximumSize(QSize(73, 22));
        serialPortInfoListBox->setLayoutDirection(Qt::LeftToRight);

        horizontalLayout_3->addWidget(serialPortInfoListBox);


        gridLayout_3->addWidget(additionalOptionsGroupBox, 0, 0, 1, 1);

        refreshOption = new QGroupBox(SettingsDialog);
        refreshOption->setObjectName(QStringLiteral("refreshOption"));
        horizontalLayout_2 = new QHBoxLayout(refreshOption);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        refreshLabel = new QLabel(refreshOption);
        refreshLabel->setObjectName(QStringLiteral("refreshLabel"));

        horizontalLayout_2->addWidget(refreshLabel);

        refreshBox = new QComboBox(refreshOption);
        refreshBox->setObjectName(QStringLiteral("refreshBox"));

        horizontalLayout_2->addWidget(refreshBox);


        gridLayout_3->addWidget(refreshOption, 0, 1, 1, 1);

        QWidget::setTabOrder(searchButton, serialPortInfoListBox);
        QWidget::setTabOrder(serialPortInfoListBox, baudRateBox);
        QWidget::setTabOrder(baudRateBox, dataBitsBox);
        QWidget::setTabOrder(dataBitsBox, parityBox);
        QWidget::setTabOrder(parityBox, stopBitsBox);
        QWidget::setTabOrder(stopBitsBox, flowControlBox);
        QWidget::setTabOrder(flowControlBox, saveButton);
        QWidget::setTabOrder(saveButton, applyButton);

        retranslateUi(SettingsDialog);

        QMetaObject::connectSlotsByName(SettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingsDialog)
    {
        SettingsDialog->setWindowTitle(QApplication::translate("SettingsDialog", "Settings", 0));
        saveButton->setText(QApplication::translate("SettingsDialog", "Save", 0));
        applyButton->setText(QApplication::translate("SettingsDialog", "Apply", 0));
        parametersBox->setTitle(QApplication::translate("SettingsDialog", "Select Parameters", 0));
        parityLabel->setText(QApplication::translate("SettingsDialog", "Parity:", 0));
        baudRateLabel->setText(QApplication::translate("SettingsDialog", "BaudRate:", 0));
        dataBitsLabel->setText(QApplication::translate("SettingsDialog", "Data bits:", 0));
        flowControlLabel->setText(QApplication::translate("SettingsDialog", "Flow control:", 0));
        stopBitsLabel->setText(QApplication::translate("SettingsDialog", "Stop bits:", 0));
        selectBox->setTitle(QApplication::translate("SettingsDialog", "Select Serial Port", 0));
        descriptionLabel->setText(QApplication::translate("SettingsDialog", "Description:", 0));
        manufacturerLabel->setText(QApplication::translate("SettingsDialog", "Manufacturer:", 0));
        serialNumberLabel->setText(QApplication::translate("SettingsDialog", "Serial number:", 0));
        locationLabel->setText(QApplication::translate("SettingsDialog", "Location:", 0));
        vidLabel->setText(QApplication::translate("SettingsDialog", "Vendor ID:", 0));
        pidLabel->setText(QApplication::translate("SettingsDialog", "Product ID:", 0));
        additionalOptionsGroupBox->setTitle(QApplication::translate("SettingsDialog", "Search Options", 0));
        searchButton->setText(QApplication::translate("SettingsDialog", "Search device", 0));
        refreshOption->setTitle(QApplication::translate("SettingsDialog", "Refresh Options", 0));
        refreshLabel->setText(QApplication::translate("SettingsDialog", "Interval (sec):", 0));
    } // retranslateUi

};

namespace Ui {
    class SettingsDialog: public Ui_SettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSDIALOG_H

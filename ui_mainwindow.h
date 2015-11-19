/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAbout;
    QAction *actionConnect;
    QAction *actionDisconnect;
    QAction *actionConfigure;
    QAction *actionQuit;
    QAction *actionToolBar;
    QAction *actionStatusBar;
    QAction *actionClear;
    QAction *actionRefresh;
    QAction *actionConsole;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidget;
    QTabWidget *tabWidget;
    QWidget *log;
    QHBoxLayout *horizontalLayout;
    QDateTimeEdit *dateTimeEdit;
    QLabel *loglevelTime;
    QComboBox *logLevelBox;
    QLabel *sensorNumber;
    QComboBox *sensorBox;
    QCheckBox *sensorCheck;
    QSpacerItem *horizontalSpacer;
    QWidget *export_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *exportButton;
    QLabel *exportLabel;
    QSpacerItem *horizontalSpacer_2;
    QMenuBar *menuBar;
    QMenu *menuCalls;
    QMenu *menuTools;
    QMenu *menuHelp;
    QMenu *menuView;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setWindowModality(Qt::NonModal);
        MainWindow->resize(451, 493);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(451, 493));
        MainWindow->setMaximumSize(QSize(16777215, 16777215));
        MainWindow->setCursor(QCursor(Qt::ArrowCursor));
        MainWindow->setContextMenuPolicy(Qt::DefaultContextMenu);
        MainWindow->setLayoutDirection(Qt::LeftToRight);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionConnect = new QAction(MainWindow);
        actionConnect->setObjectName(QStringLiteral("actionConnect"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/connect.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionConnect->setIcon(icon);
        actionDisconnect = new QAction(MainWindow);
        actionDisconnect->setObjectName(QStringLiteral("actionDisconnect"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/disconnect.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDisconnect->setIcon(icon1);
        actionConfigure = new QAction(MainWindow);
        actionConfigure->setObjectName(QStringLiteral("actionConfigure"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/settings.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionConfigure->setIcon(icon2);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/images/application-exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionQuit->setIcon(icon3);
        actionToolBar = new QAction(MainWindow);
        actionToolBar->setObjectName(QStringLiteral("actionToolBar"));
        actionToolBar->setCheckable(true);
        actionToolBar->setChecked(true);
        actionStatusBar = new QAction(MainWindow);
        actionStatusBar->setObjectName(QStringLiteral("actionStatusBar"));
        actionStatusBar->setCheckable(true);
        actionStatusBar->setChecked(true);
        actionClear = new QAction(MainWindow);
        actionClear->setObjectName(QStringLiteral("actionClear"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/images/clear.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionClear->setIcon(icon4);
        actionRefresh = new QAction(MainWindow);
        actionRefresh->setObjectName(QStringLiteral("actionRefresh"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/images/refresh.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRefresh->setIcon(icon5);
        actionConsole = new QAction(MainWindow);
        actionConsole->setObjectName(QStringLiteral("actionConsole"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/images/console.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionConsole->setIcon(icon6);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setEnabled(true);
        centralWidget->setLayoutDirection(Qt::LeftToRight);
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tableWidget = new QTableWidget(centralWidget);
        if (tableWidget->columnCount() < 5)
            tableWidget->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setMinimumSize(QSize(441, 341));
        tableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget->setSortingEnabled(false);
        tableWidget->setColumnCount(5);
        tableWidget->horizontalHeader()->setDefaultSectionSize(100);
        tableWidget->horizontalHeader()->setMinimumSectionSize(37);
        tableWidget->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableWidget->verticalHeader()->setDefaultSectionSize(30);
        tableWidget->verticalHeader()->setProperty("showSortIndicator", QVariant(false));

        verticalLayout->addWidget(tableWidget);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setEnabled(true);
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setMinimumSize(QSize(441, 71));
        tabWidget->setTabsClosable(false);
        log = new QWidget();
        log->setObjectName(QStringLiteral("log"));
        horizontalLayout = new QHBoxLayout(log);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        dateTimeEdit = new QDateTimeEdit(log);
        dateTimeEdit->setObjectName(QStringLiteral("dateTimeEdit"));
        dateTimeEdit->setCalendarPopup(true);

        horizontalLayout->addWidget(dateTimeEdit);

        loglevelTime = new QLabel(log);
        loglevelTime->setObjectName(QStringLiteral("loglevelTime"));

        horizontalLayout->addWidget(loglevelTime);

        logLevelBox = new QComboBox(log);
        logLevelBox->setObjectName(QStringLiteral("logLevelBox"));
        logLevelBox->setSizeAdjustPolicy(QComboBox::AdjustToContentsOnFirstShow);

        horizontalLayout->addWidget(logLevelBox);

        sensorNumber = new QLabel(log);
        sensorNumber->setObjectName(QStringLiteral("sensorNumber"));

        horizontalLayout->addWidget(sensorNumber);

        sensorBox = new QComboBox(log);
        sensorBox->setObjectName(QStringLiteral("sensorBox"));
        sensorBox->setEnabled(true);
        sensorBox->setSizeAdjustPolicy(QComboBox::AdjustToContentsOnFirstShow);

        horizontalLayout->addWidget(sensorBox);

        sensorCheck = new QCheckBox(log);
        sensorCheck->setObjectName(QStringLiteral("sensorCheck"));

        horizontalLayout->addWidget(sensorCheck);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        tabWidget->addTab(log, QString());
        export_2 = new QWidget();
        export_2->setObjectName(QStringLiteral("export_2"));
        horizontalLayout_2 = new QHBoxLayout(export_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        exportButton = new QPushButton(export_2);
        exportButton->setObjectName(QStringLiteral("exportButton"));

        horizontalLayout_2->addWidget(exportButton);

        exportLabel = new QLabel(export_2);
        exportLabel->setObjectName(QStringLiteral("exportLabel"));

        horizontalLayout_2->addWidget(exportLabel);

        horizontalSpacer_2 = new QSpacerItem(259, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        tabWidget->addTab(export_2, QString());

        verticalLayout->addWidget(tabWidget);


        verticalLayout_2->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 451, 21));
        menuCalls = new QMenu(menuBar);
        menuCalls->setObjectName(QStringLiteral("menuCalls"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QStringLiteral("menuTools"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QStringLiteral("menuView"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setCursor(QCursor(Qt::ArrowCursor));
        mainToolBar->setContextMenuPolicy(Qt::DefaultContextMenu);
        mainToolBar->setMovable(false);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuCalls->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuCalls->addAction(actionConnect);
        menuCalls->addAction(actionDisconnect);
        menuCalls->addSeparator();
        menuCalls->addAction(actionQuit);
        menuTools->addAction(actionConfigure);
        menuTools->addAction(actionClear);
        menuTools->addAction(actionRefresh);
        menuTools->addAction(actionConsole);
        menuHelp->addAction(actionAbout);
        menuView->addAction(actionToolBar);
        menuView->addAction(actionStatusBar);
        mainToolBar->addAction(actionConnect);
        mainToolBar->addAction(actionDisconnect);
        mainToolBar->addAction(actionConfigure);
        mainToolBar->addAction(actionClear);
        mainToolBar->addAction(actionRefresh);
        mainToolBar->addAction(actionConsole);

        retranslateUi(MainWindow);
        QObject::connect(actionToolBar, SIGNAL(toggled(bool)), mainToolBar, SLOT(setVisible(bool)));
        QObject::connect(actionStatusBar, SIGNAL(toggled(bool)), statusBar, SLOT(setVisible(bool)));
        QObject::connect(sensorCheck, SIGNAL(toggled(bool)), sensorBox, SLOT(setDisabled(bool)));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "COM Monitor", 0));
        actionAbout->setText(QApplication::translate("MainWindow", "&About", 0));
#ifndef QT_NO_TOOLTIP
        actionAbout->setToolTip(QApplication::translate("MainWindow", "About program", 0));
#endif // QT_NO_TOOLTIP
        actionAbout->setShortcut(QApplication::translate("MainWindow", "Alt+A", 0));
        actionConnect->setText(QApplication::translate("MainWindow", "C&onnect", 0));
#ifndef QT_NO_TOOLTIP
        actionConnect->setToolTip(QApplication::translate("MainWindow", "Connect to serial port", 0));
#endif // QT_NO_TOOLTIP
        actionConnect->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0));
        actionDisconnect->setText(QApplication::translate("MainWindow", "&Disconnect", 0));
#ifndef QT_NO_TOOLTIP
        actionDisconnect->setToolTip(QApplication::translate("MainWindow", "Disconnect from serial port", 0));
#endif // QT_NO_TOOLTIP
        actionDisconnect->setShortcut(QApplication::translate("MainWindow", "Ctrl+D", 0));
        actionConfigure->setText(QApplication::translate("MainWindow", "&Configure", 0));
#ifndef QT_NO_TOOLTIP
        actionConfigure->setToolTip(QApplication::translate("MainWindow", "Configure serial port", 0));
#endif // QT_NO_TOOLTIP
        actionConfigure->setShortcut(QApplication::translate("MainWindow", "Alt+S", 0));
        actionQuit->setText(QApplication::translate("MainWindow", "&Quit", 0));
        actionQuit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0));
        actionToolBar->setText(QApplication::translate("MainWindow", "ToolBar", 0));
        actionStatusBar->setText(QApplication::translate("MainWindow", "StatusBar", 0));
        actionClear->setText(QApplication::translate("MainWindow", "&Clear", 0));
        actionClear->setShortcut(QApplication::translate("MainWindow", "Alt+R", 0));
        actionRefresh->setText(QApplication::translate("MainWindow", "&Refresh", 0));
        actionRefresh->setShortcut(QApplication::translate("MainWindow", "Alt+U", 0));
        actionConsole->setText(QApplication::translate("MainWindow", "&Console", 0));
        actionConsole->setShortcut(QApplication::translate("MainWindow", "Alt+C", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "ID", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "Date", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "Sensor", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "Status", 0));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "Message", 0));
        dateTimeEdit->setDisplayFormat(QApplication::translate("MainWindow", "dd.MM.yyyy", 0));
        loglevelTime->setText(QApplication::translate("MainWindow", "Log Level:", 0));
        sensorNumber->setText(QApplication::translate("MainWindow", "Sensor:", 0));
        sensorCheck->setText(QApplication::translate("MainWindow", "All Sensors", 0));
        tabWidget->setTabText(tabWidget->indexOf(log), QApplication::translate("MainWindow", "View Options", 0));
        exportButton->setText(QApplication::translate("MainWindow", "Export", 0));
        exportLabel->setText(QApplication::translate("MainWindow", "(Export to .csv)", 0));
        tabWidget->setTabText(tabWidget->indexOf(export_2), QApplication::translate("MainWindow", "Export data", 0));
        menuCalls->setTitle(QApplication::translate("MainWindow", "Calls", 0));
        menuTools->setTitle(QApplication::translate("MainWindow", "Tools", 0));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0));
        menuView->setTitle(QApplication::translate("MainWindow", "View", 0));
        mainToolBar->setWindowTitle(QApplication::translate("MainWindow", "ToolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

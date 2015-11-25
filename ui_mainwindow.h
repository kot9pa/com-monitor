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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
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
    QAction *actionCopy;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidget;
    QTabWidget *tabWidget;
    QWidget *viewTab;
    QGridLayout *gridLayout_2;
    QLCDNumber *dateCurrent;
    QGroupBox *status;
    QGridLayout *gridLayout;
    QLabel *infoLabel;
    QLabel *infoCount;
    QLabel *warningLabel;
    QLabel *warningCount;
    QLabel *errorLabel;
    QLabel *errorCount;
    QSpacerItem *horizontalSpacer;
    QLCDNumber *timeCurrent;
    QWidget *controlTab;
    QGridLayout *gridLayout_5;
    QGroupBox *control;
    QGridLayout *gridLayout_3;
    QLabel *sensorLabel_2;
    QComboBox *sensorBoxSet;
    QCheckBox *sensorCheckAllSet;
    QLabel *sensorLabel_3;
    QComboBox *dataBoxSet;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *readButton;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *writeButton;
    QWidget *exportTab;
    QGridLayout *gridLayout_4;
    QLabel *from;
    QDateTimeEdit *dateTimeTo;
    QLabel *logLevelLabel;
    QComboBox *logBoxExport;
    QLabel *sensorLabel;
    QComboBox *sensorBoxExport;
    QLabel *to;
    QCheckBox *sensorCheckAllExport;
    QSpacerItem *horizontalSpacer_4;
    QDateTimeEdit *dateTimeFrom;
    QPushButton *exportButton;
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
        MainWindow->resize(525, 548);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(0, 0));
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
        actionCopy = new QAction(MainWindow);
        actionCopy->setObjectName(QStringLiteral("actionCopy"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/images/copy.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCopy->setIcon(icon7);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setEnabled(true);
        centralWidget->setLayoutDirection(Qt::LeftToRight);
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
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
        tableWidget->setMinimumSize(QSize(441, 340));
        tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
        tableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContentsOnFirstShow);
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
        tabWidget->setMinimumSize(QSize(525, 127));
        tabWidget->setMaximumSize(QSize(16777215, 129));
        tabWidget->setTabsClosable(false);
        viewTab = new QWidget();
        viewTab->setObjectName(QStringLiteral("viewTab"));
        gridLayout_2 = new QGridLayout(viewTab);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        dateCurrent = new QLCDNumber(viewTab);
        dateCurrent->setObjectName(QStringLiteral("dateCurrent"));
        dateCurrent->setMinimumSize(QSize(141, 0));
        dateCurrent->setFrameShape(QFrame::NoFrame);
        dateCurrent->setFrameShadow(QFrame::Raised);
        dateCurrent->setLineWidth(1);
        dateCurrent->setMidLineWidth(0);
        dateCurrent->setSmallDecimalPoint(false);
        dateCurrent->setDigitCount(10);
        dateCurrent->setSegmentStyle(QLCDNumber::Filled);
        dateCurrent->setProperty("value", QVariant(0));

        gridLayout_2->addWidget(dateCurrent, 0, 0, 1, 1);

        status = new QGroupBox(viewTab);
        status->setObjectName(QStringLiteral("status"));
        gridLayout = new QGridLayout(status);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        infoLabel = new QLabel(status);
        infoLabel->setObjectName(QStringLiteral("infoLabel"));
        infoLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(infoLabel, 0, 0, 1, 1);

        infoCount = new QLabel(status);
        infoCount->setObjectName(QStringLiteral("infoCount"));

        gridLayout->addWidget(infoCount, 0, 1, 1, 1);

        warningLabel = new QLabel(status);
        warningLabel->setObjectName(QStringLiteral("warningLabel"));
        warningLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(warningLabel, 1, 0, 1, 1);

        warningCount = new QLabel(status);
        warningCount->setObjectName(QStringLiteral("warningCount"));

        gridLayout->addWidget(warningCount, 1, 1, 1, 1);

        errorLabel = new QLabel(status);
        errorLabel->setObjectName(QStringLiteral("errorLabel"));
        errorLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(errorLabel, 2, 0, 1, 1);

        errorCount = new QLabel(status);
        errorCount->setObjectName(QStringLiteral("errorCount"));

        gridLayout->addWidget(errorCount, 2, 1, 1, 1);


        gridLayout_2->addWidget(status, 0, 1, 2, 1);

        horizontalSpacer = new QSpacerItem(87, 68, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 2, 2, 1);

        timeCurrent = new QLCDNumber(viewTab);
        timeCurrent->setObjectName(QStringLiteral("timeCurrent"));
        timeCurrent->setMinimumSize(QSize(141, 0));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        timeCurrent->setFont(font);
        timeCurrent->setFrameShape(QFrame::NoFrame);
        timeCurrent->setFrameShadow(QFrame::Raised);
        timeCurrent->setLineWidth(1);
        timeCurrent->setMidLineWidth(0);
        timeCurrent->setSmallDecimalPoint(false);
        timeCurrent->setDigitCount(8);
        timeCurrent->setSegmentStyle(QLCDNumber::Flat);
        timeCurrent->setProperty("value", QVariant(0));

        gridLayout_2->addWidget(timeCurrent, 1, 0, 1, 1);

        tabWidget->addTab(viewTab, QString());
        controlTab = new QWidget();
        controlTab->setObjectName(QStringLiteral("controlTab"));
        gridLayout_5 = new QGridLayout(controlTab);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        control = new QGroupBox(controlTab);
        control->setObjectName(QStringLiteral("control"));
        gridLayout_3 = new QGridLayout(control);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        sensorLabel_2 = new QLabel(control);
        sensorLabel_2->setObjectName(QStringLiteral("sensorLabel_2"));
        sensorLabel_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(sensorLabel_2, 0, 0, 1, 1);

        sensorBoxSet = new QComboBox(control);
        sensorBoxSet->setObjectName(QStringLiteral("sensorBoxSet"));
        sensorBoxSet->setEnabled(true);
        sensorBoxSet->setSizeAdjustPolicy(QComboBox::AdjustToContentsOnFirstShow);

        gridLayout_3->addWidget(sensorBoxSet, 0, 1, 1, 1);

        sensorCheckAllSet = new QCheckBox(control);
        sensorCheckAllSet->setObjectName(QStringLiteral("sensorCheckAllSet"));

        gridLayout_3->addWidget(sensorCheckAllSet, 0, 2, 1, 1);

        sensorLabel_3 = new QLabel(control);
        sensorLabel_3->setObjectName(QStringLiteral("sensorLabel_3"));
        sensorLabel_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(sensorLabel_3, 1, 0, 1, 1);

        dataBoxSet = new QComboBox(control);
        dataBoxSet->setObjectName(QStringLiteral("dataBoxSet"));
        dataBoxSet->setEnabled(true);
        dataBoxSet->setSizeAdjustPolicy(QComboBox::AdjustToContentsOnFirstShow);

        gridLayout_3->addWidget(dataBoxSet, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(72, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 1, 2, 1, 1);


        gridLayout_5->addWidget(control, 0, 0, 2, 1);

        readButton = new QPushButton(controlTab);
        readButton->setObjectName(QStringLiteral("readButton"));

        gridLayout_5->addWidget(readButton, 0, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(198, 68, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_3, 0, 2, 2, 1);

        writeButton = new QPushButton(controlTab);
        writeButton->setObjectName(QStringLiteral("writeButton"));

        gridLayout_5->addWidget(writeButton, 1, 1, 1, 1);

        tabWidget->addTab(controlTab, QString());
        exportTab = new QWidget();
        exportTab->setObjectName(QStringLiteral("exportTab"));
        gridLayout_4 = new QGridLayout(exportTab);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        from = new QLabel(exportTab);
        from->setObjectName(QStringLiteral("from"));
        from->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(from, 0, 0, 1, 1);

        dateTimeTo = new QDateTimeEdit(exportTab);
        dateTimeTo->setObjectName(QStringLiteral("dateTimeTo"));
        dateTimeTo->setCalendarPopup(true);

        gridLayout_4->addWidget(dateTimeTo, 1, 1, 1, 1);

        logLevelLabel = new QLabel(exportTab);
        logLevelLabel->setObjectName(QStringLiteral("logLevelLabel"));

        gridLayout_4->addWidget(logLevelLabel, 0, 2, 1, 1);

        logBoxExport = new QComboBox(exportTab);
        logBoxExport->setObjectName(QStringLiteral("logBoxExport"));
        logBoxExport->setSizeAdjustPolicy(QComboBox::AdjustToContentsOnFirstShow);

        gridLayout_4->addWidget(logBoxExport, 0, 3, 1, 1);

        sensorLabel = new QLabel(exportTab);
        sensorLabel->setObjectName(QStringLiteral("sensorLabel"));
        sensorLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(sensorLabel, 1, 2, 1, 1);

        sensorBoxExport = new QComboBox(exportTab);
        sensorBoxExport->setObjectName(QStringLiteral("sensorBoxExport"));
        sensorBoxExport->setEnabled(true);
        sensorBoxExport->setSizeAdjustPolicy(QComboBox::AdjustToContentsOnFirstShow);

        gridLayout_4->addWidget(sensorBoxExport, 1, 3, 1, 1);

        to = new QLabel(exportTab);
        to->setObjectName(QStringLiteral("to"));
        to->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(to, 1, 0, 1, 1);

        sensorCheckAllExport = new QCheckBox(exportTab);
        sensorCheckAllExport->setObjectName(QStringLiteral("sensorCheckAllExport"));

        gridLayout_4->addWidget(sensorCheckAllExport, 1, 4, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(85, 48, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_4, 0, 6, 2, 1);

        dateTimeFrom = new QDateTimeEdit(exportTab);
        dateTimeFrom->setObjectName(QStringLiteral("dateTimeFrom"));
        dateTimeFrom->setCalendarPopup(true);

        gridLayout_4->addWidget(dateTimeFrom, 0, 1, 1, 1);

        exportButton = new QPushButton(exportTab);
        exportButton->setObjectName(QStringLiteral("exportButton"));

        gridLayout_4->addWidget(exportButton, 0, 5, 2, 1);

        tabWidget->addTab(exportTab, QString());

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 525, 21));
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
        QObject::connect(sensorCheckAllExport, SIGNAL(toggled(bool)), sensorBoxExport, SLOT(setDisabled(bool)));
        QObject::connect(sensorCheckAllSet, SIGNAL(toggled(bool)), sensorBoxSet, SLOT(setDisabled(bool)));

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
        actionCopy->setText(QApplication::translate("MainWindow", "&Copy", 0));
#ifndef QT_NO_TOOLTIP
        actionCopy->setToolTip(QApplication::translate("MainWindow", "Copy", 0));
#endif // QT_NO_TOOLTIP
        actionCopy->setShortcut(QApplication::translate("MainWindow", "Ctrl+C", 0));
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
        status->setTitle(QApplication::translate("MainWindow", "Status", 0));
        infoLabel->setText(QApplication::translate("MainWindow", "Info:", 0));
        infoCount->setText(QApplication::translate("MainWindow", "Status", 0));
        warningLabel->setText(QApplication::translate("MainWindow", "Warning:", 0));
        warningCount->setText(QApplication::translate("MainWindow", "Status", 0));
        errorLabel->setText(QApplication::translate("MainWindow", "Error:", 0));
        errorCount->setText(QApplication::translate("MainWindow", "Status", 0));
        tabWidget->setTabText(tabWidget->indexOf(viewTab), QApplication::translate("MainWindow", "Monitor", 0));
        control->setTitle(QString());
        sensorLabel_2->setText(QApplication::translate("MainWindow", "Sensor:", 0));
        sensorCheckAllSet->setText(QApplication::translate("MainWindow", "All Sensors", 0));
        sensorLabel_3->setText(QApplication::translate("MainWindow", "Data:", 0));
        readButton->setText(QApplication::translate("MainWindow", "Read", 0));
        writeButton->setText(QApplication::translate("MainWindow", "Write", 0));
        tabWidget->setTabText(tabWidget->indexOf(controlTab), QApplication::translate("MainWindow", "Control", 0));
        from->setText(QApplication::translate("MainWindow", "From:", 0));
        dateTimeTo->setDisplayFormat(QApplication::translate("MainWindow", "dd.MM.yyyy", 0));
        logLevelLabel->setText(QApplication::translate("MainWindow", "Log Level:", 0));
        sensorLabel->setText(QApplication::translate("MainWindow", "Sensor:", 0));
        to->setText(QApplication::translate("MainWindow", "To:", 0));
        sensorCheckAllExport->setText(QApplication::translate("MainWindow", "All Sensors", 0));
        dateTimeFrom->setDisplayFormat(QApplication::translate("MainWindow", "dd.MM.yyyy", 0));
        exportButton->setText(QApplication::translate("MainWindow", "Export", 0));
        tabWidget->setTabText(tabWidget->indexOf(exportTab), QApplication::translate("MainWindow", "Options", 0));
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

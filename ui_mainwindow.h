/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actInfo;
    QAction *actKind;
    QAction *actOutPut;
    QAction *actSubmit;
    QAction *actionExport;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_5;
    QTabWidget *tabWidget;
    QWidget *tab;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QTableView *tableView;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_kind;
    QComboBox *comboBoxKind;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_info;
    QComboBox *comboBoxInfo;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_2;
    QComboBox *comboBoxYear;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_area;
    QLabel *label_area;
    QLineEdit *lineEdit_area_min;
    QLabel *label_nothing1;
    QLineEdit *lineEdit_area_max;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *pushButton_area_yes;
    QPushButton *pushButton_area_clear;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_weight;
    QLabel *label_weight;
    QLineEdit *lineEdit_weight_min;
    QLabel *label_nothing2;
    QLineEdit *lineEdit_weight_max;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *pushButton_weight_yes;
    QPushButton *pushButton_weight_clear;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *pushButton_search_engine;
    QLineEdit *lineEdit;
    QWidget *tab_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_statistics;
    QComboBox *comboBox_statistics;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label__statistics_year;
    QComboBox *comboBox__statistics_year_min;
    QLabel *label_statistics_nothing;
    QComboBox *comboBox__statistics_year_max;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *pushButton_statistics_yes;
    QPushButton *pushButton_statistics_export;
    QSpacerItem *verticalSpacer_5;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(863, 493);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/title.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actInfo = new QAction(MainWindow);
        actInfo->setObjectName(QStringLiteral("actInfo"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/info.png"), QSize(), QIcon::Normal, QIcon::Off);
        actInfo->setIcon(icon1);
        actKind = new QAction(MainWindow);
        actKind->setObjectName(QStringLiteral("actKind"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/kind.png"), QSize(), QIcon::Normal, QIcon::Off);
        actKind->setIcon(icon2);
        actOutPut = new QAction(MainWindow);
        actOutPut->setObjectName(QStringLiteral("actOutPut"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/images/output.png"), QSize(), QIcon::Normal, QIcon::Off);
        actOutPut->setIcon(icon3);
        actSubmit = new QAction(MainWindow);
        actSubmit->setObjectName(QStringLiteral("actSubmit"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/images/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actSubmit->setIcon(icon4);
        actionExport = new QAction(MainWindow);
        actionExport->setObjectName(QStringLiteral("actionExport"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/images/export.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExport->setIcon(icon5);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout_5 = new QVBoxLayout(centralwidget);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setSizeConstraint(QLayout::SetDefaultConstraint);
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setIconSize(QSize(25, 25));
        tabWidget->setElideMode(Qt::ElideNone);
        tabWidget->setMovable(true);
        tabWidget->setTabBarAutoHide(false);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        horizontalLayout_2 = new QHBoxLayout(tab);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        tableView = new QTableView(tab);
        tableView->setObjectName(QStringLiteral("tableView"));

        horizontalLayout_5->addWidget(tableView);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_kind = new QLabel(tab);
        label_kind->setObjectName(QStringLiteral("label_kind"));

        verticalLayout_2->addWidget(label_kind);

        comboBoxKind = new QComboBox(tab);
        comboBoxKind->setObjectName(QStringLiteral("comboBoxKind"));

        verticalLayout_2->addWidget(comboBoxKind);


        horizontalLayout_3->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_info = new QLabel(tab);
        label_info->setObjectName(QStringLiteral("label_info"));

        verticalLayout_3->addWidget(label_info);

        comboBoxInfo = new QComboBox(tab);
        comboBoxInfo->setObjectName(QStringLiteral("comboBoxInfo"));

        verticalLayout_3->addWidget(comboBoxInfo);


        horizontalLayout_3->addLayout(verticalLayout_3);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        label_2 = new QLabel(tab);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_4->addWidget(label_2);

        comboBoxYear = new QComboBox(tab);
        comboBoxYear->setObjectName(QStringLiteral("comboBoxYear"));

        verticalLayout_4->addWidget(comboBoxYear);


        horizontalLayout_4->addLayout(verticalLayout_4);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        horizontalLayout_4->setStretch(0, 1);
        horizontalLayout_4->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout_4);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        horizontalLayout_area = new QHBoxLayout();
        horizontalLayout_area->setObjectName(QStringLiteral("horizontalLayout_area"));
        label_area = new QLabel(tab);
        label_area->setObjectName(QStringLiteral("label_area"));

        horizontalLayout_area->addWidget(label_area);

        lineEdit_area_min = new QLineEdit(tab);
        lineEdit_area_min->setObjectName(QStringLiteral("lineEdit_area_min"));

        horizontalLayout_area->addWidget(lineEdit_area_min);

        label_nothing1 = new QLabel(tab);
        label_nothing1->setObjectName(QStringLiteral("label_nothing1"));

        horizontalLayout_area->addWidget(label_nothing1);

        lineEdit_area_max = new QLineEdit(tab);
        lineEdit_area_max->setObjectName(QStringLiteral("lineEdit_area_max"));

        horizontalLayout_area->addWidget(lineEdit_area_max);


        verticalLayout->addLayout(horizontalLayout_area);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        pushButton_area_yes = new QPushButton(tab);
        pushButton_area_yes->setObjectName(QStringLiteral("pushButton_area_yes"));

        horizontalLayout_6->addWidget(pushButton_area_yes);

        pushButton_area_clear = new QPushButton(tab);
        pushButton_area_clear->setObjectName(QStringLiteral("pushButton_area_clear"));

        horizontalLayout_6->addWidget(pushButton_area_clear);


        verticalLayout->addLayout(horizontalLayout_6);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout_weight = new QHBoxLayout();
        horizontalLayout_weight->setObjectName(QStringLiteral("horizontalLayout_weight"));
        label_weight = new QLabel(tab);
        label_weight->setObjectName(QStringLiteral("label_weight"));

        horizontalLayout_weight->addWidget(label_weight);

        lineEdit_weight_min = new QLineEdit(tab);
        lineEdit_weight_min->setObjectName(QStringLiteral("lineEdit_weight_min"));

        horizontalLayout_weight->addWidget(lineEdit_weight_min);

        label_nothing2 = new QLabel(tab);
        label_nothing2->setObjectName(QStringLiteral("label_nothing2"));

        horizontalLayout_weight->addWidget(label_nothing2);

        lineEdit_weight_max = new QLineEdit(tab);
        lineEdit_weight_max->setObjectName(QStringLiteral("lineEdit_weight_max"));

        horizontalLayout_weight->addWidget(lineEdit_weight_max);


        verticalLayout->addLayout(horizontalLayout_weight);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        pushButton_weight_yes = new QPushButton(tab);
        pushButton_weight_yes->setObjectName(QStringLiteral("pushButton_weight_yes"));

        horizontalLayout_7->addWidget(pushButton_weight_yes);

        pushButton_weight_clear = new QPushButton(tab);
        pushButton_weight_clear->setObjectName(QStringLiteral("pushButton_weight_clear"));

        horizontalLayout_7->addWidget(pushButton_weight_clear);


        verticalLayout->addLayout(horizontalLayout_7);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        pushButton_search_engine = new QPushButton(tab);
        pushButton_search_engine->setObjectName(QStringLiteral("pushButton_search_engine"));

        horizontalLayout_8->addWidget(pushButton_search_engine);

        lineEdit = new QLineEdit(tab);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout_8->addWidget(lineEdit);


        verticalLayout->addLayout(horizontalLayout_8);


        horizontalLayout_5->addLayout(verticalLayout);

        horizontalLayout_5->setStretch(0, 3);
        horizontalLayout_5->setStretch(1, 1);

        horizontalLayout_2->addLayout(horizontalLayout_5);

        QIcon icon6;
        icon6.addFile(QStringLiteral("images/table.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tab, icon6, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        horizontalLayout = new QHBoxLayout(tab_2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_3 = new QLabel(tab_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout->addWidget(label_3);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_statistics = new QLabel(tab_2);
        label_statistics->setObjectName(QStringLiteral("label_statistics"));

        horizontalLayout_10->addWidget(label_statistics);

        comboBox_statistics = new QComboBox(tab_2);
        comboBox_statistics->setObjectName(QStringLiteral("comboBox_statistics"));

        horizontalLayout_10->addWidget(comboBox_statistics);

        horizontalLayout_10->setStretch(0, 1);
        horizontalLayout_10->setStretch(1, 4);

        verticalLayout_6->addLayout(horizontalLayout_10);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        label__statistics_year = new QLabel(tab_2);
        label__statistics_year->setObjectName(QStringLiteral("label__statistics_year"));

        horizontalLayout_12->addWidget(label__statistics_year);

        comboBox__statistics_year_min = new QComboBox(tab_2);
        comboBox__statistics_year_min->setObjectName(QStringLiteral("comboBox__statistics_year_min"));

        horizontalLayout_12->addWidget(comboBox__statistics_year_min);

        label_statistics_nothing = new QLabel(tab_2);
        label_statistics_nothing->setObjectName(QStringLiteral("label_statistics_nothing"));

        horizontalLayout_12->addWidget(label_statistics_nothing);

        comboBox__statistics_year_max = new QComboBox(tab_2);
        comboBox__statistics_year_max->setObjectName(QStringLiteral("comboBox__statistics_year_max"));

        horizontalLayout_12->addWidget(comboBox__statistics_year_max);


        verticalLayout_6->addLayout(horizontalLayout_12);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        pushButton_statistics_yes = new QPushButton(tab_2);
        pushButton_statistics_yes->setObjectName(QStringLiteral("pushButton_statistics_yes"));

        horizontalLayout_9->addWidget(pushButton_statistics_yes);

        pushButton_statistics_export = new QPushButton(tab_2);
        pushButton_statistics_export->setObjectName(QStringLiteral("pushButton_statistics_export"));

        horizontalLayout_9->addWidget(pushButton_statistics_export);


        verticalLayout_6->addLayout(horizontalLayout_9);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_5);


        horizontalLayout->addLayout(verticalLayout_6);

        horizontalLayout->setStretch(0, 4);
        horizontalLayout->setStretch(1, 1);
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/images/chart.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tab_2, icon7, QString());

        verticalLayout_5->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 863, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        toolBar->setIconSize(QSize(80, 30));
        toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        toolBar->addAction(actKind);
        toolBar->addAction(actInfo);
        toolBar->addAction(actOutPut);
        toolBar->addSeparator();
        toolBar->addAction(actSubmit);
        toolBar->addSeparator();
        toolBar->addAction(actionExport);
        toolBar->addSeparator();

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\350\217\234\345\206\234\347\247\215\346\244\215\344\277\241\346\201\257\347\256\241\347\220\206\347\263\273\347\273\237", Q_NULLPTR));
        actInfo->setText(QApplication::translate("MainWindow", "\350\224\254\350\217\234\350\257\246\347\273\206\344\277\241\346\201\257", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actInfo->setToolTip(QApplication::translate("MainWindow", "\350\224\254\350\217\234\350\257\246\347\273\206\344\277\241\346\201\257", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actKind->setText(QApplication::translate("MainWindow", "\350\224\254\350\217\234\347\247\215\347\261\273\344\277\241\346\201\257", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actKind->setToolTip(QApplication::translate("MainWindow", "\350\224\254\350\217\234\347\247\215\347\261\273\344\277\241\346\201\257", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actOutPut->setText(QApplication::translate("MainWindow", "\350\224\254\350\217\234\344\272\247\351\207\217\344\277\241\346\201\257", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actOutPut->setToolTip(QApplication::translate("MainWindow", "\350\224\254\350\217\234\344\272\247\351\207\217\344\277\241\346\201\257", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actSubmit->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actSubmit->setToolTip(QApplication::translate("MainWindow", "\344\277\235\345\255\230\344\277\256\346\224\271", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionExport->setText(QApplication::translate("MainWindow", "\345\257\274\345\207\272", Q_NULLPTR));
        label_kind->setText(QApplication::translate("MainWindow", "   \347\247\215\347\261\273", Q_NULLPTR));
        label_info->setText(QApplication::translate("MainWindow", " \350\220\245\345\205\273\346\210\220\345\210\206", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "   \345\271\264\344\273\275", Q_NULLPTR));
        label_area->setText(QApplication::translate("MainWindow", "\347\247\215\346\244\215\351\235\242\347\247\257", Q_NULLPTR));
        label_nothing1->setText(QApplication::translate("MainWindow", "-", Q_NULLPTR));
        pushButton_area_yes->setText(QApplication::translate("MainWindow", "\347\241\256\345\256\232", Q_NULLPTR));
        pushButton_area_clear->setText(QApplication::translate("MainWindow", "\346\270\205\347\251\272", Q_NULLPTR));
        label_weight->setText(QApplication::translate("MainWindow", "\346\224\266\350\216\267\351\207\215\351\207\217", Q_NULLPTR));
        label_nothing2->setText(QApplication::translate("MainWindow", "-", Q_NULLPTR));
        pushButton_weight_yes->setText(QApplication::translate("MainWindow", "\347\241\256\345\256\232", Q_NULLPTR));
        pushButton_weight_clear->setText(QApplication::translate("MainWindow", "\346\270\205\347\251\272", Q_NULLPTR));
        pushButton_search_engine->setText(QApplication::translate("MainWindow", "\346\220\234\347\264\242", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "\350\241\250\346\240\274", Q_NULLPTR));
        label_3->setText(QString());
        label_statistics->setText(QApplication::translate("MainWindow", "\347\273\237\350\256\241\351\200\211\346\213\251", Q_NULLPTR));
        label__statistics_year->setText(QApplication::translate("MainWindow", "\345\271\264\344\273\275", Q_NULLPTR));
        label_statistics_nothing->setText(QApplication::translate("MainWindow", "-", Q_NULLPTR));
        pushButton_statistics_yes->setText(QApplication::translate("MainWindow", "\347\241\256\345\256\232", Q_NULLPTR));
        pushButton_statistics_export->setText(QApplication::translate("MainWindow", "\345\257\274\345\207\272", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "\347\273\237\350\256\241", Q_NULLPTR));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

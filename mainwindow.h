#pragma execution_character_set("utf-8")
#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "head.h"
#include <QMainWindow>
#include <QTableView>
#include <QStandardItemModel>
#include <QPainter> 


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
	bool eventFilter(QObject *watched, QEvent *event);  //ÊÂ¼þÂË²¨Æ÷
	void magicTime();
    ~MainWindow();

private slots:
    void on_actSubmit_triggered();
	void on_actKind_triggered();
	void on_actInfo_triggered();
	void on_actOutPut_triggered();
	void on_actExport_triggered();
	void ComboKindChangedSlot(const QString &);
	void ComboInfoChangedSlot(const QString &a);
	void ComboYearChangedSlot(const QString &a);
	void CombostatisticsChangedSlot(const QString &a);
	void clicked_RightMenu(const QPoint & pos);
	void on_RightEdit_triggered();
	void on_RightDel_triggered();
	void on_RightAdd_triggered();
	void on_pushButton_area_yes_clicked();
	void on_pushButton_area_clear_clicked();
	void on_pushButton_weight_yes_clicked();
	void on_pushButton_weight_clear_clicked();
	void on_pushButton_search_engine_clicked();
	void on_pushButton_statistics_yes_clicked();
	void on_pushButton_statistics_export_clicked();

private:
//    QTableView * table_view;
	QMenu * RightMenu;//ÓÒ»÷²Ëµ¥
	QAction * RightEdit;	//±à¼­°´¼ü
	QAction * RightDel;	//É¾³ý°´¼ü
	QAction * RightAdd;	//Ìí¼Ó°´¼ü
    QStandardItemModel * item_model;
	KindLink head;
    void iniUI();
	void SetKind(int row, int column, char ** kind, char ***veg);
	void SetInfo(int row, char ** veg, char ** kindnum, char ** components);
	void SetOutPut(int row, char ** kindnum, char ** veg, char ** area, char ** weight, char ** year);
	bool KindFirst;
	bool InfoFirst;
	bool OutPutFirst;
	int state;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

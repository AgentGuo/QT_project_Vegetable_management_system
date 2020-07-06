#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qinputdialog.h>
#include <qtextcodec.h>
#include <qmessagebox.h>
using namespace std;

MainWindow::MainWindow(QWidget *parent)//构造函数
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    iniUI();
}
MainWindow::~MainWindow()
{	//析构函数
    delete ui;
}

void MainWindow::iniUI()
{	//初始化函数
	LoadKindInfo(&head);
	LoadVegInfo(&head);
	LoadPlantInfo(&head);
	connect(ui->actKind, SIGNAL(triggered()), this, SLOT(on_actKind_triggered()));//Kind按钮
	connect(ui->actInfo, SIGNAL(triggered()), this, SLOT(on_actInfo_triggered()));//Info按钮
	connect(ui->actOutPut, SIGNAL(triggered()), this, SLOT(on_actOutPut_triggered()));//OutPut按钮
	connect(ui->actionExport, SIGNAL(triggered()), this, SLOT(on_actExport_triggered()));//OutPut按钮
	connect(ui->comboBoxKind, SIGNAL(currentIndexChanged(QString)), this, SLOT(ComboKindChangedSlot(const QString &)));//种类筛选框
	connect(ui->comboBoxInfo, SIGNAL(currentIndexChanged(QString)), this, SLOT(ComboInfoChangedSlot(const QString &)));//成分筛选框
	connect(ui->comboBoxYear, SIGNAL(currentIndexChanged(QString)), this, SLOT(ComboYearChangedSlot(const QString &)));//年份筛选框
	connect(ui->comboBox_statistics, SIGNAL(currentIndexChanged(QString)), this, SLOT(CombostatisticsChangedSlot(const QString &)));//年份筛选框
	//connect(ui->pushButton_area_yes, SIGNAL(clicked()), this, SLOT(on_pushButton_area_yes_clicked()));	//面积确认按钮
	//connect(ui->pushButton_area_yes, SIGNAL(clicked()), this, SLOT(on_pushButton_area_yes_clicked()));	//面积确认按钮
	//connect(ui->pushButton_area_clear, SIGNAL(clicked()), this, SLOT(on_pushButton_area_clear_clicked()));	//面积清空按钮
	//connect(ui->pushButton_weight_yes, SIGNAL(clicked()), this, SLOT(on_pushButton_weight_yes_clicked()));	//重量确认按钮
	//connect(ui->pushButton_weight_clear, SIGNAL(clicked(bool)), this, SLOT(on_pushButton_weight_clear_clicked()));	//重量清空按钮
	//connect(ui->pushButton_search_engine, SIGNAL(clicked()), this, SLOT(on_pushButton_search_engine_clicked()));	//搜索按钮
	ui->comboBoxKind->setDisabled(true);//禁用种类筛选框
	ui->comboBoxInfo->setDisabled(true);	//禁用信息筛选框
	ui->comboBoxYear->setDisabled(true);	//禁用年份筛选框
	ui->pushButton_area_yes->setDisabled(true);	//禁用面积确认按钮
	ui->pushButton_weight_yes->setDisabled(true);	//禁用重量确认按钮
    //ui->tableView = new QTableView(this);
    item_model = new QStandardItemModel(0, 0);//表格初始大小
	ui->tableView->setModel(item_model);
	//ui->tableView->setGeometry(0,55,600,300);//设置表格位置和大小
	//ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);

	//右击菜单部分
	RightEdit = new QAction("编辑", this);		//创建右击编辑action
	connect(RightEdit, SIGNAL(triggered()), this, SLOT(on_RightEdit_triggered()));	//连接槽函数
	RightDel = new QAction("删除", this);		//创建右击删除action
	connect(RightDel, SIGNAL(triggered()), this, SLOT(on_RightDel_triggered()));	//连接槽函数
	RightAdd = new QAction("添加", this);		//创建右击添加action
	connect(RightAdd, SIGNAL(triggered()), this, SLOT(on_RightAdd_triggered()));	//连接槽函数
	RightMenu = new QMenu;	//创建右击菜单
	RightMenu->addAction(RightEdit);	//菜单内添加删除action
	RightMenu->addAction(RightDel);	//菜单内添加编辑action
	RightMenu->addAction(RightAdd);	//菜单内添加action
	connect(ui->tableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(clicked_RightMenu(QPoint)));	//连接表格与菜单
	ui->tableView->setAlternatingRowColors(true);	//设置表格不同行颜色
	ui->label_3->installEventFilter(this);        //安装事件过滤器到窗口

	QStringList StatisticsList;
	StatisticsList << "各类蔬菜重量统计" << "各类蔬菜面积统计" << "年份统计";	//设置筛选框内容
	ui->comboBox_statistics->addItems(StatisticsList);
	QStringList StatisticsYearMinList;
	StatisticsYearMinList << "2015" << "2016" << "2017" << "2018" << "2019" << "2020";	//设置筛选框内容
	ui->comboBox__statistics_year_min->addItems(StatisticsYearMinList);
	QStringList StatisticsYearMaxList;
	StatisticsYearMaxList << "2015" << "2016" << "2017" << "2018" << "2019" << "2020";	//设置筛选框内容
	ui->comboBox__statistics_year_max->addItems(StatisticsYearMaxList);
	ui->label_statistics->setVisible(false);	//隐藏统计部分的控件
	ui->label_statistics_nothing->setVisible(false);
	ui->label__statistics_year->setVisible(false);
	ui->comboBox_statistics->setVisible(false);
	ui->comboBox__statistics_year_min->setVisible(false);
	ui->comboBox__statistics_year_max->setVisible(false);
	ui->pushButton_statistics_yes->setVisible(false);
	ui->pushButton_statistics_export->setVisible(false);
}

void MainWindow::on_actSubmit_triggered()
{	//保存按钮
	write(head);
}

void MainWindow::on_actKind_triggered()
{	//蔬菜种类按钮
	state = 0;
	KindFirst = true;
	ui->comboBoxKind->clear();	//清空筛选框
	ui->comboBoxKind->setEnabled(true);	//启用种类筛选框
	ui->comboBoxInfo->setDisabled(true);	//禁用信息筛选框
	ui->comboBoxYear->setDisabled(true);	//禁用年份筛选框
	ui->pushButton_area_yes->setDisabled(true);	//禁用面积确认按钮
	ui->pushButton_weight_yes->setDisabled(true);	//禁用重量确认按钮
	ui->lineEdit_area_min->clear();	//清空输入框
	ui->lineEdit_area_max->clear();
	ui->lineEdit_weight_min->clear();
	ui->lineEdit_weight_max->clear();
	QStringList strlist;
	strlist << "all" << "1" << "2" << "3" << "4" << "5";	//设置筛选框内容
	ui->comboBoxKind->addItems(strlist);
	int row = 1, column = 1;
	char **kind;
	char ***veg;
	SearchKind(head, &kind, &veg, &row, &column, NULL);	//查询所需信息
	SetKind(row, column, kind, veg);	//设置信息
	ui->label_statistics->setVisible(false);
	ui->label_statistics_nothing->setVisible(false);
	ui->label__statistics_year->setVisible(false);
	ui->comboBox_statistics->setVisible(false);
	ui->comboBox__statistics_year_min->setVisible(false);
	ui->comboBox__statistics_year_max->setVisible(false);
}

void MainWindow::on_actInfo_triggered()
{	//蔬菜基本信息按钮
	state = 1;
	ui->comboBoxKind->clear();	//清空种类筛选框
	ui->comboBoxInfo->clear();	//清空信息筛选框
	ui->lineEdit_area_min->clear();	//清空输入框
	ui->lineEdit_area_max->clear();
	ui->lineEdit_weight_min->clear();
	ui->lineEdit_weight_max->clear();
	ui->comboBoxKind->setEnabled(true);	//启用种类筛选框
	ui->comboBoxInfo->setEnabled(true);	//启用信息筛选框
	ui->comboBoxYear->setDisabled(true);	//禁用年份筛选框
	ui->pushButton_area_yes->setDisabled(true);	//禁用面积确认按钮
	ui->pushButton_weight_yes->setDisabled(true);	//禁用重量确认按钮
	InfoFirst = true;	//第一次使用，避免重复刷新
	int row = 1;
	char **veg;
	char **kindnum;
	char **components;
	ui->comboBoxKind->clear();	//清空筛选框
	ui->comboBoxInfo->clear();	//清空筛选框
	QStringList KindList, InfoList;
	KindList << "all" << "1" << "2" << "3" << "4" << "5";	//设置种类筛选框内容
	InfoList << "all" << "蛋白质" << "葡萄糖" << "多糖" << "糖种酶" << "维生素A" << "维生素B1" << "维生素B2" << "维生素C" << "维生素K" << "胡萝卜素" << "钙" << "铁" << "钾" << "磷" << "锌" << "锰" << "铜" << "镁" << "钠" << "碘";	//设置信息筛选框内容
	ui->comboBoxKind->addItems(KindList);
	ui->comboBoxInfo->addItems(InfoList);
	SearchInfo(head, &veg, &kindnum, &components, &row, const_cast<char *>(ui->comboBoxKind->currentText().toLocal8Bit().toStdString().c_str()), const_cast<char *>(ui->comboBoxInfo->currentText().toLocal8Bit().toStdString().c_str()));	//获取信息
	SetInfo(row, veg, kindnum, components);	//设置信息
	ui->label_statistics->setVisible(false);
	ui->label_statistics_nothing->setVisible(false);
	ui->label__statistics_year->setVisible(false);
	ui->comboBox_statistics->setVisible(false);
	ui->comboBox__statistics_year_min->setVisible(false);
	ui->comboBox__statistics_year_max->setVisible(false);
} 

void MainWindow::on_actOutPut_triggered()
{	//蔬菜产量信息按钮
	state = 2;
	OutPutFirst = true;
	item_model->clear();//清理表格
	ui->comboBoxKind->clear();	//清空种类筛选框
	ui->comboBoxYear->clear();	//清空种类筛选框
	ui->lineEdit_area_min->clear();	//清空输入框
	ui->lineEdit_area_max->clear();
	ui->lineEdit_weight_min->clear();
	ui->lineEdit_weight_max->clear();
	ui->comboBoxKind->setEnabled(true);	//启用种类筛选框
	ui->comboBoxInfo->setDisabled(true);	//禁用信息筛选框
	ui->comboBoxYear->setEnabled(true);	//启用用年份筛选框
	ui->pushButton_area_yes->setEnabled(true);	//启用面积确认按钮
	ui->pushButton_weight_yes->setEnabled(true);	//禁用重量确认按钮
	QStringList KindList;
	KindList << "all" << "1" << "2" << "3" << "4" << "5";	//设置筛选框内容
	ui->comboBoxKind->addItems(KindList);
	QStringList YearList;
	YearList << "all" << "2015" << "2016" << "2017" << "2018" << "2019" << "2020";	//设置筛选框内容
	ui->comboBoxYear->addItems(YearList);
	item_model->setColumnCount(5);
	item_model->setRowCount(0);
	item_model->setHeaderData(0, Qt::Horizontal, "蔬菜编号");//设置字段名
	item_model->setHeaderData(1, Qt::Horizontal, "蔬菜名称");
	item_model->setHeaderData(2, Qt::Horizontal, "种植面积");
	item_model->setHeaderData(3, Qt::Horizontal, "收获重量");
	item_model->setHeaderData(4, Qt::Horizontal, "种植年份");
	//KindLink temp = head;
	int row;
	char ** kindnum, ** veg, ** area, ** weight, ** year;
	SearchOutPut(head, &kindnum, &veg, &area, &weight, &year, &row, const_cast<char *>(ui->comboBoxKind->currentText().toLocal8Bit().toStdString().c_str()), const_cast<char *>(ui->comboBoxYear->currentText().toLocal8Bit().toStdString().c_str()), const_cast<char *>(ui->lineEdit_area_min->text().toLocal8Bit().toStdString().c_str()), const_cast<char *>(ui->lineEdit_area_max->text().toLocal8Bit().toStdString().c_str()), const_cast<char *>(ui->lineEdit_weight_min->text().toLocal8Bit().toStdString().c_str()), const_cast<char *>(ui->lineEdit_weight_max->text().toLocal8Bit().toStdString().c_str()));
	SetOutPut(row, kindnum, veg, area, weight, year);
	ui->label_statistics->setVisible(true);
	ui->label_statistics_nothing->setVisible(true);
	ui->label__statistics_year->setVisible(true);
	ui->comboBox_statistics->setVisible(true);
	ui->comboBox__statistics_year_min->setVisible(true);
	ui->comboBox__statistics_year_max->setVisible(true);
}

void MainWindow::on_actExport_triggered()
{	//导出按钮
	int i, j;
	bool ok;
	QString text = QInputDialog::getText(this, tr("导出"), tr("保存的文件名(.csv)"), QLineEdit::Normal, 0, &ok);
	if (ok && text.length() >= 1)
	{
		FILE* ExportFp = NULL;
		ExportFp = fopen(const_cast<char *>(text.toLocal8Bit().toStdString().c_str()), "w");
		for (i = 0; i < item_model->columnCount(); i++)
		{
			fprintf(ExportFp, "%s", const_cast<char *>(item_model->horizontalHeaderItem(i)->text().toLocal8Bit().toStdString().c_str()));
			if (i < item_model->columnCount() - 1)
				fprintf(ExportFp, ",");
			else
				fprintf(ExportFp, "\n");
		}
		QString temp;
		for (i = 0; i < item_model->rowCount(); i++)
		{
			for (j = 0; j < item_model->columnCount(); j++)
			{
				temp = item_model->data(item_model->index(i, j)).toString();
				fprintf(ExportFp, "%s", const_cast<char *>(temp.toLocal8Bit().toStdString().c_str()));
				if (j < item_model->columnCount() - 1)
					fprintf(ExportFp, ",");
				else
					fprintf(ExportFp, "\n");
			}
		}
		fclose(ExportFp);
	}
}

void MainWindow::ComboKindChangedSlot(const QString &a)
{	//种类筛选下拉框
	switch (state)
	{
	case 0: {
		if (KindFirst == false)
		{
			int row = 1, column = 1;
			char **kind;
			char ***veg;
			SearchKind(head, &kind, &veg, &row, &column, const_cast<char *>(a.toStdString().c_str()));	//查询所需信息
			SetKind(row, column, kind, veg);	//设置信息
		}
		else
			KindFirst = false;
		break;
	}
	case 1: {//状态1，即info状态
		if (InfoFirst == false) {
			int row = 1;
			char **veg;
			char **kindnum;
			char **components;
			//const_cast<char *>(ui->comboBoxInfo->currentText.toLocal8Bit().toStdString().c_str())
			SearchInfo(head, &veg, &kindnum, &components, &row, const_cast<char *>(a.toStdString().c_str()), const_cast<char *>(ui->comboBoxInfo->currentText().toLocal8Bit().toStdString().c_str()));//获取信息
			SetInfo(row, veg, kindnum, components);//设置信息
		}
		else
			InfoFirst = false;
		break;
	}
	case 2: {//状态2，即OutPut状态
		if (InfoFirst == false) {
			int row;
			char ** kindnum, ** veg, ** area, ** weight, ** year;
			SearchOutPut(head, &kindnum, &veg, &area, &weight, &year, &row, const_cast<char *>(ui->comboBoxKind->currentText().toLocal8Bit().toStdString().c_str()), const_cast<char *>(ui->comboBoxYear->currentText().toLocal8Bit().toStdString().c_str()), const_cast<char *>(ui->lineEdit_area_min->text().toLocal8Bit().toStdString().c_str()), const_cast<char *>(ui->lineEdit_area_max->text().toLocal8Bit().toStdString().c_str()), const_cast<char *>(ui->lineEdit_weight_min->text().toLocal8Bit().toStdString().c_str()), const_cast<char *>(ui->lineEdit_weight_max->text().toLocal8Bit().toStdString().c_str()));
			SetOutPut(row, kindnum, veg, area, weight, year);
		}
		else
			InfoFirst = false;
		break;
	}
	default:
		break;
	}
}

void MainWindow::ComboInfoChangedSlot(const QString &a)
{	//营养物质筛选下拉框
	int row = 1;
	char **veg;
	char **kindnum;
	char **components;
	//const_cast<char *>(ui->comboBoxInfo->currentText.toLocal8Bit().toStdString().c_str())
	SearchInfo(head, &veg, &kindnum, &components, &row, const_cast<char *>(ui->comboBoxKind->currentText().toStdString().c_str()), const_cast<char *>(ui->comboBoxInfo->currentText().toLocal8Bit().toStdString().c_str()));//获取信息
	SetInfo(row, veg, kindnum, components);//设置信息
}

void MainWindow::ComboYearChangedSlot(const QString &a)
{	//年份下拉框
	int row;
	char ** kindnum, ** veg, ** area, ** weight, ** year;
	SearchOutPut(head, &kindnum, &veg, &area, &weight, &year, &row, const_cast<char *>(ui->comboBoxKind->currentText().toLocal8Bit().toStdString().c_str()), const_cast<char *>(ui->comboBoxYear->currentText().toLocal8Bit().toStdString().c_str()), const_cast<char *>(ui->lineEdit_area_min->text().toLocal8Bit().toStdString().c_str()), const_cast<char *>(ui->lineEdit_area_max->text().toLocal8Bit().toStdString().c_str()), const_cast<char *>(ui->lineEdit_weight_min->text().toLocal8Bit().toStdString().c_str()), const_cast<char *>(ui->lineEdit_weight_max->text().toLocal8Bit().toStdString().c_str()));
	SetOutPut(row, kindnum, veg, area, weight, year);
}

void MainWindow::CombostatisticsChangedSlot(const QString &a)
{	//统计信息下拉框
	if (state == 2 && ui->comboBox_statistics->currentIndex() == 2)
	{
		ui->pushButton_statistics_yes->setVisible(true);
		ui->pushButton_statistics_export->setVisible(true);
	}
	else {
		ui->label_3->clear();
		ui->pushButton_statistics_yes->setVisible(false);
		ui->pushButton_statistics_export->setVisible(false);
	}
	/*
	if (state == 2 && ui->comboBox_statistics->currentIndex() == 2)
	{
		char Text[2000] = "\0";
		DrawYear(head, Text, const_cast<char *>(ui->comboBox__statistics_year_min->currentText().toStdString().c_str()), const_cast<char *>(ui->comboBox__statistics_year_max->currentText().toStdString().c_str()));
		string ss;
		ss = Text;
		ui->label_3->setText(QString::fromLocal8Bit(ss.c_str()));
	}
	*/
}

void MainWindow::SetKind(int row, int column, char ** kind, char ***veg)
{	//设置种类
	int  i = 0, j = 0;
	QTextCodec *codec = QTextCodec::codecForName("GBK");//跟换编码方式，防止中文乱码
	item_model->clear();//清除表格
	item_model->setColumnCount(column);
	item_model->setRowCount(row);
	for (i = 0; i < column; i++)
	{
		item_model->setHeaderData(i, Qt::Horizontal, codec->toUnicode(kind[i]));//设置字段名
		for (j = 0; j < row; j++)
		{
			if (strlen(veg[i][j]) == 0)
				break;
			item_model->setItem(j, i, new QStandardItem(QString(codec->toUnicode(veg[i][j]))));
		}
	}
	for (i = 0; i < column; i++)
		ui->tableView->setColumnWidth(i, 110);
}

void MainWindow::SetInfo(int row, char ** veg, char ** kindnum, char ** components)
{	//设置蔬菜基本信息
	int i = 0;
	ui->tableView->setColumnWidth(3, 200);
	item_model->clear();//清理表格
	item_model->setColumnCount(3);
	item_model->setRowCount(row);
	item_model->setHeaderData(0, Qt::Horizontal, "蔬菜名称");//设置字段名
	item_model->setHeaderData(1, Qt::Horizontal, "分类码");
	item_model->setHeaderData(2, Qt::Horizontal, "营养成分");
	QTextCodec *codec = QTextCodec::codecForName("GBK");//跟换编码方式，防止中文乱码
	for (i = 0; i < row; i++) {
		item_model->setItem(i, 0, new QStandardItem(QString(codec->toUnicode(veg[i]))));
		item_model->setItem(i, 1, new QStandardItem(QString(codec->toUnicode(kindnum[i]))));
		item_model->setItem(i, 2, new QStandardItem(QString(codec->toUnicode(components[i]))));
	}
	ui->tableView->setColumnWidth(0, 140);
	ui->tableView->setColumnWidth(1, 140);
	ui->tableView->setColumnWidth(2, 300);
}

void MainWindow::SetOutPut(int row, char ** kindnum, char ** veg, char ** area, char ** weight, char ** year)
{	//设置蔬菜种植信息
	int i = 0;
	item_model->setRowCount(row);
	QTextCodec *codec = QTextCodec::codecForName("GBK");//跟换编码方式，防止中文乱码
	for (i = 0; i < row; i++) {
		item_model->setItem(i, 0, new QStandardItem(QString(codec->toUnicode(kindnum[i]))));
		item_model->setItem(i, 1, new QStandardItem(QString(codec->toUnicode(veg[i]))));
		item_model->setItem(i, 2, new QStandardItem(QString(codec->toUnicode(area[i]))));
		item_model->setItem(i, 3, new QStandardItem(QString(codec->toUnicode(weight[i]))));
		item_model->setItem(i, 4, new QStandardItem(QString(codec->toUnicode(year[i]))));
	}
	ui->tableView->setColumnWidth(0, 115);
	ui->tableView->setColumnWidth(1, 115);
	ui->tableView->setColumnWidth(2, 115);
	ui->tableView->setColumnWidth(3, 115);
	ui->tableView->setColumnWidth(4, 115);
}

void MainWindow::clicked_RightMenu(const QPoint & pos)	//右击菜单
{	//右击菜单
	RightMenu->exec(QCursor::pos());
}

void MainWindow::on_RightEdit_triggered()
{	//右击编辑
	bool ok;
	switch (state)
	{
	case 0: {	//种类表情况下
		QString text = QInputDialog::getText(this, tr("修改单元格"), tr("请输入修改内容"), QLineEdit::Normal, 0, &ok);
		if (!ok|| text.length()<1)
			break;
		QModelIndex index = ui->tableView->currentIndex();	//获取当前行列
		QString veg = item_model->data(index).toString();	//修改蔬菜名
		VegNameEdit(&head, const_cast<char *>(veg.toLocal8Bit().toStdString().c_str()), const_cast<char *>(text.toLocal8Bit().toStdString().c_str()));
		on_actKind_triggered();	//刷新表格
		break;
	}
	case 1: {	//信息表情况下
		int cloum = ui->tableView->currentIndex().column();	//获得修改列号
		int row = ui->tableView->currentIndex().row();	//获得修改行号
		switch (cloum)
		{
		case 0: {	//修改蔬菜名
			QString text = QInputDialog::getText(this, tr("修改单元格"), tr("请输入修改内容"), QLineEdit::Normal, 0, &ok);
			if (!ok || text.length()<1)	//未输入情况
				break;
			QModelIndex index = item_model->index(row, 0);	//获取当前坐标
			QString veg = item_model->data(index).toString();	//修改蔬菜名
			VegNameEdit(&head, const_cast<char *>(veg.toLocal8Bit().toStdString().c_str()), const_cast<char *>(text.toLocal8Bit().toStdString().c_str()));
			on_actInfo_triggered();	//刷新表格
			break;
		}
		case 1: {	//修改种类
			QMessageBox::information(NULL, "提示", "种类信息不能修改", QMessageBox::Ok, QMessageBox::Ok);
			break;
		}
		case 2: {
			QString text = QInputDialog::getText(this, tr("修改单元格"), tr("请输入修改内容"), QLineEdit::Normal, 0, &ok);
			if (!ok || text.length()<1)
				break;
			QModelIndex index = item_model->index(row, 0);	//获取当前坐标
			QString veg = item_model->data(index).toString();	//蔬菜名
			ComponentsEdit(&head, const_cast<char *>(veg.toLocal8Bit().toStdString().c_str()), const_cast<char *>(text.toLocal8Bit().toStdString().c_str()));
			on_actInfo_triggered();	//刷新表格
			break;
		}
		default:
			break;
		}
		break;
	}
	case 2: {	//种植表情况下
		int cloum = ui->tableView->currentIndex().column();	//获得修改列号
		int row = ui->tableView->currentIndex().row();	//获得修改行号
		switch (cloum)
		{
		case 0: {	//修改种类
			QMessageBox::information(NULL, "提示", "种类信息不能修改", QMessageBox::Ok, QMessageBox::Ok);
			break;
		}
		case 1: {	//修改蔬菜名
			QString text = QInputDialog::getText(this, tr("修改单元格"), tr("请输入修改内容"), QLineEdit::Normal, 0, &ok);
			if (!ok || text.length()<1)
				break;
			QModelIndex index = item_model->index(row, 1);	//获取当前坐标
			QString veg = item_model->data(index).toString();	//修改蔬菜名
			VegNameEdit(&head, const_cast<char *>(veg.toLocal8Bit().toStdString().c_str()), const_cast<char *>(text.toLocal8Bit().toStdString().c_str()));
			on_actOutPut_triggered();	//刷新表格
			break;
		}
		case 2: {
			QString text = QInputDialog::getText(this, tr("修改单元格"), tr("请输入修改内容"), QLineEdit::Normal, 0, &ok);
			if (!ok || text.length()<1)
				break;
			QModelIndex VegIndex = item_model->index(row, 1);	//获取蔬菜名坐标
			QModelIndex YearIndex = item_model->index(row, 4);	//获取年份坐标
			QString veg = item_model->data(VegIndex).toString();	//蔬菜名
			QString year = item_model->data(YearIndex).toString();	//年份
			AreaWeightEdit(&head, const_cast<char *>(veg.toLocal8Bit().toStdString().c_str()), const_cast<char *>(year.toLocal8Bit().toStdString().c_str()), 0, const_cast<char *>(text.toLocal8Bit().toStdString().c_str()));
			on_actOutPut_triggered();	//刷新表格
			break;
		}
		case 3: {
			QString text = QInputDialog::getText(this, tr("修改单元格"), tr("请输入修改内容"), QLineEdit::Normal, 0, &ok);
			if (!ok || text.length()<1)
				break;
			QModelIndex VegIndex = item_model->index(row, 1);	//获取蔬菜名坐标
			QModelIndex YearIndex = item_model->index(row, 4);	//获取年份坐标
			QString veg = item_model->data(VegIndex).toString();	//蔬菜名
			QString year = item_model->data(YearIndex).toString();	//年份
			AreaWeightEdit(&head, const_cast<char *>(veg.toLocal8Bit().toStdString().c_str()), const_cast<char *>(year.toLocal8Bit().toStdString().c_str()), 1, const_cast<char *>(text.toLocal8Bit().toStdString().c_str()));
			on_actOutPut_triggered();	//刷新表格
			break;
		}
		case 4: {
			QString text = QInputDialog::getText(this, tr("修改单元格"), tr("请输入修改内容"), QLineEdit::Normal, 0, &ok);
			if (!ok || text.length()<1)
				break;
			QModelIndex VegIndex = item_model->index(row, 1);	//获取蔬菜名坐标
			QModelIndex YearIndex = item_model->index(row, 4);	//获取年份坐标
			QString veg = item_model->data(VegIndex).toString();	//蔬菜名
			QString year = item_model->data(YearIndex).toString();	//年份
			if (YearEdit(&head, const_cast<char *>(veg.toLocal8Bit().toStdString().c_str()), const_cast<char *>(year.toLocal8Bit().toStdString().c_str()), const_cast<char *>(text.toLocal8Bit().toStdString().c_str())) == 2)
				QMessageBox::information(NULL, "提示", "该年份已存在", QMessageBox::Ok, QMessageBox::Ok);
			on_actOutPut_triggered();	//刷新表格
			break;
		}
		default:
			break;
		}
		break;
	}
	default:
		break;
	}
}

void MainWindow::on_RightDel_triggered()
{	//右击删除
	switch (state)
	{
	case 0: {
		QModelIndex index = ui->tableView->currentIndex();	//获取当前行列
		QString veg = item_model->data(index).toString();
		KindDelVeg(&head, const_cast<char *>(veg.toLocal8Bit().toStdString().c_str()));	//删除该蔬菜
		on_actKind_triggered();
		break;
	}
	case 1: {
		int row = ui->tableView->currentIndex().row();
		QModelIndex index = item_model->index(row, 0);	//获取当前行列
		QString veg = item_model->data(index).toString();
		KindDelVeg(&head, const_cast<char *>(veg.toLocal8Bit().toStdString().c_str()));	//删除该蔬菜
		on_actInfo_triggered();
		break;
	}
	case 2: {
		int row = ui->tableView->currentIndex().row();
		QModelIndex VegIndex = item_model->index(row, 1);	//获取当前行列
		QModelIndex YearIndex = item_model->index(row, 4);	//获取当前行列
		QString veg = item_model->data(VegIndex).toString();
		QString year = item_model->data(YearIndex).toString();
		KindDelPlant(&head, const_cast<char *>(veg.toLocal8Bit().toStdString().c_str()), const_cast<char *>(year.toLocal8Bit().toStdString().c_str()));
		on_actOutPut_triggered();
		break;
	}
	default:
		break;
	}
}

void MainWindow::on_RightAdd_triggered()
{	//右击添加
	bool ok;
	switch (state)
	{
	case 0: {	//种类界面
		int column = ui->tableView->currentIndex().column();	//获取当前列
		QString text = QInputDialog::getText(this, tr("添加单元格"), tr("请输入需要添加的蔬菜名称"), QLineEdit::Normal, 0, &ok);
		if (!ok || text.length()<1)
			break;
		if (AddVeg(&head, column, const_cast<char *>(text.toLocal8Bit().toStdString().c_str())) == 0) {
			QMessageBox::information(NULL, "提示", "该蔬菜已存在", QMessageBox::Ok, QMessageBox::Ok);
			break;
		}
		on_actKind_triggered();	//刷新表格
		break;
	}
	case 1: {	//信息界面
		QString veg = QInputDialog::getText(this, tr("添加蔬菜组成成分"), tr("请输入需要添加的蔬菜名称"), QLineEdit::Normal, 0, &ok);
		if (!ok || veg.length()<1)
			break;
		QString info = QInputDialog::getText(this, tr("添加蔬菜组成成分"), tr("请输入该蔬菜的主要成分"), QLineEdit::Normal, 0, &ok);
		if (!ok|| info.length()<1)
			break;
		int find = AddInfo(&head, const_cast<char *>(veg.toLocal8Bit().toStdString().c_str()), const_cast<char *>(info.toLocal8Bit().toStdString().c_str()));
		if (find == 0)
			QMessageBox::information(NULL, "提示", "该蔬菜不存在", QMessageBox::Ok, QMessageBox::Ok);
		else if(find ==1)
			QMessageBox::information(NULL, "提示", "该蔬菜成分已存在，可以直接修改", QMessageBox::Ok, QMessageBox::Ok);
		else
			on_actInfo_triggered();	//刷新表格
		break;
	}
	case 2: {	//种植界面
		QString veg = QInputDialog::getText(this, tr("添加蔬菜种植信息"), tr("请输入需要添加的蔬菜名称"), QLineEdit::Normal, 0, &ok);
		if (!ok || veg.length()<1)
			break;
		QString area = QInputDialog::getText(this, tr("添加蔬菜种植信息"), tr("请输入该蔬菜的种植面积"), QLineEdit::Normal, 0, &ok);
		if (!ok || area.length()<1)
			break;
		QString weight = QInputDialog::getText(this, tr("添加蔬菜种植信息"), tr("请输入该蔬菜的收获重量"), QLineEdit::Normal, 0, &ok);
		if (!ok || weight.length()<1)
			break;
		QString year = QInputDialog::getText(this, tr("添加蔬菜种植信息"), tr("请输入该蔬菜的种植年份"), QLineEdit::Normal, 0, &ok);
		if (!ok || year.length()<1)
			break;
		int find = AddPlant(&head, const_cast<char *>(veg.toLocal8Bit().toStdString().c_str()), const_cast<char *>(area.toLocal8Bit().toStdString().c_str()), const_cast<char *>(weight.toLocal8Bit().toStdString().c_str()), const_cast<char *>(year.toLocal8Bit().toStdString().c_str()));
		if (find == 0)
			QMessageBox::information(NULL, "提示", "该蔬菜不存在", QMessageBox::Ok, QMessageBox::Ok);
		else if (find == 2)
			QMessageBox::information(NULL, "提示", "该蔬菜在该年份信息已存在，可以直接修改", QMessageBox::Ok, QMessageBox::Ok);
		else
			on_actOutPut_triggered();	//刷新表格
		break;
	}
	default:
		break;
	}
}

void MainWindow::on_pushButton_area_yes_clicked()
{	//面积筛选确定按钮
	int row;
	char ** kindnum, ** veg, ** area, ** weight, ** year;
	SearchOutPut(head, &kindnum, &veg, &area, &weight, &year, &row, const_cast<char *>(ui->comboBoxKind->currentText().toLocal8Bit().toStdString().c_str()), const_cast<char *>(ui->comboBoxYear->currentText().toLocal8Bit().toStdString().c_str()), const_cast<char *>(ui->lineEdit_area_min->text().toLocal8Bit().toStdString().c_str()), const_cast<char *>(ui->lineEdit_area_max->text().toLocal8Bit().toStdString().c_str()), const_cast<char *>(ui->lineEdit_weight_min->text().toLocal8Bit().toStdString().c_str()), const_cast<char *>(ui->lineEdit_weight_max->text().toLocal8Bit().toStdString().c_str()));
	SetOutPut(row, kindnum, veg, area, weight, year);
}

void MainWindow::on_pushButton_area_clear_clicked()
{	//面积筛选清空按钮
	ui->lineEdit_area_min->clear();	//清空输入框
	ui->lineEdit_area_max->clear();
}

void MainWindow::on_pushButton_weight_yes_clicked()
{	//重量筛选确定按钮
	int row;
	char ** kindnum, ** veg, ** area, ** weight, ** year;
	SearchOutPut(head, &kindnum, &veg, &area, &weight, &year, &row, const_cast<char *>(ui->comboBoxKind->currentText().toLocal8Bit().toStdString().c_str()), const_cast<char *>(ui->comboBoxYear->currentText().toLocal8Bit().toStdString().c_str()), const_cast<char *>(ui->lineEdit_area_min->text().toLocal8Bit().toStdString().c_str()), const_cast<char *>(ui->lineEdit_area_max->text().toLocal8Bit().toStdString().c_str()), const_cast<char *>(ui->lineEdit_weight_min->text().toLocal8Bit().toStdString().c_str()), const_cast<char *>(ui->lineEdit_weight_max->text().toLocal8Bit().toStdString().c_str()));
	SetOutPut(row, kindnum, veg, area, weight, year);
}

void MainWindow::on_pushButton_weight_clear_clicked()
{	//重量筛选清空按钮
	ui->lineEdit_weight_min->clear();	//清空输入框
	ui->lineEdit_weight_max->clear();
	//QMessageBox::information(NULL, "搜索结果", "我就试试", QMessageBox::Ok, QMessageBox::Ok);
}

void MainWindow::on_pushButton_search_engine_clicked()
{	//搜索按钮
	char * text;
	SearchEngines(head, const_cast<char *>(ui->lineEdit->text().toLocal8Bit().toStdString().c_str()), &text);
	string ss = text;
	QMessageBox::information(NULL, "搜索结果", QString::fromLocal8Bit(ss.c_str()), QMessageBox::Ok, QMessageBox::Ok);
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{	//统计的画板
	if (watched == ui->label_3 && event->type() == QEvent::Paint)
	{
		magicTime();
	}
	return QWidget::eventFilter(watched, event);
}

void MainWindow::magicTime()
{	//统计绘画的函数
	int i = 0;
	QPainter painter(ui->label_3);
	painter.setPen(Qt::black);
	painter.setBrush(Qt::gray);
	switch (state)
	{
	case 0: {
		painter.setFont(QFont("Arial", 15));
		int KindCount[5] = {0}, height;
		double max = DrawKind(head, KindCount);
		KindLink temp = head;
		string ss;
		char  TempChar[10];
		QRect rect(120, 0, 200, 20);
		painter.drawText(rect, Qt::AlignCenter, "各种类蔬菜数量统计图");
		painter.setFont(QFont("Arial", 10));
		for (i = 0; i < 5; i++)
		{
			height = int(240 * (KindCount[i] / max));
			painter.drawRect(50+70*i, 280- height, 40 , height);	//x,y,长，宽
			QRect rect1(40 + 70 * i, 290, 60, 12);
			ss = temp->name;
			painter.drawText(rect1, Qt::AlignCenter, QString::fromLocal8Bit(ss.c_str()));
			sprintf(TempChar, "%d", KindCount[i]);
			ss = TempChar;
			QRect rect2(60 + 70 * i, 265 - height, 20, 10);
			painter.drawText(rect2, Qt::AlignCenter, QString::fromLocal8Bit(ss.c_str()));
			temp = temp->next;
		}
		break;
	}
	case 1: {
		painter.setFont(QFont("Arial", 20));
		QRect rect1(150, 150, 200, 25);
		painter.drawText(rect1, Qt::AlignCenter, "暂无相关统计");
		break;
	}
	case 2: {
		switch (ui->comboBox_statistics->currentIndex())
		{
		case 0: {
			char ** KindName;
			double count[5] = { 0 };
			double max = DrawWeight(head, &KindName, count, const_cast<char *>(ui->comboBox__statistics_year_min->currentText().toStdString().c_str()), const_cast<char *>(ui->comboBox__statistics_year_max->currentText().toStdString().c_str()));

			painter.setFont(QFont("Arial", 15));
			int height;
			string ss;
			char  TempChar[10];
			QRect rect(120, 0, 200, 20);
			painter.drawText(rect, Qt::AlignCenter, "各种类蔬菜重量统计图");
			painter.setFont(QFont("Arial", 10));
			for (i = 0; i < 5; i++)
			{
				height = int(240 * (count[i] / max));
				painter.drawRect(50 + 70 * i, 280 - height, 40, height);	//x,y,长，宽
				QRect rect1(40 + 70 * i, 290, 60, 12);
				ss = KindName[i];
				painter.drawText(rect1, Qt::AlignCenter, QString::fromLocal8Bit(ss.c_str()));
				sprintf(TempChar, "%.2f", count[i]);
				ss = TempChar;
				QRect rect2(40 + 70 * i, 265 - height, 60, 10);
				painter.drawText(rect2, Qt::AlignCenter, QString::fromLocal8Bit(ss.c_str()));
			}
			break;
		}
		case 1: {
			char ** KindName;
			double count[5] = { 0 };
			double max = DrawArea(head, &KindName, count, const_cast<char *>(ui->comboBox__statistics_year_min->currentText().toStdString().c_str()), const_cast<char *>(ui->comboBox__statistics_year_max->currentText().toStdString().c_str()));

			painter.setFont(QFont("Arial", 15));
			int height;
			string ss;
			char  TempChar[10];
			QRect rect(120, 0, 200, 20);
			painter.drawText(rect, Qt::AlignCenter, "各种类蔬菜面积统计图");
			painter.setFont(QFont("Arial", 10));
			for (i = 0; i < 5; i++)
			{
				height = int(240 * (count[i] / max));
				painter.drawRect(50 + 70 * i, 280 - height, 40, height);	//x,y,长，宽
				QRect rect1(40 + 70 * i, 290, 60, 12);
				ss = KindName[i];
				painter.drawText(rect1, Qt::AlignCenter, QString::fromLocal8Bit(ss.c_str()));
				sprintf(TempChar, "%.2f", count[i]);
				ss = TempChar;
				QRect rect2(40 + 70 * i, 265 - height, 60, 10);
				painter.drawText(rect2, Qt::AlignCenter, QString::fromLocal8Bit(ss.c_str()));
			}
			break;
		}
		case 2: {
			/*
			char Text[2000] = "\0";
			DrawYear(head, Text, const_cast<char *>(ui->comboBox__statistics_year_min->currentText().toStdString().c_str()), const_cast<char *>(ui->comboBox__statistics_year_max->currentText().toStdString().c_str()));
			
			string ss;
			ss = Text;
			ui->label_3->setText(QString::fromLocal8Bit(ss.c_str()));
			*/
			/*
			painter.setFont(QFont("Arial", 15));
			QRect rect1(200, 0, 200, 20);
			painter.drawText(rect1, Qt::AlignCenter, "各蔬菜重量面积统计表");
			painter.setFont(QFont("Arial", 11));
			string ss;
			ss = Text;
			QRect rect2(120, 20, 400, 200);
			painter.drawText(rect2, Qt::AlignCenter, QString::fromLocal8Bit(ss.c_str()));
			*/
			break;
		}
		default:
			break;
		}
	}
	default:
		break;
	}
}

void MainWindow::on_pushButton_statistics_yes_clicked()
{	//统计确定按钮
	if (state == 2 && ui->comboBox_statistics->currentIndex() == 2)
	{
		char Text[2000] = "\0";
		DrawYear(head, Text, const_cast<char *>(ui->comboBox__statistics_year_min->currentText().toStdString().c_str()), const_cast<char *>(ui->comboBox__statistics_year_max->currentText().toStdString().c_str()));
		string ss;
		ss = Text;
		QMessageBox::information(NULL, "统计结果", QString::fromLocal8Bit(ss.c_str()), QMessageBox::Ok, QMessageBox::Ok);
		//ui->label_3->setText(QString::fromLocal8Bit(ss.c_str()));
	}
}

void MainWindow::on_pushButton_statistics_export_clicked()
{	//统计导出按钮
	if (state == 2 && ui->comboBox_statistics->currentIndex() == 2)
	{
		bool ok;
		QString text = QInputDialog::getText(this, tr("导出"), tr("保存的文件名(.csv)"), QLineEdit::Normal, 0, &ok);
		if (ok && text.length() >= 1) {
			SaveYear(head, const_cast<char *>(text.toLocal8Bit().toStdString().c_str()), const_cast<char *>(ui->comboBox__statistics_year_min->currentText().toStdString().c_str()), const_cast<char *>(ui->comboBox__statistics_year_max->currentText().toStdString().c_str()));
		}
	}
}
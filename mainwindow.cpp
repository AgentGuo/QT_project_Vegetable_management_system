#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qinputdialog.h>
#include <qtextcodec.h>
#include <qmessagebox.h>
using namespace std;

MainWindow::MainWindow(QWidget *parent)//���캯��
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    iniUI();
}
MainWindow::~MainWindow()
{	//��������
    delete ui;
}

void MainWindow::iniUI()
{	//��ʼ������
	LoadKindInfo(&head);
	LoadVegInfo(&head);
	LoadPlantInfo(&head);
	connect(ui->actKind, SIGNAL(triggered()), this, SLOT(on_actKind_triggered()));//Kind��ť
	connect(ui->actInfo, SIGNAL(triggered()), this, SLOT(on_actInfo_triggered()));//Info��ť
	connect(ui->actOutPut, SIGNAL(triggered()), this, SLOT(on_actOutPut_triggered()));//OutPut��ť
	connect(ui->actionExport, SIGNAL(triggered()), this, SLOT(on_actExport_triggered()));//OutPut��ť
	connect(ui->comboBoxKind, SIGNAL(currentIndexChanged(QString)), this, SLOT(ComboKindChangedSlot(const QString &)));//����ɸѡ��
	connect(ui->comboBoxInfo, SIGNAL(currentIndexChanged(QString)), this, SLOT(ComboInfoChangedSlot(const QString &)));//�ɷ�ɸѡ��
	connect(ui->comboBoxYear, SIGNAL(currentIndexChanged(QString)), this, SLOT(ComboYearChangedSlot(const QString &)));//���ɸѡ��
	connect(ui->comboBox_statistics, SIGNAL(currentIndexChanged(QString)), this, SLOT(CombostatisticsChangedSlot(const QString &)));//���ɸѡ��
	//connect(ui->pushButton_area_yes, SIGNAL(clicked()), this, SLOT(on_pushButton_area_yes_clicked()));	//���ȷ�ϰ�ť
	//connect(ui->pushButton_area_yes, SIGNAL(clicked()), this, SLOT(on_pushButton_area_yes_clicked()));	//���ȷ�ϰ�ť
	//connect(ui->pushButton_area_clear, SIGNAL(clicked()), this, SLOT(on_pushButton_area_clear_clicked()));	//�����հ�ť
	//connect(ui->pushButton_weight_yes, SIGNAL(clicked()), this, SLOT(on_pushButton_weight_yes_clicked()));	//����ȷ�ϰ�ť
	//connect(ui->pushButton_weight_clear, SIGNAL(clicked(bool)), this, SLOT(on_pushButton_weight_clear_clicked()));	//������հ�ť
	//connect(ui->pushButton_search_engine, SIGNAL(clicked()), this, SLOT(on_pushButton_search_engine_clicked()));	//������ť
	ui->comboBoxKind->setDisabled(true);//��������ɸѡ��
	ui->comboBoxInfo->setDisabled(true);	//������Ϣɸѡ��
	ui->comboBoxYear->setDisabled(true);	//�������ɸѡ��
	ui->pushButton_area_yes->setDisabled(true);	//�������ȷ�ϰ�ť
	ui->pushButton_weight_yes->setDisabled(true);	//��������ȷ�ϰ�ť
    //ui->tableView = new QTableView(this);
    item_model = new QStandardItemModel(0, 0);//����ʼ��С
	ui->tableView->setModel(item_model);
	//ui->tableView->setGeometry(0,55,600,300);//���ñ��λ�úʹ�С
	//ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);

	//�һ��˵�����
	RightEdit = new QAction("�༭", this);		//�����һ��༭action
	connect(RightEdit, SIGNAL(triggered()), this, SLOT(on_RightEdit_triggered()));	//���Ӳۺ���
	RightDel = new QAction("ɾ��", this);		//�����һ�ɾ��action
	connect(RightDel, SIGNAL(triggered()), this, SLOT(on_RightDel_triggered()));	//���Ӳۺ���
	RightAdd = new QAction("���", this);		//�����һ����action
	connect(RightAdd, SIGNAL(triggered()), this, SLOT(on_RightAdd_triggered()));	//���Ӳۺ���
	RightMenu = new QMenu;	//�����һ��˵�
	RightMenu->addAction(RightEdit);	//�˵������ɾ��action
	RightMenu->addAction(RightDel);	//�˵�����ӱ༭action
	RightMenu->addAction(RightAdd);	//�˵������action
	connect(ui->tableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(clicked_RightMenu(QPoint)));	//���ӱ����˵�
	ui->tableView->setAlternatingRowColors(true);	//���ñ��ͬ����ɫ
	ui->label_3->installEventFilter(this);        //��װ�¼�������������

	QStringList StatisticsList;
	StatisticsList << "�����߲�����ͳ��" << "�����߲����ͳ��" << "���ͳ��";	//����ɸѡ������
	ui->comboBox_statistics->addItems(StatisticsList);
	QStringList StatisticsYearMinList;
	StatisticsYearMinList << "2015" << "2016" << "2017" << "2018" << "2019" << "2020";	//����ɸѡ������
	ui->comboBox__statistics_year_min->addItems(StatisticsYearMinList);
	QStringList StatisticsYearMaxList;
	StatisticsYearMaxList << "2015" << "2016" << "2017" << "2018" << "2019" << "2020";	//����ɸѡ������
	ui->comboBox__statistics_year_max->addItems(StatisticsYearMaxList);
	ui->label_statistics->setVisible(false);	//����ͳ�Ʋ��ֵĿؼ�
	ui->label_statistics_nothing->setVisible(false);
	ui->label__statistics_year->setVisible(false);
	ui->comboBox_statistics->setVisible(false);
	ui->comboBox__statistics_year_min->setVisible(false);
	ui->comboBox__statistics_year_max->setVisible(false);
	ui->pushButton_statistics_yes->setVisible(false);
	ui->pushButton_statistics_export->setVisible(false);
}

void MainWindow::on_actSubmit_triggered()
{	//���水ť
	write(head);
}

void MainWindow::on_actKind_triggered()
{	//�߲����ఴť
	state = 0;
	KindFirst = true;
	ui->comboBoxKind->clear();	//���ɸѡ��
	ui->comboBoxKind->setEnabled(true);	//��������ɸѡ��
	ui->comboBoxInfo->setDisabled(true);	//������Ϣɸѡ��
	ui->comboBoxYear->setDisabled(true);	//�������ɸѡ��
	ui->pushButton_area_yes->setDisabled(true);	//�������ȷ�ϰ�ť
	ui->pushButton_weight_yes->setDisabled(true);	//��������ȷ�ϰ�ť
	ui->lineEdit_area_min->clear();	//��������
	ui->lineEdit_area_max->clear();
	ui->lineEdit_weight_min->clear();
	ui->lineEdit_weight_max->clear();
	QStringList strlist;
	strlist << "all" << "1" << "2" << "3" << "4" << "5";	//����ɸѡ������
	ui->comboBoxKind->addItems(strlist);
	int row = 1, column = 1;
	char **kind;
	char ***veg;
	SearchKind(head, &kind, &veg, &row, &column, NULL);	//��ѯ������Ϣ
	SetKind(row, column, kind, veg);	//������Ϣ
	ui->label_statistics->setVisible(false);
	ui->label_statistics_nothing->setVisible(false);
	ui->label__statistics_year->setVisible(false);
	ui->comboBox_statistics->setVisible(false);
	ui->comboBox__statistics_year_min->setVisible(false);
	ui->comboBox__statistics_year_max->setVisible(false);
}

void MainWindow::on_actInfo_triggered()
{	//�߲˻�����Ϣ��ť
	state = 1;
	ui->comboBoxKind->clear();	//�������ɸѡ��
	ui->comboBoxInfo->clear();	//�����Ϣɸѡ��
	ui->lineEdit_area_min->clear();	//��������
	ui->lineEdit_area_max->clear();
	ui->lineEdit_weight_min->clear();
	ui->lineEdit_weight_max->clear();
	ui->comboBoxKind->setEnabled(true);	//��������ɸѡ��
	ui->comboBoxInfo->setEnabled(true);	//������Ϣɸѡ��
	ui->comboBoxYear->setDisabled(true);	//�������ɸѡ��
	ui->pushButton_area_yes->setDisabled(true);	//�������ȷ�ϰ�ť
	ui->pushButton_weight_yes->setDisabled(true);	//��������ȷ�ϰ�ť
	InfoFirst = true;	//��һ��ʹ�ã������ظ�ˢ��
	int row = 1;
	char **veg;
	char **kindnum;
	char **components;
	ui->comboBoxKind->clear();	//���ɸѡ��
	ui->comboBoxInfo->clear();	//���ɸѡ��
	QStringList KindList, InfoList;
	KindList << "all" << "1" << "2" << "3" << "4" << "5";	//��������ɸѡ������
	InfoList << "all" << "������" << "������" << "����" << "����ø" << "ά����A" << "ά����B1" << "ά����B2" << "ά����C" << "ά����K" << "���ܲ���" << "��" << "��" << "��" << "��" << "п" << "��" << "ͭ" << "þ" << "��" << "��";	//������Ϣɸѡ������
	ui->comboBoxKind->addItems(KindList);
	ui->comboBoxInfo->addItems(InfoList);
	SearchInfo(head, &veg, &kindnum, &components, &row, const_cast<char *>(ui->comboBoxKind->currentText().toLocal8Bit().toStdString().c_str()), const_cast<char *>(ui->comboBoxInfo->currentText().toLocal8Bit().toStdString().c_str()));	//��ȡ��Ϣ
	SetInfo(row, veg, kindnum, components);	//������Ϣ
	ui->label_statistics->setVisible(false);
	ui->label_statistics_nothing->setVisible(false);
	ui->label__statistics_year->setVisible(false);
	ui->comboBox_statistics->setVisible(false);
	ui->comboBox__statistics_year_min->setVisible(false);
	ui->comboBox__statistics_year_max->setVisible(false);
} 

void MainWindow::on_actOutPut_triggered()
{	//�߲˲�����Ϣ��ť
	state = 2;
	OutPutFirst = true;
	item_model->clear();//������
	ui->comboBoxKind->clear();	//�������ɸѡ��
	ui->comboBoxYear->clear();	//�������ɸѡ��
	ui->lineEdit_area_min->clear();	//��������
	ui->lineEdit_area_max->clear();
	ui->lineEdit_weight_min->clear();
	ui->lineEdit_weight_max->clear();
	ui->comboBoxKind->setEnabled(true);	//��������ɸѡ��
	ui->comboBoxInfo->setDisabled(true);	//������Ϣɸѡ��
	ui->comboBoxYear->setEnabled(true);	//���������ɸѡ��
	ui->pushButton_area_yes->setEnabled(true);	//�������ȷ�ϰ�ť
	ui->pushButton_weight_yes->setEnabled(true);	//��������ȷ�ϰ�ť
	QStringList KindList;
	KindList << "all" << "1" << "2" << "3" << "4" << "5";	//����ɸѡ������
	ui->comboBoxKind->addItems(KindList);
	QStringList YearList;
	YearList << "all" << "2015" << "2016" << "2017" << "2018" << "2019" << "2020";	//����ɸѡ������
	ui->comboBoxYear->addItems(YearList);
	item_model->setColumnCount(5);
	item_model->setRowCount(0);
	item_model->setHeaderData(0, Qt::Horizontal, "�߲˱��");//�����ֶ���
	item_model->setHeaderData(1, Qt::Horizontal, "�߲�����");
	item_model->setHeaderData(2, Qt::Horizontal, "��ֲ���");
	item_model->setHeaderData(3, Qt::Horizontal, "�ջ�����");
	item_model->setHeaderData(4, Qt::Horizontal, "��ֲ���");
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
{	//������ť
	int i, j;
	bool ok;
	QString text = QInputDialog::getText(this, tr("����"), tr("������ļ���(.csv)"), QLineEdit::Normal, 0, &ok);
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
{	//����ɸѡ������
	switch (state)
	{
	case 0: {
		if (KindFirst == false)
		{
			int row = 1, column = 1;
			char **kind;
			char ***veg;
			SearchKind(head, &kind, &veg, &row, &column, const_cast<char *>(a.toStdString().c_str()));	//��ѯ������Ϣ
			SetKind(row, column, kind, veg);	//������Ϣ
		}
		else
			KindFirst = false;
		break;
	}
	case 1: {//״̬1����info״̬
		if (InfoFirst == false) {
			int row = 1;
			char **veg;
			char **kindnum;
			char **components;
			//const_cast<char *>(ui->comboBoxInfo->currentText.toLocal8Bit().toStdString().c_str())
			SearchInfo(head, &veg, &kindnum, &components, &row, const_cast<char *>(a.toStdString().c_str()), const_cast<char *>(ui->comboBoxInfo->currentText().toLocal8Bit().toStdString().c_str()));//��ȡ��Ϣ
			SetInfo(row, veg, kindnum, components);//������Ϣ
		}
		else
			InfoFirst = false;
		break;
	}
	case 2: {//״̬2����OutPut״̬
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
{	//Ӫ������ɸѡ������
	int row = 1;
	char **veg;
	char **kindnum;
	char **components;
	//const_cast<char *>(ui->comboBoxInfo->currentText.toLocal8Bit().toStdString().c_str())
	SearchInfo(head, &veg, &kindnum, &components, &row, const_cast<char *>(ui->comboBoxKind->currentText().toStdString().c_str()), const_cast<char *>(ui->comboBoxInfo->currentText().toLocal8Bit().toStdString().c_str()));//��ȡ��Ϣ
	SetInfo(row, veg, kindnum, components);//������Ϣ
}

void MainWindow::ComboYearChangedSlot(const QString &a)
{	//���������
	int row;
	char ** kindnum, ** veg, ** area, ** weight, ** year;
	SearchOutPut(head, &kindnum, &veg, &area, &weight, &year, &row, const_cast<char *>(ui->comboBoxKind->currentText().toLocal8Bit().toStdString().c_str()), const_cast<char *>(ui->comboBoxYear->currentText().toLocal8Bit().toStdString().c_str()), const_cast<char *>(ui->lineEdit_area_min->text().toLocal8Bit().toStdString().c_str()), const_cast<char *>(ui->lineEdit_area_max->text().toLocal8Bit().toStdString().c_str()), const_cast<char *>(ui->lineEdit_weight_min->text().toLocal8Bit().toStdString().c_str()), const_cast<char *>(ui->lineEdit_weight_max->text().toLocal8Bit().toStdString().c_str()));
	SetOutPut(row, kindnum, veg, area, weight, year);
}

void MainWindow::CombostatisticsChangedSlot(const QString &a)
{	//ͳ����Ϣ������
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
{	//��������
	int  i = 0, j = 0;
	QTextCodec *codec = QTextCodec::codecForName("GBK");//�������뷽ʽ����ֹ��������
	item_model->clear();//������
	item_model->setColumnCount(column);
	item_model->setRowCount(row);
	for (i = 0; i < column; i++)
	{
		item_model->setHeaderData(i, Qt::Horizontal, codec->toUnicode(kind[i]));//�����ֶ���
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
{	//�����߲˻�����Ϣ
	int i = 0;
	ui->tableView->setColumnWidth(3, 200);
	item_model->clear();//������
	item_model->setColumnCount(3);
	item_model->setRowCount(row);
	item_model->setHeaderData(0, Qt::Horizontal, "�߲�����");//�����ֶ���
	item_model->setHeaderData(1, Qt::Horizontal, "������");
	item_model->setHeaderData(2, Qt::Horizontal, "Ӫ���ɷ�");
	QTextCodec *codec = QTextCodec::codecForName("GBK");//�������뷽ʽ����ֹ��������
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
{	//�����߲���ֲ��Ϣ
	int i = 0;
	item_model->setRowCount(row);
	QTextCodec *codec = QTextCodec::codecForName("GBK");//�������뷽ʽ����ֹ��������
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

void MainWindow::clicked_RightMenu(const QPoint & pos)	//�һ��˵�
{	//�һ��˵�
	RightMenu->exec(QCursor::pos());
}

void MainWindow::on_RightEdit_triggered()
{	//�һ��༭
	bool ok;
	switch (state)
	{
	case 0: {	//����������
		QString text = QInputDialog::getText(this, tr("�޸ĵ�Ԫ��"), tr("�������޸�����"), QLineEdit::Normal, 0, &ok);
		if (!ok|| text.length()<1)
			break;
		QModelIndex index = ui->tableView->currentIndex();	//��ȡ��ǰ����
		QString veg = item_model->data(index).toString();	//�޸��߲���
		VegNameEdit(&head, const_cast<char *>(veg.toLocal8Bit().toStdString().c_str()), const_cast<char *>(text.toLocal8Bit().toStdString().c_str()));
		on_actKind_triggered();	//ˢ�±��
		break;
	}
	case 1: {	//��Ϣ�������
		int cloum = ui->tableView->currentIndex().column();	//����޸��к�
		int row = ui->tableView->currentIndex().row();	//����޸��к�
		switch (cloum)
		{
		case 0: {	//�޸��߲���
			QString text = QInputDialog::getText(this, tr("�޸ĵ�Ԫ��"), tr("�������޸�����"), QLineEdit::Normal, 0, &ok);
			if (!ok || text.length()<1)	//δ�������
				break;
			QModelIndex index = item_model->index(row, 0);	//��ȡ��ǰ����
			QString veg = item_model->data(index).toString();	//�޸��߲���
			VegNameEdit(&head, const_cast<char *>(veg.toLocal8Bit().toStdString().c_str()), const_cast<char *>(text.toLocal8Bit().toStdString().c_str()));
			on_actInfo_triggered();	//ˢ�±��
			break;
		}
		case 1: {	//�޸�����
			QMessageBox::information(NULL, "��ʾ", "������Ϣ�����޸�", QMessageBox::Ok, QMessageBox::Ok);
			break;
		}
		case 2: {
			QString text = QInputDialog::getText(this, tr("�޸ĵ�Ԫ��"), tr("�������޸�����"), QLineEdit::Normal, 0, &ok);
			if (!ok || text.length()<1)
				break;
			QModelIndex index = item_model->index(row, 0);	//��ȡ��ǰ����
			QString veg = item_model->data(index).toString();	//�߲���
			ComponentsEdit(&head, const_cast<char *>(veg.toLocal8Bit().toStdString().c_str()), const_cast<char *>(text.toLocal8Bit().toStdString().c_str()));
			on_actInfo_triggered();	//ˢ�±��
			break;
		}
		default:
			break;
		}
		break;
	}
	case 2: {	//��ֲ�������
		int cloum = ui->tableView->currentIndex().column();	//����޸��к�
		int row = ui->tableView->currentIndex().row();	//����޸��к�
		switch (cloum)
		{
		case 0: {	//�޸�����
			QMessageBox::information(NULL, "��ʾ", "������Ϣ�����޸�", QMessageBox::Ok, QMessageBox::Ok);
			break;
		}
		case 1: {	//�޸��߲���
			QString text = QInputDialog::getText(this, tr("�޸ĵ�Ԫ��"), tr("�������޸�����"), QLineEdit::Normal, 0, &ok);
			if (!ok || text.length()<1)
				break;
			QModelIndex index = item_model->index(row, 1);	//��ȡ��ǰ����
			QString veg = item_model->data(index).toString();	//�޸��߲���
			VegNameEdit(&head, const_cast<char *>(veg.toLocal8Bit().toStdString().c_str()), const_cast<char *>(text.toLocal8Bit().toStdString().c_str()));
			on_actOutPut_triggered();	//ˢ�±��
			break;
		}
		case 2: {
			QString text = QInputDialog::getText(this, tr("�޸ĵ�Ԫ��"), tr("�������޸�����"), QLineEdit::Normal, 0, &ok);
			if (!ok || text.length()<1)
				break;
			QModelIndex VegIndex = item_model->index(row, 1);	//��ȡ�߲�������
			QModelIndex YearIndex = item_model->index(row, 4);	//��ȡ�������
			QString veg = item_model->data(VegIndex).toString();	//�߲���
			QString year = item_model->data(YearIndex).toString();	//���
			AreaWeightEdit(&head, const_cast<char *>(veg.toLocal8Bit().toStdString().c_str()), const_cast<char *>(year.toLocal8Bit().toStdString().c_str()), 0, const_cast<char *>(text.toLocal8Bit().toStdString().c_str()));
			on_actOutPut_triggered();	//ˢ�±��
			break;
		}
		case 3: {
			QString text = QInputDialog::getText(this, tr("�޸ĵ�Ԫ��"), tr("�������޸�����"), QLineEdit::Normal, 0, &ok);
			if (!ok || text.length()<1)
				break;
			QModelIndex VegIndex = item_model->index(row, 1);	//��ȡ�߲�������
			QModelIndex YearIndex = item_model->index(row, 4);	//��ȡ�������
			QString veg = item_model->data(VegIndex).toString();	//�߲���
			QString year = item_model->data(YearIndex).toString();	//���
			AreaWeightEdit(&head, const_cast<char *>(veg.toLocal8Bit().toStdString().c_str()), const_cast<char *>(year.toLocal8Bit().toStdString().c_str()), 1, const_cast<char *>(text.toLocal8Bit().toStdString().c_str()));
			on_actOutPut_triggered();	//ˢ�±��
			break;
		}
		case 4: {
			QString text = QInputDialog::getText(this, tr("�޸ĵ�Ԫ��"), tr("�������޸�����"), QLineEdit::Normal, 0, &ok);
			if (!ok || text.length()<1)
				break;
			QModelIndex VegIndex = item_model->index(row, 1);	//��ȡ�߲�������
			QModelIndex YearIndex = item_model->index(row, 4);	//��ȡ�������
			QString veg = item_model->data(VegIndex).toString();	//�߲���
			QString year = item_model->data(YearIndex).toString();	//���
			if (YearEdit(&head, const_cast<char *>(veg.toLocal8Bit().toStdString().c_str()), const_cast<char *>(year.toLocal8Bit().toStdString().c_str()), const_cast<char *>(text.toLocal8Bit().toStdString().c_str())) == 2)
				QMessageBox::information(NULL, "��ʾ", "������Ѵ���", QMessageBox::Ok, QMessageBox::Ok);
			on_actOutPut_triggered();	//ˢ�±��
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
{	//�һ�ɾ��
	switch (state)
	{
	case 0: {
		QModelIndex index = ui->tableView->currentIndex();	//��ȡ��ǰ����
		QString veg = item_model->data(index).toString();
		KindDelVeg(&head, const_cast<char *>(veg.toLocal8Bit().toStdString().c_str()));	//ɾ�����߲�
		on_actKind_triggered();
		break;
	}
	case 1: {
		int row = ui->tableView->currentIndex().row();
		QModelIndex index = item_model->index(row, 0);	//��ȡ��ǰ����
		QString veg = item_model->data(index).toString();
		KindDelVeg(&head, const_cast<char *>(veg.toLocal8Bit().toStdString().c_str()));	//ɾ�����߲�
		on_actInfo_triggered();
		break;
	}
	case 2: {
		int row = ui->tableView->currentIndex().row();
		QModelIndex VegIndex = item_model->index(row, 1);	//��ȡ��ǰ����
		QModelIndex YearIndex = item_model->index(row, 4);	//��ȡ��ǰ����
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
{	//�һ����
	bool ok;
	switch (state)
	{
	case 0: {	//�������
		int column = ui->tableView->currentIndex().column();	//��ȡ��ǰ��
		QString text = QInputDialog::getText(this, tr("��ӵ�Ԫ��"), tr("��������Ҫ��ӵ��߲�����"), QLineEdit::Normal, 0, &ok);
		if (!ok || text.length()<1)
			break;
		if (AddVeg(&head, column, const_cast<char *>(text.toLocal8Bit().toStdString().c_str())) == 0) {
			QMessageBox::information(NULL, "��ʾ", "���߲��Ѵ���", QMessageBox::Ok, QMessageBox::Ok);
			break;
		}
		on_actKind_triggered();	//ˢ�±��
		break;
	}
	case 1: {	//��Ϣ����
		QString veg = QInputDialog::getText(this, tr("����߲���ɳɷ�"), tr("��������Ҫ��ӵ��߲�����"), QLineEdit::Normal, 0, &ok);
		if (!ok || veg.length()<1)
			break;
		QString info = QInputDialog::getText(this, tr("����߲���ɳɷ�"), tr("��������߲˵���Ҫ�ɷ�"), QLineEdit::Normal, 0, &ok);
		if (!ok|| info.length()<1)
			break;
		int find = AddInfo(&head, const_cast<char *>(veg.toLocal8Bit().toStdString().c_str()), const_cast<char *>(info.toLocal8Bit().toStdString().c_str()));
		if (find == 0)
			QMessageBox::information(NULL, "��ʾ", "���߲˲�����", QMessageBox::Ok, QMessageBox::Ok);
		else if(find ==1)
			QMessageBox::information(NULL, "��ʾ", "���߲˳ɷ��Ѵ��ڣ�����ֱ���޸�", QMessageBox::Ok, QMessageBox::Ok);
		else
			on_actInfo_triggered();	//ˢ�±��
		break;
	}
	case 2: {	//��ֲ����
		QString veg = QInputDialog::getText(this, tr("����߲���ֲ��Ϣ"), tr("��������Ҫ��ӵ��߲�����"), QLineEdit::Normal, 0, &ok);
		if (!ok || veg.length()<1)
			break;
		QString area = QInputDialog::getText(this, tr("����߲���ֲ��Ϣ"), tr("��������߲˵���ֲ���"), QLineEdit::Normal, 0, &ok);
		if (!ok || area.length()<1)
			break;
		QString weight = QInputDialog::getText(this, tr("����߲���ֲ��Ϣ"), tr("��������߲˵��ջ�����"), QLineEdit::Normal, 0, &ok);
		if (!ok || weight.length()<1)
			break;
		QString year = QInputDialog::getText(this, tr("����߲���ֲ��Ϣ"), tr("��������߲˵���ֲ���"), QLineEdit::Normal, 0, &ok);
		if (!ok || year.length()<1)
			break;
		int find = AddPlant(&head, const_cast<char *>(veg.toLocal8Bit().toStdString().c_str()), const_cast<char *>(area.toLocal8Bit().toStdString().c_str()), const_cast<char *>(weight.toLocal8Bit().toStdString().c_str()), const_cast<char *>(year.toLocal8Bit().toStdString().c_str()));
		if (find == 0)
			QMessageBox::information(NULL, "��ʾ", "���߲˲�����", QMessageBox::Ok, QMessageBox::Ok);
		else if (find == 2)
			QMessageBox::information(NULL, "��ʾ", "���߲��ڸ������Ϣ�Ѵ��ڣ�����ֱ���޸�", QMessageBox::Ok, QMessageBox::Ok);
		else
			on_actOutPut_triggered();	//ˢ�±��
		break;
	}
	default:
		break;
	}
}

void MainWindow::on_pushButton_area_yes_clicked()
{	//���ɸѡȷ����ť
	int row;
	char ** kindnum, ** veg, ** area, ** weight, ** year;
	SearchOutPut(head, &kindnum, &veg, &area, &weight, &year, &row, const_cast<char *>(ui->comboBoxKind->currentText().toLocal8Bit().toStdString().c_str()), const_cast<char *>(ui->comboBoxYear->currentText().toLocal8Bit().toStdString().c_str()), const_cast<char *>(ui->lineEdit_area_min->text().toLocal8Bit().toStdString().c_str()), const_cast<char *>(ui->lineEdit_area_max->text().toLocal8Bit().toStdString().c_str()), const_cast<char *>(ui->lineEdit_weight_min->text().toLocal8Bit().toStdString().c_str()), const_cast<char *>(ui->lineEdit_weight_max->text().toLocal8Bit().toStdString().c_str()));
	SetOutPut(row, kindnum, veg, area, weight, year);
}

void MainWindow::on_pushButton_area_clear_clicked()
{	//���ɸѡ��հ�ť
	ui->lineEdit_area_min->clear();	//��������
	ui->lineEdit_area_max->clear();
}

void MainWindow::on_pushButton_weight_yes_clicked()
{	//����ɸѡȷ����ť
	int row;
	char ** kindnum, ** veg, ** area, ** weight, ** year;
	SearchOutPut(head, &kindnum, &veg, &area, &weight, &year, &row, const_cast<char *>(ui->comboBoxKind->currentText().toLocal8Bit().toStdString().c_str()), const_cast<char *>(ui->comboBoxYear->currentText().toLocal8Bit().toStdString().c_str()), const_cast<char *>(ui->lineEdit_area_min->text().toLocal8Bit().toStdString().c_str()), const_cast<char *>(ui->lineEdit_area_max->text().toLocal8Bit().toStdString().c_str()), const_cast<char *>(ui->lineEdit_weight_min->text().toLocal8Bit().toStdString().c_str()), const_cast<char *>(ui->lineEdit_weight_max->text().toLocal8Bit().toStdString().c_str()));
	SetOutPut(row, kindnum, veg, area, weight, year);
}

void MainWindow::on_pushButton_weight_clear_clicked()
{	//����ɸѡ��հ�ť
	ui->lineEdit_weight_min->clear();	//��������
	ui->lineEdit_weight_max->clear();
	//QMessageBox::information(NULL, "�������", "�Ҿ�����", QMessageBox::Ok, QMessageBox::Ok);
}

void MainWindow::on_pushButton_search_engine_clicked()
{	//������ť
	char * text;
	SearchEngines(head, const_cast<char *>(ui->lineEdit->text().toLocal8Bit().toStdString().c_str()), &text);
	string ss = text;
	QMessageBox::information(NULL, "�������", QString::fromLocal8Bit(ss.c_str()), QMessageBox::Ok, QMessageBox::Ok);
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{	//ͳ�ƵĻ���
	if (watched == ui->label_3 && event->type() == QEvent::Paint)
	{
		magicTime();
	}
	return QWidget::eventFilter(watched, event);
}

void MainWindow::magicTime()
{	//ͳ�ƻ滭�ĺ���
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
		painter.drawText(rect, Qt::AlignCenter, "�������߲�����ͳ��ͼ");
		painter.setFont(QFont("Arial", 10));
		for (i = 0; i < 5; i++)
		{
			height = int(240 * (KindCount[i] / max));
			painter.drawRect(50+70*i, 280- height, 40 , height);	//x,y,������
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
		painter.drawText(rect1, Qt::AlignCenter, "�������ͳ��");
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
			painter.drawText(rect, Qt::AlignCenter, "�������߲�����ͳ��ͼ");
			painter.setFont(QFont("Arial", 10));
			for (i = 0; i < 5; i++)
			{
				height = int(240 * (count[i] / max));
				painter.drawRect(50 + 70 * i, 280 - height, 40, height);	//x,y,������
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
			painter.drawText(rect, Qt::AlignCenter, "�������߲����ͳ��ͼ");
			painter.setFont(QFont("Arial", 10));
			for (i = 0; i < 5; i++)
			{
				height = int(240 * (count[i] / max));
				painter.drawRect(50 + 70 * i, 280 - height, 40, height);	//x,y,������
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
			painter.drawText(rect1, Qt::AlignCenter, "���߲��������ͳ�Ʊ�");
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
{	//ͳ��ȷ����ť
	if (state == 2 && ui->comboBox_statistics->currentIndex() == 2)
	{
		char Text[2000] = "\0";
		DrawYear(head, Text, const_cast<char *>(ui->comboBox__statistics_year_min->currentText().toStdString().c_str()), const_cast<char *>(ui->comboBox__statistics_year_max->currentText().toStdString().c_str()));
		string ss;
		ss = Text;
		QMessageBox::information(NULL, "ͳ�ƽ��", QString::fromLocal8Bit(ss.c_str()), QMessageBox::Ok, QMessageBox::Ok);
		//ui->label_3->setText(QString::fromLocal8Bit(ss.c_str()));
	}
}

void MainWindow::on_pushButton_statistics_export_clicked()
{	//ͳ�Ƶ�����ť
	if (state == 2 && ui->comboBox_statistics->currentIndex() == 2)
	{
		bool ok;
		QString text = QInputDialog::getText(this, tr("����"), tr("������ļ���(.csv)"), QLineEdit::Normal, 0, &ok);
		if (ok && text.length() >= 1) {
			SaveYear(head, const_cast<char *>(text.toLocal8Bit().toStdString().c_str()), const_cast<char *>(ui->comboBox__statistics_year_min->currentText().toStdString().c_str()), const_cast<char *>(ui->comboBox__statistics_year_max->currentText().toStdString().c_str()));
		}
	}
}
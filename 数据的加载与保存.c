#include "head.h"
#include<string.h>
#include<stdlib.h>
KindLink init_Kindlist() {	//初始化一个表头结点，函数最终返回一个表头结点
	KindLink head = NULL;
	return head;
}

void write(KindLink head)	//文件保存函数，用于保存当前蔬菜链表的信息，下次系统启动就能直接加载，入口参数：蔬菜的整个链表
{
	int row = 0, i = 0, j = 0, InfoCount = 1, PlantCount = 1;
	char *** veg;
	FILE* KindFp = NULL;
	FILE* InfoFp = NULL;
	FILE* PlantFp = NULL;
	KindFp = fopen("./data/KindInformation.csv", "w");
	PlantFp = fopen("./data/PlantInformation.csv", "w");
	InfoFp = fopen("./data/VegInformation.csv", "w");
	fprintf(KindFp, "分类编号,1,2,3,4,5\n");
	fprintf(KindFp, "分类名称,根茎类,果蔬类,瓜类,叶菜类,菌类\n蔬菜名称");
	fprintf(InfoFp, "蔬菜编号,蔬菜名称,分类码,营养成分\n");
	fprintf(PlantFp, "编号,蔬菜编号,蔬菜名称,种植面积,收获重量,种植年份\n");
	KindLink temp = head;
	VegLink veghead;
	PlantLink plant;
	while (temp != NULL) {//求出行数和列数
		if (temp->VegCount > row)
			row = temp->VegCount;//求出最大行数
		temp = temp->next;
	}
	veg = (char ***)malloc(sizeof(char **)*5);
	for (i = 0; i < 5; i++)
	{
		veg[i] = (char **)malloc(sizeof(char *)*row);
		for (j = 0; j < row; j++)
		{
			veg[i][j] = (char *)malloc(sizeof(char) * 20);//动态创建蔬菜名称数组
			strcpy(veg[i][j], ",\0");//初始化
		}
	}
	temp = head;
	i = 0;
	while (temp != NULL)
	{
		j = 0;
		veghead = temp->veghead;
		while (veghead != NULL)
		{
			strcat(veg[i][j], veghead->vegname);
			if (strlen(veghead->components) != 0)
			{
				fprintf(InfoFp, "%d,%s,%s,%s\n", InfoCount,veghead->vegname,temp->kindnum,veghead->components);
				InfoCount++;
			}
			plant = veghead->plant;
			while (plant != NULL)
			{
				fprintf(PlantFp, "%d,%s,%s,%f,%f,%d\n", PlantCount, temp->kindnum, veghead->vegname, plant->area, plant->weight, plant->year);
				PlantCount++;
				plant = plant->next;
			}
			veghead = veghead->next;
			j++;
		}
		temp = temp->next;
		i++;
	}
	for (i = 0; i < row; i++)
	{
		fprintf(KindFp, "%s%s%s%s%s\n", veg[0][i], veg[1][i], veg[2][i], veg[3][i], veg[4][i]);
	}
	fclose(KindFp);
	fclose(InfoFp);
	fclose(PlantFp);
	//	writeExcel()  ;	
}

void LoadKindInfo(KindLink* head)	//加载种类信息表，将种类信息表中的数据加载到链表中，入口参数：链表的表头
{
	KindLink* temp = head, kindp;
	VegLink vegp, *veghead;
	char file[30] = "./data/KindInformation.csv", ch = '\0', kindnum[5] = { 0 }, kindname[20] = { 0 }, vegname[20] = { 0 };
	int i = 0;
	FILE* fp = NULL;
	fp = fopen(file, "r");
	while (ch != ',')
		ch = fgetc(fp);//读取表格的第一个单元格，不使用
	while ((ch = fgetc(fp)) != '\n') {//读完第一行
		i = 0;
		while (ch != ','&&ch != '\n') {//读一格
			kindnum[i] = ch;
			i++;
			ch = fgetc(fp);
		}
		kindnum[i] = '\0';
		kindp = (KindLink)malloc(sizeof(KindNode));//产生一个新节点
		strcpy((kindp)->kindnum, kindnum);
		kindp->next = NULL;
		kindp->veghead = NULL;
		(*temp) = kindp;
		temp = &((*temp)->next);
		//printf("%s", kindnum);
		if (ch == '\n')
			break;
	}
	printf("read kindnum done!\n");//类别编号读取完毕


	temp = head;//重新从第一个节点开始
	while (ch != ',')
		ch = fgetc(fp);//读取完第二行第一个单元格，不使用
	while ((ch = fgetc(fp)) != '\n') {//读完第二行
		i = 0;
		while (ch != ',' && ch != '\n') {//读一个单元格
			kindname[i] = ch;
			i++;
			ch = fgetc(fp);
		}
		kindname[i] = '\0';
		strcpy((*temp)->name, kindname);
		(*temp)->VegCount = 0;
		(*temp)->ComponetsCount = 0;
		temp = &((*temp)->next);
		//printf("%s", name);
		if (ch == '\n')
			break;
	}
	printf("read name done!\n");//类别种类名称读取完毕

	while (ch != EOF) {//读蔬菜名称，直到文件尾
		temp = head;
		while (ch != ','&&ch != EOF)//去掉每一行开头
			ch = fgetc(fp);
		if (ch == EOF)
			break;
		while ((ch = fgetc(fp)) != '\n') {//读取每一行的蔬菜名
			i = 0;
			while (ch != ',' && ch != '\n') {//获取蔬菜名
				vegname[i] = ch;
				i++;
				ch = fgetc(fp);
			}
			vegname[i] = '\0';
			if (strlen(vegname) > 0) {//当蔬菜名非空时，添加到链表
				vegp = (VegLink)malloc(sizeof(VegNode));
				strcpy(vegp->vegname, vegname);
				vegp->next = NULL;
				vegp->plant = NULL;
				(vegp->components)[0] = '\0';
				veghead = &((*temp)->veghead);
				while ((*veghead) != NULL)
					veghead = &((*veghead)->next);
				*veghead = vegp;
				(*temp)->VegCount++;
			}
			temp = &((*temp)->next);
			if (ch == '\n')
				break;
		}
	}
	fclose(fp);
}

void LoadVegInfo(KindLink* head) {	//加载蔬菜基本信息表，将蔬菜基本信息表中的数据加载到链表中，入口参数：链表的表头
	KindLink* temp = head;
	VegLink* vegp;
	char file[30] = "./data/VegInformation.csv", ch, kindnum[5], vegname[20], components[60];
	int i;
	FILE* fp = NULL;
	fp = fopen(file, "r");
	while ((ch = fgetc(fp)) != '\n')//读取第一行，不使用
		;
	while ((ch = fgetc(fp)) != EOF) {
		i = 0;
		while (ch != ',')//读取第一格，不使用
			ch = fgetc(fp);
		ch = fgetc(fp);
		while (ch != ',') {//读取第二格，蔬菜名字
			vegname[i] = ch;
			ch = fgetc(fp);
			i++;
		}
		vegname[i] = '\0';
		i = 0;
		ch = fgetc(fp);
		while (ch != ',') {//读取第三格，蔬菜种类
			kindnum[i] = ch;
			ch = fgetc(fp);
			i++;
		}
		kindnum[i] = '\0';
		i = 0;
		ch = fgetc(fp);
		while (ch != '\n'&&ch != EOF) {//读取第四格，蔬菜成分
			components[i] = ch;
			ch = fgetc(fp);
			i++;
		}
		components[i] = '\0';
		temp = head;
		while (strcmp(kindnum, (*temp)->kindnum) != 0)//查找蔬菜种类
			temp = &((*temp)->next);
		vegp = &((*temp)->veghead);
		while (((*vegp) != NULL) && (strcmp(vegname, (*vegp)->vegname) != 0)) {//查找蔬菜名
			vegp = &((*vegp)->next);
		}
		if ((*vegp) == NULL) {//查找失败
			printf("%s\t%s\t%s\t不存在！", kindnum, vegname, components);
			continue;
		}
		strcpy((*vegp)->components, components);//查找成功，添加成分信息
		((*temp)->ComponetsCount)++;
	}
}

void LoadPlantInfo(KindLink* head) {	//加载蔬菜种植信息表，将蔬菜种植信息表中的数据加载到链表中，入口参数：链表的表头
	KindLink* temp = head;
	VegLink* vegp;
	PlantLink* planthead;
	PlantLink plantp1, plantp2, plantp3;
	int i = 0, year = 0;
	double area, weight;
	char file[30] = "./data/PlantInformation.csv", ch, vegname[20], kindnum[5];
	FILE* fp = NULL;
	fp = fopen(file, "r");
	while ((ch = fgetc(fp)) != '\n');
	ch = fgetc(fp);
	while (ch != EOF) {

		i = 0;
		while (ch != ',')//读取第一格，不使用
			ch = fgetc(fp);
		ch = fgetc(fp);
		while (ch != ',') {//读取第二格，种类编号
			kindnum[i] = ch;
			ch = fgetc(fp);
			i++;
		}
		kindnum[i] = '\0';
		i = 0;
		ch = fgetc(fp);
		while (ch != ',') {//读取第三格，蔬菜名称
			vegname[i] = ch;
			ch = fgetc(fp);
			i++;
		}
		vegname[i] = '\0';
		fscanf(fp, "%lf,%lf,%d", &area, &weight, &year);
		temp = head;
		while (strcmp(kindnum, (*temp)->kindnum) != 0)//查找蔬菜种类
			temp = &((*temp)->next);
		vegp = &((*temp)->veghead);
		while (((*vegp) != NULL) && (strcmp(vegname, (*vegp)->vegname) != 0)) {//查找蔬菜名
			vegp = &((*vegp)->next);
		}
		if ((*vegp) == NULL) {//查找失败
			printf("%s\t%s\t不存在！", kindnum, vegname);
			continue;
		}
		plantp1 = (PlantLink)malloc(sizeof(PlantNode));
		plantp1->area = area;
		plantp1->weight = weight;
		plantp1->year = year;
		planthead = &((*vegp)->plant);
		plantp2 = (*planthead);
		plantp3 = (*planthead);
		while (plantp3 != NULL && (plantp3->year < year)) {
			plantp2 = plantp3;
			plantp3 = plantp3->next;
		}
		if (plantp2 == plantp3) {
			plantp1->next = plantp2;
			(*vegp)->plant = plantp1;
		}
		else {
			plantp1->next = plantp3;
			plantp2->next = plantp1;
		}

		//plantp1->next = plantp2;
		while ((ch = fgetc(fp)) == '\n');
	}
	fclose(fp);
}

void show(KindLink h) {	//当没有图形界面时用于打印链表结构，入口参数：链表表头
	VegLink vegp;
	PlantLink plantp;
	while (h != NULL) {
		printf("%s\t%s\n", h->kindnum, h->name);
		vegp = h->veghead;
		while (vegp != NULL) {
			printf("%s\t%s\t", vegp->vegname, vegp->components);
			plantp = vegp->plant;
			while (plantp != NULL) {
				printf("%lf\t%lf\t%d\t", plantp->area, plantp->weight, plantp->year);
				plantp = plantp->next;
			}
			printf("\n");
			vegp = vegp->next;
		}
		printf("\n");
		h = h->next;
	}
}

void SearchKind(KindLink head, char *** kind, char **** veg, int * row, int * column, char * KindOption)
{	//搜寻蔬菜种类信息，用于搜寻指定种类的结点，输入参数：链表表头，种类名称数组，蔬菜名称数组，行数，列数，选择的种类
	KindLink temp = head;
	VegLink veghead;
	int i = 0, j = 0;
	*row = 0;
	*column = 0;
	while (temp != NULL) {//求出行数和列数
		if (KindOption != NULL && strcmp(KindOption, "all") != 0 && strcmp(KindOption, temp->kindnum) != 0)
		{
			temp = temp->next;//筛选出所需的种类
			continue;
		}
		(*column)++;//列数加一
		if (temp->VegCount > (*row))
			(*row) = temp->VegCount;//求出最大行数
		temp = temp->next;
	}
	*kind = (char **)malloc(sizeof(char *)*(*column));
	for (i = 0; i < (*column); i++)
	{
		(*kind)[i] = (char *)malloc(sizeof(char) * 20);//动态创建蔬菜种类数组
	}
	(*veg) = (char ***)malloc(sizeof(char **)*(*column));
	for (i = 0; i < (*column); i++)
	{
		(*veg)[i] = (char **)malloc(sizeof(char *)*(*row));
		for (j = 0; j < (*row); j++)
		{
			(*veg)[i][j] = (char *)malloc(sizeof(char) * 20);//动态创建蔬菜名称数组
			strcpy((*veg)[i][j], "\0");//初始化
		}
	}
	temp = head;
	i = 0;
	while (temp != NULL) 
	{
		if (KindOption != NULL && strcmp(KindOption, "all") != 0 && strcmp(KindOption, temp->kindnum) != 0)
		{
			temp = temp->next;//筛选出所需的种类
			continue;
		}
		j = 0;
		veghead = temp->veghead;
		strcpy((*kind)[i], temp->name);//设置种类名
		strcat((*kind)[i], "(");
		strcat((*kind)[i], temp->kindnum);
		strcat((*kind)[i], ")");
		while (veghead != NULL)
		{
			strcpy((*veg)[i][j], veghead->vegname);//设置蔬菜名
			veghead = veghead->next;
			j++;
		}
		temp = temp->next;
		i++;
	}
}

void SearchInfo(KindLink head, char *** veg, char *** kindnum,char *** components, int * row, char * KindOption, char * ComponentsOption)
{	//搜寻蔬菜基本信息，用于搜寻满足种类和营养成分删选要求的蔬菜基本信息，入口参数：链表表头，蔬菜名数组，种类编号数组，蔬菜成分数组，行数，列数，选择种类，选择成分
	int i = 0;
	KindLink temp = head;
	VegLink veghead;
	(*row) = 0;
	while (temp != NULL)
	{
		if (KindOption != NULL && strcmp(KindOption, "all") != 0 && strcmp(KindOption, temp->kindnum) != 0)
		{
			temp = temp->next;//筛选出所需的种类
			continue;
		}
		veghead = temp->veghead;
		while (veghead != NULL) {
			if ((strcmp(ComponentsOption, "all") == 0 && strlen(veghead->components) != 0) || strstr(veghead->components, ComponentsOption) != NULL) {
				(*row)++;
			}
			veghead = veghead->next;
		}
		temp = temp->next;
	}
	temp = head;
	*veg = (char **)malloc(sizeof(char *)*(*row));
	*kindnum = (char **)malloc(sizeof(char *)*(*row));
	*components = (char **)malloc(sizeof(char *)*(*row));
	for (i = 0; i < (*row); i++)
	{
		(*veg)[i] = (char *)malloc(sizeof(char) * 20);//动态创建蔬菜种类数组
		(*kindnum)[i] = (char *)malloc(sizeof(char) * 5);//动态创建蔬菜种类数组
		(*components)[i] = (char *)malloc(sizeof(char) * 60);//动态创建蔬菜种类数组
	}
	i = 0;
	while (temp != NULL)
	{
		if (KindOption != NULL && strcmp(KindOption, "all") != 0 && strcmp(KindOption, temp->kindnum) != 0)
		{
			temp = temp->next;//筛选所需的种类
			continue;
		}
		veghead = temp->veghead;
		while (veghead != NULL) {
			if ((strcmp(ComponentsOption, "all") == 0 && strlen(veghead->components) != 0) || strstr(veghead->components, ComponentsOption) != NULL) {
				strcpy((*veg)[i], veghead->vegname);	//蔬菜名
				strcpy((*kindnum)[i], temp->kindnum);	//种类名
				strcpy((*components)[i], veghead->components);	//成分
				i++;
			}
			veghead = veghead->next;
		}
		temp = temp->next;
	}
}

void SearchOutPut(KindLink head, char *** kindnum, char *** veg, char *** area, char *** weight, char *** year, int * row, char * KindOption, char * YearOption, char * AreaMin, char * AreaMax, char * WeightMin, char * WeightMax)
{//搜寻种植信息，用于获得满足指定种类、年份以及种植重量和种植面积范围的种植信息，入口参数：链表表头，种类编号数组，蔬菜名称数组，种植面积数组，收获重量数组，年份数组，行数，列数，种类选择，年份选择，面积最小值，面积最大值，重量最小值，重量最大值
	int i = 0, AreaFlag = 0, WeightFlag = 0;
	double AMI = 0, AMA = 0, WMI = 0, WMA = 0;
	if (strlen(AreaMax) != 0 && strlen(AreaMin) != 0) {
		AMI = atof(AreaMin), AMA = atof(AreaMax);
		AreaFlag = 1;
	}
	if (strlen(WeightMin) != 0 && strlen(WeightMax) != 0) {
		WMI = atof(WeightMin), WMA = atof(WeightMax);
		WeightFlag = 1;
	}
	(*row) = 0;
	KindLink temp = head;
	VegLink veghead;
	PlantLink plant;
	char temp_char[10];
	while (temp != NULL) {//第一次遍历，求出行数
		if (KindOption != NULL && strcmp(KindOption, "all") != 0 && strcmp(KindOption, temp->kindnum) != 0)
		{
			temp = temp->next;//筛选出所需的种类
			continue;
		}
		veghead = temp->veghead;
		while (veghead != NULL) {
			plant = veghead->plant;
			while (plant != NULL)
			{
				if ((strcmp(YearOption, "all") == 0 || atoi(YearOption) == plant->year) && (AreaFlag == 0 || (AreaFlag == 1 && plant->area >= AMI && plant->area <= AMA)) && (WeightFlag == 0 || (WeightFlag == 1 && plant->weight >= WMI && plant->weight <= WMA)))
					(*row)++;
				plant = plant->next;
			}
			veghead = veghead->next;
		}
		temp = temp->next;
	}
	*kindnum = (char **)malloc(sizeof(char *)*(*row));
	*veg = (char **)malloc(sizeof(char *)*(*row));
	*area = (char **)malloc(sizeof(char *)*(*row));
	*weight = (char **)malloc(sizeof(char *)*(*row));
	*year = (char **)malloc(sizeof(char *)*(*row));
	for (i = 0; i < (*row); i++)
	{
		(*veg)[i] = (char *)malloc(sizeof(char) * 20);//动态创建蔬菜种类数组
		(*kindnum)[i] = (char *)malloc(sizeof(char) * 5);//动态创建蔬菜种类数组
		(*area)[i] = (char *)malloc(sizeof(char) * 10);//动态创建面积数组
		(*weight)[i] = (char *)malloc(sizeof(char) * 10);//动态创建重量数组
		(*year)[i] = (char *)malloc(sizeof(char) * 10);//动态创建年份数组
	}
	temp = head;
	i = 0;
	while (temp != NULL) {//第二次遍历，给字符串赋值
		if (KindOption != NULL && strcmp(KindOption, "all") != 0 && strcmp(KindOption, temp->kindnum) != 0)
		{
			temp = temp->next;//筛选出所需的种类
			continue;
		}
		veghead = temp->veghead;
		while (veghead != NULL) {
			plant = veghead->plant;
			while (plant != NULL)
			{
				if ((strcmp(YearOption, "all") == 0 || atoi(YearOption) == plant->year) && (AreaFlag == 0 || (AreaFlag == 1 && plant->area >= AMI && plant->area <= AMA)) && (WeightFlag == 0 || (WeightFlag == 1 && plant->weight >= WMI && plant->weight <= WMA)))
				{
					strcpy((*veg)[i], veghead->vegname);
					strcpy((*kindnum)[i], temp->kindnum);
					sprintf(temp_char, "%f", plant->area);
					strcpy((*area)[i], temp_char);
					sprintf(temp_char, "%f", plant->weight);
					strcpy((*weight)[i], temp_char);
					sprintf(temp_char, "%d", plant->year);
					strcpy((*year)[i], temp_char);
					i++;
				}
				plant = plant->next;
			}
			veghead = veghead->next;
		}
		temp = temp->next;
	}
}

void KindDelVeg(KindLink* head, char * veg)	//删除蔬菜记录，入口参数：链表表头，蔬菜名称
{
	int find = 0;
	KindLink temp = *head;
	VegLink veghead1, veghead2;
	while (temp != NULL)
	{
		veghead1 = temp->veghead;	//使用两个指针访问链表
		veghead2 = NULL;
		while (veghead1 != NULL) {
			if (strcmp(veghead1->vegname, veg) == 0)
			{
				if (strlen(veghead1->components) != 0)	//如果删除的蔬菜有成分记录，则成分记录减一
					temp->ComponetsCount--;
				if (veghead2 == NULL)
				{
					temp->veghead = veghead1->next;	//删除链表头
					free(veghead1);
				}
				else
				{
					veghead2->next = veghead1->next;	//删除链表中部
					free(veghead1);
				}
				find = 1;	//成功删除
				break;
			}
			veghead2 = veghead1;
			veghead1 = veghead1->next;
		}
		if (find) {
			temp->VegCount -= 1;	//蔬菜数减1
			break;
		}
		temp = temp->next;
	}
}

void KindDelPlant(KindLink* head, char * veg, char * year)	//删除种植记录，入口参数：链表表头，蔬菜名称，种植年份
{
	int find = 0;
	KindLink temp = *head;
	VegLink veghead;
	PlantLink plant1, plant2;
	while (temp != NULL)
	{
		veghead = temp->veghead;	//使用两个指针访问链表
		while (veghead != NULL) {
			if (strcmp(veghead->vegname, veg) == 0)
			{
				if (strlen(veghead->components) != 0)	//如果删除的蔬菜有成分记录，则成分记录减一
					temp->ComponetsCount--;
				plant1 = veghead->plant;
				plant2 = plant1;
				while (plant1 != NULL)
				{
					if (plant1->year == atoi(year))
						break;
					plant2 = plant1;
					plant1 = plant1->next;
				}
				if (plant1 == plant2)
				{
					veghead->plant = plant1->next;
					free(plant1);
				}
				else
				{
					plant2->next = plant1->next;
					free(plant1);
				}
				find = 1;	//成功删除
				break;
			}
			veghead = veghead->next;
		}
		if (find) {
			break;
		}
		temp = temp->next;
	}
}

void VegNameEdit(KindLink* head, char * VegOld, char * VegNew)	//编辑蔬菜名称，入口参数：链表表头，待修改的年份，新年份
{
	int find = 0;
	KindLink temp = *head;
	VegLink veghead;
	while (temp != NULL)
	{
		veghead = temp->veghead;
		while (veghead != NULL)
		{
			if (strcmp(VegOld, veghead->vegname) == 0) {
				strcpy(veghead->vegname, VegNew);
				find = 1;
				break;
			}
			veghead = veghead->next;
		}
		if (find)
			break;
		temp = temp->next;
	}
}

void ComponentsEdit(KindLink* head, char * Veg, char * components)	//编辑蔬菜营养成分，入口参数：链表表头，蔬菜名，成分
{
	int find = 0;
	KindLink temp = *head;
	VegLink veghead;
	while (temp != NULL)
	{
		veghead = temp->veghead;
		while (veghead != NULL)
		{
			if (strcmp(Veg, veghead->vegname) == 0) {
				strcpy(veghead->components, components);
				find = 1;
				break;
			}
			veghead = veghead->next;
		}
		if (find)
			break;
		temp = temp->next;
	}
}

void AreaWeightEdit(KindLink* head, char * Veg,char* year, int mode, char * AreaWeight)
{	//种植面积或收获重量编辑：链表表头，蔬菜名，种植年份，选择模式（0为修改种植面积，1为修改重量），种植面积或收获重量
	int find = 0;
	KindLink temp = *head;
	VegLink veghead;
	PlantLink plant;
	while (temp != NULL)
	{
		veghead = temp->veghead;
		while (veghead != NULL)
		{
			if (strcmp(Veg, veghead->vegname) == 0) {	//找到蔬菜名
				plant = veghead->plant;
				while (plant != NULL) {
					if (plant->year == atoi(year)) {	//找到对应年份
						if (mode == 0)	//根据选择模式来决定是修改面积还是重量
							plant->area = atof(AreaWeight);
						else
							plant->weight = atof(AreaWeight);
						find = 1;
						break;
					}
					plant = plant->next;
				}
				if (find)
					break;
			}
			veghead = veghead->next;
		}
		if (find)
			break;
		temp = temp->next;
	}
}

int YearEdit(KindLink* head, char * Veg, char * YearOld, char * YearNew)
{	//年份编辑，入口参数：链表表头，蔬菜名，修改前的年份，修改后的年份，出口参数：0为修改失败，1为未造成修改，2为修改成功
	int find = 0;
	KindLink temp = *head;
	VegLink veghead;
	PlantLink plant1, plant2, plant3;
	while (temp != NULL)
	{
		veghead = temp->veghead;
		while (veghead != NULL)
		{
			if (strcmp(Veg, veghead->vegname) == 0) {	//找到蔬菜名
				plant1 = veghead->plant;
				plant2 = plant1;
				while (plant1 != NULL) {
					if (plant1->year == atoi(YearOld)) {	//找到对应年份
						if (plant1 == plant2) {	//修改链表头
							veghead->plant = plant1->next;
						}
						else {	//不是表头
							plant2->next = plant1->next;
						}	//删除了节点，然后修改年份，重新按照插入（为了保证顺序）
						plant1->year = atoi(YearNew);
						plant2 = veghead->plant;
						plant3 = plant2;
						while (plant2 != NULL && plant2->year < plant1->year) {	//判断是否有相同的年份
							plant3 = plant2;
							plant2 = plant2->next;
						}
						if (plant2 != NULL && plant2->year == plant1->year) {	//插入已有的年份，报错，恢复修改
							plant1->year = atoi(YearOld);
							find = 2;
						}
						else
							find = 1;
						plant2 = veghead->plant;
						plant3 = plant2;
						while (plant2 != NULL && plant2->year < plant1->year) {	//找到第一个比插入值小的结点
							plant3 = plant2;
							plant2 = plant2->next;
						}
						if (plant2 == plant3) {	//插在表头
							veghead->plant = plant1;
							plant1->next = plant2;
						}
						else
						{	//插在表中
							plant3->next = plant1;
							plant1->next = plant2;
						}
						break;
					}
					plant2 = plant1;
					plant1 = plant1->next;
				}
				if (find)
					break;
			}
			veghead = veghead->next;
		}
		if (find)
			break;
		temp = temp->next;
	}
	return find;
}

int AddVeg(KindLink* head, int column, char * veg)
{	//增加蔬菜结点，入口参数：链表表头，行数，蔬菜名，出口参数： 0添加失败，1添加成功
	int i = 0;
	KindLink temp = *head;
	VegLink veghead;
	for (i = 0; i < column; i++)
	{
		temp = temp->next;
	}
	veghead = temp->veghead;
	while (veghead->next != NULL && strcmp(veghead->vegname,veg) != 0)
		veghead = veghead->next;
	if (veghead->next == NULL) {
		veghead->next = (VegLink)malloc(sizeof(VegNode));	//创建新节点存储蔬菜
		strcpy(veghead->next->components, "\0");
		veghead->next->next = NULL;
		veghead->next->plant = NULL;
		strcpy(veghead->next->vegname, veg);
		temp->VegCount++;
		return 1;
	}
	else
		return 0;	//蔬菜已存在，报错
}

int AddInfo(KindLink* head, char * veg, char * info)
{	//增加蔬菜基本信息，入口参数：链表表头，蔬菜名，蔬菜基本信息，出口参数：返回0则没有找到蔬菜，返回1则该蔬菜已经有了成分信息，返回2则该蔬菜没有成分信息
	int find = 0;
	KindLink temp = *head;
	VegLink veghead;
	while (temp != NULL)
	{
		veghead = temp->veghead;
		while (veghead != NULL) {
			if (strcmp(veghead->vegname, veg) == 0) {
				if (strlen(veghead->components) != 0)	//该蔬菜已经有了成分信息
					find = 1;
				else {
					strcpy(veghead->components, info);	//该蔬菜没有成分信息
					temp->ComponetsCount += 1;
					find = 2;
				}
				break;
			}
			veghead = veghead->next;
		}
		if (find)
			break;
		temp = temp->next;
	}
	return find;	//返回0则没有找到蔬菜，返回1则该蔬菜已经有了成分信息，返回2则该蔬菜没有成分信息
}

int AddPlant(KindLink* head, char * veg, char * area, char * weight, char * year)
{	//增加种植信息结点，入口参数：链表表头，蔬菜名，种植面积，种植重量，种植年份
	int find = 0;
	KindLink temp = *head;
	VegLink veghead;
	PlantLink plant1, plant2;
	while (temp != NULL)
	{
		veghead = temp->veghead;
		while (veghead != NULL)
		{
			if (strcmp(veg, veghead->vegname) == 0) {	//找到蔬菜名
				plant1 = veghead->plant;
				plant2 = plant1;
				while (plant1 != NULL&& plant1->year < atoi(year)) {
					plant2 = plant1;
					plant1 = plant1->next;
				}
				if (plant1 != NULL && plant1->year == atoi(year)) {	//插入已有的年份，报错
					find = 2;
				}
				else {
					find = 1;
					if (plant2 == plant1) {	//插在表头
						veghead->plant = (PlantLink)malloc(sizeof(PlantNode));
						veghead->plant->area = atof(area);
						veghead->plant->weight = atof(weight);
						veghead->plant->year = atoi(year);
						veghead->plant->next = plant1;
					}
					else
					{	//插在表中
						plant2->next = (PlantLink)malloc(sizeof(PlantNode));
						plant2->next->area = atof(area);
						plant2->next->weight = atof(weight);
						plant2->next->year = atoi(year);
						plant2->next->next = plant1;
					}
				}
				if (find)
					break;
			}
			veghead = veghead->next;
		}
		if (find)
			break;
		temp = temp->next;
	}
	return find;
}

void SearchEngines(KindLink head,char * input, char ** text)
{	//搜索函数，链表表头，搜索内容，搜索结果
	int find1 = 0, find2 = 0, YearFind = 0;
	char * p1, *p2;
	p1 = strtok(input, " ");
	p2 = strtok(NULL, " ");
	KindLink temp = head;
	VegLink veghead;
	PlantLink plant;
	*text = (char *)malloc(sizeof(char) * 2000);
	strcpy(*text, "\0");
	char TempChar[60] = "\0";
	while (temp != NULL)
	{
		veghead = temp->veghead;
		while (veghead != NULL)
		{
			plant = veghead->plant;
			find1 = 0;
			find2 = 0;
			YearFind = 0;
			if(p1 == NULL)
				find1 = 1;
			else
			{
				if (strlen(p1) == 1) {
					if (strstr(temp->kindnum, p1) != NULL)
						find1 = 1;
				}
				else {
					if (strstr(temp->name, p1) != NULL || strstr(veghead->components, p1) != NULL || strstr(veghead->vegname, p1) != NULL)
						find1 = 1;
				}
			}
			if (p2 == NULL)
				find2 = 1;
			else
			{
				if (strlen(p2) == 1)
				{
					if (strstr(temp->kindnum, p2) != NULL)
						find2 = 1;
				}
				else {
					if (strstr(temp->name, p2) != NULL || strstr(veghead->components, p2) != NULL || strstr(veghead->vegname, p2) != NULL)
						find2 = 1;
				}
			}
			/*
			if (p1 == NULL||strstr(temp->kindnum, p1) != NULL || strstr(temp->name, p1) != NULL || strstr(veghead->components, p1) != NULL || strstr(veghead->vegname, p1) != NULL)
				find1 = 1;
			if (p2 == NULL || strstr(temp->kindnum, p2) != NULL || strstr(temp->name, p2) != NULL || strstr(veghead->components, p2) != NULL || strstr(veghead->vegname, p2) != NULL)
				find2 = 1;
				*/
			while(plant != NULL)
			{
				sprintf(TempChar, "%d", plant->year);
				if (p1 != NULL)
				{
					if (strlen(p1) == 4 && strstr(TempChar, p1) != NULL)
					{
						YearFind = 1;
					}
				}
				if (p2 != NULL)
				{
					if (strlen(p2) == 4 && strstr(TempChar, p2) != NULL)
					{
						YearFind = 1;
					}
				}
				plant = plant->next;
			}
			if ((find1+ find2 + YearFind) >= 2) {
				strcat(*text, temp->kindnum);
				strcat(*text, "-");
				strcat(*text, temp->name);
				strcat(*text, "-");
				strcat(*text, veghead->vegname);
				strcat(*text, "-");
				strcat(*text, veghead->components);
				plant = veghead->plant;
				while (plant != NULL)
				{
					if (YearFind)
					{
						if (p1 != NULL)
						{
							sprintf(TempChar, "%d", plant->year);
							if (strlen(p1) == 4 && strstr(TempChar, p1) != NULL)
							{
								strcat(*text, "-");
								sprintf(TempChar, "%d: 种植面积:%f(亩),收获重量%f(kg)   ", plant->year, plant->area, plant->weight);
								strcat(*text, TempChar);
							}
						}
						if (p2 != NULL)
						{
							sprintf(TempChar, "%d", plant->year);
							if (strlen(p2) == 4 && strstr(TempChar, p2) != NULL)
							{
								strcat(*text, "-");
								sprintf(TempChar, "%d: 种植面积:%f(亩),收获重量%f(kg)   ", plant->year, plant->area, plant->weight);
								strcat(*text, TempChar);
							}
						}
					}
					else {
						strcat(*text, "-");
						sprintf(TempChar, "%d: 种植面积:%f(亩),收获重量%f(kg)   ", plant->year, plant->area, plant->weight);
						strcat(*text, TempChar);
					}
					plant = plant->next;
				}
				strcat(*text, "\n");
			}
			veghead = veghead->next;
		}
		temp = temp->next;
	}
}

double DrawKind(KindLink head, int * KindCount)
{	//统计种类蔬菜数量，入口参数：链表表头，蔬菜数量
	int i = 0, max;
	KindLink temp = head;
	VegLink veghead;
	while (temp != NULL)
	{
		veghead = temp->veghead;
		while (veghead != NULL)
		{
			KindCount[i]++;
			veghead = veghead->next;
		}
		i++;
		temp = temp->next;
	}
	max = KindCount[0];
	for (i = 0; i < 5; i++)
	{
		if (KindCount[i] > max)
			max = KindCount[i];
	}
	return (double)max;
}

double DrawArea(KindLink head, char *** KindName, double * count, char* MinYear, char* MaxYear)
{	//统计种类种植面积，入口参数：链表表头，蔬菜种类名称，统计数量，年份范围（最小年份，最大年份），出口参数：统计数量最大值
	KindLink temp = head;
	VegLink veghead;
	PlantLink plant;
	int i = 0, j;
	double TempCount;
	char TempName[20];
	int min = atoi(MinYear), max = atoi(MaxYear);
	*KindName = (char **)malloc(sizeof(char *)*(5));
	for (i = 0; i < 5; i++)
	{
		(*KindName)[i] = (char *)malloc(sizeof(char) * 20);//动态创建蔬菜种类数组
	}
	i = 0;
	while (temp != NULL)
	{
		strcpy((*KindName)[i], temp->name);
		veghead = temp->veghead;
		while (veghead != NULL)
		{
			plant = veghead->plant;
			while (plant != NULL)
			{
				if(plant->year >= min&&plant->year <= max)
					count[i] += plant->area;	//累加重量
				plant = plant->next;
			}
			veghead = veghead->next;
		}
		temp = temp->next;
		i++;
	}
	for (i = 0; i < 4; i++)
	{
		for (j = i + 1; j < 5; j++)
		{
			if (count[i] > count[j])
			{
				TempCount = count[i];
				count[i] = count[j];
				count[j] = TempCount;
				strcpy(TempName, (*KindName)[i]);
				strcpy((*KindName)[i], (*KindName)[j]);
				strcpy((*KindName)[j], TempName);
			}
		}
	}
	return count[4];
}

double DrawWeight(KindLink head, char *** KindName, double * count, char* MinYear, char* MaxYear)
{	//统计种类种植重量，入口参数：链表表头，蔬菜种类名称，统计数量，年份范围（最小年份，最大年份），出口参数：统计数量最大值
	KindLink temp = head;
	VegLink veghead;
	PlantLink plant;
	int i = 0, j;
	double TempCount;
	char TempName[20];
	int min = atoi(MinYear), max = atoi(MaxYear);
	*KindName = (char **)malloc(sizeof(char *)*(5));
	for (i = 0; i < 5; i++)
	{
		(*KindName)[i] = (char *)malloc(sizeof(char) * 20);//动态创建蔬菜种类数组
	}
	i = 0;
	while (temp != NULL)
	{
		strcpy((*KindName)[i], temp->name);
		veghead = temp->veghead;
		while (veghead != NULL)
		{
			plant = veghead->plant;
			while (plant != NULL)
			{
				if (plant->year >= min&&plant->year <= max)
					count[i] += plant->weight;	//累加重量
				plant = plant->next;
			}
			veghead = veghead->next;
		}
		temp = temp->next;
		i++;
	}
	for (i = 0; i < 4; i++)
	{
		for (j = i + 1; j < 5; j++)
		{
			if (count[i] > count[j])
			{
				TempCount = count[i];
				count[i] = count[j];
				count[j] = TempCount;
				strcpy(TempName, (*KindName)[i]);
				strcpy((*KindName)[i], (*KindName)[j]);
				strcpy((*KindName)[j], TempName);
			}
		}
	}
	return count[4];
}

void DrawYear(KindLink head, char * Text, char* MinYear, char* MaxYear)
{	//统计各蔬菜在指定年份内的种植总重量和种植总面积，入口参数:链表表头，保存结果，年份范围（最小年份，最大年份）
	KindLink temp = head;
	VegLink veghead;
	PlantLink plant;
	int i = 0, j, min = atoi(MinYear), max = atoi(MaxYear), row = 0;
	double TempCount;
	char TempName[20], TempChar[60];
	while (temp != NULL)
	{
		veghead = temp->veghead;
		while (veghead != NULL)
		{
			if (veghead->plant != NULL)
				row++;
			veghead = veghead->next;
		}
		temp = temp->next;
	}
	double* WeightCount = (double *)malloc(sizeof(int)* row);	//用于存放蔬菜重量
	double* AreaCount = (double *)malloc(sizeof(int)* row);	//用于存放蔬菜面积
	char **KindName = (char **)malloc(sizeof(char *)*(row));
	for (i = 0; i < 5; i++)
	{
		KindName[i] = (char *)malloc(sizeof(char) * 20);//动态创建蔬菜种类
	}
	char **VegName = (char **)malloc(sizeof(char *)*(row));
	for (i = 0; i < 5; i++)
	{
		VegName[i] = (char *)malloc(sizeof(char) * 20);//动态创建蔬菜名称
	}

	temp = head;
	i = 0;
	while (temp != NULL)
	{
		veghead = temp->veghead;
		while (veghead != NULL)
		{
			if (veghead->plant != NULL)
			{
				strcpy(KindName[i], temp->name);
				strcpy(VegName[i], veghead->vegname);
				plant = veghead->plant;
				WeightCount[i] = 0;
				AreaCount[i] = 0;
				while (plant != NULL)
				{
					if (plant->year >= min && plant->year <= max)
					{
						WeightCount[i] += plant->weight;	//累加重量
						AreaCount[i] += plant->area;	//累加重量
					}
					plant = plant->next;
				}
				i++;
			}
			veghead = veghead->next;
		}
		temp = temp->next;
	}
	//排序
	for (i = 0; i < row-1; i++)
	{
		for (j = i + 1; j < row; j++)
		{
			if (WeightCount[i] > WeightCount[j])	//以重量排序
			{
				TempCount = WeightCount[i];	//交换重量
				WeightCount[i] = WeightCount[j];
				WeightCount[j] = TempCount;

				TempCount = AreaCount[i];	//交换面积
				AreaCount[i] = AreaCount[j];
				AreaCount[j] = TempCount;

				strcpy(TempName, KindName[i]);	//交换种类
				strcpy(KindName[i], KindName[j]);
				strcpy(KindName[j], TempName);

				strcpy(TempName, VegName[i]);	//交换蔬菜名
				strcpy(VegName[i], VegName[j]);
				strcpy(VegName[j], TempName);
			}
		}
	}

	for (i = 0; i < row; i++)
	{
		strcat(Text, VegName[i]);
		strcat(Text, "-");
		strcat(Text, KindName[i]);
		strcat(Text, "-");
		sprintf(TempChar, "总重量:%f(kg)-总面积:%f(亩)\n", WeightCount[i], AreaCount[i]);
		strcat(Text, TempChar);
	}
}

void SaveYear(KindLink head,char * FileName, char* MinYear, char* MaxYear)
{	//导出各蔬菜在指定年份内的种植总重量和种植总面积的统计结果，输入参数：链表表头，保存文件名，年份范围（最小年份，最大年份）
	KindLink temp = head;
	VegLink veghead;
	PlantLink plant;
	int i = 0, j, min = atoi(MinYear), max = atoi(MaxYear), row = 0;
	double TempCount;
	char TempName[20], TempChar[60];
	while (temp != NULL)
	{
		veghead = temp->veghead;
		while (veghead != NULL)
		{
			if (veghead->plant != NULL)
				row++;
			veghead = veghead->next;
		}
		temp = temp->next;
	}
	double* WeightCount = (double *)malloc(sizeof(int)* row);	//用于存放蔬菜重量
	double* AreaCount = (double *)malloc(sizeof(int)* row);	//用于存放蔬菜面积
	char **KindName = (char **)malloc(sizeof(char *)*(row));
	for (i = 0; i < 5; i++)
	{
		KindName[i] = (char *)malloc(sizeof(char) * 20);//动态创建蔬菜种类
	}
	char **VegName = (char **)malloc(sizeof(char *)*(row));
	for (i = 0; i < 5; i++)
	{
		VegName[i] = (char *)malloc(sizeof(char) * 20);//动态创建蔬菜名称
	}

	temp = head;
	i = 0;
	while (temp != NULL)
	{
		veghead = temp->veghead;
		while (veghead != NULL)
		{
			if (veghead->plant != NULL)
			{
				strcpy(KindName[i], temp->name);
				strcpy(VegName[i], veghead->vegname);
				plant = veghead->plant;
				WeightCount[i] = 0;
				AreaCount[i] = 0;
				while (plant != NULL)
				{
					if (plant->year >= min && plant->year <= max)
					{
						WeightCount[i] += plant->weight;	//累加重量
						AreaCount[i] += plant->area;	//累加重量
					}
					plant = plant->next;
				}
				i++;
			}
			veghead = veghead->next;
		}
		temp = temp->next;
	}
	//排序
	for (i = 0; i < row - 1; i++)
	{
		for (j = i + 1; j < row; j++)
		{
			if (WeightCount[i] > WeightCount[j])	//以重量排序
			{
				TempCount = WeightCount[i];	//交换重量
				WeightCount[i] = WeightCount[j];
				WeightCount[j] = TempCount;

				TempCount = AreaCount[i];	//交换面积
				AreaCount[i] = AreaCount[j];
				AreaCount[j] = TempCount;

				strcpy(TempName, KindName[i]);	//交换种类
				strcpy(KindName[i], KindName[j]);
				strcpy(KindName[j], TempName);

				strcpy(TempName, VegName[i]);	//交换蔬菜名
				strcpy(VegName[i], VegName[j]);
				strcpy(VegName[j], TempName);
			}
		}
	}
	FILE * fp = NULL;
	fp = fopen(FileName, "w");
	fprintf(fp, "蔬菜名,种类名,总重量,总面积\n");
	for (i = 0; i < row; i++)
	{
		fprintf(fp, "%s,%s,%f,%f\n", VegName[i], KindName[i], WeightCount[i], AreaCount[i]);
	}
	fclose(fp);
}
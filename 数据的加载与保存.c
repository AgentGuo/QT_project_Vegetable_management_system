#include "head.h"
#include<string.h>
#include<stdlib.h>
KindLink init_Kindlist() {	//��ʼ��һ����ͷ��㣬�������շ���һ����ͷ���
	KindLink head = NULL;
	return head;
}

void write(KindLink head)	//�ļ����溯�������ڱ��浱ǰ�߲��������Ϣ���´�ϵͳ��������ֱ�Ӽ��أ���ڲ������߲˵���������
{
	int row = 0, i = 0, j = 0, InfoCount = 1, PlantCount = 1;
	char *** veg;
	FILE* KindFp = NULL;
	FILE* InfoFp = NULL;
	FILE* PlantFp = NULL;
	KindFp = fopen("./data/KindInformation.csv", "w");
	PlantFp = fopen("./data/PlantInformation.csv", "w");
	InfoFp = fopen("./data/VegInformation.csv", "w");
	fprintf(KindFp, "������,1,2,3,4,5\n");
	fprintf(KindFp, "��������,������,������,����,Ҷ����,����\n�߲�����");
	fprintf(InfoFp, "�߲˱��,�߲�����,������,Ӫ���ɷ�\n");
	fprintf(PlantFp, "���,�߲˱��,�߲�����,��ֲ���,�ջ�����,��ֲ���\n");
	KindLink temp = head;
	VegLink veghead;
	PlantLink plant;
	while (temp != NULL) {//�������������
		if (temp->VegCount > row)
			row = temp->VegCount;//����������
		temp = temp->next;
	}
	veg = (char ***)malloc(sizeof(char **)*5);
	for (i = 0; i < 5; i++)
	{
		veg[i] = (char **)malloc(sizeof(char *)*row);
		for (j = 0; j < row; j++)
		{
			veg[i][j] = (char *)malloc(sizeof(char) * 20);//��̬�����߲���������
			strcpy(veg[i][j], ",\0");//��ʼ��
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

void LoadKindInfo(KindLink* head)	//����������Ϣ����������Ϣ���е����ݼ��ص������У���ڲ���������ı�ͷ
{
	KindLink* temp = head, kindp;
	VegLink vegp, *veghead;
	char file[30] = "./data/KindInformation.csv", ch = '\0', kindnum[5] = { 0 }, kindname[20] = { 0 }, vegname[20] = { 0 };
	int i = 0;
	FILE* fp = NULL;
	fp = fopen(file, "r");
	while (ch != ',')
		ch = fgetc(fp);//��ȡ���ĵ�һ����Ԫ�񣬲�ʹ��
	while ((ch = fgetc(fp)) != '\n') {//�����һ��
		i = 0;
		while (ch != ','&&ch != '\n') {//��һ��
			kindnum[i] = ch;
			i++;
			ch = fgetc(fp);
		}
		kindnum[i] = '\0';
		kindp = (KindLink)malloc(sizeof(KindNode));//����һ���½ڵ�
		strcpy((kindp)->kindnum, kindnum);
		kindp->next = NULL;
		kindp->veghead = NULL;
		(*temp) = kindp;
		temp = &((*temp)->next);
		//printf("%s", kindnum);
		if (ch == '\n')
			break;
	}
	printf("read kindnum done!\n");//����Ŷ�ȡ���


	temp = head;//���´ӵ�һ���ڵ㿪ʼ
	while (ch != ',')
		ch = fgetc(fp);//��ȡ��ڶ��е�һ����Ԫ�񣬲�ʹ��
	while ((ch = fgetc(fp)) != '\n') {//����ڶ���
		i = 0;
		while (ch != ',' && ch != '\n') {//��һ����Ԫ��
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
	printf("read name done!\n");//����������ƶ�ȡ���

	while (ch != EOF) {//���߲����ƣ�ֱ���ļ�β
		temp = head;
		while (ch != ','&&ch != EOF)//ȥ��ÿһ�п�ͷ
			ch = fgetc(fp);
		if (ch == EOF)
			break;
		while ((ch = fgetc(fp)) != '\n') {//��ȡÿһ�е��߲���
			i = 0;
			while (ch != ',' && ch != '\n') {//��ȡ�߲���
				vegname[i] = ch;
				i++;
				ch = fgetc(fp);
			}
			vegname[i] = '\0';
			if (strlen(vegname) > 0) {//���߲����ǿ�ʱ����ӵ�����
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

void LoadVegInfo(KindLink* head) {	//�����߲˻�����Ϣ�����߲˻�����Ϣ���е����ݼ��ص������У���ڲ���������ı�ͷ
	KindLink* temp = head;
	VegLink* vegp;
	char file[30] = "./data/VegInformation.csv", ch, kindnum[5], vegname[20], components[60];
	int i;
	FILE* fp = NULL;
	fp = fopen(file, "r");
	while ((ch = fgetc(fp)) != '\n')//��ȡ��һ�У���ʹ��
		;
	while ((ch = fgetc(fp)) != EOF) {
		i = 0;
		while (ch != ',')//��ȡ��һ�񣬲�ʹ��
			ch = fgetc(fp);
		ch = fgetc(fp);
		while (ch != ',') {//��ȡ�ڶ����߲�����
			vegname[i] = ch;
			ch = fgetc(fp);
			i++;
		}
		vegname[i] = '\0';
		i = 0;
		ch = fgetc(fp);
		while (ch != ',') {//��ȡ�������߲�����
			kindnum[i] = ch;
			ch = fgetc(fp);
			i++;
		}
		kindnum[i] = '\0';
		i = 0;
		ch = fgetc(fp);
		while (ch != '\n'&&ch != EOF) {//��ȡ���ĸ��߲˳ɷ�
			components[i] = ch;
			ch = fgetc(fp);
			i++;
		}
		components[i] = '\0';
		temp = head;
		while (strcmp(kindnum, (*temp)->kindnum) != 0)//�����߲�����
			temp = &((*temp)->next);
		vegp = &((*temp)->veghead);
		while (((*vegp) != NULL) && (strcmp(vegname, (*vegp)->vegname) != 0)) {//�����߲���
			vegp = &((*vegp)->next);
		}
		if ((*vegp) == NULL) {//����ʧ��
			printf("%s\t%s\t%s\t�����ڣ�", kindnum, vegname, components);
			continue;
		}
		strcpy((*vegp)->components, components);//���ҳɹ�����ӳɷ���Ϣ
		((*temp)->ComponetsCount)++;
	}
}

void LoadPlantInfo(KindLink* head) {	//�����߲���ֲ��Ϣ�����߲���ֲ��Ϣ���е����ݼ��ص������У���ڲ���������ı�ͷ
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
		while (ch != ',')//��ȡ��һ�񣬲�ʹ��
			ch = fgetc(fp);
		ch = fgetc(fp);
		while (ch != ',') {//��ȡ�ڶ���������
			kindnum[i] = ch;
			ch = fgetc(fp);
			i++;
		}
		kindnum[i] = '\0';
		i = 0;
		ch = fgetc(fp);
		while (ch != ',') {//��ȡ�������߲�����
			vegname[i] = ch;
			ch = fgetc(fp);
			i++;
		}
		vegname[i] = '\0';
		fscanf(fp, "%lf,%lf,%d", &area, &weight, &year);
		temp = head;
		while (strcmp(kindnum, (*temp)->kindnum) != 0)//�����߲�����
			temp = &((*temp)->next);
		vegp = &((*temp)->veghead);
		while (((*vegp) != NULL) && (strcmp(vegname, (*vegp)->vegname) != 0)) {//�����߲���
			vegp = &((*vegp)->next);
		}
		if ((*vegp) == NULL) {//����ʧ��
			printf("%s\t%s\t�����ڣ�", kindnum, vegname);
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

void show(KindLink h) {	//��û��ͼ�ν���ʱ���ڴ�ӡ����ṹ����ڲ����������ͷ
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
{	//��Ѱ�߲�������Ϣ��������Ѱָ������Ľ�㣬��������������ͷ�������������飬�߲��������飬������������ѡ�������
	KindLink temp = head;
	VegLink veghead;
	int i = 0, j = 0;
	*row = 0;
	*column = 0;
	while (temp != NULL) {//�������������
		if (KindOption != NULL && strcmp(KindOption, "all") != 0 && strcmp(KindOption, temp->kindnum) != 0)
		{
			temp = temp->next;//ɸѡ�����������
			continue;
		}
		(*column)++;//������һ
		if (temp->VegCount > (*row))
			(*row) = temp->VegCount;//����������
		temp = temp->next;
	}
	*kind = (char **)malloc(sizeof(char *)*(*column));
	for (i = 0; i < (*column); i++)
	{
		(*kind)[i] = (char *)malloc(sizeof(char) * 20);//��̬�����߲���������
	}
	(*veg) = (char ***)malloc(sizeof(char **)*(*column));
	for (i = 0; i < (*column); i++)
	{
		(*veg)[i] = (char **)malloc(sizeof(char *)*(*row));
		for (j = 0; j < (*row); j++)
		{
			(*veg)[i][j] = (char *)malloc(sizeof(char) * 20);//��̬�����߲���������
			strcpy((*veg)[i][j], "\0");//��ʼ��
		}
	}
	temp = head;
	i = 0;
	while (temp != NULL) 
	{
		if (KindOption != NULL && strcmp(KindOption, "all") != 0 && strcmp(KindOption, temp->kindnum) != 0)
		{
			temp = temp->next;//ɸѡ�����������
			continue;
		}
		j = 0;
		veghead = temp->veghead;
		strcpy((*kind)[i], temp->name);//����������
		strcat((*kind)[i], "(");
		strcat((*kind)[i], temp->kindnum);
		strcat((*kind)[i], ")");
		while (veghead != NULL)
		{
			strcpy((*veg)[i][j], veghead->vegname);//�����߲���
			veghead = veghead->next;
			j++;
		}
		temp = temp->next;
		i++;
	}
}

void SearchInfo(KindLink head, char *** veg, char *** kindnum,char *** components, int * row, char * KindOption, char * ComponentsOption)
{	//��Ѱ�߲˻�����Ϣ��������Ѱ���������Ӫ���ɷ�ɾѡҪ����߲˻�����Ϣ����ڲ����������ͷ���߲������飬���������飬�߲˳ɷ����飬������������ѡ�����࣬ѡ��ɷ�
	int i = 0;
	KindLink temp = head;
	VegLink veghead;
	(*row) = 0;
	while (temp != NULL)
	{
		if (KindOption != NULL && strcmp(KindOption, "all") != 0 && strcmp(KindOption, temp->kindnum) != 0)
		{
			temp = temp->next;//ɸѡ�����������
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
		(*veg)[i] = (char *)malloc(sizeof(char) * 20);//��̬�����߲���������
		(*kindnum)[i] = (char *)malloc(sizeof(char) * 5);//��̬�����߲���������
		(*components)[i] = (char *)malloc(sizeof(char) * 60);//��̬�����߲���������
	}
	i = 0;
	while (temp != NULL)
	{
		if (KindOption != NULL && strcmp(KindOption, "all") != 0 && strcmp(KindOption, temp->kindnum) != 0)
		{
			temp = temp->next;//ɸѡ���������
			continue;
		}
		veghead = temp->veghead;
		while (veghead != NULL) {
			if ((strcmp(ComponentsOption, "all") == 0 && strlen(veghead->components) != 0) || strstr(veghead->components, ComponentsOption) != NULL) {
				strcpy((*veg)[i], veghead->vegname);	//�߲���
				strcpy((*kindnum)[i], temp->kindnum);	//������
				strcpy((*components)[i], veghead->components);	//�ɷ�
				i++;
			}
			veghead = veghead->next;
		}
		temp = temp->next;
	}
}

void SearchOutPut(KindLink head, char *** kindnum, char *** veg, char *** area, char *** weight, char *** year, int * row, char * KindOption, char * YearOption, char * AreaMin, char * AreaMax, char * WeightMin, char * WeightMax)
{//��Ѱ��ֲ��Ϣ�����ڻ������ָ�����ࡢ����Լ���ֲ��������ֲ�����Χ����ֲ��Ϣ����ڲ����������ͷ�����������飬�߲��������飬��ֲ������飬�ջ��������飬������飬����������������ѡ�����ѡ�������Сֵ��������ֵ��������Сֵ���������ֵ
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
	while (temp != NULL) {//��һ�α������������
		if (KindOption != NULL && strcmp(KindOption, "all") != 0 && strcmp(KindOption, temp->kindnum) != 0)
		{
			temp = temp->next;//ɸѡ�����������
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
		(*veg)[i] = (char *)malloc(sizeof(char) * 20);//��̬�����߲���������
		(*kindnum)[i] = (char *)malloc(sizeof(char) * 5);//��̬�����߲���������
		(*area)[i] = (char *)malloc(sizeof(char) * 10);//��̬�����������
		(*weight)[i] = (char *)malloc(sizeof(char) * 10);//��̬������������
		(*year)[i] = (char *)malloc(sizeof(char) * 10);//��̬�����������
	}
	temp = head;
	i = 0;
	while (temp != NULL) {//�ڶ��α��������ַ�����ֵ
		if (KindOption != NULL && strcmp(KindOption, "all") != 0 && strcmp(KindOption, temp->kindnum) != 0)
		{
			temp = temp->next;//ɸѡ�����������
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

void KindDelVeg(KindLink* head, char * veg)	//ɾ���߲˼�¼����ڲ����������ͷ���߲�����
{
	int find = 0;
	KindLink temp = *head;
	VegLink veghead1, veghead2;
	while (temp != NULL)
	{
		veghead1 = temp->veghead;	//ʹ������ָ���������
		veghead2 = NULL;
		while (veghead1 != NULL) {
			if (strcmp(veghead1->vegname, veg) == 0)
			{
				if (strlen(veghead1->components) != 0)	//���ɾ�����߲��гɷּ�¼����ɷּ�¼��һ
					temp->ComponetsCount--;
				if (veghead2 == NULL)
				{
					temp->veghead = veghead1->next;	//ɾ������ͷ
					free(veghead1);
				}
				else
				{
					veghead2->next = veghead1->next;	//ɾ�������в�
					free(veghead1);
				}
				find = 1;	//�ɹ�ɾ��
				break;
			}
			veghead2 = veghead1;
			veghead1 = veghead1->next;
		}
		if (find) {
			temp->VegCount -= 1;	//�߲�����1
			break;
		}
		temp = temp->next;
	}
}

void KindDelPlant(KindLink* head, char * veg, char * year)	//ɾ����ֲ��¼����ڲ����������ͷ���߲����ƣ���ֲ���
{
	int find = 0;
	KindLink temp = *head;
	VegLink veghead;
	PlantLink plant1, plant2;
	while (temp != NULL)
	{
		veghead = temp->veghead;	//ʹ������ָ���������
		while (veghead != NULL) {
			if (strcmp(veghead->vegname, veg) == 0)
			{
				if (strlen(veghead->components) != 0)	//���ɾ�����߲��гɷּ�¼����ɷּ�¼��һ
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
				find = 1;	//�ɹ�ɾ��
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

void VegNameEdit(KindLink* head, char * VegOld, char * VegNew)	//�༭�߲����ƣ���ڲ����������ͷ�����޸ĵ���ݣ������
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

void ComponentsEdit(KindLink* head, char * Veg, char * components)	//�༭�߲�Ӫ���ɷ֣���ڲ����������ͷ���߲������ɷ�
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
{	//��ֲ������ջ������༭�������ͷ���߲�������ֲ��ݣ�ѡ��ģʽ��0Ϊ�޸���ֲ�����1Ϊ�޸�����������ֲ������ջ�����
	int find = 0;
	KindLink temp = *head;
	VegLink veghead;
	PlantLink plant;
	while (temp != NULL)
	{
		veghead = temp->veghead;
		while (veghead != NULL)
		{
			if (strcmp(Veg, veghead->vegname) == 0) {	//�ҵ��߲���
				plant = veghead->plant;
				while (plant != NULL) {
					if (plant->year == atoi(year)) {	//�ҵ���Ӧ���
						if (mode == 0)	//����ѡ��ģʽ���������޸������������
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
{	//��ݱ༭����ڲ����������ͷ���߲������޸�ǰ����ݣ��޸ĺ����ݣ����ڲ�����0Ϊ�޸�ʧ�ܣ�1Ϊδ����޸ģ�2Ϊ�޸ĳɹ�
	int find = 0;
	KindLink temp = *head;
	VegLink veghead;
	PlantLink plant1, plant2, plant3;
	while (temp != NULL)
	{
		veghead = temp->veghead;
		while (veghead != NULL)
		{
			if (strcmp(Veg, veghead->vegname) == 0) {	//�ҵ��߲���
				plant1 = veghead->plant;
				plant2 = plant1;
				while (plant1 != NULL) {
					if (plant1->year == atoi(YearOld)) {	//�ҵ���Ӧ���
						if (plant1 == plant2) {	//�޸�����ͷ
							veghead->plant = plant1->next;
						}
						else {	//���Ǳ�ͷ
							plant2->next = plant1->next;
						}	//ɾ���˽ڵ㣬Ȼ���޸���ݣ����°��ղ��루Ϊ�˱�֤˳��
						plant1->year = atoi(YearNew);
						plant2 = veghead->plant;
						plant3 = plant2;
						while (plant2 != NULL && plant2->year < plant1->year) {	//�ж��Ƿ�����ͬ�����
							plant3 = plant2;
							plant2 = plant2->next;
						}
						if (plant2 != NULL && plant2->year == plant1->year) {	//�������е���ݣ������ָ��޸�
							plant1->year = atoi(YearOld);
							find = 2;
						}
						else
							find = 1;
						plant2 = veghead->plant;
						plant3 = plant2;
						while (plant2 != NULL && plant2->year < plant1->year) {	//�ҵ���һ���Ȳ���ֵС�Ľ��
							plant3 = plant2;
							plant2 = plant2->next;
						}
						if (plant2 == plant3) {	//���ڱ�ͷ
							veghead->plant = plant1;
							plant1->next = plant2;
						}
						else
						{	//���ڱ���
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
{	//�����߲˽�㣬��ڲ����������ͷ���������߲��������ڲ����� 0���ʧ�ܣ�1��ӳɹ�
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
		veghead->next = (VegLink)malloc(sizeof(VegNode));	//�����½ڵ�洢�߲�
		strcpy(veghead->next->components, "\0");
		veghead->next->next = NULL;
		veghead->next->plant = NULL;
		strcpy(veghead->next->vegname, veg);
		temp->VegCount++;
		return 1;
	}
	else
		return 0;	//�߲��Ѵ��ڣ�����
}

int AddInfo(KindLink* head, char * veg, char * info)
{	//�����߲˻�����Ϣ����ڲ����������ͷ���߲������߲˻�����Ϣ�����ڲ���������0��û���ҵ��߲ˣ�����1����߲��Ѿ����˳ɷ���Ϣ������2����߲�û�гɷ���Ϣ
	int find = 0;
	KindLink temp = *head;
	VegLink veghead;
	while (temp != NULL)
	{
		veghead = temp->veghead;
		while (veghead != NULL) {
			if (strcmp(veghead->vegname, veg) == 0) {
				if (strlen(veghead->components) != 0)	//���߲��Ѿ����˳ɷ���Ϣ
					find = 1;
				else {
					strcpy(veghead->components, info);	//���߲�û�гɷ���Ϣ
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
	return find;	//����0��û���ҵ��߲ˣ�����1����߲��Ѿ����˳ɷ���Ϣ������2����߲�û�гɷ���Ϣ
}

int AddPlant(KindLink* head, char * veg, char * area, char * weight, char * year)
{	//������ֲ��Ϣ��㣬��ڲ����������ͷ���߲�������ֲ�������ֲ��������ֲ���
	int find = 0;
	KindLink temp = *head;
	VegLink veghead;
	PlantLink plant1, plant2;
	while (temp != NULL)
	{
		veghead = temp->veghead;
		while (veghead != NULL)
		{
			if (strcmp(veg, veghead->vegname) == 0) {	//�ҵ��߲���
				plant1 = veghead->plant;
				plant2 = plant1;
				while (plant1 != NULL&& plant1->year < atoi(year)) {
					plant2 = plant1;
					plant1 = plant1->next;
				}
				if (plant1 != NULL && plant1->year == atoi(year)) {	//�������е���ݣ�����
					find = 2;
				}
				else {
					find = 1;
					if (plant2 == plant1) {	//���ڱ�ͷ
						veghead->plant = (PlantLink)malloc(sizeof(PlantNode));
						veghead->plant->area = atof(area);
						veghead->plant->weight = atof(weight);
						veghead->plant->year = atoi(year);
						veghead->plant->next = plant1;
					}
					else
					{	//���ڱ���
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
{	//���������������ͷ���������ݣ��������
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
								sprintf(TempChar, "%d: ��ֲ���:%f(Ķ),�ջ�����%f(kg)   ", plant->year, plant->area, plant->weight);
								strcat(*text, TempChar);
							}
						}
						if (p2 != NULL)
						{
							sprintf(TempChar, "%d", plant->year);
							if (strlen(p2) == 4 && strstr(TempChar, p2) != NULL)
							{
								strcat(*text, "-");
								sprintf(TempChar, "%d: ��ֲ���:%f(Ķ),�ջ�����%f(kg)   ", plant->year, plant->area, plant->weight);
								strcat(*text, TempChar);
							}
						}
					}
					else {
						strcat(*text, "-");
						sprintf(TempChar, "%d: ��ֲ���:%f(Ķ),�ջ�����%f(kg)   ", plant->year, plant->area, plant->weight);
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
{	//ͳ�������߲���������ڲ����������ͷ���߲�����
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
{	//ͳ��������ֲ�������ڲ����������ͷ���߲��������ƣ�ͳ����������ݷ�Χ����С��ݣ������ݣ������ڲ�����ͳ���������ֵ
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
		(*KindName)[i] = (char *)malloc(sizeof(char) * 20);//��̬�����߲���������
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
					count[i] += plant->area;	//�ۼ�����
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
{	//ͳ��������ֲ��������ڲ����������ͷ���߲��������ƣ�ͳ����������ݷ�Χ����С��ݣ������ݣ������ڲ�����ͳ���������ֵ
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
		(*KindName)[i] = (char *)malloc(sizeof(char) * 20);//��̬�����߲���������
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
					count[i] += plant->weight;	//�ۼ�����
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
{	//ͳ�Ƹ��߲���ָ������ڵ���ֲ����������ֲ���������ڲ���:�����ͷ������������ݷ�Χ����С��ݣ������ݣ�
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
	double* WeightCount = (double *)malloc(sizeof(int)* row);	//���ڴ���߲�����
	double* AreaCount = (double *)malloc(sizeof(int)* row);	//���ڴ���߲����
	char **KindName = (char **)malloc(sizeof(char *)*(row));
	for (i = 0; i < 5; i++)
	{
		KindName[i] = (char *)malloc(sizeof(char) * 20);//��̬�����߲�����
	}
	char **VegName = (char **)malloc(sizeof(char *)*(row));
	for (i = 0; i < 5; i++)
	{
		VegName[i] = (char *)malloc(sizeof(char) * 20);//��̬�����߲�����
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
						WeightCount[i] += plant->weight;	//�ۼ�����
						AreaCount[i] += plant->area;	//�ۼ�����
					}
					plant = plant->next;
				}
				i++;
			}
			veghead = veghead->next;
		}
		temp = temp->next;
	}
	//����
	for (i = 0; i < row-1; i++)
	{
		for (j = i + 1; j < row; j++)
		{
			if (WeightCount[i] > WeightCount[j])	//����������
			{
				TempCount = WeightCount[i];	//��������
				WeightCount[i] = WeightCount[j];
				WeightCount[j] = TempCount;

				TempCount = AreaCount[i];	//�������
				AreaCount[i] = AreaCount[j];
				AreaCount[j] = TempCount;

				strcpy(TempName, KindName[i]);	//��������
				strcpy(KindName[i], KindName[j]);
				strcpy(KindName[j], TempName);

				strcpy(TempName, VegName[i]);	//�����߲���
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
		sprintf(TempChar, "������:%f(kg)-�����:%f(Ķ)\n", WeightCount[i], AreaCount[i]);
		strcat(Text, TempChar);
	}
}

void SaveYear(KindLink head,char * FileName, char* MinYear, char* MaxYear)
{	//�������߲���ָ������ڵ���ֲ����������ֲ�������ͳ�ƽ������������������ͷ�������ļ�������ݷ�Χ����С��ݣ������ݣ�
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
	double* WeightCount = (double *)malloc(sizeof(int)* row);	//���ڴ���߲�����
	double* AreaCount = (double *)malloc(sizeof(int)* row);	//���ڴ���߲����
	char **KindName = (char **)malloc(sizeof(char *)*(row));
	for (i = 0; i < 5; i++)
	{
		KindName[i] = (char *)malloc(sizeof(char) * 20);//��̬�����߲�����
	}
	char **VegName = (char **)malloc(sizeof(char *)*(row));
	for (i = 0; i < 5; i++)
	{
		VegName[i] = (char *)malloc(sizeof(char) * 20);//��̬�����߲�����
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
						WeightCount[i] += plant->weight;	//�ۼ�����
						AreaCount[i] += plant->area;	//�ۼ�����
					}
					plant = plant->next;
				}
				i++;
			}
			veghead = veghead->next;
		}
		temp = temp->next;
	}
	//����
	for (i = 0; i < row - 1; i++)
	{
		for (j = i + 1; j < row; j++)
		{
			if (WeightCount[i] > WeightCount[j])	//����������
			{
				TempCount = WeightCount[i];	//��������
				WeightCount[i] = WeightCount[j];
				WeightCount[j] = TempCount;

				TempCount = AreaCount[i];	//�������
				AreaCount[i] = AreaCount[j];
				AreaCount[j] = TempCount;

				strcpy(TempName, KindName[i]);	//��������
				strcpy(KindName[i], KindName[j]);
				strcpy(KindName[j], TempName);

				strcpy(TempName, VegName[i]);	//�����߲���
				strcpy(VegName[i], VegName[j]);
				strcpy(VegName[j], TempName);
			}
		}
	}
	FILE * fp = NULL;
	fp = fopen(FileName, "w");
	fprintf(fp, "�߲���,������,������,�����\n");
	for (i = 0; i < row; i++)
	{
		fprintf(fp, "%s,%s,%f,%f\n", VegName[i], KindName[i], WeightCount[i], AreaCount[i]);
	}
	fclose(fp);
}
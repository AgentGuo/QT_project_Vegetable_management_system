#ifdef __cplusplus 
extern "C" {
#endif
#include<stdio.h>
typedef struct Plant {		//һ�����ֲ��Ϣ
	int year;				//��ֲ���
	double area, weight;	//��ֲ������ջ�����
	struct Plant* next;		//��ֲ��Ϣָ��
}PlantNode, * PlantLink;

typedef struct Veg {		//�����߲˵Ľṹ��
	char vegname[20];		//�߲�����
	char components[60];	//�߲˳ɷ�
	PlantLink plant;		//��ֲ��Ϣָ��
	struct Veg* next;		//�߲���Ϣָ��
}VegNode, * VegLink;

typedef struct Kind {		//�߲�����Ľṹ��
	int VegCount;			//���߲���ֲ��Ϣ������
	int ComponetsCount;		//���߲���ϸ��Ϣ������
	char kindnum[5];		//������
	char name[20];			//��������
	VegLink veghead;		//�߲���Ϣָ��
	struct Kind* next;		//�߲�����ָ��
}KindNode, * KindLink;

void write(KindLink head);
KindLink init_Kindlist();
void LoadKindInfo(KindLink* head);
void LoadVegInfo(KindLink* head);
void LoadPlantInfo(KindLink* head);
void show(KindLink h);
void SearchKind(KindLink head, char *** kind, char **** veg, int * row, int * column, char * KindOption);
void SearchInfo(KindLink head, char *** veg, char *** kindnum, char *** components, int * row, char * KindOption, char * ComponentsOption);
void SearchOutPut(KindLink head, char *** kindnum, char *** veg, char *** area, char *** weight, char *** year, int * row, char * KindOption, char * YearOption, char * AreaMin, char * AreaMax, char * WeightMin, char * WeightMax);
void KindDelVeg(KindLink* head, char * veg);
void KindDelPlant(KindLink* head, char * veg, char * year);
void VegNameEdit(KindLink* head, char * VegOld, char * VegNew);
void ComponentsEdit(KindLink* head, char * Veg, char * components);
void AreaWeightEdit(KindLink* head, char * Veg, char* year, int mode, char * AreaWeight);
int YearEdit(KindLink* head, char * Veg, char * YearOld, char * YearNew);
int AddVeg(KindLink* head, int column, char * veg);
int AddInfo(KindLink* head, char * veg, char * info);
int AddPlant(KindLink* head, char * veg, char * area, char * weight, char * year);
void SearchEngines(KindLink head, char * input, char ** text);
double DrawKind(KindLink head, int * KindCount);
double DrawArea(KindLink head, char *** KindName, double * count, char* MinYear, char* MaxYear);
double DrawWeight(KindLink head, char *** KindName, double * count, char* MinYear, char* MaxYear);
void SaveYear(KindLink head, char * FileName, char* MinYear, char* MaxYear);
void DrawYear(KindLink head, char * Text, char* MinYear, char* MaxYear);
#ifdef __cplusplus 
}
#endif
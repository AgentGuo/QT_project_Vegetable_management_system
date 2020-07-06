#ifdef __cplusplus 
extern "C" {
#endif
#include<stdio.h>
typedef struct Plant {		//一年的种植信息
	int year;				//种植年份
	double area, weight;	//种植面积、收获重量
	struct Plant* next;		//种植信息指针
}PlantNode, * PlantLink;

typedef struct Veg {		//单个蔬菜的结构体
	char vegname[20];		//蔬菜名称
	char components[60];	//蔬菜成分
	PlantLink plant;		//种植信息指针
	struct Veg* next;		//蔬菜信息指针
}VegNode, * VegLink;

typedef struct Kind {		//蔬菜种类的结构体
	int VegCount;			//有蔬菜种植信息的数量
	int ComponetsCount;		//有蔬菜详细信息的数量
	char kindnum[5];		//分类编号
	char name[20];			//种类名称
	VegLink veghead;		//蔬菜信息指针
	struct Kind* next;		//蔬菜种类指针
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
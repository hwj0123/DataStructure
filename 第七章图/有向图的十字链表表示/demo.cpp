#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"
#define MAX_VERTEX_NUM 20
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef int Status;
typedef char InfoType;
typedef char VertexType;
//���ڵ�ṹ
typedef struct ArcBox{
	int tailvex,headvex;//�û���β��ͷ�ڵ��ڶ�����е�λ��
	struct ArcBox *hlink,*tlink;//�ֱ�ָ��ͷ��ͬ�ͻ�β��ͬ�Ļ�������
	InfoType *info;
}ArcBox;
//����ṹ
typedef struct VexNode{
	VertexType data;
	ArcBox *firstin,*firstout;///��߱�ͳ��߱�
}VexNode;
//����ͼʮ������
typedef struct{
	VexNode xlist[MAX_VERTEX_NUM];//��ͷ����
	int vexnum,arcnum;//����ͼ�ĵ�ǰ�ڵ����ͻ���
}OLGraph;
/*****************************�㷨ʵ��********************************/
//1��ȷ��v1��v2��G�е�λ��
int LocateVex(OLGraph G, VertexType u){
	int i;
	for (i = 0; i < G.vexnum; i++) {
		if (u == G.xlist[i].data)
			return i;
	}
	return ERROR;
}
//2�����뻡����Ϣ
void Input(InfoType * &info)
{
	info = (InfoType *)malloc(50 * sizeof(InfoType));
	printf("���뻡����Ϣ��");
	gets(info);
}
//3������ͼ��ʮ������洢��ʾ
Status CreateDG(OLGraph &G)
{
	int i, j, k, IncInfo;
	VertexType v1, v2;
	ArcBox *p;
	printf("(�ո�ָ�)��������ͼ�������ͻ��������Ƿ���Ϣ(0/1)��");
	scanf("%d %d %d", &G.vexnum, &G.arcnum, &IncInfo);//IncInfo�����Ƿ�����Ϣ
	getchar();//����\n
	printf("����%d������(�ո�ָ�)��", G.vexnum);
	for (i = 0; i < G.vexnum; i++) {//����ڵ��ʼ��
		scanf("%c", &G.xlist[i].data);
		G.xlist[i].firstin = NULL;
		G.xlist[i].firstout = NULL;
		getchar();
	}
	for (k = 0; k < G.arcnum; k++) {
		printf("����һ�����������յ㣺");
		scanf("%c %c", &v1, &v2);
		getchar();
		i = LocateVex(G, v1);//ȷ��v1,v2�ڶ�����е�λ��
		j = LocateVex(G, v2);
		p = (ArcBox *)malloc(sizeof(ArcBox));//�����߽ڵ�
		if (!p){
			return ERROR;
		}
		(*p).headvex = j;//�Ի��ڵ㸳ֵ
		(*p).tailvex = i;
		(*p).hlink = G.xlist[j].firstin;
		(*p).tlink = G.xlist[i].firstout;
		(*p).info = NULL;
		G.xlist[i].firstout = G.xlist[j].firstin = p;//����뻡�ͳ�����ͷ�Ĳ���
		if (IncInfo){
			Input((*p).info);//�������������Ϣ,�����뻡����Ϣ
		}
	}
	return OK;
}

/****************************����*******************************/

void main(){
	OLGraph G;
    CreateDG(G);

}



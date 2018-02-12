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
//弧节点结构
typedef struct ArcBox{
	int tailvex,headvex;//该弧的尾和头节点在顶点表中的位置
	struct ArcBox *hlink,*tlink;//分别指向弧头相同和弧尾相同的弧的链表
	InfoType *info;
}ArcBox;
//顶点结构
typedef struct VexNode{
	VertexType data;
	ArcBox *firstin,*firstout;///入边表和出边表
}VexNode;
//有向图十字链表
typedef struct{
	VexNode xlist[MAX_VERTEX_NUM];//表头向量
	int vexnum,arcnum;//有向图的当前节点数和弧数
}OLGraph;
/*****************************算法实现********************************/
//1、确定v1和v2在G中的位置
int LocateVex(OLGraph G, VertexType u){
	int i;
	for (i = 0; i < G.vexnum; i++) {
		if (u == G.xlist[i].data)
			return i;
	}
	return ERROR;
}
//2、输入弧的信息
void Input(InfoType * &info)
{
	info = (InfoType *)malloc(50 * sizeof(InfoType));
	printf("输入弧的信息：");
	gets(info);
}
//3、有向图的十字链表存储表示
Status CreateDG(OLGraph &G)
{
	int i, j, k, IncInfo;
	VertexType v1, v2;
	ArcBox *p;
	printf("(空格分割)输入有向图顶点数和弧数及弧是否含信息(0/1)：");
	scanf("%d %d %d", &G.vexnum, &G.arcnum, &IncInfo);//IncInfo代表弧是否含有信息
	getchar();//吸收\n
	printf("输入%d个顶点(空格分隔)：", G.vexnum);
	for (i = 0; i < G.vexnum; i++) {//顶点节点初始化
		scanf("%c", &G.xlist[i].data);
		G.xlist[i].firstin = NULL;
		G.xlist[i].firstout = NULL;
		getchar();
	}
	for (k = 0; k < G.arcnum; k++) {
		printf("输入一条弧的起点的终点：");
		scanf("%c %c", &v1, &v2);
		getchar();
		i = LocateVex(G, v1);//确定v1,v2在顶点表中的位置
		j = LocateVex(G, v2);
		p = (ArcBox *)malloc(sizeof(ArcBox));//建立边节点
		if (!p){
			return ERROR;
		}
		(*p).headvex = j;//对弧节点赋值
		(*p).tailvex = i;
		(*p).hlink = G.xlist[j].firstin;
		(*p).tlink = G.xlist[i].firstout;
		(*p).info = NULL;
		G.xlist[i].firstout = G.xlist[j].firstin = p;//完成入弧和出弧连头的插入
		if (IncInfo){
			Input((*p).info);//若弧含有相关信息,则输入弧的信息
		}
	}
	return OK;
}

/****************************测试*******************************/

void main(){
	OLGraph G;
    CreateDG(G);

}



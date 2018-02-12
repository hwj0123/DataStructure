#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXEDGE 20
#define MAXVEX 20
#define INFINITY 65535

typedef int Status;	/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
//邻接矩阵
typedef struct{
	int arc[MAXVEX][MAXVEX];
	int numVertexes,numEdges;//顶点个数,边个数
}MGraph;
/*******************************************算法实现****************************************/
//1、创建邻接矩阵
void CreateMGraph(MGraph *G){
	int i,j;
	G->numEdges=15;//边
	G->numVertexes=9;//顶点
	for(i=0;i<G->numVertexes;i++){//邻接矩阵的初始化
		for(j=0;j<G->numVertexes;j++){
			if(i==j){
				G->arc[i][j]=0;
			}else{
				G->arc[i][j]=G->arc[i][j]=INFINITY;
			}
		}
	}
	G->arc[0][1]=10;
    G->arc[0][5]=11; 
	G->arc[1][2]=18; 
	G->arc[1][8]=12; 
	G->arc[1][6]=16; 
	G->arc[2][8]=8; 
	G->arc[2][3]=22; 
	G->arc[3][8]=21; 
	G->arc[3][6]=24; 
	G->arc[3][7]=16;
	G->arc[3][4]=20;
	G->arc[4][7]=7; 
	G->arc[4][5]=26; 
	G->arc[5][6]=17; 
	G->arc[6][7]=19;
	for(i=0;i<G->numVertexes;i++){//无向图的邻接矩阵关于对角线对称
		for(j=i;j<G->numVertexes;j++){
			G->arc[j][i]=G->arc[i][j];
		}
	}
}
//2、普利姆算法生成生成树
void MiniSpanTree_PRIM(MGraph G){
	int min,i,j,k;
	//没有使用结构体---->closedge
	int adjvex[MAXVEX];//保存顶点下标
	int lowcost[MAXVEX];//存储在该边上的权
	//lowcost是相关顶点间边的权值
	lowcost[0]=0;//初始化
	adjvex[0]=0;//初始化第一个节点为0
	for(i=1;i<G.numVertexes;i++){
		lowcost[i]=G.arc[0][i];//辅助数组初始化,将与0节点有边的权值全部存储
		adjvex[i]=0;
	}
	for(i=1;i<G.numVertexes;i++){
		min=INFINITY;//初始化最小权值为无穷大
		j=1;
		k=0;
		//循环所有节点找到最小权值(在与0节点相关的节点中)
		while(j<G.numVertexes){
			if(lowcost[j]!=0&&lowcost[j]<min){
				min=lowcost[j];
				k=j;//记录节点下标
			}
			j++;
		}
		printf("(%d,%d)\n",adjvex[k],k);//输出当前顶点边中权值最小的
		lowcost[k]=0;//将当前顶点权值设为0,表明已完成该节点的选择
		for(j=1;j<G.numVertexes;j++){
			//已经是最小生成树的顶点不参与最小权值的对比了
			if(lowcost[j]!=0&&G.arc[k][j]<lowcost[j]){
				//更新辅助数组的值
				lowcost[j]=G.arc[k][j];
				adjvex[j]=k;
			}
		}
	}
}
/********************************************测试********************************************/
void main(){
	MGraph G;
	CreateMGraph(&G);
	MiniSpanTree_PRIM(G);
}









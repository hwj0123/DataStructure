#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXVEX 100 /* 最大顶点数，应由用户定义 */
#define INFINITY 65535

typedef int Status;	/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef char VertexType; /* 顶点类型应由用户定义  */
typedef int EdgeType; /* 边上的权值类型应由用户定义 */

typedef struct{
	VertexType vexs[MAXVEX];//顶点表
	EdgeType arc[MAXVEX][MAXVEX];//邻接矩阵
	int numNodes,numEdges;//图中的顶点数和边数
}MGraph;
/************************实现算法*****************************/
//1、无向图的邻接矩阵表示
void CreateMGraph(MGraph *G){
	int i,j,k,w;
	printf("输入顶点数和边数(如:3,2):\n");
    scanf("%d,%d",&G->numNodes,&G->numEdges);//输入顶点数和边数
	getchar();//吸收换行
	printf("输入%d个顶点信息(如:a b c-->以空格做分割):",G->numNodes);
	for(i=0;i<G->numNodes;i++){
		scanf("%c",&G->vexs[i]);//输入顶点的信息
		getchar();
	}
	for(i=1;i<=G->numNodes;i++){
		for(j=1;j<=G->numNodes;j++){
			G->arc[i][j]=INFINITY;//邻接矩阵初始化
		}
	}
	for(k=0;k<G->numEdges;k++){
		printf("输入边(vi,vj)的下标i,下标j和权w:(如:i,j,w)\n");
		scanf("%d,%d,%d",&i,&j,&w);//
		G->arc[i][j]=w;
		G->arc[j][i]=G->arc[i][j];//无向图的邻接矩阵是对称的
	}
}
//2、打印无向图的邻接矩阵
void printGraph(MGraph G){
	for(int i=1;i<=G.numNodes;i++){
		for(int j=1;j<=G.numNodes;j++){
			printf("%d\t",G.arc[i][j]);
		}
		printf("\n");
	}
}
/**********************测试**********************/
void main(){
	MGraph G;
	CreateMGraph(&G);
	printGraph(G);
}
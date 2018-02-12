#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status;	/* Status是函数的类型,其值是函数结果状态代码，如OK等 */

#define MAXEDGE 20
#define MAXVEX 20
#define INFINITY 65535

typedef struct{
	int arc[MAXVEX][MAXVEX];
	int numVertexes,numEdges;
}MGraph;//邻接矩阵
//边集数组
typedef struct{
	int begin;
	int end;
	int weight;
}Edge;//边结构
/**********************************************实现算法************************************/
//1、无向图的邻接矩阵初始化
void CreateMGraph(MGraph *G){
	int i,j;
	G->numEdges=15;//1边
    G->numVertexes=9;
	//邻接矩阵初始化
	for(i=0;i<G->numVertexes;i++){
		for(j=0;j<G->numVertexes;j++){
			if(i==j){
				G->arc[i][j]=0;
			}else{
				G->arc[i][j]=INFINITY;
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

	for(i=0;i<G->numVertexes;i++){
		for(j=i;j<G->numVertexes;j++){
			G->arc[j][i]=G->arc[i][j];//无向图的邻接矩阵关于对角线对称
		}
	}

}
//2、交换两个边的权值,头和尾
void Swapn(Edge *edges,int i,int j){
    int temp;
	temp = edges[i].begin;
	edges[i].begin = edges[j].begin;
	edges[j].begin = temp;
	temp = edges[i].end;
	edges[i].end = edges[j].end;
	edges[j].end = temp;
	temp = edges[i].weight;
	edges[i].weight = edges[j].weight;
	edges[j].weight = temp;
}
//3、对边按照权值排序
void sort(Edge edges[],MGraph *G){
	int i, j;
	for ( i = 0; i < G->numEdges; i++){
		for ( j = i + 1; j < G->numEdges; j++){
			if (edges[i].weight > edges[j].weight){
				Swapn(edges, i, j);
			}
		}
	}
	printf("权排序之后的为:\n");
	for (i = 0; i < G->numEdges; i++){
		printf("(%d, %d) %d\n", edges[i].begin, edges[i].end, edges[i].weight);
	}

}

//4、查找连线顶点的尾部下标
int Find(int *parent,int f){
	while(parent[f]>0){
		f=parent[f];
	}
	return f;
}
//5、克鲁斯卡尔算法实现
void MiniSpanTree_Kruskal(MGraph G){
	int i,j,n,m;
	int k=0;
	int parent[MAXVEX];//辅助数组,判断边与边是否形成回路
	Edge edges[MAXEDGE];//定义边集数组
	//边数组初始化
	for(i=0;i<G.numVertexes-1;i++){
		for(j=i+1;j<G.numVertexes;j++){
			if(G.arc[i][j]<INFINITY){
				edges[k].begin=i;
				edges[k].end=j;
				edges[k].weight=G.arc[i][j];
				k++;
			}
		}
	}
	//按照权值排序
	sort(edges,&G);

	for(i=0;i<G.numVertexes;i++){
		parent[i]=0;
	}
     
	printf("打印最小生成树\n");
	for(i=0;i<G.numEdges;i++){
		n=Find(parent,edges[i].begin);
		m=Find(parent,edges[i].end);
		 /*说明该边没有与现有的生成树产生回路
		   将这条边的尾节点放入下标为起始节点的中,表明此节点已经在生成树集合中*/
		if(n!=m){
			parent[n]=m;
			printf("(%d,%d)%d\n",edges[i].begin,edges[i].end,edges[i].weight);

		}
	}
}
/***********************************测试*********************************************/
void main(){
	MGraph G;
	CreateMGraph(&G);
	MiniSpanTree_Kruskal(G);
}







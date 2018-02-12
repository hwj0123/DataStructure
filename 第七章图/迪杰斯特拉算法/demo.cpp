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
	int vexs[MAXVEX];
	int arc[MAXVEX][MAXVEX];
	int numVertexes,numEdges;
}MGraph;

typedef int Patharc[MAXVEX];//用于存储最短路径下标的数组
typedef int ShortPathTable[MAXVEX];//用于存储到个点最短路径的权值和

/*************************************算法实现**********************/
//1、创建邻接矩阵
void CreateMGraph(MGraph *G){
	int i,j;
	G->numEdges=16;
	G->numVertexes=9;

	for (i = 0; i < G->numVertexes; i++){
		G->vexs[i]=i;
	}

	for (i = 0; i < G->numVertexes; i++){
		for ( j = 0; j < G->numVertexes; j++){
			if (i==j)
				G->arc[i][j]=0;
			else
				G->arc[i][j] = G->arc[j][i] = INFINITY;
		}
	}

	G->arc[0][1]=1;
	G->arc[0][2]=5; 
	G->arc[1][2]=3; 
	G->arc[1][3]=7; 
	G->arc[1][4]=5; 

	G->arc[2][4]=1; 
	G->arc[2][5]=7; 
	G->arc[3][4]=2; 
	G->arc[3][6]=3; 
	G->arc[4][5]=3;

	G->arc[4][6]=6;
	G->arc[4][7]=9; 
	G->arc[5][7]=5; 
	G->arc[6][7]=2; 
	G->arc[6][8]=7;

	G->arc[7][8]=4;


	for(i = 0; i < G->numVertexes; i++){
		for(j = i; j < G->numVertexes; j++){
			G->arc[j][i] =G->arc[i][j];//对称
		}
	}
}
//2、迪杰斯特拉算法-->求有向网的v0顶点到其它顶点的最短路径
void ShortestPath_Dijkstra(MGraph G,int v0,Patharc *P,ShortPathTable *D){
	int v,w,k,min;
	int final[MAXVEX];//final[x]表示顶点v0到vx的最短路径
	//初始化
	for(v=0;v<G.numVertexes;v++){
		final[v]=0;
		(*D)[v]=G.arc[v0][v];
		(*P)[v]=-1;
	}
	(*D)[v0]=0;//v0到自己为0
	final[v0]=1;//v0到v0不需要求路径
	//循环求得v0到每个节点的最短路径
	for(v=1;v<G.numVertexes;v++){
		min=INFINITY;
		//寻找与v0最近的顶点
		for(w=0;w<G.numVertexes;w++){
			if(!final[w]&&(*D)[w]<min){
				k=w;
				min=(*D)[w];//找到离v0顶点最近的w顶点
			}
		}
		final[k]=1;//目前找到的最近的节点
		//修正当前最短路径及距离
		for(w=0;w<G.numVertexes;w++){
			//经过v节点的路径比现在的路径要更短
			if(!final[w]&&(min+G.arc[k][w]<(*D)[w])){
				//修改当前路径
				(*D)[w]=min=G.arc[k][w];
				(*P)[w]=k;
			}
		}
	}
}
void main(){
	int i,j,v0;
	MGraph G;
	Patharc P;
	ShortPathTable D;
	v0=0;
	CreateMGraph(&G);
	ShortestPath_Dijkstra(G,v0,&P,&D);
	printf("最短路径倒序如下:\n");
	for(i=1;i<G.numVertexes;i++){
		printf("v%d-v%d:",v0,i);
		j=i;
		while(P[j]!=-1){
			printf("%d",P[j]);
			j=P[j];
		}
		printf("\n");
	}
	printf("\n源点到各顶点的最短路径长度为:\n");
	for(i=1;i<G.numVertexes;i++){
		printf("v%d-v%d:%d\n",G.vexs[0],G.vexs[i],D[i]);
	}
}

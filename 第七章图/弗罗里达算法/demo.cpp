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

typedef struct{
	int vexs[MAXVEX];
	int arc[MAXVEX][MAXVEX];
	int numVertexes,numEdges;
}MGraph;

typedef int Patharc[MAXVEX][MAXVEX];//顶点到顶点的最短路径权值
typedef int ShortPathTable[MAXVEX][MAXVEX];//顶点到顶点的最短路径的中转下标
/***********************************算法实现********************************/
//1、创建邻接矩阵
void CreateMGraph(MGraph *G){
	int i,j;
	G->numEdges=16;
	G->numVertexes=9;
	for(i=0;i<G->numVertexes;i++){
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
			G->arc[j][i] =G->arc[i][j];
		}
	}
}
//2、弗罗里达算法
void ShortestPath_Floyd(MGraph G,Patharc *P,ShortPathTable *D){
	int v,w,k;
	//初始化D,P
	for(v=0;v<G.numVertexes;v++){
		for(w=0;w<G.numVertexes;w++){
			(*D)[v][w]=G.arc[v][w];
			(*P)[v][w]=w;
		}
	}
	for(k=0;k<G.numVertexes;k++){
		for(v=0;v<G.numVertexes;v++){
			for(w=0;w<G.numVertexes;w++){
				//从v到w路过k下标的路径比原两点间路径更短
				if((*D)[v][w]>(*D)[v][k]+(*D)[k][w]){
					//更新D,P
					(*D)[v][w]=(*D)[v][k]+(*D)[k][w];
					(*P)[v][w]=(*P)[v][k];
				}
			}
		}
	}
}
/***********************************测试**************************/
void main(){
	int v,w,k;
	MGraph G;
	Patharc P;
	ShortPathTable D;
	CreateMGraph(&G);
	ShortestPath_Floyd(G,&P,&D);
	printf("各顶点间最短路径为:\n");
	for(v=0;v<G.numVertexes;v++){
		for(w=v+1;w<G.numVertexes;w++){
			printf("v%d-v%d weight:%d\t",v,w,D[v][w]);
			k=P[v][w];
			printf("path:%d",v);//路径源点
			while(k!=w){
				printf("->%d",k);//路径中间点
				k=P[k][w];
			}
			printf("->%d\n",w);//路径终点
		}
		printf("\n");
	}
	printf("最短路径矩阵D:\n");
	for(v=0;v<G.numVertexes;v++){
		for(w=0;w<G.numVertexes;w++){
			printf("%d\t",D[v][w]);
		}
		printf("\n");
	}
	printf("最短路径矩阵P:\n");
	for(v=0;v<G.numVertexes;v++){
		for(w=0;w<G.numVertexes;w++){
			printf("%d\t",P[v][w]);
		}
		printf("\n");
	}
}




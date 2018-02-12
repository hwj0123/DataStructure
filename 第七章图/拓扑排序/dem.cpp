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
#define MAXVEX 14
#define INFINITY 65535

typedef int Status;	/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
//邻接矩阵
typedef struct{
	int vexs[MAXVEX];
	int arc[MAXVEX][MAXVEX];
	int numVertexes,numEdges;
}MGraph;
//邻接表
typedef struct EdgeNode{//边表
	int adjvex;//存储该顶点对应下标
	int weight;//权值
	struct EdgeNode *next;
}EdgeNode;
typedef struct VertexNode{//顶点表
	int in;//顶点的入度
	int data;
	EdgeNode *firstedge;//边表
}VertexNode,AdjList[MAXVEX];
typedef struct{
	AdjList adjList;
	int numVertexes,numEdges;
}graphAdjList,*GraphAdjList;

/*******************************************算法实现*******************/
//1、构建一个邻接矩阵
void CreateMGraph(MGraph *G){
	int i,j;
	G->numEdges=MAXEDGE;
	G->numVertexes=MAXVEX;
	//初始化
	for(i=0;i<G->numVertexes;i++){
		G->vexs[i]=i;
	}
	for(i=0;i<G->numVertexes;i++){
		for(j=0;j<G->numVertexes;j++){
			G->arc[i][j]=0;
		}
	}
	G->arc[0][4]=1;
	G->arc[0][5]=1; 
	G->arc[0][11]=1; 
	G->arc[1][2]=1; 
	G->arc[1][4]=1; 
	G->arc[1][8]=1; 
	G->arc[2][5]=1; 
	G->arc[2][6]=1;
	G->arc[2][9]=1;
	G->arc[3][2]=1; 
	G->arc[3][13]=1;
	G->arc[4][7]=1;
	G->arc[5][8]=1;
	G->arc[5][12]=1; 
	G->arc[6][5]=1; 
	G->arc[8][7]=1;
	G->arc[9][10]=1;
	G->arc[9][11]=1;
	G->arc[10][13]=1;
	G->arc[12][9]=1;
}
//2、利用邻接矩阵构建邻接表
void CreateALGraph(MGraph G,GraphAdjList *GL){
	int i,j;
	EdgeNode *e;
	*GL=(GraphAdjList)malloc(sizeof(graphAdjList));
	(*GL)->numVertexes=G.numVertexes;
	(*GL)->numEdges=G.numEdges;
	//初始化邻接表
	for(i=0;i<G.numVertexes;i++){
		(*GL)->adjList[i].in=0;
		(*GL)->adjList[i].data=G.vexs[i];
		(*GL)->adjList[i].firstedge=NULL;
	}
	//建立边表
	for(i=0;i<G.numVertexes;i++){
		for(j=0;j<G.numVertexes;j++){
			if(G.arc[i][j]==1){
				e=(EdgeNode *)malloc(sizeof(EdgeNode));
				e->adjvex=j;                     
				e->next=(*GL)->adjList[i].firstedge;
				(*GL)->adjList[i].firstedge=e;		
				(*GL)->adjList[j].in++;//入度++
			}
		}
	}
}
//3、拓扑排序
Status TopologicalSort(GraphAdjList GL){
       EdgeNode *e;
	   int i,k,gettop;
	   int top=0;//栈指针下标
	   int count=0;//统计输出顶点个数
	   int *stack;//栈指针
	   stack=(int *)malloc(GL->numVertexes*sizeof(int));
	   for(i=0;i<GL->numVertexes;i++){
		   if(0==GL->adjList[i].in){//将入度为0的顶点入栈
			   stack[++top]=i;
		   }
	   }
	   while(top!=0){
		   gettop=stack[top--];
		   printf("%d->",GL->adjList[gettop].data);
		   count++;//计数
		   //遍历以gettop为开始的边表
		   for(e=GL->adjList[gettop].firstedge;e;e=e->next){
			   k=e->adjvex;
			   //将k号顶点的入度减-,如果为0则入栈
			   if(!(--GL->adjList[k].in)){
				   stack[++top]=k;
			   }
		   }
	   }
		   printf("\n");
		   if(count<GL->numVertexes){
			   return ERROR;
		   }else{
			   return OK;
		   }
	   
}
/******************************测试**************************/
void main(){
	MGraph G;
	GraphAdjList GL;
	int result;
	CreateMGraph(&G);
	CreateALGraph(G,&GL);
	result=TopologicalSort(GL);
	printf("result:%d",result);
}




#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXVEX 100 /* 最大顶点数,应由用户定义 */

typedef int Status;	/* Status是函数的类型,其值是函数结果状态代码,如OK等 */
typedef char VertexType; /* 顶点类型应由用户定义 */
typedef int EdgeType; /* 边上的权值类型应由用户定义 */
typedef int Boolean; 
//边表节点结构
typedef struct EdgeNode{
	int adjvex;//存储顶点对应的下标
	EdgeType info;//用于存储与边或弧相关的信息,如权值等
	struct EdgeNode *next;//指示下一条边或弧的节点
}EdgeNode;
//顶点节点结构
typedef struct VertexNode{
	VertexType data;//顶点信息
	EdgeNode *firstedge;//指向第一条依附该顶点的弧的指针
}VertexNode,AdjList[MAXVEX];
//邻接表结构
typedef struct{
	AdjList adjList;//顶点数组
	int numNodes,numEdges;//图的当前顶点数和弧数
}GraphAdjList;
/**************************实现算法******************************/
//1、创建邻接表
void CreateALGraph(GraphAdjList *G){
	int i,j,k;
	EdgeNode *e;
	printf("输入顶点数和边数(如(3,2)):\n");
	scanf("%d,%d",&G->numNodes,&G->numEdges);
	getchar();
	printf("输入%d个顶点的信息:(如a b c)",G->numNodes);  
    for(i = 0;i < G->numNodes;i++){
		scanf("%c",&G->adjList[i].data); 	//输入顶点信息
		G->adjList[i].firstedge=NULL; 	// 将边表置为空表 
		getchar();
	}

	for(k=0;k<G->numEdges;k++){
		printf("输入边(vi,vj)上的顶点序号(注意:以,为分割,节点下标从0开始):\n");
		scanf("%d,%d",&i,&j);
		//完成顶点i,j的边表生成
		e=(EdgeNode*)malloc(sizeof(EdgeNode));
		e->adjvex=j;//存储它在顶点数组中的下标
		e->next=G->adjList[i].firstedge;//让边表头指针指向它
		G->adjList[i].firstedge=e;
        //头插法--->每次都插入到第一个
		e=(EdgeNode*)malloc(sizeof(EdgeNode));
		e->adjvex=i;
		e->next=G->adjList[j].firstedge;
		G->adjList[j].firstedge=e;
	}
}

Boolean visited[MAXVEX]; //访问标志的数组
//2、深度优先搜索
void DFS(GraphAdjList GL, int i){
    EdgeNode *p;
 	visited[i] = TRUE;//访问第i个节点
 	printf("%c\t",GL.adjList[i].data);
	p = GL.adjList[i].firstedge;
	while(p)//访问第i个节点的邻接点
	{
 		if(!visited[p->adjvex])
 			DFS(GL, p->adjvex);//对为访问的邻接顶点递归调用
		p = p->next;
 	}
}
void DFSTraverse(GraphAdjList GL){
     int i;
 	for(i = 0; i < GL.numNodes; i++)
 		visited[i] = FALSE; //初始所有顶点状态都是未访问过状态
	for(i = 0; i < GL.numNodes; i++)
 		if(!visited[i]) //对未访问过的顶点调用DFS,若是连通图,只会执行一次
			DFS(GL, i);
}
/***************************测试***********************/
void main(){
	GraphAdjList G;
	CreateALGraph(&G);
	printf("深度优先搜索:\n");
	DFSTraverse(G);
}



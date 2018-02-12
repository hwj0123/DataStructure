#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 9 /* 存储空间初始分配量 */
#define MAXEDGE 15
#define MAXVEX 9
#define INFINITY 65535

typedef int Status;	/* Status是函数的类型,其值是函数结果状态代码,如OK等 */
typedef int Boolean; /* Boolean是布尔类型,其值是TRUE或FALSE */

typedef char VertexType; /* 顶点类型应由用户定义 */
typedef int EdgeType; /* 边上的权值类型应由用户定义 */
//邻接矩阵的定义
typedef struct
{
	VertexType vexs[MAXVEX]; //顶点表
	EdgeType arc[MAXVEX][MAXVEX];//邻接矩阵,可看作边表
	int numVertexes, numEdges; //图中当前的顶点数和边数 
}MGraph;   
//邻接表的定义
typedef struct EdgeNode //边表结点
{
	int adjvex;    //邻接点域,存储该顶点对应的下标
	int weight;		//用于存储权值,对于非网图可以不需要
	struct EdgeNode *next; //链域,指向下一个邻接点
}EdgeNode;

typedef struct VertexNode //顶点结点  
{
	int in;	//顶点入度
	char data; //顶点信息
	EdgeNode *firstedge;//边表头指针 
}VertexNode, AdjList[MAXVEX];

typedef struct
{
	AdjList adjList;//顶点数组
	int numVertexes,numEdges; //图中顶点数和边数
}graphAdjList,*GraphAdjList;
//循环队列的定义
typedef struct
{
	int data[MAXSIZE];
	int front;    	//头指针
	int rear;		//尾指针
}Queue;

/********************************************循环队列算法********************************/
//1、初始化一个空队列Q
Status InitQueue(Queue *Q)
{
	Q->front=0;
	Q->rear=0;
	return  OK;
}

//2、若队列Q为空队列,则返回TRUE,否则返回FALSE
Status QueueEmpty(Queue Q){ 
	if(Q.front==Q.rear){ //队列空的标志
		return TRUE;
	}else{
		return FALSE;
	}
}

//3、若队列未满,则插入元素e为Q新的队尾元素
Status EnQueue(Queue *Q,int e){
	if ((Q->rear+1)%MAXSIZE == Q->front){//判断是否已满
		return ERROR;
	}
	Q->data[Q->rear]=e;			//将元素e赋值给队尾
	Q->rear=(Q->rear+1)%MAXSIZE;//rear指针+1,若到最后则转到数组头部							
	return  OK;
}

//4、若队列不空,则删除Q中队头元素,用e返回其值
Status DeQueue(Queue *Q,int *e){
	if (Q->front == Q->rear){
		return ERROR;
	}
	*e=Q->data[Q->front];   //返回队头元素给e
	Q->front=(Q->front+1)%MAXSIZE;	//front+1，若到最后则转到数组头部
	return  OK;
}
/************************************邻接表的DFS及BFS算法**********************************/
//1、建立邻接矩阵
void CreateMGraph(MGraph *G){
	int i,j;
    G->numEdges=15;//边数
	G->numVertexes=9;//顶点数
	//建立顶点表
	G->vexs[0]='A';
	G->vexs[1]='B';
	G->vexs[2]='C';
	G->vexs[3]='D';
	G->vexs[4]='E';
	G->vexs[5]='F';
	G->vexs[6]='G';
	G->vexs[7]='H';
	G->vexs[8]='I';
	for(i=0;i<G->numVertexes;i++){
		for(j=0;j<G->numVertexes;j++){
			G->arc[i][j]=0;
		}
	}
	G->arc[0][1]=1;
	G->arc[0][5]=1;
	G->arc[1][2]=1; 
	G->arc[1][8]=1; 
	G->arc[1][6]=1; 
	G->arc[2][3]=1; 
	G->arc[2][8]=1; 
	G->arc[3][4]=1;
	G->arc[3][7]=1;
	G->arc[3][6]=1;
	G->arc[3][8]=1;
	G->arc[4][5]=1;
	G->arc[4][7]=1;
	G->arc[5][6]=1; 
	G->arc[6][7]=1;
	for(i=0;i<G->numVertexes;i++){
		for(j=0;j<G->numVertexes;j++){
			G->arc[j][i]=G->arc[i][j];//无向图的邻接矩阵是关于对角线对称
		}
	}
}
//2、利用邻接矩阵构建邻接表
void CreateALGraph(MGraph G,GraphAdjList *GL){
	int i,j;
	EdgeNode *e;
	*GL = (GraphAdjList)malloc(sizeof(graphAdjList));
	(*GL)->numVertexes=G.numVertexes;
	(*GL)->numEdges=G.numEdges;
	for(i= 0;i <G.numVertexes;i++){//读入顶点信息,建立顶点表,完成初始化
		(*GL)->adjList[i].in=0;
		(*GL)->adjList[i].data=G.vexs[i];
		(*GL)->adjList[i].firstedge=NULL; 
	}
	//每个顶点都有自己的边表
	for(i=0;i<G.numVertexes;i++) {//根据邻接矩阵初始化边表
		for(j=0;j<G.numVertexes;j++){
			if (G.arc[i][j]==1){
				e=(EdgeNode *)malloc(sizeof(EdgeNode));
				e->adjvex=j;	                   
				e->next=(*GL)->adjList[i].firstedge;
				(*GL)->adjList[i].firstedge=e;
				(*GL)->adjList[j].in++;
				
			}
		}
	}
	
}

Boolean visited[MAXSIZE];//访问标志的数组
//3、DFS搜索
void DFS(GraphAdjList GL,int i){
	EdgeNode *p;
	visited[i]=TRUE;
	printf("%c ",GL->adjList[i].data);
	p=GL->adjList[i].firstedge;
	while(p){
		if(!visited[p->adjvex]){
			DFS(GL,p->adjvex);//递归访问它的邻接表
		}
		p=p->next;
	}
}
//邻接表的深度优先搜索
void DFSTraverse(GraphAdjList GL){
	int i;
	for(i=0;i<GL->numVertexes;i++){
		visited[i]=FALSE;//初始化所有节点都没访问过
	}
	for(i=0;i<GL->numVertexes;i++){
		if(!visited[i]){//对未曾访问过的节点进行DFS
			DFS(GL,i);
		}
	}
}
//4、广度优先搜索---------->层序遍历
void BFSTraverse(GraphAdjList GL){
	int i;
	EdgeNode *p;
	Queue Q;
	for(i=0;i<GL->numVertexes;i++){
		visited[i]=FALSE;
	}
	InitQueue(&Q);
	//利用队列先进先出的特性来完成层序遍历(依次访问路径长度为1,2,3,,,的节点)
	for(i=0;i<GL->numVertexes;i++){
		if(!visited[i]){
			visited[i]=TRUE;
			printf("%c ",GL->adjList[i].data);//输出顶点值
			EnQueue(&Q,i);//节点标号进队列
			while(!QueueEmpty(Q)){
				DeQueue(&Q,&i);//删除队头元素,用i保存它的值
				p=GL->adjList[i].firstedge;//获得当前顶点的边链表
				while(p){
					if(!visited[p->adjvex]){
						visited[p->adjvex]=TRUE;
						printf("%c ",GL->adjList[p->adjvex].data);
                        EnQueue(&Q,p->adjvex);//将当前节点放入队列
					}
					p=p->next;
				}
			}
		}
	}
}

/********************************测试**********************************/

void main(){
	MGraph G;
	GraphAdjList GL;
	CreateMGraph(&G);
	CreateALGraph(G,&GL);
	printf("\n深度遍历邻接表:");
	DFSTraverse(GL);

	printf("\n广度遍历邻接表:");
	BFSTraverse(GL);
	printf("\n");
}
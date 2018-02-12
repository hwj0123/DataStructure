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
typedef int Boolean; /* Boolean是布尔类型,其值是TRUE或FALSE */

typedef char VertexType; /* 顶点类型应由用户定义 */
typedef int EdgeType; /* 边上的权值类型应由用户定义 */

#define MAXSIZE 9 /* 存储空间初始分配量 */
#define MAXEDGE 15
#define MAXVEX 9
#define INFINITY 65535
//邻接矩阵结构
typedef struct{
	VertexType vexs[MAXVEX];//顶点表
	EdgeType arc[MAXVEX][MAXVEX];//邻接矩阵
	int numVertexes,numEdges;//顶点数和边数
}MGraph;
//队列
typedef struct{
	int data[MAXSIZE];
	int front;
	int rear;
}Queue;



/*********************************算法实现***********************/
//1、初始化一个空队列
Status InitQueue(Queue *Q){
	Q->front=0;
	Q->rear=0;
	return OK;
}
//2、判断队列是否为空
Status QueueEmpty(Queue Q){
	if(Q.front==Q.rear){
		return TRUE;
	}else{
		return FALSE;
	}
}
//3、如果队列没有满,则插入元素e为队尾元素
Status EnQueue(Queue *Q,int e){
	if((Q->rear+1)%MAXSIZE==Q->front){
		return ERROR;
	}
	Q->data[Q->rear]=e;
	Q->rear=(Q->rear+1)%MAXSIZE;
	return OK;
}
//4、若队列不为空,则删除队头元素
Status DeQueue(Queue *Q,int *e){
	if(Q->front==Q->rear){
		return ERROR;
	}
	*e=Q->data[Q->front];
	Q->front=(Q->front+1)%MAXSIZE;
	return OK;
}
//5、创建邻接矩阵
void CreateMGraph(MGraph *G){
	int i, j;
	G->numEdges=15;
	G->numVertexes=9;

	//初始化邻接矩阵
	G->vexs[0]='A';
	G->vexs[1]='B';
	G->vexs[2]='C';
	G->vexs[3]='D';
	G->vexs[4]='E';
	G->vexs[5]='F';
	G->vexs[6]='G';
	G->vexs[7]='H';
	G->vexs[8]='I';


	for (i = 0; i < G->numVertexes; i++){
		for ( j = 0; j < G->numVertexes; j++){
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

	
	for(i = 0; i < G->numVertexes; i++){
		for(j = i; j < G->numVertexes; j++){
			G->arc[j][i] =G->arc[i][j];//关于对角线对称
		}
	}
}

Boolean visited[MAXVEX];//标志数组
//6、DFS
void DFS(MGraph G,int i){
	int j;
	visited[i]=TRUE;
	printf("%c ",G.vexs[i]);//输出
	for(j=0;j<G.numVertexes;j++){
		if(G.arc[i][j]==1&&!visited[j]){
			DFS(G,j);//对未曾访问过的邻接节点递归调用
		}
	}
}

void DFSTraverse(MGraph G){
	int i;
	for(i=0;i<G.numVertexes;i++){
		visited[i]=FALSE;
	}
	for(i=0;i<G.numVertexes;i++){
		if(!visited[i]){
			DFS(G,i);//对未曾访问过的节点调用DFS
		}
	}
}
//7、BFS
void BFSTraverse(MGraph G){
	int i,j;
	Queue Q;
	//初始化标志数组
	for(i=0;i<G.numVertexes;i++){
		visited[i]=FALSE;
	}
	InitQueue(&Q);
	for(i=0;i<G.numVertexes;i++){
		if(!visited[i]){
			visited[i]=TRUE;
			printf("%c ",G.vexs[i]);
			EnQueue(&Q,i);//将此节点进入队列
			while(!QueueEmpty(Q)){
				DeQueue(&Q,&i);
				//访问该顶点的邻接点
				for(j=0;j<G.numVertexes;j++){
					if(G.arc[i][j]==1&&!visited[j]){
						visited[j]=TRUE;
						printf("%c ",G.vexs[j]);
						EnQueue(&Q,j);
					}
				}
			}
		}
	}
}


/***************************测试**********************/
void main(){
	MGraph G;
	CreateMGraph(&G);
	printf("\n深度遍历:");
	DFSTraverse(G);
	printf("\n广度遍历:");
	BFSTraverse(G);
	printf("\n");
}





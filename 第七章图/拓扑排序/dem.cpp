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

typedef int Status;	/* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
//�ڽӾ���
typedef struct{
	int vexs[MAXVEX];
	int arc[MAXVEX][MAXVEX];
	int numVertexes,numEdges;
}MGraph;
//�ڽӱ�
typedef struct EdgeNode{//�߱�
	int adjvex;//�洢�ö����Ӧ�±�
	int weight;//Ȩֵ
	struct EdgeNode *next;
}EdgeNode;
typedef struct VertexNode{//�����
	int in;//��������
	int data;
	EdgeNode *firstedge;//�߱�
}VertexNode,AdjList[MAXVEX];
typedef struct{
	AdjList adjList;
	int numVertexes,numEdges;
}graphAdjList,*GraphAdjList;

/*******************************************�㷨ʵ��*******************/
//1������һ���ڽӾ���
void CreateMGraph(MGraph *G){
	int i,j;
	G->numEdges=MAXEDGE;
	G->numVertexes=MAXVEX;
	//��ʼ��
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
//2�������ڽӾ��󹹽��ڽӱ�
void CreateALGraph(MGraph G,GraphAdjList *GL){
	int i,j;
	EdgeNode *e;
	*GL=(GraphAdjList)malloc(sizeof(graphAdjList));
	(*GL)->numVertexes=G.numVertexes;
	(*GL)->numEdges=G.numEdges;
	//��ʼ���ڽӱ�
	for(i=0;i<G.numVertexes;i++){
		(*GL)->adjList[i].in=0;
		(*GL)->adjList[i].data=G.vexs[i];
		(*GL)->adjList[i].firstedge=NULL;
	}
	//�����߱�
	for(i=0;i<G.numVertexes;i++){
		for(j=0;j<G.numVertexes;j++){
			if(G.arc[i][j]==1){
				e=(EdgeNode *)malloc(sizeof(EdgeNode));
				e->adjvex=j;                     
				e->next=(*GL)->adjList[i].firstedge;
				(*GL)->adjList[i].firstedge=e;		
				(*GL)->adjList[j].in++;//���++
			}
		}
	}
}
//3����������
Status TopologicalSort(GraphAdjList GL){
       EdgeNode *e;
	   int i,k,gettop;
	   int top=0;//ջָ���±�
	   int count=0;//ͳ������������
	   int *stack;//ջָ��
	   stack=(int *)malloc(GL->numVertexes*sizeof(int));
	   for(i=0;i<GL->numVertexes;i++){
		   if(0==GL->adjList[i].in){//�����Ϊ0�Ķ�����ջ
			   stack[++top]=i;
		   }
	   }
	   while(top!=0){
		   gettop=stack[top--];
		   printf("%d->",GL->adjList[gettop].data);
		   count++;//����
		   //������gettopΪ��ʼ�ı߱�
		   for(e=GL->adjList[gettop].firstedge;e;e=e->next){
			   k=e->adjvex;
			   //��k�Ŷ������ȼ�-,���Ϊ0����ջ
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
/******************************����**************************/
void main(){
	MGraph G;
	GraphAdjList GL;
	int result;
	CreateMGraph(&G);
	CreateALGraph(G,&GL);
	result=TopologicalSort(GL);
	printf("result:%d",result);
}




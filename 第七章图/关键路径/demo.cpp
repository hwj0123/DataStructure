#include<stdio.h>
#include<stdlib.h>
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXEDGE 30
#define MAXVEX 30
#define INFINITY 65535

typedef int Status;	/* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */

int *etv,*ltv;//�¼����緢��ʱ�����ٷ����¼�����,ȫ�ֱ���
int *stack2;//�洢�������е�ջ
int top2;//����stack2��ָ��

/* �ڽӾ���ṹ */
typedef struct
{
	int vexs[MAXVEX];
	int arc[MAXVEX][MAXVEX];
	int numVertexes, numEdges;
}MGraph;

/* �ڽӱ�ṹ****************** */
typedef struct EdgeNode /* �߱���  */
{
	int adjvex;    /* �ڽӵ��򣬴洢�ö����Ӧ���±� */
	int weight;		/* ���ڴ洢Ȩֵ�����ڷ���ͼ���Բ���Ҫ */
	struct EdgeNode *next; /* ����ָ����һ���ڽӵ� */
}EdgeNode;

typedef struct VertexNode /* ������� */
{
	int in;	/* ������� */
	int data; /* �����򣬴洢������Ϣ */
	EdgeNode *firstedge;/* �߱�ͷָ�� */
}VertexNode, AdjList[MAXVEX];

typedef struct
{
	AdjList adjList; 
	int numVertexes,numEdges; /* ͼ�е�ǰ�������ͱ��� */
}graphAdjList,*GraphAdjList;

/********************************�㷨ʵ��****************************/
//1�������ڽӾ���
void CreateMGraph(MGraph *G){
	int i, j;
	/* printf("����������Ͷ�����:"); */
	G->numEdges=13;
	G->numVertexes=10;
    /* ��ʼ��ͼ */
	for (i = 0; i < G->numVertexes; i++){
		G->vexs[i]=i;
	}
    /* ��ʼ��ͼ */
	for (i = 0; i < G->numVertexes; i++){
		for ( j = 0; j < G->numVertexes; j++){
			if (i==j)
				G->arc[i][j]=0;
			else
				G->arc[i][j]=INFINITY;
		}
	}

	G->arc[0][1]=3;
	G->arc[0][2]=4; 
	G->arc[1][3]=5; 
	G->arc[1][4]=6; 
	G->arc[2][3]=8; 
	G->arc[2][5]=7; 
	G->arc[3][4]=3;
	G->arc[4][6]=9; 
	G->arc[4][7]=4;
	G->arc[5][7]=6; 
	G->arc[6][9]=2;
	G->arc[7][8]=5;
	G->arc[8][9]=3;

}
//2�������ڽӾ��󹹽��ڽӱ�
void CreateALGraph(MGraph G,GraphAdjList *GL){
	int i,j;
	EdgeNode *e;

	*GL = (GraphAdjList)malloc(sizeof(graphAdjList));

	(*GL)->numVertexes=G.numVertexes;
	(*GL)->numEdges=G.numEdges;
	 /* ���붥����Ϣ����������� */
	for(i= 0;i <G.numVertexes;i++){
		(*GL)->adjList[i].in=0;
		(*GL)->adjList[i].data=G.vexs[i];
		(*GL)->adjList[i].firstedge=NULL; 	/* ���߱���Ϊ�ձ� */
	}
	 /* �����߱� */
	for(i=0;i<G.numVertexes;i++){ 
		for(j=0;j<G.numVertexes;j++){
			if (G.arc[i][j]!=0 && G.arc[i][j]<INFINITY){
				e=(EdgeNode *)malloc(sizeof(EdgeNode));
				e->adjvex=j;					/* �ڽ����Ϊj */   
				e->weight=G.arc[i][j];
				e->next=(*GL)->adjList[i].firstedge;	/* ����ǰ�����ϵ�ָ��Ľ��ָ�븳ֵ��e */
				(*GL)->adjList[i].firstedge=e;		/* ����ǰ�����ָ��ָ��e  */  
				(*GL)->adjList[j].in++;
				
			}
		}
	}
	
}
//3����������
Status TopologicalSort(GraphAdjList GL){
	EdgeNode *e;
	int i,k,gettop;
	int top=0;//����ջָ���±�
	int count=0;//����ͳ���������ĸ���
	int *stack;//�����Ϊ0�Ķ�����ջ
	stack=(int *)malloc(GL->numVertexes*sizeof(int));
	for(i=0;i<GL->numVertexes;i++){
		if(0==GL->adjList[i].in){//�����Ϊ0�Ľڵ���ջ
			stack[++top]=i;
		}
	}
	top2=0;
	//�¼����緢��ʱ��
	etv=(int*)malloc(GL->numVertexes*sizeof(int));
	for(i=0;i<GL->numVertexes;i++){
		etv[i]=0;//��ʼ��Ϊ0
	}
	stack2=(int*)malloc(GL->numVertexes*sizeof(int));//��������Ĵ洢ָ��
	printf("TopologicalSort:\t");
	while(top!=0){
		gettop=stack[top--];
		printf("%d->",GL->adjList[gettop].data);
		count++;
		stack2[++top2]=gettop;//�������Ķ������ѹ���������е�ջ
		//�����ö���ı߱�
		for(e=GL->adjList[gettop].firstedge;e;e=e->next){
			k=e->adjvex;//��ö�Ӧ���±�
			//��k�Ŷ�����ڽӵ����ȼ�1,�����1��Ϊ0,����ջ
			if(!(--GL->adjList[k].in)){
				stack[++top]=k;
			}
			//��������¼������翪ʼʱ��
			//max{etv[i]+len<vi,vk>}
			if((etv[gettop]+e->weight)>etv[k]){
				etv[k]=etv[gettop]+e->weight;
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
//4���ؼ�·��
void CriticalPath(GraphAdjList GL){
	EdgeNode *e;
	int i,gettop,k,j;
	int ete,lte;//����緢��ʱ�����ٷ���ʱ��
	TopologicalSort(GL);//����������,�õ�etv��stack2
	ltv=(int*)malloc(GL->numVertexes*sizeof(int));//�¼�������ʱ��
	for(i=0;i<GL->numVertexes;i++){
		ltv[i]=etv[GL->numVertexes-1];//��ʼ��
	}
	printf("etv:\t");
	for(i=0;i<GL->numVertexes;i++){
		printf("%d->",etv[i]);//���etv����
	}
	printf("\n");
	while(top2!=0){
		gettop=stack2[top2--];//ȡ��һ������
		for(e=GL->adjList[gettop].firstedge;e;e=e->next){
			k=e->adjvex;
			//����ltv[k]
			//min{ltv[j]-len<vk,vj>}
			if(ltv[k]-e->weight<ltv[gettop]){
				ltv[gettop]=ltv[k]-e->weight;
			}
		}
	}
	printf("ltv:\t");
	for(i=0;i<GL->numVertexes;i++){//���ltv����
		printf("%d->",ltv[i]);
	}
	printf("\n");
	for(j=0;j<GL->numVertexes;j++){
		for(e=GL->adjList[j].firstedge;e;e=e->next){
			k=e->adjvex;
			ete=etv[j];//����緢��ʱ��
			lte=ltv[k]-e->weight;//���ٷ���ʱ��
			//˵���ڹؼ�·����
			if(ete==lte){
				printf("<v%d-v%d> length:%d\n",GL->adjList[j].data,GL->adjList[k].data,e->weight);
			}
		}
	}
}
/*****************************����********************************/
void main(){
	MGraph G;
	GraphAdjList GL;
	CreateMGraph(&G);
	CreateALGraph(G,&GL);
	CriticalPath(GL);
}



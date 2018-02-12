#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status;	/* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */  
typedef int Boolean; /* Boolean�ǲ�������,��ֵ��TRUE��FALSE */

typedef char VertexType; /* ��������Ӧ���û����� */
typedef int EdgeType; /* ���ϵ�Ȩֵ����Ӧ���û����� */

#define MAXSIZE 9 /* �洢�ռ��ʼ������ */
#define MAXEDGE 15
#define MAXVEX 9
#define INFINITY 65535
//�ڽӾ���ṹ
typedef struct{
	VertexType vexs[MAXVEX];//�����
	EdgeType arc[MAXVEX][MAXVEX];//�ڽӾ���
	int numVertexes,numEdges;//�������ͱ���
}MGraph;
//����
typedef struct{
	int data[MAXSIZE];
	int front;
	int rear;
}Queue;



/*********************************�㷨ʵ��***********************/
//1����ʼ��һ���ն���
Status InitQueue(Queue *Q){
	Q->front=0;
	Q->rear=0;
	return OK;
}
//2���ж϶����Ƿ�Ϊ��
Status QueueEmpty(Queue Q){
	if(Q.front==Q.rear){
		return TRUE;
	}else{
		return FALSE;
	}
}
//3���������û����,�����Ԫ��eΪ��βԪ��
Status EnQueue(Queue *Q,int e){
	if((Q->rear+1)%MAXSIZE==Q->front){
		return ERROR;
	}
	Q->data[Q->rear]=e;
	Q->rear=(Q->rear+1)%MAXSIZE;
	return OK;
}
//4�������в�Ϊ��,��ɾ����ͷԪ��
Status DeQueue(Queue *Q,int *e){
	if(Q->front==Q->rear){
		return ERROR;
	}
	*e=Q->data[Q->front];
	Q->front=(Q->front+1)%MAXSIZE;
	return OK;
}
//5�������ڽӾ���
void CreateMGraph(MGraph *G){
	int i, j;
	G->numEdges=15;
	G->numVertexes=9;

	//��ʼ���ڽӾ���
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
			G->arc[j][i] =G->arc[i][j];//���ڶԽ��߶Գ�
		}
	}
}

Boolean visited[MAXVEX];//��־����
//6��DFS
void DFS(MGraph G,int i){
	int j;
	visited[i]=TRUE;
	printf("%c ",G.vexs[i]);//���
	for(j=0;j<G.numVertexes;j++){
		if(G.arc[i][j]==1&&!visited[j]){
			DFS(G,j);//��δ�����ʹ����ڽӽڵ�ݹ����
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
			DFS(G,i);//��δ�����ʹ��Ľڵ����DFS
		}
	}
}
//7��BFS
void BFSTraverse(MGraph G){
	int i,j;
	Queue Q;
	//��ʼ����־����
	for(i=0;i<G.numVertexes;i++){
		visited[i]=FALSE;
	}
	InitQueue(&Q);
	for(i=0;i<G.numVertexes;i++){
		if(!visited[i]){
			visited[i]=TRUE;
			printf("%c ",G.vexs[i]);
			EnQueue(&Q,i);//���˽ڵ�������
			while(!QueueEmpty(Q)){
				DeQueue(&Q,&i);
				//���ʸö�����ڽӵ�
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


/***************************����**********************/
void main(){
	MGraph G;
	CreateMGraph(&G);
	printf("\n��ȱ���:");
	DFSTraverse(G);
	printf("\n��ȱ���:");
	BFSTraverse(G);
	printf("\n");
}





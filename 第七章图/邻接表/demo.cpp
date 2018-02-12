#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXVEX 100 /* ��󶥵���,Ӧ���û����� */

typedef int Status;	/* Status�Ǻ���������,��ֵ�Ǻ������״̬����,��OK�� */
typedef char VertexType; /* ��������Ӧ���û����� */
typedef int EdgeType; /* ���ϵ�Ȩֵ����Ӧ���û����� */
typedef int Boolean; 
//�߱�ڵ�ṹ
typedef struct EdgeNode{
	int adjvex;//�洢�����Ӧ���±�
	EdgeType info;//���ڴ洢��߻���ص���Ϣ,��Ȩֵ��
	struct EdgeNode *next;//ָʾ��һ���߻򻡵Ľڵ�
}EdgeNode;
//����ڵ�ṹ
typedef struct VertexNode{
	VertexType data;//������Ϣ
	EdgeNode *firstedge;//ָ���һ�������ö���Ļ���ָ��
}VertexNode,AdjList[MAXVEX];
//�ڽӱ�ṹ
typedef struct{
	AdjList adjList;//��������
	int numNodes,numEdges;//ͼ�ĵ�ǰ�������ͻ���
}GraphAdjList;
/**************************ʵ���㷨******************************/
//1�������ڽӱ�
void CreateALGraph(GraphAdjList *G){
	int i,j,k;
	EdgeNode *e;
	printf("���붥�����ͱ���(��(3,2)):\n");
	scanf("%d,%d",&G->numNodes,&G->numEdges);
	getchar();
	printf("����%d���������Ϣ:(��a b c)",G->numNodes);  
    for(i = 0;i < G->numNodes;i++){
		scanf("%c",&G->adjList[i].data); 	//���붥����Ϣ
		G->adjList[i].firstedge=NULL; 	// ���߱���Ϊ�ձ� 
		getchar();
	}

	for(k=0;k<G->numEdges;k++){
		printf("�����(vi,vj)�ϵĶ������(ע��:��,Ϊ�ָ�,�ڵ��±��0��ʼ):\n");
		scanf("%d,%d",&i,&j);
		//��ɶ���i,j�ı߱�����
		e=(EdgeNode*)malloc(sizeof(EdgeNode));
		e->adjvex=j;//�洢���ڶ��������е��±�
		e->next=G->adjList[i].firstedge;//�ñ߱�ͷָ��ָ����
		G->adjList[i].firstedge=e;
        //ͷ�巨--->ÿ�ζ����뵽��һ��
		e=(EdgeNode*)malloc(sizeof(EdgeNode));
		e->adjvex=i;
		e->next=G->adjList[j].firstedge;
		G->adjList[j].firstedge=e;
	}
}

Boolean visited[MAXVEX]; //���ʱ�־������
//2�������������
void DFS(GraphAdjList GL, int i){
    EdgeNode *p;
 	visited[i] = TRUE;//���ʵ�i���ڵ�
 	printf("%c\t",GL.adjList[i].data);
	p = GL.adjList[i].firstedge;
	while(p)//���ʵ�i���ڵ���ڽӵ�
	{
 		if(!visited[p->adjvex])
 			DFS(GL, p->adjvex);//��Ϊ���ʵ��ڽӶ���ݹ����
		p = p->next;
 	}
}
void DFSTraverse(GraphAdjList GL){
     int i;
 	for(i = 0; i < GL.numNodes; i++)
 		visited[i] = FALSE; //��ʼ���ж���״̬����δ���ʹ�״̬
	for(i = 0; i < GL.numNodes; i++)
 		if(!visited[i]) //��δ���ʹ��Ķ������DFS,������ͨͼ,ֻ��ִ��һ��
			DFS(GL, i);
}
/***************************����***********************/
void main(){
	GraphAdjList G;
	CreateALGraph(&G);
	printf("�����������:\n");
	DFSTraverse(G);
}



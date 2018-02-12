#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXVEX 100 /* ��󶥵�����Ӧ���û����� */
#define INFINITY 65535

typedef int Status;	/* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
typedef char VertexType; /* ��������Ӧ���û�����  */
typedef int EdgeType; /* ���ϵ�Ȩֵ����Ӧ���û����� */

typedef struct{
	VertexType vexs[MAXVEX];//�����
	EdgeType arc[MAXVEX][MAXVEX];//�ڽӾ���
	int numNodes,numEdges;//ͼ�еĶ������ͱ���
}MGraph;
/************************ʵ���㷨*****************************/
//1������ͼ���ڽӾ����ʾ
void CreateMGraph(MGraph *G){
	int i,j,k,w;
	printf("���붥�����ͱ���(��:3,2):\n");
    scanf("%d,%d",&G->numNodes,&G->numEdges);//���붥�����ͱ���
	getchar();//���ջ���
	printf("����%d��������Ϣ(��:a b c-->�Կո����ָ�):",G->numNodes);
	for(i=0;i<G->numNodes;i++){
		scanf("%c",&G->vexs[i]);//���붥�����Ϣ
		getchar();
	}
	for(i=1;i<=G->numNodes;i++){
		for(j=1;j<=G->numNodes;j++){
			G->arc[i][j]=INFINITY;//�ڽӾ����ʼ��
		}
	}
	for(k=0;k<G->numEdges;k++){
		printf("�����(vi,vj)���±�i,�±�j��Ȩw:(��:i,j,w)\n");
		scanf("%d,%d,%d",&i,&j,&w);//
		G->arc[i][j]=w;
		G->arc[j][i]=G->arc[i][j];//����ͼ���ڽӾ����ǶԳƵ�
	}
}
//2����ӡ����ͼ���ڽӾ���
void printGraph(MGraph G){
	for(int i=1;i<=G.numNodes;i++){
		for(int j=1;j<=G.numNodes;j++){
			printf("%d\t",G.arc[i][j]);
		}
		printf("\n");
	}
}
/**********************����**********************/
void main(){
	MGraph G;
	CreateMGraph(&G);
	printGraph(G);
}
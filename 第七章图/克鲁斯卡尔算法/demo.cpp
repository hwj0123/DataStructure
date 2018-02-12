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

#define MAXEDGE 20
#define MAXVEX 20
#define INFINITY 65535

typedef struct{
	int arc[MAXVEX][MAXVEX];
	int numVertexes,numEdges;
}MGraph;//�ڽӾ���
//�߼�����
typedef struct{
	int begin;
	int end;
	int weight;
}Edge;//�߽ṹ
/**********************************************ʵ���㷨************************************/
//1������ͼ���ڽӾ����ʼ��
void CreateMGraph(MGraph *G){
	int i,j;
	G->numEdges=15;//1��
    G->numVertexes=9;
	//�ڽӾ����ʼ��
	for(i=0;i<G->numVertexes;i++){
		for(j=0;j<G->numVertexes;j++){
			if(i==j){
				G->arc[i][j]=0;
			}else{
				G->arc[i][j]=INFINITY;
			}
		}
	}
    G->arc[0][1]=10;
	G->arc[0][5]=11; 
	G->arc[1][2]=18; 
	G->arc[1][8]=12; 
	G->arc[1][6]=16; 
	G->arc[2][8]=8; 
	G->arc[2][3]=22; 
	G->arc[3][8]=21; 
	G->arc[3][6]=24; 
	G->arc[3][7]=16;
	G->arc[3][4]=20;
	G->arc[4][7]=7; 
	G->arc[4][5]=26; 
	G->arc[5][6]=17; 
	G->arc[6][7]=19;

	for(i=0;i<G->numVertexes;i++){
		for(j=i;j<G->numVertexes;j++){
			G->arc[j][i]=G->arc[i][j];//����ͼ���ڽӾ�����ڶԽ��߶Գ�
		}
	}

}
//2�����������ߵ�Ȩֵ,ͷ��β
void Swapn(Edge *edges,int i,int j){
    int temp;
	temp = edges[i].begin;
	edges[i].begin = edges[j].begin;
	edges[j].begin = temp;
	temp = edges[i].end;
	edges[i].end = edges[j].end;
	edges[j].end = temp;
	temp = edges[i].weight;
	edges[i].weight = edges[j].weight;
	edges[j].weight = temp;
}
//3���Ա߰���Ȩֵ����
void sort(Edge edges[],MGraph *G){
	int i, j;
	for ( i = 0; i < G->numEdges; i++){
		for ( j = i + 1; j < G->numEdges; j++){
			if (edges[i].weight > edges[j].weight){
				Swapn(edges, i, j);
			}
		}
	}
	printf("Ȩ����֮���Ϊ:\n");
	for (i = 0; i < G->numEdges; i++){
		printf("(%d, %d) %d\n", edges[i].begin, edges[i].end, edges[i].weight);
	}

}

//4���������߶����β���±�
int Find(int *parent,int f){
	while(parent[f]>0){
		f=parent[f];
	}
	return f;
}
//5����³˹�����㷨ʵ��
void MiniSpanTree_Kruskal(MGraph G){
	int i,j,n,m;
	int k=0;
	int parent[MAXVEX];//��������,�жϱ�����Ƿ��γɻ�·
	Edge edges[MAXEDGE];//����߼�����
	//�������ʼ��
	for(i=0;i<G.numVertexes-1;i++){
		for(j=i+1;j<G.numVertexes;j++){
			if(G.arc[i][j]<INFINITY){
				edges[k].begin=i;
				edges[k].end=j;
				edges[k].weight=G.arc[i][j];
				k++;
			}
		}
	}
	//����Ȩֵ����
	sort(edges,&G);

	for(i=0;i<G.numVertexes;i++){
		parent[i]=0;
	}
     
	printf("��ӡ��С������\n");
	for(i=0;i<G.numEdges;i++){
		n=Find(parent,edges[i].begin);
		m=Find(parent,edges[i].end);
		 /*˵���ñ�û�������е�������������·
		   �������ߵ�β�ڵ�����±�Ϊ��ʼ�ڵ����,�����˽ڵ��Ѿ���������������*/
		if(n!=m){
			parent[n]=m;
			printf("(%d,%d)%d\n",edges[i].begin,edges[i].end,edges[i].weight);

		}
	}
}
/***********************************����*********************************************/
void main(){
	MGraph G;
	CreateMGraph(&G);
	MiniSpanTree_Kruskal(G);
}







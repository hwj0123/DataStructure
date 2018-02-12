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
#define MAXVEX 20
#define INFINITY 65535

typedef int Status;	/* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
//�ڽӾ���
typedef struct{
	int arc[MAXVEX][MAXVEX];
	int numVertexes,numEdges;//�������,�߸���
}MGraph;
/*******************************************�㷨ʵ��****************************************/
//1�������ڽӾ���
void CreateMGraph(MGraph *G){
	int i,j;
	G->numEdges=15;//��
	G->numVertexes=9;//����
	for(i=0;i<G->numVertexes;i++){//�ڽӾ���ĳ�ʼ��
		for(j=0;j<G->numVertexes;j++){
			if(i==j){
				G->arc[i][j]=0;
			}else{
				G->arc[i][j]=G->arc[i][j]=INFINITY;
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
	for(i=0;i<G->numVertexes;i++){//����ͼ���ڽӾ�����ڶԽ��߶Գ�
		for(j=i;j<G->numVertexes;j++){
			G->arc[j][i]=G->arc[i][j];
		}
	}
}
//2������ķ�㷨����������
void MiniSpanTree_PRIM(MGraph G){
	int min,i,j,k;
	//û��ʹ�ýṹ��---->closedge
	int adjvex[MAXVEX];//���涥���±�
	int lowcost[MAXVEX];//�洢�ڸñ��ϵ�Ȩ
	//lowcost����ض����ߵ�Ȩֵ
	lowcost[0]=0;//��ʼ��
	adjvex[0]=0;//��ʼ����һ���ڵ�Ϊ0
	for(i=1;i<G.numVertexes;i++){
		lowcost[i]=G.arc[0][i];//���������ʼ��,����0�ڵ��бߵ�Ȩֵȫ���洢
		adjvex[i]=0;
	}
	for(i=1;i<G.numVertexes;i++){
		min=INFINITY;//��ʼ����СȨֵΪ�����
		j=1;
		k=0;
		//ѭ�����нڵ��ҵ���СȨֵ(����0�ڵ���صĽڵ���)
		while(j<G.numVertexes){
			if(lowcost[j]!=0&&lowcost[j]<min){
				min=lowcost[j];
				k=j;//��¼�ڵ��±�
			}
			j++;
		}
		printf("(%d,%d)\n",adjvex[k],k);//�����ǰ�������Ȩֵ��С��
		lowcost[k]=0;//����ǰ����Ȩֵ��Ϊ0,��������ɸýڵ��ѡ��
		for(j=1;j<G.numVertexes;j++){
			//�Ѿ�����С�������Ķ��㲻������СȨֵ�ĶԱ���
			if(lowcost[j]!=0&&G.arc[k][j]<lowcost[j]){
				//���¸��������ֵ
				lowcost[j]=G.arc[k][j];
				adjvex[j]=k;
			}
		}
	}
}
/********************************************����********************************************/
void main(){
	MGraph G;
	CreateMGraph(&G);
	MiniSpanTree_PRIM(G);
}









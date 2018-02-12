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
//�����ֵ�����
typedef VertexType CSElemType;
typedef struct CSNode {
	CSElemType data;
	struct CSNode *lchild, *nextsibling;
}CSNode, *CSTree;

//�ڽӱ�
typedef struct EdgeNode{
	int adjvex;//�洢�����Ӧ���±�
	EdgeType info;//���ڴ洢��߻���ص���Ϣ,��Ȩֵ��
	struct EdgeNode *next;//ָʾ��һ���߻򻡵Ľڵ�
}EdgeNode;

typedef struct VertexNode{//�ڽӱ�ڵ�
	VertexType data;//������Ϣ
	EdgeNode *firstedge;//ָ���һ�������ö���Ļ���ָ��
}VertexNode,AdjList[MAXVEX];

typedef struct{
	AdjList adjList;
	int numNodes,numEdges;//ͼ�ĵ�ǰ�������ͻ���
}ALGraph;
/***************************************�㷨ʵ��*************************************/
//1���õ���v���������Ϣ
VertexType GetVex(ALGraph G, int v){
	return G.adjList[v].data;
}
//2���ҵ�v֮���һ���ڵ�
int FirstAdjVex(ALGraph G,int v){
	if(v<G.numNodes){
		return v+1;
	}
	return ERROR;
}
//3���ҵ�w֮��ڶ���
int NextAdjVex(ALGraph G,int v,int w){
	if(w<G.numNodes){
		return w+1;
	}
	return ERROR;
}
//4����������ͼG�������������ɭ�ֵĺ����ֵ�����T
Status DFSTree(ALGraph G, int v, CSTree T, bool visited[]){
	bool first;
	CSTree p, q;
	int w;
	visited[v] = true;
	first = true;
	for (w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w)) {
		if (!visited[w]) {
			p = (CSTree) malloc (sizeof(CSNode));		//���亢�ӽ��
			if (!p) {
				return ERROR;
			}
			p->data = GetVex(G, w);
			p->lchild = NULL;
			p->nextsibling = NULL;
			if (first) {
				T->lchild = p;
				first = false;
			} else {
				q->nextsibling = p;
			}
			q = p;
			DFSTree(G, w, q, visited);//�ӵ�w�����㿪ʼ����������ȱ���ͼG
		}
	}
	return OK;
}
//5���ӵ�v���������������ȱ���ͼG,������TΪ����������
Status DFSForst(ALGraph G, CSTree &T, bool visited[]){
	int v;
	CSTree p, q;
	T = NULL;
	for (v = 0; v < G.numNodes; v++) {
		visited[v] = false;
	}
	for (v=0; v < G.numNodes; v++) {
		if (!visited[v]) {
			p = (CSTree) malloc (sizeof(CSNode));//���亢�ӽڵ�
			if (!p){
				return ERROR;
			}
			p->data = GetVex(G, v);
			p->lchild = NULL;
			p->nextsibling = NULL;
			if (!T) {	//�ǵ�һ���������ĸ�
				T = p;
			} else {
				q->nextsibling = p;
			}
			q = p;
			DFSTree(G, v, p, visited);
		}
	}
	return OK;
}
/**********************************************************************/
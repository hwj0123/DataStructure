#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXVEX 100 /* 最大顶点数,应由用户定义 */
typedef int Status;	/* Status是函数的类型,其值是函数结果状态代码,如OK等 */
typedef char VertexType; /* 顶点类型应由用户定义 */
typedef int EdgeType; /* 边上的权值类型应由用户定义 */
typedef int Boolean; 
//孩子兄弟链表
typedef VertexType CSElemType;
typedef struct CSNode {
	CSElemType data;
	struct CSNode *lchild, *nextsibling;
}CSNode, *CSTree;

//邻接表
typedef struct EdgeNode{
	int adjvex;//存储顶点对应的下标
	EdgeType info;//用于存储与边或弧相关的信息,如权值等
	struct EdgeNode *next;//指示下一条边或弧的节点
}EdgeNode;

typedef struct VertexNode{//邻接表节点
	VertexType data;//顶点信息
	EdgeNode *firstedge;//指向第一条依附该顶点的弧的指针
}VertexNode,AdjList[MAXVEX];

typedef struct{
	AdjList adjList;
	int numNodes,numEdges;//图的当前顶点数和弧数
}ALGraph;
/***************************************算法实现*************************************/
//1、得到第v个顶点的信息
VertexType GetVex(ALGraph G, int v){
	return G.adjList[v].data;
}
//2、找到v之后第一个节点
int FirstAdjVex(ALGraph G,int v){
	if(v<G.numNodes){
		return v+1;
	}
	return ERROR;
}
//3、找到w之后第二个
int NextAdjVex(ALGraph G,int v,int w){
	if(w<G.numNodes){
		return w+1;
	}
	return ERROR;
}
//4、建立无向图G的深度优先生成森林的孩子兄弟链表T
Status DFSTree(ALGraph G, int v, CSTree T, bool visited[]){
	bool first;
	CSTree p, q;
	int w;
	visited[v] = true;
	first = true;
	for (w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w)) {
		if (!visited[w]) {
			p = (CSTree) malloc (sizeof(CSNode));		//分配孩子结点
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
			DFSTree(G, w, q, visited);//从第w个顶点开始出发深度优先遍历图G
		}
	}
	return OK;
}
//5、从第v个顶点出发深度优先遍历图G,建立以T为根的生成树
Status DFSForst(ALGraph G, CSTree &T, bool visited[]){
	int v;
	CSTree p, q;
	T = NULL;
	for (v = 0; v < G.numNodes; v++) {
		visited[v] = false;
	}
	for (v=0; v < G.numNodes; v++) {
		if (!visited[v]) {
			p = (CSTree) malloc (sizeof(CSNode));//分配孩子节点
			if (!p){
				return ERROR;
			}
			p->data = GetVex(G, v);
			p->lchild = NULL;
			p->nextsibling = NULL;
			if (!T) {	//是第一棵生成树的根
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
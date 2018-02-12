#include <stdio.h>
#include <stdlib.h>

#include "my_headers.h"

/**
 * �㷨7.4����ͼG��������ȱ���, ����visitedΪ���ʱ�־���飬VisitΪ���ʺ���
 */
void DFSTraverse(ALGraph G, Boolean visited[], Status (*Visit)(ALGraph G, int v))
{
	int v;
	for (v = 0; v < G.vexnum; v++) {	//��ʼ����־����
		visited[v] = false;
	}
	for (v = 0; v < G.vexnum; v++) {
		if (!visited[v])		//����δ���ʹ��Ľ�����DFS
			DFS(G, v, visited, Visit);
	}
}

/**
 * �㷨7.5���ӵ�v����������ݹ��������ȱ���ͼG, visitedΪ�����ʱ�־���飬VisitΪ���ʺ���
 */
void DFS(ALGraph G, int v, Boolean visited[], Status (*Visit)(ALGraph G, int v))
{
	int w;
	visited[v] = true;
	Visit(G, v);		//���ʵ�v�����
	for (w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w)) {
		if (!visited[w])
			DFS(G, w, visited, Visit);
	}
}

/**
 * ��ӡͼG�е�v���������Ϣ 
 */
Status display(ALGraph G, int v)
{
	printf("%c ", G.vertices[v].data);
	return OK;
}

/**
 * �㷨7.6����������ȷǵݹ����ͼG��ʹ�ø�������Q�ͷ��ʱ�־����visited
 */
void BFSTraverse(ALGraph G, Boolean visited[], Status (*Visit)(ALGraph G, int v))
{
	int u, v, w;
	LinkQueue Q;
	InitQueue(Q);
	
	for (v = 0; v < G.vexnum; v++) {
		visited[v] = false;
	}

	for (v = 0; v < G.vexnum; v++) {
		if (!visited[v]) {
			visited[v] = true;
			Visit(G, v);
			EnQueue(Q, v);
			while (!QueueEmpty(Q)) {
				DeQueue(Q, u);		//����Ԫ�س��в���Ϊu
				for (w = FirstAdjVex(G, u); w >= 0; w = NextAdjVex(G, u, w)) {
					if (!visited[w]) {
						visited[w] = true;
						Visit(G, w);
						EnQueue(Q, w);
					}
				}
			}
		}
	}
}

/**
 * �㷨7.7����������ͼG�������������ɭ�ֵĺ����ֵ�����
 */
Status DFSForst(ALGraph G, CSTree &T, bool visited[])
{
	int v;
	CSTree p, q;
	T = NULL;
	for (v = 0; v < G.vexnum; v++) {
		visited[v] = false;
	}
	for (v=0; v < G.vexnum; v++) {
		if (!visited[v]) {
			p = (CSTree) malloc (sizeof(CSNode));
			if (!p)
				return ERROR;
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

/**
 * �㷨7.8���ӵ�v���������������ȱ���ͼG��������TΪ����������
 */
Status DFSTree(ALGraph G, int v, CSTree T, bool visited[])
{
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
			DFSTree(G, w, q, visited);
		}
	}
	return OK;
}

/**
 * �㷨7.9��Prim�㷨����С������
 */
void MiniSpanTree_PRIM(MGraph G, VertexType u)
{
	int i, j, k;
	lowedge closedge;
	k = LocateVex(G, u);
	for (j = 0; j < G.vexnum; j++) {	//���������ʼ��
		if (j != k) {
			closedge[j].adjvex = u;
			closedge[j].lowcost = G.arcs[k][j].adj;
		}
	}
	closedge[k].lowcost = 0;
	printf("�������ıߣ�\n");
	for (i = 1; i < G.vexnum; i++) {	//ѡ������G.vexnum-1������
		k = minimum(closedge, G.vexnum);		//���T����һ�����
		printf("%c %c\n", closedge[k].adjvex, G.vexs[k]);
		closedge[k].lowcost = 0;	//��k���㲢��U��
		for (j = 0; j < G.vexnum; j++) {
			if (G.arcs[k][j].adj < closedge[j].lowcost) {	//�¶��㲢��U������ѡ����С��
				closedge[j].adjvex = G.vexs[k];
				closedge[j].lowcost = G.arcs[k][j].adj;
			}
		}
	}
}

/**
 * ��closedge��Ȩֵ��0����С�Ķ���
 */
int minimum(lowedge closedge, int len)
{
	int min, i, j;
	min = -1;
	for (i = 0; i < len; i++) {
		if (closedge[i].lowcost != 0) {
			min = i;
			break;
		}
	}

	for (j = i; j < len; j++) {
		if (closedge[j].lowcost != 0 && closedge[min].lowcost > closedge[j].lowcost) {
			min = j;
		}
	}
	return min;
}

/**
 * �㷨7.12�����ز����У�����ͼG���ڽӱ�洢�ṹ����G���޻�·������ز����в�����OK�����򷵻�ERROR
 */
Status TopologicalSort(ALGraph G)
{
	int i, j, count;
	ArcNode *p;
	int indegree[MAX_VERTEX_NUM];
	int stack[MAX_VERTEX_NUM];		// ģ��ջ�Ĺ���
	int top = 0;				// ջָ��

	FindInDegree(G, indegree);
	for (i = 0; i < G.vexnum; i++) {
		if (0 == indegree[i]) {		//��ʼʱ�������Ϊ0�Ķ�����ջ
			stack[top] = i;
			++top;
		}
	}
	count = 0;				//�ز������ڶ���������
	while (0 != top) {
		--top;
		i = stack[top];			//��ջ�������Ϊ0�Ķ���
		printf("%d: %c\n", count+1, G.vertices[i].data);	//���������Ϣ
		++count;			//������1
		for (p = G.vertices[i].firstarc; p != NULL; p = p->nextarc) {
			j = p->adjvex;		//�������ȼ�1
			--indegree[j];
			if (0 == indegree[j]) {
				stack[top] = j;		//���Ϊ0�����ջ
				++top;
			}
		}
	}

	if (count < G.vexnum) {				//˵������ͼ�д��ڻ�·
		return ERROR;
	} else {
		return OK;
	}
}

/**
 * ���ڽӱ��ʾ������ͼG�ĸ��������ȣ�indegree�����б������������
 */
void FindInDegree(ALGraph G, int indegree[])
{
	int i, j;
	ArcNode *p;
	for (i = 0; i < G.vexnum; i++) {		//��ʼ���������
		indegree[i] = 0;
	}
	for (i = 0; i < G.vexnum; i++) {
		for (p = G.vertices[i].firstarc; p != NULL; p = p->nextarc) {
			j = p->adjvex;
			++indegree[j];
		}
	}
}

/**
 * �㷨7.13��������G�����ڽӱ�洢����������¼������緢��ʱ��ve
 * TΪ�ز����ж���ջ
 * ��G�޻�·������ջT����G��һ���ز����У��Һ���ֵΪOK������ΪERROR
 */
Status TopologicalSort(ALGraph G, SqStack &T, int ve[])
{
	SqStack S;		// SΪ�����ջ
	int indegree[MAX_VERTEX_NUM];
	int count, i, j, k;
	int arcvalue = 0;
	ArcNode *p;
	InitStack(S);
	InitStack(T);
	FindInDegree(G, indegree);
	for (i = 0; i < G.vexnum; i++) {
		if (0 == indegree[i]) {		//��ʼʱ�������Ϊ0�Ķ�����ջ����ʱӦֻ��Դ����ջ
			Push(S, i);
		}
	}
	count = 0;
	for (i = 0; i < G.vexnum; i++) {
		ve[i] = 0;
	}
	while (!StackEmpty(S)) {
		Pop(S, j);
		Push(T, j);
		++count;
		for (p = G.vertices[j].firstarc; p != NULL; p = p->nextarc) {
			k = p->adjvex;
			--indegree[k];
			if (0 == indegree[k]) {
				Push(S, k);
			}
			arcvalue = atoi(p->info);		//�ʱ��, ���ַ�ת������
			if (ve[j] + arcvalue > ve[k]) {		//ѡ�����ģ���һ����ؼ����ο��鱾P184
				ve[k] = ve[j] + arcvalue;
			}
		}
	}

	if (count < G.vexnum) {
		return ERROR;
	} else {
		return OK;
	}
}

/**
 * �㷨7.14��GΪ�����������G�ĸ���ؼ��
 * ջT�б���ͼG���ز����У�ve������Ϊ����������翪ʼʱ��
 */
Status CriticalPath(ALGraph G, SqStack &T, int ve[])
{
	int i, j, k, dut, ee ,el;
	ArcNode *p;
	int vl[MAX_VERTEX_NUM];
	if (ERROR == TopologicalSort(G, T, ve)) {
		return ERROR;
	}
	for (i = 0; i < G.vexnum; i++) {		//��ʼ���������ٷ���ʱ��
		vl[i] = ve[G.vexnum-1];
	}
	while (!StackEmpty(T)) {			//���ز�����������������ʼʱ��vlֵ
		Pop(T, j);
		for (p = G.vertices[j].firstarc; p != NULL; p = p->nextarc) {
			k = p->adjvex;
			dut = atoi(p->info);		//�ʱ��
			if (vl[k] - dut < vl[j]) {
				vl[j] = vl[k] - dut;
			}
		}
	}

	printf("�ؼ����");
	for (j = 0; j < G.vexnum; j++) {	//�������翪ʼʱ�������ʼʱ�䣬������ؼ��
		for (p = G.vertices[j].firstarc; p != NULL; p = p->nextarc) {
			k = p->adjvex;
			dut = atoi(p->info);
			ee = ve[j];		//������翪ʼʱ��
			el = vl[k]-dut;		//�������ʼʱ��
			if (ee == el) {		//�ؼ��
				printf("%c%c ", G.vertices[j].data, G.vertices[k].data);
			}
		}
	}
	printf("\n");
}

/**
 * �㷨7.15�����·���㷨��Dijkstra�㷨
 * ����������G��v0���㵽���ඥ��v�����·��P[v], �����Ȩ����ΪD[v]
 */
void ShortestPath_DIJ(MGraph G, int v0, PathMatrix &P, ShortPathTable &D)
{
	bool final[MAX_VERTEX_NUM];	//final[v]Ϊtrue��ʾ�Ѿ���ô�v0��v�����·��
	bool flag = false;		//��־V��S�еĶ������v0�Ƿ�Ϊ���޴�
	int v, w, i, min;
	for (v = 0; v < G.vexnum; v++) {	//��ʼ����ʼ״̬
		final[v] = false;
		D[v] = G.arcs[v0][v].adj;
		for (w = 0; w < G.vexnum; w++) {
			P[v][w] = false;	//���·��
		}
		if (D[v] < INFINITY) {		//�����ö�����v0ֱ��������������������v��·����
			P[v][v0] = true;
			P[v][v] = true;
		}
	}
	D[v0] = 0;
	final[v0] = true;			//��ʼ����v0��������S��

	// ��ʼ��ѭ����ÿ�����v0��ĳ����������·����������v��S��
	for (i = 1; i < G.vexnum; i++) {
		flag = false;
		min = INFINITY;
		for (w = 0; w < G.vexnum; w++) {
			if (!final[w]) {	//w������V��S��
				if (D[w] < min) {
					flag = true;
					v = w;
					min = D[w];
				}
			}
		}
		if (false == flag) {		//���v0��V��S�еľ��붼�����޴����˳�ѭ�����㷨����
			break;
		}
		final[v] = true;		//��v0��������Ķ���v����S���У�ִ�е����㷨�ĵ�2��
		for (w = 0; w < G.vexnum; w++) {	
			//���µ�ǰ���·��������,�����¼���ĵ㵽V��S���������D[k], �ؼ���һ��
			if (!final[w] && INFINITY != G.arcs[v][w].adj && (min + G.arcs[v][w].adj) < D[w]) {
				D[w] = min + G.arcs[v][w].adj;
				CopyPath(P, w, v);
				P[w][w] = true;		//P[w] = P[w] + P[v];
			}
		}
	}
}

/**
 * �������·���㷨����v��·��������w
 */
void CopyPath(PathMatrix &P, int w, int v)
{
	int i;
	for (i = 0; i < MAX_VERTEX_NUM; i++) {
		P[w][i] = P[v][i];
	}
}

/**
 * ��ӡDijkstra��õ�v0�������������·��P[0...G.vexnum]��·������D[0...G.vexnum]
 */
void DisplayShorstPath_DIJ(MGraph G, int v0, PathMatrix P, ShortPathTable D)
{
	int i ,j;
	printf("�Ӷ���%c�������������������·�����£�\n", G.vexs[v0]);
	for (i = 0; i < G.vexnum; i++) {
		if (i != v0) {
			if (INFINITY == D[i]) {
				printf("����%c���ɵ��", G.vexs[i]);
			} else {
				printf("����%c(����%d)��", G.vexs[i], D[i]);
				for (j = 0; j < G.vexnum; j++) {
					if (true == P[i][j]) {
						printf("%c ", G.vexs[j]);
					}
				}
			}
			printf("\n");
		}
	}
}

/**
 * �㷨7.16, ��Floyd�㷨��������G�и��Զ���v��w֮������·��P[v][w]�����Ȩ����D[v][w],
 * ��P[v][w][u]Ϊtrue��u�Ǵ�v��w��ǰ������·���ϵĶ���
 */
void ShortestPath_FLOYD(MGraph G, PathMatrix P[], DistanceMatrix D)
{
	int v, w, u, i;
	for (v = 0; v < G.vexnum; v++) {		//��ʼ�����Խ��֮���ʼ��֪·��������
		for (w = 0; w < G.vexnum; w++) {
			D[v][w] = G.arcs[v][w].adj;
			for (u = 0; u < G.vexnum; u++) {
				P[v][w][u] = false;
			}
			if (D[v][w] < INFINITY) {	//v��w��ֱ��·��
				P[v][w][v] = true;
				P[v][w][w] = true;
			}
		}
	}

	for (u = 0; u < G.vexnum; u++) {					//uΪv��w���м�·���ϵĶ���
		for (v = 0; v < G.vexnum; v++) {
			for (w = 0; w < G.vexnum; w++) {
				if (D[v][u] != INFINITY && D[u][w] != INFINITY 
					&& D[v][u] + D[u][w] < D[v][w]) {	//��v��u��w��һ��·������
					D[v][w] = D[v][u] + D[u][w];
					for (i = 0; i < G.vexnum; i++) {	//����·��
						P[v][w][i] = P[v][u][i] || P[u][w][i];
					}
				}
			}
		}
	}
}

/**
 * ��ӡFLOYD��õ�����ͼG�и��Զ���֮������·������Ȩ����
 */
void DisplayShorstPath_FLOYD(MGraph G, PathMatrix P[], DistanceMatrix D)
{
	int i, j, k;
	for (i = 0; i < G.vexnum; i++) {
		for (j = 0; j < G.vexnum; j++) {
			if (i != j) {
				if (INFINITY == D[i][j]) {
					printf("�ڵ�%c��%c���ɵ��\n", G.vexs[i], G.vexs[j]);
				} else {
					printf("�ڵ�%c%c֮��(��̾���%d)��", G.vexs[i], G.vexs[j], D[i][j]);
					for (k = 0; k < G.vexnum; k++) {
						if (true == P[i][j][k]) {
							printf("%c", G.vexs[k]);
						}
					}
					printf("\n");
				}
			}
		}
	}
}
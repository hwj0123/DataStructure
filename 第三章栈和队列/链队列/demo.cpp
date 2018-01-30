#include<stdio.h>
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef int Status;
typedef char QElemType;//QElemType--->char

typedef struct QNode{
	QElemType data;
	struct QNode *next;
}QNode,*QueuePtr;

typedef struct{
	QueuePtr front;//��ͷ
	QueuePtr rear;//��β
}LinkQueue;

//1������һ���յĶ���q
Status InitQueue(LinkQueue *q){
	q->front=q->rear=(QueuePtr)malloc(sizeof(QNode));
	if(!q->front){
		exit(ERROR);
	}
	q->front->next=NULL;
	return OK;
}
//2�����ٶ���q
Status DestoryQueue(LinkQueue *q){
	while(q->front){
		q->rear=q->front->next;
		free(q->front);
		q->front=q->rear;
	}
	return OK;
}
//3������Ԫ��eΪq���µĶ�βԪ��
Status EnQueue(LinkQueue *q,QElemType e){
	QueuePtr p=(QueuePtr)malloc(sizeof(QNode));
	if(!p){
		exit(ERROR);
	}
	p->data=e;
	p->next=NULL;
	q->rear->next=p;
	q->rear=p;
	return OK;

}
//4�������в���,��ɾ��q�Ķ�ͷԪ��,��e������ֵ,������OK
Status DeQueue(LinkQueue *q,QElemType *e){
	QueuePtr p;
	if(q->front==q->rear){
		return ERROR;
	}
	p=q->front->next;
	*e=p->data;//��e��¼����ͷ��ֵ
	q->front->next=p->next;
	if(q->rear==p){//���һ��Ԫ��ɾ��ʱ,��Զ�βָ�����¸�ֵ
		q->rear=q->front;
	}
	free(p);
	return OK;
	
}
//5����q��Ϊ�ն���
Status ClearQueue(LinkQueue *Q){
	QueuePtr p,q;
	Q->rear=Q->front;
	p=Q->front->next;
	Q->front->next=NULL;
	while(p)
	{
		 q=p;
		 p=p->next;
		 free(q);
	}
	return OK;

}
//6��������qΪ��,�򷵻�TRUE,����FALSE
Status QueueEmpty(LinkQueue q){
	if(q.front==q.rear)
		return TRUE;
	else
		return FALSE;
}
//7�����ض���q��Ԫ�ظ���
int	QueueLength(LinkQueue Q){
	int i=0;
	QueuePtr p;
	p=Q.front;
	while(Q.rear!=p)
	{
		 i++;
		 p=p->next;
	}
	return i;

}
//8�������в���,����e���ض���q�Ķ�ͷԪ��,������OK,���򷵻�FALSE
Status GetHead(LinkQueue q,QElemType *e){
	QueuePtr p;
	if(q.front==q.rear){
		return ERROR;
	}
	p=q.front->next;
	*e=p->data;
	return OK;
}

Status visit(QElemType c)
{
	printf("%c ",c);
	return OK;
}
//9����ͷ��β�������
Status QueueTraverse(LinkQueue Q)
{
	QueuePtr p;
	p=Q.front->next;
	while(p)
	{
		 visit(p->data);
		 p=p->next;
	}
	printf("\n");
	return OK;
}

void main(){
	LinkQueue l;
	char e;
	InitQueue(&l);
	EnQueue(&l,'a');
	EnQueue(&l,'b');
	EnQueue(&l,'c');
	printf("��ʱ��������\n");
    QueueTraverse(l);
	printf("����Ϊ%d\n",QueueLength(l));
	DeQueue(&l,&e);
	printf("ɾ����ͷԪ��%c��,��ʱ��������:\n",e);
	QueueTraverse(l);



}

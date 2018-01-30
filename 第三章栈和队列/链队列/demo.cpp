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
	QueuePtr front;//队头
	QueuePtr rear;//队尾
}LinkQueue;

//1、构造一个空的队列q
Status InitQueue(LinkQueue *q){
	q->front=q->rear=(QueuePtr)malloc(sizeof(QNode));
	if(!q->front){
		exit(ERROR);
	}
	q->front->next=NULL;
	return OK;
}
//2、销毁队列q
Status DestoryQueue(LinkQueue *q){
	while(q->front){
		q->rear=q->front->next;
		free(q->front);
		q->front=q->rear;
	}
	return OK;
}
//3、插入元素e为q的新的队尾元素
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
//4、若队列不空,则删除q的队头元素,用e返回其值,并返回OK
Status DeQueue(LinkQueue *q,QElemType *e){
	QueuePtr p;
	if(q->front==q->rear){
		return ERROR;
	}
	p=q->front->next;
	*e=p->data;//用e记录队列头的值
	q->front->next=p->next;
	if(q->rear==p){//最后一个元素删除时,需对队尾指针重新赋值
		q->rear=q->front;
	}
	free(p);
	return OK;
	
}
//5、将q清为空队列
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
//6、若队列q为空,则返回TRUE,否则FALSE
Status QueueEmpty(LinkQueue q){
	if(q.front==q.rear)
		return TRUE;
	else
		return FALSE;
}
//7、返回队列q的元素个数
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
//8、若队列不空,则用e返回队列q的队头元素,并返回OK,否则返回FALSE
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
//9、从头至尾输出队列
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
	printf("此时队列中有\n");
    QueueTraverse(l);
	printf("长度为%d\n",QueueLength(l));
	DeQueue(&l,&e);
	printf("删除队头元素%c后,此时队列中有:\n",e);
	QueueTraverse(l);



}

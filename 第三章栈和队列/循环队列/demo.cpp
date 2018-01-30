#include<stdio.h>
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXQSIZE 100
typedef int Status;
typedef char QElemType;//QElemType--->char

typedef struct{
	QElemType *base;
	int front;
	int rear;
}SqQueue;
//1������һ���ն���
Status InitQueue(SqQueue *q){
	q->base=(QElemType*)malloc(MAXQSIZE*sizeof(QElemType));
	if(!q->base){
		exit(ERROR);
	}
	q->front=q->rear=0;
	return OK;
}
//2������ѭ������q�ĳ���
int QueueLength(SqQueue q){
	return (q.rear-q.front+MAXQSIZE)%MAXQSIZE;
}
//3������Ԫ��eΪѭ������q�Ķ�βԪ��
Status EnQueue(SqQueue *q,QElemType e){
	if((q->rear+1)%MAXQSIZE==q->front){//ѭ����������
		return ERROR;
	}
	q->base[q->rear]=e;
	q->rear=(q->rear+1)%MAXQSIZE;
	return OK;
}
//4�������в���,��ɾ��q�Ķ�ͷԪ��,��e������ֵ
Status DeQueue(SqQueue *q,QElemType *e){
	if(q->front==q->rear){
		return ERROR;
	}
	*e=q->base[q->front];
	q->front=(q->front+1)%MAXQSIZE;
	return OK;
}
//5����������
Status QueueTraverse(SqQueue q)
{
    int f=q.front;
	while(f!=q.rear){
		printf("%c\t",q.base[f]);
		f=(f+1)%MAXQSIZE;
	}
	printf("\n");
	return OK;
}
void main(){
	SqQueue q;
	char e;
	InitQueue(&q);
	EnQueue(&q,'a');
	EnQueue(&q,'b');
	EnQueue(&q,'c');
	printf("��ʱ���г���Ϊ:%d\n",QueueLength(q));
	QueueTraverse(q);
	printf("ɾ����ͷԪ��a��\n");
    DeQueue(&q,&e);
	QueueTraverse(q);



}



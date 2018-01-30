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
//1、构造一个空队列
Status InitQueue(SqQueue *q){
	q->base=(QElemType*)malloc(MAXQSIZE*sizeof(QElemType));
	if(!q->base){
		exit(ERROR);
	}
	q->front=q->rear=0;
	return OK;
}
//2、返回循环队列q的长度
int QueueLength(SqQueue q){
	return (q.rear-q.front+MAXQSIZE)%MAXQSIZE;
}
//3、插入元素e为循环队列q的队尾元素
Status EnQueue(SqQueue *q,QElemType e){
	if((q->rear+1)%MAXQSIZE==q->front){//循环队列已满
		return ERROR;
	}
	q->base[q->rear]=e;
	q->rear=(q->rear+1)%MAXQSIZE;
	return OK;
}
//4、若队列不空,则删除q的队头元素,用e返回其值
Status DeQueue(SqQueue *q,QElemType *e){
	if(q->front==q->rear){
		return ERROR;
	}
	*e=q->base[q->front];
	q->front=(q->front+1)%MAXQSIZE;
	return OK;
}
//5、遍历队列
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
	printf("此时队列长度为:%d\n",QueueLength(q));
	QueueTraverse(q);
	printf("删除队头元素a后\n");
    DeQueue(&q,&e);
	QueueTraverse(q);



}



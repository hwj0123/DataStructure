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
//有序链表的数据元素类型
typedef struct{
	int OccurTime;//事件发生时刻
	int NType;//事件类型  0-到达事件  1-4四个窗口的离开事件
}Event,ElemType;
//链表的定义
typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LNode,*LinkList;

//队列中数据元素的定义
typedef struct{
	int ArrivalTime;//到达时刻
	int Duration;//办理事务所需时间
}QElemType;//队列的数据类型

//队列的定义
typedef struct QNode{
	QElemType data;
	struct QNode *next;
}QNode,*QueuePtr;

typedef struct{
	QueuePtr front;//队头
	QueuePtr rear;//队尾
}LinkQueue;

typedef LinkList EventList;

EventList ev;//事件表
Event en;//事件
LinkQueue q[5];//四个客户队列
QElemType customer;//客户记录
int TotalTime,CustomerNum;//累计客户逗留时间,客户数

//初始化链表
Status InitList(LinkList *L){
	*L=(LinkList)malloc(sizeof(LNode));
	if(!(*L)){
		return ERROR;
	}
	(*L)->next=NULL;
	return OK;
}
//初始化
void OpenForDay(){

}
//过于复杂,,,,略

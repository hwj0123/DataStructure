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
//�������������Ԫ������
typedef struct{
	int OccurTime;//�¼�����ʱ��
	int NType;//�¼�����  0-�����¼�  1-4�ĸ����ڵ��뿪�¼�
}Event,ElemType;
//����Ķ���
typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LNode,*LinkList;

//����������Ԫ�صĶ���
typedef struct{
	int ArrivalTime;//����ʱ��
	int Duration;//������������ʱ��
}QElemType;//���е���������

//���еĶ���
typedef struct QNode{
	QElemType data;
	struct QNode *next;
}QNode,*QueuePtr;

typedef struct{
	QueuePtr front;//��ͷ
	QueuePtr rear;//��β
}LinkQueue;

typedef LinkList EventList;

EventList ev;//�¼���
Event en;//�¼�
LinkQueue q[5];//�ĸ��ͻ�����
QElemType customer;//�ͻ���¼
int TotalTime,CustomerNum;//�ۼƿͻ�����ʱ��,�ͻ���

//��ʼ������
Status InitList(LinkList *L){
	*L=(LinkList)malloc(sizeof(LNode));
	if(!(*L)){
		return ERROR;
	}
	(*L)->next=NULL;
	return OK;
}
//��ʼ��
void OpenForDay(){

}
//���ڸ���,,,,��

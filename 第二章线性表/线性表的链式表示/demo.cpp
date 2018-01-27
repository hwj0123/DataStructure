#include "stdio.h"    
#include "string.h"
#include "ctype.h"      
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define MAXSIZE 20 /* �洢�ռ��ʼ������ */

typedef int Status;/* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
typedef int ElemType;/* ElemType���͸���ʵ������������������Ϊint */

typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LNode,*LinkList;
//1����������ĳ�ʼ��
Status InitList(LinkList *L){
	*L=(LinkList)malloc(sizeof(LNode));
	if(!(*L)){
		return ERROR;
	}
	(*L)->next=NULL;
	return OK;
}
//2�������Ա�L�е�i��λ�ò���Ԫ��e
Status ListInsert_L(LinkList *L,int i,ElemType e){
	int j;
	LinkList p,s;
	p=*L;
	j=0;
	while(p&&j<i-1){
		p=p->next;
		j++;
	}
	if(!p||j>i-1){//��i��Ԫ�ز�����
		return ERROR;
	}
	s=(LinkList)malloc(sizeof(LNode));
	s->data=e;
	s->next=p->next;
	p->next=s;
	return OK;
}
//3��
Status visit(ElemType e){
	printf("%d",e);
    return OK;
}
//3����ӡ��������������Ԫ��
Status ListTraverse(LinkList L){
	LinkList p=L->next;
	while(p){
		visit(p->data);
		p=p->next;
	}
	printf("\n");
	return OK;
}
//4��������������L�е�i��Ԫ��
Status GetElem_L(LinkList L,int i,ElemType *e){
	LNode *p;
	int j;
	p=L->next;
	j=1;
	while(p&&j<i){
		p=p->next;
		j++;
	}
	if(!p||j>i){
		return ERROR;
	}
	*e=p->data;
	return OK;
}
//5��ɾ�����������е�i��Ԫ��,����e������ֵ
Status ListDelete_L(LinkList *L,int i,ElemType *e){
	LinkList p,q;
	int j;
	p=*L;
	j=0;
	while(p->next&&j<i-1){
		p=p->next;
		++j;
	}
	if(!(p->next)||j>i-1){
		return ERROR;
	}
	q=p->next;
	p->next=q->next;
	*e=q->data;
	free(q);
	return OK;
}
//6����λ������n��Ԫ�ص�ֵ,������ͷ�ڵ����������L(ͷ�巨)
void CreateList_L(LinkList *L,int n){
	LinkList p;
	int i;
	*L=(LinkList)malloc(sizeof(LNode));
	(*L)->next=NULL;
	for(i=n;i>0;i--){
		p=(LinkList)malloc(sizeof(LNode));
		scanf("%d",&(p->data));
		p->next=(*L)->next;
		(*L)->next=p;
	}
}
//7����������n��Ԫ�ص�ֵ,������ͷ������������L(β�巨)
void CreateListTail(LinkList *L,int n){
	LinkList p,q;
	int i;
	*L=(LinkList)malloc(sizeof(LNode));
	(*L)->next=NULL;
	q=(*L);
	for(i=n;i>0;i--){
		p=(LinkList)malloc(sizeof(LNode));
		scanf("%d",&(p->data));
		q->next=p;
		q=p;
	}
	q->next=NULL;
}
//8��Lc=La U Lb(��La��Lb�ϲ�ΪLc)
void MergeList_L(LinkList *La,LinkList *Lb,LinkList *Lc){
	LinkList pa,pb,pc;
	pa=(*La)->next;
	pb=(*Lb)->next;
	(*Lc)=pc=(*La);
	while(pa&&pb){
		if(pa->data<=pb->data){
			pc->next=pa;
			pc=pa;
			pa=pa->next;
		}else{
			pc->next=pb;
			pc=pb;
			pb=pb->next;
		}
	}
	pc->next=pa? pa:pb;
	free(*Lb);
}
void main(){
	LinkList L;
	LinkList La,Lb,Lc;
	ElemType e;
	int j,k;
//	InitList(&L);
//	for(j=1;j<=5;j++){
//		ListInsert_L(&L,1,j);
//	}
//	printf("����1-5����ͷ��:\n");
//	ListTraverse(L);
//	GetElem_L(L,1,&k);
//	printf("��������L�е�1��Ԫ��Ϊ%d\n",k);
//	printf("ɾ�����������е�1��Ԫ�غ�:\n");
//    ListDelete_L(&L,1,&k);
//	ListTraverse(L);
//	printf("ͷ�巨����5���ڵ����������\n");
//    CreateList_L(&L,5);
//    ListTraverse(L);
//    printf("ͷ�巨����3���ڵ����������La\n");
//    CreateList_L(&La,3);
//	printf("ͷ�巨����3���ڵ����������Lb\n");
//    CreateList_L(&Lb,3);
//	printf("��La����Lb�õ�Lc\n");
//    MergeList_L(&La,&Lb,&Lc);
//    ListTraverse(Lc);

	printf("β�巨����3���ڵ����������La\n");
    CreateListTail(&La,3);
	ListTraverse(La);



}

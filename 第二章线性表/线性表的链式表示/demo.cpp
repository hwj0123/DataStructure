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
#define MAXSIZE 20 /* 存储空间初始分配量 */

typedef int Status;/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int ElemType;/* ElemType类型根据实际情况而定，这里假设为int */

typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LNode,*LinkList;
//1、线性链表的初始化
Status InitList(LinkList *L){
	*L=(LinkList)malloc(sizeof(LNode));
	if(!(*L)){
		return ERROR;
	}
	(*L)->next=NULL;
	return OK;
}
//2、在线性表L中第i个位置插入元素e
Status ListInsert_L(LinkList *L,int i,ElemType e){
	int j;
	LinkList p,s;
	p=*L;
	j=0;
	while(p&&j<i-1){
		p=p->next;
		j++;
	}
	if(!p||j>i-1){//第i个元素不存在
		return ERROR;
	}
	s=(LinkList)malloc(sizeof(LNode));
	s->data=e;
	s->next=p->next;
	p->next=s;
	return OK;
}
//3、
Status visit(ElemType e){
	printf("%d",e);
    return OK;
}
//3、打印线性链表中所有元素
Status ListTraverse(LinkList L){
	LinkList p=L->next;
	while(p){
		visit(p->data);
		p=p->next;
	}
	printf("\n");
	return OK;
}
//4、返回线性链表L中第i个元素
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
//5、删除线性链表中第i个元素,并由e返回其值
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
//6、逆位序输入n个元素的值,建立带头节点的线性链表L(头插法)
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
//7、正序输入n个元素的值,建立带头结点的线性链表L(尾插法)
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
//8、Lc=La U Lb(将La和Lb合并为Lc)
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
//	printf("插入1-5到表头后:\n");
//	ListTraverse(L);
//	GetElem_L(L,1,&k);
//	printf("线性链表L中第1个元素为%d\n",k);
//	printf("删除线性链表中第1个元素后:\n");
//    ListDelete_L(&L,1,&k);
//	ListTraverse(L);
//	printf("头插法建立5个节点的线性链表\n");
//    CreateList_L(&L,5);
//    ListTraverse(L);
//    printf("头插法建立3个节点的线性链表La\n");
//    CreateList_L(&La,3);
//	printf("头插法建立3个节点的线性链表Lb\n");
//    CreateList_L(&Lb,3);
//	printf("由La并上Lb得到Lc\n");
//    MergeList_L(&La,&Lb,&Lc);
//    ListTraverse(Lc);

	printf("尾插法建立3个节点的线性链表La\n");
    CreateListTail(&La,3);
	ListTraverse(La);



}

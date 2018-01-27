#include "stdio.h"    
#include "string.h"
#include "ctype.h"      
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define FALSE 0
#define TRUE 1
#define MAXSIZE 20 /* �洢�ռ��ʼ������ */

typedef int Status;/* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
//ElemType�Ķ���---->��
typedef struct{
	float coef;//ϵ��
	int expn;//ָ��
}term,ElemType;

typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LNode,*LinkList;

typedef LinkList polynomial;

//1����������ĳ�ʼ��
Status InitList(LinkList *L){
	*L=(LinkList)malloc(sizeof(LNode));
	if(!(*L)){
		return ERROR;
	}
	(*L)->next=NULL;
	return OK;
}
//2���ж������Ƿ�Ϊ��
Status ListEmpty(LinkList L)
{ 
    if(L->next)
        return FALSE;
    else
        return TRUE;
}

//3��ɾ��һԪ���ζ���ʽ�е�i����
Status ListDelete(LinkList *L,int i,ElemType *e) 
{ 
	int j;
	LinkList p,q;
	p = *L;
	j = 1;
	while (p->next && j < i)	/* ����Ѱ�ҵ�i��Ԫ�� */
	{
        p = p->next;
        ++j;
	}
	if (!(p->next) || j > i) 
	    return ERROR;           /* ��i��Ԫ�ز����� */
	q = p->next;
	p->next = q->next;			/* ��q�ĺ�̸�ֵ��p�ĺ�� */
	*e = q->data;               /* ��q����е����ݸ�e */
	free(q);                    /* ��ϵͳ���մ˽�㣬�ͷ��ڴ� */
	printf("ɾ���ɹ�\n");
	return OK;
}

//4�������Ա�L�е�i��λ�ò���Ԫ��e
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
//5�����ʺ���
Status visit(ElemType e){
	printf("ϵ��:%f\tָ��:%d",e.coef,e.expn);
    return OK;
}
//6����ӡ��������������Ԫ��
Status ListTraverse(LinkList L){
	LinkList p=L->next;
	while(p){
		visit(p->data);
		p=p->next;
	}
	printf("\n");
	return OK;
}
//7�������������д�����e����compre()==0��Ԫ��,��qָ��L�е�һ��ֵΪe�Ľڵ��λ��,������True
//����qָ���һ��compare()>0��Ԫ�ص�ǰ����λ��,������FALSE
//��Ŀ��˼Ӧ����Ҫ����ָ��˳��洢
Status LocateElem(LinkList L,ElemType e,int *q,int (*compare)(ElemType,ElemType)){
	int i=1;
	LinkList p=L->next;
	while(p){
		if(compare(p->data,e)==0){
             *q=i;
			 return TRUE;
		}else if(compare(p->data,e)>0){
			 *q=i;//����û��ָ��ǰ��,��Ϊ�Զ��庯��ListInsert_L����Ĳ���λ����Ҫ��
			return FALSE;
		}
		i++;
		p=p->next;
	  }
	*q=i;
	return FALSE;
}
//8���Զ���ȽϺ���--->�Ƚ�ϵ��
int compareValue(ElemType x,ElemType y){
	if(x.expn==y.expn){
		return 0;
	}else if(x.expn>y.expn){
		return 1;
	}else{
		return -1;
	}
}
//9�����������ж�����compare()��Լ��,��ֵΪe�Ľڵ���뵽��������L�ĺ���λ����...
//������һ����ָ���������е�һԪ����ʽ
//��10�еķ�ʽ����ʵ�ִ˹���,������LocateElem,ListInsert_L��ʡ�Դ˲���
Status OrderInsert(LinkList *L,ElemType e,int(*compare)(ElemType,ElemType)){
  return 0;

}
//10������m���ϵ����ָ��,������ʾһԪ����ʽ�������б�p
void CreatePolyn(polynomial *p,int m){
	ElemType e;
	int i,q;
	LinkList h;
	InitList(p);
	h=*p;
	e.coef=0.0;
	e.expn=-1;
    h->data=e;
	for(i=1;i<=m;i++){
		printf("�������%d���ϵ����ָ��\n",i);
		scanf("%f%d",&e.coef,&e.expn);
		if(!LocateElem(*p,e,&q,compareValue)){
			printf("����λ��:%d\n",q);
			ListInsert_L(p,q,e);
		}
	}

}
//11������һԪ����ʽ
void DestroyPolyn(polynomial *L){
	LinkList p,q;
	p=(*L)->next;           /*  pָ���һ����� */
	while(p)                /*  û����β */
	{
		q=p->next;
		free(p);
		p=q;
	}
	(*L)->next=NULL;        /* ͷ���ָ����Ϊ�� */
}
//12����ӡһԪ����ʽ
void PrintPolyn(polynomial L){
	   LinkList p=L->next;
	   while(p){
	       printf("%.1fx^%d\t",p->data.coef,p->data.expn);
		   p=p->next;
	   }
	   printf("\n");
}
//13������һԪ����ʽ�е�����
int PolynLength(polynomial L){
	int i=0;
    LinkList p=L->next; /* pָ���һ����� */
    while(p)                        
    {
        i++;
        p=p->next;
    }
    return i;
}
//14�����ö���ʽL�е�i���ϵ��Ϊsum
void SetCurElem(polynomial L,float sum,int i){
	int j=0;
	LinkList p;
	p=L;
	while(j<i){
		p=p->next;
		j++;
	}
	p->data.coef=sum;
	printf("��ֵ���\n");
}
//15����һԪ����ʽPa׷��Pb��ʣ��ڵ�
void Append(polynomial *Pa,LinkList qb){
	int i;
	LinkList ha=*Pa;
	while(qb){
         LocateElem(ha,qb->data,&i,compareValue);
         ListInsert_L(Pa,i,qb->data);
         qb=qb->next;
	}
}
//16����ɶ���ʽ���������,Pa=Pa+Pb,������Pb
void AddPolyn(polynomial *Pa,polynomial *Pb){
	LinkList ha,hb,qa,qb;
	ElemType elem;
	int i;
	float sum;
	ha=*Pa;//ͷ�ڵ�
	hb=*Pb;
	qa=ha->next;
	qb=hb->next;
	while(qa&&qb){
		switch(compareValue(qa->data,qb->data)){
		case -1:
			qa=qa->next;
			break;
		case 0:
            sum=qa->data.coef+qb->data.coef;
			if(sum!=0.0){
                //�޸�Pa�ж�Ӧ�ڵ��ϵ��
				LocateElem(ha,qb->data,&i,compareValue);
				printf("Pb��ʱ��Ӧ�ڵ���Pa�е�λ��%d\n",i);
                SetCurElem(ha,sum,i);
			}else{
				//ɾ��Pa�ж�Ӧ�ڵ�
				LocateElem(ha,qb->data,&i,compareValue);
				printf("ɾ��pa�еĽڵ�:\n");
				ListDelete(Pa,i,&elem);
			}  
			qa=qa->next;
			qb=qb->next;
			ListDelete(Pb,i,&elem);//ע��:��qa=qa->next,qb=qb->next��˳���ܷ�����
			break;
		case 1:
			//��Pb�еĵ�ǰ�ڵ���뵽Pa��
            LocateElem(ha,qb->data,&i,compareValue);//��λPb�ĵ�ǰ�ڵ���Pa��λ��
			printf("Pb�ĵ�ǰ�ڵ�Ӧ���뵽Pa�ĵ�%dλ\n",i);
            ListInsert_L(Pa,i,qb->data);//��Pa��λ�ò���Pb�ĵ�ǰ�ڵ�
			//ɾ��Pb�ĵ�ǰ�ڵ�
            LocateElem(hb,qb->data,&i,compareValue);
			printf("Pb�ĵ�ǰ�ڵ���Pb�еĵ�%dλ\n",i);
			qb=qb->next;
			if(ListDelete(Pb,i,&elem)){
     			printf("ɾ��Pb�ĵ�ǰ�ڵ�\n");
			}		
			break;
		}
	}
	if(!ListEmpty(hb)){
		printf("����Pb��ʣ��ڵ㵽Pa\n");
		//��Pb�е�ʣ��ڵ����Pa��
        Append(Pa,qb);
		//�ͷ�Pb��ͷ���
        free(hb);
	}
}
//17����ɶ���ʽ���������,����16
//18����ɶ���ʽ���������,����16
void main(){
//	LinkList L;
//	printf("����������3�����ϵ����ָ��\n");
//	CreatePolyn(&L,3);
//  ListTraverse(L);
//	DestroyPolyn(&L);
//	printf("������ٲ�����,һԪ���ζ���ʽ:\n");
//	ListTraverse(L);
//	PrintPolyn(L);
//	printf("��ʱһԪ����ʽ��%d����\n",PolynLength(L));
	LinkList Pa,Pb;
    printf("Pa����������2�����ϵ����ָ��\n");
	CreatePolyn(&Pa,2);
	printf("Pb����������2�����ϵ����ָ��\n");
	CreatePolyn(&Pb,2);
	AddPolyn(&Pa,&Pb);
	printf("�����ӡPa:\n");
	PrintPolyn(Pa);
	printf("�����ӡPb:\n");
//	PrintPolyn(Pb);
//	PrintPolyn(Pb);

}

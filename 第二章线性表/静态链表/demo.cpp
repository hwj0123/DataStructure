#include "string.h"
#include "ctype.h"      

#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 1000 /* �洢�ռ��ʼ������ */

typedef int Status;           /* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
typedef char ElemType;        /* ElemType���͸���ʵ������������������Ϊchar */

typedef struct{
	ElemType data;
	int cur;
}component,SLinkList[MAXSIZE];
//1����̬����ĳ�ʼ��,�õ�һ����������
Status InitList(SLinkList s){
	int i;
	for(i=0;i<MAXSIZE-1;i++){
		s[i].cur=i+1;
	}
	s[MAXSIZE-1].cur=0;
	return OK;
}
//2���ӱ���������ȡ��һ���ڵ�
int Malloc_SL(SLinkList s){
	int i;
	i=s[0].cur;
	if(s[0].cur){
		s[0].cur=s[i].cur;
	}
	return i;
}
//3�����±�Ϊk�Ŀ��нڵ���յ���������
void Free_SL(SLinkList s,int k){
	s[k].cur=s[0].cur;
	s[0].cur=k;
}
//4�����ؾ�̬����L��Ԫ�صĸ���
int ListLength(SLinkList L){
	int j=0;
	int i=L[MAXSIZE-1].cur;
	while(i){
		i=L[i].cur;
		j++;
	}
	return j;
}
//5���ھ�̬�����е�i��Ԫ��֮ǰ����Ԫ��e
Status ListInsert(SLinkList L,int i,ElemType e){
	int j,k,l;
	k=MAXSIZE-1;//kָ�����һ���ڵ�
	if(i<1||i>ListLength(L)+1){//����λ�ò�����
		return ERROR;
	}
	j=Malloc_SL(L);//���ط���Ľڵ��±�
	if(j){
		L[j].data=e;
		for(l=1;l<=i-1;l++){//�ҵ���i��Ԫ��֮ǰ��λ��
			k=L[k].cur;
		}
		L[j].cur=L[k].cur;
        L[k].cur=j;
		return OK;
	}
	return ERROR;
}
//6����ӡ��̬����
Status visit(ElemType c,int cur)
{
    printf("%c\t%d\t",c,cur);
    return OK;
}
Status ListTraverse(SLinkList L){
	int j=0;
	int i=L[MAXSIZE-1].cur;
	while(i){
		visit(L[i].data,L[i].cur);
		i=L[i].cur;
		j++;
	}
	return OK;
}
//7���������뼯��A��B��Ԫ��,��һά����s�н�����ʾ����(A-B)U(B-A)
//////���д���!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//void difference(SLinkList s){
//	int m,n,j,i,b,k,p,r,x;
//	InitList(s);
//	x=Malloc_SL(s);
//	r=MAXSIZE-1;//rָ�����һ���ڵ�
//	printf("������A��B��Ԫ�ظ���\n");
//	scanf("%d%d",&m,&n);
//	printf("������A��Ԫ��\n");
//	for(j=1;j<=m;j++){
//        i=Malloc_SL(s);
//		scanf("%d",&s[i].data);
//		s[r].cur=i;
//		r=i;
//	}
//	s[r].cur=0;
//	printf("������B��Ԫ��\n");
//	for(j=1;j<=n;j++){
//		scanf("%d",&b);
//		p=x;
//		k=s[x].cur;
//		while(k!=s[r].cur&&s[k].data!=b){
//			p=k;
//			k=s[k].cur;
//		}
//		if(k==s[r].cur){
//			i=Malloc_SL(s);
//			s[i].data=b;
//			s[i].cur=s[r].cur;
//			s[r].cur=i;
//		}else{
//			s[p].cur=s[k].cur;
//			Free_SL(s,k);
//			if(r==k){
//				r=p;
//			}
//		}
//	}
//}

		




void main(){
	SLinkList L;
	difference(L);
    ListTraverse(L);
//	InitList(L);
//	printf("��̬�����ʼ����,L.length=%d\n",ListLength(L));
//	ListInsert(L,1,'a');
//	ListInsert(L,1,'b');
//	ListInsert(L,1,'c');
//	ListTraverse(L);
//	ListInsert(L,1,'b');
//	ListTraverse(L);

//	ListInsert(L,1,'b');
//	ListInsert(L,1,'c');
//	ListTraverse(L);
//	printf("\n");
//	printf("L.length=%d\n",ListLength(L));
//    Malloc_SL(L);
//    printf("L.length=%d\n",ListLength(L));



}

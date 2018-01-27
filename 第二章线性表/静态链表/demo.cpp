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

#define MAXSIZE 1000 /* 存储空间初始分配量 */

typedef int Status;           /* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef char ElemType;        /* ElemType类型根据实际情况而定，这里假设为char */

typedef struct{
	ElemType data;
	int cur;
}component,SLinkList[MAXSIZE];
//1、静态链表的初始化,得到一个备用链表
Status InitList(SLinkList s){
	int i;
	for(i=0;i<MAXSIZE-1;i++){
		s[i].cur=i+1;
	}
	s[MAXSIZE-1].cur=0;
	return OK;
}
//2、从备用链表中取出一个节点
int Malloc_SL(SLinkList s){
	int i;
	i=s[0].cur;
	if(s[0].cur){
		s[0].cur=s[i].cur;
	}
	return i;
}
//3、将下标为k的空闲节点回收到备用链表
void Free_SL(SLinkList s,int k){
	s[k].cur=s[0].cur;
	s[0].cur=k;
}
//4、返回静态链表L中元素的个数
int ListLength(SLinkList L){
	int j=0;
	int i=L[MAXSIZE-1].cur;
	while(i){
		i=L[i].cur;
		j++;
	}
	return j;
}
//5、在静态链表中第i个元素之前插入元素e
Status ListInsert(SLinkList L,int i,ElemType e){
	int j,k,l;
	k=MAXSIZE-1;//k指向最后一个节点
	if(i<1||i>ListLength(L)+1){//插入位置不合理
		return ERROR;
	}
	j=Malloc_SL(L);//返回分配的节点下标
	if(j){
		L[j].data=e;
		for(l=1;l<=i-1;l++){//找到第i个元素之前的位置
			k=L[k].cur;
		}
		L[j].cur=L[k].cur;
        L[k].cur=j;
		return OK;
	}
	return ERROR;
}
//6、打印静态链表
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
//7、依次输入集合A和B的元素,在一维数组s中建立表示集合(A-B)U(B-A)
//////运行错误!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//void difference(SLinkList s){
//	int m,n,j,i,b,k,p,r,x;
//	InitList(s);
//	x=Malloc_SL(s);
//	r=MAXSIZE-1;//r指向最后一个节点
//	printf("请输入A和B的元素个数\n");
//	scanf("%d%d",&m,&n);
//	printf("请输入A中元素\n");
//	for(j=1;j<=m;j++){
//        i=Malloc_SL(s);
//		scanf("%d",&s[i].data);
//		s[r].cur=i;
//		r=i;
//	}
//	s[r].cur=0;
//	printf("请输入B中元素\n");
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
//	printf("静态链表初始化后,L.length=%d\n",ListLength(L));
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

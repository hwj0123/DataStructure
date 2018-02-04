#include<stdio.h>
#include<stdlib.h>
#define OVERFLOW 0
#define OK 1
typedef int ElemType;
typedef int Status;
typedef struct OLNode{
	int i,j;                //该非零元的行和列下标
	ElemType e;             //该非零元的值
	struct OLNode *right,*down;//该非零元所在行表和列表的后继链域
}OLNode,*OLink;

typedef struct{
	OLink *rhead,*chead;//行和列链表头指针向量基地址有CreateSMatrix分配
	int mu,nu,tu;//稀疏矩阵的行数,列数和非零元的个数
}CrossList;
//创建稀疏矩阵M,采用十字链表的算法
Status CreateSMatrix(CrossList *M){
	int m,n,t,i,j,e;
	OLink p,q;
    if(M){
		free(M);
	}
	printf("请输入M矩阵的行,列和非零元个数\n");
	scanf("%d%d%d",&m,&n,&t);
	M->mu=m;
	M->nu=n;
	M->tu=t;
	if(!(M->rhead=(OLink*)malloc((m+1)*sizeof(OLink)))){
		exit(OVERFLOW);
	}
	if(!(M->chead=(OLink*)malloc((n+1)*sizeof(OLink)))){
		exit(OVERFLOW);
	}
	//初始化行列头指针向量,各行列链表为空链表
	M->rhead=M->chead=NULL;
	//按任意次序输入非零元
	for(scanf("%d%d%d",&i,&j,&e);i!=0;scanf("%d%d%d",&i,&j,&e)){
		if(!(p=(OLNode*)malloc(sizeof(OLNode)))){
			exit(OVERFLOW);
		}
		p->i=i;//生成一个新节点
		p->j=j;
		p->e=e;
		if(M->rhead[i]==NULL||M->rhead[i]->j>j){
			p->right=M->rhead[i];
			M->rhead[i]=p;
		}else{
			for(q=M->rhead[i];(q->right)&&q->right->j<j;q=q->right);//找到行表中合适的插入位置
			p->right=q->right;
			q->right=p;
		}//完成行插入
		if(M->chead[i]==NULL||M->chead[j]->i>i){
			p->down=M->chead[j];
			M->chead[j]=p;
		}else{
			for(q=M->chead[j];(q->down)&&q->down->i<i;q=q->down);//找到列表合适的插入位置
			p->down=q->down;
			q->down=p;
		}//完成列插入
	}
	return OK;




}

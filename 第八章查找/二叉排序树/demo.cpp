#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 100 /* 存储空间初始分配量 */

typedef int Status;	/* Status是函数的类型,其值是函数结果状态代码，如OK等 */

//二叉树链表
typedef struct BiTNode{
	int data;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;
//1、二叉排序树的查找操作
//f指向T的双亲,p指向该数据元素或者指向最后一个节点
Status SearchBST(BiTree T,int key,BiTree f,BiTree *p){
	if(!T){
		*p=f;
		return FALSE;
	}else if(key==T->data){
		*p=T;//p指向该数据元素节点
		return TRUE;
	}else if(key<T->data){
		return SearchBST(T->lchild,key,T,p);
	}else{
		return SearchBST(T->rchild,key,T,p);
	}
}
//2、二叉排序树插入操作
Status InsertBST(BiTree *T,int key){
	BiTree p,s;
	if(!SearchBST(*T,key,NULL,&p)){//不存在该节点
		s=(BiTree)malloc(sizeof(BiTNode));
		s->data=key;
		s->lchild=s->rchild=NULL;
		if(!p){
			*T=s;
		}else if(key<p->data){
			p->lchild=s;//左
		}else{
			p->rchild=s;//右
		}
		return TRUE;
	}else{
		return ERROR;
	}
}

Status Delete(BiTree *p){
	BiTree q,s;
	if((*p)->rchild==NULL){//左子树不为空
		q=*p;
		*p=(*p)->lchild;
		free(q);
	}else if((*p)->lchild==NULL){//右子树不为空
		q=*p;
		*p=(*p)->rchild;
		free(q);
	}else{//找被删除节点的前驱节点替换
		q=*p;
		s=(*p)->lchild;
		while(s->rchild){
			q=s;
			s=s->rchild;
		}
		(*p)->data=s->data;
		if(q!=*p){
			q->rchild=s->lchild;
		}else{
			q->lchild=s->lchild;
		}
		free(s);
	}
	return TRUE;
}
Status DeleteBST(BiTree *T,int key){ 
	if(!*T)
		return FALSE;
	else{
		if (key==(*T)->data)//找到关键字等于key的数据元素删除
			return Delete(T);
		else if (key<(*T)->data)
			return DeleteBST(&(*T)->lchild,key);
		else
			return DeleteBST(&(*T)->rchild,key);
		 
	}
}

void main(){
	int i;
	int a[10]={62,88,58,47,35,73,51,99,37,93};
	BiTree T=NULL;
	
	for(i=0;i<10;i++){
		InsertBST(&T, a[i]);//插入0-10
	}
	DeleteBST(&T,93);
	DeleteBST(&T,47);
    

}
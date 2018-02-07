#include "string.h"
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

typedef int Status;	/* Status是函数的类型,其值是函数结果状态代码,如OK等 */
typedef char TElemType;//节点元素类型为char
typedef enum {Link,Thread} PointerTag;	/* Link==0:指针  Thread==1:线索 */
//二叉树的二叉线索存储表示
typedef struct BiThrNode{
	TElemType data;//节点数据
	struct BiThrNode *lchild,*rchild;//左右孩子指针
	PointerTag LTag;
	PointerTag RTag;//左右标志
}BithrNode,*BiThrTree;
TElemType Nil='#'; /* 以#符为空 */
//访问二叉树中节点
Status visit(TElemType e){
	printf("%c",e);
	return OK;
}
//按照前序来构造二叉线索树
Status CreateBiThrTree(BiThrTree *T){
	TElemType h;
	scanf("%c",&h);
	if(h==Nil){
		*T=NULL;
	}else{
		*T=(BiThrTree)malloc(sizeof(BiThrNode));
		if(!*T){
			exit(OVERFLOW);
		}
		(*T)->data=h;//生成根节点
		CreateBiThrTree(&(*T)->lchild);//构造左子树
		if((*T)->lchild){//有左孩子
			(*T)->LTag=Link;//指针
		}
		CreateBiThrTree(&(*T)->rchild);//构造右子树
		if((*T)->rchild){//有右孩子
			(*T)->RTag=Link;//指针
		}
	}
	return OK;
}
BiThrTree pre;//始终指向刚刚访问过的节点
//中序线索化
void InThreading(BiThrTree p){
	if(p){
		InThreading(p->lchild);//左子树线索化
		if(!p->lchild){//没有左孩子
			p->LTag=Thread;//前驱线索
			p->lchild=pre;//让左孩子指针指向前驱
		}
		if(!pre->rchild){//前驱没有右孩子
			pre->RTag=Thread;//后继线索
			pre->rchild=p;//让前驱的右孩子指针指向当前节点
		}
		pre=p;
		InThreading(p->rchild);//右子树线索化
	}
}
//中序遍历二叉树T,并将其中序线索化,Thrt指向头结点
Status InOrderThreading(BiThrTree *Thrt,BiThrTree T){
	*Thrt=(BiThrTree)malloc(sizeof(BiThrNode));
	if(!*Thrt){
		exit(OVERFLOW);
	}
	//头结点
	(*Thrt)->LTag=Link;//左孩子指向根节点
	(*Thrt)->RTag=Thread;//右孩子指向中序遍历访问时最后一个节点
	(*Thrt)->rchild=(*Thrt);//右指针回指自己
	if(!T){//二叉树为空
		(*Thrt)->lchild=*Thrt;//左指针回指自己
	}else{
		(*Thrt)->lchild=T;//左孩子指向根节点
		pre=(*Thrt);//始终指向刚刚访问过的节点--->根节点
		InThreading(T);//对二叉树进行中序线索化
		pre->rchild=*Thrt;//中序遍历中最后一个节点的右孩子指向头结点
		pre->RTag=Thread;//线索
		(*Thrt)->rchild=pre;//头结点的右孩子指向中序遍历中最后一个节点
	}
	return OK;
}
//中序遍历二叉线索树的非递归算法
Status InOrderTraverse_Thr(BiThrTree T){
	BiThrTree p;
	p=T->lchild;//p指向根节点
	while(p!=T){//空树或者遍历结束时,p==T
		while(p->LTag==Link){
			p=p->lchild;//让p指向其最左的孩子
		}
		if(!visit(p->data)){//访问左孩子
			return ERROR;
		}
		while(p->RTag==Thread&&p->rchild!=T){//右孩子指针指向后继节点
			p=p->rchild;
			visit(p->data);//访问后继元素
		}
		p=p->rchild;
	}
	return OK;
}


void main(){
    BiThrTree H,T;
	printf("请按先序输入二叉树(如:-*a##b##c##)\n");
	CreateBiThrTree(&T);//按先序产生二叉树
	InOrderThreading(&H,T);//中序遍历,并中序线索化二叉树
	printf("中序遍历输出二叉线索树\n");
	InOrderTraverse_Thr(H);//
	printf("\n");
}


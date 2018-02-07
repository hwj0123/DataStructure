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

typedef int Status;

int index=1;
typedef char String[24]; /*  0号单元存放串的长度 */
String str;//str存放了二叉树的元素值

typedef char TElemType;//此二叉树的节点值为字符
TElemType Nil=' '; /* 字符型以空格符为空 */
typedef struct BiTNode  /* 结点结构 */
{
   TElemType data;		/* 结点数据 */
   struct BiTNode *lchild,*rchild; /* 左右孩子指针 */
}BiTNode,*BiTree;
//完成字符串的复制--->将要二叉树节点的值放入String类型的T中
Status StrAssign(String T,char *chars){
	int i;
	if(strlen(chars)>MAXSIZE){
		return ERROR;
	}else{
		T[0]=strlen(chars);
		for(i=1;i<=T[0];i++){
			T[i]=*(chars+i-1);
		}
		return OK;
	}
}
//访问函数
Status visit(TElemType e){
	printf("%c",e);
	return OK;
}

//初始化二叉树
Status InitBiTree(BiTree *T){ 
	*T=NULL;
	return OK;
}
//销毁二叉树T
void DestoryBiTree(BiTree *T){
	if(*T){
		if((*T)->lchild){
			DestoryBiTree(&(*T)->lchild);
		}
		if((*T)->rchild){
			DestoryBiTree(&(*T)->rchild);
		}
		free(*T);
		*T=NULL;
	}
}
//按照先序(根左右)输入二叉树的节点的值
void CreateBiTree(BiTree *T){
	TElemType ch;
	ch=str[index++];
	if(ch=='#'){
		*T=NULL;
	}else{
		*T=(BiTree)malloc(sizeof(BiTNode));
		if(!*T){
			exit(OVERFLOW);
		}
		(*T)->data=ch;//生成根节点
		CreateBiTree(&(*T)->lchild);
		CreateBiTree(&(*T)->rchild);
	}
}
//判断树是否为空
Status BiTreeEmpty(BiTree T){
	if(T){
		return FALSE;
	}else{
		return TRUE;
	}
}
#define ClearBiTree DestroyBiTree//销毁树和清空树一样的操作

//返回二叉树的深度
int BiTreeDepth(BiTree T){
	int i,j;
	if(!T){
		return 0;
	}
	if(T->lchild){
		i=BiTreeDepth(T->lchild);//左子树的深度
	}else{
		i=0;
	}
	if(T->rchild){
		j=BiTreeDepth(T->rchild);//右子树的深度
	}else{
		j=0;
	}
	return i>j?i+1:j+1;//返回左右子树中最大的深度
}
//返回二叉树的根
TElemType Root(BiTree T){
	if(BiTreeEmpty(T)){
		return Nil;
	}else{
		return T->data;
	}
}
//若二叉树T存在,返回p所指节点的值
TElemType Value(BiTree p){
	return p->data;
}
//给p所指节点赋值为value
void Assign(BiTree p,TElemType value){
	p->data=value;
}
//先序遍历二叉树T--->根左右
void PreOrderTraverse(BiTree T){
	if(T==NULL){
		return ;
	}
	printf("%c",T->data);
	PreOrderTraverse(T->lchild);
	PreOrderTraverse(T->rchild);
}
//中序遍历二叉树T--->左根右
void InOrderTraverse(BiTree T){
	if(T==NULL){
		return ;
	}
	InOrderTraverse(T->lchild);
	printf("%c",T->data);
	InOrderTraverse(T->rchild);
}
//后序遍历二叉树T--->左右根
void PostOrderTraverse(BiTree T){
	if(T==NULL){
		return ;
	}
	PostOrderTraverse(T->lchild);
	PostOrderTraverse(T->rchild);
	printf("%c",T->data);
}
//中序遍历二叉树的非递归算法1
/*
Status InOrderTraverse(BiTree T,Status(*Visit)(TElemType e)){
	InitStack(S);
	Push(S,T);//先将根元素入栈
	while(!StackEmpty(S)){
		while(GetTop(S,p)&&p){
			Push(S,p->lchild);//将左孩子节点全都放入
		}
		Pop(S,p);//空指针退出栈
		if(!StackEmpty(S)){
			Pop(S,p);//弹出栈顶元素-->弹出此时最左的孩子节点
			if(!Visit(p->data)){
				return ERROR;
			}
			Push(S,p->rchild);//将右孩子节点放入栈,把它当做新的根节点
		}
	}
	return OK;
}*/
//中序遍历非递归算法2---->与非递归算法1本质上都是模拟递归工作栈的工作流程
//和算法1相比,算法2借助了指针
/*
Status InOrderTraverse(BiTree T,Status(*Visit)(TElemType e)){
	InitStack(S);
	p=T;
	while(p||!StackEmpty(S)){
		if(p){
			Push(S,p);
			p=p->lchild;
		}else{
			Pop(S,p);
			if(!Visit(p->data)){
				return ERROR;
			}
			p=p->rchild;
		}
	}
	return OK;
}*/

void main(){
	int i;
	BiTree T;
	TElemType e1;
	InitBiTree(&T);
	//#表示此节点为空
	//此时str存储着二叉树节点的值
    StrAssign(str,"ABDH#K###E##CFI###G#J##");
    CreateBiTree(&T);
	printf("构造二叉树后,树为空?%d(1:是 0:否) 树深度为%d\n",BiTreeEmpty(T),BiTreeDepth(T));
    printf("\n前序遍历二叉树:");
	PreOrderTraverse(T);
	printf("\n中序遍历二叉树:");
	InOrderTraverse(T);
	printf("\n后序遍历二叉树:");
	PostOrderTraverse(T);
	printf("\n");
	//........略

}

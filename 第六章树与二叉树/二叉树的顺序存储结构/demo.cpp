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
#define MAX_TREE_SIZE 100 /* 二叉树的最大结点数 */

typedef int Status;//状态码
typedef int TElemType;//树节点的数据类型
typedef TElemType SqBiTree[MAX_TREE_SIZE];//0号单元存储根节点

typedef struct{
	int level,order;//节点的层号,本层中的序号
}Position;

TElemType Nil=0;
//访问函数
Status visit(TElemType c){
	printf("%d",c);
	return OK;
}
//构造空二叉树T,因为T是固定数组,不会改变
Status InitBiTree(SqBiTree T){
	int i;
	for(i=0;i<MAX_TREE_SIZE;i++){
		T[i]=Nil;//初始化为0
	}
	return OK;
}
//创建一个二叉树--->完全
Status CreateBiTree(SqBiTree T){
	int i=0;
	//printf("请按层序输入节点的值(整形),0表示空节点,输入999结束,节点数要<=%d\n",MAX_TREE_SIZE);
    while(i<10){
		T[i]=i+1;//自动赋值
		if(i!=0&&T[(i+1)/2-1]==Nil&&T[i]!=Nil){
			printf("出现无双亲的非根节点%d\n",T[i]);
			exit(ERROR);
		}
		i++;
	}
	while(i<MAX_TREE_SIZE){
		T[i]=Nil;//
		i++;
	}
	return OK;
}

#define ClearBiTree InitBiTree//两函数作用相同
//判断二叉树是否为空树
Status BiTreeEmpty(SqBiTree T){
	if(T[0]==Nil){
		return TRUE;
	}else{
		return FALSE;
	}
}
//返回树T的深度--->拥有n个节点的完全二叉树,其深度为log以2为底的n向下取整再加1
int BiTreeDepth(SqBiTree T){
	int i,j=-1;
	for(i=MAX_TREE_SIZE-1;i>=0;i--){
		if(T[i]!=Nil){
			break;
		}
	}
	i++;//此时的i是该完全二叉树T的节点总数
	do{
		j++;
	}while(i>=powl(2,j));//2的j次幂
	return j;
}
//返回完全二叉树T的根
Status Root(SqBiTree T,TElemType *e){
	if(BiTreeEmpty(T)){
		return ERROR;
	}else{
		*e=T[0];
		return OK;
	}
}
//返回完全二叉树T中位于位置e的节点的值
TElemType Value(SqBiTree T,Position e){
	return T[(int)powl(2,e.level-1)+e.order-2];
}
//给完全二叉树的某个位置e的节点赋新值
Status Assign(SqBiTree T,Position e,TElemType value){
	int i=(int)powl(2,e.level-1)+e.order-2;//得到该位置在数组中的下标
	if(value!=Nil&&T[(i+1)/2-1]==Nil){//给叶子节点赋非空值,但双亲为空
		return ERROR;
	}else if(value==Nil&&T[i*2+1]!=Nil||T[i*2+2]!=Nil){//给双亲节点赋空值,但叶子节点非空
		return ERROR;
	}
	T[i]=value;
	return OK;
}
//返回完全二叉树T的e位置上的双亲节点
TElemType Parent(SqBiTree T,TElemType e){
	int i;
	if(T[0]==Nil){//空树
		return Nil;
	}
	for(i=1;i<=MAX_TREE_SIZE-1;i++){
		if(T[i]==e){
			return T[(i+1)/2-1];//找到e位置
		}
	}
	return Nil;
}
//返回完全二叉树T的e位置的左孩子
TElemType LeftChild(SqBiTree T,TElemType e){
	int i;
	if(T[0]==Nil){
		return Nil;
	}
	for(i=0;i<=MAX_TREE_SIZE-1;i++){
		if(T[i]==e){
			return T[i*2+1];
		}
	}
	return Nil;
}
//返回完全二叉树的e位置上的右孩子节点
TElemType RightChild(SqBiTree T,TElemType e){
	int i;
	if(T[0]==Nil){
		return Nil;
	}
	for(i=1;i<=MAX_TREE_SIZE-1;i++){
		if(T[i]==e&&i%2){
			return T[i+1];
		}
	}
	return Nil;
}
//先序遍历---根左右
void PreTraverse(SqBiTree T,int e){
	visit(T[e]);
	if(T[2*e+1]!=Nil){
		PreTraverse(T,2*e+1);
	}
	if(T[2*e+2]!=Nil){
		PreTraverse(T,2*e+2);
	}
}
Status PreOrderTraverse(SqBiTree T){
	if(!BiTreeEmpty(T)){
		PreTraverse(T,0);
	}
	printf("\n");
	return OK;
}
//中序遍历---左根右
void InTraverse(SqBiTree T,int e){
	if(T[2*e+1]!=Nil){
		InTraverse(T,2*e+1);//左子树不为空
	}
	if(T[2*e+2]!=Nil){
		InTraverse(T,2*e+2);//右子树不空
	}
	visit(T[e]);

}
Status InOrderTraverse(SqBiTree T){
	if(!BiTreeEmpty(T)){
		InTraverse(T,0);
	}
	printf("\n");
	return OK;
}
//后序遍历--->左右根
void PostTraverse(SqBiTree T,int e){
	if(T[2*e+1]!=Nil){
		PostTraverse(T,2*e+1);
	}
	if(T[2*e+2]!=Nil){
		PostTraverse(T,2*e+2);
	}
	visit(T[e]);
}
Status PostOrderTraverse(SqBiTree T){
	if(!BiTreeEmpty(T)){
		PostTraverse(T,0);
	}
	printf("\n");
	return OK;
}
//层序遍历完全二叉树T
void LevelOrderTraverse(SqBiTree T){
	int i=MAX_TREE_SIZE-1,j;
	while(T[i]==Nil){
		i--;//找到最后一个非空节点
	}
	for(j=0;j<=i;j++){//从根节点开始,按照层序遍历的顺序来遍历二叉树
		if(T[j]!=Nil){
			visit(T[j]);
		}
	}
	printf("\n");
}
//逐层,按本层序号输出完全二叉树
void Print(SqBiTree T){
	int j,k;
	Position p;
	TElemType e;
	for(j=1;j<=BiTreeDepth(T);j++){
		printf("第%d层:",j);
		for(k=1;k<=pow(2,j-1);k++){
			p.level=j;
			p.order=k;
			e=Value(T,p);
			if(e!=Nil){
				printf("%d:%d",k,e);
			}
		}
		printf("\n");
	}
}

void main(){
	Status i;
	Position p;
	TElemType e;
	SqBiTree T;
	InitBiTree(T);
	CreateBiTree(T);
	printf("建立二叉树后,树空?%d(1:是 0:否) 树的深度=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
    i=Root(T,&e);
	if(i){
		printf("二叉树的根为:%d\n",i);
	}else{
		printf("树为空\n");
	}
	printf("层序遍历二叉树:\n");
	LevelOrderTraverse(T);
	printf("前序遍历二叉树:\n");
	PreOrderTraverse(T);
	printf("中序遍历二叉树:\n");
	InOrderTraverse(T);
	printf("后序遍历二叉树:\n");
	PostOrderTraverse(T);
	///.................略
}

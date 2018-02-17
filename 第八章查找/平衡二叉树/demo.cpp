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

#define LH +1//左高
#define EH 0//等高
#define RH -1//右高
typedef int Status;	/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
//二叉树链表结构
typedef struct BiTNode{
	int data;//节点数据
	int bf;//节点的平衡因子
	struct BiTNode *lchild,*rchild;//左右孩子
}BiTNode,*BiTree;

/**********************************算法实现*********************/
//1、对以p为根的二叉排序树做右旋处理,处理后p指向新的树根节点
void R_Rotate(BiTree *P){
	BiTree L;
	L=(*P)->lchild;
	(*P)->lchild=L->rchild;
	L->rchild=(*P);
	*P=L;//P指向新的根节点
}
//2、对以p为根的二叉排序树做左旋处理,处理后p指向新的树根节点
void L_Rotate(BiTree *P){
	BiTree R;
	R=(*P)->rchild;
	(*P)->rchild=R->lchild;
	R->lchild=(*P);
	*P=R;
}
//3、最T所指节点为根的二叉树做左平衡旋转处理
void LeftBalance(BiTree *T){
	BiTree L,Lr;
	L=(*T)->lchild;
	switch(L->bf){
	case LH:
		//新节点插入到T的左孩子的左子树上,做单右旋处理
		(*T)->bf=L->bf=EH;
		R_Rotate(T);
		break;
	case RH:
		//新节点插入到T的左孩子的右子树上,做双旋处理
		Lr=L->rchild;
		switch(Lr->bf){
		case LH:
			(*T)->bf=RH;
			L->bf=EH;
			break;
		case EH:
			(*T)->bf=L->bf=EH;
			break;
		case RH:
			(*T)->bf=EH;
			L->bf=LH;
			break;
		}
		Lr->bf=EH;
		L_Rotate(&(*T)->lchild);//对T的左子树做左旋平衡处理
		R_Rotate(T);//对T做右旋处理
	}
}
//4、对T所指节点为根的二叉树做右平衡旋转处理
void RightBalance(BiTree *T){
	BiTree R,R1;
	R=(*T)->rchild;
	switch(R->bf){
	case RH:
		(*T)->bf=R->bf=EH;
		L_Rotate(T);
		break;
	case LH:
		R1=R->lchild;
		switch(R1->bf){
		case RH:
			(*T)->bf=LH;
			R->bf=EH;
			break;
		case EH:
			(*T)->bf=R->bf=EH;
			break;
		case LH:
			(*T)->bf=EH;
			R->bf=RH;
			break;
		}
		R1->bf=EH;
		R_Rotate(&(*T)->rchild);//对T的右子树进行右旋平衡
		L_Rotate(T);//对T做左旋平衡
	}
}
//5、向平衡二叉树T中插入元素e，如果因插入元素e使得
//失去了平衡,则做相应的平衡旋转处理，taller反映二叉树T
//长高与否
Status InsertAVL(BiTree *T,int e,Status *taller){
	if(!*T){//没有找到相应的节点，插入
		*T=(BiTree)malloc(sizeof(BiTNode));
		(*T)->data=e;
		(*T)->lchild=(*T)->rchild=NULL;
		(*T)->bf=EH;
		*taller=TRUE;
	}else{
		if(e==(*T)->data){
			*taller=FALSE;
			return FALSE;//找到了一样的,返回FALSE
		}
		if(e<(*T)->data){
			//在左子树中寻找
			if(!InsertAVL(&(*T)->lchild,e,taller)){
				return FALSE;
			}
			if(*taller){//已插入到左子树中,且taller为正
				switch((*T)->bf){
				case LH://原来左子树高---->不平衡
					LeftBalance(T);
					*taller=FALSE;
					break;
				case EH://原来左右子树相等---->现在左高
					(*T)->bf=LH;
					*taller=TRUE;
					break;
				case RH://原来右子树高--->现在等高
					(*T)->bf=EH;
					*taller=FALSE;
					break;
				}
			}
		}else{
			if(!InsertAVL(&(*T)->rchild,e,taller)){
				return FALSE;
			}
			if(*taller){
				switch((*T)->bf){
				case LH:
					(*T)->bf=EH;
					*taller=FALSE;
					break;
				case EH:
					(*T)->bf=RH;
					*taller=TRUE;
					break;
				case RH:
					RightBalance(T);
					*taller=FALSE;
					break;
				}
			}
		}
	}
	return TRUE;
}
//6、中序
void InOrderTraverse(BiTree T){
	if(T==NULL){
		return ;
	}
	InOrderTraverse(T->lchild);
	printf("%d\t",T->data);
	InOrderTraverse(T->rchild);
}
/********************************测试*************************/
void main(){
	int i;
	int a[10]={3,2,1,4,5,6,7,10,9,8};
	BiTree T=NULL;
	Status taller;
	for(i=0;i<10;i++){
		InsertAVL(&T,a[i],&taller);
	}
	InOrderTraverse(T);
	printf("\n");
}













#include<stdio.h>
#include<stdlib.h>
#define OK 1
typedef int AtomType;
typedef int Status;
typedef enum{ATOM,LIST}ElemTag;//ATOM==0:原子,LIST==1:子表(枚举类型)
typedef struct GLNode{
	ElemTag tag;//公共部分,用于区分原子结点和表结点
	union{//原子结点和表结点的结合部分
		AtomType atom;//atom是原子结点的值域,AtomType由用户定义
		struct{struct GLNode *hp,*tp;} ptr;//ptr是表节点的指针域,ptr.hp和ptr.tp分别指向表头和表尾
	};
}*GList;//广义表类型

//采用头尾链表存储结构,求广义表L的深度
int GListDepth(GList L){
	int max;
	int dep=0;
	GList pp;
	if(!L){
		return 1;//空表的深度为1
	}
	if(L->tag==ATOM){
		return 0;//原子深度为0
	}
	for(max=0,pp=L;pp;pp=pp->ptr.tp){
		dep=GListDepth(pp->ptr.hp);//求以pp->ptr.hp为头指针的子表的深度
		if(dep>max){
			max=dep;//
		}
	}
	return max+1;//非空表的深度是各元素的深度的最大值+1
}

//由广义表L复制得到广义表T
Status CopyGList(GList *T,GList L){
	if(!L){
		*T=NULL;//L为空表,则让T为空
	}else{
		if(!(*T=(GList)malloc(sizeof(GLNode)))){//创建表头节点
			exit(0);
		}
		(*T)->tag=L->tag;
		if(L->tag==ATOM){
			(*T)->atom=L->atom;//复制单原子
		}else{
			CopyGList(&(*T)->ptr.hp,L->ptr.hp);//复制广义表的L->ptr.hp
			CopyGList(&(*T)->ptr.tp,L->ptr.tp);//复制广义表的L->ptr.tp
		}
	}
	return OK;
}

//略算法5.7,5.8
void main(){
}
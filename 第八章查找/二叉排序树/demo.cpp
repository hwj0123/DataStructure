#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 100 /* �洢�ռ��ʼ������ */

typedef int Status;	/* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */

//����������
typedef struct BiTNode{
	int data;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;
//1�������������Ĳ��Ҳ���
//fָ��T��˫��,pָ�������Ԫ�ػ���ָ�����һ���ڵ�
Status SearchBST(BiTree T,int key,BiTree f,BiTree *p){
	if(!T){
		*p=f;
		return FALSE;
	}else if(key==T->data){
		*p=T;//pָ�������Ԫ�ؽڵ�
		return TRUE;
	}else if(key<T->data){
		return SearchBST(T->lchild,key,T,p);
	}else{
		return SearchBST(T->rchild,key,T,p);
	}
}
//2�������������������
Status InsertBST(BiTree *T,int key){
	BiTree p,s;
	if(!SearchBST(*T,key,NULL,&p)){//�����ڸýڵ�
		s=(BiTree)malloc(sizeof(BiTNode));
		s->data=key;
		s->lchild=s->rchild=NULL;
		if(!p){
			*T=s;
		}else if(key<p->data){
			p->lchild=s;//��
		}else{
			p->rchild=s;//��
		}
		return TRUE;
	}else{
		return ERROR;
	}
}

Status Delete(BiTree *p){
	BiTree q,s;
	if((*p)->rchild==NULL){//��������Ϊ��
		q=*p;
		*p=(*p)->lchild;
		free(q);
	}else if((*p)->lchild==NULL){//��������Ϊ��
		q=*p;
		*p=(*p)->rchild;
		free(q);
	}else{//�ұ�ɾ���ڵ��ǰ���ڵ��滻
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
		if (key==(*T)->data)//�ҵ��ؼ��ֵ���key������Ԫ��ɾ��
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
		InsertBST(&T, a[i]);//����0-10
	}
	DeleteBST(&T,93);
	DeleteBST(&T,47);
    

}
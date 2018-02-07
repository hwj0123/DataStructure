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

#define MAXSIZE 100 /* �洢�ռ��ʼ������ */

typedef int Status;	/* Status�Ǻ���������,��ֵ�Ǻ������״̬����,��OK�� */
typedef char TElemType;//�ڵ�Ԫ������Ϊchar
typedef enum {Link,Thread} PointerTag;	/* Link==0:ָ��  Thread==1:���� */
//�������Ķ��������洢��ʾ
typedef struct BiThrNode{
	TElemType data;//�ڵ�����
	struct BiThrNode *lchild,*rchild;//���Һ���ָ��
	PointerTag LTag;
	PointerTag RTag;//���ұ�־
}BithrNode,*BiThrTree;
TElemType Nil='#'; /* ��#��Ϊ�� */
//���ʶ������нڵ�
Status visit(TElemType e){
	printf("%c",e);
	return OK;
}
//����ǰ�����������������
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
		(*T)->data=h;//���ɸ��ڵ�
		CreateBiThrTree(&(*T)->lchild);//����������
		if((*T)->lchild){//������
			(*T)->LTag=Link;//ָ��
		}
		CreateBiThrTree(&(*T)->rchild);//����������
		if((*T)->rchild){//���Һ���
			(*T)->RTag=Link;//ָ��
		}
	}
	return OK;
}
BiThrTree pre;//ʼ��ָ��ոշ��ʹ��Ľڵ�
//����������
void InThreading(BiThrTree p){
	if(p){
		InThreading(p->lchild);//������������
		if(!p->lchild){//û������
			p->LTag=Thread;//ǰ������
			p->lchild=pre;//������ָ��ָ��ǰ��
		}
		if(!pre->rchild){//ǰ��û���Һ���
			pre->RTag=Thread;//�������
			pre->rchild=p;//��ǰ�����Һ���ָ��ָ��ǰ�ڵ�
		}
		pre=p;
		InThreading(p->rchild);//������������
	}
}
//�������������T,����������������,Thrtָ��ͷ���
Status InOrderThreading(BiThrTree *Thrt,BiThrTree T){
	*Thrt=(BiThrTree)malloc(sizeof(BiThrNode));
	if(!*Thrt){
		exit(OVERFLOW);
	}
	//ͷ���
	(*Thrt)->LTag=Link;//����ָ����ڵ�
	(*Thrt)->RTag=Thread;//�Һ���ָ�������������ʱ���һ���ڵ�
	(*Thrt)->rchild=(*Thrt);//��ָ���ָ�Լ�
	if(!T){//������Ϊ��
		(*Thrt)->lchild=*Thrt;//��ָ���ָ�Լ�
	}else{
		(*Thrt)->lchild=T;//����ָ����ڵ�
		pre=(*Thrt);//ʼ��ָ��ոշ��ʹ��Ľڵ�--->���ڵ�
		InThreading(T);//�Զ�������������������
		pre->rchild=*Thrt;//������������һ���ڵ���Һ���ָ��ͷ���
		pre->RTag=Thread;//����
		(*Thrt)->rchild=pre;//ͷ�����Һ���ָ��������������һ���ڵ�
	}
	return OK;
}
//������������������ķǵݹ��㷨
Status InOrderTraverse_Thr(BiThrTree T){
	BiThrTree p;
	p=T->lchild;//pָ����ڵ�
	while(p!=T){//�������߱�������ʱ,p==T
		while(p->LTag==Link){
			p=p->lchild;//��pָ��������ĺ���
		}
		if(!visit(p->data)){//��������
			return ERROR;
		}
		while(p->RTag==Thread&&p->rchild!=T){//�Һ���ָ��ָ���̽ڵ�
			p=p->rchild;
			visit(p->data);//���ʺ��Ԫ��
		}
		p=p->rchild;
	}
	return OK;
}


void main(){
    BiThrTree H,T;
	printf("�밴�������������(��:-*a##b##c##)\n");
	CreateBiThrTree(&T);//���������������
	InOrderThreading(&H,T);//�������,������������������
	printf("��������������������\n");
	InOrderTraverse_Thr(H);//
	printf("\n");
}


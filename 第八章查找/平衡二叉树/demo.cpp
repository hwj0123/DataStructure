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

#define LH +1//���
#define EH 0//�ȸ�
#define RH -1//�Ҹ�
typedef int Status;	/* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
//����������ṹ
typedef struct BiTNode{
	int data;//�ڵ�����
	int bf;//�ڵ��ƽ������
	struct BiTNode *lchild,*rchild;//���Һ���
}BiTNode,*BiTree;

/**********************************�㷨ʵ��*********************/
//1������pΪ���Ķ�������������������,�����pָ���µ������ڵ�
void R_Rotate(BiTree *P){
	BiTree L;
	L=(*P)->lchild;
	(*P)->lchild=L->rchild;
	L->rchild=(*P);
	*P=L;//Pָ���µĸ��ڵ�
}
//2������pΪ���Ķ�������������������,�����pָ���µ������ڵ�
void L_Rotate(BiTree *P){
	BiTree R;
	R=(*P)->rchild;
	(*P)->rchild=R->lchild;
	R->lchild=(*P);
	*P=R;
}
//3����T��ָ�ڵ�Ϊ���Ķ���������ƽ����ת����
void LeftBalance(BiTree *T){
	BiTree L,Lr;
	L=(*T)->lchild;
	switch(L->bf){
	case LH:
		//�½ڵ���뵽T�����ӵ���������,������������
		(*T)->bf=L->bf=EH;
		R_Rotate(T);
		break;
	case RH:
		//�½ڵ���뵽T�����ӵ���������,��˫������
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
		L_Rotate(&(*T)->lchild);//��T��������������ƽ�⴦��
		R_Rotate(T);//��T����������
	}
}
//4����T��ָ�ڵ�Ϊ���Ķ���������ƽ����ת����
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
		R_Rotate(&(*T)->rchild);//��T����������������ƽ��
		L_Rotate(T);//��T������ƽ��
	}
}
//5����ƽ�������T�в���Ԫ��e����������Ԫ��eʹ��
//ʧȥ��ƽ��,������Ӧ��ƽ����ת����taller��ӳ������T
//�������
Status InsertAVL(BiTree *T,int e,Status *taller){
	if(!*T){//û���ҵ���Ӧ�Ľڵ㣬����
		*T=(BiTree)malloc(sizeof(BiTNode));
		(*T)->data=e;
		(*T)->lchild=(*T)->rchild=NULL;
		(*T)->bf=EH;
		*taller=TRUE;
	}else{
		if(e==(*T)->data){
			*taller=FALSE;
			return FALSE;//�ҵ���һ����,����FALSE
		}
		if(e<(*T)->data){
			//����������Ѱ��
			if(!InsertAVL(&(*T)->lchild,e,taller)){
				return FALSE;
			}
			if(*taller){//�Ѳ��뵽��������,��tallerΪ��
				switch((*T)->bf){
				case LH://ԭ����������---->��ƽ��
					LeftBalance(T);
					*taller=FALSE;
					break;
				case EH://ԭ�������������---->�������
					(*T)->bf=LH;
					*taller=TRUE;
					break;
				case RH://ԭ����������--->���ڵȸ�
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
//6������
void InOrderTraverse(BiTree T){
	if(T==NULL){
		return ;
	}
	InOrderTraverse(T->lchild);
	printf("%d\t",T->data);
	InOrderTraverse(T->rchild);
}
/********************************����*************************/
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













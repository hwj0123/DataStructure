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

typedef int Status;

int index=1;
typedef char String[24]; /*  0�ŵ�Ԫ��Ŵ��ĳ��� */
String str;//str����˶�������Ԫ��ֵ

typedef char TElemType;//�˶������Ľڵ�ֵΪ�ַ�
TElemType Nil=' '; /* �ַ����Կո��Ϊ�� */
typedef struct BiTNode  /* ���ṹ */
{
   TElemType data;		/* ������� */
   struct BiTNode *lchild,*rchild; /* ���Һ���ָ�� */
}BiTNode,*BiTree;
//����ַ����ĸ���--->��Ҫ�������ڵ��ֵ����String���͵�T��
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
//���ʺ���
Status visit(TElemType e){
	printf("%c",e);
	return OK;
}

//��ʼ��������
Status InitBiTree(BiTree *T){ 
	*T=NULL;
	return OK;
}
//���ٶ�����T
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
//��������(������)����������Ľڵ��ֵ
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
		(*T)->data=ch;//���ɸ��ڵ�
		CreateBiTree(&(*T)->lchild);
		CreateBiTree(&(*T)->rchild);
	}
}
//�ж����Ƿ�Ϊ��
Status BiTreeEmpty(BiTree T){
	if(T){
		return FALSE;
	}else{
		return TRUE;
	}
}
#define ClearBiTree DestroyBiTree//�������������һ���Ĳ���

//���ض����������
int BiTreeDepth(BiTree T){
	int i,j;
	if(!T){
		return 0;
	}
	if(T->lchild){
		i=BiTreeDepth(T->lchild);//�����������
	}else{
		i=0;
	}
	if(T->rchild){
		j=BiTreeDepth(T->rchild);//�����������
	}else{
		j=0;
	}
	return i>j?i+1:j+1;//���������������������
}
//���ض������ĸ�
TElemType Root(BiTree T){
	if(BiTreeEmpty(T)){
		return Nil;
	}else{
		return T->data;
	}
}
//��������T����,����p��ָ�ڵ��ֵ
TElemType Value(BiTree p){
	return p->data;
}
//��p��ָ�ڵ㸳ֵΪvalue
void Assign(BiTree p,TElemType value){
	p->data=value;
}
//�������������T--->������
void PreOrderTraverse(BiTree T){
	if(T==NULL){
		return ;
	}
	printf("%c",T->data);
	PreOrderTraverse(T->lchild);
	PreOrderTraverse(T->rchild);
}
//�������������T--->�����
void InOrderTraverse(BiTree T){
	if(T==NULL){
		return ;
	}
	InOrderTraverse(T->lchild);
	printf("%c",T->data);
	InOrderTraverse(T->rchild);
}
//�������������T--->���Ҹ�
void PostOrderTraverse(BiTree T){
	if(T==NULL){
		return ;
	}
	PostOrderTraverse(T->lchild);
	PostOrderTraverse(T->rchild);
	printf("%c",T->data);
}
//��������������ķǵݹ��㷨1
/*
Status InOrderTraverse(BiTree T,Status(*Visit)(TElemType e)){
	InitStack(S);
	Push(S,T);//�Ƚ���Ԫ����ջ
	while(!StackEmpty(S)){
		while(GetTop(S,p)&&p){
			Push(S,p->lchild);//�����ӽڵ�ȫ������
		}
		Pop(S,p);//��ָ���˳�ջ
		if(!StackEmpty(S)){
			Pop(S,p);//����ջ��Ԫ��-->������ʱ����ĺ��ӽڵ�
			if(!Visit(p->data)){
				return ERROR;
			}
			Push(S,p->rchild);//���Һ��ӽڵ����ջ,���������µĸ��ڵ�
		}
	}
	return OK;
}*/
//��������ǵݹ��㷨2---->��ǵݹ��㷨1�����϶���ģ��ݹ鹤��ջ�Ĺ�������
//���㷨1���,�㷨2������ָ��
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
	//#��ʾ�˽ڵ�Ϊ��
	//��ʱstr�洢�Ŷ������ڵ��ֵ
    StrAssign(str,"ABDH#K###E##CFI###G#J##");
    CreateBiTree(&T);
	printf("�����������,��Ϊ��?%d(1:�� 0:��) �����Ϊ%d\n",BiTreeEmpty(T),BiTreeDepth(T));
    printf("\nǰ�����������:");
	PreOrderTraverse(T);
	printf("\n�������������:");
	InOrderTraverse(T);
	printf("\n�������������:");
	PostOrderTraverse(T);
	printf("\n");
	//........��

}

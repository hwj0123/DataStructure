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
#define MAX_TREE_SIZE 100 /* ��������������� */

typedef int Status;//״̬��
typedef int TElemType;//���ڵ����������
typedef TElemType SqBiTree[MAX_TREE_SIZE];//0�ŵ�Ԫ�洢���ڵ�

typedef struct{
	int level,order;//�ڵ�Ĳ��,�����е����
}Position;

TElemType Nil=0;
//���ʺ���
Status visit(TElemType c){
	printf("%d",c);
	return OK;
}
//����ն�����T,��ΪT�ǹ̶�����,����ı�
Status InitBiTree(SqBiTree T){
	int i;
	for(i=0;i<MAX_TREE_SIZE;i++){
		T[i]=Nil;//��ʼ��Ϊ0
	}
	return OK;
}
//����һ��������--->��ȫ
Status CreateBiTree(SqBiTree T){
	int i=0;
	//printf("�밴��������ڵ��ֵ(����),0��ʾ�սڵ�,����999����,�ڵ���Ҫ<=%d\n",MAX_TREE_SIZE);
    while(i<10){
		T[i]=i+1;//�Զ���ֵ
		if(i!=0&&T[(i+1)/2-1]==Nil&&T[i]!=Nil){
			printf("������˫�׵ķǸ��ڵ�%d\n",T[i]);
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

#define ClearBiTree InitBiTree//������������ͬ
//�ж϶������Ƿ�Ϊ����
Status BiTreeEmpty(SqBiTree T){
	if(T[0]==Nil){
		return TRUE;
	}else{
		return FALSE;
	}
}
//������T�����--->ӵ��n���ڵ����ȫ������,�����Ϊlog��2Ϊ�׵�n����ȡ���ټ�1
int BiTreeDepth(SqBiTree T){
	int i,j=-1;
	for(i=MAX_TREE_SIZE-1;i>=0;i--){
		if(T[i]!=Nil){
			break;
		}
	}
	i++;//��ʱ��i�Ǹ���ȫ������T�Ľڵ�����
	do{
		j++;
	}while(i>=powl(2,j));//2��j����
	return j;
}
//������ȫ������T�ĸ�
Status Root(SqBiTree T,TElemType *e){
	if(BiTreeEmpty(T)){
		return ERROR;
	}else{
		*e=T[0];
		return OK;
	}
}
//������ȫ������T��λ��λ��e�Ľڵ��ֵ
TElemType Value(SqBiTree T,Position e){
	return T[(int)powl(2,e.level-1)+e.order-2];
}
//����ȫ��������ĳ��λ��e�Ľڵ㸳��ֵ
Status Assign(SqBiTree T,Position e,TElemType value){
	int i=(int)powl(2,e.level-1)+e.order-2;//�õ���λ���������е��±�
	if(value!=Nil&&T[(i+1)/2-1]==Nil){//��Ҷ�ӽڵ㸳�ǿ�ֵ,��˫��Ϊ��
		return ERROR;
	}else if(value==Nil&&T[i*2+1]!=Nil||T[i*2+2]!=Nil){//��˫�׽ڵ㸳��ֵ,��Ҷ�ӽڵ�ǿ�
		return ERROR;
	}
	T[i]=value;
	return OK;
}
//������ȫ������T��eλ���ϵ�˫�׽ڵ�
TElemType Parent(SqBiTree T,TElemType e){
	int i;
	if(T[0]==Nil){//����
		return Nil;
	}
	for(i=1;i<=MAX_TREE_SIZE-1;i++){
		if(T[i]==e){
			return T[(i+1)/2-1];//�ҵ�eλ��
		}
	}
	return Nil;
}
//������ȫ������T��eλ�õ�����
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
//������ȫ��������eλ���ϵ��Һ��ӽڵ�
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
//�������---������
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
//�������---�����
void InTraverse(SqBiTree T,int e){
	if(T[2*e+1]!=Nil){
		InTraverse(T,2*e+1);//��������Ϊ��
	}
	if(T[2*e+2]!=Nil){
		InTraverse(T,2*e+2);//����������
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
//�������--->���Ҹ�
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
//���������ȫ������T
void LevelOrderTraverse(SqBiTree T){
	int i=MAX_TREE_SIZE-1,j;
	while(T[i]==Nil){
		i--;//�ҵ����һ���ǿսڵ�
	}
	for(j=0;j<=i;j++){//�Ӹ��ڵ㿪ʼ,���ղ��������˳��������������
		if(T[j]!=Nil){
			visit(T[j]);
		}
	}
	printf("\n");
}
//���,��������������ȫ������
void Print(SqBiTree T){
	int j,k;
	Position p;
	TElemType e;
	for(j=1;j<=BiTreeDepth(T);j++){
		printf("��%d��:",j);
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
	printf("������������,����?%d(1:�� 0:��) �������=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
    i=Root(T,&e);
	if(i){
		printf("�������ĸ�Ϊ:%d\n",i);
	}else{
		printf("��Ϊ��\n");
	}
	printf("�������������:\n");
	LevelOrderTraverse(T);
	printf("ǰ�����������:\n");
	PreOrderTraverse(T);
	printf("�������������:\n");
	InOrderTraverse(T);
	printf("�������������:\n");
	PostOrderTraverse(T);
	///.................��
}

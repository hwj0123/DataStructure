#include<stdio.h>
#include<stdlib.h>
#define OVERFLOW 0
#define OK 1
typedef int ElemType;
typedef int Status;
typedef struct OLNode{
	int i,j;                //�÷���Ԫ���к����±�
	ElemType e;             //�÷���Ԫ��ֵ
	struct OLNode *right,*down;//�÷���Ԫ�����б���б�ĺ������
}OLNode,*OLink;

typedef struct{
	OLink *rhead,*chead;//�к�������ͷָ����������ַ��CreateSMatrix����
	int mu,nu,tu;//ϡ����������,�����ͷ���Ԫ�ĸ���
}CrossList;
//����ϡ�����M,����ʮ��������㷨
Status CreateSMatrix(CrossList *M){
	int m,n,t,i,j,e;
	OLink p,q;
    if(M){
		free(M);
	}
	printf("������M�������,�кͷ���Ԫ����\n");
	scanf("%d%d%d",&m,&n,&t);
	M->mu=m;
	M->nu=n;
	M->tu=t;
	if(!(M->rhead=(OLink*)malloc((m+1)*sizeof(OLink)))){
		exit(OVERFLOW);
	}
	if(!(M->chead=(OLink*)malloc((n+1)*sizeof(OLink)))){
		exit(OVERFLOW);
	}
	//��ʼ������ͷָ������,����������Ϊ������
	M->rhead=M->chead=NULL;
	//����������������Ԫ
	for(scanf("%d%d%d",&i,&j,&e);i!=0;scanf("%d%d%d",&i,&j,&e)){
		if(!(p=(OLNode*)malloc(sizeof(OLNode)))){
			exit(OVERFLOW);
		}
		p->i=i;//����һ���½ڵ�
		p->j=j;
		p->e=e;
		if(M->rhead[i]==NULL||M->rhead[i]->j>j){
			p->right=M->rhead[i];
			M->rhead[i]=p;
		}else{
			for(q=M->rhead[i];(q->right)&&q->right->j<j;q=q->right);//�ҵ��б��к��ʵĲ���λ��
			p->right=q->right;
			q->right=p;
		}//����в���
		if(M->chead[i]==NULL||M->chead[j]->i>i){
			p->down=M->chead[j];
			M->chead[j]=p;
		}else{
			for(q=M->chead[j];(q->down)&&q->down->i<i;q=q->down);//�ҵ��б���ʵĲ���λ��
			p->down=q->down;
			q->down=p;
		}//����в���
	}
	return OK;




}

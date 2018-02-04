#include<stdio.h>
#define MAXSIZE 12500//����Ԫ���������ֵ��12500
#define OK 1
typedef int ElemType;
typedef int Status;
typedef struct{
	int i,j;//����
	ElemType e;//����Ԫ��ֵ
}Triple;
typedef struct{
	Triple data[MAXSIZE+1];//����Ԫ��Ԫ���,data[0]����
	int mu,nu,tu;//���������,����,����Ԫ�ĸ���
}TSMatrix;
//������Ԫ���洢��ʾ,��ϡ�����M��ת�þ���T
//1�����վ���M������������ת��
Status TransposeSMatrix(TSMatrix M,TSMatrix *T){
	int q,p,col;
	T->mu=M.nu;
	T->nu=M.mu;
	T->tu=M.tu;
	if(T->tu){
		q=1;
		for(col=1;col<=M.nu;col++){//��
			for(p=1;p<=M.tu;p++){//����Ԫ����
				if(M.data[p].j==col){
					T->data[q].i=M.data[p].j;
					T->data[q].j=M.data[p].i;
					T->data[q].e=M.data[p].e;
					q++;
				}
			}
		}
	}
	return OK;
}
//2������ת��
Status FastTransposeSMatrix(TSMatrix M,TSMatrix *T){
	T->mu=M.nu;
	T->nu=M.mu;
	T->tu=M.tu;
	//num[j]��ʾ��j����������Ԫ�ĸ���,cpot[col]��ʾ��col�еĵ�һ������Ԫ��b.data�е�λ��
	int num[MAXSIZE],col,t,cpot[MAXSIZE],p,q;//int num[M.nu]����?��ʹ��MAXSIZE
	if(T->tu){
		for(col=1;col<=M.nu;col++){
			num[col]=0;
		}
		for(t=1;t<=M.tu;t++){
			num[M.data[t].j]++;//��M������ÿһ�з���Ԫ�ĸ���
		}
		cpot[1]=1;
		for(col=2;col<=M.nu;col++){
			cpot[col]=cpot[col-1]+num[col-1];//��M����ÿ�е�һ������Ԫ��b.data�е�λ��
		}
		for(p=1;p<=M.tu;p++){//��������M�еķ���Ԫ
			col=M.data[p].j;
			q=cpot[col];//q�����col�е�һ������Ԫ��b.data�е�λ��
			T->data[q].i=M.data[p].j;
			T->data[q].j=M.data[p].i;
			T->data[q].e=M.data[p].e;
			cpot[col]++;//++���������һ������Ԫλ�ڵ�һ������Ԫ֮��
		}
	}
	return OK;
}



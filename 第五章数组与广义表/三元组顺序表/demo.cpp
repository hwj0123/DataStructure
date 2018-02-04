#include<stdio.h>
#define MAXSIZE 12500//非零元个数的最大值是12500
#define OK 1
typedef int ElemType;
typedef int Status;
typedef struct{
	int i,j;//行列
	ElemType e;//非零元的值
}Triple;
typedef struct{
	Triple data[MAXSIZE+1];//非零元三元组表,data[0]不用
	int mu,nu,tu;//矩阵的行数,列数,非零元的个数
}TSMatrix;
//采用三元组表存储表示,求稀疏矩阵M的转置矩阵T
//1、按照矩阵M的列序来进行转置
Status TransposeSMatrix(TSMatrix M,TSMatrix *T){
	int q,p,col;
	T->mu=M.nu;
	T->nu=M.mu;
	T->tu=M.tu;
	if(T->tu){
		q=1;
		for(col=1;col<=M.nu;col++){//列
			for(p=1;p<=M.tu;p++){//非零元个数
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
//2、快速转置
Status FastTransposeSMatrix(TSMatrix M,TSMatrix *T){
	T->mu=M.nu;
	T->nu=M.mu;
	T->tu=M.tu;
	//num[j]表示第j列所含非零元的个数,cpot[col]表示第col列的第一个非零元在b.data中的位置
	int num[MAXSIZE],col,t,cpot[MAXSIZE],p,q;//int num[M.nu]报错?故使用MAXSIZE
	if(T->tu){
		for(col=1;col<=M.nu;col++){
			num[col]=0;
		}
		for(t=1;t<=M.tu;t++){
			num[M.data[t].j]++;//求M矩阵中每一列非零元的个数
		}
		cpot[1]=1;
		for(col=2;col<=M.nu;col++){
			cpot[col]=cpot[col-1]+num[col-1];//求M矩阵每列第一个非零元在b.data中的位置
		}
		for(p=1;p<=M.tu;p++){//遍历矩阵M中的非零元
			col=M.data[p].j;
			q=cpot[col];//q代表第col列第一个非零元在b.data中的位置
			T->data[q].i=M.data[p].j;
			T->data[q].j=M.data[p].i;
			T->data[q].e=M.data[p].e;
			cpot[col]++;//++代表该列下一个非零元位于第一个非零元之后
		}
	}
	return OK;
}



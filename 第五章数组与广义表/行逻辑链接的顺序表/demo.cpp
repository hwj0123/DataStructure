#include<stdio.h>
#define MAXSIZE 12500//非零元个数的最大值是12500
#define OK 1
#define ERROR 0
typedef int ElemType;
typedef int Status;

typedef struct{
	int i,j;//行列
	ElemType e;//非零元的值
}Triple;
typedef struct{
	Triple data[MAXSIZE+1];//非零元三元组表
	int rpos[MAXSIZE+1];//各行第一个非零元的位置表
	int mu,nu,tu;//矩阵的行数,列数和非零元的个数
}RLSMatrix;
//求Q=MXN,采用行逻辑链接存储表示
Status MultSMatrix(RLSMatrix M,RLSMatrix N,RLSMatrix *Q){
	int arow,tp,t,p,brow,q,ccol;
	int ctemp[MAXSIZE+1];
	if(M.nu!=N.mu){//不满足相乘条件,即M矩阵的列数等于N矩阵的行数
		return ERROR;
	}
	Q->mu=M.mu;
	Q->nu=N.nu;
	Q->tu=0;
	if(M.mu*N.tu!=0){//Q是非零矩阵
		for(arow=1;arow<=M.mu;arow++){
			//ctemp[]=0;//当前行各元素累加器清为零
			//
			for(int i=0;i<MAXSIZE+1;i++){
				ctemp[i]=0;
			}
			Q->rpos[arow]=Q->tu+1;
			if(arow<M.mu){
				tp=M.rpos[arow+1];
			}else{
				tp=M.tu+1;
			}
			for(p=M.rpos[arow];p<tp;p++){//对应当前行中每一个非零元
				brow=M.data[p].j;
				if(brow<N.mu){
					t=N.rpos[brow+1];
				}else{
					t=N.tu+1;
				}
				for(q=N.rpos[brow];q<t;q++){
					ccol=N.data[q].j;
					ctemp[ccol]+=M.data[p].e*N.data[q].e;
				}
			}//求得Q中第arow行的非零元
			for(ccol=1;ccol<=Q->nu;ccol++){
				if(ctemp[ccol]){
					if(++Q->tu>MAXSIZE){
						return ERROR;
					}
					Q->data[Q->tu].e=ctemp[ccol];
					Q->data[Q->tu].i=arow;
					Q->data[Q->tu].j=ccol;
				}
			}
		}
	}
	return OK;
}
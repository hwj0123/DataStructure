#include<stdio.h>
#define MAXSIZE 12500//����Ԫ���������ֵ��12500
#define OK 1
#define ERROR 0
typedef int ElemType;
typedef int Status;

typedef struct{
	int i,j;//����
	ElemType e;//����Ԫ��ֵ
}Triple;
typedef struct{
	Triple data[MAXSIZE+1];//����Ԫ��Ԫ���
	int rpos[MAXSIZE+1];//���е�һ������Ԫ��λ�ñ�
	int mu,nu,tu;//���������,�����ͷ���Ԫ�ĸ���
}RLSMatrix;
//��Q=MXN,�������߼����Ӵ洢��ʾ
Status MultSMatrix(RLSMatrix M,RLSMatrix N,RLSMatrix *Q){
	int arow,tp,t,p,brow,q,ccol;
	int ctemp[MAXSIZE+1];
	if(M.nu!=N.mu){//�������������,��M�������������N���������
		return ERROR;
	}
	Q->mu=M.mu;
	Q->nu=N.nu;
	Q->tu=0;
	if(M.mu*N.tu!=0){//Q�Ƿ������
		for(arow=1;arow<=M.mu;arow++){
			//ctemp[]=0;//��ǰ�и�Ԫ���ۼ�����Ϊ��
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
			for(p=M.rpos[arow];p<tp;p++){//��Ӧ��ǰ����ÿһ������Ԫ
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
			}//���Q�е�arow�еķ���Ԫ
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
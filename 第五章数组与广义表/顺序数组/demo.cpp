#include<stdarg.h>
#include<stdio.h>
#include<stdlib.h>
#define MAX_ARRAY_DIM 8   //����ά�����Ϊ8
#define ERROR 0
#define OK 1
typedef int Status;
typedef int ElemType;
typedef struct{
	ElemType *base;//����Ԫ�ػ���ַ
	int dim;//����ά��
	int *bounds;//����ά�����ַ
	int *constants;//����ӳ����������ַ
}Array;
//��ά��dim�����ĸ�ά���ȺϷ�,������Ӧ������A,������OK
Status InitArray(Array *A,int dim,...){
	int elemtotal,i;
	va_list ap;
	if(dim<1||dim>MAX_ARRAY_DIM){//����ά��������
		return ERROR;
	}
	A->dim=dim;
	A->bounds=(int*)malloc(dim*sizeof(int));
	if(!A->bounds){
		exit(ERROR);
	}
	elemtotal=1;//���Ԫ������
    va_start(ap,dim);//��ʼ��ap,���Ǵ�ű䳤��������Ϣ������
	for(i=0;i<dim;i++){
		A->bounds[i]=va_arg(ap,int);
		if(A->bounds[i]<0){//����ÿά�ĳ��Ȳ�����
			return ERROR;
		}
		elemtotal*=A->bounds[i];
	}
	va_end(ap);
    A->base=(ElemType*)malloc(elemtotal*sizeof(ElemType));
	if(!A->base){
		exit(ERROR);
	}
	//��ӳ�����ĳ���ci,������A->constants[i-1],i=1,,,dim
	A->constants=(int*)malloc(dim*sizeof(int));
	if(!A->constants){
		exit(ERROR);
	}
	A->constants[dim-1]=1;//L=1,ָ��ĵݼ���Ԫ�ش�СΪ��λ
	for(i=dim-2;i>=0;--i){
		A->constants[i]=A->bounds[i+1]*A->constants[i+1];
	}
    return OK;

}
//��������A
Status DestoryArray(Array *A){
	if(!A->base){
		return ERROR;
	}
	free(A->base);
	A->base=NULL;
	if(!A->bounds){
		return ERROR;
	}
	free(A->bounds);
	A->bounds=NULL;
	if(!A->constants){
		return ERROR;
	}
	free(A->constants);
	A->constants=NULL;
	return OK;
}
//��apָʾ�ĸ����±�ֵ�Ϸ�,�������Ԫ����A�е����λ��off
Status Locate(Array A,va_list ap,int *off){
	*off=0;
	int i,ind;
	for(i=0;i<A.dim;++i){
		ind=va_arg(ap,int);
		if(ind<0||ind>=A.bounds[i]){
			return ERROR;
		}
		off+=A.constants[i]*ind;
	}
	return OK;
}
//A��nά����,eΪԪ�ر���,�����n���±�ֵ,
//�����±겻����,��e��ֵΪ��ָ����A��Ԫ��ֵ,������OK
Status Value(Array A,ElemType *e,...){
	int result,off;
    va_list ap;
	va_start(ap,e);
	if((result=Locate(A,ap,&off))<=0){
		return result;
	}
	*e=*(A.base+off);
	return OK;
}
//A��nά����,e��Ԫ�ر���,�����n���±�ֵ,
//���±겻����,��e��ֵ������ָ����A��Ԫ��ֵ,������OK
Status Assign(Array *A,ElemType e,...){
	va_list ap;
	int off,result;
	va_start(ap,e);
	if((result=Locate(*A,ap,&off))<=0){
		return result;
	}
	*(A->base+off)=e;
	return OK;
}
void main(){
	Array a;
	int x;
	printf("��ʼ��һ��3X3�Ķ�ά����\n");
	InitArray(&a,2,3,3);
	printf("�������(1,2)��ֵ\n");
	Assign(&a,5,1,2);
	Value(a,&x,1,2);
	printf("�ղŸ�����(1,2)����ֵΪ%d\n",x);

}

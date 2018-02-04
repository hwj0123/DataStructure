#include<stdarg.h>
#include<stdio.h>
#include<stdlib.h>
#define MAX_ARRAY_DIM 8   //数组维数最大为8
#define ERROR 0
#define OK 1
typedef int Status;
typedef int ElemType;
typedef struct{
	ElemType *base;//数组元素基地址
	int dim;//数组维数
	int *bounds;//数组维界基地址
	int *constants;//数组映像函数常量基址
}Array;
//若维数dim和随后的各维长度合法,则构造相应的数组A,并返回OK
Status InitArray(Array *A,int dim,...){
	int elemtotal,i;
	va_list ap;
	if(dim<1||dim>MAX_ARRAY_DIM){//数组维数不合理
		return ERROR;
	}
	A->dim=dim;
	A->bounds=(int*)malloc(dim*sizeof(int));
	if(!A->bounds){
		exit(ERROR);
	}
	elemtotal=1;//存放元素总数
    va_start(ap,dim);//初始化ap,它是存放变长参数表信息的数组
	for(i=0;i<dim;i++){
		A->bounds[i]=va_arg(ap,int);
		if(A->bounds[i]<0){//数组每维的长度不合理
			return ERROR;
		}
		elemtotal*=A->bounds[i];
	}
	va_end(ap);
    A->base=(ElemType*)malloc(elemtotal*sizeof(ElemType));
	if(!A->base){
		exit(ERROR);
	}
	//求映像函数的常数ci,并存入A->constants[i-1],i=1,,,dim
	A->constants=(int*)malloc(dim*sizeof(int));
	if(!A->constants){
		exit(ERROR);
	}
	A->constants[dim-1]=1;//L=1,指针的递减以元素大小为单位
	for(i=dim-2;i>=0;--i){
		A->constants[i]=A->bounds[i+1]*A->constants[i+1];
	}
    return OK;

}
//销毁数组A
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
//若ap指示的各个下标值合法,则求出该元素在A中的相对位置off
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
//A是n维数组,e为元素变量,随后是n个下标值,
//若各下标不超界,则e赋值为所指定的A的元素值,并返回OK
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
//A是n维数组,e是元素变量,随后是n个下标值,
//若下标不超界,则将e的值赋给所指定的A的元素值,并返回OK
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
	printf("初始化一个3X3的二维数组\n");
	InitArray(&a,2,3,3);
	printf("给数组的(1,2)赋值\n");
	Assign(&a,5,1,2);
	Value(a,&x,1,2);
	printf("刚才给数组(1,2)处赋值为%d\n",x);

}

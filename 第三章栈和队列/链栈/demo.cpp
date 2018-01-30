#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW 0
#define MAXSIZE 20 /* �洢�ռ��ʼ������ */

typedef int Status; 
typedef int SElemType; /* SElemType���͸���ʵ������������������Ϊint */

typedef struct{
	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack;
//1��ջ�ĳ�ʼ��
Status InitStack(SqStack *s){
	s->base=(SElemType*)malloc(MAXSIZE*sizeof(SElemType));
	if(!s->base){
		exit(OVERFLOW);
	}
	s->top=s->base;
	s->stacksize=MAXSIZE;
	return OK;
}
//2������ջ��Ԫ��
Status GetTop(SqStack s,SElemType *e){
	if(s.top==s.base){//ջΪ��
		return ERROR;
	}
	*e=*(s.top-1);//ֻ���ظ�Ԫ��,����ɾ��
	return OK;
}
//3������Ԫ��e��ջ��
Status Push(SqStack *s,SElemType e){
	if(s->top-s->base>=s->stacksize){//ջ��
		s->base=(SElemType*)realloc(s->base,(s->stacksize+MAXSIZE)*sizeof(SElemType));
		if(!s->base){
			exit(OVERFLOW);
		}
		s->top=s->base+s->stacksize;
		s->stacksize+=MAXSIZE;
	}
	//*s->top++=e;
    *s->top=e;
	s->top++;
	return OK;
}
//4����ջ��Ϊ��,ɾ��ջ��ջ��Ԫ�ز�������ֵ
Status Pop(SqStack *s,SElemType *e){
	if(s->top==s->base){
		return ERROR;
	}
//	*e=*--s->top;
	s->top-=1;
	*e=*s->top;
	return OK;
}


void main(){
	SqStack stack;
	int i;
	InitStack(&stack);
	//����1��5
    for(i=1;i<=5;i++){
		Push(&stack,i);
	}
	GetTop(stack,&i);
	//5
	printf("���ջ��Ԫ��%d\n",i);
	//ɾ��ջ��Ԫ��,��ʱջ��Ԫ�ر�Ϊ4
	Pop(&stack,&i);
	GetTop(stack,&i);
	printf("ɾ��ջ��Ԫ�غ�,��ʱ��ջ��Ԫ��Ϊ%d\n",i);




	

}

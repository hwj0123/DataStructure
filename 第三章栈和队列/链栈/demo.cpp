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
#define MAXSIZE 20 /* 存储空间初始分配量 */

typedef int Status; 
typedef int SElemType; /* SElemType类型根据实际情况而定，这里假设为int */

typedef struct{
	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack;
//1、栈的初始化
Status InitStack(SqStack *s){
	s->base=(SElemType*)malloc(MAXSIZE*sizeof(SElemType));
	if(!s->base){
		exit(OVERFLOW);
	}
	s->top=s->base;
	s->stacksize=MAXSIZE;
	return OK;
}
//2、返回栈顶元素
Status GetTop(SqStack s,SElemType *e){
	if(s.top==s.base){//栈为空
		return ERROR;
	}
	*e=*(s.top-1);//只返回该元素,并不删除
	return OK;
}
//3、插入元素e到栈顶
Status Push(SqStack *s,SElemType e){
	if(s->top-s->base>=s->stacksize){//栈满
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
//4、若栈不为空,删除栈的栈顶元素并返回其值
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
	//放入1至5
    for(i=1;i<=5;i++){
		Push(&stack,i);
	}
	GetTop(stack,&i);
	//5
	printf("获得栈顶元素%d\n",i);
	//删除栈顶元素,此时栈顶元素变为4
	Pop(&stack,&i);
	GetTop(stack,&i);
	printf("删除栈顶元素后,此时的栈顶元素为%d\n",i);




	

}

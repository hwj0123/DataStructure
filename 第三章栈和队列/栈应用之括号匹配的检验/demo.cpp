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
//5、栈为空的检验
Status StackEmpty(SqStack s)
{ 
	if (s.top==s.base){
		return TRUE;
	}else{
		return FALSE;
	}
}
//6、括号匹配的检验
Status chectBracket(char *c)
{
	int i = 0;
	SqStack S;
	InitStack(&S);
	SElemType e;
	while ('\0' != *(c+i)) {
		switch (*(c+i)) {
		case '(':
			Push(&S, -1);
			break;
		case '[':
			Push(&S, -2);
			break;
		case '{':
			Push(&S, -3);
			break;
		case ')':
			if (OK == GetTop(S, &e)) {		//栈非空，得到栈顶元素
				if (-1 == e)			//栈顶元素与‘）’匹配
					Pop(&S, &e);		// 删除栈顶元素
				else				// 不匹配，返回ERROR
					return ERROR;
			} else 
				return ERROR;
			break;
		case ']':
			if (OK == GetTop(S, &e)) { 
				if (-2 == e)
					Pop(&S, &e);
				else
					return ERROR;
			} else 
				return ERROR;
			break;
		case '}':
			if (OK == GetTop(S, &e)) {
				if (-3 == e)
					Pop(&S, &e);
				else
					return ERROR;
			} else
				return ERROR;
			break;
		default:
			break;
		} //switch

		i++;
	} // while

	if (StackEmpty(S))
		return OK;
	else
		return ERROR;
}

void main(){
	char *c="[([][])]";
	if(chectBracket(c)){
		printf("可以完成匹配\n");
	}
}


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
//5��ջΪ�յļ���
Status StackEmpty(SqStack s)
{ 
	if (s.top==s.base){
		return TRUE;
	}else{
		return FALSE;
	}
}
//6������ƥ��ļ���
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
			if (OK == GetTop(S, &e)) {		//ջ�ǿգ��õ�ջ��Ԫ��
				if (-1 == e)			//ջ��Ԫ���롮����ƥ��
					Pop(&S, &e);		// ɾ��ջ��Ԫ��
				else				// ��ƥ�䣬����ERROR
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
		printf("�������ƥ��\n");
	}
}


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
typedef int OperandType;
typedef int SElemType; /* SElemType���͸���ʵ��������� */

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
SElemType GetTop(SqStack s){
	SElemType e;
	if(s.top==s.base){//ջΪ��
		return ERROR;
	}
	e=*(s.top-1);//ֻ���ظ�Ԫ��,����ɾ��
	return e;
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
//5���ж��Ƿ�Ϊ�������������
bool In(char c)
{
	if ('+' == c || '-' == c || '/' == c || '*' == c 
		|| '(' == c || ')' == c || '#' == c)
		return true;
	return false;
}

//6���жϲ�����֮��Ĺ�ϵ
char Precede(char c1, char c2)
{
	switch (c1) {
	case '+':
	case '-':
		switch (c2) {
		case '+':
		case '-':
		case ')':
		case '#':
			return '>';
			break;
		case '*':
		case '/':
		case '(':
			return '<';
			break;
		default:
			break;
		}
		break;
	case '*':
	case '/':
		switch (c2) {
		case '+':
		case '-':
		case '*':
		case '/':
		case ')':
		case '#':
			return '>';
			break;
		case '(':
			return '<';
			break;
		default:
			break;
		}
		break;
	case '(':
		switch (c2) {
		case '+':
		case '-':
		case '*':
		case '/':
		case '(':
			return '<';
			break;
		case ')':
			return '=';
			break;
		default:
			break;
		}
		break;
	case ')':
		switch (c2) {
		case '+':
		case '-':
		case '*':
		case '/':
		case ')':
		case '#':
			return '>';
			break;
		default:
			break;
		}
		break;
	case '#':
		switch (c2) {
		case '+':
		case '-':
		case '*':
		case '/':
		case '(':
			return '<';
			break;
		case '#':
			return '=';
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}
//7���õ�a,b��theta����
int Operate(int a, char theta, int b)
{
	switch (theta) {
	case '+':
		printf("%d+%d=%d\n",a,b,a+b);
		return a+b;
		break;
	case '-':
		printf("%d-%d=%d\n",a,b,a-b);
		return a-b;
		break;
	case '*':
		printf("%d*%d=%d\n",a,b,a*b);
		return a*b;
		break;
	case '/':
		printf("%d/%d=%d\n",a,b,a/b);
		return a/b;
		break;
	default:
		break;
	}
	return ERROR;
}


//8�������������ֵ����������㷨
//OPTR,OPND�ֱ�Ϊ�����ջ,������ջ
//OPΪ���������
OperandType EvaluateExpression(){
	SqStack OPTR,OPND;
	int c,x,theta,b,a;
    InitStack(&OPTR);
	Push(&OPTR,(int)'#');
	InitStack(&OPND);
	printf("�������������ʽ\n");
	c=getchar();
	while(c!='#'||GetTop(OPTR)!='#'){
		if(!In(c)){//������ǲ�����,���������ջOPND
			c = c - '0';
			printf("%d��������\n",c);
			Push(&OPND,c);
			c=getchar();
			if(c=='#'){
				printf("������#\n");
			}
		}else{
			if(GetTop(OPTR)=='#'){
				printf("��ǰΪ#\n");
			}
			switch(Precede(GetTop(OPTR),c)){//�жϸ�����Ĳ�������ջ�������������ȼ���ϵ
			case '<':
				Push(&OPTR,c);
				c=getchar();
				break;
			case '=':
				printf("���ȼ����\n");
				Pop(&OPTR,&x);
				c=getchar();
				break;
			case '>':
				Pop(&OPTR,&theta);
				Pop(&OPND,&b);
				Pop(&OPND,&a);
				Push(&OPND,Operate(a,theta,b));
				break;
			}
		}
	}
    return GetTop(OPND);//�������ս��
}

void main(){
    int result;
	result=EvaluateExpression();
	printf("����:%d\n",result);
}

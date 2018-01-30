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
typedef int OperandType;
typedef int SElemType; /* SElemType类型根据实际情况而定 */

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
SElemType GetTop(SqStack s){
	SElemType e;
	if(s.top==s.base){//栈为空
		return ERROR;
	}
	e=*(s.top-1);//只返回该元素,并不删除
	return e;
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
//5、判断是否为操作符或结束符
bool In(char c)
{
	if ('+' == c || '-' == c || '/' == c || '*' == c 
		|| '(' == c || ')' == c || '#' == c)
		return true;
	return false;
}

//6、判断操作符之间的关系
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
//7、得到a,b的theta运算
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


//8、算数运算符求值的算符优先算法
//OPTR,OPND分别为运算符栈,运算数栈
//OP为运算符集合
OperandType EvaluateExpression(){
	SqStack OPTR,OPND;
	int c,x,theta,b,a;
    InitStack(&OPTR);
	Push(&OPTR,(int)'#');
	InitStack(&OPND);
	printf("请输入算术表达式\n");
	c=getchar();
	while(c!='#'||GetTop(OPTR)!='#'){
		if(!In(c)){//如果不是操作符,则进运算数栈OPND
			c = c - '0';
			printf("%d是运算数\n",c);
			Push(&OPND,c);
			c=getchar();
			if(c=='#'){
				printf("结束符#\n");
			}
		}else{
			if(GetTop(OPTR)=='#'){
				printf("当前为#\n");
			}
			switch(Precede(GetTop(OPTR),c)){//判断刚输入的操作符与栈顶操作符的优先级关系
			case '<':
				Push(&OPTR,c);
				c=getchar();
				break;
			case '=':
				printf("优先级相等\n");
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
    return GetTop(OPND);//返回最终结果
}

void main(){
    int result;
	result=EvaluateExpression();
	printf("答案是:%d\n",result);
}

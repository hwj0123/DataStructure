#include<stdio.h>


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


typedef struct{
	int x;//��
	int y;//��
}PosType;//����

 
typedef struct{
	int ord;//ͨ������·���ϵ����
	PosType seat;//ͨ�������Թ��е�����λ��
	int di;//�Ӵ�ͨ��������һͨ���ķ���
}SElemType;//ջ��Ԫ������

typedef struct{
	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack;

SqStack s;

int maze[10][10] ={
	{0,0,0,0,0,0,0,0,0,0},
	{0,1,1,0,1,1,1,0,1,0},
	{0,1,1,0,1,1,1,0,1,0},
	{0,1,1,1,1,0,0,1,1,0},
	{0,1,0,0,0,1,1,1,1,0},
	{0,1,1,1,0,1,1,1,1,0},
	{0,1,0,1,1,1,0,1,1,0},
	{0,1,0,0,0,1,0,0,1,0},
	{0,0,1,1,1,1,1,1,1,0},
	{0,0,0,0,0,0,0,0,0,0}
};

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
//5���жϵ�ǰλ���Ƿ����
Status Pass(PosType curpos){
	if(maze[curpos.x][curpos.y]){//����ͨ��
		return TRUE;
	}else{
		return FALSE;
	}     
}
//6�������㼣--->�����õ�ǰλ����1->0
void FootPrint(PosType curpos){
	maze[curpos.x][curpos.y]=0;
}
//7���趨��ǰλ�����·�������ڿ�
PosType NextPos(PosType seat,int di){
	switch(di){
	    case 1://����һ��
			seat.y=seat.y+1;
			break;
		case 2://����һ��
			seat.x=seat.x+1;
			break;
		case 3://����һ��
			seat.y=seat.y-1;
			break;
		case 4://����һ��
			seat.x=seat.x-1;
			break;
	}
	return seat;
}
//8�����²���ͨ�����㼣
void MarkPrint(PosType seat){
	maze[seat.x][seat.y]=0;
}
//9�����Թ�maze�д��ڴ����start������end��ͨ��,�����һ�������ջ��,������true,���򷵻�false
Status MazePath(PosType start,PosType end){
	
	PosType curpos;
	SElemType e;
	int curstep;
	curpos=start;
	curstep=1;
	InitStack(&s);
	do{
		if(Pass(curpos)){//�����ǰλ�ÿ���ͨ��,����δ�ߵ�����ͨ����
             FootPrint(curpos);//�����㼣
			 e.di=1;//����
			 e.ord=curstep;//����ͨ������·���ϵ����
			 e.seat=curpos;//����
			 Push(&s,e);//����ջ��
			 if((curpos.x==end.x)&&(curpos.y==end.y)){
				 return TRUE;
			 }
			 //curpos.y=curpos.y+1;
			 curpos=NextPos(curpos,1);//��һλ��Ϊ��ǰλ�õĶ������ƶ�һ��
			 curstep++;//̽����һ��
		}else{
			if(!(s.top==s.base)){
				Pop(&s,&e);//����һ��,ɾ��ջ��Ԫ��
				while(e.di==4&&!(s.top==s.base)){//��ǰλ�õ��ĸ�������߹�,��ջ��Ϊ��
					MarkPrint(e.seat);//���²���ͨ�����㼣,���ٻ���һ��
					Pop(&s,&e);
				}
				if(e.di<4){
					e.di++;
					Push(&s,e);
					curpos=NextPos(e.seat,e.di);
				}
			}
		}
	}while(!(s.base==s.top));
	return FALSE;
}
//10�����ʺ���
Status display_path(SElemType e)
{
	printf("(%d, %d) ", e.seat.x, e.seat.y);
	switch (e.di) {
	case 1:
		printf("��\n");
		break;
	case 2:
		printf("��\n");
		break;
	case 3:
		printf("��\n");
		break;
	case 4:
		printf("��\n");
		break;
	}
	return OK;
}
//11��������ջ
Status StackTraverse(SqStack S, Status (*visit)(SElemType))
{
	SElemType *p;
	p = S.base;   //pָ��ջ��
	while (p != S.top) {  //����ջ��Ԫ��
		visit(*p);
		p++;
	}
	return OK;
}
void main(){
	PosType start,end;
	start.x=1;
	start.y=1;
	end.x=8;
	end.y=8;
	MazePath(start,end);
	StackTraverse(s,display_path);

}
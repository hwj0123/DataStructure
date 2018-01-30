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
#define MAXSIZE 20 /* 存储空间初始分配量 */

typedef int Status;


typedef struct{
	int x;//横
	int y;//纵
}PosType;//坐标

 
typedef struct{
	int ord;//通道块在路径上的序号
	PosType seat;//通道块在迷宫中的坐标位置
	int di;//从此通道走向下一通道的方向
}SElemType;//栈的元素类型

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
//5、判断当前位置是否可走
Status Pass(PosType curpos){
	if(maze[curpos.x][curpos.y]){//可以通过
		return TRUE;
	}else{
		return FALSE;
	}     
}
//6、留下足迹--->即设置当前位置由1->0
void FootPrint(PosType curpos){
	maze[curpos.x][curpos.y]=0;
}
//7、设定当前位置是新方向的相邻块
PosType NextPos(PosType seat,int di){
	switch(di){
	    case 1://向右一步
			seat.y=seat.y+1;
			break;
		case 2://向下一步
			seat.x=seat.x+1;
			break;
		case 3://向左一步
			seat.y=seat.y-1;
			break;
		case 4://向上一步
			seat.x=seat.x-1;
			break;
	}
	return seat;
}
//8、留下不能通过的足迹
void MarkPrint(PosType seat){
	maze[seat.x][seat.y]=0;
}
//9、若迷宫maze中存在从入口start到出口end的通道,则求得一条存放在栈中,并返回true,否则返回false
Status MazePath(PosType start,PosType end){
	
	PosType curpos;
	SElemType e;
	int curstep;
	curpos=start;
	curstep=1;
	InitStack(&s);
	do{
		if(Pass(curpos)){//如果当前位置可以通过,即是未走到过的通道块
             FootPrint(curpos);//留下足迹
			 e.di=1;//方向
			 e.ord=curstep;//设置通道块在路径上的序号
			 e.seat=curpos;//坐标
			 Push(&s,e);//放入栈顶
			 if((curpos.x==end.x)&&(curpos.y==end.y)){
				 return TRUE;
			 }
			 //curpos.y=curpos.y+1;
			 curpos=NextPos(curpos,1);//下一位置为当前位置的东方向移动一个
			 curstep++;//探索下一步
		}else{
			if(!(s.top==s.base)){
				Pop(&s,&e);//回退一步,删除栈顶元素
				while(e.di==4&&!(s.top==s.base)){//当前位置的四个方向均走过,且栈不为空
					MarkPrint(e.seat);//留下不能通过的足迹,且再回退一步
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
//10、访问函数
Status display_path(SElemType e)
{
	printf("(%d, %d) ", e.seat.x, e.seat.y);
	switch (e.di) {
	case 1:
		printf("东\n");
		break;
	case 2:
		printf("南\n");
		break;
	case 3:
		printf("西\n");
		break;
	case 4:
		printf("北\n");
		break;
	}
	return OK;
}
//11、遍历链栈
Status StackTraverse(SqStack S, Status (*visit)(SElemType))
{
	SElemType *p;
	p = S.base;   //p指向栈底
	while (p != S.top) {  //遍历栈的元素
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
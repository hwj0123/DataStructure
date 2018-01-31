#include "string.h"
#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 40 /* 存储空间初始分配量 */
#define MaxBookNum 1000
#define MaxKeyNum 2500
#define MaxLineLen 500
#define MaxWordNum 10

typedef int Status;		/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int ElemType;	/* ElemType类型根据实际情况而定，这里假设为int */

typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LNode,*LinkList;//链表的定义

typedef char String[MAXSIZE+1]; /*  0号单元存放串的长度 */



typedef struct{
	char * item;//字符串的数组
	int last;//词表的长度
}WordListType;//词表类型

typedef int ElemType;//定义链表的数据元素类型是整形

typedef struct{
     String key;//关键词
	 LinkList bnolist;//存放书号索引的链表
}IdxTermType;//索引项类型

typedef struct{
	IdxTermType item[MaxKeyNum+1];
	int last;
}IdxListType;//索引表类型

char *buf;//书目串缓冲区
WordListType wdlist;//词表
//////////////////////////////
//过于复杂,略
void main(){
//	FILE *f,*g;
//	IdxListType idxlist;
//	if(f=fopen("D:\test.txt","r")){
//		if(g=fopen("D:\test.txt","w")){
//			InitIdxList(&idxlist);//初始化索引表idxlist为空表
//			while(!feof(f)){
//				//..........
//			}
//		}
//	}
}






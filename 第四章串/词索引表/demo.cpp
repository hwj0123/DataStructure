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
#define MAXSIZE 40 /* �洢�ռ��ʼ������ */
#define MaxBookNum 1000
#define MaxKeyNum 2500
#define MaxLineLen 500
#define MaxWordNum 10

typedef int Status;		/* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
typedef int ElemType;	/* ElemType���͸���ʵ������������������Ϊint */

typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LNode,*LinkList;//����Ķ���

typedef char String[MAXSIZE+1]; /*  0�ŵ�Ԫ��Ŵ��ĳ��� */



typedef struct{
	char * item;//�ַ���������
	int last;//�ʱ�ĳ���
}WordListType;//�ʱ�����

typedef int ElemType;//�������������Ԫ������������

typedef struct{
     String key;//�ؼ���
	 LinkList bnolist;//����������������
}IdxTermType;//����������

typedef struct{
	IdxTermType item[MaxKeyNum+1];
	int last;
}IdxListType;//����������

char *buf;//��Ŀ��������
WordListType wdlist;//�ʱ�
//////////////////////////////
//���ڸ���,��
void main(){
//	FILE *f,*g;
//	IdxListType idxlist;
//	if(f=fopen("D:\test.txt","r")){
//		if(g=fopen("D:\test.txt","w")){
//			InitIdxList(&idxlist);//��ʼ��������idxlistΪ�ձ�
//			while(!feof(f)){
//				//..........
//			}
//		}
//	}
}






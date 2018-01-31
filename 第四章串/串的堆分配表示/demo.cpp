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

typedef int Status;		/* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
typedef int ElemType;	/* ElemType���͸���ʵ������������������Ϊint */

typedef struct{
	char *ch;
	int length;
}HString;
//�ڴ�S�ĵ�pos���ַ�֮ǰ���봮T
Status StrInsert(HString *S,int pos,HString T){
	int i;
	if(pos<1||pos>S->length+1){
		return ERROR;
	}
	if(T.length){//T�ǿ�,�����·���ռ�
		if(!(S->ch=(char *)realloc(S->ch,(S->length+T.length)*sizeof(char)))){
			exit(ERROR);
		}
		for(i=S->length-1;i>=pos-1;--i){//Ϊ����T�ڳ�λ��
			S->ch[i+T.length]=S->ch[i];
		}
		for(i=0;i<T.length;i++){
			S->ch[pos-1+i]=T.ch[i];//��S�в��봮T
		}
		S->length=S->length+T.length;
	}
	return OK;
}
//����һ����ֵ���ڴ�����chars�Ĵ�T
Status StrAssign(HString *T,char * chars){
	int i,j;
	char *c;
//	if(T->ch){
//		free(T->ch);//�ͷ�Tԭ�еĿռ�---->����--->���ͷŴ���--File:dbgheap.c Line1044
//	}
	for(i=0,c=chars;*c;i++,c++);//��chars�ĳ���i
	//printf("chars�ĳ���Ϊ%d\n",i);
	if(!i){
		T->ch=NULL;
		T->length=0;
	}else{
		if(!(T->ch=(char*)malloc(i*sizeof(char)))){
			exit(ERROR);
		}
		for(j=0;j<i;j++){
			T->ch[j]=chars[j];
		}
		T->length=i;
	}
	return OK;

}
//���ش��ĳ���
int StrLength(HString S){
	return S.length;
}
//�Ƚ��������Ĵ�С
int StrCompare(HString S,HString T){
	int i;
	for(i=0;i<S.length&&i<T.length;i++){
		if(S.ch[i]!=T.ch[i]){
			return S.ch[i]-T.ch[i];
		}
	}
	return S.length-T.length;
}
//����S��Ϊ�մ�
Status ClearString(HString *S){
	if(S->ch){
		free(S->ch);
		S->ch=NULL;
	}
	S->length=0;
	return OK;
}
//T=S1 U S2
Status Concat(HString *T,HString S1,HString S2){
	int i;
	if(!T->ch){
		free(T->ch);
	}
	if(!(T->ch=(char*)malloc((S1.length+S2.length)*sizeof(char)))){
		exit(ERROR);
	}
	for(i=0;i<S1.length;i++){
		T->ch[i]=S1.ch[i];
	}
	T->length=S1.length+S2.length;
	for(i=0;i<S2.length;i++){
		T->ch[S1.length+i]=S2.ch[i];
	}
	return OK;
}
//��Sub���ش�S�ĵ�pos���ַ��𳤶�Ϊlen���Ӵ�
Status SubString(HString *Sub,HString S,int pos,int len){
	int i;
	if(pos<1||pos>S.length||len<0||len>S.length-pos+1){
		return ERROR;
	}
	if(Sub->ch){
		free(Sub->ch);
	}
	if(!len){
		Sub->ch=NULL;
		Sub->length=0;
	}else{
		Sub->ch=(char*)malloc(len*sizeof(char));
		for(i=0;i<len;i++){
			Sub->ch[i]=S.ch[pos-1+i];
		}
		Sub->length=len;
	}
	return OK;
}
//��ӡ����Ԫ��
void StrPrint(HString T)
{ 
	int i;
	for(i=0;i<T.length;i++)
		printf("%c\t",T.ch[i]);
	printf("\n");
}
void main(){
	Status k;
	HString s1,s2,s3;
	k=StrAssign(&s1,"abcd");
    printf("��s1������:%d\n",StrLength(s1));
	StrPrint(s1);
	k=StrAssign(&s2,"fgh");
	printf("��s2����Ϊ:%d\n",StrLength(s2));
	StrPrint(s2);
    Concat(&s3,s1,s2);
	printf("��s3����Ϊ:%d\n",StrLength(s3));
	StrPrint(s3);


}

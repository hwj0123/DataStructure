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

typedef int Status;		/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int ElemType;	/* ElemType类型根据实际情况而定，这里假设为int */

typedef struct{
	char *ch;
	int length;
}HString;
//在串S的第pos个字符之前插入串T
Status StrInsert(HString *S,int pos,HString T){
	int i;
	if(pos<1||pos>S->length+1){
		return ERROR;
	}
	if(T.length){//T非空,则重新分配空间
		if(!(S->ch=(char *)realloc(S->ch,(S->length+T.length)*sizeof(char)))){
			exit(ERROR);
		}
		for(i=S->length-1;i>=pos-1;--i){//为插入T腾出位置
			S->ch[i+T.length]=S->ch[i];
		}
		for(i=0;i<T.length;i++){
			S->ch[pos-1+i]=T.ch[i];//向S中插入串T
		}
		S->length=S->length+T.length;
	}
	return OK;
}
//生成一个其值等于串常量chars的串T
Status StrAssign(HString *T,char * chars){
	int i,j;
	char *c;
//	if(T->ch){
//		free(T->ch);//释放T原有的空间---->报错--->堆释放错误--File:dbgheap.c Line1044
//	}
	for(i=0,c=chars;*c;i++,c++);//求chars的长度i
	//printf("chars的长度为%d\n",i);
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
//返回串的长度
int StrLength(HString S){
	return S.length;
}
//比较两个串的大小
int StrCompare(HString S,HString T){
	int i;
	for(i=0;i<S.length&&i<T.length;i++){
		if(S.ch[i]!=T.ch[i]){
			return S.ch[i]-T.ch[i];
		}
	}
	return S.length-T.length;
}
//将串S清为空串
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
//用Sub返回串S的第pos个字符起长度为len的子串
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
//打印串中元素
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
    printf("串s1长度是:%d\n",StrLength(s1));
	StrPrint(s1);
	k=StrAssign(&s2,"fgh");
	printf("串s2长度为:%d\n",StrLength(s2));
	StrPrint(s2);
    Concat(&s3,s1,s2);
	printf("串s3长度为:%d\n",StrLength(s3));
	StrPrint(s3);


}

#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 100 /* �洢�ռ��ʼ������ */

#define SUCCESS 1
#define UNSUCCESS 0
#define HASHSIZE 12 /* ����ɢ�б�Ϊ����ĳ��� */
#define NULLKEY -32768 

typedef int Status;	/* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */ 

typedef struct{
	int *elem;//����ָ��
	int count;//��ǰ����Ԫ�ظ���
}HashTable;
int m=0;
/****************************�㷨ʵ��*********************************/
//1����ʼ����ϣ��
Status InitHashTable(HashTable *H){
	int i;
	m=HASHSIZE;
	H->count=m;
	H->elem=(int *)malloc(m*sizeof(int));
	for(i=0;i<m;i++){
		H->elem[i]=NULLKEY;//��ʼ��
	}
	return OK;

}
//2��ɢ�к���
int Hash(int key){
	return key%m;
}
//3������ؼ��ֵ�ɢ�б���
void InsertHash(HashTable *H,int key){
	int addr=Hash(key);//��ɢ�к����õ�ɢ�е�ַ
	while(H->elem[addr]!=NULLKEY){//������ͻ
		addr=(addr+1)%m;//���Ŷ�ַ��--����̽�ⷨ--->mΪ12
	}//����ֻ����1�������Ǵ�1��2,3��...n
	H->elem[addr]=key;//���뵽��λ
}
//4�����ҹؼ���
Status SearchHash(HashTable H,int key,int *addr){
	*addr=Hash(key);//�ɹؼ��ֵõ�ɢ�е�ַ
	while(H.elem[*addr]!=key){
		*addr=(*addr+1)%m;
		if(H.elem[*addr]==NULLKEY||*addr==Hash(key)){
			return UNSUCCESS;//�ؼ��ֲ�����
		}
	}
	return SUCCESS;
}
void main(){
	int arr[HASHSIZE]={12,67,56,16,25,37,22,29,15,47,48,34};
	int i,p,key,result;
	HashTable H;
	key=59;
	InitHashTable(&H);
	for(i=0;i<m;i++){
		InsertHash(&H,arr[i]);
	}
	result=SearchHash(H,key,&p);
	if(result){
		printf("����%d�ĵ�ַΪ:%d\n",key,p);
	}else{
		printf("����%dʧ��\n",key);
	}
	for(i=0;i<m;i++){
		key=arr[i];
		SearchHash(H,key,&p);
		printf("����%d�ĵ�ַΪ:%d\n",key,p);
	}
}

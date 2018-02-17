#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 100 /* 存储空间初始分配量 */

#define SUCCESS 1
#define UNSUCCESS 0
#define HASHSIZE 12 /* 定义散列表长为数组的长度 */
#define NULLKEY -32768 

typedef int Status;	/* Status是函数的类型,其值是函数结果状态代码，如OK等 */ 

typedef struct{
	int *elem;//数组指针
	int count;//当前数据元素个数
}HashTable;
int m=0;
/****************************算法实现*********************************/
//1、初始化哈希表
Status InitHashTable(HashTable *H){
	int i;
	m=HASHSIZE;
	H->count=m;
	H->elem=(int *)malloc(m*sizeof(int));
	for(i=0;i<m;i++){
		H->elem[i]=NULLKEY;//初始化
	}
	return OK;

}
//2、散列函数
int Hash(int key){
	return key%m;
}
//3、插入关键字到散列表中
void InsertHash(HashTable *H,int key){
	int addr=Hash(key);//由散列函数得到散列地址
	while(H->elem[addr]!=NULLKEY){//发生冲突
		addr=(addr+1)%m;//开放定址法--线性探测法--->m为12
	}//这里只加了1，而不是从1，2,3，...n
	H->elem[addr]=key;//插入到空位
}
//4、查找关键字
Status SearchHash(HashTable H,int key,int *addr){
	*addr=Hash(key);//由关键字得到散列地址
	while(H.elem[*addr]!=key){
		*addr=(*addr+1)%m;
		if(H.elem[*addr]==NULLKEY||*addr==Hash(key)){
			return UNSUCCESS;//关键字不存在
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
		printf("查找%d的地址为:%d\n",key,p);
	}else{
		printf("查找%d失败\n",key);
	}
	for(i=0;i<m;i++){
		key=arr[i];
		SearchHash(H,key,&p);
		printf("查找%d的地址为:%d\n",key,p);
	}
}

#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"
#include "string.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef struct{
	unsigned int weight;//节点的权值
	unsigned int parent,lchild,rchild;//父节点,左孩子节点,右孩子节点
}HTNode,*HuffmanTree;//动态分配数组存储哈夫曼树

typedef char **HuffmanCode;//动态分配数组存储哈夫曼编码表

//求赫夫曼编码
//w存储n个字符的权值,构造赫夫曼树HT，并求出n个字符的哈夫曼编码HC
void HuffmanCoding(HuffmanTree HT,HuffmanCode HC,int *w,int n){
	int m,i,s1,s2,c,start,f;
	char *cd;
	HuffmanTree p;
	if(n<=1){//字符为空
		return ;
	}
	m=2*n-1;//n个叶子节点的赫夫曼树共有2*n-1个节点
	HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode));//申请m+1个单元,0号不用
	for(p=HT,i=1;i<=n;i++,p++,w++){//将n个字符放入树HT中
		p->weight=*w;
		p->parent=0;
		p->lchild=0;
		p->rchild=0;
	}
	for(;i<=m;i++,p++){
		p->weight=0;
		p->parent=0;
		p->lchild=0;
		p->rchild=0;
	}
	
	for(i=n+1;i<=m;i++){
		//在HT[1...i-1]中选择parent为0且weight最小的两个节点,其序号分别为s1和s2
		//Select(HT,i-1,&s1,&s2);
		HT[s1].parent=i;
		HT[s2].parent=i;
		HT[i].lchild=s1;
		HT[i].rchild=s2;
		HT[i].weight=HT[s1].weight+HT[s2].weight;//将HT[s1]和HT[s2]作为左右子树构造一个新的二叉树

	}

	//从叶子到根逆向求每一个字符的赫夫曼编码
	HC=(HuffmanCode)malloc((n+1)*sizeof(char *));//分配n个字符编码的头指针向量
	cd=(char *)malloc(n*sizeof(char));//cd指向赫夫曼编码
    cd[n-1]='\0';//结束符
    for(i=1;i<=n;i++){
		start=n-1;//开始位置(逆向)
        for(c=i,f=HT[i].parent;f!=0;c=f,f=HT[f].parent){//逆向求编码
			if(HT[f].lchild==c){
				cd[--start]='0';//参看p146的图
			}else{
				cd[--start]='1';
			}
		}
		HC[i]=(char*)malloc((n-start)*sizeof(char));//为第i个字符编码分配空间
		strcpy(HC[i],&cd[start]);//从cd复制到HC
	}
	free(cd);
}



//无栈非递归遍历赫夫曼树,求赫夫曼编码
//略
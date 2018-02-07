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
	unsigned int weight;//�ڵ��Ȩֵ
	unsigned int parent,lchild,rchild;//���ڵ�,���ӽڵ�,�Һ��ӽڵ�
}HTNode,*HuffmanTree;//��̬��������洢��������

typedef char **HuffmanCode;//��̬��������洢�����������

//��շ�������
//w�洢n���ַ���Ȩֵ,����շ�����HT�������n���ַ��Ĺ���������HC
void HuffmanCoding(HuffmanTree HT,HuffmanCode HC,int *w,int n){
	int m,i,s1,s2,c,start,f;
	char *cd;
	HuffmanTree p;
	if(n<=1){//�ַ�Ϊ��
		return ;
	}
	m=2*n-1;//n��Ҷ�ӽڵ�ĺշ���������2*n-1���ڵ�
	HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode));//����m+1����Ԫ,0�Ų���
	for(p=HT,i=1;i<=n;i++,p++,w++){//��n���ַ�������HT��
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
		//��HT[1...i-1]��ѡ��parentΪ0��weight��С�������ڵ�,����ŷֱ�Ϊs1��s2
		//Select(HT,i-1,&s1,&s2);
		HT[s1].parent=i;
		HT[s2].parent=i;
		HT[i].lchild=s1;
		HT[i].rchild=s2;
		HT[i].weight=HT[s1].weight+HT[s2].weight;//��HT[s1]��HT[s2]��Ϊ������������һ���µĶ�����

	}

	//��Ҷ�ӵ���������ÿһ���ַ��ĺշ�������
	HC=(HuffmanCode)malloc((n+1)*sizeof(char *));//����n���ַ������ͷָ������
	cd=(char *)malloc(n*sizeof(char));//cdָ��շ�������
    cd[n-1]='\0';//������
    for(i=1;i<=n;i++){
		start=n-1;//��ʼλ��(����)
        for(c=i,f=HT[i].parent;f!=0;c=f,f=HT[f].parent){//���������
			if(HT[f].lchild==c){
				cd[--start]='0';//�ο�p146��ͼ
			}else{
				cd[--start]='1';
			}
		}
		HC[i]=(char*)malloc((n-start)*sizeof(char));//Ϊ��i���ַ��������ռ�
		strcpy(HC[i],&cd[start]);//��cd���Ƶ�HC
	}
	free(cd);
}



//��ջ�ǵݹ�����շ�����,��շ�������
//��
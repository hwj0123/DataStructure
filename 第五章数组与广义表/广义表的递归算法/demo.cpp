#include<stdio.h>
#include<stdlib.h>
#define OK 1
typedef int AtomType;
typedef int Status;
typedef enum{ATOM,LIST}ElemTag;//ATOM==0:ԭ��,LIST==1:�ӱ�(ö������)
typedef struct GLNode{
	ElemTag tag;//��������,��������ԭ�ӽ��ͱ���
	union{//ԭ�ӽ��ͱ���Ľ�ϲ���
		AtomType atom;//atom��ԭ�ӽ���ֵ��,AtomType���û�����
		struct{struct GLNode *hp,*tp;} ptr;//ptr�Ǳ�ڵ��ָ����,ptr.hp��ptr.tp�ֱ�ָ���ͷ�ͱ�β
	};
}*GList;//���������

//����ͷβ����洢�ṹ,������L�����
int GListDepth(GList L){
	int max;
	int dep=0;
	GList pp;
	if(!L){
		return 1;//�ձ�����Ϊ1
	}
	if(L->tag==ATOM){
		return 0;//ԭ�����Ϊ0
	}
	for(max=0,pp=L;pp;pp=pp->ptr.tp){
		dep=GListDepth(pp->ptr.hp);//����pp->ptr.hpΪͷָ����ӱ�����
		if(dep>max){
			max=dep;//
		}
	}
	return max+1;//�ǿձ������Ǹ�Ԫ�ص���ȵ����ֵ+1
}

//�ɹ����L���Ƶõ������T
Status CopyGList(GList *T,GList L){
	if(!L){
		*T=NULL;//LΪ�ձ�,����TΪ��
	}else{
		if(!(*T=(GList)malloc(sizeof(GLNode)))){//������ͷ�ڵ�
			exit(0);
		}
		(*T)->tag=L->tag;
		if(L->tag==ATOM){
			(*T)->atom=L->atom;//���Ƶ�ԭ��
		}else{
			CopyGList(&(*T)->ptr.hp,L->ptr.hp);//���ƹ�����L->ptr.hp
			CopyGList(&(*T)->ptr.tp,L->ptr.tp);//���ƹ�����L->ptr.tp
		}
	}
	return OK;
}

//���㷨5.7,5.8
void main(){
}
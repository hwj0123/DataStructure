#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
#define OVERFLOW 0
#define ERROR 0
#define OK 1
#define TRUE 1
#define FALSE 0
typedef int ElemType;
typedef int Status;
typedef struct{
	ElemType *elem;
	int length;
	int listsize;
}SqList;
//1������һ���յ�˳���
Status InitList_Sq(SqList *L){
	L->elem=(ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	if(!L->elem){
		exit(OVERFLOW);
	}
	L->length=0;
	L->listsize=LIST_INIT_SIZE;
	return OK;
}
//2����˳���L�е�i��λ�ò���Ԫ��e
Status ListInsert_Sq(SqList *L,int i,ElemType e){
	ElemType *q,*p,*newbase;
	//�жϲ���λ���Ƿ����
	if(i<1||i>L->length+1){
		return ERROR;
	}
	//�Ƿ���Ҫ����
	if(L->length>=L->listsize){
		newbase=(ElemType*)realloc(L->elem,(L->listsize+LISTINCREMENT)*sizeof(ElemType));
		if(!newbase){
			exit(OVERFLOW);
		}
		L->elem=newbase;
		L->listsize+=LISTINCREMENT;
	}
	q=&(L->elem[i-1]);
	for(p=&(L->elem[L->length-1]);p>=q;--p){
		*(p+1)=*p;
	}
	*q=e;
	++L->length;
	return OK;
}
//3����ӡ˳���
void Print_List(SqList *L){
	int i;
	printf("˳�����Ϣ:\n");
	printf("˳�����Ϊ%d,������Ϊ%d\n",L->length,L->listsize);
	for(i=0;i<L->length;i++){
		printf("%d\t",L->elem[i]);
	}
	printf("\n");
}
//4��ɾ��˳����е�i��Ԫ��
Status ListDelete_Sq(SqList *L,int i,ElemType *e){
	ElemType *p,*q;
	if((i<1)||(i>L->length)){
		return ERROR;
	}
	p=&(L->elem[i-1]);//��¼��ɾ��Ԫ�ص�λ��
	*e=*p;
	q=L->elem+L->length-1;
	for(++p;p<=q;++p){
		*(p-1)=*p;
	}
	--L->length;
	return OK;
}
//5���ҵ�˳���L�е�1��ֵ��e��ȵ�Ԫ�ص�λ��
int LocateElem_Sq(SqList L,ElemType e,Status(*compare)(ElemType,ElemType)){
	int i;
	ElemType *p;
	i=1;
	p=L.elem;
	while(i<=L.length&&!(*compare)(*p++,e)){
		++i;
	}
	if(i<=L.length){
		return i;
	}else{
		return 0;
	}
}
//6���Ƚ���������Ԫ���Ƿ����
int equal(ElemType e1,ElemType e2){
	if(e1==e2){
		return 1;
	}
	return 0;
}
//7������˳���ĳ���
int ListLength(SqList L){
    return L.length;
}
//8��ȡ��˳����е�i������Ԫ��
void GetElem(SqList L,int i,int *e){
	*e=L.elem[i-1];
}
//9��LA=LA U LB
void UnionList(SqList *La,SqList Lb){
	int La_len,Lb_len,i,e;
	La_len=ListLength(*La);
	Lb_len=ListLength(Lb);
	for(i=1;i<=Lb_len;i++){
         GetElem(Lb,i,&e);
		 if(!LocateElem_Sq(*La,e,&equal)){
			 ListInsert_Sq(La,++La_len,e);
		 }
	}
}
//10��LC=LA U LB   
void MergeList(SqList La,SqList Lb,SqList *Lc){
	InitList_Sq(Lc);
	int i,j,k,La_len,Lb_len;
	int ai,bj;
	i=j=1;
	k=0;
	La_len=ListLength(La);
	Lb_len=ListLength(Lb);
	while((i<=La_len)&&(j<=Lb_len)){
		GetElem(La,i,&ai);
		GetElem(Lb,j,&bj);
		if(ai<=bj){
			ListInsert_Sq(Lc,++k,ai);
			++i;
		}else{
			ListInsert_Sq(Lc,++k,bj);
			++j;
		}
	}
	while(i<=La_len){
		GetElem(La,i++,&ai);
		ListInsert_Sq(Lc,++k,ai);
	}
	while(j<=Lb_len){
		GetElem(Lb,j++,&bj);
		ListInsert_Sq(Lc,++k,bj);
	}

}
//11��O(La.length+Lb.length)
void MergeList_Sq(SqList La,SqList Lb,SqList *Lc){
	ElemType *pa,*pb,*pc,*pa_last,*pb_last;
	pa=La.elem;
	pb=Lb.elem;
	Lc->listsize=Lc->length=La.length+Lb.length;
	pc=Lc->elem=(ElemType*)malloc(Lc->listsize*sizeof(ElemType));
	if(!Lc->elem){
		exit(OVERFLOW);
	}
	pa_last=La.elem+La.length-1;
	pb_last=Lb.elem+Lb.length-1;
	while(pa<=pa_last&&pb<=pb_last){
		if(*pa<=*pb){
			*pc=*pa;
			pa++;
			pc++;
		}else{
			*pc=*pb;
			pb++;
			pc++;
		}
	}
	while(pa<=pa_last){
			*pc=*pa;
			pa++;
			pc++;
	}
	while(pb<=pb_last){
	    	*pc=*pb;
			pb++;
			pc++;
	}
}
//12������˳���L
void DestoryList(SqList *L){
	free(L);
}
//13����Ϊ�ձ�
Status ClearList(SqList *L){
	L->length=0;
	L->elem=NULL;
	return OK;
}
//14���ж�˳����Ƿ�Ϊ��
Status ListEmpty(SqList L){
	if(L.length==0){
		return TRUE;
	}else{
		return FALSE;
	}
}
//15����ʼ����:˳���L����
//    �������:��e��L���е�����Ԫ��,�Ҳ��ǵ�һ��,����pre_e��������ǰ��,����ʧ��
void PriorElem(SqList L,ElemType e,ElemType *pre_e){
    ElemType *q=L.elem;
	int i;
	int L_len=ListLength(L);
	for(i=1;i<L_len;i++){
		if(q[i]==e){
			*pre_e=q[i-1];
		}
	}
}
//16����ʼ����:˳���L����
//    �������:��e��L���е�����Ԫ��,�Ҳ������һ��,����next_e�������ĺ��,����ʧ��
void NextElem(SqList L,ElemType e,ElemType *next_e){
	ElemType *q=L.elem;
	int i;
	int L_len=ListLength(L);
	for(i=0;i<L_len-1;i++){
		if(q[i]==e){
			*next_e=q[i+1];
		}
	}
}

void MyPrint(int i){
	printf("%d\t",i);
}
//17����ʼ����:˳���L�Ѵ���
//    �������:���ζ�L��ÿһ������Ԫ�ص��ú���visit()
void ListTraverse(SqList L,void (*visit)(ElemType)){
	ElemType *q=L.elem;
	int i;
	for(i=0;i<L.length;i++){
		(*visit)(q[i]);
	}
}
void main(){
	SqList list,Lb,Lc;
	int i;
	InitList_Sq(&list);
	InitList_Sq(&Lb);
	InitList_Sq(&Lc);
	for(i=1;i<6;i++){
		ListInsert_Sq(&list,i,i);
	}
    PriorElem(list,3,&i);
	printf("˳���list������Ԫ��3��ǰһ����%d\n",i);
	NextElem(list,4,&i);
	printf("˳���list������Ԫ��4�ĺ�һ����%d\n",i);
	printf("����ListTraverse����\n");
	ListTraverse(list,MyPrint);
//	for(i=1;i<9;i++){
//		ListInsert_Sq(&Lb,i,i);
//	}
//    Print_List(&list);
//	Print_List(&Lb);
//    UnionList(&list,Lb);
//	printf("List=List U Lb\n");
//	Print_List(&list);
//    MergeList(list,Lb,&Lc);
//	MergeList_Sq(list,Lb,&Lc);
//	printf("Lc=List U La\n");
//	Print_List(&Lc);
//	ListDelete_Sq(&list,3,&i);
//	printf("��ɾ����Ԫ����%d\n",i);
//	printf("ɾ�����˳���:\n");
//	Print_List(&list);
//	i=LocateElem_Sq(list,4,&equal);
//	printf("4��˳����е�λ��%d\n",i);
//	printf("����ListLength��������˳���ĳ���:%d\n",ListLength(list));
//	GetElem(list,3,&i);
//	printf("����GetElem����ȡ�����е�3��Ԫ��:%d\n",i);





}




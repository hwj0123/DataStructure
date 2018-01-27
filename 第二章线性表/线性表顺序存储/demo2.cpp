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
//1、构造一个空的顺序表
Status InitList_Sq(SqList *L){
	L->elem=(ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	if(!L->elem){
		exit(OVERFLOW);
	}
	L->length=0;
	L->listsize=LIST_INIT_SIZE;
	return OK;
}
//2、在顺序表L中第i个位置插入元素e
Status ListInsert_Sq(SqList *L,int i,ElemType e){
	ElemType *q,*p,*newbase;
	//判断插入位置是否合理
	if(i<1||i>L->length+1){
		return ERROR;
	}
	//是否需要扩容
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
//3、打印顺序表
void Print_List(SqList *L){
	int i;
	printf("顺序表信息:\n");
	printf("顺序表长度为%d,总容量为%d\n",L->length,L->listsize);
	for(i=0;i<L->length;i++){
		printf("%d\t",L->elem[i]);
	}
	printf("\n");
}
//4、删除顺序表中第i个元素
Status ListDelete_Sq(SqList *L,int i,ElemType *e){
	ElemType *p,*q;
	if((i<1)||(i>L->length)){
		return ERROR;
	}
	p=&(L->elem[i-1]);//记录被删除元素的位置
	*e=*p;
	q=L->elem+L->length-1;
	for(++p;p<=q;++p){
		*(p-1)=*p;
	}
	--L->length;
	return OK;
}
//5、找到顺序表L中第1个值与e相等的元素的位序
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
//6、比较两个数据元素是否相等
int equal(ElemType e1,ElemType e2){
	if(e1==e2){
		return 1;
	}
	return 0;
}
//7、返回顺序表的长度
int ListLength(SqList L){
    return L.length;
}
//8、取出顺序表中第i个数据元素
void GetElem(SqList L,int i,int *e){
	*e=L.elem[i-1];
}
//9、LA=LA U LB
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
//10、LC=LA U LB   
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
//11、O(La.length+Lb.length)
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
//12、销毁顺序表L
void DestoryList(SqList *L){
	free(L);
}
//13、置为空表
Status ClearList(SqList *L){
	L->length=0;
	L->elem=NULL;
	return OK;
}
//14、判断顺序表是否为空
Status ListEmpty(SqList L){
	if(L.length==0){
		return TRUE;
	}else{
		return FALSE;
	}
}
//15、初始条件:顺序表L存在
//    操作结果:若e是L表中的数据元素,且不是第一个,则用pre_e返回它的前驱,否则失败
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
//16、初始条件:顺序表L存在
//    操作结果:若e是L表中的数据元素,且不是最后一个,则用next_e返回它的后继,否则失败
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
//17、初始条件:顺序表L已存在
//    操作结果:依次对L的每一个数据元素调用函数visit()
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
	printf("顺序表list中数据元素3的前一个是%d\n",i);
	NextElem(list,4,&i);
	printf("顺序表list中数据元素4的后一个是%d\n",i);
	printf("调用ListTraverse方法\n");
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
//	printf("被删除的元素是%d\n",i);
//	printf("删除后的顺序表:\n");
//	Print_List(&list);
//	i=LocateElem_Sq(list,4,&equal);
//	printf("4在顺序表中的位置%d\n",i);
//	printf("调用ListLength方法返回顺序表的长度:%d\n",ListLength(list));
//	GetElem(list,3,&i);
//	printf("调用GetElem方法取出表中第3个元素:%d\n",i);





}




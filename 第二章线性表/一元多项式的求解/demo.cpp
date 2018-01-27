#include "stdio.h"    
#include "string.h"
#include "ctype.h"      
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define FALSE 0
#define TRUE 1
#define MAXSIZE 20 /* 存储空间初始分配量 */

typedef int Status;/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
//ElemType的定义---->项
typedef struct{
	float coef;//系数
	int expn;//指数
}term,ElemType;

typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LNode,*LinkList;

typedef LinkList polynomial;

//1、线性链表的初始化
Status InitList(LinkList *L){
	*L=(LinkList)malloc(sizeof(LNode));
	if(!(*L)){
		return ERROR;
	}
	(*L)->next=NULL;
	return OK;
}
//2、判断链表是否为空
Status ListEmpty(LinkList L)
{ 
    if(L->next)
        return FALSE;
    else
        return TRUE;
}

//3、删除一元二次多项式中第i个项
Status ListDelete(LinkList *L,int i,ElemType *e) 
{ 
	int j;
	LinkList p,q;
	p = *L;
	j = 1;
	while (p->next && j < i)	/* 遍历寻找第i个元素 */
	{
        p = p->next;
        ++j;
	}
	if (!(p->next) || j > i) 
	    return ERROR;           /* 第i个元素不存在 */
	q = p->next;
	p->next = q->next;			/* 将q的后继赋值给p的后继 */
	*e = q->data;               /* 将q结点中的数据给e */
	free(q);                    /* 让系统回收此结点，释放内存 */
	printf("删除成功\n");
	return OK;
}

//4、在线性表L中第i个位置插入元素e
Status ListInsert_L(LinkList *L,int i,ElemType e){
	int j;
	LinkList p,s;
	p=*L;
	j=0;
	while(p&&j<i-1){
		p=p->next;
		j++;
	}
	if(!p||j>i-1){//第i个元素不存在
		return ERROR;
	}
	s=(LinkList)malloc(sizeof(LNode));
	s->data=e;
	s->next=p->next;
	p->next=s;
	return OK;
}
//5、访问函数
Status visit(ElemType e){
	printf("系数:%f\t指数:%d",e.coef,e.expn);
    return OK;
}
//6、打印线性链表中所有元素
Status ListTraverse(LinkList L){
	LinkList p=L->next;
	while(p){
		visit(p->data);
		p=p->next;
	}
	printf("\n");
	return OK;
}
//7、若有序链表中存在与e满足compre()==0的元素,则q指向L中第一个值为e的节点的位置,并返回True
//否则q指向第一个compare()>0的元素的前驱的位置,并返回FALSE
//题目意思应该是要按照指数顺序存储
Status LocateElem(LinkList L,ElemType e,int *q,int (*compare)(ElemType,ElemType)){
	int i=1;
	LinkList p=L->next;
	while(p){
		if(compare(p->data,e)==0){
             *q=i;
			 return TRUE;
		}else if(compare(p->data,e)>0){
			 *q=i;//这里没有指向前驱,因为自定义函数ListInsert_L所需的插入位置所要求
			return FALSE;
		}
		i++;
		p=p->next;
	  }
	*q=i;
	return FALSE;
}
//8、自定义比较函数--->比较系数
int compareValue(ElemType x,ElemType y){
	if(x.expn==y.expn){
		return 0;
	}else if(x.expn>y.expn){
		return 1;
	}else{
		return -1;
	}
}
//9、按照有序判定函数compare()的约定,将值为e的节点插入到有序链表L的合适位置中...
//即建立一个按指数升序排列的一元多项式
//用10中的方式可以实现此功能,即借助LocateElem,ListInsert_L故省略此部分
Status OrderInsert(LinkList *L,ElemType e,int(*compare)(ElemType,ElemType)){
  return 0;

}
//10、输入m项的系数和指数,建立表示一元多项式的有序列表p
void CreatePolyn(polynomial *p,int m){
	ElemType e;
	int i,q;
	LinkList h;
	InitList(p);
	h=*p;
	e.coef=0.0;
	e.expn=-1;
    h->data=e;
	for(i=1;i<=m;i++){
		printf("请输入第%d项的系数与指数\n",i);
		scanf("%f%d",&e.coef,&e.expn);
		if(!LocateElem(*p,e,&q,compareValue)){
			printf("插入位置:%d\n",q);
			ListInsert_L(p,q,e);
		}
	}

}
//11、销毁一元多项式
void DestroyPolyn(polynomial *L){
	LinkList p,q;
	p=(*L)->next;           /*  p指向第一个结点 */
	while(p)                /*  没到表尾 */
	{
		q=p->next;
		free(p);
		p=q;
	}
	(*L)->next=NULL;        /* 头结点指针域为空 */
}
//12、打印一元多项式
void PrintPolyn(polynomial L){
	   LinkList p=L->next;
	   while(p){
	       printf("%.1fx^%d\t",p->data.coef,p->data.expn);
		   p=p->next;
	   }
	   printf("\n");
}
//13、返回一元多项式中的项数
int PolynLength(polynomial L){
	int i=0;
    LinkList p=L->next; /* p指向第一个结点 */
    while(p)                        
    {
        i++;
        p=p->next;
    }
    return i;
}
//14、设置多项式L中第i项的系数为sum
void SetCurElem(polynomial L,float sum,int i){
	int j=0;
	LinkList p;
	p=L;
	while(j<i){
		p=p->next;
		j++;
	}
	p->data.coef=sum;
	printf("赋值完成\n");
}
//15、向一元多项式Pa追加Pb中剩余节点
void Append(polynomial *Pa,LinkList qb){
	int i;
	LinkList ha=*Pa;
	while(qb){
         LocateElem(ha,qb->data,&i,compareValue);
         ListInsert_L(Pa,i,qb->data);
         qb=qb->next;
	}
}
//16、完成多项式的相加运算,Pa=Pa+Pb,并销毁Pb
void AddPolyn(polynomial *Pa,polynomial *Pb){
	LinkList ha,hb,qa,qb;
	ElemType elem;
	int i;
	float sum;
	ha=*Pa;//头节点
	hb=*Pb;
	qa=ha->next;
	qb=hb->next;
	while(qa&&qb){
		switch(compareValue(qa->data,qb->data)){
		case -1:
			qa=qa->next;
			break;
		case 0:
            sum=qa->data.coef+qb->data.coef;
			if(sum!=0.0){
                //修改Pa中对应节点的系数
				LocateElem(ha,qb->data,&i,compareValue);
				printf("Pb此时对应节点在Pa中的位置%d\n",i);
                SetCurElem(ha,sum,i);
			}else{
				//删除Pa中对应节点
				LocateElem(ha,qb->data,&i,compareValue);
				printf("删除pa中的节点:\n");
				ListDelete(Pa,i,&elem);
			}  
			qa=qa->next;
			qb=qb->next;
			ListDelete(Pb,i,&elem);//注意:与qa=qa->next,qb=qb->next的顺序不能反过来
			break;
		case 1:
			//将Pb中的当前节点插入到Pa中
            LocateElem(ha,qb->data,&i,compareValue);//定位Pb的当前节点在Pa的位置
			printf("Pb的当前节点应插入到Pa的第%d位\n",i);
            ListInsert_L(Pa,i,qb->data);//向Pa的位置插入Pb的当前节点
			//删除Pb的当前节点
            LocateElem(hb,qb->data,&i,compareValue);
			printf("Pb的当前节点在Pb中的第%d位\n",i);
			qb=qb->next;
			if(ListDelete(Pb,i,&elem)){
     			printf("删除Pb的当前节点\n");
			}		
			break;
		}
	}
	if(!ListEmpty(hb)){
		printf("链接Pb的剩余节点到Pa\n");
		//将Pb中的剩余节点放入Pa中
        Append(Pa,qb);
		//释放Pb的头结点
        free(hb);
	}
}
//17、完成多项式的相减运算,参照16
//18、完成多项式的相乘运算,参照16
void main(){
//	LinkList L;
//	printf("请依次输入3个项的系数及指数\n");
//	CreatePolyn(&L,3);
//  ListTraverse(L);
//	DestroyPolyn(&L);
//	printf("完成销毁操作后,一元二次多项式:\n");
//	ListTraverse(L);
//	PrintPolyn(L);
//	printf("此时一元多项式有%d个项\n",PolynLength(L));
	LinkList Pa,Pb;
    printf("Pa请依次输入2个项的系数及指数\n");
	CreatePolyn(&Pa,2);
	printf("Pb请依次输入2个项的系数及指数\n");
	CreatePolyn(&Pb,2);
	AddPolyn(&Pa,&Pb);
	printf("下面打印Pa:\n");
	PrintPolyn(Pa);
	printf("下面打印Pb:\n");
//	PrintPolyn(Pb);
//	PrintPolyn(Pb);

}

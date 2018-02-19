#include <stdio.h>    
#include <string.h>
#include <ctype.h>      
#include <stdlib.h>   
#include <io.h>  
#include <math.h>  
#include <time.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAX_LENGTH_INSERT_SORT 7 /* 用于快速排序时判断是否选用插入排序阙值 */

typedef int Status; 


#define MAXSIZE 10000  /* 用于要排序数组个数最大值，可根据需要修改 */

typedef struct{
	int r[MAXSIZE+1];//用于存储排序数组
	int length;//记录顺序表的长度
}SqList;

/*****************************************************算法实现**********************************/
//1、交换元素
void swap(SqList *L,int i,int j){
	int temp=L->r[i];
	L->r[i]=L->r[j];
	L->r[j]=temp;
}

//2、打印
void print(SqList L){
	int i;
	for(i=1;i<L.length;i++){
		printf("%d,",L.r[i]);
	}
	printf("%d",L.r[i]);
	printf("\n");
}
//3、对顺序表做交换排序(冒泡初级)
void BubbleSort0(SqList *L){
	int i,j;
	for(i=1;i<L->length;i++){
		for(j=i+1;j<=L->length;j++){
			if(L->r[i]>L->r[j]){
				swap(L,i,j);
			}
		}
	}
}

//4、冒泡排序
void BubbleSort(SqList *L){
	int i,j;
	for(i=1;i<L->length;i++){
		for(j=L->length-1;j>=i;j--){
			if(L->r[j]>L->r[j+1]){
				swap(L,j,j+1);
			}
		}
	}
}

//5、冒泡排序的改进
void BubbleSort2(SqList *L){
	int i,j;
	Status flag=TRUE;
	for(i=1;i<L->length&&flag;i++){
		flag=FALSE;
		for(j=L->length-1;j>=i;j--){
			if(L->r[j]>L->r[j+1]){
				swap(L,j,j+1);
				flag=TRUE;//有数据需要交换则为true
			}
		}
	}
}
//6、简单选择排序
void SelectSort(SqList *L){
	int i,j,min;
	for(i=1;i<L->length;i++){
		min=i;
		for(j=i+1;j<=L->length;j++){
			if(L->r[min]>L->r[j]){
				min=j;
			}
		}
		if(i!=min){
			swap(L,i,min);
		}
	}
}
//7、直接插入排序
void InsertSort(SqList *L){
	int i,j;
	for(i=2;i<=L->length;i++){
		if(L->r[i]<L->r[i-1]){
			L->r[0]=L->r[i];//设置哨兵
			for(j=i-1;L->r[j]>L->r[0];j--){
				L->r[j+1]=L->r[j];//元素后移
			}
			L->r[j+1]=L->r[0];//插入元素L->r[0]到合适的位置
		}
	}
}
//8、希尔排序
void ShellSort(SqList *L){
	int i,j,k=0;
	int increment=L->length;
	do{
		increment=increment/3+1;//增量
		for(i=increment+1;i<=L->length;i++){
			if(L->r[i]<L->r[i-increment]){//后面的小于前面的，进行交换操作
				L->r[0]=L->r[i];
				for(j=i-increment;j>0&&L->r[0]<L->r[j];j-=increment){
					L->r[j+increment]=L->r[j];
				}
				L->r[j+increment]=L->r[0];
			}
		}
		printf("第%d趟排序:",++k);
		print(*L);
	}while(increment>1);
}
//9、堆排序
//调整为大顶堆
void HeapAdjust(SqList *L,int s,int m){
	int temp,j;
	temp=L->r[s];//哨兵
	for(j=2*s;j<=m;j*=2){
		//找到顶点s的左，右孩子中最大的一个
		if(j<m&&L->r[j]<L->r[j+1]){
			j++;
		}
		if(temp>=L->r[j]){
			break;
		}
		L->r[s]=L->r[j];//让s节点取最大值
		s=j;
	}
	L->r[s]=temp;
}
//堆排序
void HeapSort(SqList *L){
	int i;
	for(i=L->length/2;i>0;i--){
		HeapAdjust(L,i,L->length);//构建大顶堆
	}
	for(i=L->length;i>1;i--){
		swap(L,1,i);//将堆顶记录与未经过排序子序列的最后一个记录交换
		HeapAdjust(L,1,i-1);//重新调整为大顶堆
	}
}
//10、归并排序
//将有序的SR[i...m]和SR[m+1...n]归并为有序的TR[i...n]
void Merge(int SR[],int TR[],int i,int m,int n){
	int j,k,l;
	for(j=m+1,k=i;i<=m && j<=n;k++){	//将SR中记录由小到大地并入TR
		if (SR[i]<SR[j])
			TR[k]=SR[i++];
		else
			TR[k]=SR[j++];
	}
	if(i<=m){
		for(l=0;l<=m-i;l++)
			TR[k+l]=SR[i+l];		//将剩余的SR[i..m]复制到TR
	}
	if(j<=n){
		for(l=0;l<=n-j;l++)
			TR[k+l]=SR[j+l];		//将剩余的SR[j..n]复制到TR
	}
}


//递归
//将SR[s..t]归并排序为TR1[s..t]
void MSort(int SR[],int TR1[],int s, int t){
	int m;
	int TR2[MAXSIZE+1];
	if(s==t)
		TR1[s]=SR[s];
	else{
		m=(s+t)/2;				// 将SR[s..t]平分为SR[s..m]和SR[m+1..t]
		MSort(SR,TR2,s,m);		// 递归地将SR[s..m]归并为有序的TR2[s..m]
		MSort(SR,TR2,m+1,t);	// 递归地将SR[m+1..t]归并为有序的TR2[m+1..t]
		Merge(TR2,TR1,s,m,t);	// 将TR2[s..m]和TR2[m+1..t]归并到TR1[s..t]
	}
}

//对顺序表L作归并排序
void MergeSort(SqList *L){ 
 	MSort(L->r,L->r,1,L->length);
}

//非递归算法
void MergePass(int SR[],int TR[],int s,int n){
	int i=1;
	int j;
	while(i<=n-2*s+1){
		Merge(SR,TR,i,i+s-1,i+2*s-1);
		i=i+2*s;
	}
	if(i<n-s+1){
		Merge(SR,TR,i,i+s-1,n);
	}else{
		for(j=i;j<=n;j++){
			TR[j]=SR[j];
		}
	}
}
void MergeSort2(SqList *L){
	int *TR=(int *)malloc(L->length*sizeof(int));//用于存放结果
	int k=1;
	while(k<L->length){
		MergePass(L->r,TR,k,L->length);
		k=2*k;
		MergePass(TR,L->r,k,L->length);
		k=2*k;
	}
}

//快速排序
int Partition(SqList *L,int low,int high){
	int pivotkey;
	pivotkey=L->r[low];//用子表中第一个记录作为枢轴
	while(low<high){
		while(low<high&&L->r[high]>=pivotkey){
			high--;
		}
		swap(L,low,high);//将比中间记录小的记录交换到低端
		while(low<high&&L->r[low]<=pivotkey){
			low++;
		}
		swap(L,low,high);
	}
	return low;//返回枢轴所在位置
}
void QSort(SqList *L,int low,int high){
	int pivot;
	if(low<high){
		pivot=Partition(L,low,high);//将L->r一分为二，分别对这两部分再进行sort
		QSort(L,low,pivot-1);
		QSort(L,pivot+1,high);
	}
}
void QuickSort(SqList *L){
	QSort(L,1,L->length);
}
//快速排序的改进
int Partition1(SqList *L,int low,int high){
	int pivotkey;
	int m=low+(high-low)/2;
	//三数取中法确定枢轴---->让r[low]为左中右三个关键字的中间值
	if(L->r[low]>L->r[high]){
		swap(L,low,high);
	}
	if(L->r[m]>L->r[high]){
		swap(L,high,m);
	}
	if(L->r[m]>L->r[low]){
		swap(L,m,low);
	}
    pivotkey=L->r[low]; /* 用子表的第一个记录作枢轴记录 */
	L->r[0]=pivotkey;  /* 将枢轴关键字备份到L->r[0] */
	while(low<high) /*  从表的两端交替地向中间扫描 */
	{ 
		 while(low<high&&L->r[high]>=pivotkey)
			high--;
		 L->r[low]=L->r[high];
		 while(low<high&&L->r[low]<=pivotkey)
			low++;
		 L->r[high]=L->r[low];
	}
	L->r[low]=L->r[0];
	return low; /* 返回枢轴所在位置 */
}

void QSort1(SqList *L,int low,int high){
	int pivot;
	if((high-low)>MAX_LENGTH_INSERT_SORT){
	     while(low<high){
			pivot=Partition1(L,low,high); 
			QSort1(L,low,pivot-1);		//对低子表递归排序 
		    //QSort(L,pivot+1,high);		//  对高子表递归排序 
			low=pivot+1;	// 尾递归---等同于QSort(L,p+1,high);
		}
	}else{
		InsertSort(L);
	}
}
void QuickSort1(SqList *L){ 
	QSort1(L,1,L->length);
}
#define N 9
int main(){
   int i;
   
   /* int d[N]={9,1,5,8,3,7,4,6,2}; */
   int d[N]={50,10,90,30,70,40,80,60,20};
   /* int d[N]={9,8,7,6,5,4,3,2,1}; */

   SqList l0,l1,l2,l3,l4,l5,l6,l7,l8,l9,l10;
   
   for(i=0;i<N;i++)
     l0.r[i+1]=d[i];
   l0.length=N;
   l1=l2=l3=l4=l5=l6=l7=l8=l9=l10=l0;
   printf("排序前:\n");
   print(l0);

   printf("初级冒泡排序:\n");
   BubbleSort0(&l0);
   print(l0);
   
   printf("冒泡排序:\n");
   BubbleSort(&l1);
   print(l1);
   
   printf("改进冒泡排序:\n");
   BubbleSort2(&l2);
   print(l2);
   
   printf("选择排序:\n");
   SelectSort(&l3);
   print(l3);
   
   printf("直接插入排序:\n");
   InsertSort(&l4);
   print(l4);

   printf("希尔排序:\n");
   ShellSort(&l5);
   print(l5);
	
   printf("堆排序:\n");
   HeapSort(&l6);
   print(l6);

   printf("归并排序（递归）:\n");
   MergeSort(&l7);
   print(l7);

   printf("归并排序（非递归）:\n");
   MergeSort2(&l8);
   print(l8);

   printf("快速排序:\n");
   QuickSort(&l9);
   print(l9);

   printf("改进快速排序:\n");
   QuickSort1(&l10);
   print(l10);


    /*大数据排序*/
	/* 
	srand(time(0));  
	int Max=10000;
	int d[10000];
	int i;
	SqList l0;
	for(i=0;i<Max;i++)
		d[i]=rand()%Max+1;
	for(i=0;i<Max;i++)
		l0.r[i+1]=d[i];
	l0.length=Max;
	MergeSort(l0);
	print(l0);
	*/
	return 0;
}















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

#define MAX_LENGTH_INSERT_SORT 7 /* ���ڿ�������ʱ�ж��Ƿ�ѡ�ò���������ֵ */

typedef int Status; 


#define MAXSIZE 10000  /* ����Ҫ��������������ֵ���ɸ�����Ҫ�޸� */

typedef struct{
	int r[MAXSIZE+1];//���ڴ洢��������
	int length;//��¼˳���ĳ���
}SqList;

/*****************************************************�㷨ʵ��**********************************/
//1������Ԫ��
void swap(SqList *L,int i,int j){
	int temp=L->r[i];
	L->r[i]=L->r[j];
	L->r[j]=temp;
}

//2����ӡ
void print(SqList L){
	int i;
	for(i=1;i<L.length;i++){
		printf("%d,",L.r[i]);
	}
	printf("%d",L.r[i]);
	printf("\n");
}
//3����˳�������������(ð�ݳ���)
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

//4��ð������
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

//5��ð������ĸĽ�
void BubbleSort2(SqList *L){
	int i,j;
	Status flag=TRUE;
	for(i=1;i<L->length&&flag;i++){
		flag=FALSE;
		for(j=L->length-1;j>=i;j--){
			if(L->r[j]>L->r[j+1]){
				swap(L,j,j+1);
				flag=TRUE;//��������Ҫ������Ϊtrue
			}
		}
	}
}
//6����ѡ������
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
//7��ֱ�Ӳ�������
void InsertSort(SqList *L){
	int i,j;
	for(i=2;i<=L->length;i++){
		if(L->r[i]<L->r[i-1]){
			L->r[0]=L->r[i];//�����ڱ�
			for(j=i-1;L->r[j]>L->r[0];j--){
				L->r[j+1]=L->r[j];//Ԫ�غ���
			}
			L->r[j+1]=L->r[0];//����Ԫ��L->r[0]�����ʵ�λ��
		}
	}
}
//8��ϣ������
void ShellSort(SqList *L){
	int i,j,k=0;
	int increment=L->length;
	do{
		increment=increment/3+1;//����
		for(i=increment+1;i<=L->length;i++){
			if(L->r[i]<L->r[i-increment]){//�����С��ǰ��ģ����н�������
				L->r[0]=L->r[i];
				for(j=i-increment;j>0&&L->r[0]<L->r[j];j-=increment){
					L->r[j+increment]=L->r[j];
				}
				L->r[j+increment]=L->r[0];
			}
		}
		printf("��%d������:",++k);
		print(*L);
	}while(increment>1);
}
//9��������
//����Ϊ�󶥶�
void HeapAdjust(SqList *L,int s,int m){
	int temp,j;
	temp=L->r[s];//�ڱ�
	for(j=2*s;j<=m;j*=2){
		//�ҵ�����s�����Һ���������һ��
		if(j<m&&L->r[j]<L->r[j+1]){
			j++;
		}
		if(temp>=L->r[j]){
			break;
		}
		L->r[s]=L->r[j];//��s�ڵ�ȡ���ֵ
		s=j;
	}
	L->r[s]=temp;
}
//������
void HeapSort(SqList *L){
	int i;
	for(i=L->length/2;i>0;i--){
		HeapAdjust(L,i,L->length);//�����󶥶�
	}
	for(i=L->length;i>1;i--){
		swap(L,1,i);//���Ѷ���¼��δ�������������е����һ����¼����
		HeapAdjust(L,1,i-1);//���µ���Ϊ�󶥶�
	}
}
//10���鲢����
//�������SR[i...m]��SR[m+1...n]�鲢Ϊ�����TR[i...n]
void Merge(int SR[],int TR[],int i,int m,int n){
	int j,k,l;
	for(j=m+1,k=i;i<=m && j<=n;k++){	//��SR�м�¼��С����ز���TR
		if (SR[i]<SR[j])
			TR[k]=SR[i++];
		else
			TR[k]=SR[j++];
	}
	if(i<=m){
		for(l=0;l<=m-i;l++)
			TR[k+l]=SR[i+l];		//��ʣ���SR[i..m]���Ƶ�TR
	}
	if(j<=n){
		for(l=0;l<=n-j;l++)
			TR[k+l]=SR[j+l];		//��ʣ���SR[j..n]���Ƶ�TR
	}
}


//�ݹ�
//��SR[s..t]�鲢����ΪTR1[s..t]
void MSort(int SR[],int TR1[],int s, int t){
	int m;
	int TR2[MAXSIZE+1];
	if(s==t)
		TR1[s]=SR[s];
	else{
		m=(s+t)/2;				// ��SR[s..t]ƽ��ΪSR[s..m]��SR[m+1..t]
		MSort(SR,TR2,s,m);		// �ݹ�ؽ�SR[s..m]�鲢Ϊ�����TR2[s..m]
		MSort(SR,TR2,m+1,t);	// �ݹ�ؽ�SR[m+1..t]�鲢Ϊ�����TR2[m+1..t]
		Merge(TR2,TR1,s,m,t);	// ��TR2[s..m]��TR2[m+1..t]�鲢��TR1[s..t]
	}
}

//��˳���L���鲢����
void MergeSort(SqList *L){ 
 	MSort(L->r,L->r,1,L->length);
}

//�ǵݹ��㷨
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
	int *TR=(int *)malloc(L->length*sizeof(int));//���ڴ�Ž��
	int k=1;
	while(k<L->length){
		MergePass(L->r,TR,k,L->length);
		k=2*k;
		MergePass(TR,L->r,k,L->length);
		k=2*k;
	}
}

//��������
int Partition(SqList *L,int low,int high){
	int pivotkey;
	pivotkey=L->r[low];//���ӱ��е�һ����¼��Ϊ����
	while(low<high){
		while(low<high&&L->r[high]>=pivotkey){
			high--;
		}
		swap(L,low,high);//�����м��¼С�ļ�¼�������Ͷ�
		while(low<high&&L->r[low]<=pivotkey){
			low++;
		}
		swap(L,low,high);
	}
	return low;//������������λ��
}
void QSort(SqList *L,int low,int high){
	int pivot;
	if(low<high){
		pivot=Partition(L,low,high);//��L->rһ��Ϊ�����ֱ�����������ٽ���sort
		QSort(L,low,pivot-1);
		QSort(L,pivot+1,high);
	}
}
void QuickSort(SqList *L){
	QSort(L,1,L->length);
}
//��������ĸĽ�
int Partition1(SqList *L,int low,int high){
	int pivotkey;
	int m=low+(high-low)/2;
	//����ȡ�з�ȷ������---->��r[low]Ϊ�����������ؼ��ֵ��м�ֵ
	if(L->r[low]>L->r[high]){
		swap(L,low,high);
	}
	if(L->r[m]>L->r[high]){
		swap(L,high,m);
	}
	if(L->r[m]>L->r[low]){
		swap(L,m,low);
	}
    pivotkey=L->r[low]; /* ���ӱ�ĵ�һ����¼�������¼ */
	L->r[0]=pivotkey;  /* ������ؼ��ֱ��ݵ�L->r[0] */
	while(low<high) /*  �ӱ�����˽�������м�ɨ�� */
	{ 
		 while(low<high&&L->r[high]>=pivotkey)
			high--;
		 L->r[low]=L->r[high];
		 while(low<high&&L->r[low]<=pivotkey)
			low++;
		 L->r[high]=L->r[low];
	}
	L->r[low]=L->r[0];
	return low; /* ������������λ�� */
}

void QSort1(SqList *L,int low,int high){
	int pivot;
	if((high-low)>MAX_LENGTH_INSERT_SORT){
	     while(low<high){
			pivot=Partition1(L,low,high); 
			QSort1(L,low,pivot-1);		//�Ե��ӱ�ݹ����� 
		    //QSort(L,pivot+1,high);		//  �Ը��ӱ�ݹ����� 
			low=pivot+1;	// β�ݹ�---��ͬ��QSort(L,p+1,high);
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
   printf("����ǰ:\n");
   print(l0);

   printf("����ð������:\n");
   BubbleSort0(&l0);
   print(l0);
   
   printf("ð������:\n");
   BubbleSort(&l1);
   print(l1);
   
   printf("�Ľ�ð������:\n");
   BubbleSort2(&l2);
   print(l2);
   
   printf("ѡ������:\n");
   SelectSort(&l3);
   print(l3);
   
   printf("ֱ�Ӳ�������:\n");
   InsertSort(&l4);
   print(l4);

   printf("ϣ������:\n");
   ShellSort(&l5);
   print(l5);
	
   printf("������:\n");
   HeapSort(&l6);
   print(l6);

   printf("�鲢���򣨵ݹ飩:\n");
   MergeSort(&l7);
   print(l7);

   printf("�鲢���򣨷ǵݹ飩:\n");
   MergeSort2(&l8);
   print(l8);

   printf("��������:\n");
   QuickSort(&l9);
   print(l9);

   printf("�Ľ���������:\n");
   QuickSort1(&l10);
   print(l10);


    /*����������*/
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















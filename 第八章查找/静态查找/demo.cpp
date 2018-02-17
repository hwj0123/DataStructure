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

typedef int Status;	/* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */ 
/**************************�㷨ʵ��*****************************/

//1�����ڱ�˳�����---->˳�����
int Sequential_Search(int *a,int n,int key){
	int i;
	for(i=1;i<=n;i++){
		if(a[i]==key){
			return i;
		}
	}
	return 0;
}
//2�����ڱ�˳�����--->˳�����
int Sequential_Search2(int *a,int n,int key){
	int i;
	a[0]=key;
	i=n;
	while(a[i]!=key){
		i--;
	}
	return i;
}
//3���۰����---->��������
int Binary_Search(int *a,int n,int key){
	int low,high,mid;
	low=1;
	high=n;
	while(low<=high){
		mid=(low+high)/2;
		if(key<a[mid]){
			high=mid-1;
		}else if(key>a[mid]){
			low=mid+1;
		}else{
			return mid;
		}
	}
	return 0;
}
//4����ֵ����--->˳������
int Interpolation_Search(int *a,int n,int key){
	int low,high,mid;
	low=1;
	high=n;
	while(low<=high){
		//��ֵ���ʽ
		mid=low+(high-low)*(key-a[low])/(a[high]-a[low]);
		if(key<a[mid]){
			high=mid-1;
		}else if(key>a[mid]){
			low=mid+1;
		}else{
			return mid;
		}
	}
	return 0;
}
//5��������������--->��������
int F[100];//�洢����������
int Fibonacci_Search(int *a,int n,int key){
	int low,high,mid,i,k=0;
	low=1;
	high=n;
	while(n>F[k]-1){
		k++;
	}
	while(low<=high){
		mid=low+F[k-1]-1;
		if(key<a[mid]){
			high=mid-1;
			k=k-1;
		}else if(key>a[mid]){
			low=mid+1;
			k=k-2;
		}else{
			if(mid<=n){
				return mid;
			}else{
				return n;
			}
		}
	}
	return 0;
}


void main(){
	int a[MAXSIZE+1],i,result;
	int arr[MAXSIZE]={0,1,16,24,35,47,59,62,73,88,99};
	for(i=0;i<=MAXSIZE;i++){
		a[i]=i;
	}
	result=Sequential_Search(a,MAXSIZE,MAXSIZE);//˳�����1
	printf("Sequential_Search:%d\n",result);
	result=Sequential_Search2(a,MAXSIZE,MAXSIZE);//˳�����2
	printf("Sequential_Search2:%d\n",result);
	result=Binary_Search(arr,10,62);//�۰����
	printf("Binary_Search:%d\n",result);
	result=Interpolation_Search(arr,10,62);//��ֵ����
	printf("Interpolation_Search:%d\n",result);

	F[0]=0;
	F[1]=1;
	for(i=2;i<100;i++){
		F[i]=F[i-1]+F[i-2];
	}
	result=Fibonacci_Search(arr,10,62);
	printf("Fibonacci_Search:%d\n",result);

}
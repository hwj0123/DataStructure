#include<stdio.h>
int count;//�ᶯ����
void move(char x,int n,char z){
	printf("%d move disk %d from %c to %c\n",++count,n,x,z);
}
void hanoi(int n,char x,char y,char z){
	if(n==1){
		move(x,1,z);
	}else{
		hanoi(n-1,x,z,y);//��x�ϱ��Ϊ1��n-1��Բ���Ƶ�y��,z��������
		move(x,n,z);//�����Ϊn��Բ�̴�x�Ƶ�z
		hanoi(n-1,y,x,z);//��y�ϱ��Ϊ1��n-1��Բ���Ƶ�z��,x��������
	}
}
void main(){
	hanoi(3,'A','B','C');
}
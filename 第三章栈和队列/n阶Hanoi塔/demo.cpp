#include<stdio.h>
int count;//搬动计数
void move(char x,int n,char z){
	printf("%d move disk %d from %c to %c\n",++count,n,x,z);
}
void hanoi(int n,char x,char y,char z){
	if(n==1){
		move(x,1,z);
	}else{
		hanoi(n-1,x,z,y);//将x上编号为1到n-1的圆盘移到y上,z作辅助塔
		move(x,n,z);//将编号为n的圆盘从x移到z
		hanoi(n-1,y,x,z);//将y上编号为1至n-1的圆盘移到z上,x做辅助塔
	}
}
void main(){
	hanoi(3,'A','B','C');
}
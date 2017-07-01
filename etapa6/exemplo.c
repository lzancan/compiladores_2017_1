#include <stdio.h>

int a=3;

int func(){
	a=5-a;
	a=a+a;
}
int main(){
	a=a+2;
}

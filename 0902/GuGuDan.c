#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
int main(void)
{
	int i, j;
	for(j=1;j<=9;j++)
	{
		//clrscr();
		system("cls");
		for(i=1;i<=9;i++)
			printf("%2d*%2d=%2d\n", j, i, j*i);
		printf("�ƹ�Ű�� �����ÿ�.\n");
		getch();
	}
	return 0;
}

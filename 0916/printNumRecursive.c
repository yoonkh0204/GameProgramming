#include <stdio.h>
#include <conio.h>
#include <math.h>
void serial_number(long number);
void reverse_number(long number);
int main(void)
{
	long number=12345698;
	printf("�Է� ���� : %ld\n\n", number);
	
	printf("���� �������� ���\n");
	serial_number(number);
	
	printf("\n���� �������� ���\n");
	reverse_number(number);
	
	printf("press any key to continue.......");
	getch();
	
	return 0;
}
void serial_number(long number)
{
	if (number>0)
	{
		serial_number(number/10);
		printf("%ld\n", number%10);
	}
	else
		return;
}
void reverse_number(long number)
{
	printf("%ld\n", number%10);
	if((number/10)>0)
		reverse_number(number/10);
	else
		return;
}


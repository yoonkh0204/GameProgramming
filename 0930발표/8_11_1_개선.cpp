#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

void gotoxy(int x, int y);
void game_control(int order, char *name, char **sol, double **check, int quest);
void display_result(int user, int *order, double **check, char **name, char **sol, int quest);
void display_rule(void);
void display_flag(char key);
void erase_animation(void);

int main(void)
{
	int i, j, user_number, quest_number, rnd, temp;
	int l = 0;
	int *order; 
	char **solution;
	double **time_check;
	char buffer[30];
	srand(time(NULL));
	printf("û��/��� ����\n\n");
	printf("���ӿ� ������ �ο����� �Է��ϰ� Enter>");
	scanf("%d", &user_number);
	printf("\n�ִ� ������ ������ �Է��ϰ� Enter>");
	scanf("%d", &quest_number);
	
	order = (int*)malloc(sizeof(int) * user_number);
	for(i=0;i<user_number;i++)
		order[i] = i;
		
	solution = (char**)malloc(sizeof(char*)*user_number);
	for(i=0;i<user_number;i++)
		solution[i] = (char*)malloc(sizeof(char)*quest_number);
	
	time_check = (double**)malloc(sizeof(double*)*user_number);
	for(i=0;i<user_number;i++)
		time_check[i] = (double*)malloc(sizeof(double)*quest_number);	
		
	char *user_name[user_number];
	for(i=0;i<user_number;i++)
	{
		printf("%d�� �������� �̸��� �Է��ϰ� Enter>", i+1);
		scanf("%s", buffer);
		l = strlen(buffer);
		if(l>0){
			char *newstrarr = (char*)malloc(sizeof(char) * (l+1));
			strcpy(newstrarr, buffer);
			user_name[i] = newstrarr;
		}
	}
	printf("���� �ѱ��� ����Ͽ��ٸ� ����Ű�� �ٲٽʽÿ�.\n");
	printf("�ƹ�Ű�� �����ÿ�.\n");
	getch();
   printf("\n������ ������ ������ �����ϴ�. \n");
   for(i=0;i<user_number;i++)
   {
 	rnd=rand()%user_number;
	temp=order[i];
	order[i]=order[rnd];
	order[rnd]=temp;
   }
   for(i=0;i<user_number;i++)
   {
		printf("%d�� : %s\n", i+1, user_name[order[i]]);
   }
   printf("�ƹ�Ű�� �����ÿ�.\n");
   getch();

   for(i=0;i<user_number;i++)
	game_control(order[i], user_name[order[i]], solution, 
		time_check, quest_number);

   printf("\n\n");
   printf("��� ������ �������ϴ�. \n");
   printf("�ƹ�Ű�� ������ ����� ǥ���մϴ�. \n");
   getch();
   display_result(user_number, order, time_check, user_name, 
   solution, quest_number);
   free(order);
   for(i=0;i<user_number;i++){
   		free(user_name[i]);
   		free(solution[i]);
   		free(time_check[i]);
   }
   free(solution);
   free(time_check);
   getch();
   return 0;
}


void gotoxy(int x, int y)
{
   COORD Pos = {x - 1, y - 1};
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void game_control(int order, char *name, char **sol, double **check, int quest)
{
   const char *flag[]={"û��", "���"};
   const char *question[]={"����!", "�÷�!", "����������", "�ø�������"};
   clock_t start, end;
   int i, j, rnd[4];
   char key;
   system("cls");
   gotoxy(1, 3);
   printf("%s�� �����Դϴ�. Ű ������ ������ �����ϴ�.", name);
   display_flag(0);
   display_rule();
   for(i=0;i<quest;i++)
   {
  		system("cls");
		rnd[0]=rand()%2;
		rnd[1]=rand()%4;
		display_flag(0);
		start=clock();
		gotoxy(5, 10);
		if (rnd[1]>1)
		{
	    	rnd[2]=rand()%2;
	    	rnd[3]=rand()%2;
	    	printf("%d: %s %s %s %s", i+1, flag[rnd[0]], question[rnd[1]], flag[rnd[2]], question[rnd[3]]);
  		}
		else
			printf("%d: %s %s", i+1, flag[rnd[0]], question[rnd[1]]);
    	key=getch();
    	end=clock();
    	switch(key)
    	{
    		case 'a':
    			display_flag(key);
    			Sleep(500);
				break;

            case 'z':
            	display_flag(key);
                Sleep(500);
                break;
            case 'k':
                display_flag(key);
                Sleep(500);
                break;

            case 'm':
                display_flag(key);
                Sleep(500);
		}
		check[order][i]=(double)(end-start)/CLK_TCK;
		if (rnd[1]>1)
		{
			if ((rnd[2]==0) && (rnd[3]==0) && (key=='z')&&(check[order][i]<1))
				sol[order][i]=1;
			else if ((rnd[2]==0) && (rnd[3]==1) && (key=='a')&&(check[order][i]<1))	
				sol[order][i]=1;
			else if ((rnd[2]==1) && (rnd[3]==0) && (key=='m')&&(check[order][i]<1))	
				sol[order][i]=1;
			else if ((rnd[2]==1) && (rnd[3]==1) && (key=='k')&&(check[order][i]<1))	
		        sol[order][i]=1;
			else
			{
				display_flag('x');
				Sleep(500);
				sol[order][i]=0;
				for(j=i+1;j<quest;j++){
					sol[order][j] = 0;
					check[order][j] = 0;
				}
				break;	
			}
		}
		else			
		{
			if ((rnd[0]==0) && (rnd[1]==0) && (key=='z')&&(check[order][i]<1))
				sol[order][i]=1;
			else if ((rnd[0]==0) && (rnd[1]==1) && (key=='a')&&(check[order][i]<1))	
				sol[order][i]=1;
			else if ((rnd[0]==1) && (rnd[1]==0) && (key=='m')&&(check[order][i]<1))	
				sol[order][i]=1;
			else if ((rnd[0]==1) && (rnd[1]==1) && (key=='k')&&(check[order][i]<1))	
				sol[order][i]=1;
			else
			{
				display_flag('x');
				Sleep(500);
				sol[order][i]=0;	
				for(j=i+1;j<quest;j++){
					sol[order][j] = 0;
					check[order][j] = 0;	
				}
				break;
			}
		}
    }
}

void display_result(int user, int *order, double **check, char **name, char **sol, int quest)
{
   int i, j, temp, *result;
   double *min_time;
   int victory_result = 0;
   double victory_time = 100;

   result = (int*)malloc(sizeof(int)*user);
   for(i=0;i<user;i++)
   		result[i] = 0;
   min_time = (double*)malloc(sizeof(double)*user);
   for(i=0;i<user;i++)
   		min_time[i] = 0;
   system("cls");
   printf("       ");
   for(i=0;i<user;i++)
	printf("%8s  ", name[order[i]]);
   printf("\n");
   for(j=0;j<quest;j++)
   {
	printf("    %d�� : ", j+1);
	for(i=0;i<user;i++)
	{   
		if (sol[order[i]][j])
		{
			printf("O");
			result[order[i]]+=1;
			min_time[order[i]]+=check[order[i]][j];
		}
		else
			printf("X");
		printf("%5.2f     ",check[order[i]][j]);	
	}
	printf("\n");
   }
   printf("\n");
   printf("��������:");
   for(i=0;i<user;i++)
	 printf("%7d    ", result[order[i]]);
   printf("\n");
   printf("�ҿ�ð�:");
   for(i=0;i<user;i++)
	 printf("%7.2f    ", min_time[order[i]]);
   printf("\n");
   for(i=0;i<user;i++)
	{
		if(result[order[i]]>victory_result){
			victory_result = result[order[i]];
			victory_time = min_time[order[i]];
			temp = order[i];	
		}
		else if(result[order[i]]==victory_result){
			if(victory_time > min_time[order[i]]){
				victory_time = min_time[order[i]];
				temp = order[i];
			}
		}
	}
	printf("���ڴ� ");
	printf("%8s!!	", name[temp]);
	printf("�������� : ");
	printf("%7d  ", result[temp]);
	printf("�ҿ�ð� : ");
	printf("%7.2f\n", min_time[temp]); 
   free(result);
   free(min_time);
}
void display_rule(void)
{
	gotoxy(1,4);
	printf("���ӽ��������� Ű�� ������ ������!\n");
	gotoxy(1, 6);
	printf("û�� �÷� : a    ��� �÷� : k");
	gotoxy(1, 7);
	printf("û�� ���� : z    ��� ���� : m");
	Sleep(2000);
	gotoxy(1, 8);
	printf("Ʋ���ų� �ð��ʰ��� GAME OVER!\n");
	printf("5�� �Ŀ� ������ �����մϴ�. �غ��ϼ���.");
	Sleep(5000);
}
void display_flag(char key)
{
    erase_animation();
    switch (key)
    {
		case 'a':
            gotoxy(58, 5);
            printf("��");
            gotoxy(54, 6);
            printf("����");
            gotoxy(54, 5);
            printf("��");
            gotoxy(60, 6);
            printf("��");
            gotoxy(62, 6);
            printf("��");
            gotoxy(58, 6);
            printf("��");
            gotoxy(58, 7);
            printf("��");
            gotoxy(58, 8);
            printf("��");
            gotoxy(57, 9);
            printf("��");
            gotoxy(59, 9);
            printf("��");
            break;    
        case 'z':
            gotoxy(58, 5);
            printf("��");
            gotoxy(54, 6);
            printf("����");
            gotoxy(54, 7);
            printf("��");
            gotoxy(60, 6);
            printf("��");
            gotoxy(62, 6);
            printf("��");
            gotoxy(58, 6);
            printf("��");
            gotoxy(58, 7);
            printf("��");
            gotoxy(58, 8);       
			printf("��");
            gotoxy(57, 9);
            printf("��");
            gotoxy(59, 9);
            printf("��");
            break;
        case 'k':
            gotoxy(58, 5);
            printf("��");
            gotoxy(56, 6);
            printf("��");
            gotoxy(54, 6);
            printf("��");
            gotoxy(60, 6);
            printf("����");
            gotoxy(62, 5);
            printf("��");
            gotoxy(58, 6);
            printf("��");
            gotoxy(58, 7);
            printf("��");
            gotoxy(58, 8);
            printf("��");
            gotoxy(57, 9);
            printf("��");
            gotoxy(59, 9);
            printf("��");
            break;
        case 'm':
            gotoxy(58, 5);
            printf("��");
            gotoxy(56, 6);
            printf("��");
            gotoxy(54, 6);
            printf("��");
            gotoxy(60, 6);
            printf("����");
            gotoxy(62, 7);
            printf("��");
            gotoxy(58, 6);
            printf("��");
            gotoxy(58, 7);
            printf("��");
            gotoxy(58, 8);
            printf("��");
            gotoxy(57, 9);
            printf("��");
            gotoxy(59, 9);
            printf("��");
            break;
        case 'x':
        	gotoxy(59,12);
        	printf("��");
        	gotoxy(58,12);
        	printf("��");
        	gotoxy(58,11);
        	printf("|");
        	gotoxy(58,13);
        	printf("|");
        	gotoxy(57,12);
        	printf("��");
        	gotoxy(56,11);
        	printf("|");
        	gotoxy(56,13);
        	printf("/");
        	gotoxy(57,15);
        	printf("Ż��!");
        	break;
        default:
            gotoxy(58, 5);
            printf("��");
            gotoxy(56, 6);
            printf("��");
            gotoxy(54, 6);
            printf("��");
            gotoxy(60, 6);
            printf("��");
            gotoxy(62, 6);
            printf("��");
            gotoxy(58, 6);
            printf("��");
            gotoxy(58, 7);
            printf("��");
            gotoxy(58, 8);
            printf("��");
            gotoxy(57, 9);
            printf("��");
            gotoxy(59, 9);
            printf("��");
        }
}
void erase_animation(void)
{
    gotoxy(58, 5);
    printf("  ");
    gotoxy(56, 6);
    printf("  ");
    gotoxy(54, 6);
    printf("  ");
    gotoxy(58, 6);
    printf("  ");
    gotoxy(58, 7);
    printf("  ");
    gotoxy(58, 8);
    printf("  ");
    gotoxy(57, 9);
    printf("  ");
    gotoxy(59, 9);
    printf("  ");     
    gotoxy(54,5);   
    printf("  ");    
    gotoxy(60,6);    
    printf("  ");    
    gotoxy(62,6);   
    printf("  ");    
    gotoxy(54,7);   
    printf("  ");  
    gotoxy(62,5);  
    printf("  ");  
    gotoxy(62,7);  
    printf("  ");   
    gotoxy(59,12); 
    printf("  ");    
    gotoxy(58,12);   
    printf("  ");   
    gotoxy(58,11);
    printf("  ");    
    gotoxy(58,13);
    printf("  ");
    gotoxy(57,12);
    printf("  ");
    gotoxy(56,11);
    printf("  ");
    gotoxy(56,13);
    printf("  ");
    gotoxy(57,15);
    printf("  ");
    gotoxy(56,6);
	printf("  ");
}

#include <stdio.h>
#include <windows.h> // �ܼ�â �ʱ�ȭ�� ���Ե� ���
#include <conio.h> // _getch�� ���Ե� ���
#include <stdlib.h> // �����Ҵ��� ���� ���
#include <string.h>
#define leapyear(year) ((year)%4==0 && ( (year)%100!=0 || (year)%400==0 )) //����������ũ�� 
#pragma warning(disable:4996)

//����ü ���Ḯ��Ʈ

int c = 0;
int year, month; // ������ ���� ������ ���� 
int count = 0;
int n;
int choice_day;

struct node {
	char title[100];
	char bookingOffice[500];
	struct node* preptr;
	struct node* nextptr;
}*stnode, * ennode;

void start(); // �Լ� ����
int input();
void calendar();
void AddNote();
void showNote();

void start() {		//����ȭ��
	printf("\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("\t\t\t\t\t\t  Ƽ�Ͽ��� ��� (��) \t\t\t\t\t");
	printf("\n\n\n\n");
	printf("\t\t\t\t\t\t  Ƽ�Ͽ��� Ȯ�� (��) \t\t\t\t\t");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

int input() {		// �Է¹��� ������ �� ���� 
	printf("��� �������� �Է��Ͻðڽ��ϱ�?");
	scanf_s("%d", &n);	// �����Ҵ����� �迭 �ޱ�
	return n;
}


void calendar() {
	int month_total[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 }; // �� ���� ���� �� (ù��° ���� ����) 
	int lastyear, day, i;
	FILE* file;

	printf("�⵵�� ���� �Է����ּ���.(YYYY MM): ");
	scanf_s("%d %d", &year, &month);

	if (month == 2 && leapyear(year)) // �ش�⵵�� �����̸�, 2���� �� 29�� 
		month_total[2] = 29;
	lastyear = year - 1; // �۳� ������ ����� ������ ����ϱ� ���� lastyear�� ���� 
	day = (lastyear + (lastyear / 4) - (lastyear / 100) + (lastyear / 400) + 1) % 7; /* lastyear : 1���� 365��, 1���� ���������� ������ �ѹ� �þ�� (365�� 7�� ������ 1�̱� ����) +(lastyear/4)-(lastyear/100)+(lastyear/400) : ������ ���������� ������ �ι� �þ�Ƿ�, lastyear���� �ִ� ��� ������ ���Ѵ� +1 : 1�� 1�� 1���� �Ͽ����� �ƴ϶� �������̹Ƿ� 1�� ���Ѵ� (0���� ����) %7 : ������ 7���� �̹Ƿ�, ���� ��갪�� 7�� ���� �������� year�� 1���� ù���� ���Ѵ� ���������� ���� 0:�Ͽ���, 1:������, 2:ȭ����, 3:������, 4:�����, 5:�ݿ���, 6:����� */

	for (i = 1;i < month;i++) // year�� month�� ���������� �� �� ���� ���ϱ� ���� for�� 
		day += month_total[i];
	day %= 7; // year�� month�� 1���� ���� ����
	printf("\n %d�� %d��\n", year, month); // year�� month�� Ÿ��Ʋ ��� 
	printf("\n	��	��	ȭ	��	��	��	��"); // ���� ����Ʈ ���

	for (i = -day;i < month_total[month];i++) {			// ��µ� �޷��� ���� ���� �� ���߿� ��½ÿ��� �ѹ��� ����� �޷��� ��� ���� �޷��� ��ĥ��� ��¥ ���� ����
		if ((i + day) % 7 == 0) // ��µ� ���ʰ� �Ͽ����̸�, ���� 
			printf("\n");
		if (i < 0) // month�� 1���� ��µǱ� ������ ��¥�� �������� ä�� 
			printf("	");
		else // ��¥ ��� 
			printf("	%d", i + 1);
	}
	printf("\n\n");
	getchar();
}


void AddNote(int n)		// ������ ���� Ƽ�Ͽ�����, ���̸�, ����ó�� �޴´�
{
	int i, day = 0;
	char title[100], bookingOffice[100];
	struct node* fnNode;
	FILE* fp = fopen("note.txt", "a");
	system("cls");

	fprintf(fp, "Ƽ���� ��¥ : ");	// ���Ͽ� �Է�
	printf(" Ƽ���� ��¥�� �Է��ϼ��� : ");		// �ܼ� â�� ���
	scanf(" %d", &day);			// �Է¹ޱ�
	fprintf(fp, "%d��\n", day);		// ���Ͽ� �Է�

	if (n >= 1)
	{
		stnode = (struct node*)malloc(sizeof(struct node));

		if (stnode != NULL)
		{
			fprintf(fp, " (1) �� �̸��� �Է��ϼ���. : "); // ù��° node �Է�
			printf(" (1) �� �̸��� �Է��ϼ���.: ");
			scanf(" %s", title);
			fprintf(fp, "%s\n", title);
			fprintf(fp, " (1) ����ó�� �Է��ϼ���. : ");
			printf(" (1) ����ó�� �Է��ϼ���. : ");
			scanf(" %s", bookingOffice);
			fprintf(fp, "%s\n", bookingOffice);

			strcpy(stnode->title, title);		// ���� node�鿡 ���� �Է�
			strcpy(stnode->bookingOffice, bookingOffice);
			stnode->preptr = NULL;
			stnode->nextptr = NULL;
			ennode = stnode;
			
			for (i = 2; i <= n; i++)
			{
				fnNode = (struct node*)malloc(sizeof(struct node));
				if (fnNode != NULL)				// �ι�° ���� node �Է�
				{
					fprintf(fp, " (%d) �� �̸��� �Է��ϼ���. : ", i);
					printf(" (%d) �� �̸��� �Է��ϼ���. : ", i);
					scanf(" %s", title);
					fprintf(fp, "%s\n", title);
					fprintf(fp, " (%d) ����ó�� �Է��ϼ���. : ", i);
					printf(" (%d) ����ó�� �Է��ϼ���. : ", i);
					scanf(" %s", bookingOffice);
					fprintf(fp, "%s\n", bookingOffice);

					strcpy(fnNode->title, title);
					strcpy(fnNode->bookingOffice, bookingOffice);
					fnNode->preptr = ennode;    // ���ο� node�� ���� node�� ����
					fnNode->nextptr = NULL;

					ennode->nextptr = fnNode;   // ���� node�� ���ο� node��  linking 
					ennode = fnNode;            // ������ node�� ���ο� �� �Է�
				}
				else
				{
					printf(" �Ҵ��� �޸𸮰� �����ϴ�.");
					break;
				}
			}
		}
		else
		{
			printf(" �Ҵ��� �޸𸮰� �����ϴ�.");
		}
		fprintf(fp, "\n");
		fclose(fp);
	}
}


void showNote() {

	struct node* tmp;
	int n = 1;

	if (stnode == NULL)
	{

		printf(" ���ο� ������ �����ϴ�.");		// �ֱ� �Է� ���� ������
	}
	else
	{
		tmp = stnode;
		printf("\n\n ���ο� ����\n\n");		//���Ӱ� ���Ͽ� ������ ��

		while (tmp != NULL)
		{
			printf(" node %d : %s\n", n, tmp->title);
			printf(" node %d : %s\n", n, tmp->bookingOffice);
			n++;
			tmp = tmp->nextptr; // ���� �����͸� ���� node�� �̵�
		}
	}

	printf("\n\n ��ü ���� \n\n");
	FILE* fp = fopen("note.txt", "r");  //test������ r(�б�) ���� ����
	char buffer[1024] = { 0 };

	fread(buffer, 1, 1024, fp); //��ü �б�
	printf("%s", buffer);

	fclose(fp); //���� ������ �ݱ�
	getchar();

}

int main() {
	stnode = NULL;
	ennode = NULL;

	while (c != 27) { //esc ���������� �ݺ�
		start();
		c = _getch();
		int i, num, day;
		if (c == 72) {	// ���� ȭ��ǥ ����Ű Ŭ�� ��
			system("cls");
			calendar();
			num = input();
			AddNote(n);

			if (c = _getch(13)) {
				start();
			}
		}

		else if (c == 80) {	// �Ʒ��� ȭ��ǥ ����Ű Ŭ�� ��
			system("cls");
			calendar();
			showNote();
		}
	}
	return 0;
}

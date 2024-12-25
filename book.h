#if 1
#pragma once
#define INITCAPACITY 10//ͼ��ĳ�ʼ����
#define EXPENDSIZE 2//����2��
//ͼ�����
typedef struct Book {
	int book_id;
	char bookname[20];
	char author[10]; //����
	double price;
	char time[30]; //�ϼ�ͼ��ʱ��
}Book;

typedef struct Library {
	Book* books;
	int capacity; //�洢������
	int size; //��Ч�鱾����
}Library;

void InitLibrary(Library* lib);

bool Grow(Library* lib); //���ݲ���
//�ϼ�ͼ��
bool InsertTail(Library* lib); //arr[size++] = val;
bool Delete(Library* lib);
//�¼�ͼ��
bool DeleteByName(Library* lib);
bool DeleteById(Library* lib);

//����ͼ�� -- ����  ���  �۸�����  �ϼ����� (2023��)  ����
int Search(Library* lib);

int SearchByName(Library* lib);
int SearchById(Library* lib);
bool SearchByPriceRange(Library* lib);
int SearchByDate(Library* lib);
int SearchByAuthor(Library* lib);

//�޸�
int Change(Library* lib);
int ChangeByName(Library* lib);
int ChangeById(Library* lib);
int ChangeByAuthor(Library* lib);

void Show(Library* lib);
#endif
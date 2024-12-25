#if 1
#pragma once
#define INITCAPACITY 10//图书的初始容量
#define EXPENDSIZE 2//扩容2倍
//图书管理
typedef struct Book {
	int book_id;
	char bookname[20];
	char author[10]; //作者
	double price;
	char time[30]; //上架图书时间
}Book;

typedef struct Library {
	Book* books;
	int capacity; //存储书容量
	int size; //有效书本个数
}Library;

void InitLibrary(Library* lib);

bool Grow(Library* lib); //扩容操作
//上架图书
bool InsertTail(Library* lib); //arr[size++] = val;
bool Delete(Library* lib);
//下架图书
bool DeleteByName(Library* lib);
bool DeleteById(Library* lib);

//查找图书 -- 书名  编号  价格区间  上架日期 (2023年)  作者
int Search(Library* lib);

int SearchByName(Library* lib);
int SearchById(Library* lib);
bool SearchByPriceRange(Library* lib);
int SearchByDate(Library* lib);
int SearchByAuthor(Library* lib);

//修改
int Change(Library* lib);
int ChangeByName(Library* lib);
int ChangeById(Library* lib);
int ChangeByAuthor(Library* lib);

void Show(Library* lib);
#endif
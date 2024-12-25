#if 1
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "book.h"
#include <cassert>
#include <corecrt_malloc.h>
#include <graphics.h>
#include <time.h>
//ͼ�����
void GetTime(char* arr) {
	time_t t;
	time(&t);
	struct tm* ptm = localtime(&t);
	sprintf(arr,"%d-%d-%d %d:%d:%d",ptm->tm_year + 1900, ptm->tm_mon + 1,ptm->tm_mday,
		ptm->tm_hour, ptm->tm_min, ptm->tm_sec);

}
void InitLibrary(Library* lib) {
	assert(lib!=NULL);
	lib->books = (Book*)malloc(INITCAPACITY*sizeof(Book));
	assert(lib->books!=NULL);
	lib->capacity = INITCAPACITY;
	lib->size = 0;
}

bool Grow(Library* lib) {//���ݲ���
	assert(lib != NULL);
	int len = lib->capacity * EXPENDSIZE;
	Book* tmp=(Book*)realloc(lib->books,sizeof(Book)*len);
	if (NULL == tmp) {
		return false;
	}
	lib->books = tmp;
	lib->capacity = len;
	return true;
}
//�ϼ�ͼ��
bool InsertTail(Library* lib) { //arr[size++] = val;
	if (lib->size == lib->capacity && !Grow(lib)) {
		MessageBox(NULL, "�ϼ�ͼ��ʧ�ܣ���", "�ϼ�ͼ����", MB_OKCANCEL);
		return false;
	}
	InputBox(lib->books[lib->size].bookname,50,"ͼ����","�ϼ�ͼ��");
	InputBox(lib->books[lib->size].author, 50, "������", "�ϼ�ͼ��");
	char buff[10] = { 0 };
	bool flag;
	do {//������ظ���������¼����
		flag = false;
		InputBox(buff, 10, "���", "�ϼ�ͼ��");
		int id = atoi(buff);
		lib->books[lib->size].book_id = id;
	for (int i = 0; i < lib->size; i++)
	{
		if(lib->books[i].book_id==id){
			MessageBox(NULL,"����ظ���������¼��","�ϼ�ͼ��",MB_OKCANCEL);
			flag = true;
			break;
		}
	}
	} while (flag);

	InputBox(buff,10,"�۸�","�ϼ�ͼ��");
	lib->books[lib->size].price = atof(buff);
	char time[50] = { 0 };
	GetTime(time);
	strcpy(lib->books[lib->size].time,time);
	lib->size++;
	MessageBox(NULL,"�ϼ�ͼ��ɹ�����","�ϼ�ͼ����",MB_OKCANCEL);
	return true;
}
//*********�¼�ͼ��***********
bool Delete(Library* lib) {
	char buff[20] = { 0 };
	InputBox(buff, 20, "�¼��鼮\n name or id", "�¼�ͼ��");
	
	if (strncmp(buff, "name", 4) == 0) {
		return DeleteByName(lib);
	}
	if (strncmp(buff, "id", 2) == 0) {
		return DeleteById(lib);
	}
	MessageBox(NULL,"�����Բ�����\n","�¼�ʧ��",MB_OKCANCEL);
	return false;

}

//���������Ƿ��ظ�
bool DeleteByName(Library* lib) {
	char buff[20] = { 0 };
	InputBox(buff, 20, "�������¼�ͼ������", "�¼�ͼ��");
	for (int i = 0; i < lib->size; i++) {
		if (!strcmp(lib->books[i].bookname, buff)) {
			//�ҵ���ɾ��ͼ��
			for (int j = i + 1; j < lib->size; j++) {
				lib->books[j - 1] = lib->books[j];
			}
			MessageBox(NULL, "�¼�ͼ��ɹ�����", "�¼�ͼ����", MB_OK);
			lib->size--;
			return true;
		}
		MessageBox(NULL, "�¼�ͼ��ʧ�ܣ���", "�¼�ͼ����", MB_OK);
		return false;
	}
}

bool DeleteById(Library* lib) {
	char buff[20] = { 0 };
	InputBox(buff, 20, "�������¼�ͼ����", "�¼�ͼ��");
	int id = atoi(buff);
	for (int i = 0; i < lib->size; i++) {
		if (lib->books[i].book_id == id) {
			//�ҵ���ɾ��ͼ��
			for (int j = i + 1; j < lib->size; j++) {
				lib->books[j - 1] = lib->books[j];
			}
			lib->size--;//*******�ص�
			MessageBox(NULL, "�¼�ͼ��ɹ�����", "�¼�ͼ����", MB_OK);
			return true;
		}
	}
	MessageBox(NULL, "�¼�ͼ��ʧ�ܣ���", "�¼�ͼ����", MB_OK);
	return false;
}
//****************************

//**************����ͼ�� -- ����  ���  �۸�����  �ϼ����� (2023��)  ����
int Search(Library* lib) {
	char buff[20] = { 0 };
	bool flag;
	do{
		InputBox(buff, 20, "�����鼮\n ��������:\n����\n����\n���\n���\n�۸�����\n", "����ͼ��");
		flag = false;
	if (strcmp(buff, "����") == 0) {
		return SearchByName(lib);
	}
	if (strcmp(buff, "����") == 0) {
		return SearchByAuthor(lib);
	}
	if (strcmp(buff, "���") == 0) {
		return SearchById(lib);
	}
	if (strcmp(buff, "���") == 0) {
		return SearchByDate(lib);
	}
	if (strcmp(buff, "�۸�����") == 0) {
		return SearchByPriceRange(lib);
	}
	else {
		MessageBox(NULL, "�����Բ�����\n����������", "����ͼ��", MB_OKCANCEL);
		flag = true;
	}
	} while (flag);

	return -1;

}
int SearchByName(Library* lib) {
	char buff[20] = { 0 };
	InputBox(buff, 20, "�����������ͼ������", "����ͼ��");
	for (int i = 0; i < lib->size; i++) {
		if (!strcmp(lib->books[i].bookname,buff)) {
			char res[128] = { 0 };//Ҫ��ӡ���ҵ��������Ϣ
			sprintf(res, "���:%d ����:%s ����:%s �۸�:%lf �ϼ�ʱ��:%s"
				, lib->books[i].book_id, lib->books[i].bookname, lib->books[i].author
				, lib->books[i].price, lib->books[i].time);
			strcat(res, "\n���ҳɹ�!\n");
			MessageBox(NULL, res, "����ͼ��", MB_OKCANCEL);
			return i;
		}
	}
	MessageBox(NULL, "����ʧ��", "����ͼ��", MB_OKCANCEL);
	return -1;
}
int SearchById(Library* lib) {
	char buff[20] = { 0 };
	InputBox(buff, 20, "�����������ͼ����", "����ͼ��");
	int id = atoi(buff);
	for (int i = 0; i < lib->size; i++) {
		if (lib->books[i].book_id == id) {
			char res[128] = { 0 };//Ҫ��ӡ���ҵ��������Ϣ
			sprintf(res,"���:%d ����:%s ����:%s �۸�:%lf �ϼ�ʱ��:%s"
			,lib->books[i].book_id, lib->books[i].bookname, lib->books[i].author
				,lib->books[i].price, lib->books[i].time);
			strcat(res, "\n���ҳɹ�!\n");
			MessageBox(NULL, res, "����ͼ��", MB_OKCANCEL);
			return i;
		}
	}
	MessageBox(NULL, "����ʧ��", "����ͼ��", MB_OKCANCEL);
	return -1;
}
bool SearchByPriceRange(Library* lib) {
	char buff[20] = { 0 };
	InputBox(buff, 20, "������۸�����", "����ͼ��");
	double lowprice = atof(buff);
	InputBox(buff, 20, "������۸�����", "����ͼ��");
	double highprice = atof(buff);
	int index = -1;
	char  res[1024] = { 0 };//ΪʲôҪ�ഴ��������飬��Ϊ ������������кܶ��飬Ϊ�˴�౾����Ϣ
	char tmp[128] = { 0 };
	for (int i = 0; i < lib->size; i++) {
		if (lib->books[i].price>=lowprice&&lib->books[i].price<=highprice) {
			sprintf(tmp, "���:%d ����:%s ����:%s �۸�:%lf �ϼ�ʱ��:%s\n"
				, lib->books[i].book_id, lib->books[i].bookname, lib->books[i].author
				, lib->books[i].price, lib->books[i].time);
			strcat(res,tmp);
		}	
	}
	if(res[0]=='\0'){
		//!strcmp(res,'\0')
		//strcmp( )�������ݵĲ�����ָ���ַ�����ָ�룬�����ǵ������ַ���
		// ����ͨ�������ַ���װ��һ���ַ����У�����ʹ��ָ�������ݡ�
		MessageBox(NULL, "����ʧ��\n�����ڸü۸�������鼮", "����ͼ��", MB_OKCANCEL);
		return index;
	}
	strcat(res, "���ҳɹ���");
	MessageBox(NULL, res, "����ͼ��", MB_OKCANCEL);
	return true;
}
int SearchByDate(Library* lib) {
	char buff[20] = { 0 };
	InputBox(buff, 20, "��������������\n��ʽ:2023/2019", "����ͼ��");
	char  res[1024] = { 0 };
	char tmp[128] = { 0 };//��Ϊ �кö౾�飬���Զ�Ҫ��
	bool flag = false;
	for (int i = 0; i < lib->size; i++) {
		char year[128] = { 0 };
		strcpy(year,lib->books[i].time);
		char* y = strtok(year,"-");//�ָ��
		if (!strcmp(buff,y)) {
			sprintf(tmp, "���:%d ����:%s ����:%s �۸�:%2.lf �ϼ�ʱ��:%s\n"
				, lib->books[i].book_id, lib->books[i].bookname, lib->books[i].author
				, lib->books[i].price, lib->books[i].time);
			strcat(res, tmp);
			flag = true;
		}
	}
		if(flag){
			strcat(res, "���ҳɹ���");
			MessageBox(NULL, res, "����ͼ��", MB_OKCANCEL);
		}
		else
		{
			MessageBox(NULL, "����ʧ��", "����ͼ��", MB_OKCANCEL);
		}
	return flag;
}
int SearchByAuthor(Library* lib) {
	char buff[20] = { 0 };
	InputBox(buff, 20, "�����������ͼ������", "����ͼ��");
	char res[1024] = { 0 };
	char tmp[128] = { 0 };
	bool flag = false;
	for (int i = 0; i < lib->size; i++) {
		if (!strcmp(lib->books[i].author,buff)) {
			sprintf(tmp, "���:%d ����:%s ����:%s �۸�:%lf �ϼ�ʱ��:%s"
				, lib->books[i].book_id, lib->books[i].bookname, lib->books[i].author
				, lib->books[i].price, lib->books[i].time);
			strcat(res,tmp);
			flag = true;
		}
	}
	if (!flag) {
		MessageBox(NULL, "����ʧ��", "����ͼ��", MB_OKCANCEL);
	}
	else {
		strcat(res, "\n���ҳɹ�");
		MessageBox(NULL, res, "����ͼ��", MB_OKCANCEL);
	}
	return flag;
}
//*********************************************
//�޸� ���� ��� id �۸����� �ϼ����� 
int Change(Library* lib) {
	char buff[20] = { 0 };
	bool flag;
	do {
		InputBox(buff, 20, "�޸��鼮\n ��������:\n����\n����\n���\n", "�޸�ͼ��");
		flag = false;
		if (strcmp(buff, "����") == 0) {
			return ChangeByName(lib);
		}
		if (strcmp(buff, "����") == 0) {
			return ChangeByAuthor(lib);
		}
		if (strcmp(buff, "���") == 0) {
			return ChangeById(lib);
		}
		else {
			MessageBox(NULL, "�����Բ�����\n����������", "�޸�ͼ��", MB_OKCANCEL);
			flag = true;
		}
	} while (flag);

	return -1;

}

int ChangeByName(Library* lib) {
	char Bold[20] = { 0 };
	InputBox(Bold, 20, "��������޸�ͼ������", "�޸�ͼ��");
	char Bnew[20] = { 0 };
	InputBox(Bnew, 20, "�������޸ĺ��ͼ������", "�޸�ͼ��");
	int j = 0;
	for (int i = 0; i < lib->size; i++) {
		if (!strcmp(lib->books[i].bookname, Bold)) {
			strcpy(lib->books[i].bookname, Bnew);
			j = 1;
		}
	}
	if (j) {
		MessageBox(NULL, "�޸ĳɹ�", "�޸�ͼ��", MB_OKCANCEL);
	}
	else {
		MessageBox(NULL, "�޸�ʧ��", "����ͼ��", MB_OKCANCEL);
	}
	return j;
}
int ChangeById(Library* lib) {
	char Bold[20] = { 0 };
	InputBox(Bold, 20, "��������޸�ͼ����", "�޸�ͼ��");
	char Bnew[20] = { 0 };
	InputBox(Bnew, 20, "�������޸ĺ��ͼ����", "�޸�ͼ��");
	int j = 0;
	for (int i = 0; i < lib->size; i++) {
		if (lib->books[i].book_id == atoi(Bold)) {
			lib->books[i].book_id = atoi(Bnew);
			j = 1;
		}
	}
	if (j) {
		MessageBox(NULL, "�޸ĳɹ�", "�޸�ͼ��", MB_OKCANCEL);
	}
	else {
		MessageBox(NULL, "�޸�ʧ��", "����ͼ��", MB_OKCANCEL);
	}
	return j;
}
int ChangeByAuthor(Library* lib) {
	char Bold[20] = { 0 };
	InputBox(Bold, 20, "��������޸�ͼ������", "�޸�ͼ��");
	char Bnew[20] = { 0 };
	InputBox(Bnew, 20, "�������޸ĺ��ͼ������", "�޸�ͼ��");
	int j = 0;
	for (int i = 0; i < lib->size; i++) {
		if (!strcmp(lib->books[i].author, Bold)) {
			strcpy(lib->books[i].author, Bnew);
			j = 1;
		}
	}
	if (j) {
		MessageBox(NULL, "�޸ĳɹ�", "�޸�ͼ��", MB_OKCANCEL);
	}
	else {
		MessageBox(NULL, "�޸�ʧ��", "����ͼ��", MB_OKCANCEL);
	}
	return j;
}

//չʾ
void Show(Library* lib) {
	char result[1024] = {0};
	strcat(result,"���\t����\t����\t�۸�\t�ϼ�ʱ��\n");
	char buff[128] = { 0 };//��һ����
	for (int i = 0; i < lib->size;i++) {
		sprintf(buff,"%d\t%s\t%s\t%2.lf\t%s\n",lib->books[i].book_id,lib->books[i].bookname,lib->books[i].author,lib->books[i].price,lib->books[i].time);
		strcat(result,buff);//��buff���ӵ�result�ڣ��浽result��
		memset(buff,0,128);
	}
	MessageBox(NULL,result,"�鼮��Ϣ",MB_OKCANCEL);
}
#endif

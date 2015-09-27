#ifndef _BOOK_H_
#define _BOOK_H_
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;

class Book
{
public:
	string bookID;			//�鼮���
	string bookName;		//����
	string writer;			//����
	string ISBN;			//�鼮ISBN����
	string press;			//������
	string publishYear;		//�������
	int totalInventory;		//�ܿ��
	int currentInventory;	//��ǰ���
	Book *Next;				//������ָ����
	Book();
	void bookFileRead(ifstream &in);
	void bookInfoDisplay();
};

Book::Book()
{
	bookID = '\0';
	bookName = '\0';
	writer = '\0';
	ISBN = '\0';
	press = '\0';
	totalInventory = 0;
	currentInventory = 0;
	publishYear = "2015";
	Next = NULL;
}

void Book::bookFileRead( ifstream &in )
{
	int number;
	in >> number >> bookID >> bookName >> writer >> ISBN 
		>> press >> publishYear >> totalInventory >> currentInventory;
}
void Book::bookInfoDisplay()
{
	cout << "\t\t" << setiosflags(ios_base::left) << setw(20)
		 << "�鼮��ţ�" << bookID << "\n" << "\t\t" << setw(20) << "������" << bookName << "\n"
		 << "\t\t" << setw(20) << "���ߣ�" << writer<< "\n"<< "\t\t" << setw(20) << "ISBN��" << ISBN << "\n"
		 << "\t\t" << setw(20) << "�����磺" << press << "\n" << "\t\t" << setw(20) << "������ݣ�" << publishYear
		 << "\n" << "\t\t" << setw(20) << "�ܿ�棺" << totalInventory << "\n" << "\t\t" << setw(20) << "��ǰ��棺" 
		 << currentInventory << "\n" << resetiosflags(ios_base::left)<< endl;
}
#endif		//_BOOK_H_
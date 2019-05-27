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
	string bookID;			//书籍编号
	string bookName;		//书名
	string writer;			//作者
	string ISBN;			//书籍ISBN编码
	string press;			//出版社
	string publishYear;		//出版年份
	int totalInventory;		//总库存
	int currentInventory;	//当前库存
	Book *Next;				//链表结点指针域
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
		 << "书籍编号：" << bookID << "\n" << "\t\t" << setw(20) << "书名：" << bookName << "\n"
		 << "\t\t" << setw(20) << "作者：" << writer<< "\n"<< "\t\t" << setw(20) << "ISBN：" << ISBN << "\n"
		 << "\t\t" << setw(20) << "出版社：" << press << "\n" << "\t\t" << setw(20) << "出版年份：" << publishYear
		 << "\n" << "\t\t" << setw(20) << "总库存：" << totalInventory << "\n" << "\t\t" << setw(20) << "当前库存：" 
		 << currentInventory << "\n" << resetiosflags(ios_base::left)<< endl;
}
#endif		//_BOOK_H_
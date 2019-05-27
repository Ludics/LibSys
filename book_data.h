//book_data.h		BookData类的定义
#ifndef _BOOK_DATA_H_
#define _BOOK_DATA_H_
#include"book.h"
#include<iostream>
#include<fstream>
#include<iomanip>
class BookData
{
public:
	Book *bHead, *bEnd;
	BookData();
	~BookData();
	void seekBook();				//查找一本书
	void displayBooks();			//显示全部图书信息
	void saveBooks();				//保存全部图书信息到文件
};

//构造函数
BookData::BookData()
{
	ifstream in;
	bHead = new Book;
	bHead->Next = new Book;
	bEnd = bHead->Next;
	in.open("book.txt");
	while (!in.eof() )
	{
		bEnd->bookFileRead(in);
		if ( bEnd->bookID[0] == '\0' )	break;
		bEnd->Next = new Book;
		bEnd = bEnd->Next;
	}
	cout << "图书信息读取成功！"<<endl;
	in.close();
}
//析构函数
BookData::~BookData()
{
	saveBooks();
	for ( Book *temp; bHead->Next != bEnd; )
	{
		temp = bHead->Next;
		bHead->Next = bHead->Next->Next;
		delete temp;
	}
	delete bHead,bEnd;
}
//查询书籍信息函数
void BookData::seekBook()		
{
	
	string str;
	Book* p = NULL;
	int order, flag = 0;
	cout << "\t\t1.按书名查找\n\t\t2.按作者查找\n\t\t0.返回" << endl;
	cout << "\t\t请输入序号选择查询方式：";
	cin >> order;
	switch ( order )
	{
	case 0: return;
	case 1:
		{
			cout << "\t\t请输入所要查询的书籍的书名：";
			cin >> str;
			cout << endl;
			for ( p = bHead->Next; p != bEnd; p = p->Next )
			{
				if ( p->bookName == str )
				{
					flag++;
					cout << "\t" << flag << "." << endl;
					p->bookInfoDisplay();
					cout << endl;
				}
			}
		} break;
	case 2:
		{
			cout << "\t\t请输入所要查询的作者：";
			cin >> str;
			cout << endl;
			for ( p = bHead->Next; p != bEnd; p = p->Next )
			{
				if ( p->writer == str )
				{
					flag++;
					cout << "\t" << flag << "." << endl;
					p->bookInfoDisplay();
					cout << endl;
				}
			}
		} break;
	default: return;
	}
	if ( flag )
		cout << "查询完毕，按回车键继续..." << endl;
	else 
		cout << "未查询到信息，按回车键继续..." << endl;
	cin.get();cin.get();
}

void BookData::displayBooks()	//显示全部图书信息
{
	cout << endl;
	int i = 0;
	for ( Book *p = bHead->Next; p != bEnd; p = p->Next )
		i++;
	cout << "当前共有图书" << i << "种" << endl;
	i = 0;
	for ( Book *p = bHead->Next; p != bEnd; p = p->Next )
	{
		i++;
		cout << "\t" << i << "." << endl;
		p->bookInfoDisplay();
		cout << endl;
	}
	cin.get();cin.get();
}

void BookData::saveBooks()		//保存全部图书信息到文件
{
	int i = 0;
	ofstream out;
	out.open("Book.txt");
	for ( Book *p = bHead->Next; p != bEnd; p = p->Next )
	{
		i++;
		out << i << "\t"<< p->bookID << "\t"<< p->bookName << "\t"<< p->writer << "\t"<< p->ISBN << "\t" << p->press 
			<< "\t" << p->publishYear << "\t" << p->totalInventory << "\t"<< p->currentInventory << endl;
	}
}
#endif		//_BOOKDATABASE_H_
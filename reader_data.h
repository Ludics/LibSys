#ifndef _READER_DATA_H_
#define _READER_DATA_H_
#include"reader.h"
#include"book_data.h"
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class ReaderData
{
private:
	Reader reader;
public:
	Reader *rHead, *rEnd;
	ReaderData();
	~ReaderData();
	void saveReaders();
	void seekBook();				//查询图书信息
	void borrowBook(Reader *p);		//借书
	void returnBook(Reader *p);		//还书
};
ReaderData::ReaderData()
{
	ifstream in;
	rHead = new Reader;
	rHead->Next = new Reader;
	rEnd = rHead->Next;
	in.open("Reader.txt");
	if ( !in )
		cout << "新系统无读者信息..." << endl;
	else
	{
		while ( !in.eof() )
		{
			string str;
			int i;
			in >> i >> rEnd->name >> rEnd->password >> rEnd->phoneNumber >> rEnd->borrowNumber;
			for ( int i = 0; i < rEnd->borrowNumber; i++ )
				in >> rEnd->bookName[i] >> rEnd->bookID[i];
			if ( rEnd->name[0] == '\0' )	break;
			rEnd->Next = new Reader;
			rEnd = rEnd->Next;
		}	
	cout << "读者信息读取成功！" << endl;
	}
}
ReaderData::~ReaderData()
{
	saveReaders();
	for ( Reader *temp; rHead->Next != rEnd; )
	{
		temp = rHead->Next;
		rHead->Next = rHead->Next->Next;
		delete temp;
	}
	delete rHead,rEnd;
}
void ReaderData::saveReaders()		//保存读者信息
{
	ofstream out;
	out.open("Reader.txt");
	int i = 0;
	for ( Reader *p = rHead->Next; p != rEnd; p = p->Next )
	{
		i++;
		out << i << "\t"<< p->name <<  "\t" << p->password <<  "\t" 
			<< p->phoneNumber <<  "\t" << p->borrowNumber;
		for ( int i = 0; i < p->borrowNumber; i++ )
			out << "\t" << p->bookName[i] <<  "\t" << p->bookID[i];
		out << endl;
	}
}

void ReaderData::borrowBook( Reader *pR )
{
	BookData booklist;
	if ( pR->borrowNumber == MaxBor )
		cout << "已达最大借书量，请还书后再借。按回车键继续..." << endl;
	else 
	{
		int flag = 0;
		cout << "请输入所借图书的书名或作者：";
		string str;
		cin >> str;
		cout << "查询到的书籍信息如下：" << endl;
		for (Book *pB = booklist.bHead->Next; pB != booklist.bEnd; pB = pB->Next )
		{
			if ( pB->writer == str || pB->bookName == str )
			{
				flag++;
				cout << "\t" << flag << "." << endl;
				pB->bookInfoDisplay();
				cout << endl;
			}
		}
		if ( flag )
		{
			flag = 1;
			cout << "借书请输入查询到的图书编号：";
			cin >> str;
			for (Book *pB = booklist.bHead->Next; pB != booklist.bEnd; pB = pB->Next )
			{
				if ( pB->bookID == str )
				{
					flag = 0;
					if ( pB->currentInventory == 0)
						cout << "当前库存为零，无法借书！按回车键继续..." << endl;
					else
					{
						pB->currentInventory --;
						pR->bookName[pR->borrowNumber] = pB->bookName;
						pR->bookID[pR->borrowNumber] = pB->bookID;
						pR->borrowNumber ++;
						booklist.saveBooks();
						cout << "借书成功！" << endl;
					}
				}
			}
			if ( flag )
				cout << "图书编号输入不正确，借书未成功！按回车键继续..." << endl;
		}
		else
			cout << "未查询到相关信息，按回车键继续..." << endl;
	}
	cin.get();cin.get();
	saveReaders();
}
//借书
void ReaderData::returnBook( Reader *pR)
{
	BookData booklist;
	cout << "借书信息如下：" << endl;
	pR->readerInfoDisplay();
	cout << "请输入要还图书的编号：";
	string str;
	cin >> str;
	bool flag = 1;
	for (Book *pB = booklist.bHead->Next; pB != booklist.bEnd; pB = pB->Next )
	{
		if ( pB->bookID == str )
		{
			flag = 0;
			pB->currentInventory ++;
			int x;
			for ( int i = 0; i < pR->borrowNumber; i ++ )
				if ( pR->bookID[i] == str ) x = i;
			pR->bookID[x] = pR->bookID[pR->borrowNumber - 1];
			pR->bookName[x] = pR->bookName[pR->borrowNumber - 1];
			pR->borrowNumber --;
			booklist.saveBooks();
			cout << "还书成功！" << endl;
		}
	}
	if ( flag )
		cout << "编号输入不正确，还书未成功。" << endl;
	saveReaders();
	cin.get();cin.get();
}
void ReaderData::seekBook()
{
	BookData booklist;
	booklist.seekBook();
}
#endif		//_READER_DATA_H_
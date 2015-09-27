//user.h
#ifndef _Reader_H_
#define _Reader_H_
#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
#include"book_data.h"
using namespace std;
const int MaxBor = 5;		//每人最多借阅数量为五本

class Reader
{
public:
	string name;				//用户名
	string phoneNumber;			//手机号
	string password;			//密码
	string bookID[MaxBor];		//所借图书编号
	string bookName[MaxBor];	//所借图书书名
	int borrowNumber;			//借书数量
	Reader *Next;				//链表结点指针域
	Reader();					//构造函数
	Reader(Reader &reader);		//复制构造函数
	void readerInfoDisplay();	//显示信息
	void readerFileRead();		//读取信息
};
//Reader类构造函数
Reader::Reader()
{
	name = '\0';
	password = "password";
	for ( int i = 0; i < MaxBor; i++ )
	{
		bookName[i] = '\0';
		bookID[i] = '\0';
	}
	borrowNumber = 0;
	Next = NULL;
}
//Reader类复制构造函数
Reader::Reader(Reader &reader)
{
	name = reader.name;
	phoneNumber = reader.phoneNumber;
	password = reader.password;
	borrowNumber = reader.borrowNumber;
	for ( int i = 0; i < borrowNumber; i++ )
	{
		bookID[i] = reader.bookID[i];
		bookName[i] = reader.bookID[i];
	}
}
void Reader::readerInfoDisplay()
{
	cout << "\t" << setiosflags(ios_base::left) << "用户名：" << setw(15)<< name 
		<< "联系方式：" << setw(15) << phoneNumber << "已借" <<  borrowNumber << "本书" << "\n";
	cout << "      ";
	for ( int i = 0; i < 61; i++ )
		cout << "-";
	for ( int i = 0; i < borrowNumber; i++ )
		cout << "\n\t" << setiosflags(ios_base::left) << setw(30) << bookName[i] 
			 << resetiosflags(ios_base::left) << setw(27) << bookID[i];
	cout << endl;
	cout << endl;
}
#endif		//_READER_H_
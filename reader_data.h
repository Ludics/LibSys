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
	void seekBook();				//��ѯͼ����Ϣ
	void borrowBook(Reader *p);		//����
	void returnBook(Reader *p);		//����
};
ReaderData::ReaderData()
{
	ifstream in;
	rHead = new Reader;
	rHead->Next = new Reader;
	rEnd = rHead->Next;
	in.open("Reader.txt");
	if ( !in )
		cout << "��ϵͳ�޶�����Ϣ..." << endl;
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
	cout << "������Ϣ��ȡ�ɹ���" << endl;
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
void ReaderData::saveReaders()		//���������Ϣ
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
		cout << "�Ѵ������������뻹����ٽ衣���س�������..." << endl;
	else 
	{
		int flag = 0;
		cout << "����������ͼ������������ߣ�";
		string str;
		cin >> str;
		cout << "��ѯ�����鼮��Ϣ���£�" << endl;
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
			cout << "�����������ѯ����ͼ���ţ�";
			cin >> str;
			for (Book *pB = booklist.bHead->Next; pB != booklist.bEnd; pB = pB->Next )
			{
				if ( pB->bookID == str )
				{
					flag = 0;
					if ( pB->currentInventory == 0)
						cout << "��ǰ���Ϊ�㣬�޷����飡���س�������..." << endl;
					else
					{
						pB->currentInventory --;
						pR->bookName[pR->borrowNumber] = pB->bookName;
						pR->bookID[pR->borrowNumber] = pB->bookID;
						pR->borrowNumber ++;
						booklist.saveBooks();
						cout << "����ɹ���" << endl;
					}
				}
			}
			if ( flag )
				cout << "ͼ�������벻��ȷ������δ�ɹ������س�������..." << endl;
		}
		else
			cout << "δ��ѯ�������Ϣ�����س�������..." << endl;
	}
	cin.get();cin.get();
	saveReaders();
}
//����
void ReaderData::returnBook( Reader *pR)
{
	BookData booklist;
	cout << "������Ϣ���£�" << endl;
	pR->readerInfoDisplay();
	cout << "������Ҫ��ͼ��ı�ţ�";
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
			cout << "����ɹ���" << endl;
		}
	}
	if ( flag )
		cout << "������벻��ȷ������δ�ɹ���" << endl;
	saveReaders();
	cin.get();cin.get();
}
void ReaderData::seekBook()
{
	BookData booklist;
	booklist.seekBook();
}
#endif		//_READER_DATA_H_
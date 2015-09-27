//book_data.h		BookData��Ķ���
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
	void seekBook();				//����һ����
	void displayBooks();			//��ʾȫ��ͼ����Ϣ
	void saveBooks();				//����ȫ��ͼ����Ϣ���ļ�
};

//���캯��
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
	cout << "ͼ����Ϣ��ȡ�ɹ���"<<endl;
	in.close();
}
//��������
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
//��ѯ�鼮��Ϣ����
void BookData::seekBook()		
{
	
	string str;
	Book* p = NULL;
	int order, flag = 0;
	cout << "\t\t1.����������\n\t\t2.�����߲���\n\t\t0.����" << endl;
	cout << "\t\t���������ѡ���ѯ��ʽ��";
	cin >> order;
	switch ( order )
	{
	case 0: return;
	case 1:
		{
			cout << "\t\t��������Ҫ��ѯ���鼮��������";
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
			cout << "\t\t��������Ҫ��ѯ�����ߣ�";
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
		cout << "��ѯ��ϣ����س�������..." << endl;
	else 
		cout << "δ��ѯ����Ϣ�����س�������..." << endl;
	cin.get();cin.get();
}

void BookData::displayBooks()	//��ʾȫ��ͼ����Ϣ
{
	cout << endl;
	int i = 0;
	for ( Book *p = bHead->Next; p != bEnd; p = p->Next )
		i++;
	cout << "��ǰ����ͼ��" << i << "��" << endl;
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

void BookData::saveBooks()		//����ȫ��ͼ����Ϣ���ļ�
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
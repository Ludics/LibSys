//user.h
#ifndef _Reader_H_
#define _Reader_H_
#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
#include"book_data.h"
using namespace std;
const int MaxBor = 5;		//ÿ������������Ϊ�屾

class Reader
{
public:
	string name;				//�û���
	string phoneNumber;			//�ֻ���
	string password;			//����
	string bookID[MaxBor];		//����ͼ����
	string bookName[MaxBor];	//����ͼ������
	int borrowNumber;			//��������
	Reader *Next;				//������ָ����
	Reader();					//���캯��
	Reader(Reader &reader);		//���ƹ��캯��
	void readerInfoDisplay();	//��ʾ��Ϣ
	void readerFileRead();		//��ȡ��Ϣ
};
//Reader�๹�캯��
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
//Reader�ิ�ƹ��캯��
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
	cout << "\t" << setiosflags(ios_base::left) << "�û�����" << setw(15)<< name 
		<< "��ϵ��ʽ��" << setw(15) << phoneNumber << "�ѽ�" <<  borrowNumber << "����" << "\n";
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
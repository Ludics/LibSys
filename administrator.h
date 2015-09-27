#ifndef _ADMINISTRATOR_H_
#define _ADMINISTRATOR_H_
#include<iostream>
#include<string>
#include"book_data.h"
#include"reader_data.h"
using namespace std;

class Administrator:
	public BookData, public ReaderData
{
public:
	~Administrator()	{}
	void addBook();			//���ͼ����Ϣ
	void deleteBook();		//ɾ��ͼ����Ϣ
	void modifyBook();		//�޸�ͼ����Ϣ
	void addReader();		//��Ӷ�����Ϣ
	void deleteReader();	//ɾ��������Ϣ
	void displayReaders();	//��ʾȫ��������Ϣ
	void seekReader();		//����������Ϣ
	void modifyReader();	//�޸Ķ�����Ϣ
};

void Administrator::addBook()		//���ͼ����Ϣ
{
	cout << "������ͼ���ISBN���룺\n\t\t";
	string str;
	cin >> str;
	int flag = 1;
	for ( Book *p = bHead->Next; p != bEnd; p = p->Next )
	{
		if ( p->ISBN == str )
		{
			flag = 0;
			cout << "ͼ���Ѵ��ڣ�" << endl;
			p->bookInfoDisplay();
			cout << "ȷ����ӿ����(y\\n)" <<endl;
			char c;
			cin >> c;
			if ( c == 'y' || c == 'Y')
			{
				cout << "���������������";
				int i;
				cin >> i;
				p->currentInventory += i;
				p->totalInventory +=i;
				cout << "��ӿ��ɹ������س�������..." << endl;
			}
			else
				cout << "δ��ӿ�棡���س�������..." << endl;
		}
	}
	if ( flag )
	{
		bEnd->ISBN = str;
		cout << "����һ�������û�е��飡�밴ͼ����෨Ϊ���ţ�\n\t\t";
		cin >> str;
		while ( flag )
		{
			for (Book *p = bHead->Next; p != bEnd; p = p->Next )
				if ( p->bookID == str )
				{
					cout << "�˱���Ѵ��ڣ������±�ţ�";
					cin >> str;
					continue;
				}
			flag = 0;
		}
		bEnd->bookID = str;
		cout << "�밴��ʾ����ͼ����Ϣ��(�ո�����\"_\")" << endl;
		cout << "������";
		cin >> bEnd->bookName;
		cout << "���ߣ�";
		cin >> bEnd->writer;
		cout << "�����磺";
		cin >> bEnd->press;
		cout << "������ݣ�";
		cin >> bEnd->publishYear;
		bEnd->totalInventory = bEnd->currentInventory = 1;
		cout << "���������������";
		int i;
		cin >> i;
		i --;
		bEnd->currentInventory += i;
		bEnd->totalInventory += i;
		cout << "ͼ����Ϣ�����ϣ�" << endl;
		bEnd->bookInfoDisplay();
		bEnd->Next = new Book;
		bEnd = bEnd->Next;
		cout << "���س�������..." << endl;
	}
	saveBooks();
	cin.get();cin.get();
}
void Administrator::deleteBook()		//ɾ��ͼ����Ϣ
{
	int flag = 0;
	cout << "������Ҫɾ��ͼ������������ߣ�";
	string str;
	cin >> str;
	cout << "���������鼮��Ϣ���£�" << endl;
	for (Book *p = bHead->Next; p != bEnd; p = p->Next )
	{
		if ( p->writer == str || p->bookName == str )
		{
			flag++;
			cout << "\t" << flag << "." << endl;
			p->bookInfoDisplay();
			cout << endl;
		}
	}
	if ( flag )
	{
		flag = 1;
		cout << "ɾ���������������ͼ���ţ�";
		cin >> str;
		for (Book *p = bHead; p->Next != bEnd; p = p->Next )
		{
			if ( p->Next->bookID == str )
			{
				flag = 0;
				if ( p->currentInventory == p->totalInventory )
				{
					cout << "ȷ��ɾ����(y\\n)" << endl;
					char c;
					cin >> c;
					if ( c == 'y' || c == 'Y' )
					{
						Book *temp = p->Next;
						p->Next = p->Next->Next;
						delete temp;
						cout << "\n��Ϣɾ���ɹ������س�������..." << endl;
						saveBooks();
						cin.get();cin.get();
						return;
					}
					else
						cout << "\nͼ����Ϣδɾ�������س�������..." << endl;
				}
				else
					cout << "����ͼ��û�й黹���޷�ɾ����Ϣ�����س�������..." << endl;
			}
		}
		if ( flag )
			cout << "ͼ�������벻��ȷ����Ϣδɾ�������س�������..." << endl;
	}
	else
		cout << "δ�����������Ϣ�����س�������..." << endl;
	cin.get();cin.get();
}
//�޸�ͼ����Ϣ
void Administrator::modifyBook()
{
	int flag = 0;
	cout << "������Ҫ�޸ĵ�ͼ������������ߣ�";
	string str;
	cin >> str;
	cout << "���������鼮��Ϣ���£�" << endl;
	for (Book *p = bHead->Next; p != bEnd; p = p->Next )
	{
		if ( p->writer == str || p->bookName == str )
		{
			flag++;
			p->bookInfoDisplay();
			cout << endl;
			cout << "\t#�޸Ĳ˵�#\n\t\t1.�޸�����\n\t\t2.�޸�����\n\t\t3.�޸�ISBN" 
				 << "\n\t\t4.�޸ĳ�����\n\t\t5.�޸ĳ������\n\t\t6.��ӿ��\n\t\t7.�޸ı��"<< endl;
			cout << "���������ѡ��";
			int order;
			cin >> order;
			switch( order )
			{
			default: return; break;
			case 1:
				cout << "����������:";
				cin >> p->bookName;
				cout << "�޸ĳɹ����޸ĺ���ϢΪ��" << endl;
				p->bookInfoDisplay();
				break;
			case 2:
				cout << "����������:";
				cin >> p->writer;
				cout << "�޸ĳɹ����޸ĺ���ϢΪ��" << endl;
				p->bookInfoDisplay();
				break;
			case 3:
				{
					string str;
					cout << "������ISBN��";
					cin >> str;
					int flag = 1;
					int flag1 = 1;
					while ( flag1 )
					{
						for ( Book *p1 = bHead->Next; p1 != bEnd; p1 = p1->Next )
						{
							if ( p1->ISBN == str )
							{
								flag = 0;
								cout << "ISBN�Ѵ��ڣ�" << endl;
								p1->bookInfoDisplay();
								cout << "����������ISBN��";
								cin >> str;
								continue;
							}
						}
						flag1 = 0;
					}
					if ( flag )
					{
						cout << "�޸ĳɹ����޸ĺ���ϢΪ��";
						p->bookInfoDisplay();
					}
				} break;
			case 4:
				cout << "�����������:";
				cin >> p->press;
				cout << "�޸ĳɹ����޸ĺ���ϢΪ��" << endl;
				p->bookInfoDisplay();
				break;
			case 5:
				cout << "������������:";
				cin >> p->publishYear;
				cout << "�޸ĳɹ����޸ĺ���ϢΪ��" << endl;
				p->bookInfoDisplay();
				break;
			case 6:
			{
				cout << "�����������Ŀ��";
				int i;
				cin >> i;
				p->currentInventory += i;
				p->totalInventory += i;
				cout << "�޸ĳɹ����޸ĺ���ϢΪ��" << endl;
				p->bookInfoDisplay();	
			} break;
			case 7:
				{
					string str;
					cout << "�������ţ�";
					cin >> str;
					int flag = 1;
					int flag1 = 1;
					while ( flag1 )
					{
						for ( Book *p1 = bHead->Next; p1 != bEnd; p1 = p1->Next )
						{
							if ( p1->bookID == str )
							{
								flag = 0;
								cout << "����Ѵ��ڣ�" << endl;
								p1->bookInfoDisplay();
								cout << "�����������ţ�";
								cin >> str;
								continue;
							}
						}
						flag1 = 0;
					}
					if ( flag )
					{
						p->bookID = str;
						cout << "�޸ĳɹ����޸ĺ���ϢΪ��" << endl;
						p->bookInfoDisplay();
					}
				} break;
			}
		}
	}
	if ( !flag )
		cout << "δ�����������Ϣ��" << endl;
	saveBooks();
	cin.get();cin.get();
}

void Administrator::addReader()		//��Ӷ�����Ϣ
{
	cout << "�������û���(���Ȳ�����14���ַ�)��";
	string str;
	cin >> str;
	while(1)
	{
		if ( str.size() < 14 )
		{
			bool flag = 1;
			for ( Reader *p = rHead->Next; p != rEnd; p = p->Next )
			{
				if ( p->name == str )
				{
					flag = 0;
					cout << "�û����ѱ�ʹ�ã����������룺";
					cin >> str;
				}
			}
			if ( flag )	break;
		}
		else
		{
			cout << "�û������ȳ���14���ַ������������룺";
			cin >> str;
		}
	}
	rEnd->name = str;
	cout << "���������룺";
	cin >> rEnd->password;
	cout << "�������ֻ����룺";
	cin >> rEnd->phoneNumber;
	rEnd->Next = new Reader;
	rEnd = rEnd->Next;
	cout << "�¶����û������ɹ������س�������..." << endl;
	saveReaders();
	cin.get();cin.get();
}
void Administrator::deleteReader()			//ɾ��������Ϣ
{
	bool flag = 1;
	cout << "��������Ҫɾ���Ķ��ߵ��û�����";
	string str;
	cin >> str;
	for ( Reader *p = rHead; p->Next != rEnd; p = p->Next )
	{
		if ( p->Next->name == str )
		{
			flag = 0;
			cout << "����������ϢΪ��" << endl;
			p->Next->readerInfoDisplay();
			if ( p->borrowNumber != 0 )
				cout << "\n�˶��߻���ͼ��δ�黹��";
			cout << "\nȷ��ɾ����(y\\n)" << endl;
			char c;
			cin >> c;
			if ( c == 'y' || c == 'Y' )
			{
				Reader *temp;
				temp = p->Next;
				p->Next = p->Next->Next;
				delete temp;
				cout << "ɾ���ɹ���" << endl;
				saveReaders();
				cin.get();cin.get();
				return;
			}
		}
	}
	if ( flag )
		cout << "δ�����������Ϣ��" << endl;
	saveReaders();
	cin.get();cin.get();
}
void Administrator::displayReaders()	//��ʾȫ��������Ϣ
{
	int i = 0;
	for ( Reader *p = rHead->Next; p != rEnd; p = p->Next )
		i++;
	cout << "��ǰ���ж��߼�¼" << i << "��" << endl;
	i = 0;
	for ( Reader *p = rHead->Next; p != rEnd; p = p->Next )
	{
		i++;
		cout << "\t" << i << "." << endl;
		p->readerInfoDisplay();
	}
	cout << "ȫ��������Ϣ��ʾ��ϣ����س�������..." << endl;
	cin.get();cin.get();
}

void Administrator::seekReader()	//����������Ϣ
{
	int flag = 0;
	cout << "������Ҫ�����Ķ��ߵ��û�����";
	string str;
	cin >> str;
	cout << "���������û���Ϣ���£�" << endl;
	for (Reader *p = rHead->Next; p != rEnd; p = p->Next )
	{
		if ( p->name == str )
		{
			flag++;
			cout << "\t" << flag << "." << endl;
			p->readerInfoDisplay();
			cout << endl;
		}
	}
	if ( !flag )
		cout << "δ�����������Ϣ��" << endl;
	cin.get();cin.get();
}
void Administrator::modifyReader()	//�޸Ķ�����Ϣ
{
	int flag = 0;
	cout << "������Ҫ�޸ĵĶ��ߵ��û�����";
	string str;
	cin >> str;
	cout << "���������û���Ϣ���£�" << endl;
	for (Reader *p = rHead->Next; p != rEnd; p = p->Next )
	{
		if ( p->name == str )
		{
			flag++;
			p->readerInfoDisplay();
			cout << endl;
			cout << "\t#�޸Ĳ˵�#\n\t\t1.�޸��û���\n\t\t2.�޸�����\n\t\t3.�޸��ֻ�����" << endl;
			cout << "���������ѡ��";
			int order;
			cin >> order;
			switch( order )
			{
			case 1:
				{
					cout << "�������û���(���Ȳ�����14���ַ�)��";
					cin >> str;
					while(1)
					{
						if ( str.size() < 14 )
						{
							bool i = 1;
							for ( Reader *p = rHead->Next; p != rEnd; p = p->Next )
							{
								if ( p->name == str )
								{
									cout << "�û����ѱ�ʹ�ã����������룺";
									cin >> str;
								}
							}
							if ( i )	break;
						}
						else
						{
							cout << "�û������ȳ���14���ַ������������룺";
							cin >> str;
						}
					}
					p->name = str;
				}break;
			case 2:
				cout << "���������룺";
				cin >> p->password;
				break;
			case 3:
				cout << "�������ֻ����룺";
				cin >> p->phoneNumber;
				break;
			default:
				cout << "���س�������..." << endl;
			}
		}
	}
	if ( !flag )
		cout << "δ�����������Ϣ��" << endl;
	saveReaders();
	cin.get();cin.get();
}
#endif   //_ADMINISTRATOR_H_
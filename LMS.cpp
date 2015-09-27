#include"book.h"
#include"reader.h"
#include"book_data.h"
#include"administrator.h"
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
const string PASSWORD = "1";

void Index();
void Welcome();
void Login();
void AdminLogin();
void AdminMenu();
void ReaderMenu();
void BookMenu();
void ReaderInterface();

int main()
{
	int order, i;
	bool quit, quit_1, quit_2,quit_3;
	quit = quit_1 = quit_2 = quit_3 = false;
	Administrator Admin;
	Welcome();
	while ( !quit )
	{
		Login();
		cin >> order;
		switch ( order )
		{
		case 0: quit = true; break;
		case 1:
		{
			Reader *p;
			Index();
			cout << "\t\t#���ߵ�¼#\n";
			cout << "\n\n\t\t�������û�����\n\t\t";
			string str;
			bool flag = 1;
			cin >> str;
			for ( p = Admin.rHead->Next; p != Admin.rEnd; p = p->Next )
				if ( p->name == str || p->phoneNumber == str )
				{
					flag = 0;
					cout << "\t\t���������룺\n\t\t";
					cin >> str;
					int i = 1;
					while ( 1 )
					{
						i++;
						if ( str == p->password )
						{
							cout << "\n\t\t��¼�ɹ���"<< endl;
							system("pause");
							while ( !quit_1 )
							{
								ReaderInterface();
								cin >> i;
								switch ( i )
								{
								case 0: exit(0);break;
								case 1: Admin.borrowBook(p);break;
								case 2: Admin.returnBook(p);break;
								case 3: Admin.ReaderData::seekBook();break;
								case 4: p->readerInfoDisplay();
									cin.get();cin.get();
									break;
								default: continue;
								}
							}
						}
						else
						{
							if ( 4 - i )
							{
								cout << "��������㻹��" <<  4 - i 
									<< "�λ��ᡣ" << endl;
								cout << "\t\t���������룺\n\t\t"; 
								cin >> str;
							}
							else 
							{
								cout << "��������˳�ϵͳ..." << endl;
								getchar();
								exit(0);
							}
						}	
					}
				}
			if ( flag )
			{
				cout << "�û������ڣ�";
				cin.get();cin.get();
				continue;
			}
			
		}break;
		case 2:
			Index();
			cout << "\t\t#�û�ע��#\n\n\n";
			Admin.addReader();
			break;
		case 3:
			AdminLogin();
			while ( !quit_1 )
			{
				AdminMenu();
				cin >> i;
				switch ( i )
				{
				case 0: exit(0);break;
				case 1: 
					while ( !quit_2 )
					{
						ReaderMenu();
						cin >> i;
						switch ( i )
						{
						case 6: quit_2 = true;break;
						case 1: Admin.addReader();break;
						case 2: Admin.deleteReader();break;
						case 3: Admin.seekReader();break;
						case 4: Admin.modifyReader();break;
						case 5: Admin.displayReaders();break;
						case 0: exit(0);break;
						default: continue;
						}
					}
					break;
				case 2: 
					while ( !quit_3 )
					{
						BookMenu();
						cin >> i;
						switch ( i )
						{
						case 6: quit_3 = true;break;
						case 1: Admin.addBook();break;
						case 2: Admin.deleteBook();break;
						case 3: Admin.BookData::seekBook();break;
						case 4: Admin.modifyBook();break;
						case 5: Admin.displayBooks();break;
						case 0: exit(0);break;
						default: continue;
						}
					}
					break;
				default: continue;
				}
			}
			break;
		default:continue;
		}
	}
	return 0;
}

void Index()
{
	system ("cls");
	cout << "\n\n\n\t\t\t*******************************\n";  
	cout << "\t\t                 ͼ�����ϵͳ\n";  
	cout << "\t\t\t*******************************\n\n\n";  
	for ( int i = 0; i < 80; i++)
		cout << '-';
	cout << endl; 
}
void Welcome()
{
	cout << "\n\n\n\t\t\t*******************************\n";  
	cout << "\t\t             ��ӭ����ͼ�����ϵͳ\n";  
	cout << "\t\t\t*******************************\n\n\n";  
	for ( int i = 0; i < 80; i++)
		cout << '-';
	cout << endl; 
	cout << "\n\t\t\t���飬\n";  
	cout << "\t\t\t\t  ���ż���͵ĸ߹�֮��\n\n";  
	cout << "\t_______________________________"
		 << "_______________________________\n";  
	cout << "\t��Ȩ����\tversion: 1.0\n\t\t\t\t\t\t\t\tLudics\n\n\n";  
	cout << "\n\n\t<�����������>" << endl;
	getchar();
}

void Login()
{
	Index(); 
	cout << "\t\t#��¼#\n";
	cout << "\t\t\t       1.��¼"<<endl;
	cout << "\t\t\t       2.ע��"<<endl;
	cout << "\t\t\t       3.����Ա��¼"<<endl;
	cout << "\t\t\t       0.��ȫ�˳�ϵͳ"<<endl;
	cout << "\t_______________________________"
		 << "_______________________________\n"; 
	cout << "\n\t\t\n\t\t��ѡ��";
}

void AdminLogin()
{
	Index();
	cout << "\t\t���������Ա���\n\t\t" ;
	string str;
	cin >> str;
	int i = 1;
	while ( 1 )
	{
		i++;
		if ( str == PASSWORD )	break;
		else
		{
			if ( 4 - i )
			{
				cout << "��������㻹��" <<  4 - i << "�λ��ᡣ" << endl;
				cout << "\t\t���������Ա���\n\t\t"; 
				cin >> str;
			}
			else 
			{
				cout << "��������˳�ϵͳ..." << endl;
				getchar();
				exit(0);
			}
		}	
	}
}
void AdminMenu()
{
	Index();
	cout << "\t\t#����Ա�˵�#\n";
	cout << "\t\t\t       1.������Ϣά��"<<endl;
	cout << "\t\t\t       2.ͼ����Ϣά��"<<endl;
	cout << "\t\t\t       0.��ȫ�˳�ϵͳ"<<endl;
	cout << "\t_______________________________"
		 << "_______________________________\n"; 
	cout << "\n\t\t\n\t\t��ѡ��";
}

void ReaderMenu()
{
	Index();
	cout << "\t\t#������Ϣά��#\n";
	cout << "\t\t\t       1.��Ӷ�����Ϣ"<<endl;
	cout << "\t\t\t       2.ɾ��������Ϣ"<<endl;
	cout << "\t\t\t       3.����������Ϣ"<<endl;
	cout << "\t\t\t       4.�޸Ķ�����Ϣ"<<endl;
	cout << "\t\t\t       5.��ʾȫ����Ϣ"<<endl;
	cout << "\t\t\t       6.����"<<endl;
	cout << "\t\t\t       0.��ȫ�˳�ϵͳ"<<endl;
	cout << "\t_______________________________"
		 << "_______________________________\n"; 
	cout << "\n\t\t\n\t\t��ѡ��";
}

void BookMenu()
{
	Index();
	cout << "\t\t#ͼ����Ϣά��#\n";
	cout << "\t\t\t       1.���ͼ����Ϣ"<<endl;
	cout << "\t\t\t       2.ɾ��ͼ����Ϣ"<<endl;
	cout << "\t\t\t       3.����ͼ����Ϣ"<<endl;
	cout << "\t\t\t       4.�޸�ͼ����Ϣ"<<endl;
	cout << "\t\t\t       5.��ʾȫ����Ϣ"<<endl;
	cout << "\t\t\t       6.����"<<endl;
	cout << "\t\t\t       0.��ȫ�˳�ϵͳ"<<endl;
	cout << "\t_______________________________"
		 << "_______________________________\n"; 
	cout << "\n\t\t\n\t\t��ѡ��";
}

void ReaderInterface()
{
	Index();
	cout << "\t\t#���߲˵�#\n";
	cout << "\t\t\t       1.����"<<endl;
	cout << "\t\t\t       2.����"<<endl;
	cout << "\t\t\t       3.����ͼ����Ϣ"<<endl;
	cout << "\t\t\t       4.�鿴������Ϣ"<<endl;
	cout << "\t\t\t       0.��ȫ�˳�ϵͳ"<<endl;
	cout << "\t_______________________________"
		 << "_______________________________\n"; 
	cout << "\n\t\t\n\t\t��ѡ��";
}



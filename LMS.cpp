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
			cout << "\t\t#读者登录#\n";
			cout << "\n\n\t\t请输入用户名：\n\t\t";
			string str;
			bool flag = 1;
			cin >> str;
			for ( p = Admin.rHead->Next; p != Admin.rEnd; p = p->Next )
				if ( p->name == str || p->phoneNumber == str )
				{
					flag = 0;
					cout << "\t\t请输入密码：\n\t\t";
					cin >> str;
					int i = 1;
					while ( 1 )
					{
						i++;
						if ( str == p->password )
						{
							cout << "\n\t\t登录成功！"<< endl;
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
								cout << "密码错误！你还有" <<  4 - i 
									<< "次机会。" << endl;
								cout << "\t\t请输入密码：\n\t\t"; 
								cin >> str;
							}
							else 
							{
								cout << "按任意键退出系统..." << endl;
								getchar();
								exit(0);
							}
						}	
					}
				}
			if ( flag )
			{
				cout << "用户不存在！";
				cin.get();cin.get();
				continue;
			}
			
		}break;
		case 2:
			Index();
			cout << "\t\t#用户注册#\n\n\n";
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
	cout << "\t\t                 图书管理系统\n";  
	cout << "\t\t\t*******************************\n\n\n";  
	for ( int i = 0; i < 80; i++)
		cout << '-';
	cout << endl; 
}
void Welcome()
{
	cout << "\n\n\n\t\t\t*******************************\n";  
	cout << "\t\t             欢迎进入图书管理系统\n";  
	cout << "\t\t\t*******************************\n\n\n";  
	for ( int i = 0; i < 80; i++)
		cout << '-';
	cout << endl; 
	cout << "\n\t\t\t读书，\n";  
	cout << "\t\t\t\t  是门槛最低的高贵之举\n\n";  
	cout << "\t_______________________________"
		 << "_______________________________\n";  
	cout << "\t版权所有\tversion: 1.0\n\t\t\t\t\t\t\t\tLudics\n\n\n";  
	cout << "\n\n\t<按任意键继续>" << endl;
	getchar();
}

void Login()
{
	Index(); 
	cout << "\t\t#登录#\n";
	cout << "\t\t\t       1.登录"<<endl;
	cout << "\t\t\t       2.注册"<<endl;
	cout << "\t\t\t       3.管理员登录"<<endl;
	cout << "\t\t\t       0.安全退出系统"<<endl;
	cout << "\t_______________________________"
		 << "_______________________________\n"; 
	cout << "\n\t\t\n\t\t请选择：";
}

void AdminLogin()
{
	Index();
	cout << "\t\t请输入管理员口令：\n\t\t" ;
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
				cout << "口令错误！你还有" <<  4 - i << "次机会。" << endl;
				cout << "\t\t请输入管理员口令：\n\t\t"; 
				cin >> str;
			}
			else 
			{
				cout << "按任意键退出系统..." << endl;
				getchar();
				exit(0);
			}
		}	
	}
}
void AdminMenu()
{
	Index();
	cout << "\t\t#管理员菜单#\n";
	cout << "\t\t\t       1.读者信息维护"<<endl;
	cout << "\t\t\t       2.图书信息维护"<<endl;
	cout << "\t\t\t       0.安全退出系统"<<endl;
	cout << "\t_______________________________"
		 << "_______________________________\n"; 
	cout << "\n\t\t\n\t\t请选择：";
}

void ReaderMenu()
{
	Index();
	cout << "\t\t#读者信息维护#\n";
	cout << "\t\t\t       1.添加读者信息"<<endl;
	cout << "\t\t\t       2.删除读者信息"<<endl;
	cout << "\t\t\t       3.检索读者信息"<<endl;
	cout << "\t\t\t       4.修改读者信息"<<endl;
	cout << "\t\t\t       5.显示全部信息"<<endl;
	cout << "\t\t\t       6.返回"<<endl;
	cout << "\t\t\t       0.安全退出系统"<<endl;
	cout << "\t_______________________________"
		 << "_______________________________\n"; 
	cout << "\n\t\t\n\t\t请选择：";
}

void BookMenu()
{
	Index();
	cout << "\t\t#图书信息维护#\n";
	cout << "\t\t\t       1.添加图书信息"<<endl;
	cout << "\t\t\t       2.删除图书信息"<<endl;
	cout << "\t\t\t       3.检索图书信息"<<endl;
	cout << "\t\t\t       4.修改图书信息"<<endl;
	cout << "\t\t\t       5.显示全部信息"<<endl;
	cout << "\t\t\t       6.返回"<<endl;
	cout << "\t\t\t       0.安全退出系统"<<endl;
	cout << "\t_______________________________"
		 << "_______________________________\n"; 
	cout << "\n\t\t\n\t\t请选择：";
}

void ReaderInterface()
{
	Index();
	cout << "\t\t#读者菜单#\n";
	cout << "\t\t\t       1.借书"<<endl;
	cout << "\t\t\t       2.还书"<<endl;
	cout << "\t\t\t       3.检索图书信息"<<endl;
	cout << "\t\t\t       4.查看个人信息"<<endl;
	cout << "\t\t\t       0.安全退出系统"<<endl;
	cout << "\t_______________________________"
		 << "_______________________________\n"; 
	cout << "\n\t\t\n\t\t请选择：";
}



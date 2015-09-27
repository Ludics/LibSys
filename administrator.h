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
	void addBook();			//添加图书信息
	void deleteBook();		//删除图书信息
	void modifyBook();		//修改图书信息
	void addReader();		//添加读者信息
	void deleteReader();	//删除读者信息
	void displayReaders();	//显示全部读者信息
	void seekReader();		//检索读者信息
	void modifyReader();	//修改读者信息
};

void Administrator::addBook()		//添加图书信息
{
	cout << "请输入图书的ISBN编码：\n\t\t";
	string str;
	cin >> str;
	int flag = 1;
	for ( Book *p = bHead->Next; p != bEnd; p = p->Next )
	{
		if ( p->ISBN == str )
		{
			flag = 0;
			cout << "图书已存在！" << endl;
			p->bookInfoDisplay();
			cout << "确认添加库存吗？(y\\n)" <<endl;
			char c;
			cin >> c;
			if ( c == 'y' || c == 'Y')
			{
				cout << "请输入添加数量：";
				int i;
				cin >> i;
				p->currentInventory += i;
				p->totalInventory +=i;
				cout << "添加库存成功！按回车键继续..." << endl;
			}
			else
				cout << "未添加库存！按回车键继续..." << endl;
		}
	}
	if ( flag )
	{
		bEnd->ISBN = str;
		cout << "这是一种书库中没有的书！请按图书分类法为其编号：\n\t\t";
		cin >> str;
		while ( flag )
		{
			for (Book *p = bHead->Next; p != bEnd; p = p->Next )
				if ( p->bookID == str )
				{
					cout << "此编号已存在，请重新编号：";
					cin >> str;
					continue;
				}
			flag = 0;
		}
		bEnd->bookID = str;
		cout << "请按提示输入图书信息。(空格请用\"_\")" << endl;
		cout << "书名：";
		cin >> bEnd->bookName;
		cout << "作者：";
		cin >> bEnd->writer;
		cout << "出版社：";
		cin >> bEnd->press;
		cout << "出版年份：";
		cin >> bEnd->publishYear;
		bEnd->totalInventory = bEnd->currentInventory = 1;
		cout << "请输入添加数量：";
		int i;
		cin >> i;
		i --;
		bEnd->currentInventory += i;
		bEnd->totalInventory += i;
		cout << "图书信息添加完毕！" << endl;
		bEnd->bookInfoDisplay();
		bEnd->Next = new Book;
		bEnd = bEnd->Next;
		cout << "按回车键继续..." << endl;
	}
	saveBooks();
	cin.get();cin.get();
}
void Administrator::deleteBook()		//删除图书信息
{
	int flag = 0;
	cout << "请输入要删除图书的书名或作者：";
	string str;
	cin >> str;
	cout << "检索到的书籍信息如下：" << endl;
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
		cout << "删除请输入检索到的图书编号：";
		cin >> str;
		for (Book *p = bHead; p->Next != bEnd; p = p->Next )
		{
			if ( p->Next->bookID == str )
			{
				flag = 0;
				if ( p->currentInventory == p->totalInventory )
				{
					cout << "确认删除吗？(y\\n)" << endl;
					char c;
					cin >> c;
					if ( c == 'y' || c == 'Y' )
					{
						Book *temp = p->Next;
						p->Next = p->Next->Next;
						delete temp;
						cout << "\n信息删除成功！按回车键继续..." << endl;
						saveBooks();
						cin.get();cin.get();
						return;
					}
					else
						cout << "\n图书信息未删除！按回车键继续..." << endl;
				}
				else
					cout << "还有图书没有归还，无法删除信息。按回车键继续..." << endl;
			}
		}
		if ( flag )
			cout << "图书编号输入不正确，信息未删除！按回车键继续..." << endl;
	}
	else
		cout << "未检索到相关信息，按回车键继续..." << endl;
	cin.get();cin.get();
}
//修改图书信息
void Administrator::modifyBook()
{
	int flag = 0;
	cout << "请输入要修改的图书的书名或作者：";
	string str;
	cin >> str;
	cout << "检索到的书籍信息如下：" << endl;
	for (Book *p = bHead->Next; p != bEnd; p = p->Next )
	{
		if ( p->writer == str || p->bookName == str )
		{
			flag++;
			p->bookInfoDisplay();
			cout << endl;
			cout << "\t#修改菜单#\n\t\t1.修改书名\n\t\t2.修改作者\n\t\t3.修改ISBN" 
				 << "\n\t\t4.修改出版社\n\t\t5.修改出版年份\n\t\t6.添加库存\n\t\t7.修改编号"<< endl;
			cout << "请输入序号选择：";
			int order;
			cin >> order;
			switch( order )
			{
			default: return; break;
			case 1:
				cout << "请输入书名:";
				cin >> p->bookName;
				cout << "修改成功！修改后信息为：" << endl;
				p->bookInfoDisplay();
				break;
			case 2:
				cout << "请输入作者:";
				cin >> p->writer;
				cout << "修改成功！修改后信息为：" << endl;
				p->bookInfoDisplay();
				break;
			case 3:
				{
					string str;
					cout << "请输入ISBN：";
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
								cout << "ISBN已存在！" << endl;
								p1->bookInfoDisplay();
								cout << "请重新输入ISBN：";
								cin >> str;
								continue;
							}
						}
						flag1 = 0;
					}
					if ( flag )
					{
						cout << "修改成功！修改后信息为：";
						p->bookInfoDisplay();
					}
				} break;
			case 4:
				cout << "请输入出版社:";
				cin >> p->press;
				cout << "修改成功！修改后信息为：" << endl;
				p->bookInfoDisplay();
				break;
			case 5:
				cout << "请输入出版年份:";
				cin >> p->publishYear;
				cout << "修改成功！修改后信息为：" << endl;
				p->bookInfoDisplay();
				break;
			case 6:
			{
				cout << "请输入添加数目：";
				int i;
				cin >> i;
				p->currentInventory += i;
				p->totalInventory += i;
				cout << "修改成功！修改后信息为：" << endl;
				p->bookInfoDisplay();	
			} break;
			case 7:
				{
					string str;
					cout << "请输入编号：";
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
								cout << "编号已存在！" << endl;
								p1->bookInfoDisplay();
								cout << "请重新输入编号：";
								cin >> str;
								continue;
							}
						}
						flag1 = 0;
					}
					if ( flag )
					{
						p->bookID = str;
						cout << "修改成功！修改后信息为：" << endl;
						p->bookInfoDisplay();
					}
				} break;
			}
		}
	}
	if ( !flag )
		cout << "未检索到相关信息。" << endl;
	saveBooks();
	cin.get();cin.get();
}

void Administrator::addReader()		//添加读者信息
{
	cout << "请输入用户名(长度不大于14个字符)：";
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
					cout << "用户名已被使用，请重新输入：";
					cin >> str;
				}
			}
			if ( flag )	break;
		}
		else
		{
			cout << "用户名长度超过14个字符，请重新输入：";
			cin >> str;
		}
	}
	rEnd->name = str;
	cout << "请输入密码：";
	cin >> rEnd->password;
	cout << "请输入手机号码：";
	cin >> rEnd->phoneNumber;
	rEnd->Next = new Reader;
	rEnd = rEnd->Next;
	cout << "新读者用户创建成功！按回车键继续..." << endl;
	saveReaders();
	cin.get();cin.get();
}
void Administrator::deleteReader()			//删除读者信息
{
	bool flag = 1;
	cout << "请输入所要删除的读者的用户名：";
	string str;
	cin >> str;
	for ( Reader *p = rHead; p->Next != rEnd; p = p->Next )
	{
		if ( p->Next->name == str )
		{
			flag = 0;
			cout << "检索到的信息为：" << endl;
			p->Next->readerInfoDisplay();
			if ( p->borrowNumber != 0 )
				cout << "\n此读者还有图书未归还！";
			cout << "\n确认删除吗？(y\\n)" << endl;
			char c;
			cin >> c;
			if ( c == 'y' || c == 'Y' )
			{
				Reader *temp;
				temp = p->Next;
				p->Next = p->Next->Next;
				delete temp;
				cout << "删除成功！" << endl;
				saveReaders();
				cin.get();cin.get();
				return;
			}
		}
	}
	if ( flag )
		cout << "未检索到相关信息。" << endl;
	saveReaders();
	cin.get();cin.get();
}
void Administrator::displayReaders()	//显示全部读者信息
{
	int i = 0;
	for ( Reader *p = rHead->Next; p != rEnd; p = p->Next )
		i++;
	cout << "当前共有读者记录" << i << "条" << endl;
	i = 0;
	for ( Reader *p = rHead->Next; p != rEnd; p = p->Next )
	{
		i++;
		cout << "\t" << i << "." << endl;
		p->readerInfoDisplay();
	}
	cout << "全部读者信息显示完毕，按回车键继续..." << endl;
	cin.get();cin.get();
}

void Administrator::seekReader()	//检索读者信息
{
	int flag = 0;
	cout << "请输入要检索的读者的用户名：";
	string str;
	cin >> str;
	cout << "检索到的用户信息如下：" << endl;
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
		cout << "未检索到相关信息。" << endl;
	cin.get();cin.get();
}
void Administrator::modifyReader()	//修改读者信息
{
	int flag = 0;
	cout << "请输入要修改的读者的用户名：";
	string str;
	cin >> str;
	cout << "检索到的用户信息如下：" << endl;
	for (Reader *p = rHead->Next; p != rEnd; p = p->Next )
	{
		if ( p->name == str )
		{
			flag++;
			p->readerInfoDisplay();
			cout << endl;
			cout << "\t#修改菜单#\n\t\t1.修改用户名\n\t\t2.修改密码\n\t\t3.修改手机号码" << endl;
			cout << "请输入序号选择：";
			int order;
			cin >> order;
			switch( order )
			{
			case 1:
				{
					cout << "请输入用户名(长度不大于14个字符)：";
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
									cout << "用户名已被使用，请重新输入：";
									cin >> str;
								}
							}
							if ( i )	break;
						}
						else
						{
							cout << "用户名长度超过14个字符，请重新输入：";
							cin >> str;
						}
					}
					p->name = str;
				}break;
			case 2:
				cout << "请输入密码：";
				cin >> p->password;
				break;
			case 3:
				cout << "请输入手机号码：";
				cin >> p->phoneNumber;
				break;
			default:
				cout << "按回车键继续..." << endl;
			}
		}
	}
	if ( !flag )
		cout << "未检索到相关信息。" << endl;
	saveReaders();
	cin.get();cin.get();
}
#endif   //_ADMINISTRATOR_H_
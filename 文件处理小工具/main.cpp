#include <iostream>
#include "fileHanding.h"
using namespace std;


int main(int argv, char const* argc[])
{
	FileHanding* fh = new FileHanding;
	int select = 0;
	while (1) 
	{
		fh->showMenu();
		cin >> select;
		switch (select)
		{
		case 1:
			fh->splitFile();
			break;
		case 2:
			fh->mergeFile();
			break;
		case 0:
			system("pause");
			delete fh;
			exit(0);
			break;
		default:
			cout << "输入错误，请重新输入！" << endl;
			break;
		}
		system("pause");
		system("cls");
	}
	
	system("pause");
	return 0;
}

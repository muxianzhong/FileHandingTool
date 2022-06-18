#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <io.h>
#include <direct.h>
#include <vector>
#include <stdio.h>
#include <sys/stat.h>
#include "fileHanding.h"
using namespace std;

#pragma warning(disable : 4996)

// 构造函数
FileHanding::FileHanding()
{

}

// 析构函数
FileHanding::~FileHanding()
{

}

// 主菜单
void FileHanding::showMenu()
{
	cout << "==============文件处理小工具==============" << endl;
	cout << "\t--------------------------" << endl;
	cout << "\t|                        | " << endl;
	cout << "\t|       1.文件分行       |" << endl;
	cout << "\t|                        | " << endl;
	cout << "\t|       2.文件合并       |" << endl;
	cout << "\t|                        | " << endl;
	cout << "\t|       0.退出系统       |" << endl;
	cout << "\t|                        | " << endl;
	cout << "\t--------------------------" << endl;
	cout << "请输入您的选择：" << endl;
}

// 获取时间
void FileHanding::printTime()
{
	time_t now;
	time(&now);
	tm *t;
	t = localtime(&now);
	char buffer[80];
	strftime(buffer, sizeof(buffer), "[%Y-%m-%d %H:%M:%S]", t);
	cout << buffer;
}

// 获取文件路径 
string FileHanding::getPath(const unsigned short mode)
{
	string path;
	cout << "请输入文件路径：" << endl;
	while (1) {
		cin >> path;
		if (access(path.c_str(), 0) != 0) {
			cout << "文件路径输入错误，请重新输入：" << endl;
			continue;
		}

		struct stat s;
		int ret = stat(path.c_str(), &s);
		if (ret != 0 || (s.st_mode & _S_IFMT) != mode) {
			cout << ret << endl;
			cout << s.st_mode << endl;
			cout << "文件路径输入错误，请重新输入：" << endl;
			continue;
		}

		break;
	}

	return path;
}

void FileHanding::getFiles(const string& path, vector<string>& filse)
{
	intptr_t hFile = 0;
	struct _finddata_t fileinfo;
	string p = path + "\\*";
	
	hFile = _findfirst(p.c_str(), &fileinfo);
	if (hFile != -1) {
		do {
			if (fileinfo.attrib & _A_ARCH) {
				filse.push_back(fileinfo.name);
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
	else {
		perror("_findfirst");
	}

}

// 拆分文件，在原始文件路径下创建新文件夹保存
void FileHanding::splitFile()
{
	string path = this->getPath(S_IFREG);
	int index = path.find_last_of('\\');
	string folderPath = path.substr(0, index);
	string fileName = path.substr(index + 1, -1);
	index = fileName.find_last_of('.');

	string storeFolder = folderPath + '\\' + fileName.substr(0, index);
	if (access(storeFolder.c_str(), 0) != 0) {
		int a = mkdir(storeFolder.c_str());
	}

	int numRows = 0;
	cout << "请输入拆分后的文件行数：" << endl;
	cin >> numRows;

	string newFile = to_string(numRows);
	string extension = fileName.substr(index, -1);
	string storePath;

	ifstream ifs(path, ios::in);
	ofstream ofs;
	string text;

	int count = 1;
	int lineNum = 0;

	int select = 0;
	cout << "请选择输出文件行间分割符：" << endl;
	cout << "1 - 空格" << endl;
	cout << "2 - 换行" << endl;
	while (1) {
		cin >> select;
		if (select != 1 && select != 2) {
			cout << "输入错误，请重新输入" << endl;
		}
		else {
			break;
		}
	}
	char symbol = '\n';
	if (select == 1) symbol = ' ';

	while (getline(ifs, text, '\n')) {
		if (lineNum == 0) {
			storePath = storeFolder + '\\' + newFile + '(' + to_string(count) + ')' + extension;
			printTime();
			cout << "正在处理文件：" << storePath << endl;
			ofs.open(storePath, ios::out);
		}
		ofs << text << symbol;
		lineNum++;
		if (lineNum == numRows) {
			ofs.close();
			lineNum = 0;
			count++;
		}
	}

	ifs.close();
	if (ofs.is_open()) ofs.close();

	cout << "文件分割完毕，已分割文件数量：" << count << endl;
}


// 文件合并，将多个文件合并为一个文件
void FileHanding::mergeFile()
{
	string path = this->getPath(S_IFDIR);
	cout << "请输入每个文件跳过行数：" << endl;
	int skip = 0;
	cin >> skip;

	vector<string> files;
	this->getFiles(path, files);
	if (files.size() == 0) {
		cout << "所选路径中无文件" << endl;
		return;
	}

	// 生成输出文件路径
	int index = path.find_last_of('\\');
	string newPath = path.substr(0, index);
	string newFile = path.substr(index + 1, -1);
	index = files[0].find_last_of('.');
	newFile.append(files[0].substr(index, -1));
	newPath.append("\\").append(newFile);

	ifstream ifs;
	ofstream ofs(newPath, ios::out);
	path.append("\\");
	string text;
	for (int i = 0; i < files.size(); i++) {
		printTime();
		cout << "正在处理文件：" << path + files[i] << endl;
		ifs.open(path + files[i], ios::in);
		for (int j = 0; j < skip; j++) {
			if (!(getline(ifs, text, '\n')))
				break;
		}
		while (getline(ifs, text, '\n')) {
			ofs << text << endl;
		}
		ifs.close();
	}
	ofs.close();
	cout << "合并后的文件路径为：" << newPath << endl;
}
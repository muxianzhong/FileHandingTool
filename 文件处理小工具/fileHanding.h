#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 文件拆分类
class FileHanding
{
public:
	// 构造函数
	FileHanding();

	// 析构函数
	~FileHanding();

	// 主菜单
	void showMenu();

	// 输出时间：'[1900-00-00 00:00:00]'
	void printTime();

	// 获取文件路径
	string getPath(const unsigned short mode);

	// 获取文件夹内全部文件路径
	void getFiles(const string& path, vector<string>& filse);

	// 文件拆分，将一个或多个文件拆分为相同行数的多个文件
	void splitFile();

	// 文件合并，将多个文件合并为一个文件
	void mergeFile();
};
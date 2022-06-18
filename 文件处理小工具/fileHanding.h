#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// �ļ������
class FileHanding
{
public:
	// ���캯��
	FileHanding();

	// ��������
	~FileHanding();

	// ���˵�
	void showMenu();

	// ���ʱ�䣺'[1900-00-00 00:00:00]'
	void printTime();

	// ��ȡ�ļ�·��
	string getPath(const unsigned short mode);

	// ��ȡ�ļ�����ȫ���ļ�·��
	void getFiles(const string& path, vector<string>& filse);

	// �ļ���֣���һ�������ļ����Ϊ��ͬ�����Ķ���ļ�
	void splitFile();

	// �ļ��ϲ���������ļ��ϲ�Ϊһ���ļ�
	void mergeFile();
};
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
#include <io.h>

using namespace std;

// ������� ������ �)
void task_01();       

// ������� ������ �)
void task_02();

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	task_01();
	//task_02();

	return 0;
}

// a. ��� ��������� ����. ������������� ���, ������ �� ������ ������ �����, ������������� ����� ���� ���.
void task_01()
{
	try
	{
		cout << "������� �������� �����, ������ ����� ������� �������: ";
		char finName[256];
		cin >> finName;
		FILE* fin;
		fopen_s(&fin, finName, "r+b");


		int count[100] = {0};
		char arr_words[100][100];

		char str[256];
		string strUniqueCharFile;
		char readChar;
		long file_pos;
		fseek(fin, 0, SEEK_END);
		long file_end = ftell(fin);
		fseek(fin, 0, SEEK_SET);
		int i = 0;
		long file_pos_write = ftell(fin);
		long file_pos_read = ftell(fin);
		while(ftell(fin) != file_end && fread(&readChar, sizeof(char), 1, fin) != EOF){
			while (ftell(fin) != file_end && readChar != EOF && readChar != '\n') {
				fseek(fin, file_pos_read, SEEK_SET);
				int j = 0;
				while (ftell(fin) != file_end && fread(&readChar, sizeof(char), 1, fin) != EOF && readChar != '\n' && readChar != ' ') {
					str[j] = readChar;
					j++;
				}
				str[j] = '\0';
				file_pos_read = ftell(fin);
				int index_search = 0;
				while (index_search < 100 && strcmp(str, arr_words[index_search]) != 0)
					index_search++;
				if (index_search == 100 || count[index_search] == 1) {//���� ����� ����������� �� ����� 1 ��� 0 ���
					fseek(fin, file_pos_write, SEEK_SET);//����������� ��������� �� ������� ��� ������
					fwrite(&str, sizeof(char*), 1, fin);//������ ����� � ����
					file_pos_write = ftell(fin);//��������� ������� ��� ������
					if (index_search == 100) {
						strcpy_s(arr_words[i], str);
						count[i] = 1;
						i++;
					}
					else
						count[index_search]++;
				}
				fseek(fin, file_pos_read, SEEK_SET);
				fread(&readChar, sizeof(char), 1, fin);
			}
		}
		_chsize(_fileno(fin), file_pos_write);
		fclose(fin);
		cout << "�� ������ �������!" << endl;
	}
	catch (const char* msg)
	{
		cerr << msg << endl;
		exit(-1);
	}
}

// ������� 2-��� ������� ��� �������� � ����� �������� � �������� ����
void CreateBinFile();

// ������� 2-��� ������� ��� ��������� ��������� �����
void ProcessBinFile();

// ������� 2-��� ������� ��� ������ �������� ��������� 
void WriteBinFIle();

void task_02()
{
	while (true)
	{
		cout << "�������� �������:" << endl;
		cout << "1 - ������� �������� ����;" << endl;
		cout << "2 - ���������� �������� ����;" << endl;
		cout << "3 - ������� �������� ��������� �����;" << endl;
		cout << "4 - ����� �� ���������;" << endl;
		int select;
		cin >> select;

		cout << endl << "#####################################################" << endl;
		switch (select)
		{
		case 1:
			CreateBinFile();
			break;
		case 2:
			ProcessBinFile();
			break;
		case 3:
			WriteBinFIle();
			break;
		case 4:
			cout << "����� �� ���������..." << endl;
			return;
		default:
			cout << "�� ���������� ������ �������!" << endl;
			break;
		}

		cout << "#####################################################" << endl << endl;
	}
}

// ������� ��� �������� �����
void CreateBinFile()
{
	try
	{
		cout << "������� �������� �����, ���� ����� ������� �����: ";
		string foutName;
		cin >> foutName;
		ofstream fout(foutName, ios::binary | ios::out);
		if (!fout.is_open())
			throw "���� ��� ����� ����� �� ������!";

		cout << "������� ����� n: ";
		int n;
		cin >> n;

		cout << "������� �������� ��� ��������� �����:" << endl;
		cout << "������� ���������� 2n ������������� + 2n ������������� �������������������" << endl;
		int k;
		cin >> k;
		for (size_t i = 0; i < k; i++)
		{
			cout << "������� 2n ������������� �����" << endl;
			for (int i = 0; i < 2 * n; i++)
			{
				int value;
				cin >> value;
				fout.write((char*)&value, sizeof(value));
			}
			cout << "������� 2n ������������� �����" << endl;
			for (int i = 0; i < 2 * n; i++)
			{
				int value;
				cin >> value;
				fout.write((char*)&value, sizeof(value));
			}
		}
		
		fout.close();

		cout << "�� ������ �������!" << endl;
	}
	catch (const char* msg)
	{
		cerr << msg << endl;
		exit(-1);
	}
}

// ������� ��� ������ �����
void WriteBinFIle()
{
	try
	{
		cout << "������� �������� �����, ���� ����� ������� �����: ";
		string finName;
		cin >> finName;

		ifstream fin(finName, ios::binary | ios::out);
		if (!fin.is_open())
			throw "���� ��� ����� ����� �� ������!";

		int value;
		fin.read((char*)&value, sizeof(value));
		while (!fin.eof())
		{
			cout << value << ' ';
			fin.read((char*)&value, sizeof(value));
		}
		cout << endl;

		fin.close();

		cout << "�� ������ �������!" << endl;
	}
	catch (const char* msg)
	{
		cerr << msg << endl;
		exit(-1);
	}
}

// �. ��� ���� �� ��������� ����� ����� � ����� n. ����� � ����� ���� � ��������� �������: 2n �������������, 2n �������������.
// ������������� ���� ���, ����� ����� � ����� ��� � c�������� �������: n �������������, n ������������� � ��� �����
void ProcessBinFile()
{
	try
	{
		cout << "������� �������� �����, ������ ����� ������� �����: ";
		string fName;
		cin >> fName;
		fstream f(fName, ios::binary | ios::in | ios::out);
		if (!f.is_open())
			throw "���� ��� ���������� ����� �� ������!";

		cout << "������� ����� n: ";
		int n;
		cin >> n;

		streampos pos = n * sizeof(int);
		streampos t_pos = (n - 1) * sizeof(int);
		streampos pos_cur = pos * 2;

		f.seekg(0, ios::end);
		streampos pos_end = f.tellg();

		f.seekg(pos_cur, ios::beg);
		pos_cur = pos * 6;
		int k = 0;
		while (f.tellg() < pos_end)
		{
			int x;
			int y;
			for (int i = 0; i < n; i++) { //����� ��������(�� ���������� n)
				f.seekp(-pos, ios::cur);
				streampos pos_x = f.tellp();
				f.read((char*)&x, sizeof(x));
				f.seekp(t_pos, ios::cur);
				streampos pos_y = f.tellp();
				f.read((char*)&y, sizeof(y));
				f.seekg(pos_x, ios::beg);
				f.write((char*)&y, sizeof(y));
				f.seekg(pos_y, ios::beg);
				f.write((char*)&x, sizeof(x));
				
			}
			k++;
			f.seekg(0, ios::beg);
			f.seekp(0, ios::beg);
			streampos pos_k = pos_cur * k;
			f.seekg(pos_k, ios::beg);
		}

		f.close();

		cout << "�� ������ �������!" << endl;
	}
	catch (const char* msg)
	{
		cerr << msg << endl;
		exit(-1);
	}
}

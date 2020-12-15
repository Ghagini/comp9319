// bwt.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
using namespace std;
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include<algorithm>
#include<map>


class bwtarray
{
public:
	void set_symble(char c) {
		this->symble = c;
	}
	int set_position(int i) {
		this->position = i;
		return i + 1;
	}
	void count_num(int i)
	{
		this->match_num = i;
	}
	void output()
	{
		cout << this->position<<' ';
		cout << this->symble<<' ';
		cout << this->match_num << endl;
	}
	char get_symble()
	{
		return this->symble;

	}
	int get_position()
	{
		return this->position;
	}
	int get_match()
	{
		return this->match_num;
	}

private:
	int position;
	char symble;
	int match_num;
};

void write_decoded_file(const std::string& path, const std::string& s);
string get_file_contents(const char* filename);


int main(int argc, char* argv[])
{
    const char* filename1 =argv[1];
	const char* filename2 = argv[2];
    //get file content
    std::string str1 = get_file_contents(filename1);
	map<char, int> map;
	std::map<char, int>::iterator iter;
	bwtarray* l=(bwtarray*)malloc(sizeof(bwtarray)* str1.length());
	int init_pos = 0;

    //decode
    for (int i = 0; i < str1.length(); i++)
    {
		if(str1[i]=='\n')
		{
			init_pos = i;
		}
		bwtarray array;
		iter = map.find(str1[i]);
		if (iter == map.end()) {
			map.insert(pair<char, int>(str1[i], 0));
			array.count_num(map[str1[i]]);
		}
		else {
			map[str1[i]] = map[str1[i]] + 1;
			array.count_num(map[str1[i]]);
		}
		array.set_symble(str1[i]);
		array.set_position(i);
		l[i] = array;
    }

	int temp1,temp2;
	std::map <char, int>::iterator m1_Iter;

	for (m1_Iter = map.begin(); m1_Iter != map.end(); m1_Iter++)
	{
		if (m1_Iter == map.begin())
		{
			temp1 = m1_Iter->second+1;
			m1_Iter->second = 0;
		}
		else {
			temp2 = temp1 + m1_Iter->second+1;
			m1_Iter->second = temp1;
			temp1 = temp2;
		}

	}

	char symb = '\n';
	int a, b, pos=init_pos;
	string output;

	for (int i = 0; i < str1.length(); i++)

	{
		output = symb + output;
		a = l[pos].get_match();
		b = map.at(symb);
		pos = a + b;
		symb= l[pos].get_symble();


	}
	write_decoded_file(filename2, output);


}

void write_decoded_file(const std::string& path, const std::string& s)
{
	std::fstream file(path, std::ios::out | std::ios::binary);
	file << s;
	file.close();
}


string get_file_contents(const char * filename)
{

	ifstream ifile(filename);
	ostringstream buf;
	char ch;
	while (buf && ifile.get(ch))
	buf.put(ch);
	return buf.str();
}
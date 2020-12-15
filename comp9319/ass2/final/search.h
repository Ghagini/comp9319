#pragma once
using namespace std;
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <string>
#include<algorithm>
#include<map>


class Search
{
public:
	std::string get_file_contents(const char* filename);
	void create_tables(std::string s);


	int backward_search(std::string pattern);
	int rank(char c, unsigned int n);

protected:
	std::map<char, unsigned int> c_table;
	std::map<char, std::map<int, int>> occ_table;
	int file_size;

};
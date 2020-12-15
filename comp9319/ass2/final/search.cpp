
using namespace std;
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <search.h>
#include<algorithm>
#include<map>
#include"search.h"



void Search:: create_tables(std::string s)
{
	std::map<char, unsigned int> c_table;
	std::map<char, std::map<int, int>> occ_table;  //charactor,position,occrance times
	std::map<int, int> times;
	std::map<char,unsigned int>::iterator iter;
	std::map<char, std::map<int, int>>::iterator iter2;
	std::map<int, int>::iterator iter3;
	int temp1, temp2;
	for (int i = 0; i < s.length(); i++)
	{
		iter = c_table.find(s[i]);
		if (iter == c_table.end()) {
			c_table.insert(pair<char, int>(s[i], 0));
		}
		else {
			c_table[s[i]] = c_table[s[i]] + 1;
		}

		iter2= occ_table.find(s[i]);
		if (iter2 == occ_table.end()) {
			times.clear();
			times.insert(pair<int, int>(i,1));
			occ_table.insert(pair<char, std::map<int, int>>(s[i], times));
		}
		else {
			times.clear();
			times = iter2->second;
			iter3 = times.end();
			iter3--;
			temp2 = times[iter3->first];
			times.insert(pair<int, int>(i,temp2+1));
			occ_table[s[i]]=times ;

		}




	}

	for (iter = c_table.begin(); iter != c_table.end(); iter++)
	{
		if (iter == c_table.begin())
		{
			temp1 = iter->second + 1;
			//cout << "temp1:" << temp1<<endl;
			iter->second = 0;
		}
		else {
			temp2 = temp1 + iter->second + 1;
			iter->second = temp1;
			temp1 = temp2;
		}

	}

	/*
	for (iter2 = occ_table.begin(); iter2 != occ_table.end(); iter2++)
	{

		cout << iter2->first<<endl;
		times = iter2->second;
		for(iter3 = times.begin(); iter3 != times.end(); iter3++)
		{
			cout << iter3->first << " " << iter3->second<<endl;
		}
		cout << '\n';

	}

	for (iter = c_table.begin(); iter != c_table.end(); iter++)
	{

		cout << iter->first << iter->second << endl;

	}
*/

	this->c_table =c_table ;
	this->occ_table = occ_table;


}
int  Search:: rank(char c,unsigned int n) {
	std::map<int, int> times;
	std::map<int, int>::iterator iter3;
	times=this->occ_table[c];
	int number =0;
	if (times.find(n)!=times.end())
	{
		number = times[n];
	}
	else {
		for (iter3 = times.begin(); iter3 != times.end(); iter3++)
		{
			if (iter3->first > n) {
				break;
			}

			else {
				number = iter3->second;
			}

		}
	}
	return number;
}
int  Search::backward_search(std::string pattern) {
	int p= pattern.length();
	const char* P=(char*)malloc(sizeof(char)*p);
	P = pattern.c_str();
	int i = p - 1;
	char c = P[p - 1];
	int fr = this->c_table[c];
	int lr;

	if (std::next(c_table.find(c)) != c_table.end())
	{
		lr = std::next(c_table.find(c))->second-1;
	}
	else
	{
		lr = this->file_size-1;
	}
	while (fr <= lr && i > 0)
	{
		c = P[i - 1];
		fr = c_table[c] + rank(c, fr - 1);
		lr = c_table[c] + rank(c, lr)-1;
		i--;

		if (lr < fr)
			return 0;
	}

	return (lr - fr+1);


	return 0;
}



std::string Search::get_file_contents(const char* filename)
{
	ifstream ifile(filename);
	ostringstream buf;
	char ch;
	while (buf && ifile.get(ch))
		buf.put(ch);
	this->file_size = (buf.str()).length();
	return buf.str();
}
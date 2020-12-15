// bwtsearch.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#pragma once
using namespace std;
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <string>
#include<algorithm>
#include<map>
#include "search.h"

int main(int argc, char* argv[])
{
    char c = '\0';
    int num = 0;
    std::string filename,pattern;
    filename= argv[1];
    //deal with the file
    Search search;
    std::string content= search.get_file_contents(filename.c_str());
    //create c_table and occ_table
    search.create_tables(content);
    while (c != EOF)
    {
        c = std::cin.get();
        if (c == EOF)
        {
            break;
        }
        else if (c == '\n')
        {
            //search the patten
             num = search.backward_search(pattern);
             cout << num << endl;
             pattern = "";
    
        }
        else {
            pattern = pattern + c;
        }

    }
    std::cin.clear();






}


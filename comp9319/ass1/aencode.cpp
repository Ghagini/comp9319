// acoding.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include"acode.h"


using namespace std;

int main()
{
   // cout << "please input the string:";
    char c='\0',list[1024] = {'\0'};
    int temp = 0, num_of_char = 0;
    while (c!=EOF)
    {
        c = cin.get();
        if (c == EOF)
        {
            break;
        }
        else if(c=='\n'||c=='\r')
        {
            continue;
        }
        else {
        list[temp] = c;
      //  cout << list[temp];
        temp = temp +1;
        }
  
    }
    cin.clear();


    for (int i = 0; (i < strlen(list)) && (list[i] !=EOF); i++)
    {
        if (list[i] != '\0')
        {
            num_of_char = num_of_char++;
        }
    }
    char* str1 = (char*)calloc(num_of_char, sizeof(char));
    char* str2 = (char*)calloc(num_of_char, sizeof(char));
    strcpy(str1, list);
    strcpy(str2, list);
    sort(str1, str1+num_of_char);
    //cout << str1;

    map<char, int> map;
    std::map<char, int>::iterator iter;
    for (int i = 0; i < strlen(str1); i++) {
        iter = map.find(str1[i]);
        if (iter == map.end()) {
            map.insert(pair<char,int>(str1[i], 1));
        }
        else {
            map[str1[i]] = map[str1[i]] + 1;
        }

    }
    std::map <char, int>::iterator m1_Iter;
    for (m1_Iter = map.begin(); m1_Iter != map.end(); m1_Iter++)
    {
        cout << m1_Iter->first << " " << m1_Iter->second << endl;
    }

    //修改此处数据类型
    std::map<char, Range> level;
    mpfr_t lowlevel,highlevel ,a, b,prob,lowRange,highRange,delta;
    mpfr_init2(lowlevel, 1024);
    mpfr_init2(highlevel, 256);
    mpfr_init2(b, 256);
    mpfr_init2(a, 256);
    mpfr_init2(prob, 256);
    mpfr_init2(lowRange, 256);
    mpfr_init2(highRange, 256);
    mpfr_init2(delta, 256);
    mpfr_set_d(highlevel, 0.0, rnd);
    mpfr_set_d(lowlevel, 0.0, rnd);
    mpfr_set_d(b,strlen(str2), rnd);



    mpfr_exp_t exponent = 0,temex=0;
  

    for (m1_Iter = map.begin(); m1_Iter != map.end(); m1_Iter++)
    {
        mpfr_set_d(a, m1_Iter->second, rnd);
        mpfr_div(prob, a, b, rnd);
        mpfr_set(lowlevel, highlevel, rnd);
        mpfr_add(highlevel, lowlevel, prob, rnd);
        Range range;
        range.setchar(m1_Iter->first);
        range.setLow(lowlevel);
        range.setHigh(highlevel);
        range.setDelta(prob);
        level.insert(std::pair<char, Range>(m1_Iter->first, range));
    }

    mpfr_set_d(lowRange, 0.0, rnd);
    mpfr_set_d(highRange, 1.0, rnd);
    char l[1024];
    for (int i = 0; i < strlen(str2); i++)
    {
        mpfr_sub(delta, highRange, lowRange, rnd);
        mpfr_mul(a, delta, level[str2[i]].getHigh(),rnd);
        mpfr_add(highRange,lowRange,a,rnd);//highRange = lowRange + delta * level[str2[i]].getHigh();
        mpfr_mul(b, delta, level[str2[i]].getLow(), rnd);
        mpfr_add(lowRange, lowRange, b, rnd);//   lowRange = lowRange + delta * level[str2[i]].getLow();
    }
    int k = 0;

    k = strlen(str2) * ceil(log10(map.size()));
    if (map.size() == 1)
    {
        cout << 0 << " " << 1 << endl;
    }
    else
    {
        mpfr_get_str(l, &exponent, 10, k, lowRange, rnd);
        cout << "0." << l;
        mpfr_get_str(l, &exponent, 10, k, highRange, rnd);
        cout << " 0." << l << endl;

    }
    mpfr_clear(lowlevel);
    mpfr_clear(highlevel);
    mpfr_clear(a);
    mpfr_clear(b);
    mpfr_clear(lowRange);
    mpfr_clear(highRange);
    mpfr_clear(prob);
    mpfr_clear(delta);
    mpfr_free_cache();
}

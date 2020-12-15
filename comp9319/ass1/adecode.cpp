#include"acode.h"


using namespace std;
int main()
{
	char c = '\0',ch[1024];
    string str,num,outstr;
    int num_of_line=0,num_of_chara=0;
	std::map<char, int> map;
    std::map<char, int>::iterator iter;
    while (c != EOF)
    {
        c = cin.get();
        if (c == EOF)
        {
            break;
        }
        else if (c == '\n' || c == '\r')
        {
            continue;
        }
        else {
            cin.getline(ch, 1024);
            str = string(ch);
            num = c + str;
            num_of_line = num_of_line++;
            if(ch[0]!=' ')
            {

                do
                {
                    c = cin.get();
                } while (c != EOF);
                    break;
            }
            iter = map.find(c);
            if (iter == map.end()) {
                map.insert(pair<char, int>(c, stoi(str)));
                }
        }

    }
    cin.clear();
    if(map.size()!=(num_of_line-1))
    {
        c = num[0];
        map.erase(map.find(c));
    }


    std::map <char, int>::iterator m1_Iter;


    for (m1_Iter = map.begin(); m1_Iter != map.end(); m1_Iter++)
    {
        num_of_chara = num_of_chara + m1_Iter->second;
    }

    num = strtok((char*)num.c_str(), " ");

    mpfr_t bignum;
    mpfr_init2(bignum, 1024);

    mpfr_set_str(bignum, (char*)num.c_str(),0,MPFR_RNDA);



    std::map<char, Range> level;
    std::map<char, Range>::iterator m2_Iter;
    mpfr_t lowlevel, highlevel, a, b, prob, lowRange, highRange, delta;
    mpfr_init2(lowlevel, 1024);
    mpfr_init2(highlevel, 1024);
    mpfr_init2(b,1024);
    mpfr_init2(a,1024);
    mpfr_init2(prob,1024);

    mpfr_init2(lowRange, 1024);
    mpfr_init2(highRange, 1024);
    mpfr_init2(delta, 1024);

    mpfr_set_d(highlevel, 0.0, rnd);
    mpfr_set_d(lowlevel, 0.0, rnd);
    mpfr_set_d(b, num_of_chara, rnd);


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
    int temp1, temp2;
    //find first symbol
    for (m2_Iter=level.begin(); m2_Iter != level.end();++ m2_Iter) {
        temp1=mpfr_cmp(bignum,(m2_Iter->second).getLow());
        temp2=mpfr_cmp((m2_Iter->second).getHigh(), bignum);
        if (temp1>=0 &&temp2 > 0) {
            mpfr_set(lowRange,(m2_Iter->second).getLow(), rnd);
            mpfr_set(highRange,(m2_Iter->second).getHigh(), rnd);
            outstr+=(m2_Iter->first);
            break;
        }
    }

    //find rest part
    for (int i = 0; i < num_of_chara - 1; ++i) {
        mpfr_sub(delta, highRange, lowRange,rnd);
        mpfr_sub(bignum, bignum, lowRange, MPFR_RNDA);
        mpfr_div(bignum, bignum, delta, MPFR_RNDA);


        for (m2_Iter = level.begin(); m2_Iter != level.end();++ m2_Iter) {

            temp1 = mpfr_cmp(bignum, (m2_Iter->second).getLow());
            temp2 = mpfr_cmp((m2_Iter->second).getHigh(), bignum);
            if (temp1 >= 0 && temp2 > 0) {
                mpfr_set(lowRange, (m2_Iter->second).getLow(),rnd);
                mpfr_set(highRange, (m2_Iter->second).getHigh(), rnd);
                outstr +=(m2_Iter->first);
                break;
            }
        }
    }


    cout << outstr;


}

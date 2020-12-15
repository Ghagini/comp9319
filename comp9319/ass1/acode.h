#pragma once

#include <iostream>
#include <string>
#include<algorithm>
#include<map>
#include <gmp.h>
#include<mpfr.h>
using namespace std;
#define rnd MPFR_RNDN

class Range
{
public:
    Range() {
        mpfr_init2(high, 1024);
        mpfr_init2(low, 1024);
        mpfr_init2(deltaLevel, 1024);
        mpfr_set_d(high, 1.0, rnd);
        mpfr_set_d(low, 0.0, rnd);
        mpfr_set_d(deltaLevel, 1.0, rnd);

    }
    ~Range() {
    }
    char getchar() {
        return this->c;
    }
    mpfr_ptr getLow() {
        return this->low;
    }

    mpfr_ptr getHigh() {
        return this->high;
    }
    mpfr_ptr getdelta() {
        return this->deltaLevel;
    }

    void setchar(char c) {
        this->c = c;
    }

    void setLow(mpfr_t low) {
        mpfr_set(this->low, low, rnd);
    }


    void setHigh(mpfr_t high) {
        mpfr_set(this->high, high,rnd);
    }

    void setDelta(mpfr_t delta) {
        mpfr_set(this->deltaLevel, deltaLevel, rnd);
    }
private:
    char c;
    mpfr_t high, low, deltaLevel;
};


/*        mpfr_clear(this->high);
        mpfr_clear(this->low);
        mpfr_clear(this->deltaLevel);
        mpfr_free_cache();*/

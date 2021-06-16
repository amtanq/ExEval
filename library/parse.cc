#ifndef PARSE_CC
#define PARSE_CC

#include <utility>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <cmath>

char lookahead;
size_t lookcount;
size_t precision;

bool parse();
bool match(char character);
long double fA();
long double fB();
long double fC();
long double fD();
long double parseId();
std::pair<char, long double> fAp();
std::pair<char, long double> fBp();
std::pair<char, long double> fCp();
long double operate(long double (*)(), std::pair<char, long double> (*)());
std::pair<char, long double> direct(const char *, long double (*)(), std::pair<char, long double> (*)());

#endif

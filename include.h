#include <iostream>
#include <curl/curl.h>
#include <vector>

#define ToUnicode(x) L##x

using namespace std;

class NetworkCommuncation
{
    string url;
    string *parametters;
    char *RADIX_itoa(int, char *, int);
    static size_t writefunc(void *, size_t, size_t, std::string *);

public:
    string send(const string &);
    string translateResult(string &);
    string UTF8encode(const wchar_t *);
};

class Translator
{
    string text, langIn, langOut;
    NetworkCommuncation google;

public:
    void setLangIn(const string);
    void setLangOut(const string);
    string getLangIn();
    string getLangOut();
    string translate(const string &);
    string resumeResult(const string &);
};

#include "include.cpp"

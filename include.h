#include <iostream>
#include <curl/curl.h>
#define ToUnicode(x) L##x

using namespace std;

/*
    Usando curl para a comunicação
*/
class NetworkCommuncation
{
    string url;
    string *parametters;
    char *RADIX_itoa(int, char*, int);

public:
    NetworkCommuncation(const string &,string *);
    string send(const string &);
    string translateResult(string &);
    string UTF8encode(const wchar_t *);
};


class Translator{
    string text, langIn, langOut;
    NetworkCommuncation google;
public:
    Translator();
    void setLangIn(const string &);
    void setLangOut(const string &);
    string translate(const string &);
    string resumeResult(const string &);

};




string translator(string text)
{
    Translate trans("auto", "pt-br");
    string s = trans.send(text);
    return trans.translateResult(s);
}
#include "include.cpp"

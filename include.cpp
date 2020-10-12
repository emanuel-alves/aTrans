
#include <iostream>

using namespace std;
static string s;

char * NetworkCommuncation::RADIX_itoa(int value, char *str, int radix)
{
    const static char dig[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int n = 0, neg = 0;
    unsigned int v;
    char *p, *q;
    char c;

    if (radix == 10 && value < 0)
    {
        value = -value;
        neg = 1;
    }

    v = value;
    do
    {
        str[n++] = dig[v % radix];
        v /= radix;
    } while (v);

    if (neg)
        str[n++] = '-';

    str[n] = '\0';

    for (p = str, q = p + (n - 1); p < q; ++p, --q)
        c = *p, *p = *q, *q = c;

    return str;
}

string NetworkCommuncation::UTF8encode(const wchar_t *mytext)
{
    // endian-independant
    char chrarry_HexNumber[10];
    std::string strUTF8encodedString = "";
    wchar_t *newtext;
    int intCharacterBinaryValue;

    for (newtext = (wchar_t *)mytext; *newtext != 0; newtext++)
    {
        intCharacterBinaryValue = (int)*newtext;
        if ((ToUnicode('a') <= intCharacterBinaryValue && intCharacterBinaryValue <= ToUnicode('z')) || (ToUnicode('A') <= intCharacterBinaryValue && intCharacterBinaryValue <= ToUnicode('Z')) || (ToUnicode('0') <= intCharacterBinaryValue && intCharacterBinaryValue <= ToUnicode('9')))
        {
            strUTF8encodedString += (char)intCharacterBinaryValue;
        }
        else
        {

            int intUTFbyte1 = 0;
            int intUTFbyte2 = 0;
            int intUTFbyte3 = 0;
            int intUTFbyte4 = 0;
            int intUTFbyte5 = 0;
            int intUTFbyte6 = 0;

            if (intCharacterBinaryValue < 128)
                intUTFbyte1 = intCharacterBinaryValue;

            if (intCharacterBinaryValue > 127 && intCharacterBinaryValue < 2048)
            {
                intUTFbyte1 = 192 + (intCharacterBinaryValue / 64);
                intUTFbyte2 = 128 + (intCharacterBinaryValue % 64);
            }

            if (intCharacterBinaryValue > 2047 && intCharacterBinaryValue < 65536)
            {
                intUTFbyte1 = 224 + (intCharacterBinaryValue / 4096);
                intUTFbyte2 = 128 + ((intCharacterBinaryValue / 64) % 64);
                intUTFbyte3 = 128 + (intCharacterBinaryValue % 64);
            }

            if (intCharacterBinaryValue > 65535 && intCharacterBinaryValue < 2097152)
            {
                intUTFbyte1 = 240 + (intCharacterBinaryValue / 262144);
                intUTFbyte2 = 128 + ((intCharacterBinaryValue / 4096) % 64);
                intUTFbyte3 = 128 + ((intCharacterBinaryValue / 64) % 64);
                intUTFbyte4 = 128 + (intCharacterBinaryValue % 64);
            }

            if (intCharacterBinaryValue > 2097151 && intCharacterBinaryValue < 67108864)
            {
                intUTFbyte1 = 248 + (intCharacterBinaryValue / 16777216);
                intUTFbyte2 = 128 + ((intCharacterBinaryValue / 262144) % 64);
                intUTFbyte3 = 128 + ((intCharacterBinaryValue / 4096) % 64);
                intUTFbyte4 = 128 + ((intCharacterBinaryValue / 64) % 64);
                intUTFbyte5 = 128 + (intCharacterBinaryValue / 64);
            }

            if (intCharacterBinaryValue > 67108863 && intCharacterBinaryValue <= 2147483647)
            {
                intUTFbyte1 = 252 + (intCharacterBinaryValue / 1073741824);
                intUTFbyte2 = 128 + ((intCharacterBinaryValue / 16777216) % 64);
                intUTFbyte3 = 128 + ((intCharacterBinaryValue / 262144) % 64);
                intUTFbyte4 = 128 + ((intCharacterBinaryValue / 4096) % 64);
                intUTFbyte5 = 128 + ((intCharacterBinaryValue / 64) % 64);
                intUTFbyte6 = 128 + (intCharacterBinaryValue % 64);
            }

            if (intUTFbyte1)
            {
                strUTF8encodedString += "%";
                strUTF8encodedString += RADIX_itoa(intUTFbyte1, chrarry_HexNumber, 16);
            }
            if (intUTFbyte2)
            {
                strUTF8encodedString += "%";
                strUTF8encodedString += RADIX_itoa(intUTFbyte2, chrarry_HexNumber, 16);
            }
            if (intUTFbyte3)
            {
                strUTF8encodedString += "%";
                strUTF8encodedString += RADIX_itoa(intUTFbyte3, chrarry_HexNumber, 16);
            }

            if (intUTFbyte4)
            {
                strUTF8encodedString += "%";
                strUTF8encodedString += RADIX_itoa(intUTFbyte4, chrarry_HexNumber, 16);
            }

            if (intUTFbyte5)
            {
                strUTF8encodedString += "%";
                strUTF8encodedString += RADIX_itoa(intUTFbyte5, chrarry_HexNumber, 16);
            }

            if (intUTFbyte6)
            {
                strUTF8encodedString += "%";
                strUTF8encodedString += RADIX_itoa(intUTFbyte6, chrarry_HexNumber, 16);
            }
        }
    }
    return strUTF8encodedString;
}


size_t NetworkCommuncation::writefunc(void *ptr, size_t size, size_t nmemb, std::string *s)
{
    s->append(static_cast<char *>(ptr), size * nmemb);
    return size * nmemb;
}

string NetworkCommuncation::send(const string &url)
{

    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    s.clear();

    if (curl)
    {

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));

        curl_easy_cleanup(curl);
    }
    return s;
}

string Translator::translate(const string &text)
{
    NetworkCommuncation net;
    string url = "https://translate.googleapis.com/translate_a/single?client=gtx&sl=";
    url += langIn;
    url += "&tl=";
    url += langOut;
    url += "&dt=t&q=";
    wstring name(text.begin(), text.end());
    const wchar_t *szName = name.c_str();
    url += net.UTF8encode(szName);
    return net.send(url);

}

string Translator::resumeResult(const string &text)
{
    string str;
    for (int a = 4; a < text.size(); a++)
    {
        if (text[a] == '\"' && text[a - 1] != '\\')
            break;
        str += text[a];
    }
    return str;
}

void Translator::setLangIn(const string langIn)
{
    this->langIn = langIn;
}
void Translator::setLangOut(const string langOut)
{
    this->langOut = langOut;
}

string Translator::getLangIn()
{
    return langIn;
}
string Translator::getLangOut()
{
    return langOut;
}
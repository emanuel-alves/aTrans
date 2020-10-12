#include "include.h"

const short int mapString(const string & str)
{
    if(str == "exit") return 1;
    if(str == "help") return 2;
    if(str.substr(0, 6) == "langI") return 3;
    if(str.substr(0, 6) == "langO") return 4;
    if(str == "clear") return 5;
    return 0;

}


string command(string str)
{
    switch (mapString(str))
    {
    case 0:
        cout << ">> Comadno não encontrado";
        break;
    case 1: 
        exit(0);
        break;
    case 2:
        cout << ">> HELP";
        break;
    case 3:
        break;
    default:
        break;
    }
}

int main()
{
    string langIn, langOut, text1, text2;
    cout << "Digite \\help para receber ajuda.\n";

    while (true)
    {
        cout << "<< ";
        getline(cin, text1);
        
        if(text1[0] == '\\') command(text1.substr(1));
        else cout << ">> "  << translator(text1);

    }
}

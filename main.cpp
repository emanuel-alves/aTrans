#include "include.h"

Translator trans;

const short int mapString(const string &str)
{
    if (str == "exit")
        return 1;
    if (str == "help")
        return 2;
    if (str.substr(0, 6) == "set li")
        return 3;
    if (str.substr(0, 6) == "set lo")
        return 4;
    if (str == "get lang")
        return 5;
    if (str == "clear")
        return 6;
    return 0;
}

void help(){
    cout << "Lista de ajuda!";
    cout << "\n\\set li\n";
    cout << "\tConfigura o idioma de entrada!";
    cout << "\n\\set lo\n";
    cout << "\tConfigura o idioma de entrada!";
    cout << "\n\\get lang\n";
    cout << "\tExibe os idiomas usados!";
    cout << "\n\\clear\n";
    cout << "\tLimpa a tela";
    cout << "\n\\exit\n";
    cout << "\tSai do programa.\n";
}


string command(string str)
{
    switch (mapString(str))
    {
    case 0:
        cout << ">> Comando não encontrado\n";
        break;
    case 1:
        exit(0);
        break;
    case 2:
        help();
        break;
    case 3:
        trans.setLangIn(str.substr(7));
        break;
    case 4:
        trans.setLangOut(str.substr(7));
        break;
    case 5:
        cout << ">>In: " << trans.getLangIn() << " Out: " << trans.getLangOut() << endl;
    case 6:
        cout << "\x1B[2J\x1B[H";
    default:
        cout << "Comando não encontrado!";
        break;
    }
    return "  ";
}


int main()
{
    string langIn, langOut, text1, text2;
    cout << "Digite \\help para receber ajuda.\n";
    trans.setLangIn("en");
    trans.setLangOut("pt");
    while (true)
    {
        cout << "<< ";
        getline(cin, text1);

        if (text1[0] == '\\')
            command(text1.substr(1));
        else
        {
            text2 = trans.translate(text1);
            cout << ">> " << trans.resumeResult(text2) << endl;
        }
    }
}

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <QFile>
#include <QString>

using namespace std;

QString generate_letters()
{
    srand(time(NULL));
    int ascii;
    QString wynik;
    for (int i=0;i<20;i++)
    {
        ascii = 97 + rand()%26;
        wynik = wynik + (char)ascii;
        cout << (char)ascii<< " ";
    }
    cout<<endl;
    return wynik;
}

vector<QString> get_dictionary()
{
    vector<QString> slownik;
    QFile file("dictionary.txt");
    if (file.open(QIODevice::ReadOnly))
    {
        while(!file.atEnd())
            {
                QString slowo = file.readLine();
                slownik.push_back(slowo);
            }
    }
    else 
        cout<<"Blad danych";
    return slownik;
}

bool check_word(string slowo, string lista){
    int check;
    for (int i=0;i<slowo.size();i++)
    {
        check = 0;
        for (int j=0;j<lista.size();j++)
            if (slowo[i]==lista[j])
                {
                    lista.erase(j,1);
                    check = 1;
                    break;
                }
        if (check == 0)
            return false;
    }
    return true;          
}

bool check_dictionary(string slowo, vector<string> slownik){
    for (int i=0;i<slownik.size();i++)
        if (slownik[i]==slowo)
            return true;
    return false;
}

bool check_base(string slowo, vector<string> baza)
{
    for (int i=0;i<baza.size();i++)
        if (baza[i]==slowo)
            return false;
    return true;
}

string result(string slowo, string lista, vector<string> slownik, vector<string> baza)
{
    string wynik;
    if (!check_word(slowo, lista))
        wynik = "Nie da sie utworzyc podanego slowa z danych liter";
    else if (!check_dictionary(slowo, slownik))
        wynik = "Nie ma takiego slowa";
    else if (!check_base(slowo, baza))
        wynik = "To slowo zostalo juz podane przez Twojego przeciwnika";
    else
        wynik = "Podales prawidlowe slowo, gratulacje!";
    return wynik;
}


//int main()
//{
//    string word, message, letters = "";
//    vector<string> base, dict;
//    int points = 0;
    
//    dict = get_dictionary();
//    letters = generate_letters();
//    cin>>word;

//    message = result(word, letters, dict, base);
//    cout<<message;
//    if(message == "Podales prawidlowe slowo, gratulacje!")
//        {
//            base.push_back(word);
//            points++;
//        }
//    return 0;
//}

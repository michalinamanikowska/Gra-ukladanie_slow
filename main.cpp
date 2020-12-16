#include <iostream>

using namespace std;

bool check_word(string slowo, string lista){
    int check;
    for (int i=0;i<slowo.size();i++)
    {
        check = 0;
        for (int j=0;j<lista.size();j++)
            if (slowo[i]==lista[j])
                {
                    lista.erase(j);
                    check = 1;
                    break;
                }
        if (check == 0)
            return false;
    }
    return true;          
}

int main()
{
    string word, letters;
    letters = "wslkgpaiahcn";
    word = "cat";
    cout << check_word(word,letters);
    return 0;
}
# Gra-ukladanie_slow
KOMPILACJA:
https://www.youtube.com/watch?v=jla3qEnAFx0&ab_channel=PoetaKodu
g++ -o gra.exe main.cpp
./gra.exe

OPIS FUNKCJI:
generate_letters - zwraca liste liter (w formie jednego slowa)
get_dictionary - pobiera z pliku dictionary.txt slowa
check_word - sprawdza czy da sie utworzyc dane slowo z podanych liter
check_dictionary - sprawdza czy dane slowo istnieje w slowniku
check_base - sprawdza czy dane slowo jest juz w bazie, zwraca prawda jesli NIE zostalo wczesniej podane
result - zwraca odpowiedni komunikat do uzytkownika w zaleznosci od podanego slowa

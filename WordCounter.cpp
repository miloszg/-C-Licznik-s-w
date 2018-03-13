//Gustawski Milosz Microsoft Visual Studio 2015

#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <clocale> //------------umozliwia wystepowanie polskich znakow
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

const int MAX_WYRAZOW = 200;	//stala wyrazajaca ilosc maksymalnej liczbie roznych slow

//----------------------------------umozliwienie polskich znakow
void setCharset()
{
	setlocale(LC_ALL, "polish");
}

//---------------------------------wypisanie bledu gdy liczba roznych slow jest za duza
void blad()
{
	cout << "Liczba roznych wyrazow przekracza dopuszczalna ilosc";
	exit(1);
}

//-----------------------------------czyszczenie glownej tablicy w celu
void zerowanie_tablicy(char* wyrazy[MAX_WYRAZOW])
{
	for (int i = 0; i < MAX_WYRAZOW; i++)
	{
		wyrazy[i] = 0;
	}
}

//-----------------------------------wypisywanie 20 rownych slow na podstawie tabeli
void wypisywanie(char* wyrazy[MAX_WYRAZOW], int ilosc_wystapien[MAX_WYRAZOW], int liczba_wyrazow)
{
	cout << "Liczba slow: " << liczba_wyrazow << endl;

	for (int j = 0; j < 20 && wyrazy[j] != 0; j++)
	{
		cout << wyrazy[j] << " " << ilosc_wystapien[j] << endl;
	}
}

//-----------------------------------sprawdzenie czy plik zostal otwarty poprawnie
void sprawdzanie_pliku(fstream &plik)
{
	if (!plik)
	{
		cout << "Plik wejsciowy nie otwarty" << endl;
		exit(1);
	}
}

//------------------------------------porownywanie 2 slow w celu wpisaniu ich w odpowiednie okienko tablicy i wyliczenie ilosci wystapien danego slowa
void porownywanie(char* wyrazy[MAX_WYRAZOW], char* pomocniczy, int ilosc_wystapien[MAX_WYRAZOW], bool wystapil)
{
	int i = 0;
	while (wyrazy[i] != 0)
	{
		if (_stricoll(wyrazy[i], pomocniczy) == 0)
		{
			ilosc_wystapien[i] += 1;
			wystapil = true;
		}
		i++;
		if (i >= 199) blad(); 
	}
	if (!wystapil)
	{
		wyrazy[i] = pomocniczy;
		ilosc_wystapien[i] = 1;
	}
}

//---------------------------------sortowanie wyrazow rosnaco na podstawie ich ilosci wystapien
void sortowanie(char* wyrazy[], int ilosc_wystapien[], int liczba_wyrazow)
{
	bool zmiana = true;
	while (zmiana)
	{
		zmiana = false;
		for (int j = 0; j < liczba_wyrazow - 1 && ilosc_wystapien[j + 1] != 0; j++)
		{
			if (ilosc_wystapien[j] < ilosc_wystapien[j + 1]) {
				swap(ilosc_wystapien[j], ilosc_wystapien[j + 1]);
				char *tmp = wyrazy[j];
				wyrazy[j] = wyrazy[j + 1];
				wyrazy[j + 1] = tmp;
				zmiana = true;
			}
		}
	}
}

int main()
{
	setCharset(); // umozliwienie wystepowania polskich znakow

	int liczba_roznych_slow = 0;
	int liczba_wyrazow = 0;
	string linia;
	int ilosc_wystapien[MAX_WYRAZOW];
	char* wyrazy[MAX_WYRAZOW];
	char znaki[] = " ,.?-"; // znaki oddzielajace 2 slowa
	char* pomocniczy;

	fstream plik("przyklad.txt", ios::in); //notatnik musi byc kodowany w ANSI

	sprawdzanie_pliku(plik);
	zerowanie_tablicy(wyrazy);


	while (!plik.eof())
	{
		getline(plik, linia);

		int n = linia.length();

		for (int i = 0; i < n; i++)
		{
			if (linia[i] == ' ')
				liczba_wyrazow++;
		}

		if (!(linia == "")) liczba_wyrazow++;	// liczenie slow, ktore sa ostatnim slowem w linii, po ktorej nie ma spacji

		char* tablica = new char[linia.size() + 1];
		strcpy(tablica, linia.c_str()); // skopiowanie zawartosci string'a linia do tablicy dynamicznej
		pomocniczy = strtok(tablica, znaki); // funkcja dzieli podanego stringa na pojedyncze slowa, za pomoca rozrozniania znakow specjalnych

		while (pomocniczy != 0)
		{
			bool wystapil = false;
			if (wyrazy[0] == 0) // dla piewszego wyrazu tablicy
			{
				wyrazy[0] = pomocniczy;
				ilosc_wystapien[0] = 1;
			}
			else
			{
				porownywanie(wyrazy, pomocniczy, ilosc_wystapien, wystapil);
				liczba_roznych_slow++;
			}
			pomocniczy = strtok(NULL, znaki);
		}
	}
	sortowanie(wyrazy, ilosc_wystapien, liczba_wyrazow);
	wypisywanie(wyrazy, ilosc_wystapien, liczba_wyrazow);

	plik.close();

	return 0;
}


#include <iostream>
#include <math.h>
#include <list>
#include <stack>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;
double** mapaPomocnicza;
class AStar
{

public:

	int wiersze;
	int kolumny;
	int ruch;
	int rodzic_wiersz;
	int rodzic_kolumna;
	double wartosc;
	double pozycja;

	AStar(int wiersz, int kolumna, int krok,double**& mapa) {

		wiersze = wiersz;
		kolumny = kolumna;
		ruch = krok;
		wartosc = mapa[wiersz][kolumna];
		pozycja = (krok + sqrt(pow((kolumna-1), 2) + pow((wiersz-20), 2)));
	}
	AStar() {
		wiersze = 0;
		kolumny = 20;
		wartosc = 0;
		pozycja = INT_MAX;
	}
};

list<AStar> Otwarta;
list<AStar> Zamknieta;
stack<string> droga;

AStar minimalna() {
	AStar minimalna;
	minimalna.pozycja = INT_MAX;

	for (AStar sx : Otwarta) {
		bool spr = true;
		for (AStar x : Zamknieta) {

			if (x.wiersze == sx.wiersze && x.kolumny == sx.kolumny)
				spr= false ;
		}

		if (spr == true && minimalna.pozycja >= sx.pozycja) minimalna = sx;

	}
	return minimalna;
}

void generuj(int zmwiersz, int zmkolumna,int zmkrok, double**& mapa) {

	AStar gora;
	AStar dol;
	AStar lewo;
	AStar prawo;

	if (zmwiersz - 1 != 0) {
		if (mapa[zmwiersz - 1][zmkolumna] != 5) {
			gora = AStar(zmwiersz - 1, zmkolumna,zmkrok+1, mapa);
			gora.rodzic_wiersz = zmwiersz;
			gora.rodzic_kolumna = zmkolumna;
			bool spr = true;
			for (AStar idx : Otwarta) {

				if (gora.wiersze == idx.wiersze && gora.kolumny == idx.kolumny)
					spr = false;
			}
			if (spr)Otwarta.push_back(gora);
		};
	}

	if (zmwiersz + 1 != 21) {
		if (mapa[zmwiersz - 1][zmkolumna] != 5) {
			dol = AStar(zmwiersz + 1, zmkolumna,zmkrok+1 ,mapa);
			dol.rodzic_wiersz = zmwiersz;
			dol.rodzic_kolumna = zmkolumna;

			bool spr = true;
			for (AStar idx : Otwarta) {

				if (dol.wiersze == idx.wiersze && dol.kolumny == idx.kolumny)
					spr = false;
			}
			if(spr)Otwarta.push_back(dol);
		}
	}

	if (zmkolumna - 1 != 0) {
		if (mapa[zmwiersz][zmkolumna - 1] != 5){
			lewo = AStar(zmwiersz, zmkolumna - 1,zmkrok+1, mapa);
			lewo.rodzic_wiersz = zmwiersz;
			lewo.rodzic_kolumna = zmkolumna;
			bool spr = true;
			for (AStar idx : Otwarta) {

				if (lewo.wiersze == idx.wiersze && lewo.kolumny == idx.kolumny)
					spr = false;
			}
			if (spr)Otwarta.push_back(lewo);
		};
	}

	if (zmkolumna + 1 != 21) {
		if (mapa[zmwiersz][zmkolumna + 1] != 5) {
			prawo = AStar(zmwiersz, zmkolumna + 1,zmkrok+1, mapa);
			prawo.rodzic_wiersz = zmwiersz;
			prawo.rodzic_kolumna = zmkolumna;
			bool spr = true;
			for (AStar idx : Otwarta) {

				if (prawo.wiersze == idx.wiersze && prawo.kolumny == idx.kolumny)
					spr = false;
			}
			if (spr)Otwarta.push_back(prawo);
		}
	}
}

void wybierz(AStar end) {
		string sciezka =to_string(end.wiersze)+" "+ to_string(end.kolumny);
		droga.push(sciezka);

		mapaPomocnicza[end.wiersze][end.kolumny] = 3;

		if (end.rodzic_wiersz == 0 && end.rodzic_kolumna == 0) return;
		for (AStar x : Zamknieta) {
			if (end.rodzic_wiersz == x.wiersze && end.rodzic_kolumna == x.kolumny) wybierz(x);
		}
}

int main()
{
    cout << "Hello AStar!" << endl;
	// kod z pliku wczytywanie.cpp
	 cout << "Wczytywanie danych z pliku\n";

	 string nazwap = "grid.txt";
	 int wym2 = 20; //kolumna
	 int wym1 = 20; //wiersz

	 int rows = wym2 + 1;
	 double** mapa;
	 mapa = new double* [rows];
	 while (rows--) mapa[rows] = new double[wym1 + 1];

	 std::ifstream plik(nazwap.c_str());

	 for (int i = 1; i < wym2 + 1; i++)
	 {
		 for (int j = 1; j < wym1 + 1; j++)
		 {
			 plik >> mapa[i][j];
		 }
	 }
	 plik.close();

	 	 	 	 //WYSWIETLANIE MAPY

	 cout << "\nWygenerowana mapa wyglada tak:\n\n";
	 for (int i = 1; i < wym2 + 1; i++)
	 {
		 for (int j = 1; j < wym1 + 1; j++)
		 {
			 cout << " " << mapa[i][j];
		 }cout << "\n";
	 }

    mapaPomocnicza = mapa;

	 AStar Start(20, 1, 0, mapa);
	 Start.rodzic_wiersz = 0;
	 Start.rodzic_kolumna = 0;
	 Otwarta.push_front(Start);

	 do {

		 AStar aktualny = minimalna();
		 Zamknieta.push_back(aktualny);
		 if (aktualny.wiersze == 1 && aktualny.kolumny == 20) break;
		 generuj(aktualny.wiersze, aktualny.kolumny,aktualny.ruch, mapa);

	 } while (!Otwarta.empty());
	 Otwarta.clear();
	 AStar koniec = Zamknieta.back();
	 wybierz(koniec);

	 	 	 //WYSWIETLANIE MAPY POMOCNICZEJ Z WYNIKIEM
    if ((mapaPomocnicza[1][19] == 3 || mapaPomocnicza[2][20] == 3) && mapaPomocnicza[1][20] != 5){
        mapaPomocnicza[1][20] = 3;
    }
    else cout << "\nBrak mozliwosci dotarcia do mety\n\n";
    if (mapaPomocnicza[1][20] == 3){
	 cout << "\nWygenerowana droga wyglada tak:\n\n";
	 for (int i = 1; i < wym2 + 1; i++)
	 {
		 for (int j = 1; j < wym1 + 1; j++)
		 {
			 cout << " " << mapaPomocnicza[i][j];
		 }cout << "\n";
	 }
    }
	 for (int i = 0; i < wym2 + 1; i++)
	 {
		 delete[] mapa[i];
	 }
	 delete[] mapa;

	 cout << "\n\nKoniec programu - nacisnij ENTER";
	 getchar();

	 return 0;
}

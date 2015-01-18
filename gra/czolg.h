#pragma once
#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>

#include "pocisk.h"
#include "mina.h"
#include "zagrodzenie.h"

extern const int WIDTH;
extern const int HEIGHT;
extern const int ROZMIAR;
extern const int LICZBA_POCISKOW;
extern const int LICZBA_ZAGRODZEN;

class przeciwnik; // deklaracja zapowiadajaca
class mody; // deklaracja zapowiadajaca

enum KEYS{UP, DOWN, LEFT, RIGHT}; 
extern bool keys[];

class czolg
{
	static const short int MAX_LIVES = 6; 
	static const short int SPEED = 1;
protected:
	int x;
	int y;
	short int lives;
	bool *kierunek;
	short int ostKierunek;
	clock_t timerPociskow;

public:
	czolg(void);
	~czolg(void);
 
	pocisk *pociski;
	mina mina;

	void Rysuj(void);
	void RysujZycie(const short int max); 
	
	void PrzesunWGore(void);
	void PrzesunWDol(void);
	void PrzesunWLewo(void);
	void PrzesunWPrawo(void);

	void Wystrzel(void);

	void Sterowanie(const zagrodzenie *zagrodzenia);

	static void ZdefObrazek();
	static void ZniszczObrazek();

	int PozycjaX(){return x;}
	int PozycjaY(){return y;}
	int Zycie(){return lives;}
	void OstatniKieKierunek(int kierunek){ostKierunek = kierunek;}

	friend void kolidowanieCzolgow(czolg &mojCzolg, przeciwnik *przeciwniki);
	friend void kolidowaniePociskow(czolg &mojCzolg, przeciwnik *przeciwniki, const zagrodzenie *zagrodzenia);
	friend void kolidowanieDodatkow(czolg &mojCzolg, przeciwnik *przeciwniki, const mody *zycie);
};


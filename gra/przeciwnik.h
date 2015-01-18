#pragma once
#include "czolg.h"

extern const int LICZBA_PRZECIWNIKOW;
extern int LEVEL;
extern const int MAX_LEVEL;

extern int SCORE;

class przeciwnik : public czolg
{
	static const short int MAX_LIVES = 3;
	short int miejsce;
public:
	przeciwnik(void);
	~przeciwnik(void);
 
	
	void Rysuj(void);
	void OdswiezPrzeciwnika(czolg &mojCzolg, przeciwnik *przeciwniki);
	void Inteligencja(const zagrodzenie *zagrodzenia, int mojCzolg_x, int mojCzolg_y);
	static void ZdefObrazek();
	static void ZniszczObrazek();
};
#pragma once
#include <allegro5\allegro.h>

class czolg; // deklaracja zapowiadajaca
class przeciwnik; // deklaracja zapowiadajaca

extern const int ROZMIAR;
extern const int HEIGHT;
extern const int WIDTH;
extern const int LICZBA_DODATKOWEGO_ZYCIA;
extern int **PoleGry;

class mody
{
	mutable int live;
	int x;
	int y;
public:
	mody(void);
	~mody(void);

	void Rysuj(void) const;

	static void ZdefObrazek();
	static void ZniszczObrazek();

	friend void kolidowanieDodatkow(czolg &mojCzolg, przeciwnik *przeciwniki, const mody *zycie);
};


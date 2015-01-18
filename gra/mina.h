#pragma once
#include <allegro5\allegro.h>

#include "eksplozja.h"

extern const int ROZMIAR;

class czolg; // deklaracja zapowiadajaca
class przeciwnik; // deklaracja zapowiadajaca
class mody; // deklaracja zapowiadajaca


class mina
{
	int x;
	int y;
	int live;
public:
	mina(void);
	~mina(void);

	eksplozja Boom;
	bool ekspEnd;

	void Ustaw(int poz_x, int poz_y);
	void Rysuj();

	static void ZdefObrazek();
	static void ZniszczObrazek();

	friend void kolidowanieDodatkow(czolg &mojCzolg, przeciwnik *przeciwniki,const mody *zycie);
};


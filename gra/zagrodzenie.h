#pragma once
#include <allegro5\allegro.h>

extern const int ROZMIAR;
extern const int HEIGHT;
extern const int WIDTH;
extern int **PoleGry;

enum {DRZEWO = 1, CEGLA, BETON};

class zagrodzenie
{
public:
	zagrodzenie(void);
	~zagrodzenie(void);

	int x;
	int y;
	mutable short int typ;
	mutable short int lives;

	void Rysuj() const;
	static void ZdefObrazki();
	static void ZniszczObrazki();

};

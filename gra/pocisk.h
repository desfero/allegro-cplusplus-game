#pragma once
#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include "eksplozja.h"

extern const int WIDTH;
extern const int HEIGHT;
extern const int ROZMIAR_POCISKOW;

class pocisk
{
	static const int SPEED = 4;
public:
	pocisk(void);
	~pocisk(void);

	int x;
	int y;
	bool live;
	int kierunek;
	bool ekspEnd;

	eksplozja Boom;

	void Rysuj();
	void Przerysuj();
};
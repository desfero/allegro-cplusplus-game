#pragma once
#include <allegro5\allegro.h>
class eksplozja
{
	static const short int MAX_FRAME = 10;
	static const short int FRAME_DELAY = 4;
	static const short int FRAME_WIDTH = 81;
	static const short int FRAME_HEIGHT = 65;

	int x;
	int y;
	bool live;
	int curFrame;
	int frameCount;
public:
	eksplozja(void);
	~eksplozja(void);

	void Rysuj(void);
	void Start(int poz_x, int poz_y);
	void Przerysuj(bool &ekspEnd);

	static void ZdefObrazek();
	static void ZniszczObrazek();
};


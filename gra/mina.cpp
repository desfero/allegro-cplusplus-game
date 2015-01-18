#include "mina.h"
ALLEGRO_BITMAP *minaImg = NULL;

mina::mina(void)
{
	live = false;
	ekspEnd = true;
}

mina::~mina(void){}

void mina::Ustaw(int poz_x, int poz_y)
{
	if(!live && ekspEnd)
	{
		x = poz_x + ROZMIAR/2;
		y = poz_y + ROZMIAR/2;
		live = true;
		ekspEnd = false;
	}
}

void mina::Rysuj()
{
	if(live)
	{
		al_draw_scaled_bitmap(minaImg, 0, 0, 50, 50, x - 10, y - 10, 20, 20, 0);
	}
}

void mina::ZdefObrazek()
{
	minaImg = al_load_bitmap("mine.png");
}

void mina::ZniszczObrazek()
{
	al_destroy_bitmap(minaImg);
}
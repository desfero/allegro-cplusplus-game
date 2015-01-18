#include "mody.h"
ALLEGRO_BITMAP *zycie = NULL;

mody::mody(void)
{
	x = rand() % (WIDTH/ROZMIAR);
	y = rand() % (HEIGHT/ROZMIAR);

	x = x * ROZMIAR + (ROZMIAR/2); 
	y = y * ROZMIAR + (ROZMIAR/2);

	live = true;
}

mody::~mody(void){}

void mody::Rysuj(void) const
{
	if(live)
	{
		al_draw_scaled_bitmap(zycie, 0, 0, 48, 48, x - 10, y - 10, 20, 20, 0);
	}
}

void mody::ZdefObrazek()
{
		zycie = al_load_bitmap("zycie.png");
}

void mody::ZniszczObrazek()
{
	al_destroy_bitmap(zycie);
}
#include "eksplozja.h"

ALLEGRO_BITMAP *eksImage = NULL;

eksplozja::eksplozja(void)
{
	live = false;
	curFrame = 0;
	frameCount = 0;
}

eksplozja::~eksplozja(void){}

void eksplozja::Rysuj(void)
{
	if(live)
	{
		int fx = curFrame * FRAME_WIDTH;
		int fy = 0;
	
		al_draw_bitmap_region(eksImage, fx, fy, FRAME_WIDTH, FRAME_HEIGHT, x - FRAME_WIDTH / 2, y - FRAME_HEIGHT / 2, 0);
	}
}

void eksplozja::Start(int poz_x, int poz_y)
{
	if(!live)
	{
		x = poz_x;
		y = poz_y;
		live = true;
	}
}

void eksplozja::Przerysuj(bool &ekspEnd)
{
	if(live)
	{
		if(++frameCount >= FRAME_DELAY)
		{
			++curFrame;
			if(curFrame >= MAX_FRAME)
			{
				curFrame = 0;
				live = false;
				ekspEnd = true;

			}
			frameCount = 0;
		}
	}
	else ekspEnd = true; // dodaje to, bo inaczej jest zle z kolidowaniem pocisk z pociskem, bo start wywoluje tylko dla jednego z pociskow
}

void eksplozja::ZdefObrazek()
{
		eksImage = al_load_bitmap("eksplozja.png");
}

void eksplozja::ZniszczObrazek()
{
	al_destroy_bitmap(eksImage);
}
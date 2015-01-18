#include "zagrodzenie.h"

ALLEGRO_BITMAP *drzewo = NULL;
ALLEGRO_BITMAP *drzewo1 = NULL;
ALLEGRO_BITMAP *ceglaMax = NULL;
ALLEGRO_BITMAP *ceglaMid = NULL;
ALLEGRO_BITMAP *ceglaMin = NULL;
ALLEGRO_BITMAP *beton = NULL;
ALLEGRO_BITMAP *beton1 = NULL;
ALLEGRO_BITMAP *beton2 = NULL;
ALLEGRO_BITMAP *beton3 = NULL;
ALLEGRO_BITMAP *beton4 = NULL;
ALLEGRO_BITMAP *beton5 = NULL;

zagrodzenie::zagrodzenie()
{
	switch(typ = rand() % 3 + 1)
	{
		case DRZEWO:
			lives = 2;
			break;
		case CEGLA:
			lives = 3;
			break;
		case BETON:
			lives = 6;
			break;
	}
	
	while(1) // wybieramy losowo polozenie zagrodzenia i sprawdzamy czy miejsce nie jest juz zajete
	{
		x = rand() % (WIDTH/ROZMIAR);
		y = rand() % (HEIGHT/ROZMIAR);
		if(PoleGry[x][y] == -1)
		{
			PoleGry[x][y] = typ;
			break;
		}
	}
	
	x *= ROZMIAR; 
	y *= ROZMIAR;
}

zagrodzenie::~zagrodzenie(void){}

void zagrodzenie::Rysuj() const
{
	if(lives)
	{
		if(typ == DRZEWO)
		{
			switch(lives)
			{
			case 2:
				al_draw_scaled_bitmap(drzewo, 0, 0, 100, 100, x, y, ROZMIAR, ROZMIAR, 0);
				break;
			case 1:
				al_draw_scaled_bitmap(drzewo1, 0, 0, 100, 100, x, y, ROZMIAR, ROZMIAR, 0);
				break;
			}
		}
		else if(typ == CEGLA)
		{
			switch(lives)
			{
			case 3:
				al_draw_scaled_bitmap(ceglaMax, 0, 0, 100, 100, x, y, ROZMIAR, ROZMIAR, 0);
				break;
			case 2:
				al_draw_scaled_bitmap(ceglaMid, 0, 0, 100, 100, x, y, ROZMIAR, ROZMIAR, 0);
				break;
			case 1:
				al_draw_scaled_bitmap(ceglaMin, 0, 0, 100, 100, x, y, ROZMIAR, ROZMIAR, 0);
				break;
			}
		}
		else if(typ == BETON)
		{
			switch (lives)
			{
			case 6:
				al_draw_scaled_bitmap(beton, 0, 0, 100, 100, x, y, ROZMIAR, ROZMIAR, 0);
				break;
			case 5:
				al_draw_scaled_bitmap(beton1, 0, 0, 100, 100, x, y, ROZMIAR, ROZMIAR, 0);
				break;
			case 4:
				al_draw_scaled_bitmap(beton2, 0, 0, 100, 100, x, y, ROZMIAR, ROZMIAR, 0);
				break;
			case 3:
				al_draw_scaled_bitmap(beton3, 0, 0, 100, 100, x, y, ROZMIAR, ROZMIAR, 0);
				break;
			case 2:
				al_draw_scaled_bitmap(beton4, 0, 0, 100, 100, x, y, ROZMIAR, ROZMIAR, 0);
				break;
			case 1:
				al_draw_scaled_bitmap(beton5, 0, 0, 100, 100, x, y, ROZMIAR, ROZMIAR, 0);
				break;
			}
		}
	}
}

void zagrodzenie::ZdefObrazki()
{
	drzewo = al_load_bitmap("drzewo.jpg");
	drzewo1 = al_load_bitmap("drzewo1.jpg");

	ceglaMax = al_load_bitmap("cegla_max.jpg");
	ceglaMid = al_load_bitmap("cegla_mid.jpg");
	ceglaMin = al_load_bitmap("cegla_min.jpg");

	beton = al_load_bitmap("beton.jpg");
	beton1 = al_load_bitmap("beton1.jpg");
	beton2 = al_load_bitmap("beton2.jpg");
	beton3 = al_load_bitmap("beton3.jpg");
	beton4 = al_load_bitmap("beton4.jpg");
	beton5 = al_load_bitmap("beton5.jpg");

}

void zagrodzenie::ZniszczObrazki()
{
	al_destroy_bitmap(drzewo);
	al_destroy_bitmap(drzewo1);


	al_destroy_bitmap(ceglaMax);
	al_destroy_bitmap(ceglaMid);
	al_destroy_bitmap(ceglaMin);

	al_destroy_bitmap(beton);
	al_destroy_bitmap(beton1);
	al_destroy_bitmap(beton2);
	al_destroy_bitmap(beton3);
	al_destroy_bitmap(beton4);
	al_destroy_bitmap(beton5);
}
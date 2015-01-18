#include "przeciwnik.h"

ALLEGRO_BITMAP *czolgPrzeciwnika = NULL;

przeciwnik::przeciwnik(void)
{
	static int p = 0;

	pociski = new pocisk[LICZBA_POCISKOW];
	kierunek = new bool[4];
	
	miejsce = p++;

	if(miejsce == 0)
	{
		x = 0;
		y = 0;
	}
	else if(miejsce == 1)
	{
		x = 0;
		y = HEIGHT - ROZMIAR;
	}
	else if(miejsce == 2)
	{
		x = WIDTH - ROZMIAR;
		y = 0;
	}
	else if(miejsce == 3)
	{
		x = WIDTH - ROZMIAR;
		y = HEIGHT - ROZMIAR;

		p = 0; // zerujemy licznik miejsca
	}

	lives = MAX_LIVES;
	ostKierunek = rand() % 4;
	timerPociskow = clock();
}

przeciwnik::~przeciwnik(void){}

void przeciwnik::Rysuj(void)
{
	switch (ostKierunek)
	{
		case UP:
			al_draw_scaled_rotated_bitmap(czolgPrzeciwnika, 0, 100, x, y, ROZMIAR/100.0, ROZMIAR/100.0, 90 * 3.14159/180, 0);
			break;
		case DOWN:
			al_draw_scaled_rotated_bitmap(czolgPrzeciwnika, 100, 0, x, y, ROZMIAR/100.0, ROZMIAR/100.0, -90 * 3.14159/180, 0);
			break;
		case LEFT:
			al_draw_scaled_bitmap(czolgPrzeciwnika, 0, 0, 100, 100, x, y, ROZMIAR, ROZMIAR, 0);
			break;
		case RIGHT:
			al_draw_scaled_rotated_bitmap(czolgPrzeciwnika, 100, 100, x, y, ROZMIAR/100.0, ROZMIAR/100.0, 180 * 3.14159/180, 0);
			break;
	}
	RysujZycie(MAX_LIVES);	
}

void przeciwnik::OdswiezPrzeciwnika(czolg &mojCzolg, przeciwnik *przeciwniki)
{
	if(lives <= 0)
	{
		while(1) 
		{
			x = rand() % (WIDTH/ROZMIAR);
			y = rand() % (HEIGHT/ROZMIAR);
			if(PoleGry[x][y] <= 0)
			{
				x *= ROZMIAR;
				y *= ROZMIAR;

				if(!(((abs(mojCzolg.PozycjaX() - x)) <= ROZMIAR) && (abs(mojCzolg.PozycjaY() - y) <= ROZMIAR)))
				{
					for(int i = 0; i < LICZBA_PRZECIWNIKOW; ++i)
					{
						if(i != miejsce)
						{
							if(!(((abs(przeciwniki[i].x - x)) <= ROZMIAR) && (abs(przeciwniki[i].y - y) <= ROZMIAR)))
							{
								++SCORE;
								goto przerwij;
							}
						}
					}
				}
			}
		}
		przerwij:

		lives = MAX_LIVES;
		ostKierunek = rand() % 4;
	}
}

void przeciwnik::Inteligencja(const zagrodzenie *zagrodzenia, int mojCzolg_x, int mojCzolg_y)
{
	/* Sterowanie przemieszczeniem przeciwnikow */
	bool przesun[4] = {false, false, false, false};
	przesun[ostKierunek] = true;
	int kierunek_r;

	Sterowanie(zagrodzenia);
	
	if(!kierunek[ostKierunek] || rand() % 200 == 0)
	{
		if((kierunek_r = rand() % 4) != ostKierunek && kierunek[kierunek_r])
		{
			przesun[kierunek_r] = true;
		}
		przesun[ostKierunek] = false;
	}

	if(przesun[UP])
	{
		PrzesunWGore();
	}
	else if(przesun[DOWN])
	{
		PrzesunWDol();
	}
	else if(przesun[LEFT])
	{
		PrzesunWLewo();
	}
	else if(przesun[RIGHT])
	{
		PrzesunWPrawo();
	}

	// Strzelanie w zagrodzenia, gdy liczba mozliwych drog jest mniejsza od 1
	int k = 0;
	for(int i = 0; i < sizeof(kierunek); ++i)
	{
		if(kierunek[i] == false)
		{
			++k;
		}
	}
	if(k >= 3 && rand() % 4 == 0)
	{
		ostKierunek = rand() % k;
		Wystrzel();
	}
	////////////////////////////////////////////////////////////////////////
	// Ustawianie min
	if(rand() % 2000 == 0)
	{
		mina.Ustaw(x, y);
	}
	///////////////////////////////////////////////////////////////////////

	/* Kierowanie pociskami przeciwnikow */
	int tmp_x = x + ROZMIAR/2;
	int tmp_y = y + ROZMIAR/2;

	if(LEVEL <= 2 ? rand() % 100 == 0 : LEVEL <= 4 ? rand() % 80 == 0 : rand() % 60 == 0)
	{
		if(tmp_x >= mojCzolg_x &&
		   tmp_x <= mojCzolg_x + ROZMIAR &&
		   y > mojCzolg_y)
		{
			ostKierunek = UP;
			Wystrzel();
		}
		if(tmp_x >= mojCzolg_x &&
		   tmp_x <= mojCzolg_x + ROZMIAR &&
		   y < mojCzolg_y)
		{
			ostKierunek = DOWN;
			Wystrzel();
		}
		if(tmp_y >= mojCzolg_y &&
		   tmp_y <= mojCzolg_y + ROZMIAR &&
		   x > mojCzolg_x)
		{
			ostKierunek = LEFT;
			Wystrzel();
		}
		if(tmp_y >= mojCzolg_y &&
		   tmp_y <= mojCzolg_y + ROZMIAR &&
		   x < mojCzolg_x)
		{
			ostKierunek = RIGHT;
			Wystrzel();
		}
	}

	/* ------------------------------- */
	for(int i = 0; i < sizeof(kierunek); ++i)
	{
		kierunek[i] = true;
	}
}

void przeciwnik::ZdefObrazek()
{
	czolgPrzeciwnika = al_load_bitmap("tank2.png");
}

void przeciwnik::ZniszczObrazek()
{
	al_destroy_bitmap(czolgPrzeciwnika);
}


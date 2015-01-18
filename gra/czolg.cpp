#include "czolg.h"

ALLEGRO_BITMAP *image = NULL;

czolg::czolg(void)
{
	pociski = new pocisk[LICZBA_POCISKOW];
	kierunek = keys;
	
	x = (WIDTH/ROZMIAR)/2 * ROZMIAR;
	y = (HEIGHT/ROZMIAR)/2 * ROZMIAR;
	lives = MAX_LIVES;
	ostKierunek = UP;

	clock_t timerPociskow = clock();
}

czolg::~czolg(void){}

void czolg::Rysuj(void)
{
	if(lives >= 1)
	{
		switch (ostKierunek)
		{
			case UP:
				al_draw_scaled_rotated_bitmap(image, 0, 100, x, y, ROZMIAR/100.0, ROZMIAR/100.0, 90 * 3.14159/180, 0);
				break;
			case DOWN:
				al_draw_scaled_rotated_bitmap(image, 100, 0, x, y, ROZMIAR/100.0, ROZMIAR/100.0, -90 * 3.14159/180, 0);
				break;
			case LEFT:
				al_draw_scaled_bitmap(image, 0, 0, 100, 100, x, y, ROZMIAR, ROZMIAR, 0);
				break;
			case RIGHT:
				al_draw_scaled_rotated_bitmap(image, 100, 100, x, y, ROZMIAR/100.0, ROZMIAR/100.0, 180 * 3.14159/180, 0);
				break;
		}
		RysujZycie(MAX_LIVES);	
	}
}

void czolg::RysujZycie(const short int max)
{
	int tmp_x = x;
	int tmp_y = y;
	static const int ODSTEP = 15; // odstep od krajow czolga

	if(ostKierunek == UP)
	{
		tmp_x += ODSTEP;
		tmp_y += (ROZMIAR - ODSTEP);
	}
	if(ostKierunek == DOWN)
	{
		tmp_x += (ROZMIAR - ODSTEP);
		tmp_y += ODSTEP;
	}
	if(ostKierunek == RIGHT)
	{
		tmp_x += ODSTEP;
		tmp_y += ODSTEP;
	}
	if(ostKierunek == LEFT)
	{
		tmp_x += (ROZMIAR - ODSTEP);
		tmp_y += (ROZMIAR - ODSTEP);
	}


	double z = max/3;
	if(lives <= 1 * z)
	{
		al_draw_filled_circle(tmp_x, tmp_y, 3, al_map_rgb(255,0, 0));
	}
	else if(lives <= 2 * z)
	{
		al_draw_filled_circle(tmp_x, tmp_y, 3, al_map_rgb(255,192, 0));
	}
	else if(lives <= 3 * z)
	{
		al_draw_filled_circle(tmp_x, tmp_y, 3, al_map_rgb(124,252, 0));
	}
}

void czolg::Wystrzel(void)
{
	for(int i = 0; i < LICZBA_POCISKOW; ++i)
	{
		if(!pociski[i].live && clock() - timerPociskow >= 150 && pociski[i].ekspEnd)
		{
			timerPociskow = clock();
			pociski[i].kierunek = ostKierunek;
			if(pociski[i].kierunek == UP)
			{
				pociski[i].x = x + ROZMIAR/2;
				pociski[i].y = y;
			}
			if(pociski[i].kierunek == DOWN)
			{
				pociski[i].x = x + ROZMIAR/2;
				pociski[i].y = y + ROZMIAR;
			}
			if(pociski[i].kierunek == LEFT)
			{
				pociski[i].x = x;
				pociski[i].y = y + ROZMIAR/2;
			}
			if(pociski[i].kierunek == RIGHT)
			{
				pociski[i].x = x + ROZMIAR;
				pociski[i].y = y + ROZMIAR/2;
			}
			pociski[i].live = true;
			pociski[i].ekspEnd = false;
			return;
		}
	}
}

void czolg::PrzesunWGore()
{
	ostKierunek = UP;
	y -= SPEED;
}

void czolg::PrzesunWDol()
{
	ostKierunek = DOWN;
	y += SPEED;
}

void czolg::PrzesunWLewo()
{
	ostKierunek = LEFT;
	x -= SPEED;
}

void czolg::PrzesunWPrawo()
{
	ostKierunek = RIGHT;
	x += SPEED;
}

void czolg::Sterowanie(const zagrodzenie *zagrodzenia)
{
	/* Sterowanie dla mojego czalga */
	int tmp; // zmienna pomocnicza, ktora przechowuje wspolzedne przed zmiana
	static short int kalibracja = 10; // do ilu piksuleki poprawiac kierunek
	if(ostKierunek == UP || ostKierunek == DOWN)
	{
		tmp = x; 
		if((x % ROZMIAR) > (ROZMIAR - kalibracja))
		{
			x = x + (ROZMIAR - (x % ROZMIAR));
		}
		else if((x % ROZMIAR) < kalibracja)
		{
			x = x - (x % ROZMIAR);
			
		}
	}
	else if(ostKierunek == LEFT || ostKierunek == RIGHT)
	{
		tmp = y; // zmienna pomocnicza, ktora przechowuje wspolzedne przed zmiana
		if((y % ROZMIAR) > (ROZMIAR - kalibracja))
		{
			y = y + (ROZMIAR - (y % ROZMIAR));
		}
		else if((y % ROZMIAR) < kalibracja)
		{
			y = y - (y % ROZMIAR);
		}
	}
	// kod ponizej sprawdza czy w kierunku jazdy nie ma przeszkody, jesli jest, to nic nie robimy
	/* Kolidowanie */
	for(int i = 0; i < LICZBA_ZAGRODZEN; ++i)
	{
		if(zagrodzenia[i].typ > 0)
		{
			if((x + ROZMIAR > zagrodzenia[i].x &&
			   x < zagrodzenia[i].x + ROZMIAR &&
			   y > zagrodzenia[i].y && 
			   y == zagrodzenia[i].y + ROZMIAR) ||
			   y <= 0)
			{
				kierunek[UP] = false;
			}
			if((x > zagrodzenia[i].x - ROZMIAR &&
			   x - ROZMIAR < zagrodzenia[i].x &&
			   y == zagrodzenia[i].y - ROZMIAR && 
			   y < zagrodzenia[i].y) ||
			   y >= HEIGHT-ROZMIAR)
			{
				kierunek[DOWN] = false;
			}
			if((x > zagrodzenia[i].x &&
			   x == zagrodzenia[i].x + ROZMIAR &&
			   y + ROZMIAR > zagrodzenia[i].y && 
			   y < zagrodzenia[i].y + ROZMIAR) ||
			   x <= 0)
			{
				kierunek[LEFT] = false;
			}
			if((x == zagrodzenia[i].x - ROZMIAR &&
			   x < zagrodzenia[i].x &&
			   y > zagrodzenia[i].y - ROZMIAR && 
			   y - ROZMIAR < zagrodzenia[i].y) ||
			   x >= WIDTH - ROZMIAR) 
			{
				kierunek[RIGHT] = false;
			}
		} 
	}
	/* -------- */
	if(!(kierunek[ostKierunek])) 
	{
		switch (ostKierunek)
		{
			case UP:
			case DOWN:
				x = tmp; // w kierunku jest zagrodzenie, to wracamy sie do wspolzednych ktore byly przed zmiana
				break;
			case LEFT:
			case RIGHT:
				y = tmp; // w kierunku jest zagrodzenie, to wracamy sie do wspolzednych ktore byly przed zmiana
				break;
		}
	}
	/* ----------------------------------- */
}

void czolg::ZdefObrazek()
{
		image = al_load_bitmap("tank1.png");
}

void czolg::ZniszczObrazek()
{
	al_destroy_bitmap(image);
}

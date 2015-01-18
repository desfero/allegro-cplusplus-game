#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_image.h>

#include "zagrodzenie.h"
#include "mody.h"
#include "przeciwnik.h" // przez to dolaczam jeszcze czolg.h, pocisk.h, eksplozja.h, mina.h

//GLOBALS==========
const int WIDTH = 1260;
const int HEIGHT = 630;
const int ROZMIAR = 70;
const int LICZBA_POCISKOW = 5;
const int ROZMIAR_POCISKOW = 2;
const int LICZBA_ZAGRODZEN = 85;
const int LICZBA_PRZECIWNIKOW = 4;
const int LICZBA_DODATKOWEGO_ZYCIA = 3;

bool keys[4] = {false, false, false, false};

/* Poziom gry */
int SCORE; // Zliczamy ilosc zniszczonych przeciwnikow w jednym poziomie
int ALL_SCORE; // Ilosc wszystkich zniszczonych przeciwnikow
int LEVEL = 1; // Poziom gry
int CEL_INKREMENTACJA = 3; // Ile mam zniszczyc do nastepnego poziomu 
const int CEL = 3;
const int MAX_LEVEL = 5;

time_t Poziomy(bool &isLevelComplete, bool &isGameComplete)
{
	if(SCORE >= CEL_INKREMENTACJA)
	{
		if(LEVEL == MAX_LEVEL)
		{
			isGameComplete = true;
		}
		else 
		{
			++LEVEL;
			isLevelComplete = true;
		}

		if(LEVEL == MAX_LEVEL) CEL_INKREMENTACJA = CEL;
		else CEL_INKREMENTACJA += CEL;

		ALL_SCORE += SCORE;
		SCORE = 0;

		return time(NULL);
	}
	return 0;
}
void Poziomy(bool &isLevelComplete) // do resetowania poziomow
{
	isLevelComplete = true;

	LEVEL = 1;
	CEL_INKREMENTACJA = CEL;
	ALL_SCORE = 0;
	SCORE = 0;
} 
/* ----------------------------*/

/* Pole gry - pole w ktorym potem 7bede rozmieszczac zagrodzenia */
int **UtworzPoleGry(void)
{
	int **poleGryTabl = new int*[WIDTH/ROZMIAR];
	for(int i = 0; i < WIDTH/ROZMIAR; ++i)
	{
		poleGryTabl[i] = new int[HEIGHT/ROZMIAR];
	}

	for(int i = 0; i < WIDTH/ROZMIAR; ++i)
	{
		for(int j = 0; j < HEIGHT/ROZMIAR; ++j)
		{
			poleGryTabl[i][j] = -1;
		}
	}

	// Zabronione pola
	const int w = WIDTH/ROZMIAR;
	const int h = HEIGHT/ROZMIAR;

	poleGryTabl[w/2][h/2] = poleGryTabl[0][0] = poleGryTabl[w - 1][0] = poleGryTabl[0][h - 1] = poleGryTabl[w - 1][h - 1] = 0;
	// ---------
	return poleGryTabl;
}
int **PoleGry = UtworzPoleGry();
/* -------------------------- */
int main(void)
{
	//Primitive variable
	bool done = false;
	bool redraw = true;
	bool isGameOver = false;
	bool isGameComplete = false;
	bool isLevelComplete = true;

	const int FPS = 100;

	srand(time(NULL)); 

	//Object variables
	czolg mojCzolg;
	przeciwnik przeciwniki[LICZBA_PRZECIWNIKOW];
	const zagrodzenie zagrodzenia[LICZBA_ZAGRODZEN];
	const mody zycie[3];

	//Allegro variables
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_FONT *font100 = NULL;
	ALLEGRO_FONT *font36 = NULL;
	ALLEGRO_FONT *font22 = NULL;
	ALLEGRO_FONT *font16 = NULL;
	ALLEGRO_BITMAP *tlo = NULL;

	//Initialization Functions
	if(!al_init()) return -1; //initialize Allegro
		
	display = al_create_display(WIDTH, HEIGHT); //create our display object
	if(!display) return -1;

	al_init_primitives_addon();
	al_install_keyboard();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);

	font100 = al_load_font("Volkoff.ttf", 100, 0);
	font36 = al_load_font("Volkoff.ttf", 36, 0);
	font22 = al_load_font("Volkoff.ttf", 22, 0);
	font16 = al_load_font("calibri.ttf", 16, 0);

	zagrodzenie::ZdefObrazki();
	czolg::ZdefObrazek();
	przeciwnik::ZdefObrazek();
	eksplozja::ZdefObrazek();
	mina::ZdefObrazek();
	mody::ZdefObrazek();

	tlo = al_load_bitmap("tlo.jpg");

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_start_timer(timer);
	while(!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_TIMER)
		{
			redraw = true;

			if(!isGameOver && !isLevelComplete)
			{
				kolidowanieCzolgow(mojCzolg, przeciwniki);
				kolidowaniePociskow(mojCzolg, przeciwniki, zagrodzenia);
				kolidowanieDodatkow(mojCzolg, przeciwniki, zycie);
	
				/* Moj czolg */
				mojCzolg.Sterowanie(zagrodzenia);
				mojCzolg.mina.Boom.Przerysuj(mojCzolg.mina.ekspEnd);
				for(int i = 0; i < LICZBA_POCISKOW; ++i)
				{
					mojCzolg.pociski[i].Przerysuj();
					mojCzolg.pociski[i].Boom.Przerysuj(mojCzolg.pociski[i].ekspEnd);
				}	
				/* -------- */
				/* Przeciwniki */
				for(int i = 0; i < LICZBA_PRZECIWNIKOW; ++i)
				{
					przeciwniki[i].OdswiezPrzeciwnika(mojCzolg, przeciwniki); // wznawiamy przeciwnika, gdy liczba zycia jest mniejsza lub rowna 0
					przeciwniki[i].Inteligencja(zagrodzenia, mojCzolg.PozycjaX(), mojCzolg.PozycjaY());
					przeciwniki[i].mina.Boom.Przerysuj(przeciwniki[i].mina.ekspEnd);
					for(int j = 0; j < LICZBA_POCISKOW; ++j)
					{
						przeciwniki[i].pociski[j].Przerysuj();
						przeciwniki[i].pociski[j].Boom.Przerysuj(przeciwniki[i].pociski[j].ekspEnd);
					}	
				}
				/* --------- */

				if(keys[UP])
				{
					mojCzolg.PrzesunWGore();
				}
				else if(keys[DOWN])
				{
					mojCzolg.PrzesunWDol();
				}
				else if(keys[LEFT])
				{
					mojCzolg.PrzesunWLewo();
				}
				else if(keys[RIGHT])
				{
					mojCzolg.PrzesunWPrawo();
				}

				if(mojCzolg.Zycie() <= 0)
				{
					isGameOver = true;
				}
			}
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			done = true;

		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			if(!isGameOver && !isLevelComplete)
			{
				switch (ev.keyboard.keycode)
				{
					case ALLEGRO_KEY_UP:
						keys[UP] = true;
						mojCzolg.OstatniKieKierunek(UP);
						break;
					case ALLEGRO_KEY_DOWN:
						keys[DOWN] = true;
						mojCzolg.OstatniKieKierunek(DOWN);
						break;
					case ALLEGRO_KEY_LEFT:
						keys[LEFT] = true;
						mojCzolg.OstatniKieKierunek(LEFT);
						break;
					case ALLEGRO_KEY_RIGHT:
						keys[RIGHT] = true;
						mojCzolg.OstatniKieKierunek(RIGHT);
						break;
					case ALLEGRO_KEY_SPACE:
						mojCzolg.Wystrzel();
						break;
					case ALLEGRO_KEY_B:
						mojCzolg.mina.Ustaw(mojCzolg.PozycjaX(), mojCzolg.PozycjaY());
				}
			}
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(ev.keyboard.keycode)
			{
				case ALLEGRO_KEY_UP:
					keys[UP] = false;
					break;
				case ALLEGRO_KEY_DOWN:
					keys[DOWN] = false;
					break;
				case ALLEGRO_KEY_LEFT:
					keys[LEFT] = false;
					break;
				case ALLEGRO_KEY_RIGHT:
					keys[RIGHT] = false;
					break;
				case ALLEGRO_KEY_ESCAPE:
					done = true;
					break;
				case ALLEGRO_KEY_ENTER:
					if(isLevelComplete || isGameComplete || isGameOver)
					{
						mojCzolg.czolg::czolg();
						for(int i = 0; i < LICZBA_PRZECIWNIKOW; ++i)
						{
							przeciwniki[i].przeciwnik::przeciwnik();
						}
						PoleGry = UtworzPoleGry();
						for(int i = 0; i < LICZBA_ZAGRODZEN; ++i)
						{
							zagrodzenia[i].zagrodzenie::zagrodzenie();	
						}
						for(int i = 0; i < LICZBA_DODATKOWEGO_ZYCIA; ++i)
						{
							zycie[i].mody::mody();	
						}

						if(isLevelComplete)
						{
							isLevelComplete = false;
						}
						else
						{
							Poziomy(isLevelComplete);
							isGameComplete = false;
							isGameOver = false;
						}
					}
					
					break;
			}
		}

		if(redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;

			time_t delay = Poziomy(isLevelComplete, isGameComplete);

			if(isLevelComplete)
			{
				if(delay)
				{
					while(difftime(time(NULL), delay) <= 1)
					{
						al_draw_textf(font100, al_map_rgb(0, 0, 0), WIDTH / 2, (HEIGHT / 2) - 70, ALLEGRO_ALIGN_CENTRE, "LEVEL COMPLETE !");

						al_flip_display();
						al_clear_to_color(al_map_rgb(132,130,130));
					}
				}

				al_draw_textf(font100, al_map_rgb(0, 0, 0), WIDTH / 2, (HEIGHT / 2) - 100, ALLEGRO_ALIGN_CENTRE, "LEVEL %i !", LEVEL);
				al_draw_textf(font36, al_map_rgb(0, 0, 0), WIDTH / 2, (HEIGHT / 2) + 20, ALLEGRO_ALIGN_CENTRE, "CEL: ZNISZCZ %i PRZECIWNIKOW", CEL_INKREMENTACJA);
				al_draw_text(font16, al_map_rgb(0, 0, 0), WIDTH / 2, (HEIGHT / 2) + 80, ALLEGRO_ALIGN_CENTER, "(ENTER - rozpocznij gre    -    ESC - zakoncz gre)");

				al_flip_display();
				al_clear_to_color(al_map_rgb(132,130,130));
			}
			else if(!isGameOver && !isGameComplete)
			{
				/* Rysujemy tlo */
				for(int i = 0; i <= WIDTH; i += al_get_bitmap_width(tlo))
				{
					for(int j = 0; j <= HEIGHT; j += al_get_bitmap_height(tlo))
					{
						al_draw_bitmap(tlo, i, j, 0);
					}
				}
				/* Rysujemy dodatki */
				for(int i = 0; i < LICZBA_DODATKOWEGO_ZYCIA; ++i)
				{
					zycie[i].Rysuj();
				}
				mojCzolg.mina.Rysuj();
				for(int i = 0; i < LICZBA_PRZECIWNIKOW; ++i)
				{
					przeciwniki[i].mina.Rysuj();
				}
				/* Rysujemy czolg i pociski */
				mojCzolg.Rysuj();
				for(int i = 0; i < LICZBA_POCISKOW; ++i)
				{
					mojCzolg.pociski[i].Rysuj();
				}
				/* Rysujemy przeciwnikow i pociski */
				for(int i = 0; i < LICZBA_PRZECIWNIKOW; ++i)
				{
					przeciwniki[i].Rysuj();
					for(int j = 0; j < LICZBA_POCISKOW; ++j)
					{
						przeciwniki[i].pociski[j].Rysuj();
					}
				}
				/* Rysujemy zagrodzenia */
				for(int i = 0; i < LICZBA_ZAGRODZEN; ++i)
				{
					zagrodzenia[i].Rysuj();
				}
				/* Rysujemy eksplozje */
				mojCzolg.mina.Boom.Rysuj();
				for(int i = 0; i < LICZBA_POCISKOW; ++i)
				{			
					mojCzolg.pociski[i].Boom.Rysuj();
					for(int j = 0; j < LICZBA_PRZECIWNIKOW; ++j)
					{
						przeciwniki[j].pociski[i].Boom.Rysuj();
						przeciwniki[j].mina.Boom.Rysuj();
					}
				}
				/* Rysuje pomocniecze napisy */
				al_draw_textf(font22, al_map_rgb(0, 0, 0), 10, 4, ALLEGRO_ALIGN_LEFT, "LEVEL: %i", LEVEL);
				al_draw_textf(font22, al_map_rgb(0, 0, 0), 10, 28, ALLEGRO_ALIGN_LEFT, "CEL: %i", CEL_INKREMENTACJA - SCORE);

				al_flip_display();
				al_clear_to_color(al_map_rgb(0,0,0));
			} 
			else // isGameOver && isGameComplete
			{
				if(isGameComplete)
					al_draw_textf(font100, al_map_rgb(0, 0, 0), WIDTH / 2, (HEIGHT / 2) - 100, ALLEGRO_ALIGN_CENTRE, "YOU WIN !");
				else
					al_draw_textf(font100, al_map_rgb(0, 0, 0), WIDTH / 2, (HEIGHT / 2) - 100, ALLEGRO_ALIGN_CENTRE, "GAME OVER !");

				if(ALL_SCORE <= 20)
				{
					al_draw_textf(font36, al_map_rgb(0, 0, 0), WIDTH / 2, (HEIGHT / 2) + 20, ALLEGRO_ALIGN_CENTRE, "DZISIAJ CI JAKOS NIE POSZLO, SPROBOJ JESZCZE RAZ");
				}
				else if(ALL_SCORE <= 30)
				{
					al_draw_textf(font36, al_map_rgb(0, 0, 0), WIDTH / 2, (HEIGHT / 2) + 20, ALLEGRO_ALIGN_CENTRE, "SKASOWALES %i PRZECIWNIKOW. NIE NAJLEPSZY WYNIK", ALL_SCORE);
				}
				else
				{
					al_draw_textf(font36, al_map_rgb(0, 0, 0), WIDTH / 2, (HEIGHT / 2) + 20, ALLEGRO_ALIGN_CENTRE, "GRATULACJE. ZNISZCZYLES %i PRZECIWNIKOW", ALL_SCORE);
				}
				al_draw_text(font16, al_map_rgb(0, 0, 0), WIDTH / 2, (HEIGHT / 2) + 80, ALLEGRO_ALIGN_CENTER, "(ENTER - rozpocznij gre ponownie   -    ESC - zakoncz gre)");

				al_flip_display();
				al_clear_to_color(al_map_rgb(132,130,130));
			}	
		}
	}

	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_font(font100);
	al_destroy_font(font36);
	al_destroy_font(font22);
	al_destroy_font(font16);
	al_destroy_display(display);
	al_destroy_bitmap(tlo);

	zagrodzenie::ZniszczObrazki();
	czolg::ZniszczObrazek();
	przeciwnik::ZniszczObrazek();
	eksplozja::ZniszczObrazek();
	mody::ZniszczObrazek();
	mina::ZniszczObrazek();

	/* Zwolniamy pamiec z tablicy PoleGry */
	for(int i = 0; i < WIDTH/ROZMIAR; ++i)
	{
		delete[]PoleGry[i];
	}
	delete[]PoleGry;

	return 0;
}

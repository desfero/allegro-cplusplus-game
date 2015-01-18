#pragma once

#include "zagrodzenie.h"
#include "mody.h"
#include "przeciwnik.h" // przez to dolaczam jeszcze czolg.h, pocisk.h, eksplozja.h, mina.h

void kolidowanieCzolgow(czolg &mojCzolg, przeciwnik *przeciwniki)
{
	/* Moj czolg z czolgiem przeciwnika */ 
	for(int i = 0; i < LICZBA_PRZECIWNIKOW; ++i)
	{
	
		if(mojCzolg.x + ROZMIAR > przeciwniki[i].x &&
		   mojCzolg.x < przeciwniki[i].x + ROZMIAR &&
		   mojCzolg.y > przeciwniki[i].y && 
		   mojCzolg.y <= przeciwniki[i].y + ROZMIAR)
		{
			mojCzolg.kierunek[UP] = false;
			przeciwniki[i].kierunek[DOWN] = false;
		}
		if(mojCzolg.x > przeciwniki[i].x - ROZMIAR &&
		   mojCzolg.x - ROZMIAR < przeciwniki[i].x &&
		   mojCzolg.y >= przeciwniki[i].y - ROZMIAR && 
		   mojCzolg.y < przeciwniki[i].y)
		{
			mojCzolg.kierunek[DOWN] = false;
			przeciwniki[i].kierunek[UP] = false;
		}
		if(mojCzolg.x > przeciwniki[i].x &&
		   mojCzolg.x <= przeciwniki [i].x + ROZMIAR &&
		   mojCzolg.y + ROZMIAR > przeciwniki[i].y && 
		   mojCzolg.y < przeciwniki[i].y + ROZMIAR)
		{
			mojCzolg.kierunek[LEFT] = false;
			przeciwniki[i].kierunek[RIGHT] = false;
		}
		if(mojCzolg.x >= przeciwniki[i].x - ROZMIAR &&
		   mojCzolg.x < przeciwniki[i].x &&
		   mojCzolg.y > przeciwniki[i].y - ROZMIAR && 
		   mojCzolg.y - ROZMIAR < przeciwniki[i].y)
		{
			mojCzolg.kierunek[RIGHT] = false;
			przeciwniki[i].kierunek[LEFT] = false;
		}
	}
	/* ----------------------------------- */

	/* Przeciwnik z przeciwnikiem */
	for(int i = 0; i < LICZBA_PRZECIWNIKOW; ++i)
	{
		for(int j = 0; (j < LICZBA_PRZECIWNIKOW) && j != i; ++j)
		{
			if(przeciwniki[i].x + ROZMIAR > przeciwniki[j].x &&
			   przeciwniki[i].x < przeciwniki[j].x + ROZMIAR &&
			   przeciwniki[i].y > przeciwniki[j].y && 
			   przeciwniki[i].y <= przeciwniki[j].y + ROZMIAR)
			{
				przeciwniki[i].kierunek[UP] = false;
				przeciwniki[j].kierunek[DOWN] = false;
			}
			if(przeciwniki[i].x > przeciwniki[j].x - ROZMIAR &&
			   przeciwniki[i].x - ROZMIAR < przeciwniki[j].x &&
			   przeciwniki[i].y >= przeciwniki[j].y - ROZMIAR && 
			   przeciwniki[i].y < przeciwniki[j].y)
			{
				przeciwniki[i].kierunek[DOWN] = false;
				przeciwniki[j].kierunek[UP] = false;
			}
			if(przeciwniki[i].x > przeciwniki[j].x &&
			   przeciwniki[i].x <= przeciwniki [j].x + ROZMIAR &&
			   przeciwniki[i].y + ROZMIAR > przeciwniki[j].y && 
			   przeciwniki[i].y < przeciwniki[j].y + ROZMIAR)
			{
				przeciwniki[i].kierunek[LEFT] = false;
				przeciwniki[j].kierunek[RIGHT] = false;
			}
			if(przeciwniki[i].x >= przeciwniki[j].x - ROZMIAR &&
			   przeciwniki[i].x < przeciwniki[j].x &&
			   przeciwniki[i].y > przeciwniki[j].y - ROZMIAR && 
			   przeciwniki[i].y - ROZMIAR < przeciwniki[j].y)
			{
				przeciwniki[i].kierunek[RIGHT] = false;
				przeciwniki[j].kierunek[LEFT] = false;
			}
		}
	}
	/* ---------------------------------- */

	
}
void kolidowaniePociskow(czolg &mojCzolg, przeciwnik *przeciwniki, const zagrodzenie *zagrodzenia)
{
	/* Moj pocisk z czolgiem preciwnika */
	for(int i = 0; i < LICZBA_POCISKOW; ++i)
	{
		if(mojCzolg.pociski[i].live)
		{
			for(int j = 0; j < LICZBA_POCISKOW; ++j)
			{
				if(mojCzolg.pociski[i].x >= przeciwniki[j].x &&
				   mojCzolg.pociski[i].x <= przeciwniki[j].x + ROZMIAR &&
				   mojCzolg.pociski[i].y >= przeciwniki[j].y &&
				   mojCzolg.pociski[i].y <= przeciwniki[j].y + ROZMIAR)
				{
					--przeciwniki[j].lives;
					mojCzolg.pociski[i].live = false;

					mojCzolg.pociski[i].Boom.Start(mojCzolg.pociski[i].x, mojCzolg.pociski[i].y); 
				}
			}
		}
	}
	/* ------------------------------------- */

	/* Moj pocisk z zagrodzeniem */
	for(int i = 0; i < LICZBA_POCISKOW; ++i)
	{
		if(mojCzolg.pociski[i].live)
		{
			for(int j = 0; j < LICZBA_ZAGRODZEN; ++j)
			{
				if(zagrodzenia[j].typ != 0)
				{
					if(mojCzolg.pociski[i].x >= zagrodzenia[j].x &&
					   mojCzolg.pociski[i].x <= zagrodzenia[j].x +    ROZMIAR &&
					   mojCzolg.pociski[i].y >= zagrodzenia[j].y && 
					   mojCzolg.pociski[i].y <= zagrodzenia[j].y + ROZMIAR)
					{ 		
						--zagrodzenia[j].lives;
						mojCzolg.pociski[i].live = false;

						mojCzolg.pociski[i].Boom.Start(mojCzolg.pociski[i].x, mojCzolg.pociski[i].y);
						if(zagrodzenia[j].lives == 0)
						{
							zagrodzenia[j].typ = 0;
						}
					}
				}
			}
		}
	}
	/* ----------------------------------- */

	/* Pocisk przeciwnika z zagrodzeniem */
	for(int i = 0; i < LICZBA_PRZECIWNIKOW; ++i)
	{
		for(int j = 0; j < LICZBA_POCISKOW; ++j)
		{
			if(przeciwniki[i].pociski[j].live)
			{
				for(int k = 0; k < LICZBA_ZAGRODZEN; ++k)
				{
					if(zagrodzenia[k].typ != 0)
					{
						if(przeciwniki[i].pociski[j].x >= zagrodzenia[k].x &&
						   przeciwniki[i].pociski[j].x <= zagrodzenia[k].x + ROZMIAR &&
						   przeciwniki[i].pociski[j].y >= zagrodzenia[k].y && 
						   przeciwniki[i].pociski[j].y <= zagrodzenia[k].y + ROZMIAR)
						{ 		
							/* LEVEL i MAX_LEVEL pobieram z clasy przeciwnik */
							if(LEVEL != MAX_LEVEL) przeciwniki[i].pociski[j].live = false; // - czolgi moga niszczyc wszystkie zagrodzenia gdy jest maksymalny level
							--zagrodzenia[k].lives;

							przeciwniki[i].pociski[j].Boom.Start(przeciwniki[i].pociski[j].x, przeciwniki[i].pociski[j].y);
							if(zagrodzenia[k].lives <= 0)
							{
								zagrodzenia[k].typ = 0;
							}
						}
					}
				}
			}
		}
	}
	/* ----------------------------------- */

	/* Pocisk przeciwnika z moim czolgiem */
	for(int i = 0; i < LICZBA_PRZECIWNIKOW; ++i)
	{
		for(int j = 0; j < LICZBA_POCISKOW; ++j)
		{
			if(przeciwniki[i].pociski[j].live)
			{
				if(przeciwniki[i].pociski[j].x >= mojCzolg.x &&
				   przeciwniki[i].pociski[j].x <= mojCzolg.x + ROZMIAR &&
				   przeciwniki[i].pociski[j].y >= mojCzolg.y && 
				   przeciwniki[i].pociski[j].y <= mojCzolg.y + ROZMIAR)
				{ 		
					przeciwniki[i].pociski[j].live = false;
					--mojCzolg.lives;

					przeciwniki[i].pociski[j].Boom.Start(przeciwniki[i].pociski[j].x, przeciwniki[i].pociski[j].y);
				}
			}
		}
	}
	/* ----------------------------------- */

	/* Pocisk przeciwnika z przeciwnikiem */
	for(int i = 0; i < LICZBA_PRZECIWNIKOW; ++i)
	{
		for(int j = 0; j < LICZBA_POCISKOW; ++j)
		{
			if(przeciwniki[i].pociski[j].live)
			{
				for(int k = 0; k < LICZBA_PRZECIWNIKOW; ++k)
				{
					
					if(przeciwniki[i].pociski[j].x >= przeciwniki[k].x &&
					   przeciwniki[i].pociski[j].x <= przeciwniki[k].x + ROZMIAR &&
					   przeciwniki[i].pociski[j].y >= przeciwniki[k].y && 
					   przeciwniki[i].pociski[j].y <= przeciwniki[k].y + ROZMIAR)
					{ 		
						przeciwniki[i].pociski[j].live = false;
						--przeciwniki[k].lives;

						przeciwniki[i].pociski[j].Boom.Start(przeciwniki[i].pociski[j].x, przeciwniki[i].pociski[j].y);
					}
					
				}
			}
		}
	}
	/* ----------------------------------- */

	/* Moj pocisk z pociskiem przeciwnika */
	for(int i = 0; i < LICZBA_POCISKOW; ++i)
	{
		if(mojCzolg.pociski[i].live)
		{
			for(int j = 0; j < LICZBA_PRZECIWNIKOW; ++j)
			{
				for(int k = 0; k < LICZBA_POCISKOW; ++k)
				{
					if(przeciwniki[j].pociski[k].live)
					{
						if(mojCzolg.ostKierunek == UP || mojCzolg.ostKierunek == DOWN)
						{
							if(mojCzolg.pociski[i].x - ROZMIAR_POCISKOW >= przeciwniki[j].pociski[k].x - ROZMIAR_POCISKOW &&
							   mojCzolg.pociski[i].x - ROZMIAR_POCISKOW <= (przeciwniki[j].pociski[k].x - ROZMIAR_POCISKOW) + ROZMIAR_POCISKOW && 
							   mojCzolg.pociski[i].y - ROZMIAR_POCISKOW >= przeciwniki[j].pociski[k].y - ROZMIAR_POCISKOW && 
							   mojCzolg.pociski[i].y - ROZMIAR_POCISKOW <= (przeciwniki[j].pociski[k].y - ROZMIAR_POCISKOW) + (ROZMIAR_POCISKOW * 6))
							{
								mojCzolg.pociski[i].live = false;
								przeciwniki[j].pociski[k].live = false;

								mojCzolg.pociski[i].Boom.Start(mojCzolg.pociski[i].x, mojCzolg.pociski[i].y);
							}
						}
						else
						{
							if(mojCzolg.pociski[i].x - ROZMIAR_POCISKOW >= przeciwniki[j].pociski[k].x - ROZMIAR_POCISKOW &&
							   mojCzolg.pociski[i].x - ROZMIAR_POCISKOW <= (przeciwniki[j].pociski[k].x - ROZMIAR_POCISKOW) + (ROZMIAR_POCISKOW * 6) && 
							   mojCzolg.pociski[i].y - ROZMIAR_POCISKOW >= przeciwniki[j].pociski[k].y - ROZMIAR_POCISKOW && 
							   mojCzolg.pociski[i].y - ROZMIAR_POCISKOW <= (przeciwniki[j].pociski[k].y - ROZMIAR_POCISKOW) + ROZMIAR_POCISKOW )
							{
								mojCzolg.pociski[i].live = false;
								przeciwniki[j].pociski[k].live = false;

								mojCzolg.pociski[i].Boom.Start(mojCzolg.pociski[i].x, mojCzolg.pociski[i].y);
							}
						}
					}
				}	
			}
		}
	}
	/* ----------------------------------- */

	/* Pocisk przeciwnika z pociskiem przeciwnika */
	for(int h = 0; h < LICZBA_PRZECIWNIKOW; ++h)
	{
		for(int i = 0; i < LICZBA_POCISKOW; ++i)
		{
			if(przeciwniki[h].pociski[i].live)
			{
				for(int j = 0; j < LICZBA_PRZECIWNIKOW && j != h; ++j)
				{
					for(int k = 0; k < LICZBA_POCISKOW; ++k)
					{
						if(przeciwniki[j].pociski[k].live)
						{
							if(mojCzolg.ostKierunek == UP || mojCzolg.ostKierunek == DOWN)
							{
								if(przeciwniki[h].pociski[i].x - ROZMIAR_POCISKOW >= przeciwniki[j].pociski[k].x - ROZMIAR_POCISKOW &&
								   przeciwniki[h].pociski[i].x - ROZMIAR_POCISKOW <= (przeciwniki[j].pociski[k].x - ROZMIAR_POCISKOW) + ROZMIAR_POCISKOW && 
								   przeciwniki[h].pociski[i].y - ROZMIAR_POCISKOW >= przeciwniki[j].pociski[k].y - ROZMIAR_POCISKOW && 
								   przeciwniki[h].pociski[i].y - ROZMIAR_POCISKOW <= (przeciwniki[j].pociski[k].y - ROZMIAR_POCISKOW) + (6 * ROZMIAR_POCISKOW))
								{
									przeciwniki[h].pociski[i].live = false;
									przeciwniki[j].pociski[k].live = false;

									przeciwniki[j].pociski[k].Boom.Start(przeciwniki[j].pociski[k].x, przeciwniki[j].pociski[k].y);
								}
							}
							else
							{
								if(przeciwniki[h].pociski[i].x - ROZMIAR_POCISKOW >= przeciwniki[j].pociski[k].x - ROZMIAR_POCISKOW &&
								   przeciwniki[h].pociski[i].x - ROZMIAR_POCISKOW <= (przeciwniki[j].pociski[k].x - ROZMIAR_POCISKOW) + (6 * ROZMIAR_POCISKOW) && 
								   przeciwniki[h].pociski[i].y - ROZMIAR_POCISKOW >= przeciwniki[j].pociski[k].y - ROZMIAR_POCISKOW && 
								   przeciwniki[h].pociski[i].y - ROZMIAR_POCISKOW <= (przeciwniki[j].pociski[k].y - ROZMIAR_POCISKOW) + ROZMIAR_POCISKOW )
								{
									przeciwniki[h].pociski[i].live = false;
									przeciwniki[j].pociski[k].live = false;

									przeciwniki[j].pociski[k].Boom.Start(przeciwniki[j].pociski[k].x, przeciwniki[j].pociski[k].y);
								}
							}
						}
					}	
				}
			}
		}
	}
	/* ----------------------------------- */
}
void kolidowanieDodatkow(czolg &mojCzolg, przeciwnik *przeciwniki,const mody *zycie)
{
	/* Mina mojego czolga z przeciwnikiem */
	if(mojCzolg.mina.live)
	{
		for(int i = 0; i < LICZBA_PRZECIWNIKOW; ++i)
		{
			if(mojCzolg.mina.x >= przeciwniki[i].x &&
			   mojCzolg.mina.x <= przeciwniki[i].x + ROZMIAR &&
			   mojCzolg.mina.y >= przeciwniki[i].y &&
			   mojCzolg.mina.y <= przeciwniki[i].y + ROZMIAR)
			{
				przeciwniki[i].lives = 0;
				mojCzolg.mina.live = false;

				mojCzolg.mina.Boom.Start(mojCzolg.mina.x, mojCzolg.mina.y); 
			}
		}
	}
	/* -------------------------------- */

	/* Moj czolg z mina przeciwnika */
	for(int i = 0; i < LICZBA_PRZECIWNIKOW; ++i)
	{
		if(przeciwniki[i].mina.live)
		{
			if(przeciwniki[i].mina.x >= mojCzolg.x &&
			   przeciwniki[i].mina.x <= mojCzolg.x + ROZMIAR &&
			   przeciwniki[i].mina.y >= mojCzolg.y &&
			   przeciwniki[i].mina.y <= mojCzolg.y + ROZMIAR)
			{
				mojCzolg.lives -= czolg::MAX_LIVES/2;
				przeciwniki[i].mina.live = false;

				przeciwniki[i].mina.Boom.Start(przeciwniki[i].mina.x, przeciwniki[i].mina.y); 
			}
		}
	}
	/* --------------------------- */

	/* Zycie z moim czolgiem */
	for(int i = 0; i < LICZBA_DODATKOWEGO_ZYCIA; ++i)
	{
		if(zycie[i].live && mojCzolg.lives != czolg::MAX_LIVES)
		{
			if(zycie[i].x >= mojCzolg.x &&
			   zycie[i].x <= mojCzolg.x + ROZMIAR &&
			   zycie[i].y >= mojCzolg.y &&
			   zycie[i].y <= mojCzolg.y + ROZMIAR)
			{
				++mojCzolg.lives;
				zycie[i].live = false;
			}
		}
	}
	/* ---------------------- */
}
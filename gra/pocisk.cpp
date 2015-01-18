#include "pocisk.h"

pocisk::pocisk(void)
{
	live = false;
	ekspEnd = true;
}

pocisk::~pocisk(void){}

void pocisk::Rysuj()
{
	if(live)
	{
		al_draw_filled_circle(x, y, ROZMIAR_POCISKOW, al_map_rgb(250, 250, 240));
	}
}

void pocisk::Przerysuj()
{
	if(live)
	{
		if(kierunek == 0)
		{
			y -= SPEED;
		}
		else if(kierunek == 1)
		{
			y += SPEED;
		}
		else if(kierunek == 2)
		{
			x -= SPEED;
		}
		else if(kierunek == 3)
		{
			x += SPEED;
		}

		if(x > WIDTH || x < 0 || y > HEIGHT || y < 0)
		{
			live = false;
			Boom.Start(x, y);
		}
	}

}




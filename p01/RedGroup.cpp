#include "RedGroup.h"
#include "Surface.h"
#include "Includes.h"
#include "Constants.h"

Image yellowimage("images/galaxian/GalaxianFlagship.gif");
Image redimage("images/galaxian/GalaxianRedAlien.gif");

Surface redsurface(W, H);

Rect yellow_rect = yellowimage.getRect();
Rect red_rect = redimage.getRect();


void RedGroup::draw(int x, int y, bool red_ship)
{
    if (red_ship)
    {
        red_rect.x = x;
        red_rect.y = y;

        redsurface.put_image(redimage,red_rect); // show the red spaceship
    }
    else
    {
        yellow_rect.x = x;
        yellow_rect.y = y;

        // show the yellow spaceship
        redsurface.put_image(yellowimage,yellow_rect); 
    }

    
}



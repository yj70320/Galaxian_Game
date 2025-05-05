#include "PurpleAlien.h"
#include "Surface.h"
#include "Includes.h"
#include "Constants.h"

Image Purpleimage("images/galaxian/GalaxianPurpleAlien.gif");
Surface Purplesurface(W, H);
Rect Purplerect = Purpleimage.getRect();


void PurpleAlien::draw(int x, int y)
{
    Purplerect.x = x;
    Purplerect.y = y;

    Purplesurface.put_image(Purpleimage,Purplerect); // show the spaceship
}



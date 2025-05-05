#include "Ship.h"
#include "Surface.h"
#include "Includes.h"
#include "Constants.h"

Image image("images/galaxian/GalaxianGalaxip.gif");
Surface surface(W, H);
Rect rect = image.getRect();



void Ship::draw(int x, int y)
{
    rect.x = x;
    rect.y = y;

    surface.put_image(image,rect); // show the spaceship
}


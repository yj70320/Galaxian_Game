#include "BlueAlien.h"
#include "Surface.h"
#include "Includes.h"
#include "Constants.h"

Image blueimage("images/galaxian/GalaxianAquaAlien.gif");
Surface bluesurface(W, H);
Rect bluerect = blueimage.getRect();


void BlueAlien::draw(int x, int y)
{
    bluerect.x = x;
    bluerect.y = y;

    bluesurface.put_image(blueimage,bluerect); // show the spaceship
}



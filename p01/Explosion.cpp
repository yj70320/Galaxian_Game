#include "Explosion.h"
#include "Surface.h"
#include "Includes.h"
#include "Constants.h"

Image e1_image("images/galaxian/e1.png");
Image e2_image("images/galaxian/e2.png");
Image e3_image("images/galaxian/e3.png");
Image e4_image("images/galaxian/e4.png");

Surface surface_ep(W, H);

Rect recte1 = e1_image.getRect();
Rect recte2 = e2_image.getRect();
Rect recte3 = e3_image.getRect();
Rect recte4 = e4_image.getRect();



void Explosion::draw(int x, int y, int e)
{
    if (e == 1)
    {
        recte1.x = x;
        recte1.y = y;

        surface_ep.put_image(e1_image,recte1); // explosion gif 1
    }

    if (e == 2)
    {
        recte2.x = x;
        recte2.y = y;

        surface_ep.put_image(e2_image,recte2); // explosion gif 2
    }

    if (e == 3)
    {
        recte3.x = x;
        recte3.y = y;

        surface_ep.put_image(e3_image,recte3); // explosion gif 3
    }

    if (e == 4)
    {
        recte4.x = x;
        recte4.y = y;

        surface_ep.put_image(e4_image,recte4); // explosion gif 4
    }
    
}


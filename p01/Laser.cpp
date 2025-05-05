#include "Laser.h"
#include "Includes.h"
#include "Constants.h"


// Surface surface(W, H);
Surface surf(W, H);

void Laser::draw(int x, int y, bool laser_color)
{

    // 0为玩家激光，红色
    if (!laser_color)
    {
        surf.put_rect(x,y,2,20,200,20,20);
    }
    // 1为外星激光，蓝色
    else
    {
        surf.put_rect(x,y,2,20,0, 200, 200);
    }
}

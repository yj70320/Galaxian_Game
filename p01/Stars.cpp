#include <iostream>
#include "Stars.h"
#include "Surface.h"

void Sky::draw()
{
    for (int i = 0; i < 50; ++i)
    {
        if (stars[i].y() >= H)
        {
            stars[i].y(0);
            stars[i].x(rand() % W);
        }
        stars[i].move();
        // 显示矩形，即星星
        surface_.put_rect(stars[i].x(), stars[i].y(), stars[i].w(), stars[i].h(),
                          stars[i].r(), stars[i].g(), stars[i].b());
    }
}

void Sky::build()
{
    for (int i = 0; i < 50; ++i)
    {
        Stars star;
        
        star.x(rand() % W);
        star.y(rand() % H);

        star.type(rand() % 2 + 1);
        
        if (star.type() == 1)
        {
            star.w(1);
            star.h(1);
            star.speed(1);
            star.r(150);
            star.g(150);
            star.b(150);
        }
        else if (star.type() == 2)
        {
            star.w(2);
            star.h(2);
            star.speed(2);
            star.r(175);
            star.g(175);
            star.b(175);
        }
       
        stars.push_back(star);
    }
    // 保证星星个数不超过50个,防止星星溢出
    stars.shrink_to_fit();
}

void Stars::move()
{
    y_ += speed_;
}

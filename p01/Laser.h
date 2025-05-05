#ifndef LASER_H
#define LASER_H

#include "Includes.h"
// #include "Ship.h"
// #include "Image.h"
// #include "Surface.h"
#include "Constants.h"

class Laser
{
public:

    void draw(int x, int y, bool laser_color);
  
    
private:
    int x;
    int y;
};



#endif


#ifndef ALIEN_H
#define ALIEN_H

class Alien
{
public:
    Alien(int x = 0, int y = 0) : x_(x), y_(y) {}

protected:
    int x_;
    int y_;

};

#endif
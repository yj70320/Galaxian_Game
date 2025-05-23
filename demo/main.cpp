/****************************************************************************
 Yihsiang Liow
 Copyright
 ****************************************************************************/
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <sstream>

#include "Includes.h"
#include "Constants.h"
#include "compgeom.h"
#include "Surface.h"
#include "Event.h"

/*****************************************************************************
This is a short introduction to graphics, animation, sound, music, keyboard
control. Together with software development techniques, you can develop any
2d game. 

C/C++ does not have language features for game development. One would have to
look for 3rd party extension. The tools (functions, etc.) you are using is
developed by me on top of a 3rd party extension called SDL, an industrial
strength tool for game development. 

I've developed this only for this class. You are free to use this for any 
personal game development.

The setup of programs using this game development tool is complex if you have
never done it before. Furthermore the process has nothing to do with learning
to program or problem solving. Therefore instead of setting up a new project 
on your own, you should simply make a *copy* of this project when you need a 
new one.
*****************************************************************************/


/*****************************************************************************
MS .NET STUDIO

You can quickly find "identifiers" (i.e. names of variables, functions, etc.) 
using MS .NET Studio. Look at your "Class View" side bar. It should be close 
to your Solution Explorer. 

Using the "Class View" look for main().
*****************************************************************************/


/*****************************************************************************
An Event object that has access to user input such as "user close program",
"user presses a key", etc.

An *object* is like a variable but there are some differences. One big 
difference is that whereas an integer variable has an integer value, an object 
actually *contains* other variables and even functions! That's why you see 
things like

	event.poll()	// returns true if the user caused an event to occur

and

	event.type()	// returns the type of event caused by the user

In this function, event is an Event variable and in event there are two 
functions: poll() and type(). 

The delay() function will yield CPU time to other programs. This will give
other programs time to run. Otherwise this program will take up all the CPU,
making the computer unresponsive. You might have problems closing this program
if you don't yield some time.
*****************************************************************************/
void test_event()
{
	Surface surface(W, H);	// W = 640, H = 480 are constants. This creates
                            // a drawing surface of size W-by-H

	Event event; // event is an Event object. It's used to process user
                 // events such as mouse clicks, key presses, etc.
	while (1)
	{
		// This statement basically breaks out of the while-loop if the user
		// closes the program. You can treat this as a blackbox. In more
		// details, the program breaks out of the while loop if the
		// event object detects a user event (example: mouse click) and the
		// type of the event is to close the program.
		if (event.poll() && event.type() == QUIT) break;

		delay(100); // yield 100 milliseconds to other programs
	}

	// If the program reaches this point, then the user must have closed
	// the program. At this point, the program executes "return" which
	// causes the program goes back to where it came from.
	return;
}

void fancyhelloworld()
{
	Surface surface(W, H);
	Sound sound("sounds/laser.wav");
	Music music("sounds/GameLoop.ogg");
	music.play();
	Event event;

	Font font("fonts/FreeSans.ttf", 48);
	Image image(font.render("hello world", WHITE));
	Rect rect = image.getRect();

	int r = 0;
	int g = 0;
	int b = 255;
	int dr = 1;
	int dg = 2;
	int db = 3;
	Color c = {0, 100, 200};

	int dx = 2;
	int dy = 3;

	//sound.off();
	//music.off();
	int RATE = 1000 / 60;

	while (1)
	{
		if (event.poll() && event.type() == QUIT) break;

		int start = getTicks();

		r += dr;
		if (r < 0)
		{
			r = 0;
			dr = - dr;
		}
		else if (r > 255)
		{
			r = 255;
			dr = -dr;
		}

		g += dg;
		if (g < 0)
		{
			g = 0;
			dg = - dg;
		}
		else if (g > 255)
		{
			g = 255;
			dg = -dg;
		}

		db += db;
		if (b < 0)
		{
			b = 0;
			db = -db;
		}
		else if (b > 255)
		{
			b = 255;
			db = -db;
		}
		Color c = {Uint8(r), Uint8(g), Uint8(b)};
		Image image(font.render("hello world", c));

		rect.x += dx;
		if (rect.x < 0)
		{
			sound.play();
			rect.x = 0;
			dx = -dx;
		}
		else if (rect.x + rect.w > W - 1)
		{
			sound.play();
			rect.x = W - 1 - rect.w;
			dx = -dx;
		}

		rect.y += dy;
		if (rect.y < 0)
		{
			sound.play();
			rect.y = 0;
			dy = -dy;
		}
		else if (rect.y + rect.h > H - 1)
		{
			sound.play();
			rect.y = H - 1 - rect.h;
			dy = -dy;
		}

		surface.lock();
		surface.fill(BLACK);
		surface.put_image(image, rect);
		surface.unlock();
		surface.flip();

		int end = getTicks();
		int dt = RATE - end + start;
		if (dt > 0) delay(dt);
	}
	return;
}


/*****************************************************************************
This function show you how to draw a pixel (basically a dot on the screen).
First you have a create a Surface object (ours is called surface). To draw a
pixel at (x,y) with color r,g,b (r, g, b intensities) you do this:

	surface.put_pixel(x, y, r, g, b);

The color intensities r, g, b ranges from 0 to 255.

Exercise: r,g,b are 255,255,255 which is white (correct?). Modify this program
to draw pixels with random color.

Another thing to note is that in the while-loop, before you draw anything, you 
have to lock the surface using surface.lock() and after you've drawn 
everything, you need to unlock and flip the surface.

One thing to note that is that on the computer screen, the x-axis grows to
the right BUT the y-axis grows *downward*.

  0123456789 ...
 +-----------------------------
0|p
1|    r
2|
3| q
4|

p has x = 0, y = 0
q has x = 1, y = 3
r has x = 4, y = 1

WARNING: 
Another thing to note is that if you have a screen of width W, the maximum x
value you can use for drawing a pixel is W - 1. Likewise if the height if H,
the maximum y value is H - 1.

Exercise. Modify the program so that it draw random pixels (x,y) where x and y
are between 0 and 200.
*****************************************************************************/
void test_pixel()
{
	Surface surface(W, H);	// Create surface of width W and height H 
							// for drawing
	Event event;

	while (1)
	{
		if (event.poll() && event.type() == QUIT) break;

		int x = rand() % W;
		int y = rand() % H;
		int r = rand() % 256;
		int g = rand() % 256;
		int b = rand() % 256;

		surface.lock();
		surface.put_pixel(x, y, r, g, b);
		surface.unlock();
		//surface.update_rect(x, y, 1, 1);
		surface.flip();
		
		delay(2);
	}
	return;
}


/*****************************************************************************
This function, test_line(), shows you how to draw a line:

	surface.put_line(x0, y0, x1, y1, r, g, b);

This draws a line on the surface from (x0,y0) to (x1,y1) with color r,g,b.

Note that I've performed by computation of x0,y0,x1,y1 before I lock the 
surface. In general, the gap between locking and unlocking the surface should
be as small as possible.

Exercise. Modify the program to draw random lines with *random* color.
*****************************************************************************/
void test_line()
{
	Surface surface(W, H);
	Event event;

	while (1)
	{
		if (event.poll() && event.type() == QUIT) break;

		// Computation part
		int x0 = rand() % W;
		int y0 = rand() % H;
		int x1 = rand() % W;
		int y1 = rand() % H;

        int r = rand() % 256;
        int g = rand() % 256;
        int b = rand() % 256;
        
		// Drawing part: minimize the gap between lock and unlock
		surface.lock();
		surface.put_line(x0, y0, x1, y1, r, g, b);
		surface.unlock();
		surface.flip();

		delay(10);
	}
	return;
}


/*****************************************************************************
This function, test_circle(), shows you how to draw a circle:

surface.put_circle(x, y, rad, r, g, b);

This draws a circle on surface with center at (x,y), radius r, and with random
color.

Exercise. Modify the program to draw circles with radius 10.
*****************************************************************************/
void test_circle()
{
	Surface surface(W, H);
	Event event;

    
	while (1)
	{
		if (event.poll() && event.type() == QUIT) break;

		int x = rand() % W;
		int y = rand() % H;
		int r = rand() % 100 + 10;

		surface.lock();
		surface.put_circle(x, y, r, rand() % 256, rand() % 256 , rand() % 256);
		surface.unlock();
		surface.flip();

		delay(10);
	}
	return;
}

void test_unfilled_circle()
{
	Surface surface(W, H);
	Event event;

	while (1)
	{
		if (event.poll() && event.type() == QUIT) break;

		int x = rand() % W;
		int y = rand() % H;
		int r = rand() % 100 + 10;

		surface.lock();
		surface.put_unfilled_circle(x, y, r, rand() % 256, rand() % 256 , rand() % 256);
		surface.unlock();
		surface.flip();

		delay(10);
	}
	return;
}


/*****************************************************************************
This function, test_rect(), shows you how to draw a rectangle. The call

surface.put_rect(x, y, w, h, r, g, b);

draw a rectangle on surface with top-right corner (x,y), width w, height h,
and color r,g,b.

For instance the following is a rectangle with top-left corner (2,1), width 4
and height 3.

 0123456789...
 +---------------------
0| 
1| xxxx
2| xxxx
3| xxxx
4|

*****************************************************************************/
void test_rect()
{
	Surface surface(W, H);
	Event event;
	while (1)
	{
		if (event.poll() && event.type() == QUIT) break;

		int x = rand() % (W - 1);
		int y = rand() % (H - 1);
		int w = rand() % (W - 1 - x);
		int h = rand() % (H - 1 - y);

		surface.lock();
		surface.put_rect(x, y, w, h, rand() % 256, rand() % 256 , rand() % 256);
		surface.unlock();
		surface.flip();

		delay(10);
	}
	return;
}


/*****************************************************************************
This function, test_keyboard(), shows you how to check keyboard inputs.

When this function is running, press and release the left arrow key. The 
statement

		KeyPressed keypressed = get_keypressed();

create a KeyPressed variable.

		keypressed[LEFTARROW]

is true exactly when the left arrow key is pressed when you create the
KeyPressed variable keypressed.

Exercise. Change LEFTARROW to RIGHTARROW and run the program again.

Exercise. Try DOWNARROW, UPARROW, and SPACE.

The other keys are for instance SDLK_1 for the 1 key, SDLK_a for the a key,
SDLK_F1 for the F1 key, etc. (Google "SDL SDLK".)
*****************************************************************************/
void test_keyboard()
{
    Surface surface(W, H);
	Event event;

	while (1)
	{
		if (event.poll() && event.type() == QUIT) break;

		KeyPressed keypressed = get_keypressed();
		if (keypressed[LEFTARROW])
		{
			int x = rand() % W;
			int y = rand() % H;
			int rx = min(int(W - 1 - x), int(x));
			int ry = min(H - 1 - y, y);

			surface.lock();
			surface.put_circle(x, y, min(rx, ry), rand() % 256, rand() % 256 , rand() % 255);
			surface.unlock();
			surface.flip();

			delay(10);
		}
		if (keypressed[SPACE])
		{
			int x = rand() % W;
			int y = rand() % H;
			int rx = min(int(W - 1 - x), int(x));
			int ry = min(H - 1 - y, y);

			surface.lock();
			surface.put_circle(x, y, min(rx, ry), 255, 0, 0);
			surface.unlock();
			surface.flip();

			delay(10);
		}
	}
	return;
}

/*****************************************************************************
NEWS: ADDED 3/24/2013

This function, test_key_up_down(), shows you how to check keyboard events.

Note that a Keypressed variable will read the keyboard for the key pressed.
If you hold a key down event for a split second, if your game loop runs fast
enough, you would have processed this key pressed for 50 game loops. There are
times when you really only want to tell the game loop "the key is pressed"
and you want to execute something once. For instance, suppose if your game
allows the player to turn the sound on or off by pressing the S key, then
your game could potentially be turning the sound on and off about 51-100 times
even though the player press and release the S key only once.

(If you do not want to use an Event object to detect a key being pressed
and a key being released and you want to process a key, say S, being pressed
50-100 times, another way to achieve this is to insert a delay of say 1 sec
when you detect S being pressed.)

The way to get around this is to combine the reading of the key being pressed
with an Event objects a key being pressed down and then the key being
released. The Event object can tell you that *some* key is pressed and when
*some* key is released.

The following function shows you how to detect a key press event and a
key release event. The crucial thing to note is that when you press a key
down, the Event object detects *one* key down event (regardless of how long
you hold the key down). For that key that is pressed, when you release the key
is released, the Event object detects *one* key up event. 
*****************************************************************************/
void test_key_up_down()
{
    Surface surface(W, H);
	Event event;

	while (1)
	{
        int key = -1;
		if (event.poll())
        {
            if (event.type() == QUIT) break;
            else if (event.type() == KEYDOWN)
            {
                key = 1;
            }
            else if (event.type() == KEYUP)
            {
                key = 2;
            }
        }


        if (key != -1)
        {
            int x = rand() % W;
            int y = rand() % H;
            int rx = min(int(W - 1 - x), int(x));
            int ry = min(H - 1 - y, y);

            surface.lock();
            switch (key)
            {
                case 1:
                    surface.put_circle(x, y, min(rx, ry), 255, 0, 0);
                    break;
                case 2:
                    surface.put_circle(x, y, min(rx, ry), 0, 255, 0);
                    break;
            }                    
            surface.unlock();
            surface.flip();
        }
        
        delay(10);
	}
	return;
}



/*****************************************************************************
This function, test_image(), shows you how to load and "blit" an image. "Blit"
stands for "block image transfer".

The statement

	Image image("images/galaxian/GalaxianAquaAlien.gif");

creates an Image object, image, from a graphics image file.

The statement 

	Rect rect = image.getRect();

give you a Rect variable (object) with rect.x = 0, rect.y = 0 and rect.w and 
rect.h are the width and height of the image. rect is an object containing
4 variable x, y, w, h. The x in rect is called rect.x; the y in rect is called 
rect.y.

Another function in surface that is helpful is the fill() function.

	surface.fill(BLACK);

will fill the whole surface with BLACK color. This is like clearing the 
whole surface (if your background is black). If your background is red you
can paint the whole surface red like this:

	Color red = {255, 0, 0};
	surface.fill(red);

Exercise. Change the background to your favorite color.

Exercise. Make the alien bug move at twice its speed.

Exercise. Make the alien bug stop when it hits the right wall.

Exercise. Make the alien bug move backward when it hits the right wall.
Hint: Suppose this is the surface and the rect where you want to blit the 
image.

... ------------+
				|
		XXXX	|
		XXXX	|
		        |

The top-left of the rect is rect.x. The top-RIGHT of the rect is rect.x + 
rect.w.

Exercise. Make the alien bug move forward and backward between the left and 
right wall.

Exercise. Make the alien bug move in both the x and y direction within the
surface.
*****************************************************************************/
void test_image()
{
	Surface surface(W, H);
	Event event;

	Image image("images/galaxian/GalaxianAquaAlien.gif");	// loads image

    Rect rect = image.getRect();

    int speed = 5;
	int dx = speed;
    int dy = 0;
    
	while (1)
	{
		if (event.poll() && event.type() == QUIT) break;

        rect.x += dx;
        /*
          rect.x += dx;
        
        if (rect.x > 400)
        {
            dx = -1;
        }
        else if (rect.x < 0)
        {
            dx = 1;
        }
        */

        if (rect.x + rect.w >= W)
        {
            // CASE: right side of image touches the right side of surface
            dx = -speed;
        }
        else if (rect.x <= 0)
        {
            // CASE: right side of image touches the right side of surface
            dx = speed;
        }
        
		surface.lock();
		surface.fill(BLACK);
        surface.put_image(image, rect); // blit image at rect on surface
        surface.unlock();
		surface.flip();

		delay(20);
	}
	return;
}


/*****************************************************************************
This function shows you how to play sound and music.
*****************************************************************************/
void test_sound()
{
	Surface surface(W, H);
	Sound sound("sounds/laser.wav");		// create sound object from file
	Music music("sounds/GameLoop.ogg");		// create music object from file
	music.play();							// loop over music
	Event event;

	while (1)
	{
		if (event.poll() && event.type() == QUIT) break;

		if (rand() < 100) sound.play();		// play sound randomly
		delay(10);
	}
}

/*****************************************************************************
This function, helloworld(), shows you how to create an image from a font
file.

The statement

	Font font("fonts/FreeSans.ttf", 48);

creates a font object. 

The statement following statement creates an image using the font object.

	Color c = {0, 0, 255}; // color with red = 0, green = 0, blue = 255
	Image image(font.render("hello world", c));

You can of course change the string to whatever you need. The color variable
c can also be changed.

Exercise. Print a different message using a different font file, a different
color and a different size.
*****************************************************************************/
void helloworld()
{
	Surface surface(W, H);
	Event event;

	Font font("fonts/FreeMonoBold.ttf", 24);
	Color c = {0, 0, 255};
	Image image(font.render("frodo lives", c));
	Rect rect = image.getRect();

	// Initially rect has x = 0, y = 0
	// Let's move it.
	rect.x = 10;
	rect.y = 10;

	surface.lock();
	surface.put_image(image, rect);
	surface.unlock();
	surface.flip();

	while (1)
	{
		if (event.poll() && event.type() == QUIT) break;

		delay(100);
	}
	return;
}

/*****************************************************************************
To draw a filled polygon, call:

	surface.put_polygon(x, y, n, r, g, b);

where x and y are arrays of int describing the vertices (corners) of the 
polygon and n is the number of corners. The integer values r, g, b is the 
color to use. For instance to draw a red polygon with corners (10, 100), 
(20, 100), (15, 150), (10, 100), you do this:

int x[] = {10, 20, 15, 10};
int y[] = {100, 100, 150, 100};
surface.put_polygon(x, y, 4, 255, 0, 0);

Note that the polygon is filled. To draw the outline of the polygon, you 
should call

int x[] = {10, 20, 15, 10};
int y[] = {100, 100, 150, 100};
surface.put_polygon(x, y, 4, 255, 0, 0, false);

I.e. the last argument specifies whether the polygon should be filled.
*****************************************************************************/
void move(int & x, int & dx, int max)
{
	x += dx;
	if (x < 0)
	{
		x = 0;
		dx = -dx;
	}
	else if (x > max)
	{
		x = max;
		dx = -dx;
	}
}
void test_polygon(bool fill)
{
	Surface surface(640, 480);
	Event event;

	const int n = 500;

	int x[n], dx[n] = {3};
	int y[n], dy[n] = {5};
	int r = rand() % 256; 
	int g = rand() % 256;
	int b = rand() % 256;
	int dr = rand() % 3 + 1;
	int dg = rand() % 3 + 1;
	int db = rand() % 3 + 1;

	for (int i = 0; i < n; i++)
	{
		x[i] = rand() % 640;
		y[i] = rand() % 480;
	}

	for (int i = 1; i < n; i++)
	{
		dx[i] = dx[0];
		dy[i] = dy[0];
	}

	while (1)
	{
		if (event.poll() && event.type() == QUIT) break;

		for (int i = 0; i < n; ++i)
		{
			move(x[i], dx[i], 639);
			move(y[i], dy[i], 479);
		}
		move(r, dr, 255);
		move(g, dg, 255);
		move(b, db, 255);

		surface.lock();
		surface.fill(BLACK);
		surface.put_polygon(x, y, n, r, g, b, fill);
		surface.unlock();
		surface.flip();

		delay(10);
	}
}


/******************************************************************************
  You can read the x,y position of the mouse at any time.
  You can read the state of the mouse buttons at any time.
  - mouse_x(): the x-coordinate of the mouse cursor
  - mouse_y(): the y-coordinate of the mouse cursor
  - mouse_left(): true iff the left mouse button is down
  - mouse_middle(): true iff the middle mouse button is down
  - mouse_right(): true if the right mouse button is down

  Instead of read the x,y, and button states in every single game loop,
  sometimes you can to read them only when the mouse is moved or when the
  button is pressed and released, i.e., when there's a mouse motion
  or mouse button event.
  - event.type() == MOUSEMOTION is true when the mouse is moved
  - event.type() == MOUSEBUTTON is true when a mouse button is pressed or
    released.
 *****************************************************************************/
void test_mouse()
{
    const int FONTSIZE = 24;
	Surface surface(640, 480);
	Event event;
    Font font("fonts/FreeSans.ttf", FONTSIZE);
	
	while (1)
	{
	    if (event.poll() && event.type() == QUIT) break;

        std::stringstream out1;
        out1 << "x:" << mouse_x() << " y:" << mouse_y();
        Image image1(font.render(out1.str().c_str(), WHITE));
        Rect rect1 = image1.getRect();

        std::stringstream out2;
        out2 << "leftbutton:" << mouse_left()
             << " middlebutton:" << mouse_middle()
             << " rightbutton:" << mouse_right();
        Image image2(font.render(out2.str().c_str(), WHITE));
        Rect rect2 = image2.getRect();
        rect2.y = FONTSIZE + 5;
        
        surface.lock();
        surface.fill(BLACK);
        surface.put_image(image1, rect1);
        surface.put_image(image2, rect2);
        surface.unlock();
        surface.flip();

        delay(10);
    }
}
/******************************************************************************
  Instead of read the x,y, and button states in every single game loop,
  sometimes you can to read them only when the mouse is moved or when the
  button is pressed or released, i.e., when there's a mouse motion
  or mouse button event. Here's how to check for mouse motion event or mouse
  button pressed/released event:
  - event.type() == MOUSEMOTION is true when the mouse is moved
  - event.type() == MOUSEBUTTONDOWN is true when a mouse button is pressed
  - event.type() == MOUSEBUTTONUP is true when a mouse button is released
  Once the above is true, you execute:

  mouse.update(event);

  and after that you can read the mouse cursor position and the states of the
  mouse buttons when the mouse motion or mouse button press/release occurs
  using these:
  - mouse.x() -  x-coordinate of the mouse cursor
  - mouse.y() - y-coordinate of the mouse cursor
  - mouse.left() - true iff the left mouse button is pressed
  - mouse.middle() - true iff the middle mouse button is pressed
  - mouse.right() - true iff the right mouse button is pressed
 *****************************************************************************/
void test_mouse_event()
{
    const int FONTSIZE = 24;
	Surface surface(640, 480);
	Event event;
    Font font("fonts/FreeSans.ttf", FONTSIZE);
    Mouse mouse;
	
	while (1)
	{
        std::stringstream out;
	    if (event.poll())
        { 
            if (event.type() == QUIT) break;
            else if (event.type() == MOUSEMOTION)
            {
                mouse.update(event);
                out << "mouse moved";
            }
            else if (event.type() == MOUSEBUTTONDOWN)
            {
                mouse.update(event);
                out << "mouse button pressed";
            }
            else if (event.type() == MOUSEBUTTONUP)
            {
                mouse.update(event);
                out << "mouse button released";
            }
            out << " ... x,y = " << mouse.x() << ',' << mouse.y()
                << " ... buttons = "
                << mouse.left() << ','
                << mouse.middle() << ','
                << mouse.right();
        }

        if (out.str() != "")
        {
            std::cout << out.str() << std::endl;
            
            Color c = {Uint8(rand() % 50 + 200),
                       Uint8(rand() % 50 + 200),
                       Uint8(rand() % 50 + 200)};
            Image image(font.render(out.str().c_str(), c));
            Rect rect = image.getRect();
            
            surface.lock();
            surface.fill(BLACK);
            surface.put_image(image, rect);
            surface.unlock();
            surface.flip();
        }
        delay(10);
    }
}

/******************************************************************************
 This is an example on using the mouse to perform drag-n-drop.
 *****************************************************************************/
void test_drag_n_drop()
{
    const int FONTSIZE = 24;
	Surface surface(640, 480);
	Event event;
    Font font("fonts/FreeSans.ttf", FONTSIZE);
    Mouse mouse;

    int x = 100, y = 100, w = 100, h = 100;
    bool move = false; // true iff the square is moving with the mouse

    std::stringstream out;
    out << "drag-n-drop sim: click on mouse to pick up/put down";
    Color c = {255, 255, 255};
    Image helpimage(font.render(out.str().c_str(), c));
    Rect helprect = helpimage.getRect();
    
	while (1)
	{
        std::stringstream out;
	    if (event.poll())
        { 
            if (event.type() == QUIT) break;
            else if (event.type() == MOUSEMOTION)
            {
                mouse.update(event);
                if (move)
                {
                    x = mouse.x();
                    y = mouse.y();
                }
            }
            else if (event.type() == MOUSEBUTTONDOWN)
            {
                // do nothing ... pick up and put down
                // happens only when the button is released
            }
            else if (event.type() == MOUSEBUTTONUP)
            {
                mouse.update(event);
                int mousex = mouse.x();
                int mousey = mouse.y();
                if (x <= mousex && mousex <= x + w
                    && y <= mousey && mousey <= y + h)
                {
                    move = !move;
                }
            }
        }

        surface.lock();
        surface.fill(BLACK);
        if (move)
        {            
            surface.put_rect(x, y, w, h, 100, 100, 100);
        }
        else
        {
            surface.put_rect(x, y, w, h, 255, 255, 255);
        }
        surface.put_image(helpimage, helprect);
        surface.unlock();
        surface.flip();

        delay(10);
    }
}

/******************************************************************************
 This is tested only with Logictech gamepad.
 *****************************************************************************/
void test_gamepad()
{
    const int FONTSIZE = 24;
	Surface surface(640, 480);
	Event event;
    Font font("fonts/FreeSans.ttf", FONTSIZE);
    Mouse mouse;

    std::cout << "num joysticks: " << num_joysticks() << std::endl;

    Joystick js;

    std::cout << "num axes: " << js.num_axes() << std::endl;
    std::cout << "num buttons: " << js.num_buttons() << std::endl;
    
	while (1)
	{
        std::stringstream out;
	    if (event.poll())
        {
            if (event.type() == QUIT)
            {
                break;
            }
            else if (event.type() == JOYSTICKAXISMOTION)
            {
                js.update(event);
                out << "axis, value: "
                    << js.axis()
                    << ", "
                    << js.axis_value();
            }
            else if (event.type() == JOYSTICKBUTTONDOWN)
            {
                js.update(event);
                out << "button down: " << js.button();
            }
            else if (event.type() == JOYSTICKBUTTONUP)
            {
                js.update(event);
                out << "button up: " << js.button();
            }
            else if(event.type() == JOYSTICKHATMOTION)
            {
                js.update(event);
                out << "hat up,down,left,right: "
                    << js.hat_up() << ','
                    << js.hat_down() << ','
                    << js.hat_left() << ','
                    << js.hat_right();                 
            }
        }

        if (out.str() != "")
        {
            std::cout << out.str() << std::endl;
            
            Color c = {Uint8(rand() % 50 + 200),
                       Uint8(rand() % 50 + 200),
                       Uint8(rand() % 50 + 200)};
            Image image(font.render(out.str().c_str(), c));
            Rect rect = image.getRect();
            
            surface.lock();
            surface.fill(BLACK);
            surface.put_image(image, rect);
            surface.unlock();
            surface.flip();
        }
        delay(10);
    }
}


/*****************************************************************************
For our programs involving graphics and sound, the template is this:

int main(int argc, char* argv[])
{
    ... PROGRAM ...

    return 0;
}

Our main() is made up of calling various functions. This is the first time you
are actually seeing the *code* of functions. Before this, you have been 
*using* functions, i.e. *calling* the functions.

For instance the first function call is

	test_event();

When you run this program, the program will execute a function call to 
test_event(). This means that the program will look for "text_event" and 
execute the code until it sees the statement "return". Executing return
will cause the program to go back to where it came from.

After running the program, comment out the call to test_event(), uncomment
the call to test_pixel() and run the program. Etc.
*****************************************************************************/
int main(int argc, char* argv[])
{
	//freopen("CON", "w", stdout);
	//freopen("CON", "w", stderr);

	// Prints to console window
	std::cout << "hello world" << std::endl;

	//test_event();
	//test_pixel();
	//test_line();
	//test_circle();
	//test_unfilled_circle();
	//test_rect();
	//test_image();
	//helloworld();			// Of course we must have a hello world right?
	//test_keyboard();
	//test_key_up_down(); // NEW 2013
	//test_sound();
	//fancyhelloworld();		// eye candy
	//test_polygon(false);
	//test_polygon(true);

    // mouse
    //test_mouse(); // NEW 2013
    //test_mouse_event(); // NEW 2013
    //test_drag_n_drop(); // NEW 2013

    // gamepad
    //test_gamepad(); // NEW 2013
    
	return 0;
}

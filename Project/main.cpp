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
#include <algorithm>

#include "Includes.h"
#include "Constants.h"
#include "compgeom.h"
#include "Surface.h"
#include "Event.h"
#include "Stars.h"
#include "Ship.h"
#include "Laser.h"
#include "Alien.h"
#include "BlueAlien.h"
#include "Explosion.h"
#include "RedGroup.h"
#include "PurpleAlien.h"

int test_play();
void welcome_page();
void game_end(int score0, int h_score, int l_score, int m_score);

// information line
// R1       40       |       44        <= yellow x2      
// R2    41 42 43    |    45 46 47     <= red x3 per group, x2 per line
// R3 20 21 22 23 24 | 25 26 27 28 29  <= purple
// R4 30 31 32 33 34 | 35 36 37 38 39
// R5 00 01 02 03 04 | 05 06 07 08 09  <= blue
// R6 10 11 12 13 14 | 15 16 17 18 19 

int main(int argc, char* argv[])
{
    std::cout << "Galaxian_game running..." << std::endl;
    Sound basesound("sounds/GameLoop.ogg"); // 背景音乐
	

    Event event_main;

    // 分数榜
    int your_score = 0; 

    std::ifstream inFile;
    inFile.open("high_score.txt");
    if (!inFile)
    {
        std::cerr << "high score file not open. \n";
        exit(1);
    }

    std::string line;
    int l = 0;
    int high_score[3] = {0};

    while (std::getline(inFile,line))
    {
        high_score[l] = stoi(line);
        l += 1;
    }
    inFile.close();

    // 游戏过程
    while(1)
    {
        basesound.play();
        welcome_page();
        your_score = test_play();
        game_end(your_score, high_score[0], high_score[2], high_score[1]);
    }
	
    return 0;
}

int test_play()
{
    Surface surface(W, H);
    Event event;
    Sound sound("sounds/laser.wav");
    Sound explosion("sounds/explosion.wav");
    Sound warning("sounds/warning.wav");

    Ship ship;
    Laser laser;
    // Music music("sounds/GameLoop.ogg");
    // music.play();
	
    BlueAlien BlueAlien;
    PurpleAlien PurpleAlien;
    RedGroup RedGroup;
    Explosion e2_p;

    Image image("images/galaxian/GalaxianGalaxip.gif");
    Image blue("images/galaxian/GalaxianAquaAlien.gif");

    Image e1("images/galaxian/e1.png");
    Image e2("images/galaxian/e2.png");
    Image e3("images/galaxian/e3.png");
    Image e4("images/galaxian/e4.png"); 

    int score = 0;
    std::string sc = "Score: ";
    Font score_font("fonts/FreeSans.ttf", 20);

    int game_round = 1;
    std::string wv = "Wave: ";
    Font wv_font("fonts/FreeSans.ttf", 20);


    Rect rect = image.getRect();
    rect.y = 480-65;
    int max_laser_qty = ALIENQTY; // default setting of the maximum qty of laser on screen
    int speed = 5;
    int dx = speed;
    int dy = speed * -2;
    int laser_x[max_laser_qty] = {320};
    int laser_y[max_laser_qty] = {416};
    bool laser_on[max_laser_qty] = {false};
    rect.x = 320;
    int laser_index = 0;

    Rect blue_rect = blue.getRect();
    blue_rect.y = 66;
    blue_rect.x = 320;
    int alien_attack_speed = speed / 2;
    int blue_dx = alien_attack_speed;
    int blue_dy = alien_attack_speed;
    bool blue_attack = false;
    int blue_hold = 0;

    // Rect yellow_rect = yellow.getRect();

    // 锁定15帧，之内不允许再发射激光
    bool laser_delay = false;
    int laser_delay_count = 0;

    Sky background(surface);
    background.build();
	
    int alien_status[ALIENQTY]  = {1}; // normal:1; attack:2; recovey:3; dead:0
    int alien_x[ALIENQTY] = {145};
    int alien_y[ALIENQTY] = {ALIENORIY}; // ALIENORIY = alien original y value = 175
    int alien_group_speed = 2; // alien group x axis moving speed

    // 初始化外星舰队
    for (int i = 1; i < ALIENQTY; i++) 
    {
        alien_status[i]  = {1};
        if (i < 10) 
        { 
            alien_x[i] = alien_x[0]+ i * 35;
            alien_y[i] = alien_y[0];
        }
        else if (i >= 10 && i < 20)
        {
            alien_x[i] = alien_x[0] + (i - 10) * 35;
            alien_y[i] = alien_y[0] + (i / 10) * 35;
        } 
        else if (i >= 20 && i < 30)
        {
            alien_x[i] = alien_x[0] + (i - 20) * 35;
            alien_y[i] = alien_y[0] - (i / 10) * 35;
        }
        else if (i >= 30 && i < 40)
        {
            alien_x[i] = alien_x[0] + (i - 30) * 35;
            alien_y[i] = alien_y[0] - (i / 10) * 35 + 70;
        }
        else if (i >= 40 && i < 44)
        {
            if (i == 40) 
            {
                alien_x[i] = alien_x[0] + 2 * 35;
                alien_y[i] = alien_y[0] - (i / 10) * 35;
            }
            else 
            {
                alien_x[i] = alien_x[0] + (i % 10) * 35;
                alien_y[i] = alien_y[0] - (i / 10 - 1) * 35;
            }			
        }
        else if (i >= 44 && i < 48)
        {
            if (i == 44) 
            {
                alien_x[i] = alien_x[0] + 7 * 35;
                alien_y[i] = alien_y[0] - (i / 10) * 35;
            }
            else 
            {
                alien_x[i] = alien_x[0] + (i % 10 + 1) * 35;
                alien_y[i] = alien_y[0] - (i / 10 - 1) * 35;
            }			
        }
		
    }

    // 爆炸效果图的位置
    Rect e2_rect = e2.getRect();

    int alien_explosion_count[ALIENQTY] = {0};
    int alien_explosion_index[ALIENQTY] = {0};

    int attack_timing = 0;

    bool blue_laser_on[ALIENQTY] = {false};
    int blue_laser_x[ALIENQTY];
    int blue_laser_y[ALIENQTY];

    int ship_life = 3;
    bool ship_hit = false;

    // 检查是否这一轮所有的外星飞船被消灭，是否开始新一轮舰队
    bool alien_clear = true;

    int RATE = 1000/60;

    while (1) // 一个循环一帧，即16毫秒
    {
        if (event.poll() && event.type() == QUIT) break;
        
        int start = getTicks();

        std::string s = sc + std::to_string(score);
        const char* pchar = s.c_str();
        Image score_image(score_font.render(pchar, 255, 150, 150));
        Rect score_rect = score_image.getRect();
        score_rect.x = 2;
        score_rect.y = 2;

        std::string wave_r = wv + std::to_string(game_round);
        const char* p1char = wave_r.c_str();
        Image wave_image(wv_font.render(p1char, 255, 150, 150));
        Rect wave_rect = wave_image.getRect();
        wave_rect.x = 480;
        wave_rect.y = 445;

        laser_delay_count += 1;
        alien_clear = true;

        // 外星飞船的所有事情
        for (int i = 0; i < ALIENQTY; i++) // all events, related to blue alien spaceships
        {
            if (alien_clear && alien_status[i] != 0) alien_clear = false;
            if (alien_explosion_index[i] == 1) alien_explosion_count[i] += 1;
            if (alien_explosion_count[i] >= 60) // explosion image stays in screen for 1 second.
            {
                alien_explosion_count[i] = 0;
                alien_explosion_index[i] = 0;
            } 

            // alien_status:  normal:1; attack:2; recovey:3; dead:0
            if (alien_status[i] == 1 && attack_timing >= 300)
            {
                if (i < 40 && rand() % 5 == 0) alien_status[i] = 2; // every 5 seconds, 1/5 of remaining alien ships go to attack mode
                if (i == 40 && rand() % 7 == 0)  // elite group has 1/7 chance to attack
                {
                    for (int i = 40; i <= 43; i++) if (alien_status[i] == 1) alien_status[i] = 2;
                }
                if (i == 44 && rand() % 7 == 0) 
                {
                    for (int i = 44; i <= 47; i++) if (alien_status[i] == 1) alien_status[i] = 2;
                }
            } 

            if (alien_status[i] != 0 && attack_timing % 120 == 60)
            {
                if (rand() % 14 == 0) // every 2 seconds, 1/14 of remaining alien ships fire laser
                {
                    blue_laser_on[i] = true;
                    blue_laser_x[i] = alien_x[i] + 16;
                    blue_laser_y[i] = alien_y[i] + 32;
                }
            }

            if (blue_laser_on[i])
            {
                blue_laser_y[i] += 4; // alien lasers go downwards
                if (blue_laser_x[i] > (rect.x - 1) && blue_laser_x[i] < (rect.x + 32) && blue_laser_y[i] > (rect.y - 20) && blue_laser_y[i] < (rect.y + 32)) 
                {
                    ship_hit = true; // alien laser hit
                    blue_laser_on[i] = false;
                }
            }
 
            if (alien_status[i] == 2 && alien_x[i] > (rect.x - 32) && alien_x[i] < (rect.x + 32) && alien_y[i] > (rect.y - 32) && alien_y[i] < (rect.y +32)) 
            { 
                ship_hit = true; // alien crashs into ship
                alien_status[i] = 0;
            }

            if (blue_laser_y[i] > 460) 
            {
                blue_laser_y[i] = 0;
                blue_laser_on[i] = false; // alien lasers vanish after hitting the bottom
            }

            // 更新本帧中每一个外星飞船的位置
            if (i < 10 && i > 0) 
            {				
                alien_x[i] = alien_x[0] + i * 35; // alien ships follow the left top corner
                if (alien_status[i] == 1) alien_y[i] = ALIENORIY;  // recovery mode final destination
            }
            else if (i >= 10 && i < 20)
            {
                alien_x[i] = alien_x[0] + (i - 10) * 35; // alien ships follow the left top corner
                if (alien_status[i] == 1) alien_y[i] = ALIENORIY + 35;// recovery mode final destination for 2nd row
            }
            else if (i >= 20 && i < 30)
            {
                alien_x[i] = alien_x[0] + (i - 20) * 35; // alien ships follow the left top corner
                if (alien_status[i] == 1) alien_y[i] = ALIENORIY - 70;// recovery mode final destination for 3rd row
            }
            else if (i >= 30 && i < 40)
            {
                alien_x[i] = alien_x[0] + (i - 30) * 35; // alien ships follow the left top corner
                if (alien_status[i] == 1) alien_y[i] = ALIENORIY - 35;// recovery mode final destination for 4th row
            }
            else if (i >= 40 && i < 44)
            {
                if (i == 40) 
                {
                    alien_x[i] = alien_x[0] + 2 * 35;
                    if (alien_status[i] == 1) alien_y[i] = ALIENORIY - (i / 10) * 35;
                }
                else 
                {
                    alien_x[i] = alien_x[0] + (i % 10) * 35;
                    if (alien_status[i] == 1) alien_y[i] = ALIENORIY - (i / 10 - 1) * 35;
                }			
            }
            else if (i >= 44 && i <= 47)
            { 
                if (i == 44) 
                {
                    alien_x[i] = alien_x[0] + 7 * 35;
                    if (alien_status[i] == 1) alien_y[i] = ALIENORIY - (i / 10) * 35;
                }
                else 
                {
                    alien_x[i] = alien_x[0] + (i % 10 + 1) * 35;
                    if (alien_status[i] == 1) alien_y[i] = ALIENORIY - (i / 10 - 1) * 35;
                }			
            }

            
            // alien_status:  normal:1; attack:2; recovey:3; dead:0
            if (alien_status[i] == 2) alien_y[i] += alien_attack_speed; // alien ships in attack mode, moving downwards
            if (alien_y[i] > 480-3) // attack mode ships hitting the bottom
            {
                alien_status[i] = 3;
                alien_y[i] = 0;
            }
            if (alien_status[i] == 3) // recovery mode
            {
                alien_y[i] += alien_attack_speed;
                if (i < 10 && alien_y[i] >= ALIENORIY) alien_status[i] = 1;
                if (i >= 10 && i < 20 && alien_y[i] >= (ALIENORIY + 35)) alien_status[i] = 1;
                if (i >= 20 && i < 30 && alien_y[i] >= (ALIENORIY - 70)) alien_status[i] = 1;
                if (i >= 30 && i < 40 && alien_y[i] >= (ALIENORIY - 35)) alien_status[i] = 1;
                if (i == 40 && alien_y[40] >= (ALIENORIY - 4*35)) 
                {
                    for (int i = 40; i <= 43; i++) if (alien_status[i] != 0) alien_status[i] = 1;					
                }
                if (i == 44 && alien_y[44] >= (ALIENORIY - 4*35)) 
                {
                    for (int i = 44; i <= 47; i++) if (alien_status[i] != 0) alien_status[i] = 1;					
                }
            }

        } // ---------all events, related to blue alien spaceships------------

        if (alien_clear) // all alien dead
        {
            alien_attack_speed += 1; // new round: alien speeds up
            game_round += 1;

            // 重置所有飞船状态
            for (int i = 0; i < ALIENQTY; i++) alien_status[i] = 1;
            // alien_clear = false;
            // alien_x[0] = 145;
            
            // 不重置y的话，00船连带新舰队会刷新在死的位置
            alien_y[0] = ALIENORIY;
        }
		
        if (attack_timing >= 300) attack_timing = 0;
        else attack_timing += 1 ;

        if (laser_delay_count > LASER_FRAME) 
        {
            laser_delay_count = 0;
            laser_delay = false;
        }		

        alien_x[0] += alien_group_speed;

        // when alien ship reaches the left or right boundary
        if (alien_x[0] > 289 || alien_x[0] < 1) alien_group_speed = alien_group_speed * -1; 
        // red_x = alien_x[0] + 70;		
		
        blue_rect.x += blue_dx; // ship reaches left or right boundary
        if (blue_rect.x > W - 33)
        {
            blue_rect.x = W - 33;
            blue_dx = - blue_dx;
        }
        else if (blue_rect.x < 0)
        {
            blue_rect.x = 0;
            blue_dx = - blue_dx;
        }	

        // 左右按键，玩家不飞出窗口
        KeyPressed keypressed = get_keypressed();
        if (keypressed[LEFTARROW])
        {
            rect.x -= dx;
            if (rect.x < 0)
            {
                rect.x = 0;
            }
        }
        if (keypressed[RIGHTARROW])
        {
            rect.x += dx;
            if (rect.x > 608)
            {
                rect.x = 608;
            }			
        }

        // 比较所有的激光和所有的外星飞船的位置
        for (int i = 0; i < max_laser_qty; i++) // i for player laser
        {		
            for (int j = 0; j < ALIENQTY; j++) // laser collision, j for alien ship
            {
                if (laser_on[i] && alien_status[j] != 0 // 激光存在 && 外星飞船不死
                    && laser_x[i] >= (alien_x[j]-1) && laser_x[i] <= (alien_x[j] + 32) && laser_y[i] >= alien_y[j] && laser_y[i] <= (alien_y[j] + 32))
                { // 检查飞船和激光的位置是否重合
                    explosion.play();
                    alien_status[j] = 0; // normal:1; attack:2; recovey:3; dead:0
                    laser_on[i] = false;

                    // 分数计算
                    if (j < 20) score += 30;
                    else if (j < 40) score += 40;
                    else if (j == 40 || j == 44) score += 60;
                    else score += 50;
                    
                    alien_explosion_index[j] = 1;
                    // j = ALIENQTY; 
                    e2_rect.x = alien_x[i]; 
                    break; // one laser can only kill one alienship
                }
            }

            // 激光飞出窗口，关闭激光
            if (laser_on[i] == true)
            {
                laser_y[i] = laser_y[i] + dy;
                if (laser_x[i] < 0 || laser_x[i] > 624 || laser_y[i] < 0 || laser_y[i] > 448) laser_on[i] = false;
            }

			
        }

        // 玩家发射激光
        if (keypressed[SPACE] && laser_delay == false)
        {									
            sound.play();
            laser_on[laser_index] = true;		
            blue_hold += 1;
            // laser(rect.x, rect.y);
            // Rect 为玩家坐标，激光在玩家前方中间，占2*20像素
            laser_x[laser_index] = rect.x + 15;
            laser_y[laser_index] = rect.y - 22;
            laser_index += 1;
            if (laser_index >= max_laser_qty) laser_index = 0;
            laser_delay = true;	// 锁定15帧，之内不允许再发射激光
        }	
		
        // =========== Frame update section ============== //
        // 以上是数据整理，以下将整理的数据画出来
        surface.lock();
        surface.fill(BLACK);
        background.draw();
        surface.put_image(score_image, score_rect);
        surface.put_image(wave_image, wave_rect);

        // RedGroup.draw(red_x,red_y,true);

        if (!ship_hit) ship.draw(rect.x, rect.y); // ship hit displays explosion, normal status displays ship
        else
        {
            warning.play();
            ship_life--;
            // 爆炸效果图
            e2_p.draw(rect.x,rect.y,2);
            ship_hit = false;
        }

        // 没命了，进入结算界面
        if (ship_life <= 0) break;	

        // 剩几条命，就画几个小飞机
        for (int i = 0; i < ship_life; i++)
        {
            ship.draw( 2 + i * 35, (480 - 35)); // left bottom corner displays remaining life count
        }

        for (int i = 0; i < max_laser_qty; i++)
        {							
            if (laser_on[i] == true) laser.draw(laser_x[i],laser_y[i], false); // draw remaining valid laser on scoreen
        }
		
        for (int i = 0; i < ALIENQTY; i++) // draw alien ship and alien laser on screen
        {
            // alien_status:  normal:1; attack:2; recovey:3; dead:0
            if (alien_status[i] != 0) 
            {
                if (i < 20) BlueAlien.draw(alien_x[i],alien_y[i]);
                else if (i < 40) PurpleAlien.draw(alien_x[i],alien_y[i]);

                // RedGroup，1打印旗舰，0打印护卫红舰
                else if ( (i == 40) || (i == 44) ) RedGroup.draw(alien_x[i],alien_y[i],false);
                else RedGroup.draw(alien_x[i],alien_y[i],true);
            }
            else if (alien_explosion_index[i] != 0)
            {
                // 60表示60帧，为爆炸效果持续时间（1秒）
                if (alien_explosion_count[i] < 60) e2_p.draw(alien_x[i],alien_y[i],2);
            }
            if (blue_laser_on[i]) laser.draw(blue_laser_x[i], blue_laser_y[i], true);
        }

        surface.unlock();
        surface.flip();		

        int end = getTicks();
        int dt = RATE - end + start;

        // std::cout << alien_status[44] << std::endl;
        if (dt > 0) delay(dt); // delay current frame, make it 60 fps
		
    }




    return score;
}


void welcome_page()
{	
    Font font("fonts/FreeMonoBold.ttf", 60);
    Image text(font.render("Galaxian", 200, 0, 0));

    Font name_("fonts/FreeMonoBold.ttf", 25);
    Image name(name_.render("by Yijun Wu", 0, 150, 0));

    Font instruction("fonts/FreeMono.ttf", 30);
    Image info(instruction.render("Press SPACE to Start", 200, 200, 0));

    Surface surface(W, H);
    Event event_w;


    Rect rect_text = text.getRect();
    Rect name_text = name.getRect();
    Rect info_text = info.getRect();

    Sky background(surface);
    background.build();

    rect_text.y = H / 2 - (rect_text.h / 2) - 100; 
    rect_text.x = W / 2 - (rect_text.w / 2); 

    name_text.y = H / 2 - (name_text.h / 2) - 50; 
    name_text.x = W / 2 - (name_text.w / 2); 

    info_text.y = H / 2 - (info_text .h / 2) + 120; 
    info_text.x = W / 2 - (info_text .w / 2); 

    int flash_count = 0;

    while (1)
    {
        int start = getTicks();
        if (event_w.poll() && event_w.type() == QUIT) break;		
		
        KeyPressed keypressed = get_keypressed();
        if (keypressed[SPACE]) break;

        flash_count++;
		
        // std::cout << "looping" << std::endl;
        surface.lock();        
        surface.fill(BLACK);                               
        // galaxy.draw();      
        background.draw();                     
        surface.put_image(text, rect_text); 
        surface.put_image(name, name_text);  

        // 每75帧，显示60帧
        if (flash_count > 15) surface.put_image(info, info_text);  
        if (flash_count > 75) flash_count = 0;
		
        surface.unlock();
        surface.flip();

        int end = getTicks();
        int dt = 1000/60 - end + start; // 每一秒60张图

        // std::cout << dt << std::endl;
        if (dt > 0) delay(dt); // delay current frame, make it 60 fps

    }
    return;
}

void game_end(int score0, int h_score, int l_score, int m_score)
{
// 	Font score_1("fonts/FreeMonoBold.ttf", 45);
//     Image score_2(score_1.render("Your Score is: ", 200, 200, 0));

    Font new_high_f("fonts/FreeSans.ttf", 30);		
    Image new_high(new_high_f.render("You've hit a historic high score!", 200, 200, 0));
    Rect new_high_r = new_high.getRect();
    new_high_r.y = H / 2 - (new_high_r.h / 2) - 200; 
    new_high_r.x = W / 2 - (new_high_r.w / 2);

    Font new_rec_f("fonts/FreeSans.ttf", 30);		
    Image new_rec(new_rec_f.render("Your score reaches top 3!", 200, 200, 0));
    Rect new_rec_r = new_rec.getRect();
    new_rec_r.y = H / 2 - (new_rec_r.h / 2) - 200; 
    new_rec_r.x = W / 2 - (new_rec_r.w / 2);


    std::string score_t = "Your Score is: ";
    Font score_f("fonts/FreeSans.ttf", 25);
	
    std::string score3 = score_t + std::to_string(score0);
    const char* p2char = score3.c_str();
    Image score_image4(score_f.render(p2char, 200, 200, 0));
    Rect score_r = score_image4.getRect();
    score_r.y = H / 2 - (score_r.h / 2) - 125; 
    score_r.x = W / 2 - (score_r.w / 2);


    Font over("fonts/FreeMonoBold.ttf", 55);
    Image game(over.render("Game Over", 200, 0, 0));

    Font over2("fonts/FreeMonoBold.ttf", 22);
    Image restart(over2.render("Wait for next round starting...", 200, 200, 0));

    Surface surface(W, H);
    Event event;
    Rect over_text = game.getRect();
    Rect rest_text = restart.getRect();	
    // Rect score_text = score_2.getRect();

    // score_text.y = H / 2 - (score_text.h / 2) - 250; 
    // score_text.x = W / 2 - (score_text.w / 2); 

    over_text.y = H / 2 - (over_text.h / 2) - 50; 
    over_text.x = W / 2 - (over_text.w / 2); 

    rest_text.y = H / 2 - (rest_text.h / 2) + 100; 
    rest_text.x = W / 2 - (rest_text.w / 2); 

    int RATE = 1000/60;
    int ending = 0;

    while (1)
    {
        int start = getTicks();
		
        ending++;
        if (event.poll() && event.type() == QUIT) break;
		
        // std::cout << "looping" << std::endl;
        surface.lock();        
        surface.fill(BLACK);                               
        // galaxy.draw();      
        // background.draw();   
        if (score0 > h_score)
        {
            surface.put_image(new_high, new_high_r);  
        }                  
        else if (score0 >= l_score)
        {
            surface.put_image(new_rec, new_rec_r);  
        }
        surface.put_image(game, over_text); 
        surface.put_image(restart, rest_text); 
        surface.put_image(score_image4, score_r); 
		
        surface.unlock();
        surface.flip();

        // restart game in 5 seconds
        if (ending >= 300)
        {
            ending = 0;
            break;
        }

        int end = getTicks();
        int dt = RATE - end + start;

        // std::cout << dt << std::endl;
        if (dt > 0) delay(dt); // delay current frame, make it 60 fps

    }

    if (score0 > l_score)
    {
        std::vector<int> rank = {h_score,m_score,score0};
        std::sort(rank.begin(),rank.end(),std::greater<int>() );
		
        std::ofstream outFile;
        outFile.open("high_score.txt", std::ofstream::out | std::ofstream::trunc); 
        if (!outFile) { 
            std::cerr << "unable to open high_score.txt";
            exit(1); 
        }

        for (int i = 0; i < 3; i++) { 
            outFile << rank[i] << std::endl;
        }

        outFile.close(); 

    }

    return;
}

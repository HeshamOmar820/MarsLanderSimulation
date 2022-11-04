#include <SFML/Audio.hpp>
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <list>
using namespace sf;

float landingSpeed  = 10;
float g=3.721;
float l[5] = {0,1,2.5,3.721,10.5};
float fuel = 500;
//float a;
struct Acceleration
{ float x,y;} a;

struct Velocity
{ float x,y;} v;

struct Obstacle
{ int x,y;}  o[10];
int frame = 0;
//v.y = 10;
//float v = 5;
int level=0;
int angle = 0;
bool isLanded = false;


int N=50,M=50;
int size=16;
int w = size*N;
int h = size*M;
//flags
bool isAlive=true;
bool isFed;
//num is snake length
int dir,num=4;



struct Craft
{ int x,y;} c;




//void Tick()
// {
//     isFed = false;
//    for (int i=num;i>0;--i)
//     {s[i].x=s[i-1].x; s[i].y=s[i-1].y;}
//    //setting directions
//    if (dir==0) s[0].y+=1;//down
//    if (dir==1) s[0].x-=1;//left
//    if (dir==2) s[0].x+=1;//right
//    if (dir==3) s[0].y-=1;//up
//
//    //ate fruit
//    if ((s[0].x==f.x) && (s[0].y==f.y))
//     {num++; f.x=rand()%N; f.y=rand()%M; isFed=true;}
//
//    if (s[0].x>N) s[0].x=0;  if (s[0].x<0) s[0].x=N;
//    if (s[0].y>M) s[0].y=0;  if (s[0].y<0) s[0].y=M;
//
//    //when eat itself
//    for (int i=1;i<num;i++)
//    if (s[0].x==s[i].x && s[0].y==s[i].y)  {
//        isAlive=false;
//    }
////     if (s[0].x==s[i].x && s[0].y==s[i].y)  num=i;
// }

int main()
{



    srand(time(0));

    RenderWindow window(VideoMode(w, h), "Mars Landing!");
    window.setFramerateLimit(60);

//   RectangleShape craft(Vector2f(3*size,5*size));
//   craft.setOrigin(craft.getGlobalBounds().width/2,craft.getGlobalBounds().height/2);
//    c.x = window.getSize().x/2;
    c.y = window.getSize().y/2;





//RectangleShape ground(Vector2f(window.getSize().x*5, 20));
//   craft.setOrigin(craft.getGlobalBounds().width/2,craft.getGlobalBounds().height/2);
//    c.x = window.getSize().x/2;
//    c.y = window.getSize().y/2;

    Texture tex1, tex2, tex3, texBack[4];
    tex1.loadFromFile("images/newobs.png");
    tex2.loadFromFile("images/white rocket2.png");
    tex3.loadFromFile("images/land.png");
    for(int i=0; i<4; i++)
    texBack[i].loadFromFile("images/s"+std::to_string(i)+".png");
    Sprite sObstacle(tex1), craft(tex2), ground(tex3), background(texBack[frame]);
    background.setScale(0.27,0.27);
    craft.setScale(0.08,0.08);
   craft.setOrigin(craft.getGlobalBounds().width/2,craft.getGlobalBounds().height/2);

ground.setScale(0.5,0.5);
   ground.setOrigin(ground.getGlobalBounds().width/2,0);

    Font font;
    font.loadFromFile("fonts/arial.ttf");
    Text t1("", font, 24), t2("", font, 24), t3("", font, 24), t4("", font, 24);
t4.setString("Successful");

//
    Clock clock;
    float timer=0, delay=0.2;
//
//    f.x=10;
//    f.y=10;
//    back.setLoop(true);
//    back.play();
c.x = w/2;

for (int i=0;i<10;i++)
    {
        o[i].y = rand()%120 + h - 120;
        o[i].x=rand()%w;
//      o[i].y=o[i].y-dy;
//      if (o[i].y>533) {o[i].y=0; o[i].x=rand()%400;}
    }

    while (window.isOpen())
    {


//        delay=0.2-0.1*std::log10(num-3);
//        if(delay<0.1) delay = 0.1; //max speed
////        std::cout<<"delay is: "<<delay<<"   "<<num<<std::endl;
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;
//
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
            if(!isLanded){
                if (Keyboard::isKeyPressed(Keyboard::Up)&& level!=4) ++level;
                if (Keyboard::isKeyPressed(Keyboard::Down)&&level!=0) --level;
                if (Keyboard::isKeyPressed(Keyboard::Right)&& angle!=45) angle++;
                if (Keyboard::isKeyPressed(Keyboard::Left)&& angle!=-45) angle--;

            }
        }
        if (fuel<=0) {
                fuel=0;
        level=0;}
//


//        if (Keyboard::isKeyPressed(Keyboard::R)&&!isAlive) {
//            isAlive=true;
//            num=4;
//            for (int i=num;i>0;--i)
//     {s[i].x=s[i-1].x; s[i].y=s[i-1].y;}
//            window.close();
//            over.stop();
//            main();
//        }
//
        if (c.y + craft.getGlobalBounds().height < window.getSize().y -60){
        if (timer>delay) {
            a.y=g-l[level]*std::cos(angle*3.14159/180);
            c.y += v.y*timer + 0.5*a.y*std::pow(timer,2);
            v.y += a.y*timer;

            a.x = l[level]*std::sin(angle*3.14159/180);
            c.x += v.x*timer + 0.5*a.x*std::pow(timer,2);
            v.x += a.x*timer;
            fuel -= l[level] * timer;
//            std::cout<<std::sin(angle*3.14159/180)<<std::endl;
//            std::cout<<c.x<<"       "<<w+craft.getOrigin().x<<"     "<<craft.getOrigin().x<<std::endl;

            if(c.x>= w+craft.getOrigin().x )
            {
//                std::cout<<"we here"<<std::endl;
                c.x= -craft.getOrigin().x;
                frame++;
//                if(frame>3) frame =0;
            }
            if(c.x< -craft.getOrigin().x)
            {
//                std::cout<<"we there"<<std::endl;
                c.x=w+craft.getOrigin().x;
                frame--;
                if(frame<0) frame=3;
            }
            if(c.y<= craft.getOrigin().y) c.y=craft.getOrigin().y;

            timer = 0;
        } //ticking
        }else{

            if(v.y > landingSpeed || angle != 0) t4.setString("Failure");
//            if(v.y <= 10) t4.setString("Successful");

            a.x=0; a.y=0;
            v.x=0; v.y=0;
            isLanded = true;
        }

        craft.setPosition(c.x,c.y);
        craft.rotate(angle-craft.getRotation());
        ground.setPosition(w/2, h-60);

        t1.setString("Velocity  Vertical : " + std::to_string(v.y) + " m/s"+"   Horizontal: " +std::to_string(v.x) + " m/s");
        t2.setString("Acceleration  Vertical : " + std::to_string(a.y) + " m/s^2"+"   Horizontal: " +std::to_string(a.x) + " m/s^2");
        t3.setString("Power Level: " + std::to_string(level)+ "     Angle: " + std::to_string(angle)+" degree   " + "Fuel: " + std::to_string(fuel));
        t2.setPosition(0,50);
        t3.setPosition(0,100);
        t4.setPosition(w/2,h/2);

    window.clear(Color::Blue);

    background.setTexture(texBack[frame]);
    window.draw(background);
        for (int i=0;i<10;i++)
    {
    sObstacle.setPosition(o[i].x,o[i].y);
    window.draw(sObstacle);
    }


    window.draw(ground);
    window.draw(craft);
    window.draw(t1);
    window.draw(t2);
    window.draw(t3);
    if(isLanded)
    window.draw(t4);


    window.display();
    }
    return 0;
}

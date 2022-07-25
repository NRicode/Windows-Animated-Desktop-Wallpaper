#include <iostream>
#include <SFML/Graphics.hpp>

#include "AnimatedGIF.h"
#include "winapi.h"
#include "setwallpaper.h"
#include "initialization.h"

int main(int argc, char** argv)
{
    int fps;
    if (!initialize(&fps)) {
        return 0;
    }

    AnimatedGIF gif("source.gif");
    sf::Vector2i gifsize = gif.getSize();

    float sw = getScreenWidth();
    float sh = getScreenHeight();
    float HeightToWidthRatio = sh / sw;

    float rx = gifsize.x;
    float ry = gifsize.x * HeightToWidthRatio;

    //resolution is set to match the gif's resolution to save resource
    sf::RenderWindow window(sf::VideoMode(rx,ry), "gifplayer", sf::Style::None);

    //since.gif files don't have a constant framerate, this framerate setting will be
    //free for the user to modify, just make sure that the framerate is as high as the
    //.gif average framerate or higher. setting this lower will save more gpu usage
    
    window.setFramerateLimit(fps);

    //set size is the window's physical size on screen
    window.setSize(sf::Vector2u(sw, sh));
    window.setPosition(sf::Vector2i(0, 0));

    float spritescale = (float)rx / (float)gifsize.x;

    //if there is space still available on vertical axis, we try to zoom in more to fit the screen
    if (spritescale * gifsize.y < ry) {

        spritescale = (float)ry / (float)gifsize.y;

    }

    sf::Sprite sprite;
    sprite.setScale(spritescale, spritescale); //this will clip the gif, but it's fine because it will be fitted to the center of the screen
  
    float spritescaledwidth = gifsize.x * spritescale;
    float spritescaledheight = gifsize.y * spritescale;
    sprite.setPosition(rx / 2 - spritescaledwidth / 2, ry / 2 - spritescaledheight / 2); //center the gif on screen
    
    setAsWallpaper(window.getSystemHandle());

    while (window.isOpen())
    {
        
       window.draw(sprite);
       sf::Event event;
       while (window.pollEvent(event))
       {

           if (event.type == sf::Event::Closed) {

               window.close();

           }

       }

       //since the window is a wallapaper, it will not receive window messages, we need to get raw input
       if (GetAsyncKeyState(VK_SHIFT) < 0 && GetAsyncKeyState(VK_F1) < 0) {

           window.close();

       }

       //we only want to redraw the window when the .gif frame updates to save resource
       if (gif.update(sprite)) {
           
           window.draw(sprite);

       }

       window.display(); //window.display is where the rendering & loop delay is done
       
    }

    restoreWallpaper();
    
    return 0;
}
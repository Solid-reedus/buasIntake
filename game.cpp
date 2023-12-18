#include "game.h"
#include "surface.h"
#include <cstdio> //printf

namespace Tmpl8
{
	void Game::Init()
	{
	}
	
	void Game::Shutdown()
	{
	}

	Surface image("assets/ball.png");

	void Game::Tick(float deltaTime)
	{
        // clear the graphics window
        screen->Clear(0);
        // draw a grid
        for (int x = 15; x < 800; x += 16)
        {
            for (int y = 6; y < 480; y += 12)
            {
                Pixel p = image.GetBuffer()[x / 16 + (y / 12) * 50];
                int red = p & 0xff0000;
                int green = p & 0x00ff00;
                int blue = p & 0x0000ff;
                screen->Bar(x, y, x + 12, y + 2, red);
                screen->Bar(x, y + 4, x + 12, y + 6, green);
                screen->Bar(x, y + 8, x + 12, y + 10, blue);
            }
        }
	}
};
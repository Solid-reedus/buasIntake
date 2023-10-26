#include "BaseHeader.h"
#include "UIBaseHeader.h"

#include "MenuScene.h"
#include "GameplayScene.h"

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
SDL_Texture* gTexture = nullptr;
TTF_Font* gFont = nullptr;

MenuScene menuScene;
GameplayScene gameplayScene;

enum GameScene
{
    none_GameScene,
    menu,
    gameplay
};

enum PopupScreen
{
    none_PopupScreen,
    settings,
    load,
    save,
};

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;

static bool quitGame = false;

GameScene gameScene = gameplay;

bool Init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    gWindow = SDL_CreateWindow("lords and castles", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (gWindow == NULL)
    {
        printf("unable to make window: %s\n", SDL_GetError());
        return false;
    }
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

    if (TTF_Init() == -1)
    {
        printf("TTF_OpenFont failed! TTF_Error: \n");
        return false;
    }


    // defines global font 
    gFont = TTF_OpenFont("mcFont.ttf", 24);

    if (!gFont)
    {
        printf("gFont is indefined");
        return false;
    }

    return true;
}

void Close()
{
    TTF_CloseFont(gFont);
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gFont = nullptr;
    gRenderer = nullptr;
    gWindow = nullptr;
    TTF_Quit();
    SDL_Quit();
}

int main(int argc, char* args[])
{
    if (Init())
    {
        while (!quitGame)
        {
            switch (gameScene)
            {
            case menu:
            {
                menuScene.Init(&quitGame, gRenderer, gFont);
                break;
            }

            case gameplay:
            {
                gameplayScene.Init(&quitGame, gRenderer, gFont);
                break;
            }

            case none_GameScene:
            {
                printf("Error: No gameScene selected.\n");
                break;
            }
            default:
                break;
            }
        }

        // Free resources and quit SDL
        Close();
    }

    return 0;
}

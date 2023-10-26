#ifndef I_SCENE

#define I_SCENE
#include "BaseHeader.h"
#include "UIBaseHeader.h"

class IScene {
    public:
    virtual void Update() = 0;
    virtual bool Init(bool *m_quitGame, SDL_Renderer* m_renderer, TTF_Font* m_font) = 0;
    virtual void Clear() = 0;
    virtual void RenderScreen() = 0;
};

#endif
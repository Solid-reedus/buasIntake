#include "MenuScene.h"

namespace Tmpl8
{

	MenuScene::MenuScene(Surface* m_surface)
	{
		surface = m_surface;
		printf("current scene is menu \n");


		// load ui
		// init foreach button a lambda/funtion
		// init click events for the scene
		
		
		
		//rotatingGun = new Sprite(new Surface("assets/aagun.tga"), 36);
		//frame = 0;
	}

	MenuScene::~MenuScene()
	{

	}

	void MenuScene::InitScene()
	{

	}

	void MenuScene::Update()
	{
		surface->Print("hello world", 2, 2, 0xffffff);


		// draw a sprite
		//rotatingGun->SetFrame(frame);
		//rotatingGun->Draw(surface, 100, 100);
		//if (++frame == 36) frame = 0;
	}


	void MenuScene::Delete()
	{

	}

}
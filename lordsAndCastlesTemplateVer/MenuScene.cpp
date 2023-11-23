#include "MenuScene.h"

namespace Tmpl8
{

	MenuScene::MenuScene(Surface* m_surface)
	{
		surface = m_surface;
		mouseBtnInput = 0;
		mouseX = 0;
		mouseY = 0;

		printf("current scene is menu \n");

		testBtn = Button();

		InitScene();

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
		//testBtn = Button({100, 500, 200, 100}, 0xff00ff, surface, "test", 0x00ffff);
		testBtn = Button({100, 500, 200, 100}, 0xff0044, surface);


		menuClickEvents += [&]()
		{
			if (mouseBtnInput == 1)
			{
				testBtn.OnClick(mouseX, mouseY);
			}
		};

		testBtn.event += []()
		{
			printf("click \n");
		};


	}

	void MenuScene::KeyDown(int key)
	{

	}

	void MenuScene::MouseDown(int m_button, int m_x, int m_y)
	{
		mouseBtnInput = m_button;
		mouseX = m_x;
		mouseY = m_y;
		menuClickEvents.Invoke();
	}

	void MenuScene::Update()
	{

		surface->Print("hello world", 2, 2, 0xffffff);

		surface->Box(100, 100, 300, 200, 0xffffff);
		surface->Bar(400, 400, 700, 500, 0xffffff);

		testBtn.RenderBtn();

		// draw a sprite
		//rotatingGun->SetFrame(frame);
		//rotatingGun->Draw(surface, 100, 100);
		//if (++frame == 36) frame = 0;
	}


	void MenuScene::Delete()
	{

	}

}
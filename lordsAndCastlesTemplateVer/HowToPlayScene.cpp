#include "HowToPlayScene.h"

namespace Tmpl8
{
	HowToPlayScene::HowToPlayScene(Surface* p_ptrSurface, Game* p_ptrGame)
	{
		m_ptrSurface = p_ptrSurface;
		m_ptrGame = p_ptrGame;
		m_mouseBtnInput = 0;
		m_mouseX = 0;
		m_mouseY = 0;

		m_GoToMenubtn = Button({ 50, 50, 200, 75 }, k_grey, m_ptrSurface, "go back to menu", 2, k_red);
	}

	HowToPlayScene::~HowToPlayScene()
	{

	}

	void HowToPlayScene::InitScene()
	{
		// init foreach button a lambda/funtion
		#pragma region init button events

		m_HowToPlayClickEvents += [&]()
		{
			if (m_mouseBtnInput == 1)
			{
				m_GoToMenubtn.OnClick(m_mouseX, m_mouseY);
			}
		};

		#pragma endregion


				// init click events for the scene
		#pragma region add buttons to the scene events

		m_GoToMenubtn.event += [&]()
		{
			m_ptrGame->ChangeScene(menuScn);
		};

		#pragma endregion
	}

	void HowToPlayScene::DrawScrollBar()
	{
		m_ptrSurface->Bar(ScreenWidth - 60, 100, ScreenWidth - 40, ScreenHeight - 100, k_gold);

		// 100 (start pos) + the max value * how close relativeHeight is to the max height
		int thumbPosition = 100 + ((ScreenHeight - 110) - 110) * static_cast<float>(-relativeHeight) / maxHeight;
		m_ptrSurface->Bar(ScreenWidth - 70, thumbPosition, ScreenWidth - 30, thumbPosition + 20, k_grey);
	}


	void HowToPlayScene::Update(float p_deltaTime)
	{
		DrawScrollBar();
		m_ptrSurface->PrintScaled("how to play", ScreenWidth / 2 - 100, relativeHeight + 50, k_gold, 3);

		m_ptrSurface->PrintScaled("move around the map with wasd", 100, relativeHeight + 200, k_gold, 3);
		m_ptrSurface->PrintScaled("you can select what you want to build by", 100, relativeHeight + 300, k_gold, 3);
		m_ptrSurface->PrintScaled("clicking on one of these images in your UI bar", 100, relativeHeight + 320, k_gold, 3);

		uiImage.Draw(m_ptrSurface, 100, relativeHeight + 350);

		m_ptrSurface->PrintScaled("on the bottom right you can see your stats", 100, relativeHeight + 600, k_gold, 3);
		m_ptrSurface->PrintScaled("the green number is your popularity", 100, relativeHeight + 620, k_gold, 3);
		m_ptrSurface->PrintScaled("when you dont have any food it will go down", 100, relativeHeight + 640, k_gold, 3);
		m_ptrSurface->PrintScaled("if it hits 0 your game over", 100, relativeHeight + 660, k_gold, 3);

		m_ptrSurface->PrintScaled("you can produce food by placing buildings", 100, relativeHeight + 710, k_gold, 3);
		m_ptrSurface->PrintScaled("make sure to make woodcutters, otherwise you wont", 100, relativeHeight + 730, k_gold, 3);
		m_ptrSurface->PrintScaled("be able to make any buildings", 100, relativeHeight + 750, k_gold, 3);
		
		m_ptrSurface->PrintScaled("you will also need to build houses in order", 100, relativeHeight + 800, k_gold, 3);
		m_ptrSurface->PrintScaled("to occupy the building", 100, relativeHeight + 820, k_gold, 3);
		
		uiStats.Draw(m_ptrSurface, 300, relativeHeight + 860);

		m_ptrSurface->PrintScaled("try to build your kingdom!", 100, relativeHeight + 1100, k_gold, 3);
		m_ptrSurface->PrintScaled("the more people you have and", 100, relativeHeight + 1120, k_gold, 3);
		m_ptrSurface->PrintScaled("the longer you survive the more gold you get", 100, relativeHeight + 1140, k_gold, 3);


		m_GoToMenubtn.RenderBtn();
	}

	void HowToPlayScene::Delete()
	{

	}

	void HowToPlayScene::KeyDown(SDL_Keycode key)
	{

	}

	void HowToPlayScene::MouseMove(int p_x, int p_y)
	{

	}

	void HowToPlayScene::MouseScroll(int y)
	{

		if ((y > 0 && relativeHeight < 0) ||		// <-- positve  y val
			(y < 0 && relativeHeight > -maxHeight)) // <-- negative y val
		{
			relativeHeight += y * 15;
		}

		printf("relativeHeight = %d \n", relativeHeight);
	}

	void HowToPlayScene::MouseDown(int p_button, int p_x, int p_y)
	{
		m_mouseBtnInput = p_button;
		m_mouseX = p_x;
		m_mouseY = p_y;

		// m_HowToPlayClickEvents needs to be invoked by InvokeCopy
		// because the memory could be destroyed while its still busy and cause a error
		m_HowToPlayClickEvents.InvokeCopy();
	}


}
#include "MenuScene.h"


namespace Tmpl8
{
	MenuScene::MenuScene(Surface* p_ptrSurface, Game* p_ptrGame)
	{
		m_ptrSurface = p_ptrSurface;
		m_ptrGame = p_ptrGame;
		m_mouseBtnInput = 0;
		m_mouseX = 0;
		m_mouseY = 0;

		printf("current scene is menu \n");

		// load ui
		m_playGamebtn = Button({ 100, 200, 150, 75 }, k_grey, m_ptrSurface, "play", 3, k_red);
		m_GoToHowToPlaysbtn = Button({ 100, 300, 150, 75 }, k_grey, m_ptrSurface, "how to play", 2, k_red);
	}


	MenuScene::~MenuScene()
	{

	}

	void MenuScene::InitScene()
	{

		// init foreach button a lambda/funtion
		#pragma region init button events

			m_menuClickEvents += [&]()
			{
				if (m_mouseBtnInput == 1)
				{
					m_playGamebtn.OnClick(m_mouseX, m_mouseY);
					m_GoToHowToPlaysbtn.OnClick(m_mouseX, m_mouseY);
				}
			};

		#pragma endregion


		// init click events for the scene
		#pragma region add buttons to the scene events

			m_playGamebtn.event += [&]()
			{
				m_ptrGame->ChangeScene(gameplayScn);
			};
			m_GoToHowToPlaysbtn.event += [&]()
			{
				m_ptrGame->ChangeScene(howToPlayScn);
			};

		#pragma endregion

	}

	void MenuScene::KeyDown(int key)
	{

	}

	void MenuScene::MouseDown(int p_button, int p_x, int p_y)
	{
		m_mouseBtnInput = p_button;
		m_mouseX = p_x;
		m_mouseY = p_y;

		// m_menuClickEvents needs to be invoked by InvokeCopy
		// because the memory could be destroyed while its still busy and cause a error
		m_menuClickEvents.InvokeCopy();
	}

	void MenuScene::Update(float p_deltaTime)
	{
		m_ptrSurface->PrintScaled("lords and castles", ScreenWidth / 2 - 250, 50, k_gold, 5);
		m_playGamebtn.RenderBtn();
		m_GoToHowToPlaysbtn.RenderBtn();
	}

	void MenuScene::MouseScroll(int y)
	{

	}

	void MenuScene::Delete()
	{

	}

}
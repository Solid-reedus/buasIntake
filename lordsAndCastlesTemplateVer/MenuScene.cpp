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
		m_playGamebtn = Button({ 100, 100, 200, 100 }, k_grey, m_ptrSurface);
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
				}
			};

		#pragma endregion


		// init click events for the scene
		#pragma region add buttons to the scene events

			m_playGamebtn.event += [&]()
			{
				m_ptrGame->ChangeScene(gameplayScn);
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
		m_menuClickEvents.Invoke();
	}

	void MenuScene::Update()
	{
		m_ptrSurface->Print("hello world", 2, 2, k_gold);
		m_playGamebtn.RenderBtn();
	}


	void MenuScene::Delete()
	{

	}

}
#include "GameScene.h"

namespace Tmpl8
{
	GameScene::GameScene(Surface* p_ptrSurface, Game* p_ptrGame)
	{
		m_ptrSurface = p_ptrSurface;
		m_ptrGame = p_ptrGame;
		m_mouseBtnInput = 0;
		m_mouseX = 0;
		m_mouseY = 0;

		printf("current scene is game \n");

	}


	GameScene::~GameScene()
	{

	}

	void GameScene::InitScene()
	{

	}

	void GameScene::KeyDown(int key)
	{

	}

	void GameScene::MouseDown(int p_button, int p_x, int p_y)
	{
		m_mouseBtnInput = p_button;
		m_mouseX = p_x;
		m_mouseY = p_y;
		m_menuClickEvents.Invoke();
	}

	void GameScene::Update()
	{
		m_ptrSurface->Print("hello world", 2, 2, 0xff1122);
	}


	void GameScene::Delete()
	{

	}

}
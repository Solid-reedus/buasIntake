#pragma once

enum GameScene
{
	noneScn     = 0,
	menuScn     = 1,
	gameplayScn = 2
};


class BaseScene
{
	public:
	virtual void InitScene() = 0;
	virtual void Update() = 0;
	virtual void Delete() = 0;
	virtual void KeyDown(int m_key) = 0;
	virtual void MouseDown(int m_button, int m_x, int m_y) = 0;
	virtual ~BaseScene() = default;
};


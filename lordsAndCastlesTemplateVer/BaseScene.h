#pragma once

// this is a way to give scenes a way to change the scene
// in game 

enum GameSceneEnum
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
	virtual void KeyDown(int p_key) = 0;
	virtual void MouseDown(int p_button, int p_x, int p_y) = 0;
	virtual ~BaseScene() = default;
};


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
	virtual ~BaseScene() = default;
};


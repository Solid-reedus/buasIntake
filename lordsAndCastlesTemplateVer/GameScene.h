#pragma once

#include "BaseHeader.h"
#include "BaseScene.h"

#include "surface.h"
#include "Event.h"
#include "game.h"

#include "SpriteSheet.h"
#include "Tile.h"
#include "Npc.h"
#include "PerspectiveMath.h"
#include "Buidlings.h"
#include "Tree.h"
#include "Rect.h"
#include "vGameObject.h"
#include <algorithm> 

enum BuildingEnum
{
	buildingNone,
	buildingAppleFarm,
	buildingDairyFarm,
	buildinghovel,
	buildingWoodCutterHut
};

enum SpriteSheetIndex
{
	sprDairyFarm,
	sprAppleFarm,
	sprWoodCutterHut,
	sprFarmer,
	sprStockPile,
	sprGranary,
	sprKeep,
	sprHovel,
	sprTileSheet,
	sprTreeIdle,
	sprTreeTimber,
	sprWoodCutter,
};


struct buildingStats
{
	uint8_t width;
	uint8_t height;
	uint8_t buildCost;
};

namespace Tmpl8
{
	// Forward declaration
	class Game;

	class GameScene : public BaseScene
	{
		public:
		GameScene(Surface* surface, Game* game);
		~GameScene() override;

		void InitScene() override;
		void Update(float p_deltaTime) override;
		void Delete() override;
		void KeyDown(SDL_Keycode key) override;
		void MouseDown(int button, int x, int y) override;
		void MouseScroll(int y) override;
		void MouseMove(int p_x, int p_y) override;

		private:


		void GameEventsTick(float p_deltaTime);
		void renderTiles();
		void DrawUI();
		void PlaceBuilding(int x, int y);


		Surface* m_ptrSurface;
		GameSceneEnum m_scene = menuScn;

		Event m_menuClickEvents;
		Game* m_ptrGame;

		//WorkerNpc and BaseBuilding are heap memory
		std::vector<BaseNpc*> npcVector;
		std::vector<BaseBuilding*> buildings;

		BuildingEnum m_selectedBuilding = buildingDairyFarm;
		SpriteSheet* SpritesheetArray[12];

		IdleBuilding granary = IdleBuilding();
		IdleBuilding keep = IdleBuilding();
		IdleBuilding stockpile = IdleBuilding();

		const buildingStats appleFarmstats = { 8, 8, 20 };
		const buildingStats dairyFarmstats = { 8, 6, 15 };
		const buildingStats hovelstats = { 4, 5, 6 };
		const buildingStats woodcuttersHutstats = { 2, 3, 5 };

		uint32_t playerGold = 0;
		uint32_t playerWood = 100;
		uint32_t playerFood = 430;
		uint32_t playerMaxPopulation = 12;
		int8_t playerPopulairity = 70;
		char toolTipText[30] = "";

		const float GameEventsTickInterval = 3000.0f;
		float GameEventsTickTime = 0.0f;

		std::vector<char*> warnings;
		uint8_t maxWarnings = 10;
		float warningDuration = 1500;
		float warningTime = 0;

		const vector2Int stockpilePos = vector2Int(56, 42);
		const vector2Int granaryPos = vector2Int(53, 56);
		const vector2Int applefarmPos = vector2Int(30, 40);
		const vector2Int spawnPos = vector2Int(66, 61);

		Tile* grassTile = nullptr;
		Tile* sandTile = nullptr;
		Tile* waterTile = nullptr;
		Tile** tilesArray = nullptr;

		Surface* controlpanelBanner = new Surface("assets/map.jpg");
		std::vector<vector2Int> unwalkableTiles;
		std::vector<vGameObject*> sceneObjects;

		float relativeHeight = -1000;
		float relativeWidth = 200;

		// this is a little padding so buildings arent rendering outside the map diamond
		const uint8_t mapPadding = 1;

		// this is for methods that dont have acces too deltatime
		float m_deltaTime = 0;

		float cameraSpeed = 3;
		const uint8_t cameraMaxSpeed = 10;

		RectInt uiAppleFarmRect = { 20, ScreenHeight - interfacebannerWidth + 20, 80, 80 };
		RectInt uiDairyFarmRect = { 120, ScreenHeight - interfacebannerWidth + 20, 80, 80 };
		RectInt uiHovelRect = { 220, ScreenHeight - interfacebannerWidth + 25, 70, 70 };
		RectInt uiWoodcutterRect = { 310, ScreenHeight - interfacebannerWidth + 25, 70, 70 };

		std::vector<Tree*> trees;
	};
}

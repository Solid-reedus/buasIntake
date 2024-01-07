#pragma once

#include "BaseHeader.h"
#include "BaseScene.h"

#include "surface.h"
#include "Event.h"
#include "game.h"

#include "SpriteSheet.h"
#include "Tile.h"
#include "WorkerNpc.h"
#include "PerspectiveMath.h"
#include "Buidlings.h"
#include "Tree.h"
#include "Rect.h"

enum BuildingEnum
{
	buildingNone,
	buildingAppleFarm,
	buildingDairyFarm,
	buildinghovel,
};

enum SpriteSheetIndex
{
	sprDairyFarm,
	sprAppleFarm,
	sprWoodCutter,
	sprFarmer,
	sprStockPile,
	sprGranary,
	sprKeep,
	sprHovel,
	sprTileSheet,
	sprTreeIdle,
	sprTreeTimber,
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


		private:

		void renderTiles();
		void DrawUI();
		void PlaceBuilding(int x, int y);


		Surface* m_ptrSurface;
		GameSceneEnum m_scene = menuScn;

		Event m_menuClickEvents;
		Game* m_ptrGame;

		//WorkerNpc and BaseBuilding are heap memory
		std::vector<WorkerNpc*> npcVector;
		std::vector<BaseBuilding*> buildings;

		BuildingEnum m_selectedBuilding = buildingDairyFarm;
		SpriteSheet* SpritesheetArray[11];

		IdleBuilding granary = IdleBuilding();
		IdleBuilding keep = IdleBuilding();
		IdleBuilding stockpile = IdleBuilding();

		const buildingStats appleFarmstats = { 8, 8, 20 };
		const buildingStats dairyFarmstats = { 8, 6, 15 };
		const buildingStats hovelstats = { 4, 5, 6 };

		uint16_t playerGold = 9995;
		uint16_t playerWood = 1100;
		uint16_t playerFood = 430;
		uint16_t playerStone = 150;
		int8_t playerPopulairity = 70;

		std::vector<char*> warnings;
		float warningDuration = 1500;
		float warningTime = 0;

		const vector2Int stockpilePos = vector2Int(29, MAP_WIDTH - 40);
		const vector2Int granaryPos = vector2Int(53, 56);
		const vector2Int applefarmPos = vector2Int(30, 40);
		const vector2Int spawnPos = vector2Int(66, 61);

		Tile* grassTile = nullptr;
		Tile* sandTile = nullptr;
		Tile* waterTile = nullptr;
		Tile** tilesArray = nullptr;

		Surface* controlpanelBanner = new Surface("assets/map.jpg");
		std::vector<vector2Int> unwalkableTiles;

		float relativeHeight = -1000;
		float relativeWidth = 200;

		// this is for methods that dont have acces too deltatime
		float m_deltaTime = 0;

		float cameraSpeed = 3;
		const uint8_t cameraMaxSpeed = 10;

		RectInt uiAppleFarmRect = { 20, ScreenHeight - interfacebannerWidth + 20, 80, 80 };
		RectInt uiDairyFarmRect = { 120, ScreenHeight - interfacebannerWidth + 20, 80, 80 };
		RectInt uiHovelRect = { 220, ScreenHeight - interfacebannerWidth + 25, 70, 70 };
		RectInt uiWoodcutterRect = { 310, ScreenHeight - interfacebannerWidth + 25, 70, 70 };

		std::vector<Tree> trees;
	};
}

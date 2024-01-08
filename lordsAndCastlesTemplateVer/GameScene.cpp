#include "GameScene.h"

namespace Tmpl8
{
	GameScene::GameScene(Surface* p_ptrSurface, Game* p_ptrGame)
	{
		m_ptrSurface = p_ptrSurface;
		m_ptrGame = p_ptrGame;

		SpritesheetArray[0] = new SpriteSheet(m_ptrSurface, new Surface("assets/cheesfarmerspritesheet6x10row2col14.png"), 2, 15),
		SpritesheetArray[1] = new SpriteSheet(m_ptrSurface, new Surface("assets/appleFarms8x8pritesheet1x7.png"), 1, 7),
		SpritesheetArray[2] = new SpriteSheet(m_ptrSurface, new Surface("assets/woodcuttershutSprite2x3.png"), 1, 1),
		SpritesheetArray[3] = new SpriteSheet(m_ptrSurface, new Surface("assets/farmerSpriteSheet8x55.png"), 8, 55),
		SpritesheetArray[4] = new SpriteSheet(m_ptrSurface, new Surface("assets/stockpile8x5v2.png"), 1, 1),
		SpritesheetArray[5] = new SpriteSheet(m_ptrSurface, new Surface("assets/granary5x5v2.png"), 1, 1),
		SpritesheetArray[6] = new SpriteSheet(m_ptrSurface, new Surface("assets/keep10x10v2.png"), 1, 1),
		SpritesheetArray[7] = new SpriteSheet(m_ptrSurface, new Surface("assets/hovel4x5v2.png"), 1, 1),
		SpritesheetArray[8] = new SpriteSheet(m_ptrSurface, new Surface("assets/tileSheet.png"), 1, 3),
		SpritesheetArray[9] = new SpriteSheet(m_ptrSurface, new Surface("assets/treeSpriteSheet1x15.png"), 1, 15),
		SpritesheetArray[10] = new SpriteSheet(m_ptrSurface, new Surface("assets/treeSingleSpriteSheet1x1.png"), 1, 1),
		SpritesheetArray[11] = new SpriteSheet(m_ptrSurface, new Surface("assets/woodCutterSpritesv6.png"), 9, 55),

		SpritesheetArray[sprDairyFarm]->SetCollumCountOfRow(static_cast<uint8_t>(bldnStateIdle), 14);
		SpritesheetArray[sprDairyFarm]->SetCollumCountOfRow(static_cast<uint8_t>(bldnStateActive), 14);

		SpritesheetArray[sprAppleFarm]->SetCollumCountOfRow(0, 7);
		SpritesheetArray[sprTreeTimber]->SetCollumCountOfRow(0, 14);

		SpritesheetArray[sprFarmer]->SetCollumCountOfRow(static_cast<uint8_t>(npcWalkTL), 55);
		SpritesheetArray[sprFarmer]->SetCollumCountOfRow(static_cast<uint8_t>(npcWalkT), 55);
		SpritesheetArray[sprFarmer]->SetCollumCountOfRow(static_cast<uint8_t>(npcWalkTR), 55);
		SpritesheetArray[sprFarmer]->SetCollumCountOfRow(static_cast<uint8_t>(npcWalkR), 55);
		SpritesheetArray[sprFarmer]->SetCollumCountOfRow(static_cast<uint8_t>(npcWalkTR), 55);
		SpritesheetArray[sprFarmer]->SetCollumCountOfRow(static_cast<uint8_t>(npcWalkBR), 55);
		SpritesheetArray[sprFarmer]->SetCollumCountOfRow(static_cast<uint8_t>(npcWalkB), 55);
		SpritesheetArray[sprFarmer]->SetCollumCountOfRow(static_cast<uint8_t>(npcWalkBL), 55);
		SpritesheetArray[sprFarmer]->SetCollumCountOfRow(static_cast<uint8_t>(npcWalkL), 55);

		SpritesheetArray[sprWoodCutter]->SetCollumCountOfRow(static_cast<uint8_t>(npcWalkTL), 55);
		SpritesheetArray[sprWoodCutter]->SetCollumCountOfRow(static_cast<uint8_t>(npcWalkT), 55);
		SpritesheetArray[sprWoodCutter]->SetCollumCountOfRow(static_cast<uint8_t>(npcWalkTR), 55);
		SpritesheetArray[sprWoodCutter]->SetCollumCountOfRow(static_cast<uint8_t>(npcWalkR), 55);
		SpritesheetArray[sprWoodCutter]->SetCollumCountOfRow(static_cast<uint8_t>(npcWalkTR), 55);
		SpritesheetArray[sprWoodCutter]->SetCollumCountOfRow(static_cast<uint8_t>(npcWalkBR), 55);
		SpritesheetArray[sprWoodCutter]->SetCollumCountOfRow(static_cast<uint8_t>(npcWalkB), 55);
		SpritesheetArray[sprWoodCutter]->SetCollumCountOfRow(static_cast<uint8_t>(npcWalkBL), 55);
		SpritesheetArray[sprWoodCutter]->SetCollumCountOfRow(static_cast<uint8_t>(npcWalkL), 55);
		SpritesheetArray[sprWoodCutter]->SetCollumCountOfRow(static_cast<uint8_t>(npcWork), 44);

		grassTile = new Tile(SpritesheetArray[sprTileSheet], 0, 0, tlfwalkable);
		sandTile = new Tile(SpritesheetArray[sprTileSheet], 0, 1, tlfwalkable);
		waterTile = new Tile(SpritesheetArray[sprTileSheet], 0, 2, tlfNone);

		tilesArray = new Tile * [MAP_WIDTH * MAP_HEIGHT];

		for (size_t i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++)
		{
			tilesArray[i] = grassTile;
		}

		granary = IdleBuilding(SpritesheetArray[sprGranary], vector2Int(50, 50), 5, 5, &unwalkableTiles, &relativeWidth, &relativeHeight);
		keep = IdleBuilding(SpritesheetArray[sprKeep], vector2Int(63, 50), 10, 10, &unwalkableTiles, &relativeWidth, &relativeHeight);
		stockpile = IdleBuilding(SpritesheetArray[sprStockPile], vector2Int(53, 35), 8, 5, &unwalkableTiles, &relativeWidth, &relativeHeight);
		stockpile.ResetUnwalkableTiles(0, 1, 8, 6);

		tilesArray[15 + (30 * MAP_HEIGHT)] = sandTile;


		trees.push_back(Tree(SpritesheetArray[sprTreeIdle], SpritesheetArray[sprTreeTimber], vector2Int(15, 30), &unwalkableTiles, &relativeWidth, &relativeHeight));

		for (size_t i = 0; i < 8; i++)
		{
			for (size_t j = 0; j < 3; j++)
			{
				trees.push_back(Tree(SpritesheetArray[sprTreeIdle], SpritesheetArray[sprTreeTimber], vector2Int(50 + (3 * i), 22 + (4 * j)), &unwalkableTiles, &relativeWidth, &relativeHeight));
			}
		}

	}


	GameScene::~GameScene()
	{
		for (BaseBuilding* building : buildings)
		{
			delete building;
		}
		buildings.clear();

		for (BaseNpc* npc : npcVector)
		{
			delete npc;
		}
		npcVector.clear();

		if (grassTile != nullptr)
		{
			delete grassTile;
			grassTile = nullptr;
		}
		if (sandTile != nullptr)
		{
			delete sandTile;
			sandTile = nullptr;
		}
		if (waterTile != nullptr)
		{
			delete waterTile;
			waterTile = nullptr;
		}
		if (tilesArray != nullptr)
		{
			delete[] tilesArray;
			tilesArray = nullptr;
		}


		//for (SpriteSheet* sheet : SpritesheetArray)
		//{
		//	if (sheet != nullptr)
		//	{
		//		delete sheet;
		//	}
		//}

	}

	void GameScene::InitScene()
	{

	}

	void GameScene::KeyDown(SDL_Keycode key)
	{

		printf("relativeWidth = %f  relativeHeight = %f \n", relativeWidth, relativeHeight);

		switch (key)
		{
			case SDLK_a:
			{
				relativeWidth += cameraSpeed * m_deltaTime;
				break;
			}
			case SDLK_d:
			{
				relativeWidth -= cameraSpeed * m_deltaTime;
				break;
			}
			case SDLK_s:
			{
				relativeHeight -= cameraSpeed * m_deltaTime;
				break;
			}
			case SDLK_w:
			{
				relativeHeight += cameraSpeed * m_deltaTime;
				break;
			}
			case SDLK_KP_PLUS:
			{
				if (cameraSpeed < cameraMaxSpeed)
				{
					cameraSpeed++;
				}
				break;
			}
			case SDLK_KP_MINUS:
			{
				if (cameraSpeed > 2)
				{
					cameraSpeed--;
				}
				break;
			}
			default:
			break;
		}
	}

	void GameScene::MouseDown(int p_button, int p_x, int p_y)
	{
		if (p_button == 1)
		{
			if (p_y > ScreenHeight - interfacebannerWidth)
			{

				if (uiAppleFarmRect.IsInside(p_x, p_y))
				{
					m_selectedBuilding = buildingAppleFarm;
				}
				else if (uiDairyFarmRect.IsInside(p_x, p_y))
				{
					m_selectedBuilding = buildingDairyFarm;
				}
				else if (uiHovelRect.IsInside(p_x, p_y))
				{
					m_selectedBuilding = buildinghovel;
				}
				else if (uiWoodcutterRect.IsInside(p_x, p_y))
				{
					m_selectedBuilding = buildingWoodCutterHut;
				}
			}
			else
			{
				PlaceBuilding(p_x, p_y);
			}

		}
		//m_mouseBtnInput = p_button;
		//m_mouseX = p_x;
		//m_mouseY = p_y;
		//m_menuClickEvents.Invoke();
	}

	void GameScene::renderTiles()
	{
		int tlX, tlY, trX, trY, brX, brY, blX, blY;

		IsometricToCartesian(-TILE_HEIGHT, -TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT, tlX, tlY, relativeWidth, relativeHeight);
		IsometricToCartesian(ScreenWidth + TILE_HEIGHT, TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT, trX, trY, relativeWidth, relativeHeight);

		IsometricToCartesian(ScreenWidth + TILE_HEIGHT, ScreenHeight + (TILE_HEIGHT * 2) - interfacebannerWidth, TILE_WIDTH, TILE_HEIGHT, brX, brY, relativeWidth, relativeHeight);
		IsometricToCartesian(-TILE_HEIGHT, ScreenHeight + (TILE_HEIGHT * 2) - interfacebannerWidth, TILE_WIDTH, TILE_HEIGHT, blX, blY, relativeWidth, relativeHeight);

		// renders the top layer that isnt consistant
		for (int i = 2; i < MAP_WIDTH; i++)
		{
			int isoX, isoY;
			CartesianToIsometric(i, 2, TILE_WIDTH, TILE_HEIGHT, isoX, isoY, relativeWidth, relativeHeight);
			if (isoX > ScreenWidth || isoY > ScreenHeight)
			{
				break;
			}
			else if (isoX - (TILE_WIDTH * 2) < 0 || isoY < 0)
			{
				continue;
			}
			tilesArray[i + (2 * MAP_HEIGHT)]->Render(isoX, isoY, TILE_WIDTH, TILE_HEIGHT);
		}

		for (int j = tlX; j < trX; j++)
		{
			for (int i = tlY; i < blY; i++)
			{
				int x = i + j - tlY;
				int y = i - j + tlX;

				int isoX, isoY, isoX2, isoY2;

				if (x <= 1 || x >= MAP_WIDTH || y <= 1 || y >= MAP_HEIGHT)
				{
					continue;
				}
				CartesianToIsometric(x, y, TILE_WIDTH, TILE_HEIGHT, isoX, isoY, relativeWidth, relativeHeight);
				tilesArray[(y * MAP_WIDTH) + x]->Render(isoX, isoY, TILE_WIDTH, TILE_HEIGHT);
				//printf("x = %d y = %d pitch = %d \n",x, y, ((y * MAP_WIDTH) + x));

				if (y + 1 >= MAP_HEIGHT)
				{
					continue;
				}

				CartesianToIsometric(x, y + 1, TILE_WIDTH, TILE_HEIGHT, isoX2, isoY2, relativeWidth, relativeHeight);
				tilesArray[((y + 1) * MAP_WIDTH) + x]->Render(isoX2, isoY2, TILE_WIDTH, TILE_HEIGHT);
			}
		}

	}

	void GameScene::PlaceBuilding(int x, int y)
	{
		switch (m_selectedBuilding)
		{
		case buildingAppleFarm:
		{
			if (playerWood - appleFarmstats.buildCost < 0)
			{
				warnings.push_back("not enough wood");
				printf("not enough wood \n");
				return;
			}

			playerWood -= appleFarmstats.buildCost;

			int cartX, cartY;
			IsometricToCartesian(x, y, TILE_WIDTH, TILE_HEIGHT, cartX, cartY, relativeWidth, relativeHeight);

			if (cartX < 1 || cartX + appleFarmstats.width > MAP_WIDTH ||
				cartY < 1 || cartY + appleFarmstats.height + 1 > MAP_HEIGHT)
			{
				return;
			}

			for (int i = cartX; i < cartX + appleFarmstats.width; i++)
			{
				for (int j = cartY; j < cartY + appleFarmstats.height; j++)
				{
					// if the pos that is clicked plus the size of the 
					// building overlap with a unwalkable tile or other building
					// then it will not be build
					if (!(tilesArray[i + (j * MAP_HEIGHT)]->tileFlags & tlfwalkable) ||
						std::find(unwalkableTiles.begin(), unwalkableTiles.end(),
							vector2Int(i, j)) != unwalkableTiles.end())
					{
						warnings.push_back("cant place it here my lord");
						printf("applefarm is unable to be placed at %d %d \n", cartX, cartY);
						return;
					}
				}
			}

			IdleAnimBuidling* newBuilding = new IdleAnimBuidling(SpritesheetArray[sprAppleFarm],
				vector2Int(cartX, cartY), appleFarmstats.width, appleFarmstats.height,
				5000, &unwalkableTiles, &relativeWidth, &relativeHeight);

			buildings.push_back(newBuilding);
			npcVector.push_back(new WorkerNpc(SpritesheetArray[sprFarmer], tilesArray,
				&unwalkableTiles,
				spawnPos,
				newBuilding->GetEntryPos(),
				granaryPos,
				newBuilding, 5000,
				&relativeWidth, &relativeHeight,
				&playerFood, 10));

			break;
		}

		case buildingDairyFarm:
		{
			if (playerWood - dairyFarmstats.buildCost < 0)
			{
				warnings.push_back("not enough wood");
				printf("not enough wood \n");
				return;
			}

			playerWood -= dairyFarmstats.buildCost;

			int cartX, cartY;
			IsometricToCartesian(x, y, TILE_WIDTH, TILE_HEIGHT, cartX, cartY, relativeWidth, relativeHeight);

			if (cartX < 1 || cartX + dairyFarmstats.width > MAP_WIDTH ||
				cartY < 1 || cartY + dairyFarmstats.height + 1 > MAP_HEIGHT)
			{
				return;
			}

			for (int i = cartX; i < cartX + dairyFarmstats.width; i++)
			{
				for (int j = cartY; j < cartY + dairyFarmstats.height; j++)
				{
					// if the pos that is clicked plus the size of the 
					// building overlap with a unwalkable tile or other building
					// then it will not be build
					if (!(tilesArray[i + (j * MAP_HEIGHT)]->tileFlags & tlfwalkable) ||
						std::find(unwalkableTiles.begin(), unwalkableTiles.end(),
							vector2Int(i, j)) != unwalkableTiles.end())
					{
						warnings.push_back("cant place it here my lord");
						printf("dairy farm is unable to be placed at %d %d \n", cartX, cartY);
						return;
					}
				}
			}

			AnimatedBuilding* newBuilding = new AnimatedBuilding(SpritesheetArray[sprDairyFarm],
				vector2Int(cartX, cartY), dairyFarmstats.width, dairyFarmstats.height,
				5000, &unwalkableTiles, &relativeWidth, &relativeHeight, 300);

			newBuilding->ResetUnwalkableTiles(-2, 0, 8, 6);

			buildings.push_back(newBuilding);

			npcVector.push_back(new WorkerNpc(SpritesheetArray[sprFarmer], tilesArray,
				&unwalkableTiles,
				spawnPos,
				newBuilding->GetEntryPos(),
				granaryPos,
				newBuilding, 5000,
				&relativeWidth, &relativeHeight,
				&playerFood, 10));

			break;
		}

		case buildinghovel:
		{
			if (playerWood - hovelstats.buildCost < 0)
			{
				warnings.push_back("not enough wood");
				printf("not enough wood \n");
				return;
			}

			playerWood -= hovelstats.buildCost;

			int cartX, cartY;
			IsometricToCartesian(x, y, TILE_WIDTH, TILE_HEIGHT, cartX, cartY, relativeWidth, relativeHeight);

			if (cartX < 1 || cartX + hovelstats.width > MAP_WIDTH ||
				cartY < 1 || cartY + hovelstats.height + 1 > MAP_HEIGHT)
			{
				return;
			}

			for (int i = cartX; i < cartX + hovelstats.width; i++)
			{
				for (int j = cartY; j < cartY + hovelstats.height; j++)
				{
					// if the pos that is clicked plus the size of the 
					// building overlap with a unwalkable tile or other building
					// then it will not be build
					if (!(tilesArray[i + (j * MAP_HEIGHT)]->tileFlags & tlfwalkable) ||
						std::find(unwalkableTiles.begin(), unwalkableTiles.end(),
							vector2Int(i, j)) != unwalkableTiles.end())
					{
						warnings.push_back("cant place it here my lord");
						printf("hovel is unable to be placed at %d %d \n", cartX, cartY);
						return;
					}
				}
			}

			IdleBuilding* newBuilding = new IdleBuilding(SpritesheetArray[sprHovel],
				vector2Int(cartX, cartY), hovelstats.width, hovelstats.height,
				&unwalkableTiles, &relativeWidth, &relativeHeight);

			buildings.push_back(newBuilding);
			break;
		}
		case buildingWoodCutterHut:
		{
			if (playerWood - woodcuttersHutstats.buildCost < 0)
			{
				warnings.push_back("not enough wood");
				printf("not enough wood \n");
				return;
			}

			playerWood -= woodcuttersHutstats.buildCost;

			int cartX, cartY;
			IsometricToCartesian(x, y, TILE_WIDTH, TILE_HEIGHT, cartX, cartY, relativeWidth, relativeHeight);

			if (cartX < 1 || cartX + woodcuttersHutstats.width > MAP_WIDTH ||
				cartY < 1 || cartY + woodcuttersHutstats.height + 1 > MAP_HEIGHT)
			{
				return;
			}

			for (int i = cartX; i < cartX + woodcuttersHutstats.width; i++)
			{
				for (int j = cartY; j < cartY + woodcuttersHutstats.height; j++)
				{
					// if the pos that is clicked plus the size of the 
					// building overlap with a unwalkable tile or other building
					// then it will not be build
					if (!(tilesArray[i + (j * MAP_HEIGHT)]->tileFlags & tlfwalkable) ||
						std::find(unwalkableTiles.begin(), unwalkableTiles.end(),
							vector2Int(i, j)) != unwalkableTiles.end())
					{
						warnings.push_back("cant place it here my lord");
						printf("dairy farm is unable to be placed at %d %d \n", cartX, cartY);
						return;
					}
				}
			}

			IdleBuilding* newBuilding = new IdleBuilding(SpritesheetArray[sprWoodCutterHut],
				vector2Int(cartX, cartY), woodcuttersHutstats.width, woodcuttersHutstats.height,
				&unwalkableTiles, &relativeWidth, &relativeHeight);

			buildings.push_back(newBuilding);

			npcVector.push_back(new WoodCutterNpc(SpritesheetArray[sprWoodCutter], tilesArray,
				&unwalkableTiles, spawnPos,
				stockpilePos, 5000,
				&relativeWidth, &relativeHeight,
				&playerWood, 30, &trees));


			break;
		}

		default:
		case buildingNone:
			break;
		}
	}

	void GameScene::DrawUI()
	{

		if (!warnings.empty())
		{
			int spacing = 20;
			for (char* warning : warnings)
			{
				m_ptrSurface->PrintScaled(warning, 20, spacing, 0xE90101, 2);
				spacing += 20;
			}
		}

		m_ptrSurface->RenderFrom(m_ptrSurface, controlpanelBanner, 0, ScreenHeight - interfacebannerWidth, ScreenWidth,
			interfacebannerWidth, 0, 0, controlpanelBanner->GetWidth() - interfacebannerWidth, controlpanelBanner->GetHeight());

		m_ptrSurface->Bar(ScreenWidth - interfacebannerWidth - 20, ScreenHeight - interfacebannerWidth - 20, ScreenWidth, ScreenHeight, 0x8F9898);


		SpritesheetArray[sprAppleFarm]->RenderFrom(20, ScreenHeight - interfacebannerWidth + 20, 80, 80, 0, 0);
		SpritesheetArray[sprDairyFarm]->RenderFrom(120, ScreenHeight - interfacebannerWidth + 20, 80, 80, 1, 0);
		SpritesheetArray[sprHovel]->RenderFrom(220, ScreenHeight - interfacebannerWidth + 25, 70, 70, 0, 0);
		SpritesheetArray[sprWoodCutterHut]->RenderFrom(310, ScreenHeight - interfacebannerWidth + 25, 70, 70, 0, 0);


		char goldText[10];
		char woodText[10];
		char foodText[10];
		char populationText[60];
		char populairityText[3];

		//population
		//999/999

		sprintf(goldText, "gold %d", playerGold);
		sprintf(woodText, "wood %d", playerWood);
		sprintf(foodText, "food %d", playerFood);
		sprintf(populationText, "%d/%d", playerPopulation, playerMaxPopulation);
		sprintf(populairityText, "%d", playerPopulairity);


		m_ptrSurface->PrintScaled(populairityText, ScreenWidth - interfacebannerWidth / 2 - 40, ScreenHeight - interfacebannerWidth - 5, 0x18C800, 4);
		m_ptrSurface->PrintScaled(goldText, ScreenWidth - interfacebannerWidth, ScreenHeight - interfacebannerWidth + 20, 0xB8C330, 2);
		m_ptrSurface->PrintScaled(woodText, ScreenWidth - interfacebannerWidth, ScreenHeight - interfacebannerWidth + 40, 0x9E620E, 2);
		m_ptrSurface->PrintScaled(foodText, ScreenWidth - interfacebannerWidth, ScreenHeight - interfacebannerWidth + 60, 0xC81B1B, 2);
		

		m_ptrSurface->PrintScaled("population", ScreenWidth - interfacebannerWidth - 10, ScreenHeight - interfacebannerWidth + 80, 0xD1D1D1, 2);
		m_ptrSurface->PrintScaled(populationText, ScreenWidth - interfacebannerWidth, ScreenHeight - interfacebannerWidth + 100, 0xD1D1D1, 2);

	}

	void GameScene::Update(float p_deltaTime)
	{
		m_deltaTime = p_deltaTime;
		m_ptrSurface->Clear(0);

		if (!warnings.empty())
		{
			warningTime += p_deltaTime;
			if (warningTime > warningDuration)
			{
				warnings.erase(warnings.begin());
				warningTime = 0;
			}
		}

		renderTiles();
		//FoodTick(p_deltaTime);


		for (BaseNpc* npc : npcVector)
		{
			npc->Update(p_deltaTime);
		}

		for (Tree &tree : trees)
		{
			tree.Update(p_deltaTime);
		}

		granary.Update(p_deltaTime);
		keep.Update(p_deltaTime);
		stockpile.Update(p_deltaTime);

		//buildings
		for (BaseBuilding* building : buildings)
		{
			building->Update(p_deltaTime);
		}


		DrawUI();
	}

	void GameScene::MouseScroll(int y)
	{

	}

	void GameScene::Delete()
	{

	}

	void GameScene::GameEventsTick(float p_deltaTime)
	{
		GameEventsTickTime += p_deltaTime;
		if (GameEventsTickTime > GameEventsTickInterval)
		{
			if (!npcVector.empty())
			{
				playerFood -= npcVector.size();
				playerGold += npcVector.size() * 5;
			}

			GameEventsTickTime = 0;
		}


	}

}
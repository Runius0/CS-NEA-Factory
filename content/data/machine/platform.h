#pragma once
#include "../../../src/core/machine.h"
#include "../../../src/core/item.h"

class SurfacePlatform : public Machine {
public:
	Player* targetPlayer;
	int vel;
	int depth;
	PlayerState currentState;
	SurfacePlatform();
	void init(int worldX, int worldY, Direction direction);
	Machine* copy(int worldX, int worldY, Direction direction);
	void draw(SDL_Renderer* renderer, float x, float y) override;
	void DrawPreview(SDL_Renderer* renderer, float x, float y, Direction direction);
	void tick(World* world, int gameTick);

	bool interract(Player* player) override;
};



class CavesPlatform : public Machine {
public:
	Player* targetPlayer;
	int vel;
	int depth;
	PlayerState currentState;
	CavesPlatform();
	void init(int worldX, int worldY, Direction direction);
	Machine* copy(int worldX, int worldY, Direction direction);
	void draw(SDL_Renderer* renderer, float x, float y) override;
	void drawOverlay(SDL_Renderer* renderer, float x, float y) override;
	void DrawPreview(SDL_Renderer* renderer, float x, float y, Direction direction);
	void tick(World* world, int gameTick);

	bool interract(Player* player) override;
};
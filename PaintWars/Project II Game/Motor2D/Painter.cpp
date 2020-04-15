#include "p2Defs.h"
#include "p2Log.h"

#include "Painter.h"

#include "j1Player.h"
#include "Scene.h"
#include "j1EntityManager.h"
#include "j1Pathfinding.h"
#include "j1Map.h"
#include "j1Collision.h"
#include "j1Textures.h"

Painter::Painter(iPoint tile, int damage, j1Module* listener, Entity* creator) : Entity(tile, damage, listener, creator) {

	// Handle data and initialize the Painter
	*(ENTITY_TYPE*)&entityType = ENTITY_TYPE_PAINTER;
	*(ENTITY_CATEGORY*)&entityCategory = ENTITY_CATEGORY_DYNAMIC_ENTITY;
	*(ENTITY_SIZE*)&entitySize = ENTITY_SIZE_SMALL;
	
	maxLife = 10;
	currLife = maxLife - damage;
	
	size = { 88, 118 };

	currentTile = tile;
	fPoint tileWorldPosition = App->map->MapToWorld(currentTile.x, currentTile.y);

	pos.x = tileWorldPosition.x + App->map->data.tile_width / 2 - size.x / 2;
	pos.y = tileWorldPosition.y + App->map->data.tile_height / 2 - size.y;

	speed = 200.0f;

	spawningTime = 10.0f;

	destination = currentTile;

	isEntityFromPlayer = true;

	extractionRate = 25.0f;

	isBuildingSomething = false;

	for (std::vector<Animation>::iterator i = App->map->allAnimations.begin(); i != App->map->allAnimations.end(); i++)
	{
		/*if (this->type == (i)->type)
		{
			if ((i)->orientation == ORIENTATION::ORIENTATION_NORTH)
			{
				this->north = i->GetAnimation(); continue;
			}
			
		}*/
	}


}

Painter::~Painter() {}

void Painter::SpawnEntity(iPoint pos) {

	if (App->player->woodCount.count >= 20) {
		App->player->woodCount.count -= 20;
	}
	else {
		isSelectingPlacement = false;
		return;
	}

	isSelectingPlacement = false;
	if (!isBuildingSomething) {
		App->entities->AddEntity(ENTITY_TYPE_PAINT_EXTRACTOR, pos, App->entities, this, 0);
		isBuildingSomething = true;
	}
}

void Painter::ExtractPaint(float dt) {

	if (App->pathfinding->IsPaint(currentTile) && currentTile == destination) {
		App->player->paintCount.count += extractionRate * dt;
	}
}

void Painter::ExtractWood(float dt) {

	if (App->pathfinding->IsWood(currentTile) && currentTile == destination) {
		App->player->woodCount.count += extractionRate * dt;
	}
}
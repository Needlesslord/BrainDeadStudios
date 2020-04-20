#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1UI_manager.h"
#include "j1SceneManager.h"
#include "j1Audio.h"
#include "SettingsScene.h"
#include "TransitionManager.h"

SettingsScene::SettingsScene() : Scene(SCENES::SETTINGS_SCENE)
{

}

// Destructor
SettingsScene::~SettingsScene()
{

}

// Called before render is available
bool SettingsScene::Awake(pugi::xml_node& config)
{
	LOG("Loading MenuScene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool SettingsScene::Start()
{
	bool ret = true;

	backgroundImage = App->gui->AddElement(TypeOfUI::GUI_IMAGE, nullptr, { 0, 0 }, { 0,0 }, true, true, { 0, 0, App->win->width, App->win->width }, nullptr, App->scenes,TEXTURE::MAIN_IMAGE);

	musicLabel = App->gui->AddElement(TypeOfUI::GUI_LABEL, nullptr, { 300, 150 }, { 0, 0 }, false, true, { 0, 0, 0, 0 }, "Music");

	vfxLabel = App->gui->AddElement(TypeOfUI::GUI_LABEL, nullptr, { 300, 250 }, { 0, 0 }, false, true, { 0, 0, 0, 0 }, "VFX");

	fullscreenLabel = App->gui->AddElement(TypeOfUI::GUI_LABEL, nullptr, { 300, 350 }, { 0, 0 }, false, true, { 0, 0, 0, 0 }, "Fullscreen");

	gpadLabel = App->gui->AddElement(TypeOfUI::GUI_LABEL, nullptr, { 300, 450 }, { 0, 0 }, false, true, { 0, 0, 0, 0 }, "GamePad");

	

	fullscreenButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 620, 350 }, { 0,0 }, true, true, { 0, 1031, 182, 58 }, nullptr, App->scenes, TEXTURE::ATLAS);
	fullscreenButton->hover_rect = { 0, 1031, 182, 58 };
	fullscreenButton->click_rect = { 0, 1031, 182, 58 };

	gpadButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 620, 450 }, { 0,0 }, true, true, { 0, 1031, 182, 58 }, nullptr, App->scenes, TEXTURE::ATLAS);
	gpadButton->hover_rect = { 0, 1031, 182, 58 };
	gpadButton->click_rect = { 0, 1031, 182, 58 };

	resetButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 500, 550 }, { 30,15 }, true, true, { 0, 658, 207, 71 }, "Reset", App->scenes, TEXTURE::ATLAS);
	resetButton->hover_rect = { 263, 658, 207, 71 };
	resetButton->click_rect = { 525, 658, 207, 71 };

	backButton = App->gui->AddElement(TypeOfUI::GUI_BUTTON, nullptr, { 900, 630 }, { 50,15 }, true, true, { 0, 658, 207, 71 }, "BACK", App->scenes, TEXTURE::ATLAS);
	backButton->hover_rect = { 263, 658, 207, 71 };
	backButton->click_rect = { 525, 658, 207, 71 };

	return ret;
}

// Called each loop iteration
bool SettingsScene::PreUpdate()
{
	bool ret = true;

	return ret;
}

// Called each loop iteration
bool SettingsScene::Update(float dt)
{
	bool ret = true;
	
	CameraDebugMovement(dt);

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		App->scenes->SwitchScene(SCENES::GAME_SCENE);
	}

	return ret;
}

// Called each loop iteration
bool SettingsScene::PostUpdate()
{
	bool ret = true;

	if ( exit)
		ret = false;

	//ExecuteTransition();

	return ret;
}

// Called before quitting
bool SettingsScene::CleanUp()
{
	LOG("Freeing Scene");
	bool ret = true;

	for (int i = 0; i < App->gui->GUI_ELEMENTS.count(); i++)
	{
		App->gui->GUI_ELEMENTS[i]->CleanUp();
	}

	RELEASE(vfxScroll);
	RELEASE(musicScroll);


	if (scene_texture != nullptr)
	{
		App->tex->UnLoad(scene_texture);
	}

	if (tileset_texture != nullptr)
	{
		App->tex->UnLoad(tileset_texture);
	}

	if (SDL_RenderClear(scene_renderer) == 0)
	{
		scene_renderer = nullptr;
	}

	if (scene_surface != nullptr)
	{
		SDL_FreeSurface(scene_surface);
	}

	return ret;
}


void SettingsScene::GUI_Event_Manager(GUI_Event type, j1UIElement* element)
{
	if (element == backButton && type == GUI_Event::EVENT_ONCLICK)
	{
		App->transition_manager->CreateFadeToColour(SCENES::MENU_SCENE);
	}

	if (element == fullscreenButton && type == GUI_Event::EVENT_ONCLICK)
	{
		if (!App->win->fullscreen)
		{
			fullscreenButton->rect = { 0, 973, 182, 58 };
			fullscreenButton->hover_rect = { 0, 973, 182, 58 };
			fullscreenButton->click_rect = { 0, 973, 182, 58 };
		}

		if (App->win->fullscreen)
		{
			fullscreenButton->rect = { 0, 1031, 182, 58 };
			fullscreenButton->hover_rect = { 0, 1031, 182, 58 };
			fullscreenButton->click_rect = { 0, 1031, 182, 58 };
		}


		App->win->Fullscreen_Swap();
	}
}


//void MenuScene::InitScene()
//{
//	tileset_texture = App->tex->Load("maps/tiles_first_map.png", scene_renderer);	// This texture will be used SceneToTexture(). Needed to get a single whole texture of the map.
//
//	App->map->GetMapSize(map_width, map_height);
//	App->map->GetTileOffset(x_offset, y_offset);
//	
//	App->render->camera.x = map_width * 0.3f;										// This camera position gets the camera close to the center of the map.
//	App->render->camera.y = -40;
//
//	// --- TRANSITIONS WITH TEXTURE
//	/*App->render->camera.x = map_width * 0.5f;										// This camera position is to have the renderer render all the scene_texture.
//	App->render->camera.y = 0;
//
//	SceneToTexture();
//
//	App->render->camera.x = map_width * 0.3f;										// This camera position gets the camera close to the center of the map.
//	App->render->camera.y = -40;*/
//}

//void MenuScene::DrawScene()
//{
//	App->map->Draw();
//
//
//	// --- TRANSITIONS WITH TEXTURE
//	/*if (scene_texture != nullptr)
//	{
//		App->render->Blit(scene_texture, -(map_width) * 0.5f, 0, NULL);
//	}*/	
//}


//SDL_Texture* MenuScene::SceneToTexture()
//{
//	App->render->CreateSubRenderer(map_width + x_offset, map_height + y_offset, scene_surface, scene_renderer);		// Both scene_surface and scene renderer are passed by reference.
//
//	tileset_texture = App->tex->Load("maps/tiles_first_map.png", scene_renderer);
//	App->map->DrawToSubRenderer(scene_renderer, tileset_texture);
//
//	scene_texture = SDL_CreateTextureFromSurface(App->render->renderer, scene_surface);
//
//	return scene_texture;
//}


void SettingsScene::ExecuteTransition()
{
	if (!App->transition_manager->is_transitioning)
	{
		if (App->input->GetKey(SDL_SCANCODE_H) == KEY_DOWN)
		{
			App->transition_manager->CreateCut(SCENES::GAME_SCENE);
		}

		if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
		{
			App->transition_manager->CreateFadeToColour(SCENES::GAME_SCENE);
		}

		//	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
		//	{
		//		App->transition_manager->CreateSlide(SCENES::SECOND_SCENE, 0.5f, true);
		//	}

		//	if (App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN)
		//	{
		//		App->transition_manager->CreateSlide(SCENES::SECOND_SCENE, 0.5f, true, true);
		//	}

		//	if (App->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN)
		//	{
		//		App->transition_manager->CreateWipe(SCENES::SECOND_SCENE, 0.5f, true);
		//	}

		//	if (App->input->GetKey(SDL_SCANCODE_6) == KEY_DOWN)
		//	{
		//		App->transition_manager->CreateWipe(SCENES::SECOND_SCENE, 0.5f, true, true);
		//	}

		//	if (App->input->GetKey(SDL_SCANCODE_7) == KEY_DOWN)
		//	{
		//		App->transition_manager->CreateAlternatingBars(SCENES::SECOND_SCENE, 0.5f, true);
		//	}

		//	if (App->input->GetKey(SDL_SCANCODE_8) == KEY_DOWN)
		//	{
		//		App->transition_manager->CreateExpandingBars(SCENES::SECOND_SCENE, 0.5f, true);
		//	}

		//	if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_DOWN)
		//	{
		//		iPoint mouse_pos = App->input->GetMouseToWorld();

		//		App->transition_manager->CreateZoomToMouse(SCENES::SECOND_SCENE, mouse_pos, 0.5f, true);
		//	}

		//	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
		//	{
		//		iPoint mouse_pos = App->input->GetMouseToWorld();

		//		App->transition_manager->CreateCameraToMouse(mouse_pos, 0.5f, true);
		//	}


		//	// --- TRANSITION WITH TEXTURE METHODS (NOT IMPLEMENTED)
		//	if (App->input->GetKey(SDL_SCANCODE_9) == KEY_DOWN)
		//	{
		//		if (scene_texture != nullptr)
		//		{
		//			App->transition_manager->CreateDissolve(SCENES::SECOND_SCENE, 1.0f);
		//		}
		//	}

		//	if (App->input->GetMouseButtonDown(SDL_BUTTON_MIDDLE) == KEY_DOWN)
		//	{
		//		iPoint mouse_pos = App->input->GetMouseToWorld();

		//		if (scene_texture != nullptr)
		//		{
		//			App->transition_manager->CreateZoomToTexture(SCENES::SECOND_SCENE, mouse_pos);
		//		}
		//	}
		}
	}
#ifndef __MENUSCENE_H__
#define __MENUSCENE_H__

#include "j1Module.h"
#include "Scene.h"

class MenuScene : public Scene
{
public:

	MenuScene();									// Constructor
	~MenuScene();									// Destructor

	bool Awake(pugi::xml_node& config);				// Called before render is available
	bool Start();									// Called before the first frame
	bool PreUpdate();								// Called before all Updates
	bool Update(float dt);							// Called each loop iteration
	bool PostUpdate();								// Called before all Updates
	bool CleanUp();									// Called before quitting


	//CAMERA



	//MAP & SCENE 
	void Map_Manager();
	void Create_Forest_Map();
	void Create_Snow_Map();
	void Create_Volcano_Map();
	

public:
	void InitScene();								// Method that will be used to initialize all scene elements.
	void DrawScene();								// Method that will draw all scene elements on screen.
	//SDL_Texture* SceneToTexture();				// Method that will be used to get a texture from the current screen.

	void ExecuteTransition();						// Method that will trigger a new transition depending on the input received.

public:

	//MAP MANAGER
	bool LoadingMap;
	bool Forest_Map_Active;
	bool Volcano_Map_Active;
	bool Snow_Map_Active;
	bool Load_Forest_Map;
	bool Load_Volcano_Map;
	bool Load_Snow_Map;
	bool Change_Map;


};

#endif // __FIRSTSCENE_H__

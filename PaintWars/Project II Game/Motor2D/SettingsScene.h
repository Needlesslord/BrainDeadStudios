#ifndef __SETTINGSSCENE_H__
#define __SETTINGSSCENE_H__

#include "j1Module.h"
#include "Scene.h"

class SettingsScene : public Scene
{
public:

	SettingsScene();									// Constructor
	~SettingsScene();									// Destructor

	bool Awake(pugi::xml_node& config);				// Called before render is available
	bool Start();									// Called before the first frame
	bool PreUpdate();								// Called before all Updates
	bool Update(float dt);							// Called each loop iteration
	bool PostUpdate();								// Called before all Updates
	bool CleanUp();									// Called before quitting



public:
	//void InitScene();								// Method that will be used to initialize all scene elements.
	
	//void DrawScene();								// Method that will draw all scene elements on screen.
	//SDL_Texture* SceneToTexture();				// Method that will be used to get a texture from the current screen.


	void GUI_Event_Manager(GUI_Event type, j1Element* element);


	void ExecuteTransition();						// Method that will trigger a new transition depending on the input received.

public:

	j1Element* musicLabel = nullptr;
	j1Element* vfxLabel = nullptr;
	j1Element* fullscreenLabel = nullptr;
	j1Element*gpadLabel = nullptr;
	j1Element* musicScroll = nullptr;
	j1Element* vfxScroll = nullptr;
	j1Element* fullscreenButton = nullptr;
	j1Element* gpadButton = nullptr;
	j1Element* resetButton = nullptr;
	j1Element* backButton = nullptr;

};

#endif // __FIRSTSCENE_H__

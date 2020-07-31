#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include "Thomas.h"
#include "Bob.h"
#include "LevelManager.h"
#include "SoundManager.h"
#include "HUD.h"
#include "ParticleSystem.h"

using namespace sf;

class Engine
{
private:
	//Texture holder
	TextureHolder th; 

	//Particle system
	ParticleSystem m_PS;

	//Characters
	Thomas m_Thomas;
	Bob m_Bob;

	//Level maanger
	LevelManager m_LM;

	//Sound manager
	SoundManager m_SM;

	//Hud
	Hud m_Hud;
	int m_FrameSinceLastUpdate = 0;
	int m_TargetFramesPerHUDUpdate = 500;

	const int TILE_SIZE = 50;
	const int VERTS_IN_QUAD = 4;

	//Force pushing characters down
	const int GRAVITY = 300;

	//Regular render window
	RenderWindow m_Window;

	//Main views
	View m_MainView;
	View m_LeftView;
	View m_RightView;

	//views for background
	View m_BGMainView;
	View m_BGLeftView;
	View m_BGRightView;

	View m_HudView;

	//Bckground sprite
	Sprite m_BackgroundSprite;
	Texture m_BackgroundTexture;
	Shader m_RippleShader;

	//is game playing
	bool m_Playing = false;

	//Is focus on character 1
	bool m_Character1 = true;

	//Is split screen mode
	bool m_SplitScreen = false;

	//Time
	float m_TimeRemaining;
	Time m_GameTimeTotal;

	//Is it time for new level
	bool m_NewLevelRequired = true;
	bool m_PassedLevel = true;

	//Level design
	VertexArray m_VALevel;
	int** m_arrayLevel = NULL;

	//background texture
	Texture m_TextureTiles;

	//Functions
	void input();
	void update(float dtAsSeconds);
	void draw();
	void loadLevel();
	bool detectCollision(PlayableCharacter& character);

	//Creates vector of best places to emut sounds from
	void populateEmitters(vector <Vector2f>& vSoundEmitters, int** arrayLevel);

	vector <Vector2f> m_FireEmitters;

public:
	Engine();

	//Calls all private functions
	void run();
};
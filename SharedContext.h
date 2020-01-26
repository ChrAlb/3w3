#pragma once
#include "Window.h"
#include "EventManager.h"
#include "FontManager.h"
#include "GUI_Manager.h"
#include "TextureManager.h"
#include "EntityManager.h"
#include "DebugOverlay.h"

class Map;
struct SharedContext{
	SharedContext() :
		m_wind(nullptr),
		m_eventManager(nullptr),
		m_textureManager(nullptr),
		m_entityManager(nullptr),
		m_fontManager(nullptr),
		m_gameMap(nullptr),
		m_guiManager(nullptr){}

	Window* m_wind;
	EventManager* m_eventManager;
	TextureManager* m_textureManager;
	EntityManager* m_entityManager;
	FontManager* m_fontManager;
	Map* m_gameMap;
	GUI_Manager* m_guiManager;
	DebugOverlay m_debugOverlay;
};
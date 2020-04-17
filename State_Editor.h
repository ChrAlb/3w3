#pragma once
#include "BaseState.h"
#include "Map.h"
#include "EventManager.h"

class State_Editor : public BaseState {
public:
	State_Editor(StateManager* l_stateManager);
	~State_Editor();

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& l_time);
	void Draw();

	void MainMenu(EventDetails* l_details);

private:
	Map* m_gameMap;

	sf::View       m_TileView;
	sf::View       m_DesignView;
	sf::View       m_LevelView;
	sf::View       m_LayerView;

	sf::Vector2i   m_Map_Size;
	sf::Vector2f  m_pos_TileArray;
	sf::Vector2f  m_pos_DesingArray;
	sf::Vector2f  m_TileLevelSize;
	sf::Vector2f  m_LevelSize;

	sf::FloatRect TileFläche;
	sf::FloatRect DesignFläche;
		
};
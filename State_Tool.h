#pragma once
#include "BaseState.h"
#include "EventManager.h"

class State_Tool : public BaseState {
public:
	State_Tool(StateManager* l_stateManager);
	~State_Tool();

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& l_time);
	void Draw();

	void F1(EventDetails* l_details);
	void F2(EventDetails* l_details);

private:
	sf::Sprite m_introSprite;
	sf::Font m_font;
};
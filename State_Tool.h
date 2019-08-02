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

	void Toolexit(EventDetails* l_details);
	void Tools1(EventDetails* l_details);

private:
	sf::Sprite m_introSprite;
	sf::Font m_font;
	sf::Text m_text;
};
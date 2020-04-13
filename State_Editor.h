#pragma once
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

	

private:
	

};
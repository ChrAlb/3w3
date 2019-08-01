#include "State_Tool.h"
#include "StateManager.h"

State_Tool::State_Tool(StateManager* l_stateManager)
	: BaseState(l_stateManager) {}

State_Tool::~State_Tool() {}

void State_Tool::OnCreate() {
	sf::Vector2u windowSize = m_stateMgr->GetContext()
		->m_wind->GetRenderWindow()->getSize();


	EventManager* evMgr = m_stateMgr->GetContext()->m_eventManager;
	evMgr->AddCallback(StateType::Tool, "", &State_Tool::F1, this);
	evMgr->AddCallback(StateType::Tool, "", &State_Tool::F2, this);
}

void State_Tool::OnDestroy() {
	

	EventManager* evMgr = m_stateMgr->GetContext()->m_eventManager;
	
	evMgr->RemoveCallback(StateType::Tool, "F1");
	evMgr->RemoveCallback(StateType::Tool, "F2");
}

void State_Tool::Draw() {
	sf::RenderWindow* window = m_stateMgr->
		GetContext()->m_wind->GetRenderWindow();

	window->draw(m_introSprite);
}

void State_Tool::F1(EventDetails* l_details)
{
	m_stateMgr->SwitchTo(StateType::MainMenu);
	m_stateMgr->Remove(StateType::Tool);
}

void State_Tool::F2(EventDetails* l_details)
{

}


void State_Tool::Update(const sf::Time& l_time) {}
void State_Tool::Activate() {}
void State_Tool::Deactivate() {}
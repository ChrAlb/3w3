#include "State_MainMenu.h"
#include "StateManager.h"

State_MainMenu::State_MainMenu(StateManager* l_stateManager)
	: BaseState(l_stateManager){}

State_MainMenu::~State_MainMenu(){}

void State_MainMenu::OnCreate() {

	sf::Vector2u windowSize = m_stateMgr->GetContext()
		->m_wind->GetRenderWindow()->getSize();

	TextureManager* textureMgr = m_stateMgr->GetContext()->m_textureManager;
	textureMgr->RequireResource("BgMenu");
	m_bgSprite.setTexture(*textureMgr->GetResource("BgMenu"));
	m_bgSprite.setOrigin(textureMgr->GetResource("BgMenu")->getSize().x / 2.0f,
		textureMgr->GetResource("Intro")->getSize().y / 2.0f);
    m_bgSprite.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

	GUI_Manager* gui = m_stateMgr->GetContext()->m_guiManager;
	gui->LoadInterface(StateType::MainMenu, "MainMenu.interface", "MainMenu");
	gui->GetInterface(StateType::MainMenu, "MainMenu")->SetPosition(sf::Vector2f(250.f, 168.f));

	EventManager* eMgr = m_stateMgr->GetContext()->m_eventManager;
	eMgr->AddCallback(StateType::MainMenu, "MainMenu_Play", &State_MainMenu::Play, this);
	eMgr->AddCallback(StateType::MainMenu, "MainMenu_LevEdit", &State_MainMenu::LevEdit, this);
	eMgr->AddCallback(StateType::MainMenu, "MainMenu_Quit", &State_MainMenu::Quit, this);
	
}

void State_MainMenu::OnDestroy() {
	m_stateMgr->GetContext()->m_guiManager->RemoveInterface(StateType::MainMenu, "MainMenu");
	EventManager* eMgr = m_stateMgr->GetContext()->m_eventManager;
	eMgr->RemoveCallback(StateType::MainMenu, "MainMenu_Play");
	eMgr->RemoveCallback(StateType::MainMenu, "MainMenu_LevEdit");
	eMgr->RemoveCallback(StateType::MainMenu, "MainMenu_Quit");
	eMgr->RemoveCallback(StateType::MainMenu, "Key_F1");
	eMgr->RemoveCallback(StateType::MainMenu, "Key_F2");
}

void State_MainMenu::Activate(){
	if (m_stateMgr->HasState(StateType::Game)
		&& m_labels[0].getString() != "RESUME")
	{
		m_labels[0].setString(sf::String("RESUME"));
	} else {
		m_labels[0].setString(sf::String("PLAY"));
	}

	sf::FloatRect rect = m_labels[0].getLocalBounds();
		m_labels[0].setOrigin(rect.left + rect.width / 2.0f,
		rect.top + rect.height / 2.0f);
}


void State_MainMenu::Draw(){
	sf::RenderWindow* window = m_stateMgr->
		GetContext()->m_wind->GetRenderWindow();
	window->draw(m_bgSprite);
	window->draw(m_text);
	for(int i = 0; i < 3; ++i){
		window->draw(m_rects[i]);
		window->draw(m_labels[i]);
	}
}

void State_MainMenu::Play(EventDetails* l_details)
{
}

void State_MainMenu::LevEdit(EventDetails* l_details)
{
}

void State_MainMenu::Quit(EventDetails* l_details)
{
}

void State_MainMenu::Update(const sf::Time& l_time){}
void State_MainMenu::Deactivate(){}
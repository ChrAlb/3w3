#include "State_Editor.h"
#include "StateManager.h"


State_Editor::State_Editor(StateManager* l_stateManager)
	: BaseState(l_stateManager) {}

State_Editor::~State_Editor()
{
}

void State_Editor::OnCreate()
{
	EventManager* evMgr = m_stateMgr->GetContext()->m_eventManager;
    evMgr->AddCallback(StateType::Game, "Key_Escape", &State_Editor::MainMenu, this);

	m_Map_Size = { 50,50 };

	m_TileView.reset(sf::FloatRect(0, 0, 400, sf::VideoMode::getDesktopMode().height));
	m_DesignView.reset(sf::FloatRect(0, 0, sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height));
	m_LevelView.reset(sf::FloatRect(0, 0, (m_Map_Size.x * Sheet::Tile_Size), (m_Map_Size.y * Sheet::Tile_Size)));
	m_LayerView.reset(sf::FloatRect(0, 0, sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height));

	m_TileLevelSize.x = 6;
	m_TileLevelSize.y = 9;

	m_LevelSize.x = 65;
	m_LevelSize.y = 21;

	m_pos_TileArray.x = 50;
	m_pos_TileArray.y = 400;

	m_pos_DesingArray.x = 400;
	m_pos_DesingArray.y = 0;

	TileFläche = { m_pos_TileArray.x,m_pos_TileArray.y, m_TileLevelSize.x * Sheet::Tile_Size,   m_TileLevelSize.y * Sheet::Tile_Size };
	DesignFläche = { m_pos_DesingArray.x, m_pos_DesingArray.y,m_LevelSize.x * Sheet::Tile_Size, m_LevelSize.y * Sheet::Tile_Size };

	m_gameMap = new Map(m_stateMgr->GetContext(), this);
	m_gameMap->LoadMap("media/Maps/editordefault.map");
	
}

void State_Editor::OnDestroy()
{
	EventManager* evMgr = m_stateMgr->GetContext()->m_eventManager;
		evMgr->RemoveCallback(StateType::Game, "Key_Escape");
}

void State_Editor::Activate()
{
}

void State_Editor::Deactivate()
{
}

void State_Editor::Update(const sf::Time& l_time)
{
}

void State_Editor::Draw()
{
	sf::RenderWindow* window = m_stateMgr->
		GetContext()->m_wind->GetRenderWindow();

	window->setView(m_TileView);
	
}

void State_Editor::MainMenu(EventDetails* l_details)
{
	m_stateMgr->SwitchTo(StateType::MainMenu);
}

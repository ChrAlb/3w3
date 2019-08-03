#include "State_Tool.h"
#include "StateManager.h"

State_Tool::State_Tool(StateManager* l_stateManager)
	: BaseState(l_stateManager) {}

State_Tool::~State_Tool() {}

void State_Tool::OnCreate() {
	sf::Vector2u windowSize = m_stateMgr->GetContext()
		->m_wind->GetRenderWindow()->getSize();


	EventManager* evMgr = m_stateMgr->GetContext()->m_eventManager;
	evMgr->AddCallback(StateType::Tool, "ToolExit", &State_Tool::Toolexit, this);
	evMgr->AddCallback(StateType::Tool, "Tool1", &State_Tool::Tools1, this);
}

void State_Tool::OnDestroy() {
	

	EventManager* evMgr = m_stateMgr->GetContext()->m_eventManager;
	
	evMgr->RemoveCallback(StateType::Tool, "Toolexit");
	evMgr->RemoveCallback(StateType::Tool, "Tool1");
}

void State_Tool::Draw() {
	sf::RenderWindow* window = m_stateMgr->
		GetContext()->m_wind->GetRenderWindow();

	window->draw(m_text);
}

void State_Tool::Toolexit(EventDetails* l_details)
{

	m_stateMgr->SwitchTo(StateType::MainMenu);
	m_stateMgr->Remove(StateType::Tool);
}


// Tool1 = Macht Sheet aus Tiles
void State_Tool::Tools1(EventDetails* l_details)
{
	TileSize = 256;
	BrickCounter = 1;

	DestFName = "C:\\Test\\tilesheet2048.png";


	
	if (!DestinationFile.loadFromFile(DestFName));
	{
		printf("Error DestFile");

	}
	
	for(i=0;i<8;i++)
		for (j = 0; j < 8; j++)
		{
			if (
				(i == 0) || 
				
				( (j == 0) && (i==1 ))
				)
				;
			else
			{
				std::string name;
				name = "C:\\Test\\Brick (" ;

				std::stringstream ss;
				ss << BrickCounter;
				std::string str = ss.str();
				name = name + str + ").png";

				SourceFName = name;

				if (!SourceFiles.loadFromFile(SourceFName))
				{
					printf("Error SourceFile");
				}

				DestinationFile.copy(SourceFiles, (j) * TileSize, (i) * TileSize, { 0,0,TileSize,TileSize }, false);
				BrickCounter++;

			}

			
		}
	DestinationFile.saveToFile(DestFName);
}

void State_Tool::Update(const sf::Time& l_time) {}
void State_Tool::Activate() {}
void State_Tool::Deactivate() {}
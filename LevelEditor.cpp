
#include "LevelEditor.h"
#include "StateManager.h"
#include <sstream>
#include <fstream>

#include <iostream>


LevelEditor::LevelEditor(StateManager* l_stateManager)
	: BaseState(l_stateManager) 
{
	windo = m_stateMgr->GetContext()->m_wind->GetRenderWindow();
	windo->setView(m_DesignView);
}

LevelEditor::~LevelEditor()  {}



void LevelEditor::set_const()
{
	m_TileLevelSize.x = 6;
	m_TileLevelSize.y = 9;

	m_LevelSize.x = 65;
	m_LevelSize.y = 21;

	m_pos_TileArray.x = 50;
	m_pos_TileArray.y = 400;

	m_pos_DesingArray.x = 400;
	m_pos_DesingArray.y = 0;

	TileFläche = { m_pos_TileArray.x,m_pos_TileArray.y, m_TileLevelSize.x * TILE_SIZE,   m_TileLevelSize.y * TILE_SIZE };
	DesignFläche = { m_pos_DesingArray.x, m_pos_DesingArray.y,m_LevelSize.x*TILE_SIZE, m_LevelSize.y*TILE_SIZE };

	m_inTileView = false;
	m_inDesignView = false;

	m_Tile_picked = false;

	m_oldpos = { 0,0 };

	m_picked_TileNumber = 0;

	m_LevelArray.setPrimitiveType(Quads);
	m_LevelArray.resize(m_LevelSize.x*m_LevelSize.y*VERTS_IN_QUAD);

}

void LevelEditor::OnCreate()
{
	sf::Vector2u windowSize = m_stateMgr->GetContext()->m_wind->GetRenderWindow()->getSize();

	LevelEditor::set_const();
	
	m_TileView.reset(sf::FloatRect(0,0,400, VideoMode::getDesktopMode().height));
	m_DesignView.reset(sf::FloatRect(0,0, VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height));
	m_LevelView.reset(sf::FloatRect(0, 0,(m_LevelSize.x*TILE_SIZE) , (m_LevelSize.y*TILE_SIZE) ));
	m_LayerView.reset(sf::FloatRect(0, 0, VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height));

	m_TileSheet.load(Textures::Tileset1, "graphics/tiles_sheet1.png");
	//m_DefaultTile.load(Textures::LevelEditorSet,"graphics/default_tile.png");
	

	GUI_Manager* gui = m_stateMgr->GetContext()->m_guiManager;
	gui->LoadInterface(StateType::LevelEditor, "LevelEditor.interface", "LevelEditor");
	gui->GetInterface(StateType::LevelEditor, "LevelEditor")->SetPosition(sf::Vector2f(50.f, 950.f));
	

	EventManager* evMgr = m_stateMgr->GetContext()->m_eventManager;
    evMgr->AddCallback(StateType::LevelEditor, "Mouse_Left", &LevelEditor::MouseClick, this);
	evMgr->AddCallback(StateType::LevelEditor, "LevelEditor_OK", &LevelEditor::OK, this);
	evMgr->AddCallback(StateType::LevelEditor, "LevelEditor_Abbrechen", &LevelEditor::Abbrechen, this);
	evMgr->AddCallback(StateType::LevelEditor, "Key_F2", &LevelEditor::Load, this);
	

	m_ArrayLevel = new int*[m_LevelSize.y];


	for (int i = 0; i < m_LevelSize.y; ++i)
	{
		m_ArrayLevel[i] = new int[m_LevelSize.x];
	}

	for (int x = 0; x < m_LevelSize.x; x++)
	{
		for (int y = 0; y < m_LevelSize.y; y++)
		{
			m_ArrayLevel[y][x] = 50 ;
		}
	}

	TileBackground.setPosition(0, 0);
	TileBackground.setSize(Vector2f(m_pos_DesingArray.x, VideoMode::getDesktopMode().height));
	TileBackground.setFillColor(sf::Color(234, 162,43));

	
	LevelEditor::read_Tileset();
	LevelEditor::manage_ArrayLevel();
	
	windo->setView(m_DesignView);

	
}

void LevelEditor::OnDestroy()
{
	
    EventManager* evMgr = m_stateMgr->GetContext()->m_eventManager;
	evMgr->RemoveCallback(StateType::LevelEditor, "LevelEditor_OK");
	evMgr->RemoveCallback(StateType::LevelEditor, "LevelEditor_Abbrechen");
	evMgr->RemoveCallback(StateType::LevelEditor, "MMouse_Left");
} 



void LevelEditor::Activate()
{
	;
}

void LevelEditor::Deactivate()
{
	;
}



void LevelEditor::read_Tileset()
{
	m_TileArray.setPrimitiveType(Quads);
	m_TileArray.resize(m_TileLevelSize.x*m_TileLevelSize.y*VERTS_IN_QUAD);

	int currentVertex = 0;
	int verticalOffset = 0;
	int verticalcounter = 0;
	
	
	for (int y = 0; y < m_TileLevelSize.y; y++)
	{
		for (int x = 0; x < m_TileLevelSize.x; x++)
		{		
			m_TileArray[currentVertex + 0].position = Vector2f(m_pos_TileArray.x+x*TILE_SIZE, m_pos_TileArray.y+y* TILE_SIZE);
			m_TileArray[currentVertex + 1].position = Vector2f(m_pos_TileArray.x +x*TILE_SIZE + TILE_SIZE, m_pos_TileArray.y +y* TILE_SIZE);
			m_TileArray[currentVertex + 2].position = Vector2f(m_pos_TileArray.x +x*TILE_SIZE + TILE_SIZE, m_pos_TileArray.y +y* TILE_SIZE + TILE_SIZE);
			m_TileArray[currentVertex + 3].position = Vector2f(m_pos_TileArray.x +x*TILE_SIZE, m_pos_TileArray.y +y* TILE_SIZE + TILE_SIZE);
			
			verticalOffset = verticalcounter * TILE_SIZE;
			

			m_TileArray[currentVertex + 0].texCoords = Vector2f(0, 0 + verticalOffset);
			m_TileArray[currentVertex + 1].texCoords = Vector2f(TILE_SIZE, 0 + verticalOffset);
			m_TileArray[currentVertex + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);
			m_TileArray[currentVertex + 3].texCoords = Vector2f(0, TILE_SIZE + verticalOffset);

			currentVertex = currentVertex + VERTS_IN_QUAD;
			verticalcounter++;
		}
		
	}

}



bool LevelEditor::mouse_pos_in(FloatRect Fläche, Vector2f pos)
{
	if ( 
		(pos.x > Fläche.left) &&  (pos.x < Fläche.left + Fläche.width) &&
		(pos.y > Fläche.top) && (pos.y < Fläche.top + Fläche.height)
	   )
		return true;
	else
		return false;
}

void LevelEditor::draw_mousepose_inTileView(FloatRect field)
{
	windo->setView(m_LayerView);
	sf::RectangleShape rectangle;
	rectangle.setPosition(field.left,field.top);
	rectangle.setSize(sf::Vector2f(field.width,field.height));
	rectangle.setOutlineThickness(3);
	rectangle.setOutlineColor(sf::Color::Black);
	rectangle.setFillColor(sf::Color::Transparent);
	windo->draw(rectangle);
}

FloatRect LevelEditor::calculateActualTile(Vector2f mouspos)
{
	FloatRect Tile;

	Tile.left = ((int) mouspos.x / TILE_SIZE) * TILE_SIZE;
	Tile.top = ((int) mouspos.y / TILE_SIZE ) * TILE_SIZE ;
	Tile.width = TILE_SIZE;
	Tile.height = TILE_SIZE;

	return Tile;
}

void LevelEditor::MouseClick(EventDetails * l_details)
{
	SharedContext* context = m_stateMgr->GetContext();
	sf::Vector2i mousePos = l_details->m_mouse;

	if (m_inTileView)
	{
		m_Tile_picked = true;
		m_ClickedTile.left = ((int)mousePos.x / TILE_SIZE) * TILE_SIZE;
		m_ClickedTile.top = ((int)mousePos.y / TILE_SIZE) * TILE_SIZE;
		m_ClickedTile.width = TILE_SIZE;
		m_ClickedTile.height = TILE_SIZE;

		m_picked_TileNumber = Calc_TileNumber(mousePos);
	}


	if (m_inDesignView && m_Tile_picked)
	{
		windo->setView(m_DesignView);


		Vector2f pixpos = windo->mapPixelToCoords(sf::Mouse::getPosition());

		int x = pixpos.x / TILE_SIZE;
		int y = pixpos.y / TILE_SIZE;

		m_ArrayLevel[y][x] = m_picked_TileNumber;

		LevelEditor::manage_ArrayLevel();

	} 

}

void LevelEditor::OK(EventDetails * l_details)
{
	GUI_Interface* menu = m_stateMgr->GetContext()->m_guiManager->GetInterface(StateType::LevelEditor, "LevelEditor");
	std::string name = menu->GetElement("DatName")->GetText();
	name = name + ".txt";

	string path;
	path = Utils::GetWorkingDirectory();
	path = path + "\\levels\\";
	
	std::fstream os(path + name, std::ios::out | std::ios::trunc);
	LevelEditor::saveLevelArray(os);

	m_stateMgr->Remove(StateType::LevelEditor);
	m_stateMgr->SwitchTo(StateType::MainMenu);

	
}

void LevelEditor::Abbrechen(EventDetails * l_details)
{
	m_stateMgr->Remove(StateType::LevelEditor);
	m_stateMgr->SwitchTo(StateType::MainMenu);
}

void LevelEditor::Load(EventDetails * l_details)
{
	GUI_Interface* menu = m_stateMgr->GetContext()->m_guiManager->GetInterface(StateType::LevelEditor, "LevelEditor");
	std::string name = menu->GetElement("DatName")->GetText();
	name = name + ".txt";
	
	string path;
	path = Utils::GetWorkingDirectory();
	path = path + "\\levels\\";

	std::fstream os(path + name, std::ios::in );
	LevelEditor::loadLevelArray(os);

	LevelEditor::manage_ArrayLevel();
}



int LevelEditor::Calc_TileNumber(Vector2i mousepos)
{

	Vector2f pos;
	int Number;

	mousepos.x = mousepos.x - m_pos_TileArray.x;
	mousepos.y = mousepos.y - m_pos_TileArray.y;

	pos.x = (int)mousepos.x / TILE_SIZE;
	Number = pos.x;

	pos.y = (int)mousepos.y / TILE_SIZE;

	Number = Number + pos.y*m_TileLevelSize.x;

	return Number;
}

void LevelEditor::manage_ArrayLevel()
{
	int currentVertex = 0;

	for (int x = 0; x < m_LevelSize.x; x++)
	{
		for (int y = 0; y < m_LevelSize.y; y++)
		{
			m_LevelArray[currentVertex + 0].position = Vector2f(x*TILE_SIZE, y* TILE_SIZE);
			m_LevelArray[currentVertex + 1].position = Vector2f(x*TILE_SIZE + TILE_SIZE, y* TILE_SIZE);
			m_LevelArray[currentVertex + 2].position = Vector2f(x*TILE_SIZE + TILE_SIZE, y* TILE_SIZE + TILE_SIZE);
			m_LevelArray[currentVertex + 3].position = Vector2f(x*TILE_SIZE, y* TILE_SIZE + TILE_SIZE);

			int verticalOffset = m_ArrayLevel[y][x] * TILE_SIZE;

			m_LevelArray[currentVertex + 0].texCoords = Vector2f(0, 0 + verticalOffset);
			m_LevelArray[currentVertex + 1].texCoords = Vector2f(TILE_SIZE, 0 + verticalOffset);
			m_LevelArray[currentVertex + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);
			m_LevelArray[currentVertex + 3].texCoords = Vector2f(0, TILE_SIZE + verticalOffset);

			currentVertex = currentVertex + VERTS_IN_QUAD;
		}
	}
}

std::ostream & LevelEditor::saveLevelArray(std::ostream & os)
{

	for (int i = 0; i < m_LevelSize.y; ++i)
	{
		for (int j = 0; j < m_LevelSize.x; ++j)
		{
			if (m_ArrayLevel[i][j] < 10)
				os << "0";

			os << m_ArrayLevel[i][j] ;
			
			if (j < m_LevelSize.x - 1)
				os << ",";
		}
		os << "\n";
	}
	return os;
}

void LevelEditor::loadLevelArray(std::istream & os)
{
	string row;
	int y = 0;
	std::string delimiter = ",";


	while (os >> row)
	{
		int x = 0;
		std::string token;
		size_t pos = 0;

		while ((pos = row.find(delimiter)) != std::string::npos)
		{
			token = row.substr(0, pos);
			m_ArrayLevel[y][x] = std::stoi(token);
			row.erase(0, pos + delimiter.length());
			x++;
		}

		y++;
	}
 }




void LevelEditor::Update(const sf::Time & l_time) 

{
	
	mouseposition = static_cast <sf::Vector2f> (sf::Mouse::getPosition());
	
	if (mouse_pos_in(TileFläche, mouseposition))
	{
		m_ActualTile = LevelEditor::calculateActualTile(mouseposition);
		m_inTileView = true;
    }
	else m_inTileView = false;
	

	if (mouse_pos_in(DesignFläche, mouseposition))    
	{
		
		if (Keyboard::isKeyPressed(Keyboard::Right))

		{
			m_DesignView.move(1, 0);
		}


		if (Keyboard::isKeyPressed(Keyboard::Left))

		{
			m_DesignView.move(-1, 0);
		}
		
		m_inDesignView = true;

		
	} 
	else
		m_inDesignView = false;

}

void LevelEditor::Draw()
{
	
	windo->clear(sf::Color(255,160,0));
	
	//window->setView(m_DesignView);

	windo->setView(m_DesignView);
	m_DesignView.setViewport(sf::FloatRect(0.2, 0, 1, 1));
	//window->draw(m_LevelArray, &m_DefaultTile.get(Textures::LevelEditorSet));
	windo->draw(m_LevelArray, &m_TileSheet.get(Textures::Tileset1));
	
	windo->setView(m_TileView);
	windo->draw(TileBackground);
	m_TileView.setViewport(sf::FloatRect(0, 0, 0.2, 1));
	
    windo->draw(m_TileArray, &m_TileSheet.get(Textures::Tileset1));

	windo->setView(m_LevelView);
	m_LevelView.setViewport(sf::FloatRect(0, 0, 0.2, 0.2));
	
	windo->draw(m_LevelArray, &m_TileSheet.get(Textures::Tileset1));
	
	if (m_inTileView)
	   LevelEditor::draw_mousepose_inTileView(m_ActualTile);
	
	if (m_Tile_picked)
	{

		windo->setView(m_LayerView);
		sf::RectangleShape rectangle;
		rectangle.setPosition(m_ClickedTile.left, m_ClickedTile.top);
		rectangle.setSize(sf::Vector2f(m_ClickedTile.width, m_ClickedTile.height));
		rectangle.setOutlineThickness(6);
		rectangle.setOutlineColor(sf::Color::Blue);
		rectangle.setFillColor(sf::Color::Transparent);

        windo->draw(rectangle);

		

	}

}

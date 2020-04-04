#pragma once
#include <SFML\Graphics.hpp>
#include "BaseState.h"

#include "EventManager.h"
#include "SharedContext.h"

#include <string>

using namespace sf;

class LevelEditor : public BaseState
{
public:

	LevelEditor(StateManager* l_stateManager);
	~LevelEditor();
	
	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& l_time);
	void Draw();

	
	void read_Tileset();
	
    void set_const();
	bool mouse_pos_in(FloatRect Fläche, Vector2f pos);

	void draw_mousepose_inTileView(FloatRect field);

	FloatRect calculateActualTile(Vector2f mouspos);

	void MouseClick(EventDetails* l_details);
    void OK(EventDetails* l_details);
	void Abbrechen(EventDetails* l_details);
	void Load(EventDetails* l_details);
	
	int Calc_TileNumber(Vector2i mousepos);

	void manage_ArrayLevel();

	std::ostream& saveLevelArray(std::ostream& os);

	void loadLevelArray(std::istream& os);

	
private:

	int m_NumberofFiles;
	
	Vector2i   m_LevelDimension;
	View       m_TileView;
	View       m_DesignView;
	View       m_LevelView;
	View       m_LayerView;

	Vector2f  m_TileLevelSize;
	Vector2f  m_LevelSize;
	Vector2f  m_pos_TileArray;
	Vector2f  m_pos_DesingArray;

	Vector2f  m_oldpos;

	int     VERTS_IN_QUAD = 4;
	int     TILE_SIZE = 50;

	String     m_tileFile;
	String     m_LevelFile

	VertexArray  m_TileArray;
	VertexArray  m_LevelArray;

	TextureHolder m_TileSheet;
	TextureHolder m_DefaultTile;

	FloatRect TileFläche;
	FloatRect DesignFläche;

	FloatRect m_ActualTile;
	FloatRect m_ClickedTile;
	
	Vector2f mouseposition;

	bool m_inTileView;
	bool m_Tile_picked;
	bool m_inDesignView;

	int m_picked_TileNumber;

	int** m_ArrayLevel = NULL;

	RectangleShape TileBackground;

	RenderWindow* windo;
	
	};

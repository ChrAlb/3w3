#include "Game.h"


Game::Game(): m_window("3w3", sf::Vector2u(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height)),
	m_stateManager(&m_context), m_entityManager(&m_context, 100), m_guiManager(m_window.GetEventManager(),&m_context)


{
	m_clock.restart();
	srand(time(nullptr));

	m_context.m_wind = &m_window;
	m_context.m_eventManager = m_window.GetEventManager();
	m_context.m_textureManager = &m_textureManager;
	m_context.m_fontManager = &m_fontManager;
	
	m_context.m_guiManager = &m_guiManager;
	m_context.m_entityManager = &m_entityManager;
	m_fontManager.RequireResource("Main");
	m_stateManager.SwitchTo(StateType::Intro);
}

Game::~Game()
{
	m_fontManager.ReleaseResource("Main");
}

sf::Time Game::GetElapsed(){ return m_clock.getElapsedTime(); }
void Game::RestartClock(){ m_elapsed = m_clock.restart(); }
Window* Game::GetWindow(){ return &m_window; }


void Game::Update(){
	m_window.Update();
	m_stateManager.Update(m_elapsed);

	
	
	
	m_guiManager.Update(m_elapsed.asSeconds());
	//m_context.m_guiManager->Update(m_elapsed.asSeconds());
	GUI_Event guiEvent;
	while (m_context.m_guiManager->PollEvent(guiEvent))
	{
		m_window.GetEventManager()->HandleEvent(guiEvent);
	}
}

void Game::Render(){
	m_window.BeginDraw();
	// Render here.
	m_stateManager.Draw();

	// Debug.
	if(m_context.m_debugOverlay.Debug()){
		m_context.m_debugOverlay.Draw(m_window.GetRenderWindow());
	}
	// End debug.

	sf::View CurrentView = m_window.GetRenderWindow()->getView();
	m_window.GetRenderWindow()->setView(m_window.GetRenderWindow()->getDefaultView());
	m_context.m_guiManager->Render(m_window.GetRenderWindow());
	m_window.GetRenderWindow()->setView(CurrentView);

	m_window.EndDraw();
}

void Game::LateUpdate(){
	m_stateManager.ProcessRequests();
	RestartClock();
}
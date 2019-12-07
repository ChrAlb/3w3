#include "Bullet.h"
#include "EntityManager.h"
#include "StateManager.h"
#include "Map.h"
#include "SharedContext.h"


Bullet::Bullet(EntityManager* l_entityMgr)
	:Character(l_entityMgr), m_hasDestination(false) 
{
	Load("Bullet.char");
	m_type = EntityType::Bullet;

	
}

Bullet::~Bullet() {}

void Bullet::OnEntityCollision(EntityBase* l_collider, bool l_attack)
{
	
	/*
	if (m_state == EntityState::Dying) { return; }
	if (l_attack) { return; }
	if (l_collider->GetType() != EntityType::Player) { return; }
	Character* player = (Character*)l_collider;
	SetState(EntityState::Attacking);
	player->GetHurt(1);
	if (m_position.x > player->GetPosition().x) {
		player->AddVelocity(-m_speed.x, 0);
		m_spriteSheet.SetDirection(Direction::Left);
	}
	else {
		player->AddVelocity(m_speed.y, 0);
		m_spriteSheet.SetDirection(Direction::Right);
	} */
}

void Bullet::Update(float l_dT) {
	
	Character::Update(l_dT);
	
	if (m_entitydir == Direction::Left)
		Character::Move(Direction::Left);
	else
		Character::Move(Direction::Right);
	
	//Map* map = m_entityManager->GetContext()->m_gameMap;

	//float tt= map->GetMapSize().x*map->GetTileSize();
	

	if (m_position.x < 1 );
	    m_state = EntityState::Dying;


	
	
}




#pragma once
#include "Character.h"

class Bullet : public Character {
public:
	Bullet(EntityManager* l_entityMgr);
	~Bullet();

	void OnEntityCollision(EntityBase* l_collider, bool l_attack);
	void Update(float l_dT);
private:
	sf::Vector2f m_destination;
	bool m_hasDestination;
	
};
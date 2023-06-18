#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"

class Player : public Entity
{
private:
	//Variables

	//Init functions
	void initVariables();
	void initComponents();

public:
	Player(float x, float y, sf::Texture& texture_sheet);
	virtual ~Player();

	//Functions
	void update(const float& dt, const float windowWidth, const float windowHeight);
};
#endif
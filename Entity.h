#ifndef ENTITY_H
#define ENTITY_H

#include "HitboxComponent.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"

class Entity
{
private:
	void initVariables();
protected:
	
	sf::Sprite sprite;
	HitboxComponent* hitboxComponent;
	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;

public:
	Entity();
	virtual ~Entity();

	//Comp functions
	void setTexture(sf::Texture& texture); 
	void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
	void createAnimationComponent(sf::Texture& texture_sheet);
	void createHitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);

	//Functions
	virtual void setPosition(const float x, const float y);
	virtual void move(const float x, const float y, const float& dt);

	bool checkEntityCollision(Entity& entity);
	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget& target);

};

#endif // !ENTITY_H

#pragma once
#include "Entity.h"

/// Class which defines bullet objects
/// 
/// Entity is it's parent class
class Bullet : public Entity
{
private:
	/// Stores shape and color of the bullet
	sf::RectangleShape bullet_shape;
	/// Indicates wheter this bullet was shot or not
	bool isShot;
	/// Indicates intervals between every shot (How fast can player shoot)
	int shootTimer;
public:
	/// Bullet multi-argument constructor
	/// 
	/// @param pos			Bullet's initial position
	/// @param size			Size of the bullet
	/// @param sht_timer	shootTimer value
	Bullet(sf::Vector2f pos, sf::Vector2f size, int sht_timer);
	/// Bullet destructor
	~Bullet();
	/// Getter used for getting bullet's shape
	sf::RectangleShape getShape();
	/// Resets position to given value
	/// 
	/// @param pos			New position
	void resetPos(sf::Vector2f pos);
	/// Getter which returns isShot value
	bool getIsShot();
	/// Sets isShot value to True
	void isShotTrue();
	/// Sets isShot value to False
	void isShotFalse();
	/// Getter which returns shot timer
	int getShotTimer();
};


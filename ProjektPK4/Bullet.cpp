#include "Bullet.h"

Bullet::Bullet(sf::Vector2f pos, sf::Vector2f size, int sht_timer)
{
	bullet_shape.setSize(size);
	bullet_shape.setFillColor(sf::Color::Yellow);
	bullet_shape.setPosition(pos);
	isShot = false;
	shootTimer = sht_timer;
} 

Bullet::~Bullet()
{
	std::cout << "Bullet object destroyed...\n";
}

sf::RectangleShape Bullet::getShape()
{
	return bullet_shape;
}

void Bullet::resetPos(sf::Vector2f pos)
{
	bullet_shape.setPosition(pos);
}

bool Bullet::getIsShot()
{
	return isShot;
}

void Bullet::isShotTrue()
{
	isShot = true;
}

void Bullet::isShotFalse()
{
	isShot = false;
}

int Bullet::getShotTimer()
{
	return shootTimer;
}
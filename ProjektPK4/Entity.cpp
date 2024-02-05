#include "Entity.h"


Entity::Entity()
{
	max_lives = lives = 2;
	health_bar_offset = 0;
	std::cout<<"Entity created...\n";
}

Entity::Entity(int lives_ct, sf::Vector2f pos)
{
	max_lives = lives = lives_ct;
	position = pos;
	health_bar.setFillColor(sf::Color(140, 0, 25));
	health_bar.setPosition(pos + sf::Vector2f(0.f,30.f));
	health_bar_offset = 0;
}

Entity::~Entity()
{
	std::cout << "Entity destructed...\n";
}

void Entity::setTexture(std::string path)
{
	if (!texture.loadFromFile(path))
		throw "Could not load selected png path";
}

void Entity::loadSpritesFromSheet(int spriteWidth, int spriteHeight, int numRows, int numColumns)
{
	spriteVector.reserve(numRows * numColumns);

	for (int row = 0; row < numRows; row++)
	{
		for (int col = 0; col < numColumns; col++)
		{
			int x = col * spriteWidth;
			int y = row * spriteHeight;
			sf::Sprite sprite(texture, sf::IntRect(x, y, spriteWidth, spriteHeight));
			spriteVector.push_back(sprite);
		}
	}
	health_bar.setSize(sf::Vector2f(spriteVector[0].getGlobalBounds().width, 9.f));
	health_bar_offset = spriteVector[0].getGlobalBounds().width / max_lives;
}

void Entity::setSprite(int num_of_sprite, sf::Vector2f pos)
{
	sprite = spriteVector[num_of_sprite];
	sprite.setPosition(position);
}

sf::Vector2f& Entity::getPos()
{
	return position;
}

sf::Vector2f Entity::getCenter()
{
	return sf::Vector2f(sprite.getPosition().x + (sprite.getGlobalBounds().width / 2 - 2.f),
		sprite.getPosition().y + (sprite.getGlobalBounds().height / 2) - 35.f);
}

sf::Sprite& Entity::getSprite()
{
	return sprite;
}

void Entity::Draw(sf::RenderWindow& target)
{
	target.draw(sprite);
	health_bar.setPosition(sprite.getPosition() + sf::Vector2f(0.f,-40.f));
	target.draw(health_bar);
}

int &Entity::getLives()
{
	return lives;
}

void Entity::livesDecr()
{
	lives--;
}

void Entity::setPos(sf::Vector2f pos)
{
	position = pos;
	sprite.setPosition(pos);
}

void Entity::Animation()
{
	sf::Vector2f tempPos2 = Entity::getSprite().getPosition();
	sf::Time tempTime = animation_clock.getElapsedTime();


	if (tempTime.asMilliseconds() >= freq_of_animation_switch)
	{
		currSprite++;
		if (currSprite == spriteVector.size())
		{
			currSprite = 0;
			setSprite(currSprite, Entity::getPos());
		}
		else
		{
			setSprite(currSprite, Entity::getPos());
		}
		animation_clock.restart();
		Entity::getSprite().setPosition(tempPos2);
	}
}

void Entity::setAnimationFrequency(int freq)
{
	freq_of_animation_switch = freq;
}

void Entity::updateHealthBar()
{

	health_bar.setSize(sf::Vector2f(health_bar.getSize().x - health_bar_offset, health_bar.getSize().y));
	
}
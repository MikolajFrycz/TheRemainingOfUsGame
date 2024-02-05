#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <string>
#include <vector>
#include <random>
#include <filesystem>

/// Entity is an abstract class which defines basic attributes and methods for players, npcs and more
/// 
/// E.g. in this program it is used for Player, Zombie and bullet
class Entity
{
private:
	/// Integer value which states how many lives an entity has
	int lives;
	/// Indicates maximum number of lifes (or initial number of lives)
	int max_lives;
	/// Indicates how many sprites and entity has
	int spriteCount = 0;
	/// Holds entity's texture (mainly used for loading sprites)
	sf::Texture texture;
	/// Used for holding a sprite (mainly used for loading sprites to a vector of sprites)
	sf::Sprite sprite;
	/// Vector of sprites which stores all the sprites and switches them to perform animations
	std::vector<sf::Sprite> spriteVector;
	/// Used for storing current position of an entity in a form of two floats
	sf::Vector2f position;
	/// Used for timing sprite switches (needed for animation)
	sf::Clock animation_clock;
	/// Indicates which sprite from a vector is currently used
	int currSprite = 0;
	/// Indicates how long should be the intervals between sprite switches in an animation
	int freq_of_animation_switch = 0;
	/// Rectangle-shaped bar used for displaying health
	sf::RectangleShape health_bar;
	/// Indicates size of the health bar offset when its shrinks along with decreasing lives value
	float health_bar_offset;

public:
	/// Default Entity constructor
	Entity();
	/// Entity multi-argument constructor
	/// 
	/// Used for setting starting values
	/// @param lives_ct			Indicates how many lives an entity should start with
	/// @param pos				Indicates what starting postition should an entity have
	Entity(int lives_ct, sf::Vector2f pos);
	/// Entity destructor
	virtual ~Entity();
	/// Setter used for setting texture attribute value
	/// 
	/// @param path				Path of an input file
	void setTexture(std::string path);
	/// Loads sprites from sheet and stores them in the vector
	/// 
	/// Sprites are loaded from a png file which consists of all the needed entity sprites
	/// @param spriteWidth		Width of one sprite (in pixels)
	/// @param spriteHeight		Height of the whole png
	/// @param numRows			Number of rows
	/// @param numColumns		Number of columns
	void loadSpritesFromSheet(int spriteWidth, int spriteHeight, int numRows, int numColumns);
	/// Used for setting a sprite and position
	/// 
	/// @param num_of_sprite	Index of wanted sprite
	/// @param pos				Wanted position
	void setSprite(int num_of_sprite, sf::Vector2f pos);
	/// Draws entity's sprite to a target window
	/// 
	/// @param target			Target window
	void Draw(sf::RenderWindow& target);
	/// Runs entity's animation
	void Animation();
	/// Getter used for getting position
	sf::Vector2f& getPos();
	/// Getter used for getting center of the entity
	sf::Vector2f getCenter();
	/// Getter used for getting entity's current sprite
	sf::Sprite& getSprite();
	/// Getter used for getting lives count
	int &getLives();
	/// Decrements lives count
	void livesDecr();
	/// Sets position to a new one
	///
	/// @param pos			New position
	void setPos(sf::Vector2f pos);
	/// Setter used for setting animation frequency
	/// 
	/// @param freq			Frequency of sprites switches
	void setAnimationFrequency(int freq);
	/// Refreshes healthbar, based on current lives count : max lives count ratio
	void updateHealthBar();
};
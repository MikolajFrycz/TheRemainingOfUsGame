#pragma once
#include "Entity.h"
#include "Player.h"

/// This class defines zombie objects which are enemies in this game
/// 
/// Different types of zombies can be created with this class. It also inherits from the Entity abstract class
class Zombie : public Entity
{
private:
	/// Clock variable which is used for spawning zombies
	sf::Clock spawn_clock;
	/// Holds the value of score gained after killing the zombie
	int score_value;
	/// Base frequency of the spawn
	int base_spawn_freq;
	/// Current frequency of the spawn
	int curr_spawn_freq;
	/// Count of zombies
	int basic_zombie_count = 0;
	/// Current lives count
	int curr_lives = Zombie::Entity::getLives();
	/// Base movement speed
	float base_mov_speed;
	/// Current movement speed
	float curr_mov_speed;
public:
	/// Zombie default constructor 
	Zombie();
	/// Multi argument constructor
	/// 
	/// @param score_val			Amount of score gained after killing
	/// @param lives_ct				No of lives
	/// @param spawn_freq_ms		Spawn frequency in ms
	/// @param pos					Initial position
	/// @param mov_spd				Initial movement speed
	Zombie(int score_val, int lives_ct, int spawn_freq_ms, sf::Vector2f pos, float mov_spd);
	/// Zombie Destructor
	~Zombie();
	/// Getter used for getting movement speed
	float getMovSpeed();
	/// Getter used for getting current spawn frequency
	int getCurrSpawnFreq();
	/// Setter used for setting current spawn frequency
	void setCurrSpawnFreq(int val);
	/// Getter used for getting Base spawn frequency
	int getBaseSpawnFreq();
	/// Setter used for setting Base spawn frequency
	void setBaseSpawnFreq(int val);
	/// setter used for setting current movement speed
	void setCurrMovSpeed(int val);
	/// Resets all Zombie attributes to their initial state
	void resetValues();
	/// Restarts spawn clock
	void restartClock();
	/// Getter used for getting spawn clock
	sf::Clock &getSpawnClock();
	/// Getter used for getting score value
	int getScoreValue();
};
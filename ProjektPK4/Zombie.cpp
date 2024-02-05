#include "Zombie.h"

Zombie::Zombie() { base_spawn_freq = curr_spawn_freq = 1000; base_mov_speed = curr_mov_speed = 5.f; score_value = 50; };

Zombie::Zombie(int score_val, int lives_ct, int spawn_freq_ms, sf::Vector2f pos, float mov_spd) : Entity(lives_ct, pos) 
{
	base_mov_speed = curr_mov_speed = mov_spd; base_spawn_freq = curr_spawn_freq = spawn_freq_ms; score_value = score_val;
}

Zombie::~Zombie() {};

float Zombie::getMovSpeed()
{
	return curr_mov_speed;
}

void Zombie::setCurrMovSpeed(int val)
{
	curr_mov_speed = val;
}

int Zombie::getCurrSpawnFreq()
{
	return curr_spawn_freq;
}

void Zombie::setCurrSpawnFreq(int val)
{
	if (val >= 0)
	{
		curr_spawn_freq = val;
	}
	else
		throw "spawn frequency cannot be < 0!";
}

int Zombie::getBaseSpawnFreq()
{
	return base_spawn_freq;
}

void Zombie::setBaseSpawnFreq(int val)
{
	if (val >= 0)
	{
		base_spawn_freq = curr_spawn_freq = val;
	}
	else
		throw "spawn frequency cannot be < 0!";
}

void Zombie::resetValues()
{
	curr_mov_speed = base_mov_speed;
	curr_spawn_freq = base_spawn_freq;
}

void Zombie::restartClock()
{
	spawn_clock.restart();
}

sf::Clock &Zombie::getSpawnClock()
{
	return spawn_clock;
}

int Zombie::getScoreValue()
{
	return score_value;
}
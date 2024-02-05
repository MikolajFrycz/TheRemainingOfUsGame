#pragma once 
#include "Bullet.h"
#include "Entity.h"
#include "HUD.h"
#include "SFML\Audio.hpp"
#include <future>

/// Player class defines players' objects
/// 
/// Player class defines all the attributes and methods needed for an Entity class to transform into player
class Player : public Entity
{
private:
	/// Maximum ammunition value
	int max_ammo;
	/// Current ammunition value
	int curr_ammo;
	/// Temporary ammo value needed for HUD
	int temp_ammo_for_hud;
	/// Vector of bullets
	std::vector<sf::RectangleShape> bullet_clip;
	/// Times shot animation sprite switches
	int shootAnimationTimer = 0;
	/// Defines wheter player is shooting or not
	bool isShooting = false;
	/// Defines wheter player is reloading or not
	bool isReloading = false;
	/// Defines player's beginning position
	sf::Vector2f start_pos;
	/// Defines the interval between shots
	int sht_timer;

public:
	/// Player default constructor
	Player();
	/// Player multi-argument constructor
	/// 
	/// @param lives_ct			Initial lives count
	/// @param max_amm			Maximum ammo initial value
	/// @param curr_amm			Current ammo initial value
	/// @param pos				Initial position
	Player(int lives_ct, int max_amm, int curr_amm, sf::Vector2f pos);
	/// Player destructor
	~Player();
	/// Resets ammo (Also on HUD)
	void resetAmmo(HUD& hud);
	/// Defines how the first player moves
	/// 
	/// @param windsize			size of window
	void player1Movement(int windsize);
	/// Defines how the second player moves
	/// 
	/// @param windsize			size of window
	void player2Movement(int windsize);
	/// Performs the reloading procedure and returns true if a reload was initiated
	/// 
	/// @param reloadClock		Used for counting the duration of reload
	/// @param key				Passed key variable defines which key is then used for reloading
	bool playerReload(sf::Clock& reloadClock, sf::Keyboard::Key key);
	/// This method is used for player's shooting and returns true if shot was initiated
	/// 
	/// While used in the game_loop, player can shoot bullets when a given key is pressed
	/// @param shootkey			Key used for shooting
	/// @param bullet			Bullet objects used for drawing them
	/// @param target_window	Target window for drawing
	/// @param reloadClock		Used for timing the reload
	/// @param hud				HUD is needed so that the ammo count on screen can be updated
	bool shootPistol(sf::Keyboard::Key shootkey, Bullet& bullet, sf::RenderWindow& target_window, sf::Clock& reloadClock, HUD& hud);
	/// Getter used for getting size of the bullet clip
	int getBulletClipSize();
	/// Getter which returns bullet clip
	std::vector<sf::RectangleShape>& getBulletClip();
	/// Getter which returns current ammo value as an integer
	int getCurrAmmo();
	/// Getter which returns max ammo value as an integer
	int getMaxAmmo();
	/// Getter which returns isShooting value
	bool getIsShooting();
	/// Getter which returns isReloading value
	bool getIsReloading();
	/// isShooting setter
	///
	/// @param val			IsShooting's new value
	void changeIsShootingValue(bool val);
	/// This method resets all player's attributes to their beginning state
	void playerReset();
	/// Used to perform player's shooting animation
	///
	/// @param reloadclock			Times the animatioon
	void shootingAnimation(sf::Clock reloadclock);
	/// Used to perform player's reloading animation
	///
	/// @param reloadclock			Times the reload animation
	/// @param hud					Updates hud when finished
	void reloadAnimation(sf::Clock reloadclock, HUD &hud);
	/// Polimorphic Draw method used to properly draw player to target window
	///
	/// @param target				Target window
	void Draw(sf::RenderWindow& target);
	/// Getter used for getting shotTimer
	int getShotTimer();
};
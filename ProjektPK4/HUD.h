#pragma once
#include "Entity.h"
#include <sstream>

/// This class is used for creating and displaying heads-up-display
///  
/// HUD can display current ammo, max ammo, score etc.
class HUD
{
private:
	/// Current score held in integer
	int score_count_integer;
	/// Current ammo as an integer
	int curr_ammo;
	/// Max ammo as an integer
	int max_ammo;
	/// Max initial ammo as an integer
	int max_ammo_begin;

	/// Font used in texts
	sf::Font font;
	/// Score count text
	sf::Text score_count;
	/// Max ammo text
	sf::Text max_ammo_text;
	/// Curr ammo text
	sf::Text curr_ammo_text;
	/// Text that displays AMMO word on screen
	sf::Text ammo_word_text;
	/// Text that displays SCORE word on screen
	sf::Text score_text;
	
	/// Player's name
	std::string player_name;
public:
	/// HUD default constructor
	HUD();
	/// Multi-argument constructor
	/// 
	/// @param score_start				Initial score int
	/// @param max_ammo_start			Initial max ammo
	/// @param player_name				Player's name
	/// @param font_path				Directory of the font file	
	HUD(int score_start, int max_ammo_start, std::string player_name, std::string font_path);
	/// HUD destructor
	~HUD();
	/// This method draws HUD on screen
	/// 
	/// @param target_window			Target window
	void drawHUD(sf::RenderWindow &target_window);
	/// Used to update score in HUD
	/// 
	/// @param added_ammount			Ammount added to the score
	void updateScore(int added_ammount);
	/// Changes max ammo value
	/// 
	/// @param new_ammo					New ammo value
	void changeMaxAmmo(int new_ammo);
	/// Adapts the hud for 2nd player
	/// 
	/// @param offset					Vector of floats which indicates how the hud should be moved from it's initial position
	void setHUDfor2ndPlayer(sf::Vector2f offset);
	/// This method changes current ammo
	///
	/// @param add_to_ammo				Ammount added to ammo
	void changeCurrAmmo(int add_to_ammo);
	/// Getter used for getting score as an int
	int &getScoreCountInt();
	/// Resets hud's values
	void resetHUD();
};


#pragma once
#include "Menu.h"

/// A Menu derived class which acts like a menu but is used as a deathscreen
/// 
/// It could also be called Deathscreen Menu
class DeathScreen : public Menu
{
	/// Deathscreen text options
	sf::Text dstext[4];
	/// Final score as an integer
	int score_ct_int;
public:
	/// Multi-argument constructor
	/// 
	/// @param k_time			Keytime value
	/// @param f_path			Font file's directory
	/// @param backgrd_path		Background png's directory
	DeathScreen(int k_time, std::string f_path, std::filesystem::path backgrd_path);
	/// This method initializes the deathscreen
	/// 
	/// @param window			Target window
	/// @param val				Score
	void setValues(sf::RenderWindow &window, int val);
	/// This method initializes deathscreen for two-player mode
	/// 
	/// @param window			Target window
	/// @param val				Score
	/// @param which_won		States which player won the game (had a higher score/draw also possible)
	void set2PlayerValues(sf::RenderWindow& window, int val, int which_won);
	/// Polimorphic moveDown method
	void moveDown();
};
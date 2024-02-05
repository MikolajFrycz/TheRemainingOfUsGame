#pragma once


#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <regex>
#include <ranges>
#include <algorithm>
#include <tuple>
#include <cmath>
#include <chrono>
#include <future>

//Custom classes
#include "Player.h"
#include "Menu.h"
#include "HUD.h"
#include "Zombie.h"
#include "DeathScreen.h"
#include "Functions.h"

//SFML libraries
#include "SFML\System.hpp"
#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\Network.hpp"
#include "SFML\Window.hpp"



/// This class is responsible for running the game loop
/// 
/// Game class uses all the created classes to process the game and run it using the run() method
class Game
{
private:
	/// Defines which case of the switch function (state of the game) should be run, e.g. menu, singleplayer game...
	int opt = -4;
	/// Window variable to which sprites are rendered
	sf::RenderWindow window;
	/// Used to load and hold background image texture
	sf::Texture texture;
	/// Used to load and hold game intro background image texture
	sf::Texture intro_texture;
	/// Used to load and hold game outro background image texture
	sf::Texture outro_texture;
	/// Used to load and hold game tutorial background image texture
	sf::Texture instruct_texture;
	/// Used to draw background image sprites on screen
	sf::Sprite background;
	/// Used to draw intro image sprites on screen
	sf::Sprite intro;
	/// Used to draw outro image sprites on screen
	sf::Sprite outro;
	/// Used to draw tutorial image sprites on screen
	sf::Sprite instruct;
	/// This vector is used to store zombies meant to be drawn on screen
	std::vector<Zombie> vec_of_zombies;

	/// This variable is used to draw player name on screen during the nickname input sequence
	sf::Text player_name_render;
	/// This vector stores players read from the input leaderboard file
	std::vector<sf::Text> vec_of_leaderboard_texts;
	/// This sf::Text variable holds text which asks for input prompt
	sf::Text nickInputPrompt;
	/// Used to carry font used for text generation
	sf::Font font;
	/// This string is used for storing player's nickname before writing it to output file
	std::string player_name;
	
	/// This pair is used for storing player's name and their highscore (used in the leaderboard sequence)
	std::tuple<int, std::string> player_n_highscore;
	/// This vector stores player_n_highscore pairs
	std::vector<std::tuple<int, std::string>> vec_of_pairs;
	/// This Path file is used for locating leaderboard file and operating on it
	std::filesystem::path leaderboard_file;
	/// This regex object is used for handling custom player name input
	std::regex input_regex;

	/// This buffer is used to load intro music from a file to a sf::Sound variable
	sf::SoundBuffer intro_buffer;
	/// This buffer is used to load main game music from a file to a sf::Sound variable
	sf::SoundBuffer game_buffer;
	/// This buffer is used to load deathscreen music from a file to a sf::Sound variable
	sf::SoundBuffer deathscreen_buffer;
	/// This buffer is used to load zombie sound from a file to a sf::Sound variable
	sf::SoundBuffer zombie_buffer;
	/// This buffer is used to load gun sound from a file to a sf::Sound variable
	sf::SoundBuffer shot_buffer;
	/// This buffer is used to load reload sound from a file to a sf::Sound variable
	sf::SoundBuffer reload_buffer;
	
	/// This variable is used to play intro music
	sf::Sound intro_sound;
	/// This variable is used to play main game music
	sf::Sound game_sound;
	/// This variable is used to play deathscreen music
	sf::Sound deathscreen_sound;
	/// This variable is used to play zombie sound (array is needed so that the sounds can overlay eachother)
	sf::Sound zombie_sound[24];
	/// This variable is used to play gun shot sound (array is needed so that the sounds can overlay eachother)
	sf::Sound shot_sound[24];
	/// This variable is used to play reload sound (array is needed so that the sounds can overlay eachother)
	sf::Sound reload_sound[24];
	/// This clock is needed to play the game intro for a specific time
	sf::Clock intro_outro_clk;

public:
	/// Game default constructor
	Game();
	/// Game destructor
	~Game();
	/// Run method is used to play the game in main function. This method is all that's needed for the game to run in main function
	void run();
	/// Update method is used for drawing all the video on screen as well as for the whole game mechanism
	/// 
	/// Update method draws all the necessary objects in a form of sprites or sf::Text objects
	/// @param player1			Player object used for singleplayer and for Player no 1 in two-player mode
	/// @param player2			Player object used for player no 2 in two-player mode
	/// @param basiczombie		Zombie class object used for creating basic-type zombies
	/// @param strong_zombie	Zombie class object used for creating strong-type zombies
	/// @param fast_zombie		Zombie class object used for creating fast-type zombies
	/// @param bullet			Bullet class object used for creating bullets in game that are later used by Player to shoot
	/// @param reloadClock		Variable used for timed sprite switches during reload animation
	/// @param reloadClock2		The same as reloadClock but for second player
	/// @param hud				HUD object used for drawing head-up display on screen
	/// @param hud2				The same as hud but for second player (used in two-player mode)
	/// @param menu				Object used for Main Menu handling in game
	/// @param deathscreen		Used for displaying game's deathscreen after the player dies
	/// @param duo_ds			Just like deathscreen but for two-player mode
	/// @param option			Used for defining which case is used, adequate to the Game class opt attribute
	void Update(Player& player1, Player& player2, Zombie& basiczombie, Zombie& strong_zombie, Zombie& fast_zombie, Bullet& bullet,
		sf::Clock& reloadClock, sf::Clock& reloadClock2, HUD& hud, HUD &hud2, Menu& menu, DeathScreen& deathscreen, DeathScreen &duo_ds, int& option);
	/// This method is used for processing different events
	/// 
	/// It processes events like: player nickname input or closing the game window with mouse
	/// @param zombie			Basic zombie type object. It's resetting methods are needed e.g. to reset spawn clocks before the game is initiated
	/// @param strong_zombie	Strong zombie type object. It's resetting methods are needed e.g. to reset spawn clocks before the game is initiated
	/// @param fast_zombie		Fast zombie type object. It's resetting methods are needed e.g. to reset spawn clocks before the game is initiated
	void processEvents(Zombie& zombie, Zombie& strong_zombie, Zombie& fast_zombie);
	/// Method used for spawning zombies
	/// 
	/// Its used for handling zombies' behaviour (spawning, collisions etc.) + some other aspects like updating hud's score count when a zombie is killed
	/// @param player1				Player class object used to decrease health when zombie touches the bottom
	/// @param zombie					Zombie class object for basic-type zombies
	/// @param strong_zombie			Zombie class object for strong-type zombies
	/// @param fast_zombie			Zombie class object for fast-type zombies
	/// @param hud					HUD object needed for updating HUD.
	void zombieHandling(Player& player1, Zombie& zombie, Zombie& strong_zombie, Zombie& fast_zombie, HUD& hud);
	/// Slightly altered version of zombieHandling method
	/// 
	/// It also needs second player's object and second hud to work in two-player mode
	void zombieHandling_2Player(Player& player1, Player& player2, Zombie& zombie, Zombie& strong_zombie, Zombie& fast_zombie, HUD& hud, HUD& hud2);
	/// This method is used for loading player_n_highscore pairs from a leaderboard file
	///
	/// @param path				Path parameter containing input file's location
	void loadPairsFromFile(std::filesystem::path path);
	/// This method draw leaderboard file pairs of players and their highscores to a target window
	///
	/// @param target_window	Window to which pairs are drawn
	void drawPNHPairs(sf::RenderWindow& target_window);
};
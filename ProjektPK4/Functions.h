#pragma once
#include "SFML\Audio.hpp"
#include <filesystem>
#include <ranges>
#include <fstream>
#include <iostream>
#include "Zombie.h"
#include <string>
#include <future>

/// This function reads lines from a file and returns them as a vector of lines
/// 
/// @param filename			File directory
std::vector<std::string> readLinesFromFile(const std::string& filename);

/// This function updates leaderboard file after each game
/// 
/// @param leaderboard_path				Leaderboard file directory
/// @param player_nick					Player's nickname
/// @param score						Player's score
void updateLeaderboardFile(std::filesystem::path leaderboard_path, std::string player_nick, int score);

/// This function is used to increase game difficulty
/// 
/// It does so by increasing zombies' movement speeds and spawn frequencies
/// @param zombie						Basic zombie
/// @param strong_zombie				Strong zombie
/// @param hud							HUD
void increaseDifficulty(Zombie& zombie, Zombie& strong_zombie, HUD& hud);

/// This function is used in thread initiation to load audio from files
///
/// @param promise						Audio promise variable
/// @param file_path					Audio file's directory
void loadAudioPromise(std::promise<sf::SoundBuffer> promise, std::string file_path);
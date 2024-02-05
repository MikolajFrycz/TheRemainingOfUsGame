#include "Functions.h"

std::vector<std::string> readLinesFromFile(const std::string& filename) {
	std::vector<std::string> lines;

	std::ifstream file(filename);
	if (!file.is_open()) {
		throw "Failed to open file: ", filename;
		return lines;
	}

	// Read lines from the file using ranges and store them in the vector
	std::ranges::copy(std::ranges::istream_view<std::string>(file), std::back_inserter(lines));

	file.close();
	return lines;
}

void updateLeaderboardFile(std::filesystem::path leaderboard_path, std::string player_nick, int score)
{
	//check if file exists
	bool exists = std::filesystem::exists(leaderboard_path);
	if (!exists)
	{
		exit(13);
	}

	bool player_found = false;
	std::vector<std::string> lines = readLinesFromFile(leaderboard_path.string());

	//searching for player in file (if found and newscore > oldscore, update score)
	for (int i = 0; i < lines.size(); i++)
	{
		if (lines[i] == player_nick)
		{
			player_found = true;
			std::cout << "Nick found: " << player_nick 
				<< " ; and prev score: " << lines[i + 1] << "; and new score: " << score << "\n\n";

			if (std::stoll(lines[i + 1]) < score)
			{
				lines[i + 1] = std::to_string(score);
			}
			break;
		}
	}

	//If there is no player with such nick in file, add them
	if (player_found == false)
	{
		lines.push_back("PLAYER");
		lines.push_back(player_nick);
		lines.push_back(std::to_string(score));
	}

	//refresh file
	std::ofstream clear_file(leaderboard_path, std::ios::trunc);
	clear_file.close();

	std::ofstream outfile(leaderboard_path, std::ios::app);
		
	if (outfile.is_open())
	{
		for (int i = 0; i < lines.size(); i++)
		{
			outfile << lines[i] << "\n";
		}
	}

	outfile.close();
	

}

void increaseDifficulty(Zombie& zombie, Zombie& strong_zombie, HUD& hud)
{
	//increasing difficulty
	if (hud.getScoreCountInt() == 1000)
	{
		zombie.setCurrMovSpeed(zombie.getMovSpeed() + 0.5f);
		strong_zombie.setCurrMovSpeed(strong_zombie.getMovSpeed() + 0.5f);
		zombie.setCurrSpawnFreq(zombie.getCurrSpawnFreq() + 1000);
		hud.updateScore(100);
	}
	if (hud.getScoreCountInt() == 2000)
	{
		zombie.setCurrMovSpeed(zombie.getMovSpeed() + 0.5f);
		strong_zombie.setCurrMovSpeed(strong_zombie.getMovSpeed() + 0.5f);
		zombie.setCurrSpawnFreq(zombie.getCurrSpawnFreq() + 1000);
		hud.updateScore(100);
	}
	if (hud.getScoreCountInt() == 3000)
	{
		zombie.setCurrSpawnFreq(zombie.getCurrSpawnFreq() + 1000);
		strong_zombie.setCurrMovSpeed(strong_zombie.getMovSpeed() + 0.5f);
		zombie.setCurrMovSpeed(zombie.getMovSpeed() + 1.5f);
		hud.updateScore(100);
	}
	if (hud.getScoreCountInt() == 5000)
	{
		zombie.setCurrSpawnFreq(zombie.getCurrSpawnFreq() + 1000);
		strong_zombie.setCurrMovSpeed(strong_zombie.getMovSpeed() + 0.5f);
		zombie.setCurrMovSpeed(zombie.getMovSpeed() + 1.5f);
		hud.updateScore(100);
	}
}

void loadAudioPromise(std::promise<sf::SoundBuffer> promise, std::string file_path)
{
	std::filesystem::path file = file_path;

	bool exists = std::filesystem::exists(file);

	if (!exists)
	{
		exit(13);
	}

	sf::SoundBuffer buffer;
	buffer.loadFromFile(file_path);

	promise.set_value(buffer);
}
#include "HUD.h"

HUD::HUD()
{
	score_count_integer = 0;
	score_count.setString("0");
	player_name = "Player";
}

HUD::HUD(int score_start, int max_ammo_start , std::string name, std::string font_path)
{
	max_ammo_begin = max_ammo_start;
	player_name = name;
	score_count_integer = score_start;
	max_ammo = max_ammo_start;
	curr_ammo = max_ammo_start;

	if (!font.loadFromFile(font_path))
		throw "Could not load given font.ttf path!\n";
	
	//ammo text
	ammo_word_text.setFont(font);
	ammo_word_text.setString("AMMO:");
	ammo_word_text.setCharacterSize(64);
	ammo_word_text.setPosition(0,550);
	ammo_word_text.setFillColor(sf::Color(83, 149, 59));

	//score text
	score_text.setFont(font);
	score_text.setString("SCORE: ");
	score_text.setFillColor(sf::Color(83, 149, 59));
	
	//score count
	score_count.setFont(font);
	score_count.setString("0");
	score_count.setPosition(0, 30);

	//max_ammo
	max_ammo_text.setFont(font);
	std::stringstream ss1;
	ss1 << "/" << max_ammo_start;
	std::string s1 = ss1.str();
	max_ammo_text.setString(s1);
	max_ammo_text.setCharacterSize(64);
	max_ammo_text.setPosition(60, 610);

	//curr_ammo
	curr_ammo_text.setFont(font);
	std::stringstream ss2;
	ss2 << max_ammo_start;
	std::string s2 = ss2.str();
	curr_ammo_text.setString(s2);
	curr_ammo_text.setCharacterSize(64);
	curr_ammo_text.setPosition(0,610);
	
}

void HUD::setHUDfor2ndPlayer(sf::Vector2f offset)
{
	ammo_word_text.setPosition(ammo_word_text.getPosition() + offset);
	ammo_word_text.setFillColor(sf::Color(156,30,42));
	score_text.setPosition(score_text.getPosition() + offset);
	score_text.setFillColor(sf::Color(156, 30, 42));
	score_count.setPosition(score_count.getPosition() + offset);
	max_ammo_text.setPosition(max_ammo_text.getPosition() + offset);
	curr_ammo_text.setPosition(curr_ammo_text.getPosition() + offset);
}

HUD::~HUD() {};

void HUD::drawHUD(sf::RenderWindow &target_window)
{
	target_window.draw(score_text);
	target_window.draw(score_count);
	target_window.draw(max_ammo_text);
	target_window.draw(curr_ammo_text);
	target_window.draw(ammo_word_text);
}

void HUD::updateScore(int added_ammount)
{
	score_count_integer += added_ammount;

	std::stringstream ss1, ss2;
	ss1 << score_count_integer;
	std::string s = ss1.str();
	score_count.setString(s);
}

void HUD::changeMaxAmmo(int new_ammo)
{
	max_ammo = new_ammo;

	std::stringstream ss1;
	ss1 << "/" << max_ammo;
	std::string s = ss1.str();
	max_ammo_text.setString(s);
}

void HUD::changeCurrAmmo(int add_to_ammo)
{
	curr_ammo += add_to_ammo;
	std::stringstream ss1;
	ss1 << curr_ammo;
	std::string s = ss1.str();
	curr_ammo_text.setString(s);
}

int &HUD::getScoreCountInt()
{
	return score_count_integer;
}

void HUD::resetHUD()
{
	//reseting int values
	curr_ammo = max_ammo_begin;
	max_ammo = max_ammo_begin;
	score_count_integer = 0;

	//reseting score count text
	score_count.setString("0");

	//reset current ammo text
	std::stringstream ss2;
	ss2 << max_ammo_begin;
	std::string s2 = ss2.str();
	curr_ammo_text.setString(s2);

	//reseting max ammo text
	std::stringstream ss1;
	ss1 << "/" << max_ammo_begin;
	std::string s1 = ss1.str();
	max_ammo_text.setString(s1);
}
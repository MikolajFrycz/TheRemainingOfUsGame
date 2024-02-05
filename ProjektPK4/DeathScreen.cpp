#include "DeathScreen.h"

DeathScreen::DeathScreen(int k_time, std::string f_path, std::filesystem::path backgrd_path) : Menu(k_time, f_path, backgrd_path) { score_ct_int = 0;}

void DeathScreen::setValues(sf::RenderWindow& window, int val)
{
	//non-clickables
	
	getMenuText(0).setFont(getFont());
	getMenuText(0).setString("SCORE:");
	getMenuText(0).setPosition(sf::Vector2f(window.getSize().x / 2 - 300, (window.getSize().y / 3)+100));
	getMenuText(0).setFillColor(sf::Color(140, 2, 25));
	getMenuText(0).setCharacterSize(64);

	score_ct_int = val;

	std::stringstream ss1;
	ss1 << score_ct_int;
	std::string s1 = ss1.str();

	getMenuText(1).setString(s1);
	getMenuText(1).setFont(getFont());
	getMenuText(1).setFillColor(sf::Color::White);
	getMenuText(1).setPosition(sf::Vector2f(getMenuText(0).getPosition().x + 220, getMenuText(0).getPosition().y));
	getMenuText(1).setCharacterSize(64);

	//clickables
	getMenuText(2).setFont(getFont());
	getMenuText(2).setString("Try again?");
	getMenuText(2).setPosition(sf::Vector2f(window.getSize().x / 2 - 250, (window.getSize().y / 3)+200));
	getMenuText(2).setFillColor(sf::Color(140, 2, 25));

	getMenuText(3).setFont(getFont());
	getMenuText(3).setString("Return to menu");
	getMenuText(3).setPosition(sf::Vector2f(window.getSize().x / 2 - 300, (window.getSize().y / 3)+250));
	getMenuText(3).setFillColor(sf::Color::White);

	getSelectedItemIndex() = 2;
}

void DeathScreen::set2PlayerValues(sf::RenderWindow& window, int val, int which_won)
{
	//non-clickables
	if (which_won == 0)
	{
		getMenuText(0).setFont(getFont());
		getMenuText(0).setString("PLAYER 1 WON WITH SCORE:");
		getMenuText(0).setPosition(sf::Vector2f(window.getSize().x / 2 - 300, (window.getSize().y / 4) + 100));
		getMenuText(0).setFillColor(sf::Color(140, 2, 25));
		getMenuText(0).setCharacterSize(64);
	}
	if (which_won == 1)
	{
		getMenuText(0).setFont(getFont());
		getMenuText(0).setString("PLAYER 2 WON WITH SCORE:");
		getMenuText(0).setPosition(sf::Vector2f(window.getSize().x / 2 - 300, (window.getSize().y / 4) + 100));
		getMenuText(0).setFillColor(sf::Color(140, 2, 25));
		getMenuText(0).setCharacterSize(64);
	}
	if (which_won == 2)
	{
		getMenuText(0).setFont(getFont());
		getMenuText(0).setString("DRAW WITH SCORE:");
		getMenuText(0).setPosition(sf::Vector2f(window.getSize().x / 2 - 300, (window.getSize().y / 4) + 100));
		getMenuText(0).setFillColor(sf::Color(140, 2, 25));
		getMenuText(0).setCharacterSize(64);
	}

	score_ct_int = val;

	std::stringstream ss1;
	ss1 << score_ct_int;
	std::string s1 = ss1.str();

	getMenuText(1).setString(s1);
	getMenuText(1).setFont(getFont());
	getMenuText(1).setFillColor(sf::Color::White);
	getMenuText(1).setPosition(sf::Vector2f(window.getSize().x / 2 - 300, getMenuText(0).getPosition().y + 70));
	getMenuText(1).setCharacterSize(90);

	//clickables
	getMenuText(2).setFont(getFont());
	getMenuText(2).setString("Try again?");
	getMenuText(2).setPosition(sf::Vector2f(window.getSize().x / 2 - 250, (window.getSize().y / 3) + 250));
	getMenuText(2).setFillColor(sf::Color(140, 2, 25));

	getMenuText(3).setFont(getFont());
	getMenuText(3).setString("Return to menu");
	getMenuText(3).setPosition(sf::Vector2f(window.getSize().x / 2 - 300, (window.getSize().y / 3) + 300));
	getMenuText(3).setFillColor(sf::Color::White);

	getSelectedItemIndex() = 2;
}

void DeathScreen::moveDown()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && getKeytime() >= 10)
	{
		if (getSelectedItemIndex() + 1 < 4)
		{
			getMenuText(getSelectedItemIndex()).setPosition(sf::Vector2f(getMenuText(getSelectedItemIndex()).getPosition().x - 50, getMenuText(getSelectedItemIndex()).getPosition().y));
			getMenuText(getSelectedItemIndex()).setFillColor(sf::Color::White);
			getSelectedItemIndex()++;
			getMenuText(getSelectedItemIndex()).setFillColor(sf::Color(140, 0, 25));
			getMenuText(getSelectedItemIndex()).setPosition(sf::Vector2f(getMenuText(getSelectedItemIndex()).getPosition().x + 50, getMenuText(getSelectedItemIndex()).getPosition().y));
		}
		getKeytime() = 0;
	}
}
#include "Menu.h"

Menu::Menu(int k_time, std::string f_path, std::filesystem::path backgrd_path)
{
	keytime = k_time;

	if (!font.loadFromFile(f_path))
		throw "Couldn't load font file!\n";

	
	texture.loadFromFile(backgrd_path.string());
	background.setTexture(texture);

	selected_item_index = 0;
}

void Menu::setValues()
{
	menu[0].setFont(font);
	menu[0].setString("BEGIN SOLO");
	menu[0].setFillColor(sf::Color(140, 0, 25));
	menu[0].setPosition(sf::Vector2f(55, 150));

	menu[1].setFont(font);
	menu[1].setString("BEGIN DUO");
	menu[1].setFillColor(sf::Color::White);
	menu[1].setPosition(sf::Vector2f(15, 250));

	menu[2].setFont(font);
	menu[2].setString("SURVIVOR LEADERBOARD");
	menu[2].setFillColor(sf::Color::White);
	menu[2].setPosition(sf::Vector2f(15, 350));

	menu[3].setFont(font);
	menu[3].setString("HOW TO PLAY");
	menu[3].setFillColor(sf::Color::White);
	menu[3].setPosition(sf::Vector2f(15, 450));

	menu[4].setFont(font);
	menu[4].setString("GIVE UP...");
	menu[4].setFillColor(sf::Color::White);
	menu[4].setPosition(sf::Vector2f(15, 550));
}

void Menu::draw(sf::RenderWindow& window)
{
	window.draw(background);
	for (int i = 0; i < 5; i++)
	{
		window.draw(menu[i]); 
	}
}

Menu::~Menu(){};

void Menu::moveUp(int min_opt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && keytime >= 10)
	{
		if (selected_item_index - 1 >= min_opt)
		{
			menu[selected_item_index].setPosition(sf::Vector2f(menu[selected_item_index].getPosition().x - 50, menu[selected_item_index].getPosition().y));
			menu[selected_item_index].setFillColor(sf::Color::White);
			selected_item_index--;
			menu[selected_item_index].setFillColor(sf::Color(140, 0, 25));
			menu[selected_item_index].setPosition(sf::Vector2f(menu[selected_item_index].getPosition().x + 50, menu[selected_item_index].getPosition().y));
		}
		keytime = 0;
	}
}

void Menu::moveDown()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && keytime >= 10)
	{
		if (selected_item_index + 1 < 5)
		{
			menu[selected_item_index].setPosition(sf::Vector2f(menu[selected_item_index].getPosition().x - 50, menu[selected_item_index].getPosition().y));
			menu[selected_item_index].setFillColor(sf::Color::White);
			selected_item_index++;
			menu[selected_item_index].setFillColor(sf::Color(140, 0, 25));
			menu[selected_item_index].setPosition(sf::Vector2f(menu[selected_item_index].getPosition().x + 50, menu[selected_item_index].getPosition().y));
		}
		keytime = 0;
	}
}

int &Menu::getKeytime()
{
	return keytime;
}

int Menu::getSelectedItem()
{
	return selected_item_index;
}

sf::Font &Menu::getFont()
{
	return font;
}

void Menu::setText(int i, sf::Text text)
{
	menu[i] = text;
}

sf::Sprite& Menu::getBackground()
{
	return background;
}

int &Menu::getSelectedItemIndex()
{
	return selected_item_index;
}

sf::Text &Menu::getMenuText(int i)
{
	return menu[i];
}
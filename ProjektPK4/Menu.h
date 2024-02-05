#pragma once
#include "Entity.h"

/// This class dictates the behaviour of main menu
class Menu
{
private:
	/// Key time
	int keytime;
	/// Font file's directory
	std::string font_path;
	/// Index of the selected menu option
	int selected_item_index = 0;
	/// Font used for text generation
	sf::Font font;
	/// Text options on screen
	sf::Text menu[5];
	/// Texture of background png
	sf::Texture texture;
	/// Sprite of bacground to which texture is loaded
	sf::Sprite background;
	
public:
	/// Menu multi-argument constructor
	/// 
	/// @param k_time				Sets key time value
	/// @param f_path				Font file directory
	/// @param backgrd_path			Directory of background png
	Menu(int k_time, std::string f_path, std::filesystem::path backgrd_path);
	/// Menu destructor
	~Menu();
	/// This method draws the menu on screen
	/// 
	/// It is used to draw all the sf::Text variables 
	/// @param window				Target window
	void draw(sf::RenderWindow& window);
	/// Initiates menu's values
	virtual void setValues();
	/// Used to switch to a higher option
	/// 
	/// @param min_opt				Dictates which sf::Text variable is the top one
	void moveUp(int min_opt);
	/// Used to switch to lower option
	virtual void moveDown();
	/// Getter which returns keytime
	int &getKeytime();
	/// Getter which returns selected item
	int getSelectedItem();
	/// Getter which returns Font
	sf::Font &getFont();
	/// Setter which sets text value to the adequate Text by its index i
	void setText(int i, sf::Text text);
	/// Getter which returns background sprite
	sf::Sprite &getBackground();
	/// Getter which returns selected item index
	int &getSelectedItemIndex();
	/// Getter which returns option's text by it's id i
	sf::Text& getMenuText(int i);
};
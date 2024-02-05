#include "Game.h"

Game::Game() : window(sf::VideoMode(710, 850), "The Remaining of Us" , sf::Style::Titlebar | sf::Style::Close)
{
	window.setFramerateLimit(60);
	texture.loadFromFile("Textures/tempBackgroundx.png");
	sf::Sprite background1(texture);

	input_regex = std::regex("[a-z0-9]+");
	leaderboard_file = "LeaderboardFile.txt";
	background = background1;

	intro_texture.loadFromFile("Textures/IntroPic.png");
	intro.setTexture(intro_texture);

	instruct_texture.loadFromFile("Textures/Instructions.png");
	instruct.setTexture(instruct_texture);

	outro_texture.loadFromFile("Textures/OutPic.png");
	outro.setTexture(outro_texture);
}

Game::~Game() {};

void Game::run()
{
	std::promise<sf::SoundBuffer> introPromise;
	std::future introFuture = introPromise.get_future();
	std::thread loadSound1(loadAudioPromise, std::move(introPromise), "Audio\\INTRO.ogg");
	loadSound1.detach();

	std::promise<sf::SoundBuffer> gamePromise;
	std::future gameFuture = gamePromise.get_future();
	std::thread loadSound2(loadAudioPromise, std::move(gamePromise), "Audio\\MAIN.ogg");
	loadSound2.detach();

	std::promise<sf::SoundBuffer> deathscreenPromise;
	std::future deathscreenFuture = deathscreenPromise.get_future();
	std::thread loadSound3(loadAudioPromise, std::move(deathscreenPromise), "Audio\\GAME_OVER.ogg");
	loadSound3.detach();

	std::promise<sf::SoundBuffer> zombiePromise;
	std::future zombieFuture = zombiePromise.get_future();
	std::thread loadSound4(loadAudioPromise, std::move(zombiePromise), "Audio\\ZombieDeath.ogg");
	loadSound4.detach();

	std::promise<sf::SoundBuffer> shotPromise;
	std::future shotFuture = shotPromise.get_future();
	std::thread loadSound5(loadAudioPromise, std::move(shotPromise), "Audio\\Shot.ogg");
	loadSound5.detach();

	std::promise<sf::SoundBuffer> reloadPromise;
	std::future reloadFuture = reloadPromise.get_future();
	std::thread loadSound6(loadAudioPromise, std::move(reloadPromise), "Audio\\reloadSound.ogg");
	loadSound6.detach();

	std::string font_path = "Textures/chineserocks.otf";
	font.loadFromFile(font_path);
	std::filesystem::path menu_back_path = "Textures\\TROUMenu.png";
	std::filesystem::path deathscreen_back_path = "Textures\\DeathScreen.png";
	sf::Clock reloadClock, reloadClock2;

	Menu menu(15, font_path, menu_back_path);
	menu.setValues();



	DeathScreen deathscreen(15,font_path,deathscreen_back_path);
	DeathScreen duo_deathscreen(15, font_path, deathscreen_back_path);

	//Player 1
	Player player1(1, 15, 15, sf::Vector2f(window.getSize().x/2 - 40, window.getSize().y-270.f));
	player1.setTexture("Textures/PlayertexSpriteSheet.png");
	player1.loadSpritesFromSheet(100, 107, 2, 3);
	player1.setSprite(0, sf::Vector2f(window.getSize().x / 2, window.getSize().y - 270.f));

	//Player 2
	Player player2(1, 15, 15, sf::Vector2f(window.getSize().x / 2 - 40, window.getSize().y - 270.f));
	player2.setTexture("Textures/Player2texSpriteSheet.png");
	player2.loadSpritesFromSheet(100, 107, 2, 3);
	player2.setSprite(0, sf::Vector2f(window.getSize().x / 2, window.getSize().y - 270.f));

	//HUD
	HUD hud(0, player1.getMaxAmmo(), "Player", font_path);
	HUD hudfor2ndplayer(0, player1.getMaxAmmo(), "Player2", font_path);
	hudfor2ndplayer.setHUDfor2ndPlayer(sf::Vector2f(580.f, 0.f));

	Bullet pistol_bullet(player1.getCenter(), sf::Vector2f(3.f, 20.f), 25);
	Zombie basic_zombies(100, 2, 1000, sf::Vector2f(0.f,0.f), 2.f);
	Zombie strong_zombies(300, 5, 10000, sf::Vector2f(0.f, 0.f), 1.f);
	Zombie fast_zombies(200, 1, 15000, sf::Vector2f(0.f, 0.f), 4.f);
	//zombier strong skonczyc z getFreq
	
	basic_zombies.setTexture("Textures/zombie1.png");
	basic_zombies.loadSpritesFromSheet(53, 75, 1, 2);
	basic_zombies.setSprite(0, sf::Vector2f(0.f, 0.f));
	basic_zombies.setAnimationFrequency(200);

	strong_zombies.setTexture("Textures/StrongZombieSpriteSheet.png");
	strong_zombies.loadSpritesFromSheet(138, 139, 1, 2);
	strong_zombies.setSprite(0, sf::Vector2f(0.f, 0.f));
	strong_zombies.setAnimationFrequency(600);

	fast_zombies.setTexture("Textures/FastZombieSheet.png");
	fast_zombies.loadSpritesFromSheet(108, 125, 1, 2);
	fast_zombies.setSprite(0,sf::Vector2f(0.f,0.f));
	fast_zombies.setAnimationFrequency(400);

	sf::Font tempFont;
	tempFont.loadFromFile(font_path);
	
	nickInputPrompt.setFont(tempFont);
	nickInputPrompt.setCharacterSize(32);
	nickInputPrompt.setString("INPUT YOUR NICKNAME:");
	nickInputPrompt.setPosition(60.f, 300.f);

	player_name_render.setFont(tempFont);
	player_name_render.setFillColor(sf::Color(140, 0, 25));
	player_name_render.setCharacterSize(64);
	player_name_render.setPosition(60.f, 350.f);

	intro_buffer = introFuture.get();
	intro_sound.setBuffer(intro_buffer);
	intro_sound.setVolume(60);
	intro_sound.setLoop(true);
	
	game_buffer = gameFuture.get();
	game_sound.setBuffer(game_buffer);
	game_sound.setVolume(60);
	game_sound.setLoop(true);

	deathscreen_buffer = deathscreenFuture.get();
	deathscreen_sound.setBuffer(deathscreen_buffer);
	deathscreen_sound.setVolume(60);
	deathscreen_sound.setLoop(true);


	zombie_buffer = zombieFuture.get();
	for (int i = 0; i < 24; i++)
	{
		zombie_sound[i].setBuffer(zombie_buffer);
	}
	shot_buffer = shotFuture.get();
	for (int i = 0; i < 24; i++)
	{
		shot_sound[i].setBuffer(shot_buffer);
	}
	reload_buffer = reloadFuture.get();
	for (int i = 0; i < 24; i++)
	{
		reload_sound[i].setBuffer(reload_buffer);
	}

	intro_outro_clk.restart();
	intro_sound.play();
	//Game loop
	while (window.isOpen())
	{
		processEvents(basic_zombies, strong_zombies, fast_zombies);
		//Wrzucic te parametry z update do atrybutow Game
		Update(player1, player2, basic_zombies, strong_zombies, fast_zombies, pistol_bullet, reloadClock, reloadClock2, hud, hudfor2ndplayer, menu, deathscreen, duo_deathscreen, opt);
		
		//animations for player 1
		player1.shootingAnimation(reloadClock);
		player1.reloadAnimation(reloadClock, hud);
		//animations for player 2
		player2.shootingAnimation(reloadClock2);
		player2.reloadAnimation(reloadClock2, hudfor2ndplayer);

	}
}

void Game::processEvents(Zombie& zombie, Zombie& strong_zombie, Zombie& fast_zombie)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		//Closing window
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
		if (event.type == sf::Event::KeyPressed)
		{
			if (opt == -1 && player_name != "")
			{
				if (event.key.code == sf::Keyboard::Enter)
				{
					strong_zombie.restartClock();
					zombie.restartClock();
					fast_zombie.restartClock();
					opt = 1;
					intro_sound.stop();
					game_sound.play();
				}
				if (event.key.code == sf::Keyboard::Backspace)
				{
					player_name.pop_back();
					return;
				}
			}
		}
		//Typing input
		if (event.type == sf::Event::TextEntered)
		{
			if (opt == -1)
			{
				char input = event.text.unicode;
				std::string input_str = " ";
				input_str[0] = input;
				
				if (std::regex_match(input_str, input_regex) && player_name.size() < 10)
				{
					player_name += event.text.unicode;
				}
			}
		}
	}
}

void Game::Update(Player &player1, Player &player2, Zombie& basiczombie, 
	Zombie& strong_zombie, Zombie& fast_zombie, Bullet &bullet, sf::Clock &reloadClock, sf::Clock &reloadClock2,
	HUD &hud, HUD &hud2, Menu &menu, DeathScreen &deathscreen, DeathScreen &duo_ds, int &option)
{
switch (option)
{
	//instructions
	case -5:
	{
		window.clear();
		window.draw(instruct);

		window.display();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			opt = 0;
		}

		break;
	}
	//Intro
	case -4:
	{
		window.clear();
		window.draw(intro);

		window.display();

		if (intro_outro_clk.getElapsedTime().asMilliseconds() >= 3000)
		{
			opt = 0;
		}
		break;
	}
	//Outro
	case -3:
	{
		window.clear();
		window.draw(outro);

		window.display();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}

		break;
	}
	//Leaderboard menu
	case -2:
	{

		if (menu.getKeytime() <= 15)
		{
			menu.getKeytime()++;
		}

		window.clear();
		window.draw(menu.getBackground());

		
		Game::drawPNHPairs(window);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && menu.getKeytime() >= 14)
		{
			option = 0;
			menu.getKeytime() = 0;
		}
		
		window.display();
		break;
	}

	//Player name input
	case -1:
	{
		window.clear();


		window.draw(menu.getBackground());

		player_name_render.setString(player_name);

		window.draw(nickInputPrompt);
		window.draw(player_name_render);
		

		window.display();
		break;
	}
	//Menu
	case 0:
	{
		if (menu.getKeytime() < 10)
		{
			menu.getKeytime()++;
		}

		window.clear();
		menu.draw(window);
		window.display();
		
		//choosing menu options
		menu.moveUp(0);
		menu.moveDown();
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && menu.getKeytime() >= 10)
		{
			if (menu.getSelectedItem() == 0)
			{
				option = -1;
			}
			if (menu.getSelectedItem() == 1)
			{
				option = 2;
				basiczombie.restartClock();
				strong_zombie.restartClock();
				fast_zombie.restartClock();
				//set players side-by-side before duo mode start
				player1.getSprite().setPosition(player1.getSprite().getPosition().x - 50.f,player1.getSprite().getPosition().y);
				player2.getSprite().setPosition(player2.getSprite().getPosition().x + 50.f, player2.getSprite().getPosition().y);
				intro_sound.stop();
				game_sound.play();

			}
			if (menu.getSelectedItem() == 2)
			{
				Game::loadPairsFromFile(leaderboard_file);
				option = -2;
			}
			//instructions menu
			if (menu.getSelectedItem() == 3)
			{
				opt = -5;
			}
			//outro
			if (menu.getSelectedItem() == 4)
			{
				opt = -3;
			}
			menu.getKeytime() = 0;
		}
		break;
	}

	//Singleplayer
	case 1:
	{

		player1.player1Movement(window.getSize().x);
		if (player1.shootPistol(sf::Keyboard::Space, bullet, window, reloadClock, hud))
		{
			int index = 0;
			for (int i = 0; i < 24; i++)
			{
				if (shot_sound[i].getStatus() != sf::Sound::Playing)
				{
					index = i;
					break;
				}
			}
			shot_sound[index].setVolume(15);
			shot_sound[index].play();
		}
		if (player1.playerReload(reloadClock, sf::Keyboard::R))
		{
			int index = 0;
			for (int i = 0; i < 10; i++)
			{
				if (reload_sound[i].getStatus() != sf::Sound::Playing)
				{
					index = i;
					break;
				}
			}
			reload_sound[index].setVolume(50);
			reload_sound[index].play();
		}
	

		Game::zombieHandling(player1, basiczombie, strong_zombie, fast_zombie, hud);
		
		//draw
		window.clear(sf::Color::Black);

		window.draw(background);
		hud.drawHUD(window);
		player1.Draw(window);

		//draw bullets
		if (player1.getCurrAmmo() >= 0)
		{
			for (size_t i = 0; i < player1.getBulletClipSize(); i++)
			{
				window.draw(player1.getBulletClip()[i]);
			}
		}

		//draw zombies
		if (vec_of_zombies.size() >= 0)
		{
			for (size_t i = 0; i < vec_of_zombies.size(); i++)
			{
				vec_of_zombies[i].Animation();
				vec_of_zombies[i].Draw(window);
			}
		}

		if (player1.getLives() == 0)
		{
			updateLeaderboardFile(leaderboard_file, player_name, hud.getScoreCountInt());

			deathscreen.setValues(window, hud.getScoreCountInt());
			//reseting the board after finished game
			player1.playerReset();
			
			hud.resetHUD();
			//deleting remaining zombies
			vec_of_zombies.erase(vec_of_zombies.begin(), vec_of_zombies.end());
			basiczombie.resetValues();
			strong_zombie.resetValues();
			fast_zombie.resetValues();

			game_sound.stop();
			deathscreen_sound.play();

			option = 3;
		}


		window.display();
		break;
	}

	//2Player
	case 2:
	{
		int zb_freq = 1000, strong_zb_freq = 11000;

		player1.player1Movement(window.getSize().x);
		if (player1.shootPistol(sf::Keyboard::Space, bullet, window, reloadClock, hud))
		{
			int index = 0;
			for (int i = 0; i < 24; i++)
			{
				if (shot_sound[i].getStatus() != sf::Sound::Playing)
				{
					index = i;
					break;
				}
			}
			shot_sound[index].setVolume(15);
			shot_sound[index].play();
		}
		if (player1.playerReload(reloadClock, sf::Keyboard::R))
		{
			int index = 0;
			for (int i = 0; i < 10; i++)
			{
				if (reload_sound[i].getStatus() != sf::Sound::Playing)
				{
					index = i;
					break;
				}
			}
			reload_sound[index].setVolume(50);
			reload_sound[index].play();
		}


		player2.player2Movement(window.getSize().x);
		if (player2.shootPistol(sf::Keyboard::RControl, bullet, window, reloadClock2, hud2))
		{
			int index = 0;
			for (int i = 0; i < 24; i++)
			{
				if (shot_sound[i].getStatus() != sf::Sound::Playing)
				{
					index = i;
					break;
				}
			}
			shot_sound[index].setVolume(15);
			shot_sound[index].play();
		}
		
		if (player2.playerReload(reloadClock2, sf::Keyboard::RAlt))
		{
			int index = 0;
			for (int i = 0; i < 10; i++)
			{
				if (reload_sound[i].getStatus() != sf::Sound::Playing)
				{
					index = i;
					break;
				}
			}
			reload_sound[index].setVolume(50);
			reload_sound[index].play();
		}

		zombieHandling_2Player(player1, player2, basiczombie, strong_zombie, fast_zombie, hud, hud2);

		//draw
		window.clear(sf::Color::Black);

		window.draw(background);
		hud.drawHUD(window);
		hud2.drawHUD(window);
		player1.Draw(window);
		player2.Draw(window);


		//draw bullets
		if (player1.getCurrAmmo() >= 0)
		{
			for (size_t i = 0; i < player1.getBulletClipSize(); i++)
			{
				window.draw(player1.getBulletClip()[i]);
			}
		}

		if (player2.getCurrAmmo() >= 0)
		{
			for (size_t i = 0; i < player2.getBulletClipSize(); i++)
			{
				window.draw(player2.getBulletClip()[i]);
			}
		}

		//draw zombies
		if (vec_of_zombies.size() >= 0)
		{
			for (size_t i = 0; i < vec_of_zombies.size(); i++)
			{
				vec_of_zombies[i].Animation();
				vec_of_zombies[i].Draw(window);
			}
		}

		if (player1.getLives() == 0)
		{
			if (hud.getScoreCountInt() > hud2.getScoreCountInt())
			{
				duo_ds.set2PlayerValues(window, hud.getScoreCountInt(), 0);
			}
			if (hud.getScoreCountInt() < hud2.getScoreCountInt())
			{
				duo_ds.set2PlayerValues(window, hud2.getScoreCountInt(), 1);
			}
			if (hud.getScoreCountInt() == hud2.getScoreCountInt())
			{
				duo_ds.set2PlayerValues(window, hud.getScoreCountInt(), 2);
			}
			//reseting the board after finished game
			player1.playerReset();
			player2.playerReset();
			hud.resetHUD();
			hud2.resetHUD();
			game_sound.stop();
			deathscreen_sound.play();

			//deleting remaining zombies
			vec_of_zombies.erase(vec_of_zombies.begin(), vec_of_zombies.end());

			basiczombie.resetValues();
			strong_zombie.resetValues();
			fast_zombie.resetValues();

			option = 4;
		}


		window.display();

		break;
	}

	//1 player Deathscreen
	case 3:
	{
		if (deathscreen.getKeytime() < 10)
		{
			deathscreen.getKeytime()++;
		}
		window.clear();
		deathscreen.draw(window);
		
		deathscreen.moveUp(2);
		deathscreen.moveDown();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && deathscreen.getKeytime() >= 10)
		{
			if (deathscreen.getSelectedItem() == 2)
			{
				player1.getLives() = 1;
				hud.updateScore(-hud.getScoreCountInt());
				option = 1;
				basiczombie.restartClock();
				strong_zombie.restartClock();
				fast_zombie.restartClock();
				deathscreen_sound.stop();
				game_sound.play();
			}
			if (deathscreen.getSelectedItem() == 3)
			{
				player1.getLives() = 1;
				hud.updateScore(-hud.getScoreCountInt());
				player_name = "";
				option = 0;
				deathscreen_sound.stop();
				intro_sound.play();
			}
			deathscreen.getKeytime() = 0;
		}

		window.display();
		break;
	}


	//2Player Deathscreen
	case 4:
	{
		if (duo_ds.getKeytime() < 10)
		{
			duo_ds.getKeytime()++;
		}

		window.clear();
		duo_ds.draw(window);

		duo_ds.moveUp(2);
		duo_ds.moveDown();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && duo_ds.getKeytime() >= 10)
		{
			if (duo_ds.getSelectedItem() == 2)
			{
				player1.getLives() = 1;
				hud.updateScore(-hud.getScoreCountInt());
				hud2.updateScore(-hud2.getScoreCountInt());
				option = 2;
				player1.getSprite().setPosition(player1.getSprite().getPosition().x - 50.f, player1.getSprite().getPosition().y);
				player2.getSprite().setPosition(player2.getSprite().getPosition().x + 50.f, player2.getSprite().getPosition().y);
				basiczombie.restartClock();
				strong_zombie.restartClock();
				fast_zombie.restartClock();
				deathscreen_sound.stop();
				game_sound.play();
			}

			if (duo_ds.getSelectedItem() == 3)
			{
				player1.getLives() = 1;
				hud.updateScore(-hud.getScoreCountInt());
				hud2.updateScore(-hud2.getScoreCountInt());
				option = 0;
				deathscreen_sound.stop();
				intro_sound.play();
			}
			duo_ds.getKeytime() = 0;
		}

		window.display();
		break;
	}
	
}
}

void Game::loadPairsFromFile(std::filesystem::path path)
{
	vec_of_pairs.clear();
	vec_of_leaderboard_texts.clear();

	std::ifstream read_file(path);
	std::string line;

	std::vector<std::string> lines;
	std::string temp_playername;
	std::string temp_playerscore;

	if (read_file.is_open())
	{
		while (std::getline(read_file, line))
		{
			lines.push_back(line);
		}
	}
	for (int i = 0; i < lines.size(); i++)
	{
		if (lines[i] == "PLAYER")
		{	
			player_n_highscore = make_tuple(std::stol(lines[i + 2]), lines[i + 1]);
			//std::cout << "pair: " << lines[i + 1] << "; " << lines[i + 2] << "\n\n";
			vec_of_pairs.push_back(player_n_highscore);
		}
	}

	std::sort(vec_of_pairs.rbegin(), vec_of_pairs.rend());

	sf::Text temp_text;
	temp_text.setFont(font);
	temp_text.setCharacterSize(50);
	temp_text.setPosition(sf::Vector2f(10.f, 150.f));

	temp_text.setString("TOP SURVIVORS:");
	temp_text.setFillColor(sf::Color(140, 0, 25));
	vec_of_leaderboard_texts.push_back(temp_text);

	temp_text.setFillColor(sf::Color::White);
	temp_text.setPosition(10.f, 200.f);

	std::string temp_str;

	for (int i = 0; i < vec_of_pairs.size(); i++)
	{
		temp_str += std::get<1>(vec_of_pairs[i]);
		temp_str = temp_str + ": ";
		temp_str += std::to_string((std::get<0>(vec_of_pairs[i])));
		
		
		temp_text.setString(temp_str);
		vec_of_leaderboard_texts.push_back(temp_text);
		//std::cout << temp_str << "\n\n";
		temp_str = "";
		temp_text.setPosition(sf::Vector2f(10.f, temp_text.getPosition().y + 50.f));

		if (i == 9)
		{
			break;
		}
	}

	temp_text.setString("PRESS ENTER TO RETURN...");
	temp_text.setPosition(10.f, 700.f);
	temp_text.setFillColor(sf::Color(140, 0, 25));
	vec_of_leaderboard_texts.push_back(temp_text);
}

void Game::drawPNHPairs(sf::RenderWindow& target_window)
{
	for (int i = 0; i < vec_of_leaderboard_texts.size(); i++)
	{
		target_window.draw(vec_of_leaderboard_texts[i]);
	}
}

void Game::zombieHandling(Player& player1, Zombie &zombie, Zombie& strong_zombie, Zombie& fast_zombie,HUD& hud)
{
	//increasing difficulty
	increaseDifficulty(zombie, strong_zombie, hud);
	//Basic zombie spawn
		sf::Time spawn_timer = zombie.getSpawnClock().getElapsedTime();

		std::uniform_int_distribution<int> distribution(140, 510);
		std::uniform_int_distribution<int> time_distribution(1000, 20000 - zombie.getCurrSpawnFreq());

		// Generate a random number using the default random engine
		std::random_device rd;
		std::default_random_engine generator(rd());
		float random_x = static_cast<float>(distribution(generator));
		float random_time = static_cast<float>(time_distribution(generator));
		// Generate a random number between 1 and 100

	//Strong zombie spawn
		sf::Time spawn_timer_s = strong_zombie.getSpawnClock().getElapsedTime();

		std::uniform_int_distribution<int> distribution_s(209, 442);
		std::uniform_int_distribution<int> time_distribution_s(strong_zombie.getCurrSpawnFreq(), strong_zombie.getCurrSpawnFreq() + 10000);

		// Generate a random number using the default random engine
		std::random_device rd_s;
		std::default_random_engine generator_s(rd_s());
		float random_x_s = static_cast<float>(distribution_s(generator_s));
		float random_time_s = static_cast<float>(time_distribution_s(generator_s));
	//Fast zombie spawn
		sf::Time spawn_timer_f = fast_zombie.getSpawnClock().getElapsedTime();

		std::uniform_int_distribution<int> distribution_f(209, 442);
		std::uniform_int_distribution<int> time_distribution_f(fast_zombie.getCurrSpawnFreq(), fast_zombie.getCurrSpawnFreq() + 10000);

		// Generate a random number using the default random engine
		std::random_device rd_f;
		std::default_random_engine generator_f(rd_f());
		float random_x_f = static_cast<float>(distribution_f(generator_f));
		float random_time_f = static_cast<float>(time_distribution_f(generator_f));
	
	if (spawn_timer.asMilliseconds() >= random_time)
	{
		zombie.getSprite().setPosition(sf::Vector2f(random_x, -50));
		vec_of_zombies.push_back(zombie);
		zombie.restartClock();
		//std::cout << "\n\n" << vec_of_zombies.size() << "\n\n";
	}
	if (spawn_timer_s.asMilliseconds() >= random_time_s)
	{
		strong_zombie.getSprite().setPosition(sf::Vector2f(random_x_s, -50));
		vec_of_zombies.push_back(strong_zombie);
		strong_zombie.restartClock();
		//std::cout << "\n\n" << vec_of_zombies.size() << "\n\n";
	}
	if (spawn_timer_f.asMilliseconds() >= random_time_f)
	{
		fast_zombie.getSprite().setPosition(sf::Vector2f(random_x_f, -50));
		vec_of_zombies.push_back(fast_zombie);
		fast_zombie.restartClock();
		//std::cout << "\n\n" << vec_of_zombies.size() << "\n\n";
	}

	//pushing back zombies to a vector
	for (size_t i = 0; i < vec_of_zombies.size(); i++)
	{
		//move zombie downward
		vec_of_zombies[i].getSprite().move(0.f, +vec_of_zombies[i].getMovSpeed());

		if (vec_of_zombies[i].getSprite().getPosition().y >= 620.f)
		{
			vec_of_zombies.erase(vec_of_zombies.begin() + i);
			player1.livesDecr();
			std::cout << "Lives: " << player1.getLives() << std::endl;
		}
	}

	//start of measure
	//std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
	//bullet-zombie collison
	for (size_t i = 0; i < player1.getBulletClip().size(); i++)
	{
		sf::FloatRect bullet_bounds = player1.getBulletClip()[i].getGlobalBounds();
		float nearest_distance = std::numeric_limits<float>::max(); //Closest distance firstly set to max
		int nearest_index = -1; //Closest zombie index

		//Find nearest zombie
		for (size_t j = 0; j < vec_of_zombies.size(); j++)
		{
			sf::FloatRect zombie_bounds = vec_of_zombies[j].getSprite().getGlobalBounds();
			float distance = std::sqrt(std::pow(bullet_bounds.left - zombie_bounds.left, 2) + std::pow(bullet_bounds.top - zombie_bounds.top, 2));

			//Check if zombie is the nearest one
			if (distance < nearest_distance)
			{
				nearest_distance = distance;
				nearest_index = j;
			}
		}

		//Check collision with nearest zombie
		if (nearest_index != -1 && bullet_bounds.intersects(vec_of_zombies[nearest_index].getSprite().getGlobalBounds()))
		{
			vec_of_zombies[nearest_index].livesDecr();
			vec_of_zombies[nearest_index].updateHealthBar();
			player1.getBulletClip().erase(player1.getBulletClip().begin() + i);
			//Death sound
			if (vec_of_zombies[nearest_index].getLives() <= 0)
			{
				hud.updateScore(vec_of_zombies[nearest_index].getScoreValue());
				vec_of_zombies.erase(vec_of_zombies.begin() + nearest_index);
				
				int index = 0;
				for (int i = 0; i < 24; i++)
				{
					if (zombie_sound[i].getStatus() != sf::Sound::Playing)
					{
						index = i;
						break;
					}
				}
				zombie_sound[index].setVolume(30);
				zombie_sound[index].play();
			}
		}
	}
	
	//End of measure
	//std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	//Calculate the duration between the two time points
	//std::chrono::duration<double> duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

	//Print the duration in seconds
	//std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;
}

void Game::zombieHandling_2Player(Player& player1, Player &player2, Zombie& zombie, Zombie& strong_zombie, Zombie& fast_zombie, HUD& hud, HUD &hud2)
{
	Game::zombieHandling(player1, zombie, strong_zombie, fast_zombie, hud);

	for (size_t i = 0; i < player2.getBulletClip().size(); i++)
	{
		sf::FloatRect bulletBounds = player2.getBulletClip()[i].getGlobalBounds();
		float nearestDistance = std::numeric_limits<float>::max(); // Najbli¿sza odleg³oœæ pocz¹tkowo ustawiona na maksymaln¹ wartoœæ
		int nearestIndex = -1; // Indeks najbli¿szego zombie

		//bullet-zombie collison
		for (size_t i = 0; i < player2.getBulletClip().size(); i++)
		{
			sf::FloatRect bullet_bounds = player2.getBulletClip()[i].getGlobalBounds();
			float nearest_distance = std::numeric_limits<float>::max(); //Closest distance firstly set to max
			int nearest_index = -1; //Closest zombie index

			//Find nearest zombie
			for (size_t j = 0; j < vec_of_zombies.size(); j++)
			{
				sf::FloatRect zombie_bounds = vec_of_zombies[j].getSprite().getGlobalBounds();
				float distance = std::sqrt(std::pow(bullet_bounds.left - zombie_bounds.left, 2) + std::pow(bullet_bounds.top - zombie_bounds.top, 2));

				//Check if zombie is the nearest one
				if (distance < nearest_distance)
				{
					nearest_distance = distance;
					nearest_index = j;
				}
			}

			//Check collision with nearest zombie
			if (nearest_index != -1 && bullet_bounds.intersects(vec_of_zombies[nearest_index].getSprite().getGlobalBounds()))
			{
				vec_of_zombies[nearest_index].livesDecr();
				vec_of_zombies[nearest_index].updateHealthBar();
				player2.getBulletClip().erase(player2.getBulletClip().begin() + i);
				if (vec_of_zombies[nearest_index].getLives() <= 0)
				{
					hud2.updateScore(vec_of_zombies[nearest_index].getScoreValue());
					vec_of_zombies.erase(vec_of_zombies.begin() + nearest_index);

					int index = 0;
					for (int i = 0; i < 24; i++)
					{
						if (zombie_sound[i].getStatus() != sf::Sound::Playing)
						{
							index = i;
							break;
						}
					}
					zombie_sound[index].setVolume(30);
					zombie_sound[index].play();
				}
			}
		}
	}
}

//Kolizje zombie zawêziæ do tych, które nas interesuj¹ (Optymalizacja)
//Done with Nearest Neighbour Algorithm

//Standard loop-in-loop checking every zombie with each bullet
	/*
	Time taken : 6e-07 seconds
		Time taken : 6e-07 seconds
		Time taken : 5e-07 seconds
		shot
		Time taken : 9.6e-06 seconds
		Time taken : 1.11e-05 seconds
		Time taken : 1.08e-05 seconds
		Time taken : 1.36e-05 seconds
		Time taken : 1.41e-05 seconds
		Time taken : 1.46e-05 seconds
		Time taken : 1.27e-05 seconds
		Time taken : 1.42e-05 seconds
		Entity destructed...
		Time taken : 0.0011213 seconds
		Time taken : 7e-07 seconds
		Time taken : 7e-07 seconds
		Time taken : 7e-07 seconds
		Time taken : 1.1e-06 seconds
		Time taken : 9e-07 seconds
		Time taken : 9e-07 seconds
		Time taken : 8e-07 seconds
		Time taken : 8e-07 seconds
		*/

		//Nearest neighbour algorithm 
		/*  Time taken : 1.4e-06 seconds
			Time taken : 1e-06 seconds
			Time taken : 9e-07 seconds
			Time taken : 8e-07 seconds
			Time taken : 1.38e-05 seconds
			Time taken : 1.57e-05 seconds
			Time taken : 1.83e-05 seconds
			Time taken : 1.66e-05 seconds
			Time taken : 1.71e-05 seconds
			Time taken : 1.73e-05 seconds
			Time taken : 2.29e-05 seconds
			Time taken : 1.67e-05 seconds
			Time taken : 1.66e-05 seconds
			Time taken : 1.66e-05 seconds
			Time taken : 1.65e-05 seconds
			Time taken : 1.95e-05 seconds
			Time taken : 1.7e-05 seconds
			Time taken : 1.61e-05 seconds
			Time taken : 1.81e-05 seconds
			Time taken : 1.88e-05 seconds
			Time taken : 5.21e-05 seconds
			*/

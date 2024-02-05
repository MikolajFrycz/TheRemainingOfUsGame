#include "Player.h"

Player::Player() : Entity()
{
	temp_ammo_for_hud = 10;
	curr_ammo = 10;
	max_ammo = 10;
	sht_timer = 0;
}

Player::Player(int lives_ct, int max_amm, int curr_amm, sf::Vector2f pos) 
	: Entity(lives_ct, pos), max_ammo(max_amm), curr_ammo(curr_amm), start_pos(pos), temp_ammo_for_hud(curr_amm) 
{
	sht_timer = 0;
}

Player::~Player()
{
	std::cout << "Player ceased\n";
}

void Player::player1Movement(int windsize)
{
	int keyTime = 8;

	if (keyTime < 8)
		keyTime++;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && getSprite().getPosition().x > 120.f)
	{
		getSprite().move(-8.f, 0.f);
		keyTime = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && getSprite().getPosition().x + 210.f < windsize)
	{
		getSprite().move(8.f, 0.f);
		keyTime = 0;
	}
	getPos() = getSprite().getPosition();
}

void Player::player2Movement(int windsize)
{
	int keyTime = 8;

	if (keyTime < 8)
		keyTime++;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && getSprite().getPosition().x > 120.f)
	{
		getSprite().move(-8.f, 0.f);
		keyTime = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && getSprite().getPosition().x + 210.f < windsize)
	{
		getSprite().move(8.f, 0.f);
		keyTime = 0;
	}
	getPos() = getSprite().getPosition();
}

void Player::shootingAnimation(sf::Clock reloadclock)
{
	if (isShooting)
	{
		sf::Time tempTime2 = reloadclock.getElapsedTime();
		setSprite(1, getPos());
		if (tempTime2.asMilliseconds() >= 200)
		{

			setSprite(0, getPos());
			isShooting = false;
		}
	}
}

void Player::reloadAnimation(sf::Clock reloadclock, HUD& hud)
{
	
	if (isReloading == true)
	{
		
		sf::Time tempTime = reloadclock.getElapsedTime();

		setSprite(2, getPos());
		if (tempTime.asMilliseconds() >= 330 && tempTime.asMilliseconds() < 660)
		{
			setSprite(3, getPos());

		}
		else if (tempTime.asMilliseconds() >= 660)
		{
			setSprite(4, getPos());

		}

		// Check if reload time is complete
		if (tempTime.asMilliseconds() >= 1000)
		{
			setSprite(0, getPos());
			resetAmmo(hud);
			isReloading = false;

		}
	}
	
}

bool Player::playerReload(sf::Clock &reloadClock, sf::Keyboard::Key key)
{
	bool reload_snd = false;
	if (sf::Keyboard::isKeyPressed(key) || curr_ammo == 0)
	{
		if (isReloading == false && curr_ammo < max_ammo)
		{
			reload_snd = true;
			std::cout << "Reload\n";
			isReloading = true;
			temp_ammo_for_hud = curr_ammo;
			curr_ammo = 0;
			reloadClock.restart();
		}
	}
	if (reload_snd)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Player::shootPistol(sf::Keyboard::Key shootkey, Bullet &bullet, sf::RenderWindow& target_window, sf::Clock &reloadClock, HUD &hud)
{
	bool wasShot = false;

	if (sht_timer < bullet.getShotTimer())
		sht_timer++;

	//Shooting procedure
	if (curr_ammo > 0 && isReloading == false)
	{

		if (sf::Keyboard::isKeyPressed(shootkey) && sht_timer >= bullet.getShotTimer())
		{

			reloadClock.restart();
			isShooting = true;
			bullet.resetPos(Player::getCenter());
				
			bullet_clip.push_back(sf::RectangleShape(bullet.getShape()));
				
			std::cout << "shot\n";
			curr_ammo--;
			hud.changeCurrAmmo(-1);
			sht_timer = 0;
			wasShot = true;
		}
	}
	
	//bullet handling
	if (curr_ammo >= 0)
	{
		for (size_t i = 0; i < bullet_clip.size(); i++)
		{
			bullet_clip[i].move(0.f, -30.f);

			if (bullet_clip[i].getPosition().y < 0)
			{
				bullet_clip.erase(bullet_clip.begin() + i);
			}
		}
	}

	if (wasShot)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Player::getBulletClipSize()
{
	return bullet_clip.size();
}

std::vector<sf::RectangleShape> &Player::getBulletClip()
{
	return bullet_clip;
}

int Player::getCurrAmmo()
{
	return curr_ammo;
}

void Player::resetAmmo(HUD &hud)
{
	hud.changeCurrAmmo(max_ammo - temp_ammo_for_hud);
	curr_ammo = max_ammo;
}

bool Player::getIsShooting()
{
	return isShooting;
}

void Player::changeIsShootingValue(bool val)
{
	isShooting = val;
}

void Player::playerReset()
{
	curr_ammo = max_ammo;
	Player::setPos(start_pos);
	isReloading = false;
	Player::setSprite(0, Player::getPos());
	Entity::getLives() += 1;
	bullet_clip.erase(bullet_clip.begin(), bullet_clip.end());
}

bool Player::getIsReloading()
{
	return isReloading;
}

int Player::getMaxAmmo()
{
	return max_ammo;
}

void Player::Draw(sf::RenderWindow& target)
{
	target.draw(Player::getSprite());
}

int Player::getShotTimer()
{
	return sht_timer;
}
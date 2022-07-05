#include "GameManager.h"
#include <cmath>
#include "Pistol.h"
#include <algorithm>
#include "BounceBullet.h"
#include <chrono>
#include <random>
#include "MusicManager.h"
#include <fstream>
#include "LevelManager.h"


static const float VIEW_HEIGHT = 512.0f;

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int GameManager::play(sf::RenderWindow& window){
	//SETUP

	LevelManager::loadLevel(*this, "fajny string");
	bool b = true;

	int hp = 2;
	std::string h_f;
	std::ifstream file("conf.g");
	if(file.is_open()) {
		file >> hp;
	}
	file.close();

	sf::RectangleShape background(sf::Vector2f(Config::getInstance().getScreenWidth() / 2.f,Config::getInstance().getScreenHeight()));
	background.setTexture(&texture_pool.at("background_texture"));

	Block ammo_box_low(&texture_pool.at("ammo"),sf::Vector2f(32.0f,32.0f),sf::Vector2f(16.5*32,Config::getInstance().getScreenHeight()-1.5*32.0f));
	Block ammo_box_mid(&texture_pool.at("ammo"),sf::Vector2f(32.0f,32.0f),sf::Vector2f(16.5*32,16.5*32.0f));
	Block ammo_box_top(&texture_pool.at("ammo"),sf::Vector2f(32.0f,32.0f),sf::Vector2f(16.5*32,2.5*32.0f));
	float ammo_box_low_cooldown = 0.f;
	float ammo_box_mid_cooldown = 0.f;
	float ammo_box_top_cooldown = 0.f;

	float initial_ammo_cooldown = 20.f;
	int random_ammo_max_cooldown = 30.f;

	//PLAYER1
    Player player1(sf::Vector2f(40.f, 40.f), sf::Vector2f(120.f, 20.f), &texture_pool.at("player_one"),&texture_pool.at("arrow"), &texture_pool.at("red_idle"), 1, MusicManager::getInstance().gunBuffer1, MusicManager::getInstance().pickBuffer1);
	std::unique_ptr<WeaponBase> pistol1 = std::make_unique<Pistol>();
	player1.setWeapon(std::move(pistol1));
	Ammunition ammo1(std::make_unique<BounceBullet>(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f), &texture_pool.at("bounce_bullet")), &texture_pool.at("bullet"), 0);
	player1.setAmmo(std::move(ammo1), false);

	sf::View viewOne = window.getDefaultView();
	viewOne.setSize(sf::Vector2f(Config::getInstance().getScreenWidth(),Config::getInstance().getScreenHeight()));
	viewOne.setViewport(sf::FloatRect(-0.25f, 0.f, 1.f, 1.f));
	viewOne.setCenter(sf::Vector2f(Config::getInstance().getScreenWidth() / 4.f,Config::getInstance().getScreenHeight() / 2.f));

	player1.setHealth(hp);

	//PLAYER2
    Player player2(sf::Vector2f(40.f, 40.f), sf::Vector2f(900.f, 20.f), &texture_pool.at("player_two"),&texture_pool.at("arrow"), &texture_pool.at("red_idle"), 2, MusicManager::getInstance().gunBuffer2, MusicManager::getInstance().pickBuffer2);
	std::unique_ptr<WeaponBase> pistol2 = std::make_unique<Pistol>();
	player2.setWeapon(std::move(pistol2));
	Ammunition ammo2(std::make_unique<BounceBullet>(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f), &texture_pool.at("bounce_bullet")), &texture_pool.at("bullet"), 0);
	player2.setAmmo(std::move(ammo2), false);

	player2.setRotation(180.f);
	player2.changeRotationDirection();

	sf::View viewTwo = window.getDefaultView();
	viewTwo.setSize(sf::Vector2f(Config::getInstance().getScreenWidth(),Config::getInstance().getScreenHeight()));
	viewTwo.setViewport(sf::FloatRect(0.25f, 0.f, 1.f, 1.f));
	viewTwo.setCenter(sf::Vector2f(Config::getInstance().getScreenWidth() / 4.f,Config::getInstance().getScreenHeight() / 2.f));

	player2.setHealth(hp);

	int viewOneRotationC = 0;
	int viewTwoRotationC = 0;
	int viewOneRotationCounterC = 0;
	int viewTwoRotationCounterC = 0;

	int rotationsNeeded = 45;
	float angle = 90.f;
	float degrees = angle / rotationsNeeded;

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::minstd_rand0 generator (seed);

	// LOOP
	float deltaTime = 0.0f;
	sf::Clock clock;
    while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		if (deltaTime > 1.0f / 20.f)
			deltaTime = 1.0f / 20.f;

		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
				if(player1.rotateCounterClockwise()) {
					viewOneRotationC += rotationsNeeded;
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
				if(player1.rotateClockwise()) {
					viewOneRotationCounterC += rotationsNeeded;
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
				if(player2.rotateCounterClockwise()) {
					viewTwoRotationC += rotationsNeeded;
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
				if(player2.rotateClockwise()) {
					viewTwoRotationCounterC += rotationsNeeded;
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
				b = !b;
			}
			break;
			}
		}

		if(viewOneRotationC) {
			viewOne.rotate(-degrees);
			viewOneRotationC--;
		}
		if(viewOneRotationCounterC) {
			viewOne.rotate(degrees);
			viewOneRotationCounterC--;
		}
		if(viewTwoRotationC) {
			viewTwo.rotate(-degrees);
			viewTwoRotationC--;
		}
		if(viewTwoRotationCounterC) {
			viewTwo.rotate(degrees);
			viewTwoRotationCounterC--;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			player1.goLeft();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			player1.goRight();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			player1.doJump();
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
			player1.shoot(bullets);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			player2.goLeft();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			player2.goRight();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			player2.doJump();
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::K))
			player2.shoot(bullets);


		// UPDATES

		player1.update(deltaTime);

		player2.update(deltaTime);

		for(auto& bullet : bullets)
			bullet->update(deltaTime);


		if(ammo_box_low_cooldown >= 0)
			ammo_box_low_cooldown-=deltaTime;
		if(ammo_box_mid_cooldown >= 0)
			ammo_box_mid_cooldown-=deltaTime;
		if(ammo_box_top_cooldown >= 0)
			ammo_box_top_cooldown-=deltaTime;

		// COLLISIONS

		sf::Vector2f direction;

		Collider player1Collider = player1.getCollider();

		for (Block& Block : blocks)
			if (Block.getCollider().checkCollision(player1Collider, direction, 1.0f, true))
			{
				player1.onCollision(direction);
			}

		Collider player2Collider = player2.getCollider();

		for (Block& Block : blocks)
			if (Block.getCollider().checkCollision(player2Collider, direction, 1.0f, true))
			{
				player2.onCollision(direction);
			}

		for (auto& bullet : bullets)
			for(auto& block : blocks)
				if (block.getCollider().checkCollision(bullet->getCollider(), direction, 1.0f, true))
			{
				bullet->onCollision(direction);
			}

		for (auto& bullet : bullets)
			if (bullet->getCollider().checkCollision(player1.getCollider(), direction, 0.0f, false))
			{
				bullet->hitPlayer(player1);
			}

		for (auto& bullet : bullets)
			if (bullet->getCollider().checkCollision(player2.getCollider(), direction, 0.0f, false))
			{
				bullet->hitPlayer(player2);
			}

		if(ammo_box_low_cooldown < 0)
			if(ammo_box_low.getCollider().checkCollision(player1.getCollider(), direction, 0.0f, false)) {
				Ammunition ammo(std::make_unique<BounceBullet>(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f), &texture_pool.at("bounce_bullet")), &texture_pool.at("bullet"), 5);
				player1.setAmmo(std::move(ammo));
				ammo_box_low_cooldown = initial_ammo_cooldown + static_cast<float>(generator() % random_ammo_max_cooldown);
			}
		if(ammo_box_mid_cooldown < 0)
			if(ammo_box_mid.getCollider().checkCollision(player1.getCollider(), direction, 0.0f, false)) {
				Ammunition ammo(std::make_unique<BounceBullet>(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f), &texture_pool.at("bounce_bullet")), &texture_pool.at("bullet"), 5);
				player1.setAmmo(std::move(ammo));
				ammo_box_mid_cooldown = initial_ammo_cooldown + static_cast<float>(generator() % random_ammo_max_cooldown);
			}
		if(ammo_box_top_cooldown < 0)
			if(ammo_box_top.getCollider().checkCollision(player1.getCollider(), direction, 0.0f, false)) {
				Ammunition ammo(std::make_unique<BounceBullet>(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f), &texture_pool.at("bounce_bullet")), &texture_pool.at("bullet"), 5);
				player1.setAmmo(std::move(ammo));
				ammo_box_top_cooldown = initial_ammo_cooldown + static_cast<float>(generator() % random_ammo_max_cooldown);
			}

		if(ammo_box_low_cooldown < 0)
			if(ammo_box_low.getCollider().checkCollision(player2.getCollider(), direction, 0.0f, false)) {
				Ammunition ammo(std::make_unique<BounceBullet>(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f), &texture_pool.at("bounce_bullet")), &texture_pool.at("bullet"), 5);
				player2.setAmmo(std::move(ammo));
				ammo_box_low_cooldown = initial_ammo_cooldown + static_cast<float>(generator() % random_ammo_max_cooldown);
			}
		if(ammo_box_mid_cooldown < 0)
			if(ammo_box_mid.getCollider().checkCollision(player2.getCollider(), direction, 0.0f, false)) {
				Ammunition ammo(std::make_unique<BounceBullet>(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f), &texture_pool.at("bounce_bullet")), &texture_pool.at("bullet"), 5);
				player2.setAmmo(std::move(ammo));
				ammo_box_mid_cooldown = initial_ammo_cooldown + static_cast<float>(generator() % random_ammo_max_cooldown);
			}
		if(ammo_box_top_cooldown < 0)
			if(ammo_box_top.getCollider().checkCollision(player2.getCollider(), direction, 0.0f, false)) {
				Ammunition ammo(std::make_unique<BounceBullet>(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f), &texture_pool.at("bounce_bullet")), &texture_pool.at("bullet"), 5);
				player2.setAmmo(std::move(ammo));
				ammo_box_top_cooldown = initial_ammo_cooldown + static_cast<float>(generator() % random_ammo_max_cooldown);
			}

		//REMOVE DELETED BULLETS
		bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](std::unique_ptr<Bullet>& b)->bool{ return b->isDestroyed();}), bullets.end());


		//DRAW VIEW1
		window.setView(viewOne);

		window.clear(sf::Color(150, 150, 150));

		for (auto& block : blocks) {
			block.draw(window);
		}

		if(b)
		window.draw(background);

		for (auto& block : decorationBlocks) {
			block.draw(window);
		}

		if(ammo_box_low_cooldown < 0)
			ammo_box_low.draw(window);
		if(ammo_box_mid_cooldown < 0)
			ammo_box_mid.draw(window);
		if(ammo_box_top_cooldown < 0)
			ammo_box_top.draw(window);

		for(auto& bullet : bullets) {
			bullet->draw(window);
		}

		player1.draw(window);
		player2.draw(window);

		//DRAW VIEW2
		window.setView(viewTwo);

		for (auto& block : blocks) {
			block.draw(window);
		}

		if(b)
		window.draw(background);

		for (auto& block : decorationBlocks) {
			block.draw(window);
		}

		if(ammo_box_low_cooldown < 0)
			ammo_box_low.draw(window);
		if(ammo_box_mid_cooldown < 0)
			ammo_box_mid.draw(window);
		if(ammo_box_top_cooldown < 0)
			ammo_box_top.draw(window);

		for(auto& bullet : bullets) {
			bullet->draw(window);
		}

		player1.draw(window);
		player2.draw(window);

		// DISPLAY STATUS

		window.setView(window.getDefaultView());
		sf::Text ps1(std::string("Hp: ").append(std::to_string(player1.getHealth())).append("\nAmmo: ").append(std::to_string(player1.getAmmoCount())), Config::getInstance().c_font, 25);
		sf::Text ps2(std::string("Hp: ").append(std::to_string(player2.getHealth())).append("\nAmmo: ").append(std::to_string(player2.getAmmoCount())), Config::getInstance().c_font, 25);
		ps1.setPosition(sf::Vector2f(48.f, 928.f));
		ps2.setPosition(sf::Vector2f(Config::getInstance().getScreenWidth() / 2.f + 48.f, 928.f));
		ps1.setColor(sf::Color::White);
		ps2.setColor(sf::Color::White);

		window.draw(ps1);
		window.draw(ps2);

		window.display();

		//VICTORY CHECK

		if(!player1.isAlive() && !player2.isAlive()) {
			window.setView(window.getDefaultView());
			return 3;
		}

		if(!player1.isAlive()) {
			window.setView(window.getDefaultView());
			return 2;
		}
		if(!player2.isAlive()) {
			window.setView(window.getDefaultView());
			return 1;
		}

	}


	return 0;
}
#include "LevelManager.h"

bool LevelManager::GameManager::loadLevel(GameManager& gm, std::string fileName){

	Config::getInstance().setScreenWidth(Config::getInstance().getScreenWidth() / 2.f);

    auto& texture_pool = gm.texture_pool;
    auto& blocks = gm.blocks;

	texture_pool.insert({"background_texture",sf::Texture()});
	texture_pool.at("background_texture").loadFromFile(".\\Textures\\Background.png");


	texture_pool.insert({"transparent", sf::Texture()});
	texture_pool.at("transparent").loadFromFile(".\\Textures\\Beton.png");

	texture_pool.insert({"player_one",sf::Texture()});
	texture_pool.at("player_one").loadFromFile(".\\Textures\\Czerwony.png");


	texture_pool.insert({"player_two",sf::Texture()});
	texture_pool.at("player_two").loadFromFile(".\\Textures\\Niebieski.png");

	texture_pool.insert({"arrow",sf::Texture()});
	texture_pool.at("arrow").loadFromFile(".\\Textures\\Strzalka.png");

	texture_pool.insert({"ammo",sf::Texture()});
	texture_pool.at("ammo").loadFromFile(".\\Textures\\ammo_box.png");

	texture_pool.insert({"red_idle",sf::Texture()});
	texture_pool.at("red_idle").loadFromFile(".\\Textures\\CHARACTER_SPRITES\\Red\\Gunner_Red_Idle.png");

	texture_pool.insert({"bullet",sf::Texture()});
	texture_pool.at("bullet").loadFromFile(".\\Textures\\bullet.png");

	texture_pool.insert({"bounce_bullet",sf::Texture()});
	texture_pool.at("bounce_bullet").loadFromFile(".\\Textures\\bounce_bullet.png");

	//Granice
	Block borderUpper(&texture_pool.at("transparent"),sf::Vector2f(Config::getInstance().getScreenWidth(),32.0f),sf::Vector2f(Config::getInstance().getScreenWidth()/2.0f,16.0f));
	Block borderLower(&texture_pool.at("transparent"),sf::Vector2f(Config::getInstance().getScreenWidth(),32.0f),sf::Vector2f(Config::getInstance().getScreenWidth()/2.0f,Config::getInstance().getScreenHeight()-16.0f));
	Block borderLeft(&texture_pool.at("transparent"),sf::Vector2f(32.0f,Config::getInstance().getScreenHeight()-64.0f),sf::Vector2f(16,Config::getInstance().getScreenHeight()/2.0f));
	Block borderRight(&texture_pool.at("transparent"),sf::Vector2f(32.0f,Config::getInstance().getScreenHeight()-64.0f),sf::Vector2f(Config::getInstance().getScreenWidth()-16.0f,Config::getInstance().getScreenHeight()/2.0f));

	blocks.push_back(borderUpper);
	blocks.push_back(borderLower);
	blocks.push_back(borderLeft);
	blocks.push_back(borderRight);

	//Bloki poziome lewe
	Block HorizontalLeftUpper(&texture_pool.at("transparent"),sf::Vector2f(7*32,16.0f),sf::Vector2f(6.5f*32,Config::getInstance().getScreenHeight()-4.75f*32));
	Block HorizontalLeftLower(&texture_pool.at("transparent"),sf::Vector2f(7*32,16.0f),sf::Vector2f(6.5f*32,7.25f*32));

	blocks.push_back(HorizontalLeftLower);
	blocks.push_back(HorizontalLeftUpper);

	//Bloki poziome prawe
	Block HorizontalRightUpper(&texture_pool.at("transparent"),sf::Vector2f(7*32,16.0f),sf::Vector2f(Config::getInstance().getScreenWidth()-6.5f*32,Config::getInstance().getScreenHeight()-4.75f*32));
	Block HorizontalRightLower(&texture_pool.at("transparent"),sf::Vector2f(7*32,16.0f),sf::Vector2f(Config::getInstance().getScreenWidth()-6.5f*32,7.25f*32+2.0f));

	blocks.push_back(HorizontalRightLower);
	blocks.push_back(HorizontalRightUpper);

	//Bloki pionowe po bokach
	Block VerticalLeft(&texture_pool.at("transparent"),sf::Vector2f(32.0f,12*32.0f),sf::Vector2f(6.5*32.0f,17*32.0f));
	Block VerticalRight(&texture_pool.at("transparent"),sf::Vector2f(32.0f,12*32.0f),sf::Vector2f(Config::getInstance().getScreenWidth()-6.5*32.0f,17*32.0f));

	blocks.push_back(VerticalRight);
	blocks.push_back(VerticalLeft);

	//Bloki pionowe srodek
	Block VerticalMidLower(&texture_pool.at("transparent"),sf::Vector2f(32.0f,10*32.0f),sf::Vector2f(16.5*32,Config::getInstance().getScreenHeight()-9*32.0f));
	Block VerticalMidUpper(&texture_pool.at("transparent"),sf::Vector2f(32.0f,11*32.0f),sf::Vector2f(16.5*32,9.5*32.0f));

	blocks.push_back(VerticalMidLower);
	blocks.push_back(VerticalMidUpper);

	//Boxy
	Block BoxLeftUpper(&texture_pool.at("transparent"),sf::Vector2f(64.0f,32.0f),sf::Vector2f(13*32.0f,Config::getInstance().getScreenHeight()-2.5*32.0f));
	Block BoxLeftLower(&texture_pool.at("transparent"),sf::Vector2f(64.0f,32.0f),sf::Vector2f(13*32.0f,Config::getInstance().getScreenHeight()-1.5*32.0f));

	Block BoxRightUpper(&texture_pool.at("transparent"),sf::Vector2f(64.0f,32.0f),sf::Vector2f(20*32.0f,Config::getInstance().getScreenHeight()-2.5*32.0f));
	Block BoxRightLower(&texture_pool.at("transparent"),sf::Vector2f(64.0f,32.0f),sf::Vector2f(20*32.0f,Config::getInstance().getScreenHeight()-1.5*32.0f));

	blocks.push_back(BoxLeftUpper);
	blocks.push_back(BoxLeftLower);
	blocks.push_back(BoxRightUpper);
	blocks.push_back(BoxRightLower);

	//Platforma nad rura

	Block PlatformMiddle(&texture_pool.at("transparent"),sf::Vector2f(5*32.0f,16.0f),sf::Vector2f(16.5*32.0,3.75*32.0f+5.0f));

	blocks.push_back(PlatformMiddle);

	Config::getInstance().setScreenWidth(Config::getInstance().getScreenWidth() * 2.f);

	return false;
}
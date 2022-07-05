#pragma once
#include <SFML/Audio.hpp>

class MusicManager{
    public:
    static MusicManager& getInstance();
    void setVolume(float newVolume){volume=newVolume;}
    float getVolume(){return volume;}
    sf::SoundBuffer gunBuffer1;
    sf::SoundBuffer gunBuffer2;
	sf::SoundBuffer pickBuffer1;
    sf::SoundBuffer pickBuffer2;

    private:
    MusicManager();
    float volume = 50.0f;

    MusicManager(const MusicManager& m) = delete;
    MusicManager(const MusicManager&& m) = delete;

};
#include "MusicManager.h"

MusicManager& MusicManager::getInstance() {
    static MusicManager conf;
    return conf;
}

MusicManager::MusicManager() {
    gunBuffer1.loadFromFile(".\\Music\\pistol-shot-14649.wav");
    gunBuffer2.loadFromFile(".\\Music\\pistol-shot-14649.wav");
    pickBuffer1.loadFromFile(".\\Music\\item-equip-6904.wav");
    pickBuffer2.loadFromFile(".\\Music\\item-equip-6904.wav");
}
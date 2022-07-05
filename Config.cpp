#include "Config.h"

Config& Config::getInstance() {
    static Config conf;
    return conf;
}

Config::Config() {

}
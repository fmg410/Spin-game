#include "MenuManager.h"
#include "GameManager.h"

// MenuManager::MenuManager(){
//     WindowManager window;
//     Button start("Start",sf::Vector2f(50.0f,50.0f),sf::Color::Red,sf::Color::Black,25,);
//     Button options("Start",sf::Vector2f(50.0f,50.0f),sf::Color::Red,sf::Color::Black,25);
//     Button highscore("Start",sf::Vector2f(50.0f,50.0f),sf::Color::Red,sf::Color::Black,25);
// }

void MenuManager::initializePanels(sf::Vector2f menuSize, sf::Font& font){
panels.push_back(std::bind([menuSize, &font](MenuManager& m){
        m.buttons.clear();
        Button logo(sf::Vector2f(menuSize.x/4,menuSize.y/6),".\\Textures\\logo.png",sf::Vector2f(menuSize.x/2.0f,menuSize.y/10.0f), std::bind([](MenuManager& m){m.buttons.at(0).rotateButton(90.f);}, std::ref(m)));
        Button start("Start",sf::Vector2f(menuSize.x/4,menuSize.y/6),sf::Color::Red,sf::Color::Black,20,sf::Vector2f(menuSize.x/2.0f,menuSize.y/4+menuSize.y/10.0f), font, std::bind([](sf::RenderWindow& w, MenuManager& m){GameManager g; m.won = g.play(w); m.changePanel(1);}, std::ref(m.window), std::ref(m)));
        Button options("Sound ON",sf::Vector2f(menuSize.x/4,menuSize.y/6),sf::Color::Red,sf::Color::Black,20,sf::Vector2f(menuSize.x/2.0f,2*menuSize.y/4+menuSize.y/10.0f), font, std::bind([](MenuManager& m){MusicManager::getInstance().setVolume(MusicManager::getInstance().getVolume()== 0.0f ? 50.0f : 0.0f); if(MusicManager::getInstance().getVolume()== 0.0f){m.buttons.at(2).changeString("Sound OFF");} if(MusicManager::getInstance().getVolume()== 50.0f){m.buttons.at(2).changeString("Sound ON");}; },std::ref(m)));
        if(MusicManager::getInstance().getVolume()==0.00f){
            options.changeString("Sound OFF");
        }else{
            options.changeString("Sound ON");
        }

        Button quit("Quit",sf::Vector2f(menuSize.x/4,menuSize.y/6),sf::Color::Red,sf::Color::Black,20,sf::Vector2f(menuSize.x/2.0f,3*menuSize.y/4+menuSize.y/10.0f), font, std::bind([](sf::RenderWindow& w){w.close();},std::ref(m.window)));

        m.buttons.push_back(logo);
        m.buttons.push_back(start);
        m.buttons.push_back(options);
        m.buttons.push_back(quit);
    }, std::ref(*this)));
    panels.push_back(std::bind([menuSize,&font](MenuManager& m){

    std::string winner;
    m.buttons.clear();

    if(m.won==1){
        winner=sf::String("Player 1 won !!");
    } else if(m.won == 2){
    winner=sf::String("Player 2 won !!");
    } else{
    winner=sf::String("It's a draw !!");
    }

    Button txt(winner,sf::Vector2f(menuSize.x/4,menuSize.y/6),sf::Color::Transparent,sf::Color::Yellow,45,sf::Vector2f(menuSize.x/2.0f,menuSize.y/2.0f),font,[](){});
    Button back("Back to menu",sf::Vector2f(menuSize.x/4,menuSize.y/6),sf::Color::Red,sf::Color::Black,20,sf::Vector2f(menuSize.x/2.0f,3*menuSize.y/4+menuSize.y/10.0f), font, std::bind([](MenuManager& m){m.changePanel(0);},std::ref(m)));

    m.buttons.push_back(txt);
    m.buttons.push_back(back);


},std::ref(*this)));
}

MenuManager::MenuManager(sf::Font& font, sf::RenderWindow& window) : window(window)  {
    sf::Texture buttonTxt;
    Button start("Start",sf::Vector2f(50.0f,50.0f),sf::Color::Red,sf::Color::Black,12,sf::Vector2f(standardWidth/2.0f,standardHeight/3+standardHeight/10.0f), font, [](){std::cout << "start";});
    Button options("Options",sf::Vector2f(50.0f,50.0f),sf::Color::Red,sf::Color::Black,12,sf::Vector2f(standardWidth/2.0f,2*standardHeight/3+standardHeight/10.0f), font, [](){std::cout << "options";});

    buttons.push_back(start);
    buttons.push_back(options);

}

MenuManager::MenuManager(sf::Vector2f menuSize, sf::Font& font, sf::RenderWindow& window) : window(window) {
    initializePanels(menuSize, font);
}


void MenuManager::drawMenu(sf::RenderWindow& window){
    for(int i=0; i<buttons.size();i++){
        buttons.at(i).drawButton(window);
    }
}

void MenuManager::changeWindow(sf::RenderWindow& window){
    window.clear();

}
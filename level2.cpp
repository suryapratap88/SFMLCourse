#include <SFML/Graphics.hpp>
int main(){
    sf::RenderWindow window(sf::VideoMode({800,600}),"Level-2=sprite");
    sf::Texture playerTexture;
    if(!playerTexture.loadFromFile("player.png")){
        return -1;
    }
    auto size = playerTexture.getSize();
    sf::Sprite player(playerTexture);
    player.setPosition({400.f,300.f});
    player.setOrigin({size.x/2.f,size.y/2.f});
    player.setColor(sf::Color::Red);
    player.setScale({.5,.5});
    while(window.isOpen()){
        while(const std::optional event = window.pollEvent()){
            if(event->is<sf::Event::Closed>()){
                window.close();
            }
        }
        window.clear();
        window.draw(player);
        window.display();
    }
    return 0;
}
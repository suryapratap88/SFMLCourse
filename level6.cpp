#include<SFML/Graphics.hpp>
#include<math.h>
int main(){
    sf::RenderWindow window(sf::VideoMode({800,600}),"Level-6=boundary");
    window.setFramerateLimit(120);
    float speed = 100.f;
    sf::Texture playerTexture;
    if(!playerTexture.loadFromFile("player.png")){
        return -1;
    }
    sf::Sprite player(playerTexture);
    player.setPosition({400.f,300.f});
    player.setScale({0.15f,0.15f});
    auto size= playerTexture.getSize();
    player.setOrigin({size.x/2.f,size.y/2.f});
    sf::Clock clock;
    while(window.isOpen()){
        while(const std::optional event= window.pollEvent()){
            if(event->is<sf::Event::Closed>()){
                window.close();
            }
        }
        sf::Vector2f direction(0.f,0.f);
        float dt = clock.restart().asSeconds();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
            direction.x -= 1.f;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
            direction.y -= 1.f;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
            direction.x += 1.f;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
            direction.y += 1.f;
        }
        float length = std::sqrt(direction.x*direction.x+direction.y*direction.y);
        if(length!=0){
            direction /= length;
        }
        player.move(dt*speed*direction);
        sf::FloatRect bounds=player.getGlobalBounds();
        sf::Vector2f pos=player.getPosition();
        if(bounds.position.x<0){
            pos.x -= bounds.position.x;
        }
        if(bounds.position.y<0){
            pos.y -= bounds.position.y;
        }
        if(bounds.position.x+bounds.size.x>window.getSize().x){
            pos.x -= (bounds.position.x+bounds.size.x-window.getSize().x);
        }
        if(bounds.position.y+bounds.size.y>window.getSize().y){
            pos.y -= (bounds.position.y+bounds.size.y-window.getSize().y);
        }
        player.setPosition(pos);
        window.clear();
        window.draw(player);
        window.display();
    }
    return 0;
}
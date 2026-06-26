#include<SFML/Graphics.hpp>
#include<math.h>
int main(){
    sf::RenderWindow window(sf::VideoMode({800,600}),"Level-7=enemy collision");
    sf::Texture playerTexture;
    if(!playerTexture.loadFromFile("player.png")){
        return -1;
    }
    float hp=100.f;
    float speed=100.f;
    sf::Sprite player(playerTexture);
    player.setPosition({400.f,300.f});
    player.setScale({0.15f,0.15f});
    auto size =playerTexture.getSize();
    player.setOrigin({size.x/2.f,size.y/2.f});
    sf::RectangleShape enemy({50.f,50.f});
    enemy.setPosition({300.f,200.f});
    enemy.setFillColor(sf::Color::Red);
    sf::Clock clock;
    while(window.isOpen()){
        while(const std::optional event= window.pollEvent()){
            if(event->is<sf::Event::Closed>()){
                window.close();
            }
        }
        float dt = clock.restart().asSeconds();
        sf::Vector2f direction(0.f,0.f);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
            direction.x -= 1.f;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
            direction.x += 1.f;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
            direction.y -= 1.f;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
            direction.y += 1.f;
        }
        float length = std::sqrt(direction.x*direction.x+direction.y*direction.y);
        if(length != 0){
            direction /= length;
        }
        sf::Vector2f oldpos=player.getPosition();
        player.move(dt*speed*direction);
        sf::Vector2f pos = player.getPosition();
        sf::FloatRect bounds = player.getGlobalBounds();
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
        if(player.getGlobalBounds().findIntersection(enemy.getGlobalBounds())){
            hp -= 10;
            player.setPosition(oldpos);
        }
        if(hp<=0){
            window.close();
        }
        window.clear();
        window.draw(player);
        window.draw(enemy);
        window.display();
    }
    return 0;
}
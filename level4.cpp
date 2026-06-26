#include<SFML/Graphics.hpp>
int main(){
    sf::RenderWindow window(sf::VideoMode({800,600}),"Level-4=dt+speed");
    sf::Texture playerTexture;
    if(!playerTexture.loadFromFile("player.png")){
        return -1;
    }
    float speed = 50.f;
    window.setFramerateLimit(60);
    sf::Sprite player(playerTexture);
    player.setPosition({400.f,300.f});
    player.setScale({0.15f,0.15f});
    auto size = playerTexture.getSize();
    player.setOrigin({size.x/2.f,size.y/2.f});
    sf::Clock clock;
    while(window.isOpen()){
        while(const std::optional event=window.pollEvent()){
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
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
            direction.y += 1.f;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
            direction.y -= 1.f;
        }
        player.move(speed*direction*dt);
        window.clear();
        window.draw(player);
        window.display();
    }
    return 0;
}
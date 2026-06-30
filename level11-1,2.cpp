#include<SFML/Graphics.hpp>
#include<cmath>
#include<string>
#include<iostream>
int main(){
    sf::RenderWindow window(sf::VideoMode({800,600}),"Level-11=Mouse");
    sf::Texture playerTexture;
    if(!playerTexture.loadFromFile("player.png")){
        return -1;
    }
    window.setFramerateLimit(120);
    sf::Sprite player(playerTexture);
    player.setPosition({400.f,300.f});
    player.setScale({0.15f,0.15f});
    auto size = playerTexture.getSize();
    player.setOrigin({size.x/2.f,size.y/2.f});

    sf::RectangleShape enemy({100.f,100.f});
    enemy.setPosition({200.f,100.f});
    enemy.setFillColor(sf::Color::Red);

    sf::View view;
    view.setSize({800.f,600.f});

    sf::Font font;
    if(!font.openFromFile("arial.ttf")){
        return -1;
    }
    sf::Text hpText(font);
    hpText.setPosition({20.f,20.f});
    hpText.setCharacterSize(30);

    sf::RectangleShape hpBack({200.f,20.f});
    hpBack.setPosition({20.f,60.f});
    hpBack.setFillColor(sf::Color(80,80,80));
    sf::RectangleShape hpBar({200.f,20.f});
    hpBar.setPosition({20.f,60.f});
    hpBar.setFillColor(sf::Color::Green);
    
    float speed = 200.f;
    float hp = 100.f;
    float maxHp =100.f;
     sf::Clock clock;

    while(window.isOpen()){
        while(const std::optional event = window.pollEvent()){
            if(event->is<sf::Event::Closed>()){
                window.close();
            }
        }
        float dt = clock.restart().asSeconds();

         sf::Vector2f direction(0.f, 0.f);
         sf::Vector2i mousePos = sf::Mouse::getPosition(window);
         if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
            std::cout
            << "Left Click: ("
            << mousePos.x
            << ", "
            << mousePos.y
            << ")\n";
         }
         if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)){
            std::cout
            << "Right Click: ("
            << mousePos.x
            << ", "
            << mousePos.y
            << ")\n";
         }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            direction.x -= 1.f;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
            direction.x += 1.f;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
            direction.y -= 1.f;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            direction.y += 1.f;
            
            float length=std::sqrt(direction.x*direction.x+direction.y*direction.y);

            if(length != 0){
                direction /=length;
            }
            if(direction.x>0){
                player.setScale({0.15f,0.15f});
            }
            if(direction.x<0){
                player.setScale({-0.15f,0.15f});
            }
            
            float moveX = direction.x*dt*speed;
            float moveY = direction.y*dt*speed;
             
            player.move({moveX,0.f});
            if(player.getGlobalBounds().findIntersection(enemy.getGlobalBounds())){
                player.move({-moveX,0.f});
                hp -=1.f;
            }
            player.move({0.f,moveY});
            if(player.getGlobalBounds().findIntersection(enemy.getGlobalBounds())){
                player.move({0.f,-moveY});
                hp -=1.f;
            }
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
            view.setCenter(player.getPosition());
            window.setView(view);
            if(hp<0){
                hp = 0;
            }
            hpText.setString("Hp: "+ std::to_string(static_cast<int>(hp)));
            float hpPercent = hp/maxHp;
            hpBar.setSize({hpPercent*200.f,20.f});
            window.clear();
            window.draw(player);
            window.draw(enemy);
            window.draw(hpBack);
            window.draw(hpBar);
            window.draw(hpText);
            window.display();
    }
    return 0;
}
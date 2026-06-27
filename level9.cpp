#include<SFML/Graphics.hpp>
#include<cmath>
#include<string>
int main(){
    sf::RenderWindow window(sf::VideoMode({800,600}),"Level-9=UI");
    sf::Texture playerTexture;
    if(!playerTexture.loadFromFile("player.png")){
        return -1;
    }
    sf::Sprite player(playerTexture);
    player.setPosition({400.f,300.f});
    player.setScale({0.15f,0.15f});
    auto size = playerTexture.getSize();
    player.setOrigin({size.x/2.f,size.y/2.f});

    sf::RectangleShape enemy({100.f,100.f});
    enemy.setFillColor(sf::Color::Red);
    enemy.setPosition({100.f,200.f});
    
    sf::View view;
    view.setSize({800.f,600.f});

    sf::Font font;
    if(!font.openFromFile("arial.ttf")){
        return -1;
    }
    sf::Text hpText(font);
    hpText.setCharacterSize(30);
    hpText.setPosition({20.f,20.f});

    float speed = 200.f;
    float hp = 100.f;

    sf::Clock clock;
    
    while(window.isOpen()){
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }
        float dt = clock.restart().asSeconds();

         sf::Vector2f direction(0.f, 0.f);

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
                player.setScale({0.15,0.15});
            }
            if(direction.x<0){
                player.setScale({-0.15,0.15});
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
            sf::Vector2f pos=player.getPosition();
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

            hpText.setString("HP: " + std::to_string(static_cast<int>(hp)));
            window.clear();
            window.draw(enemy);
            window.draw(player);
            window.draw(hpText);
            window.display();
    }
    return 0;
}
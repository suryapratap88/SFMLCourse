#include<SFML/Graphics.hpp>
#include<cmath>
int main(){
    sf::RenderWindow window(sf::VideoMode({800,600}),"Level-12=vector");
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

    sf::RectangleShape previewBuilding({80.f,80.f});
    previewBuilding.setFillColor(sf::Color(0,250,0,150));
    sf::RectangleShape newBuilding({80.f,80.f});
    newBuilding.setFillColor(sf::Color::Blue);
    newBuilding.setPosition({1000.f,1000.f});
    std::vector<sf::RectangleShape> buildings;

    float speed = 200.f;
    bool placeBuilding = false;
    bool canPlace = true;
    sf::Clock clock;

    while(window.isOpen()){
        sf::Vector2i mousepos = sf::Mouse::getPosition(window);
        sf::Vector2f worldMouse = window.mapPixelToCoords(mousepos);
        float dt = clock.restart().asSeconds();
        while(const std::optional event = window.pollEvent()){
            if(event->is<sf::Event::Closed>()){
                window.close();
            }
            if(const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()){
                if(keyPressed->code==sf::Keyboard::Key::B){
                    placeBuilding = true;
                }
            }
        if(const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()){
            if(mousePressed->button==sf::Mouse::Button::Left and placeBuilding and canPlace){
                newBuilding.setPosition(previewBuilding.getPosition());
                placeBuilding = false;
                buildings.push_back(newBuilding);
            }
        }
        }
        if(placeBuilding){
        previewBuilding.setPosition(worldMouse);
        canPlace = true;
        sf::FloatRect previewBounds = previewBuilding.getGlobalBounds();
            if(previewBounds.findIntersection(enemy.getGlobalBounds()) or previewBounds.findIntersection(player.getGlobalBounds())){
                canPlace = false;
            }
            for(const auto& building : buildings){
                if(previewBounds.findIntersection(building.getGlobalBounds())){
                    canPlace = false;
                    break;
                }
            }
            if(previewBounds.position.x<0){
                canPlace = false;
            }
            if(previewBounds.position.y<0){
                canPlace = false;
            }
            if(previewBounds.position.x+previewBounds.size.x>window.getSize().x){
                canPlace = false;
            }
            if(previewBounds.position.y+previewBounds.size.y>window.getSize().y){
                canPlace = false;
            }
        }
            if(canPlace){
            previewBuilding.setFillColor(sf::Color(0,255,0,155));
        }
        else{
            previewBuilding.setFillColor(sf::Color(250,0,0,150));
        }
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
            }
            for(const auto& building :buildings){
                if(player.getGlobalBounds().findIntersection(building.getGlobalBounds())){
                    player.move({-moveX,0.f});
                }
            }
            player.move({0.f,moveY});
            if(player.getGlobalBounds().findIntersection(enemy.getGlobalBounds())){
                player.move({0.f,-moveY});
            }
            for(const auto& building :buildings){
                if(player.getGlobalBounds().findIntersection(building.getGlobalBounds())){
                    player.move({0.f,-moveY});
                }
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
            window.clear();
            window.draw(player);
            window.draw(enemy);
            if(placeBuilding){
                window.draw(previewBuilding);
            }
            for(const auto& building : buildings){
                window.draw(building);
                    }
            window.display();
    }
    return 0;
}
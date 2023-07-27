
#include <iostream>
#include <sstream>
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"



int main()
{
    /*
    Game game;
    */
    //init game
    float gridSizeF = 100.f;
    unsigned gridSizeU = static_cast<unsigned>(gridSizeF);
    float dt = 0.f;
    sf::Clock dtClock;//delta time
    sf::Vector2i mousePosScreen = sf::Mouse::getPosition();
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;
    sf::Vector2u mousePosGrid; //make this vector2i if you want negatives in grid
    sf::Font fontA;
    fontA.loadFromFile("assets/arial.ttf");
    sf::Text textA;
    textA.setCharacterSize(12);
    textA.setFillColor(sf::Color::White);
    textA.setFont(fontA);
    textA.setPosition(20.f, 20.f);
    textA.setString("TEST");

    sf::Text mapCoordTextH[26];
    
    //we set position in for loop
    sf::Text mapCoordTextV[26];
    //there's a way to do this in a for loop that i don't want to look up
    mapCoordTextH[0].setString("A"); mapCoordTextH[1].setString("B"); mapCoordTextH[2].setString("C"); mapCoordTextH[3].setString("D"); mapCoordTextH[4].setString("E");
    mapCoordTextH[5].setString("F"); mapCoordTextH[6].setString("G"); mapCoordTextH[7].setString("H"); mapCoordTextH[8].setString("I"); mapCoordTextH[9].setString("J");
    mapCoordTextH[10].setString("K"); mapCoordTextH[11].setString("L"); mapCoordTextH[12].setString("M"); mapCoordTextH[13].setString("N"); mapCoordTextH[14].setString("O");
    mapCoordTextH[15].setString("P"); mapCoordTextH[16].setString("Q"); mapCoordTextH[17].setString("R"); mapCoordTextH[18].setString("S"); mapCoordTextH[19].setString("T");
    mapCoordTextH[20].setString("U"); mapCoordTextH[21].setString("V"); mapCoordTextH[22].setString("W"); mapCoordTextH[23].setString("X"); mapCoordTextH[24].setString("Y");
    mapCoordTextH[25].setString("Z");
    


    //init window
    float windowSizeH = 800;
    float windowSizeV = 800;
    sf::RenderWindow window(sf::VideoMode(windowSizeH, windowSizeV), "SoT Map");
    window.setFramerateLimit(60);

    float viewZoom = 1.f;

    sf::View view;
    view.setSize(windowSizeH* viewZoom, windowSizeV * viewZoom);
    //setting size smaller than the window will zoom in. setting it higher than the window zooms out

    view.setCenter(window.getSize().x / 2.f, window.getSize().y / 2.f);

    //viewSpeed is used to say how fast we pan around the map with WASD
    float viewSpeed = 400.f;

    
    //testing lines
    

    for (int i = 0; i <= 26; i++)
    {
        //sf::LineStrip()

    }

    //init game elements
    sf::Vector2f viewCtrStartDrag;
    sf::Vector2i mousePosPrev;
    sf::Vector2i mouseDrag;
    sf::Vector2f mousePosPrevF;
    sf::Vector2f mousePosCurrF;
    sf::Vector2f viewCtrPrev;
    sf::Vector2f viewDrag;
    bool startDrag = false;
    bool zoomHandled = false;
    sf::RectangleShape shape(sf::Vector2f(gridSizeF, gridSizeF));

    const int mapSize = 26;
    sf::RectangleShape tileMap[mapSize][mapSize];
    for (int x = 0; x < mapSize; x++) 
    {
        //setting info for each tile on tileMap
        //also setting info for A, B, C, D... 1, 2, 3, 4...

        //if( y ==0)
        mapCoordTextH[x].setPosition((x * gridSizeF) + (gridSizeF / 2.f), -30.f);
        mapCoordTextH[x].setOrigin(7.f, 0.f);
        mapCoordTextH[x].setCharacterSize(20);
        mapCoordTextH[x].setFont(fontA);

        for (int y = 0; y < mapSize; y++)
        {
            
            tileMap[x][y].setSize(sf::Vector2f(gridSizeF, gridSizeF));
            tileMap[x][y].setFillColor(sf::Color::White);
            tileMap[x][y].setOutlineThickness(1.f);
            tileMap[x][y].setOutlineColor(sf::Color::Black);
            tileMap[x][y].setPosition(x * gridSizeF, y * gridSizeF);

            if(x==0)
            {
                mapCoordTextV[y].setPosition(-30.f, (y * gridSizeF) + (gridSizeF / 2.f));
                mapCoordTextV[y].setOrigin(7.f, 0.f);
                mapCoordTextV[y].setCharacterSize(20);
                mapCoordTextV[y].setFont(fontA);
            }

        }
    }

    sf::RectangleShape tileSelector(sf::Vector2f(gridSizeF, gridSizeF));
    tileSelector.setFillColor(sf::Color::Transparent);
    tileSelector.setOutlineThickness(1.f);
    tileSelector.setOutlineColor(sf::Color::Green);

    auto waterColor = sf::Color{ 47 , 100, 180, 255 };

    sf::Texture texture;
    if (!texture.loadFromFile("assets/brig.png")) 
    {
        //load from file, and if it doesn't, print this message
        std::cout << "Could not load brig texture";
        return 0;
    }
    sf::Sprite brigSprite;
    brigSprite.setTexture(texture);
    brigSprite.setPosition(sf::Vector2f(100, 100));
    brigSprite.scale(sf::Vector2f(.5, .5));

    sf::RectangleShape rect;
    sf::Vector2f rectanglePosition(480, 270);

    rect.setPosition(rectanglePosition);

    rect.setSize(sf::Vector2f(100, 100));

    float xVelocity = 3;
    float yVelocity = 3;

    //Game Loop
    //while (game.running())
    while(window.isOpen())
    {
        /*
        game.update();
        game.render();
        */
        //Update dt
        dt = dtClock.restart().asSeconds();

        //Update mouse positions
        mousePosScreen = sf::Mouse::getPosition();
        mousePosWindow = sf::Mouse::getPosition(window); //relative to window
        window.setView(view); //needed to update mouse position in the view
        mousePosView = window.mapPixelToCoords(mousePosWindow);
        if(mousePosView.x >= 0.f)
            mousePosGrid.x = (mousePosView.x / gridSizeF);
        if (mousePosView.y >= 0.f)
            mousePosGrid.y = (mousePosView.y / gridSizeF);
        window.setView(window.getDefaultView());

        //Update game elements
        tileSelector.setPosition(mousePosGrid.x * gridSizeF, mousePosGrid.y * gridSizeF);
        //mousePosWindow is relative to the window
        //mousePosView is relative to the view
        //mousePosGrid gives us which grid tile we're pointing at

        

        //Update UI
        std::stringstream ss;
        ss << "Screen: " << mousePosScreen.x << " " << mousePosScreen.y << "\n"
            << "Window: " << mousePosWindow.x << " " << mousePosWindow.y << "\n"
            << "View: " << mousePosView.x << " " << mousePosView.y << "\n"
            << "Grid: " << mousePosGrid.x << " " << mousePosGrid.y << "\n";

        textA.setString(ss.str());

        //Events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close(); //if we close the window, our program won't crash

            if (event.type == sf::Event::Resized)
            {
                //sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                //window.setView(sf::View(visibleArea));
                //this doesn't do anything because we setView later; I also don't know if it even works
            }

            //
            if (event.type == sf::Event::MouseWheelScrolled)
            {
                if (event.mouseWheelScroll.delta > 0) // moving up
                {
                    //zoom in
                    viewZoom *= 0.9f;
                    view.setSize(windowSizeH* viewZoom, windowSizeV* viewZoom);
                }
                else if (event.mouseWheelScroll.delta < 0) // moving down
                {
                    //zoom out
                    viewZoom *= 1.1f;
                    view.setSize(windowSizeH* viewZoom, windowSizeV* viewZoom);
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
        }
        
        //Game Logic
        //physics/update
        rectanglePosition.x += xVelocity;
        rectanglePosition.y += yVelocity;
        rect.setPosition(rectanglePosition);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))//Left
        {
            view.move(-viewSpeed * dt, 0.f);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))//Right
        {
            view.move(viewSpeed * dt, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))//Up
        {
            view.move(0.f, -viewSpeed * dt);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))//Down
        {
            view.move(0.f, viewSpeed * dt);
        }

        //Zoom, + and - buttons
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
        {
            viewZoom *= 0.9f;
            view.setSize(windowSizeH * viewZoom, windowSizeV * viewZoom);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
        {
            viewZoom *= 1.1f;
            view.setSize(windowSizeH * viewZoom, windowSizeV * viewZoom);
        }


        //Click and Drag map
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !startDrag) 
        {
            //initialize dragging on mouse click
            mousePosPrev = sf::Mouse::getPosition(window);
            mousePosPrevF = window.mapPixelToCoords(mousePosPrev);
            mousePosCurrF = mousePosPrevF;
            viewCtrStartDrag = view.getCenter();
            //std::cout << viewCtrStartDrag.x << ", " << viewCtrStartDrag.y << std::endl;
            startDrag = true;
        } else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && startDrag)
        {
            //drag location based on mouse movement; using viewZoom gives us correct proportions, instead of a slower or faster drag based on 
            mousePosCurrF = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            view.setCenter(viewCtrStartDrag + (mousePosPrevF - mousePosCurrF) * viewZoom);
            viewCtrStartDrag = view.getCenter();
            mousePosPrevF = mousePosCurrF;
        }
        else if(!sf::Mouse::isButtonPressed(sf::Mouse::Left) && startDrag){
            //stop dragging when we've released mouse button
            startDrag = false;
        }
        



        //render
        window.clear(waterColor);
        
        //render game elements
        window.setView(view); 

        
        //draw first what you want underneath; draw last what you want on top
        //background first, then boats, then players, last is UI

        //drawing each "tile" on tileMap
        //also drawing A->Z... 1->26...

        for (int x = 0; x < mapSize; x++)
        {
            window.draw(mapCoordTextH[x]);

            for (int y = 0; y < mapSize; y++)
            {
                window.draw(tileMap[x][y]);

                mapCoordTextV[y].setString(std::to_string(y + 1));
                if (x == 0)
                    window.draw(mapCoordTextV[y]);
            }
        }

        window.draw(brigSprite);

        //window.draw(shape);
        window.draw(tileSelector);

        //render UI
        window.setView(window.getDefaultView());
        
        window.draw(textA);


        //done drawing
        window.display();
    }

    

    return 0;
}

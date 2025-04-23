#include "window.h"

//Private
void Game::makeGrid(){

    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < rows; ++j) {
            grid[i][j].setSize(sf::Vector2f(cellSize, cellSize));
            grid[i][j].setFillColor(sf::Color::Transparent);
            grid[i][j].setOutlineColor(sf::Color::White);
            grid[i][j].setOutlineThickness(1);
            grid[i][j].setPosition(sf::Vector2f(i * cellSize + (window.getSize().x / 4), j * cellSize + 10));
        }
    }
}

void Game::playerSpawn() {
    grid[12][12].setTexture(texture.getTexture(-1));
}

void Game::moveRight() {
    
}

void Game::moveLeft() {
    
}


//Public
Game::Game() {}

Game::~Game() {}

void Game::init() {
    window.create(sf::VideoMode(1920, 1080), "Pac Man | RedBlaze908");

    grid.resize(cols, std::vector<sf::RectangleShape>(rows));

    /*sf::Font font;
    if (!font.loadFromFile("../../../src/font/Tetris.ttf")) {
        std::cerr << "Error While Trying to load the font!" << std::endl;
        exit(EXIT_FAILURE);
    }

    score.setFont(font);
    score.setCharacterSize(38);
    score.setFillColor(sf::Color::White);
    score.setString("Score: 0");
    score.setPosition(sf::Vector2f(window.getSize().x / 2 + 200, 100));*/

    ImGui::SFML::Init(window);

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_::ImGuiConfigFlags_DockingEnable;

    Game::makeGrid();
    Game::playerSpawn();

    bool timerExpired = false;

    while (window.isOpen()) {
        
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
                btnClock.getElapsedTime().asSeconds() >= 0.1f) {

                btnClock.restart();
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
                btnClock.getElapsedTime().asSeconds() >= 0.1f) {

                btnClock.restart();
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
                btnClock.getElapsedTime().asSeconds() >= 0.1f) {

                btnClock.restart();
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) &&
                btnClock.getElapsedTime().asSeconds() >= 0.1f) {

                btnClock.restart();
            }
        }

        sf::Time deltaTime = deltaClock.restart();


        ImGui::SFML::Update(window, deltaTime);
        
        

        window.clear();

        /*if (!over) window.draw(score);
        else {
            score.setStyle(sf::Text::Underlined);
            window.draw(score);
        }*/

        for (int i = 0; i < cols; ++i) {
            for (int j = 0; j < rows; ++j) {
                window.draw(grid[i][j]);
            }
        }
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}



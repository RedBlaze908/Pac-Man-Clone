#include "window.h"

//Private
void Game::makeGrid(){

    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < rows; ++j) {
            grid[i][j].t.setSize(sf::Vector2f(cellSize, cellSize));
            grid[i][j].t.setOutlineColor(sf::Color::Black);
            grid[i][j].t.setOutlineThickness(1);
            grid[i][j].t.setPosition(sf::Vector2f(i * cellSize + (window.getSize().x / 4), j * cellSize + 10));
            grid[i][j].val = 0;
        }
    }
}

void Game::playerSpawn() {
    sf::Texture* player = texture.getTexture(-1);
    if (!player) {
        std::cout << "Error While Trying To Open The Player Texture!" << std::endl;
        exit(EXIT_FAILURE);
    }
    grid[12][12].t.setTexture(player);
    grid[12][12].val = -1;
}

void Game::moveRight() {
    if (grid[playerPos.x + 1][playerPos.y].val == 0) {
        grid[playerPos.x][playerPos.y].t.setTexture(NULL);
        grid[playerPos.x][playerPos.y].val = 0;
        grid[playerPos.x + 1][playerPos.y].t.setTexture(texture.getTexture(-1));
        grid[playerPos.x + 1][playerPos.y].val = -1;
        playerPos.x++;
    }
}

void Game::moveLeft() {
    if (grid[playerPos.x - 1][playerPos.y].val == 0) {
        grid[playerPos.x][playerPos.y].t.setTexture(NULL);
        grid[playerPos.x][playerPos.y].val = 0;
        grid[playerPos.x - 1][playerPos.y].t.setTexture(texture.getTexture(-1));
        grid[playerPos.x - 1][playerPos.y].val = -1;
        playerPos.x--;
    }
}

void Game::moveUp() {
    if (grid[playerPos.x][playerPos.y - 1].val == 0) {
        grid[playerPos.x][playerPos.y].t.setTexture(NULL);
        grid[playerPos.x][playerPos.y].val = 0;
        grid[playerPos.x][playerPos.y - 1].t.setTexture(texture.getTexture(-1));
        grid[playerPos.x][playerPos.y - 1].val = -1;
        playerPos.y--;
    }
}

void Game::moveDown() {
    if (grid[playerPos.x][playerPos.y + 1].val == 0) {
        grid[playerPos.x][playerPos.y].t.setTexture(NULL);
        grid[playerPos.x][playerPos.y].val = 0;
        grid[playerPos.x][playerPos.y + 1].t.setTexture(texture.getTexture(-1));
        grid[playerPos.x][playerPos.y + 1].val = -1;
        playerPos.y++;
    }
}


//Public
Game::Game() {}

Game::~Game() {}

void Game::init() {
    window.create(sf::VideoMode(1920, 1080), "Pac Man | RedBlaze908");

    grid.resize(cols, std::vector<tile>(rows));

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

                Game::moveLeft();
                btnClock.restart();
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
                btnClock.getElapsedTime().asSeconds() >= 0.1f) {

                Game::moveRight();
                btnClock.restart();
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
                btnClock.getElapsedTime().asSeconds() >= 0.1f) {

                Game::moveDown();
                btnClock.restart();
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
                btnClock.getElapsedTime().asSeconds() >= 0.1f) {

                Game::moveUp();
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
                window.draw(grid[i][j].t);
            }
        }
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}



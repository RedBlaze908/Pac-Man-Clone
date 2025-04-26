#include "window.h"

//Private
void Game::makeGrid(){
    std::ifstream file("../../../src/window/map.txt");
    if (!file.is_open()) {
        std::cerr << "Error: Map not found!" << std::endl;
        exit(EXIT_FAILURE);
    }

    int val;
    std::string line;
    for (int i = 0; i < cols; ++i) {
        std::getline(file, line);
        std::istringstream ss(line);

        for (int j = 0; j < rows; ++j) {
            ss >> val;
            grid[j][i].val = val;
            sf::Texture* Texture_ = texture.getTexture(static_cast<int8_t>(val));
            if (!Texture_ && val != 0) {
                std::cerr << "Error: Texture Not Found!" << std::endl;
                exit(EXIT_FAILURE);
            }

            grid[j][i].t.setSize(sf::Vector2f(cellSize, cellSize));
            grid[j][i].t.setOutlineColor(sf::Color::Black);
            grid[j][i].t.setOutlineThickness(1);
            grid[j][i].t.setPosition(sf::Vector2f(j * cellSize + (window.getSize().x / 4), i * cellSize + 10));
            grid[j][i].t.setTexture(Texture_);
        }
    }
}

void Game::playerSpawn() {
    sf::Texture* player = texture.getTexture(static_cast<int8_t>(-1));
    if (!player) {
        std::cerr << "Error While Trying To Open The Player Texture!" << std::endl;
        exit(EXIT_FAILURE);
    }
    grid[12][12].t.setTexture(player);
    grid[12][12].val = -1;
}

void Game::moveRight() {
    //std::cout << grid[playerPos.x + 1][playerPos.y].val << std::endl;
    if ((playerPos.x + 1) < 25 && grid[playerPos.x + 1][playerPos.y].val == 0) {
        sf::Texture* Texture_ = texture.getTexture(static_cast<int8_t>(0));
        grid[playerPos.x][playerPos.y].t.setTexture(Texture_);
        grid[playerPos.x][playerPos.y].val = 0;
        grid[playerPos.x + 1][playerPos.y].t.setTexture(texture.getTexture(static_cast<int8_t>(-1)));
        grid[playerPos.x + 1][playerPos.y].val = -1;
        playerPos.x++;
    }
}

void Game::moveLeft() {
    if ((playerPos.x + 1) < 24 && grid[playerPos.x - 1][playerPos.y].val == 0) {
        sf::Texture* Texture_ = texture.getTexture(static_cast<int8_t>(0));
        grid[playerPos.x][playerPos.y].t.setTexture(Texture_);
        grid[playerPos.x][playerPos.y].val = 0;
        grid[playerPos.x - 1][playerPos.y].t.setTexture(texture.getTexture(static_cast<int8_t>(-1)));
        grid[playerPos.x - 1][playerPos.y].val = -1;
        playerPos.x--;
    }
}

void Game::moveUp() {
    if ((playerPos.x + 1) < 24 && grid[playerPos.x][playerPos.y - 1].val == 0) {
        sf::Texture* Texture_ = texture.getTexture(static_cast<int8_t>(0));
        grid[playerPos.x][playerPos.y].t.setTexture(Texture_);
        grid[playerPos.x][playerPos.y].val = 0;
        grid[playerPos.x][playerPos.y - 1].t.setTexture(texture.getTexture(static_cast<int8_t>(-1)));
        grid[playerPos.x][playerPos.y - 1].val = -1;
        playerPos.y--;
    }
}

void Game::moveDown() {
    if ((playerPos.x + 1) < 24 && grid[playerPos.x][playerPos.y + 1].val == 0) {
        sf::Texture* Texture_ = texture.getTexture(static_cast<int8_t>(0));
        grid[playerPos.x][playerPos.y].t.setTexture(Texture_);
        grid[playerPos.x][playerPos.y].val = 0;
        grid[playerPos.x][playerPos.y + 1].t.setTexture(texture.getTexture(static_cast<int8_t>(-1)));
        grid[playerPos.x][playerPos.y + 1].val = -1;
        playerPos.y++;
    }
}


//Public
Game::Game() : ptrFunc([](){}) {}

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
                btnClock.getElapsedTime().asSeconds() >= 0.2f) {

                Game::moveLeft();
                ptrFunc = std::bind(&Game::moveLeft, this);
                timerExpired = true;
                btnClock.restart();
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
                btnClock.getElapsedTime().asSeconds() >= 0.2f) {

                Game::moveRight();
                ptrFunc = std::bind(&Game::moveRight, this);
                timerExpired = true;
                btnClock.restart();
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
                btnClock.getElapsedTime().asSeconds() >= 0.2f) {

                Game::moveDown();
                ptrFunc = std::bind(&Game::moveDown, this);
                timerExpired = true;
                btnClock.restart();
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
                btnClock.getElapsedTime().asSeconds() >= 0.2f) {

                Game::moveUp();
                ptrFunc = std::bind(&Game::moveUp, this);
                timerExpired = true;
                btnClock.restart();
            }
        }

        sf::Time deltaTime = deltaClock.restart();
        

        ImGui::SFML::Update(window, deltaTime);
        
        if (!timerExpired && clock.getElapsedTime().asSeconds() >= 0.2f &&
            playerPos.x < 24 && playerPos.x > 0 && playerPos.y < 24 && playerPos.y > 0) {
            ptrFunc();
            clock.restart();
        }
        else timerExpired = false;

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



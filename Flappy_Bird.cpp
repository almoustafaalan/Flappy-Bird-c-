#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

struct Pipe {
    sf::RectangleShape top, bottom;
    float x;
    Pipe(float startX, float gapY) {
        float pipeWidth = 80;
        float gapHeight = 200;

        top.setSize(sf::Vector2f(pipeWidth, gapY));
        top.setFillColor(sf::Color::Green);
        top.setPosition(startX, 0);

        bottom.setSize(sf::Vector2f(pipeWidth, WINDOW_HEIGHT - (gapY + gapHeight)));
        bottom.setFillColor(sf::Color::Green);
        bottom.setPosition(startX, gapY + gapHeight);

        x = startX;
    }

    void move(float dx) {
        x += dx;
        top.setPosition(x, 0);
        bottom.setPosition(x, bottom.getPosition().y);
    }
};

int main() {
    srand(time(0));
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Flappy Bird (SFML)");
    window.setFramerateLimit(60);

    // Bird
    sf::CircleShape bird(20);
    bird.setFillColor(sf::Color::Yellow);
    float birdY = WINDOW_HEIGHT / 2;
    float velocity = 0;
    const float gravity = 0.5;
    const float jumpStrength = -8;

    // Pipes
    std::vector<Pipe> pipes;
    float pipeSpawnTimer = 0;
    const float pipeSpacing = 200;

    // Score
    int score = 0;
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return -1; // make sure arial.ttf is in project folder
    }
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::White);

    bool gameOver = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (!gameOver && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                velocity = jumpStrength;
            }
            if (gameOver && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                // Reset game
                birdY = WINDOW_HEIGHT / 2;
                velocity = 0;
                pipes.clear();
                score = 0;
                gameOver = false;
            }
        }

        if (!gameOver) {
            // Bird physics
            velocity += gravity;
            birdY += velocity;
            bird.setPosition(WINDOW_WIDTH / 4, birdY);

            // Spawn pipes
            pipeSpawnTimer += 1;
            if (pipeSpawnTimer > pipeSpacing) {
                float gapY = rand() % (WINDOW_HEIGHT - 250) + 50;
                pipes.push_back(Pipe(WINDOW_WIDTH, gapY));
                pipeSpawnTimer = 0;
            }

            // Move pipes & check collisions
            for (auto &pipe : pipes) {
                pipe.move(-4);
                if (bird.getGlobalBounds().intersects(pipe.top.getGlobalBounds()) ||
                    bird.getGlobalBounds().intersects(pipe.bottom.getGlobalBounds())) {
                    gameOver = true;
                }
                if (pipe.x + 80 < WINDOW_WIDTH / 4 && !gameOver) {
                    score++;
                }
            }

            // Out of bounds check
            if (birdY < 0 || birdY > WINDOW_HEIGHT) {
                gameOver = true;
            }
        }

        // Draw
        window.clear(sf::Color::Cyan);
        window.draw(bird);
        for (auto &pipe : pipes) {
            window.draw(pipe.top);
            window.draw(pipe.bottom);
        }

        scoreText.setString("Score: " + std::to_string(score));
        window.draw(scoreText);

        if (gameOver) {
            sf::Text overText;
            overText.setFont(font);
            overText.setString("GAME OVER\nPress Enter to Restart");
            overText.setCharacterSize(40);
            overText.setFillColor(sf::Color::Red);
            overText.setPosition(200, 250);
            window.draw(overText);
        }

        window.display();
    }

    return 0;
}

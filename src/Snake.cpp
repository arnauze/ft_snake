# include "../header/Snake.hpp"

Snake::Snake(void) { return ; }
Snake::~Snake(void) { return ; }
Snake::Snake(Snake const & snake) { *this = snake; return; }
Snake                   &Snake::operator=(Snake const & snake) { return *this; }

Snake::Snake(int width, int height) : win_width(width), win_height(height) {
    std::vector<Position*> *snake = new std::vector<Position*>;
    snake->insert(snake->begin(), new Position(width / 2, height / 2));
    this->snake = snake;
}

std::vector<Position*>           *Snake::getSnake(void) const {
    return this->snake;
}
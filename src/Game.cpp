# include "../header/Game.hpp"

Game::Game(void) : direction(1), alive(true), timer(0), score(0) {
    srand(time(NULL));
    return ;
}

Game::~Game(void) { return ; }

Game::Game(Game const & game) { 
    *this = game;
    return ;
}

Game                &Game::operator=(Game const & game) {
    return *this;
}

void                Game::init(void) {
    initscr();
    srand(0);
    this->snake = new Snake(getmaxx(stdscr), getmaxy(stdscr));
    this->minX = getmaxx(stdscr) / 2 - 100;
    this->minY = getmaxy(stdscr) / 2 - 25;
    this->maxX = getmaxx(stdscr) / 2 + 100;
    this->maxY = getmaxy(stdscr) / 2 + 25;
    this->food = new Position(rand() % getmaxx(stdscr), rand() % getmaxy(stdscr));
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    start_color();
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
}

void                Game::printBackground(void) {
    int height = this->snake->win_height;
    int width = this->snake->win_width;
    int middle_w = width / 2;
    int middle_h = height /2;

    int     i = -1;
    while (++i < 50)
        mvaddch(this->minY + i, this->minX, '*');
    i = -1;
    while (++i < 50)
        mvaddch(this->minY + i, this->maxX, '*');
    i = -1;
    while (++i < 200)
        mvaddch(this->minY, this->minX + i, '*');
    i = -1;
    while (++i < 200)
        mvaddch(this->maxY, this->minX + i, '*');

    mvaddstr(this->minY - 4, middle_w, "Score: 0");
    mvaddstr(this->minY - 2, middle_w, "Time: 0");
}

void                Game::printObjects(void) const {
    attron(COLOR_PAIR(1));
    for (int i = 0; i < this->snake->getSnake()->size(); i++) {
        std::vector<Position*> *snake = this->snake->getSnake();
        int x = (*snake)[i]->getX();
        int y = (*snake)[i]->getY();
        mvaddch(y, x, 'S');
    }
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(2));
    mvaddch(this->food->getY(), this->food->getX(), 'O');
    attroff(COLOR_PAIR(2));
}

void                Game::moveSnake(void) {
    int x = 0;
    int y = 0;
    if (this->direction == 1) 
        x = 2;
    else if (this->direction == 2)
        y = 1;
    else if (this->direction == 3)
        x = -2;
    else if (this->direction == 4)
        y = -1;

    Position        *head = this->snake->getSnake()->back();
    int x2 = head->getX() + x;
    int y2 = head->getY() + y;
    if ((x2 == this->maxX || x2 == this->minX) || (y2 == this->maxY || y2 == this->minY))
        this->alive = false;
    this->snake->getSnake()->insert(this->snake->getSnake()->end(), new Position(x2, y2));
    if ((x2 == this->food->getX() || x2 - 1 == this->food->getX()) && y2 == this->food->getY()) {
        delete this->food;
        this->score += 1;
        this->food = new Position((rand() % 200) + this->minX, rand() % 50 + this->minY);
    } else
        this->snake->getSnake()->erase(this->snake->getSnake()->begin());
    this->selfCollision(x2, y2);
}

void                Game::selfCollision(int x, int y) {
    std::vector<Position*>  *snake = this->snake->getSnake();
    for (int i = 0; i < snake->size() - 1; i++) {
        if ((x == (*snake)[i]->getX()) && (y == (*snake)[i]->getY()))
            this->alive = false;
    }
}

void                Game::gameLoop(void) {
    int tick = -1;
    mvaddstr(this->snake->win_height / 2, this->snake->win_width / 2 - 11, "Press any key to start!");
    getch();
    nodelay(stdscr, TRUE);
    clear();
    while (this->alive) {
        ++tick;
        this->printBackground();
        this->printObjects();
        char c = getch();
        if (c == 'q')
            break;
        else if (c == 'w' && this->direction != 2)
            this->direction = 4;
        else if (c == 'd'  && this->direction != 3)
            this->direction = 1;
        else if (c == 's'  && this->direction != 4)
            this->direction = 2;
        else if (c == 'a'  && this->direction != 1)
            this->direction = 3;
        
        this->moveSnake();
        usleep(50000);
        clear();
        refresh();
    }
    endwin();
}

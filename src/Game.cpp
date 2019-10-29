# include "../header/Game.hpp"

Game::Game(void) { return ; }

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
    this->food = new Position(rand() % getmaxx(stdscr), rand() % getmaxy(stdscr));
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    start_color();
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
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

void                Game::moveSnake(int direction) {
    int x = 0;
    int y = 0;
    if (direction == 1) 
        x = 2;
    else if (direction == 2)
        y = 1;
    else if (direction == 3)
        x = -2;
    else if (direction == 4)
        y = -1;

    Position        *head = this->snake->getSnake()->back();
    int x2 = head->getX() + x;
    int y2 = head->getY() + y;
    this->snake->getSnake()->insert(this->snake->getSnake()->end(), new Position(x2, y2));
    if ((x2 == this->food->getX() || x2 - 1 == this->food->getX()) && (y2 == this->food->getY() || y2 - 1 == this->food->getY())) {
        srand(time(NULL));
        delete this->food;
        this->food = new Position(rand() % getmaxx(stdscr), rand() % getmaxy(stdscr));
    } else
        this->snake->getSnake()->erase(this->snake->getSnake()->begin());
}

void                Game::gameLoop(void) {
    int tick = -1;
    int direction = 1;
    mvaddstr(this->snake->win_height / 2, this->snake->win_width / 2 - 11, "Press any key to start!");
    getch();
    nodelay(stdscr, TRUE);
    clear();
    while (1) {
        ++tick;
        this->printObjects();
        char c = getch();
        if (c == 'q')
            break;
        else if (c == 'w' && direction != 2)
            direction = 4;
        else if (c == 'd'  && direction != 3)
            direction = 1;
        else if (c == 's'  && direction != 4)
            direction = 2;
        else if (c == 'a'  && direction != 1)
            direction = 3;
        
        this->moveSnake(direction);
        usleep(50000);
        clear();
        refresh();
    }
    endwin();
}
#ifndef GAME_HPP
# define GAME_HPP

# include <string>
# include <iostream>
# include <curses.h>
# include <time.h>
# include <unistd.h>

# include "../header/Snake.hpp"

class           Game {

    public:
        Game(void);
        ~Game(void);
        Game(Game const & game);
        Game    &operator=(Game const & target);

        void    init(void);
        void    gameLoop(void);
        void    printObjects(void) const;
        void    moveSnake(void);
        void    selfCollision(int x, int y);
        void    printBackground(void);

    private:
        Snake   *snake;
        Position    *food;
        bool        alive;
        int         direction;
        int         maxX;
        int         maxY;
        int         minX;
        int         minY;
        int         score;
        int         timer;
};

#endif
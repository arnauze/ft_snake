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
        void    moveSnake(int direction);

    private:
        Snake   *snake;
        Position    *food;
};

#endif
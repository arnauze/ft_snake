#ifndef SNAKE_HPP
# define SNAKE_HPP

# include "Position.hpp"
# include <vector>

class               Snake {
    public:
        Snake(void);
        Snake(int width, int height);
        ~Snake(void);
        Snake(Snake const & snake);
        Snake       &operator=(Snake const & snake);

        std::vector<Position*> *getSnake(void) const;

        int                         win_width;
        int                         win_height;

    private:
        std::vector<Position*>       *snake;

};


#endif
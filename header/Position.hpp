#ifndef POSITION_HPP
# define POSITION_HPP

class                   Position {
    public:
        Position(void);
        Position(int x, int y);
        ~Position(void);
        Position(Position const & position);
        Position &operator=(Position const & position);

        void            setX(int x);
        void            setY(int y);
        int             getX(void) const;
        int             getY(void) const;

    private:
        int             x;
        int             y;
};

#endif
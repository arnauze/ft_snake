# include "../header/Position.hpp"

Position::Position(void) { return ; }
Position::Position(int x, int y) : x(x), y(y) { return ; }
Position::~Position(void) { return ; }

Position::Position(Position const & position) {
    *this = position;
    return ;
}

Position                &Position::operator=(Position const & position) {
    return *this;
}

void                    Position::setX(int x) {
    this->x = x;
}

void                    Position::setY(int y) {
    this->y = y;
}

int                     Position::getX(void) const {
    return this->x;
}

int                     Position::getY(void) const {
    return this->y;
}
#ifndef DEPLACEMENT_H
#define DEPLACEMENT_H

#include <iostream>
#include <vector>

class Deplacement {
public:

    //Constr
    Deplacement(int first = 0, int second = 0, int scr = 0);

    void montreToi() {
        std::cout << i << "  " << j << "  " << m_points << std::endl;
    }

    //getset methodes
    int getX() { return i; }
    int getY() { return j; }
    int getScore() { return m_points; }
    void setX(int allo) { i = allo; }
    void setY(int allo) { j = allo; }
    void setScore(int allo) { m_points = allo; }

private:
    int i;
    int j;
    int m_points;
};
#endif // DEPLACEMENT_H
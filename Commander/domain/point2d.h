#ifndef POINT2D_H
#define POINT2D_H

class Point2D
{
public:
    Point2D();

    float x(){return m_x;}
    float y(){return m_y;}

    void setX(float value){m_x = value;}
    void setY(float value){m_y = value;}

private:
    float m_x, m_y;
};

#endif // POINT2D_H

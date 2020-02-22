#ifndef GLCAMERA_H
#define GLCAMERA_H

#include <GL/glu.h>
#include <cmath>

class GLCamera
{
public:
    GLCamera();

    void look_at() const;
    void move_to(float x,float y,float z);
    void move_forward(int speed);
    void move_backward(int speed);
    void move_left(int speed);
    void move_right(int speed);
    void translate(float x,float y,float z);
    void set_perspective(int width,int height)const;
    void update(float px,float py,float pz,
                float rx,float ry,float rz);

    void turn_left(float fValue);
    void turn_right(float fValue);
    void turn_up(float fValue);
    void turn_down(float fValue);

private:
    void turn_to(float x,float y,float z);

    GLdouble eyeX;
    GLdouble eyeY;
    GLdouble eyeZ;

    GLdouble centerX;
    GLdouble centerY;
    GLdouble centerZ;

    GLdouble upX;
    GLdouble upY;
    GLdouble upZ;

    GLdouble dAngle_LR;
    GLdouble dAngle_UD;
};

#endif // GLCAMERA_H

#include "glcamera.h"
#include <iostream>

GLCamera::GLCamera()
    :eyeX(0.0),eyeY(0.0),eyeZ(0.0),centerX(0.0),centerY(0.0)
    ,centerZ(0.0),upX(0.0),upY(1.0),upZ(0.0),dAngle_LR(M_PI/2)
    ,dAngle_UD(M_PI/2)
{

}

void GLCamera::look_at() const
{
    gluLookAt(eyeX, eyeY, eyeZ
              , centerX, centerY, centerZ
              , upX, upY, upZ);
}

void GLCamera::move_to(float x, float y, float z)
{
    eyeX = x;
    eyeY = y;
    eyeZ = z;
}

void GLCamera::move_forward(int speed)
{
    eyeZ += speed;
}

void GLCamera::move_backward(int speed)
{
    eyeZ -= speed;
}

void GLCamera::move_left(int speed)
{
    eyeX -= speed;
}

void GLCamera::move_right(int speed)
{
    eyeX += speed;
}

void GLCamera::translate(float x, float y, float z)
{
    eyeX += x;
    eyeY += y;
    eyeZ += z;

    centerX += x;
    centerY += y;
    centerZ += z;
}

void GLCamera::set_perspective(int width, int height) const
{
    gluPerspective(70,(GLdouble)width/height,1,1000);
}

void GLCamera::update(float px, float py, float pz, float rx
                      , float ry, float rz)
{
    eyeX = px;
    eyeY = py;
    eyeZ = pz;

    centerX = rx;
    centerY = ry;
    centerZ = rz;
}

void GLCamera::turn_left(float fValue)
{
    dAngle_LR -= fValue;

    centerX = eyeX + cos(dAngle_LR);
    centerZ = eyeZ - sin(dAngle_LR);
}

void GLCamera::turn_right(float fValue)
{
    dAngle_LR += fValue;

    centerX = eyeX + cos(dAngle_LR);
    centerZ = eyeZ - sin(dAngle_LR);
}

void GLCamera::turn_up(float fValue)
{
    dAngle_UD += fValue;

    centerY = eyeY + cos(dAngle_UD);
    centerZ = eyeZ - sin(dAngle_UD);
}

void GLCamera::turn_down(float fValue)
{
    dAngle_UD -= fValue;

    centerY = eyeY + cos(dAngle_UD);
    centerZ = eyeZ - sin(dAngle_UD);
}

void GLCamera::turn_to(float x, float y, float z)
{
}

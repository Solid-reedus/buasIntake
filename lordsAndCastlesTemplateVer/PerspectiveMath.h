#ifndef PERSPECTIVE_MATH
#define PERSPECTIVE_MATH

#include "baseHeader.h"

void IsometricToCartesian(int p_isoX, int p_isoY, int p_tileWidth, int p_tileHeight,
    int& p_cartX, int& p_cartY, float p_relativeWidth, float p_relativeHeight);

void CartesianToIsometric(int p_x, int p_y, int p_w, int p_h, int& p_isoX, int& p_isoY,
    float p_relativeWidth, float p_relativeHeight);

void StaticIsometricToCartesian(int p_isoX, int p_isoY, int p_tileWidth, int p_tileHeight,
    int& p_cartX, int& p_cartY);

void StaticCartesianToIsometric(int x, int y, int w, int h, int& isoX, int& isoY);

void FloatCartesianToIsometric(float p_x, float p_y, float p_w, float p_h, float& p_isoX, float& p_isoY,
    float p_relativeWidth, float p_relativeHeight);

#endif
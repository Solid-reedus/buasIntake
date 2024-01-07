#ifndef PERSPECTIVE_MATH
#define PERSPECTIVE_MATH

#include "baseHeader.h"

/*
    cartesian & isometric shortly explained

    cartesian is on a traditional grid like a chessboard and/or old zelda games
    going +1 on the y equals going +1 up on the y and on the x axis the same.

    isometric is a way to fake 3d by having the tiles as a 45 degree square and making the width
    double of the height. +1 on a isometric grid looks more like going on the y 0.5+ and 
    on the x 1.5+. please see games like stronghold, age of empires 2 and diablo 2

    see here a more detailed explanation
    https://gamedev.stackexchange.com/questions/142784/how-do-you-transform-a-coordinate-system-from-cartesian-to-isometric
*/

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
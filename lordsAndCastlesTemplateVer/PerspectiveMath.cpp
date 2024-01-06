#include "PerspectiveMath.h"

void IsometricToCartesian(int p_isoX, int p_isoY, int p_tileWidth, int p_tileHeight,
	int& p_cartX, int& p_cartY, float p_relativeWidth, float p_relativeHeight)
{
	p_isoX -= (p_relativeWidth + (p_tileWidth / 2));
	p_isoY -= (p_relativeHeight + (p_tileHeight / 2));

	double isoXf = static_cast<double>(p_isoX);
	double isoYf = static_cast<double>(p_isoY);
	double tileWidthf = static_cast<double>(p_tileWidth);
	double tileHeightf = static_cast<double>(p_tileHeight);

	double cartXf = (isoXf / (tileWidthf / 2.0) + isoYf / (tileHeightf / 2.0)) / 2.0;
	double cartYf = (isoYf / (tileHeightf / 2.0) - isoXf / (tileWidthf / 2.0)) / 2.0;

	p_cartX = (cartXf >= 0.0) ? std::round(cartXf) : -std::round(-cartXf);
	p_cartY = (cartYf >= 0.0) ? std::round(cartYf) : -std::round(-cartYf);

}

void StaticIsometricToCartesian(int p_isoX, int p_isoY, int p_tileWidth, int p_tileHeight,
	int& p_cartX, int& p_cartY)
{
	double isoXf = static_cast<double>(p_isoX);
	double isoYf = static_cast<double>(p_isoY);
	double tileWidthf = static_cast<double>(p_tileWidth);
	double tileHeightf = static_cast<double>(p_tileHeight);

	double cartXf = (isoXf / (tileWidthf / 2.0) + isoYf / (tileHeightf / 2.0)) / 2.0;
	double cartYf = (isoYf / (tileHeightf / 2.0) - isoXf / (tileWidthf / 2.0)) / 2.0;

	p_cartX = static_cast<int>((cartXf >= 0.0) ? std::round(cartXf) : -std::round(-cartXf));
	p_cartY = static_cast<int>((cartYf >= 0.0) ? std::round(cartYf) : -std::round(-cartYf));
}


void CartesianToIsometric(int p_x, int p_y, int p_w, int p_h, int& p_isoX, int& p_isoY,
	float p_relativeWidth, float p_relativeHeight)
{
	p_isoX = ((p_x - p_y) * p_w / 2) + p_relativeWidth;
	p_isoY = ((p_x + p_y) * p_h / 2) + p_relativeHeight;
}

void StaticCartesianToIsometric(int x, int y, int w, int h, int& isoX, int& isoY)
{
	isoX = ((x - y) * w / 2);
	isoY = ((x + y) * h / 2);
}

void FloatCartesianToIsometric(float p_x, float p_y, float p_w, float p_h, float& p_isoX, float& p_isoY,
	float p_relativeWidth, float p_relativeHeight)
{
	p_isoX = ((p_x - p_y) * p_w / 2.0f) + p_relativeWidth;
	p_isoY = ((p_x + p_y) * p_h / 2.0f) + p_relativeHeight;
}

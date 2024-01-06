#ifndef RECT
#define RECT

struct Rect
{
	public:
	int x;
	int y;
	int w;
	int h;
	bool IsInside(int p_x, int p_y) const
	{
		return (p_x > x && p_x < x + w && p_y > y && p_y < y + h);
	}

};

struct RectFloat
{
	public:
	float x;
	float y;
	float w;
	float h;
	bool IsInside(float p_x, float p_y) const
	{
		return (p_x > x && p_x < x + w && p_y > y && p_y < y + h);
	}
};

#endif


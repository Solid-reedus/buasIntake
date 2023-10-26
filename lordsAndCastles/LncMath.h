#ifndef LNC_MATH
#define LNC_MATH

class vector2
{
    public:
    float x;
    float y;
    vector2() : x(0), y(0) {}
    vector2(float x, float y) : x(x), y(y) {}

    vector2 operator+(const vector2& other) const
    {
        return vector2(x + other.x, y + other.y);
    }

    vector2 operator-(const vector2& other) const
    {
        return vector2(x - other.x, y - other.y);
    }

    vector2 operator*(const vector2& other) const
    {
        return vector2(x * other.x, y * other.y);
    }

    vector2 operator*(float scalar) const
    {
        return vector2(x * scalar, y * scalar);
    }

    vector2& operator+=(const vector2& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    bool operator==(const vector2& other) const
    {
        return (x == other.x) && (y == other.y);
    }

};

class vector2Int
{
    public:
    int x;
    int y;
    vector2Int() : x(0), y(0) {}
    vector2Int(int x, int y) : x(x), y(y) {}

    vector2Int operator+(const vector2Int& other) const
    {
        return vector2Int(x + other.x, y + other.y);
    }

    // Overload equality operator
    bool operator==(const vector2Int& other) const
    {
        return (x == other.x) && (y == other.y);
    }

    bool operator<(const vector2Int& other) const {
        if (x < other.x) return true;
        if (x > other.x) return false;
        return y < other.y;
    }

};



#endif



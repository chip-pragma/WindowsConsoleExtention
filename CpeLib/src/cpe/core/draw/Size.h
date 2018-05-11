#pragma once


namespace cpe {

class Point;

class Size {
public:
    Size();

    Size(uint32_t x, uint32_t y);

    uint32_t width() const;

    void width(uint32_t w);

    uint32_t height() const;

    void height(uint32_t h);

    Point to_point() const;

    std::string to_string() const;

    Size &operator+=(const Size &p1);

    Size operator+(const Size &p1) const;

    Size &operator-=(const Size &p1);

    Size operator-(const Size &p1) const;

    Size &operator*=(uint32_t k);

    Size operator*(uint32_t k) const;

    Size &operator/=(uint32_t k);

    Size operator/(uint32_t k) const;

    bool operator==(const Size &size) const;

    bool operator!=(const Size &size) const;

protected:
    uint32_t mWidth;
    uint32_t mHeight;
};

}


#ifndef COORDINATE_H
#define COORDINATE_H

#include <climits>
#include <ostream>
#include <exception>
#include <cmath>


typedef std::exception NullPtrException;

inline bool equal(const double a, const double b)
{
	#define EPS 1e-9
	return fabs(a-b)<EPS ? true : false;
}

template <typename coor_t>
class Coor
{
private:
	coor_t x, y;

public:
	static const int INF = INT_MAX;
	static const int NINF = INT_MIN;

	explicit Coor(coor_t a=0, coor_t b=0) : x(a), y(b) {}
	Coor(const Coor<coor_t>& rhs) : x(rhs.x), y(rhs.y) {}
	virtual ~Coor() {}

	// setter
	void set(coor_t a=0, coor_t b=0) { x = a, y = b; }
	void setX(coor_t new_x) { x = new_x; }
	void setY(coor_t new_y) { y = new_y; }
	// getter
	coor_t getX() const { return x; }
	coor_t getY() const { return y; }
	// add value
	void addToX(coor_t value) { x += value; }
	void addToY(coor_t value) { y += value; }

	Coor& operator-= (const Coor<coor_t>& right)
	{
		this->x -= right.x;
		this->y -= right.y;
		return *this;
	}

	Coor& operator+= (const Coor<coor_t>& right)
	{
		this->x += right.x;
		this->y += right.y;
		return *this;
	}

	Coor& operator+= (const coor_t& value)
	{
		this->x += value;
		this->y += value;
		return *this;
	}

	Coor& operator-= (const coor_t& value)
	{
		this->x -= value;
		this->y -= value;
		return *this;
	}
};


/** operator overloading for Coor **/
template <typename coor_t>
inline Coor<coor_t> operator- (const Coor<coor_t>& lhs, const Coor<coor_t>& rhs)
{
	Coor<coor_t> temp(lhs);
	temp -= rhs;
	return temp;
}


template <typename coor_t>
inline Coor<coor_t> operator+ (const Coor<coor_t>& lhs, const Coor<coor_t>& rhs)
{
	Coor<coor_t> temp(lhs);
	temp += rhs;
	return temp;
}


template <typename coor_t>
inline Coor<coor_t> operator- (Coor<coor_t>&& lhs, const Coor<coor_t>& rhs)
{
	lhs -= rhs;
	return lhs;
}


template <typename coor_t>
inline Coor<coor_t> operator+ (Coor<coor_t>&& lhs, const Coor<coor_t>& rhs)
{
	lhs += rhs;
	return lhs;
}


template <typename coor_t>
inline Coor<coor_t> operator- (const Coor<coor_t>& lhs, const coor_t& val)
{
	Coor<coor_t> temp(lhs);
	temp -= val;
	return temp;
}


template <typename coor_t>
inline Coor<coor_t> operator+ (const Coor<coor_t>& lhs, const coor_t& val)
{
	Coor<coor_t> temp(lhs);
	temp += val;
	return temp;
}


template <typename coor_t>
inline Coor<coor_t> operator- (Coor<coor_t>&& lhs, const coor_t& rhs)
{
	lhs -= rhs;
	return lhs;
}


template <typename coor_t>
inline Coor<coor_t> operator+ (Coor<coor_t>&& lhs, const coor_t& rhs)
{
	lhs += rhs;
	return lhs;
}


template <typename coor_t>
inline bool operator< (const Coor<coor_t>& lhs, const Coor<coor_t>& rhs)
{
    return ((lhs.getX() < rhs.getX()) && (lhs.getY() < rhs.getY()));
}


template <typename coor_t>
inline bool operator> (const Coor<coor_t>& lhs, const Coor<coor_t>& rhs)
{
    return ((lhs.getX() > rhs.getX()) && (lhs.getY() > rhs.getY()));
}


template <typename coor_t>
inline bool operator== (const Coor<coor_t>& lhs, const Coor<coor_t>& rhs)
{
	if(lhs.getX() != rhs.getX()) { return false; }
	if(lhs.getY() != rhs.getY()) { return false; }
	return true;
}


template <typename coor_t>
inline bool operator!= (const Coor<coor_t>& lhs, const Coor<coor_t>& rhs)
{
	if(lhs == rhs) return false;
	return true;
}


/** specialization version of overloaded operators of Coor **/
template <>
inline bool operator< (const Coor<double>& lhs, const Coor<double>& rhs)
{
    if (equal(lhs.getX(), rhs.getX())) { return (lhs.getX() < rhs.getX()); }
    if (equal(lhs.getY(), rhs.getY())) { return (lhs.getY() < rhs.getY()); }
    return ((lhs.getX() < rhs.getX()) && (lhs.getY() < rhs.getY()));
}


/** specialization version of overloaded operators of Coor **/
template <>
inline bool operator> (const Coor<double>& lhs, const Coor<double>& rhs)
{
    if (equal(lhs.getX(), rhs.getX())) { return (lhs.getX() > rhs.getX()); }
    if (equal(lhs.getY(), rhs.getY())) { return (lhs.getY() > rhs.getY()); }
    return ((lhs.getX() > rhs.getX()) && (lhs.getY() > rhs.getY()));
}


template <>
inline bool operator== (const Coor<double>& lhs, const Coor<double>& rhs)
{
	if(!equal(lhs.getX(), rhs.getX())) { return false; }
	if(!equal(lhs.getY(), rhs.getY())) { return false; }
	return true;
}


/** overload stream operator for Coor **/
template <typename coor_t>
std::ostream& operator<< (std::ostream &out, const Coor<coor_t> &coor)
{
	out << '(';
	if(coor.getX() == Coor<coor_t>::INF) out << "inf";
	else if(coor.getX() == Coor<coor_t>::NINF) out << "-inf";
	else out << coor.getX();
	out << ", ";
	if(coor.getY() == Coor<coor_t>::INF) out << "inf";
	else if(coor.getY() == Coor<coor_t>::NINF) out << "-inf";
	else out << coor.getY();
	out << ')';
	return out;
}


/***********************************************
* Rectangle Definition
* width: rectangle width
* height: rectangle height
* bl: bottom left coordinate of this rectangle
************************************************/
template <typename T>
struct Rect
{
private:
    Coor<T> bl, tr;
    T width, height;

    inline void resetWH()
    {
        width  = tr.getX() - bl.getX();
        height = tr.getY() - bl.getY();
    }

public:
    Rect(const T x=T(), const T y=T(), const T w=T(), const T h=T()) : bl(x, y), tr(x+w, y+h), width(w), height(h) {}
    Rect(const Coor<T>& nbl, const Coor<T>& ntr) : bl(nbl), tr(ntr) { resetWH(); }

    inline const Coor<T>& getBL() const { return bl; }
    inline const Coor<T>& getTR() const { return tr; }
    inline const T& getW() const 		{ return width; }
    inline const T& getH() const		{ return height; }
    inline void setBL(const T x, const T y)
    {
        bl.set(x, y);
        resetWH();
    }
    inline void setBL(const Coor<T>& nbl)
    {
        bl.set(nbl);
        resetWH();
    }
    inline void setTR(const T x, const T y)
    {
        tr.set(x, y);
        resetWH();
    }
    inline void setTR(const Coor<T>& ntr)
    {
        tr.set(ntr);
        resetWH();
    }
    inline void set(const T x1, const T y1, const T x2, const T y2)
    {
        bl.set(x1, y1);
        tr.set(x2, y2);
        resetWH();
    }
    inline void blAddToX(const T val)
    {
        bl.addToX(val);
        width -= val;
    }
    inline void blAddToY(const T val)
    {
        bl.addToY(val);
        height -= val;
    }
    inline void trAddToX(const T val)
    {
        tr.addToX(val);
        width += val;
    }
    inline void trAddToY(const T val)
    {
        tr.addToY(val);
        height += val;
    }
    inline void shiftX(const T val)
    {
        bl.addToX(val);
        tr.addToX(val);
    }
    inline void shiftY(const T val)
    {
        bl.addToY(val);
        tr.addToY(val);
    }
    inline void setW(const T w)
    {
        width = w;
        tr.setX(bl.getX() + w);
    }
    inline void setH(const T h)
    {
        height = h;
        tr.setY(bl.getY() + h);
    }
};

#endif

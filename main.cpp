/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  A polygon to rectangle conversion tool
 *                  Reference: Kevin D. Gourley and Douglas M. Green
 *                  "A Polygon-to-Rectangle Conversion Algorithm"
 *                  In Proc. IEEE Computer Graphics and Applications, vol. 3, issue. 1
 *                  pp. 31-36, Jan, 1983.
 *
 *        Version:  1.0
 *        Created:  2017/09/18 (yyyy/mm/dd)
 *       Revision:  none
 *       Compiler:  g++ (C++14)
 *
 *         Author:  lionking
 *   Organization:  NCTU-CS-EDA
 *
 * =====================================================================================
 */
#include <cstdio>
#include <vector>
#include <list>
#include <tuple>
#include <iterator>
#include <algorithm>
#include <iostream>
#include "coordinate.hpp"


using namespace std;


// Decompose a polygon into a set of non-overlapping rectangles.
// A polygon is a set of point array in either clockwise or counter-clockwise order,
// and the first point in the point array will not be repeated in the last point in the point array
template <typename T, typename const_iterator>
void rectirization(const const_iterator& first, const const_iterator& last, std::vector< Rect<T> >& result);


int main()
{
    vector< Coor<int> > polygon;
    vector< Rect<int> > result;

    polygon.emplace_back(1, 1);
    polygon.emplace_back(3, 1);
    polygon.emplace_back(3, 3);
    polygon.emplace_back(4, 3);
    polygon.emplace_back(4, 1);
    polygon.emplace_back(5, 1);
    polygon.emplace_back(5, 5);
    polygon.emplace_back(4, 5);
    polygon.emplace_back(4, 4);
    polygon.emplace_back(2, 4);
    polygon.emplace_back(2, 2);
    polygon.emplace_back(1, 2);

    rectirization(polygon.cbegin(), polygon.cend(), result);

    cout << "rectangle list:\n";
    for (const auto& rect : result) {
        cout << "\t<" << rect.getBL() << " - " << rect.getTR() << ">\n";
    }

    return 0;
}


// return the target coordinate tuple for generating rectangle: Pk, Pl, Pm
// Reference: Figure 3 of the cited paper
template <typename const_iterator>
static auto findCoorTuple(const const_iterator& first, const const_iterator& last) -> std::tuple<const_iterator, const_iterator, const_iterator>
{
    // find Pk: the bottom and the leftmost coordinate
    const auto Pk = std::min_element(first, last, [](const auto& lhs, const auto& rhs) -> bool {
                if (lhs.getY() != rhs.getY()) { return (lhs.getY() < rhs.getY()); }
                else { return (lhs.getX() < rhs.getX()); }
            });

    // find Pl: the bottom and the leftmost coordinate except Pk
    const auto Pl = std::min_element(first, last, [&Pk](const auto& lhs, const auto& rhs) -> bool {
                // skip the element Pk
                if (lhs == (*Pk)) { return false; }
                else if (rhs == (*Pk)) { return true; }
                // find the smallest element
                else if (lhs.getY() != rhs.getY()) { return (lhs.getY() < rhs.getY()); }
                else { return (lhs.getX() < rhs.getX()); }
            });

    const auto Pm = std::min_element(first, last, [&Pk, &Pl](const auto& lhs, const auto& rhs) -> bool {
                // skip the element (x, y) out of the range:
                // Pk.getX() <= x < Pl.getX() && Pk.getY() < y
                if ((lhs.getY() <= Pk->getY()) || (lhs.getX() < Pk->getX()) || (lhs.getX() >= Pl->getX())) { return false; }
                else if ((rhs.getY() <= Pk->getY()) || (rhs.getX() < Pk->getX()) || (rhs.getX() >= Pl->getX())) { return true; }
                // find the smallest element
                else if (lhs.getY() != rhs.getY()) { return (lhs.getY() < rhs.getY()); }
                else { return (lhs.getX() < rhs.getX()); }
                return true;
            });

    return {Pk, Pl, Pm};
}


template <typename T>
static void updatePolygon(std::list< Coor<T> >& polygon, const Coor<T>& Pk, const Coor<T>& Pl, const Coor<T>& Pm)
{
    auto iter = polygon.begin();
    const Coor<int> upl(Pk.getX(), Pm.getY()), upr(Pl.getX(), Pm.getY());
    bool insert_upl = true, insert_upr = true;

    // update policy:
    // 1. if the coordinate exists in the point array: remove from the point array
    // 2. otherwise: add into the point array
    while (iter != polygon.end()) {
        if (*iter == Pk)        { iter = polygon.erase(iter); }
        else if (*iter == Pl)   { iter = polygon.erase(iter); }
        else if (*iter == upl)  { iter = polygon.erase(iter); insert_upl = false; }
        else if (*iter == upr)  { iter = polygon.erase(iter); insert_upr = false; }
        else                    { ++iter; }
    }

    if (insert_upl) { polygon.emplace_back(upl); }
    if (insert_upr) { polygon.emplace_back(upr); }
}


template <typename T, typename const_iterator>
void rectirization(const const_iterator& first, const const_iterator& last, std::vector< Rect<T> >& result)
{
    std::list< Coor<T> > polygon(first, last);

    result.clear();
    while (polygon.size() > 0) {
        const auto& coor_tuple = findCoorTuple(polygon.cbegin(), polygon.cend());
        const auto Pk = *(std::get<0>(coor_tuple));
        const auto Pl = *(std::get<1>(coor_tuple));
        const auto Pm = *(std::get<2>(coor_tuple));

        // extract rectangle
        result.emplace_back(Pk.getX(), Pk.getY(), Pl.getX() - Pk.getX(), Pm.getY() - Pk.getY());

        // update polygon (point array)
        updatePolygon(polygon, Pk, Pl, Pm);
    }
}


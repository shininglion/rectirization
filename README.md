# rectirization
A polygon to rectangle conversion tool
This tool will decompose a rectilinear polygon into a set of non-overlapping rectangles.
A polygon is a set of point array in either clockwise or counter-clockwise order, and the first point in the point array will not be repeated in the last point in the point array.

The key algorithm is as follows:
Pk: the leftmost point with the smallest Y-coordinate.
Pl: the leftmost point except Pk with the smallest Y-coordinate.
Pm: the leftmost point with the smallest Y-coordinate among the set of points satisfying Pk.x <= x < Pl.x && Pk.y < y
F(x, y): if the point array contains (x, y), remove (x, y) from the point array, otherwise add (x, y) into the point array.
while (polygon is not empty) {
    Find Pk, Pl, Pm.
    Form the rectangle: <Pk, (Pl.x, Pm.y)>
    F(Pk)
    F(Pl)
    F(Pk.x, Pm.y)
    F(Pl.x, Pm.y)
}

Reference: 
Kevin D. Gourley and Douglas M. Green, "A Polygon-to-Rectangle Conversion Algorithm," In Proc. IEEE Computer Graphics and Applications, vol. 3, issue. 1, pp. 31-36, Jan, 1983.

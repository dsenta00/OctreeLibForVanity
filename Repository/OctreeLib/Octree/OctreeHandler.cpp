//
//	OctreeHandler.cpp
//  Octal tree handler definition.
//
//  © 2018 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#include "pch.h"
#include "OctreeHandler.h"
#include "Pos3Handler.h"

/**
 *
 * @param leaf
 * @param current
 * @return
 */
OctreeLeaf *
OctreeHandler::insert(OctreeLeaf *leaf, OctreeLeaf *current)
{
    if (!current)
    {
        return leaf;
    }

    uint8_t index = current->route(leaf);
    (*current)[index] = insert(leaf, (*current)[index]);

    return current;
}

void
OctreeHandler::erase(OctreeLeaf *current)
{
    if (!current)
    {
        return;
    }

    for (var child : *current)
    {
        erase(child);
    }

    delete current;
}

void
OctreeHandler::print(OctreeLeaf *leaf)
{
    if (!leaf)
    {
        return;
    }

    for (var child : *leaf)
    {
        print(child);
    }

    std::cout << leaf->toString() << std::endl;
}

void
OctreeHandler::findNearest(std::vector<OctreeLeaf *> &vertices, Pos3 &position, OctreeLeaf *current)
{
    if (!current)
    {
        return;
    }

    if (vertices.empty())
    {
        vertices.insert(vertices.begin(), current);

        for (var leaf : *current)
        {
            findNearest(vertices, position, leaf);
        }

        return;
    }

    var currentClosest = vertices.front();

    if (current->distanceFrom(&position) < currentClosest->distanceFrom(&position))
    {
        vertices.insert(vertices.begin(), current);

        for (var leaf : *current)
        {
            findNearest(vertices, position, leaf);
        }
    }
}

void
OctreeHandler::iterateNext(OctreeLeaf *leaf, std::function<void(const Pos3 *position)> doSomething)
{
    if (!leaf)
    {
        return;
    }

    doSomething(leaf->getPosition());

    for (var child : *leaf)
    {
        iterateNext(child, doSomething);
    }
}

Pos3
OctreeHandler::averagePoint(Octree *o)
{
    Pos3 result = { 0.0f, 0.0f, 0.0f };

    if (o->empty())
    {
        /* This is just the early return, nothing to calculate here .. */
        return result;
    }

    o->foreach([&](const Pos3 *position) {
        result.x += position->x;
        result.y += position->y;
        result.z += position->z;
    });

    result.x /= o->getCount();
    result.y /= o->getCount();
    result.z /= o->getCount();

    return result;
}

Pos3
OctreeHandler::minkowskiSumSupport(Octree *o1, Octree *o2, Pos3 &direction)
{
    const Pos3 *furthestO1 = o1->furthestPointAccordingToDirection(direction);
    const Pos3 *furthestO2 = o2->furthestPointAccordingToDirection(Pos3Handler::negate(direction));

    return Pos3Handler::subtract(
        *(Pos3 *)furthestO1,
        *(Pos3 *)furthestO2
        );
}

/**
 * Gilbert-Johnson-Keerthi (GJK) collision detection algorithm in 3D
 * http://www.dyn4j.org/2010/04/gjk-gilbert-johnson-keerthi/
 * http://mollyrocket.com/849
 */
bool
OctreeHandler::collides(Octree *o1, Octree *o2)
{
    if (o1->empty() || o2->empty())
    {
        return false;
    }

    size_t index = 0; // index of current vertex of simplex
    Pos3 a, b, c, ao, ab, ac, abperp, acperp, simplex[3];

    Pos3 position1 = o1->averagePoint(); // not a CoG but
    Pos3 position2 = o2->averagePoint(); // it's ok for GJK )

    // initial direction from the center of 1st body to the center of 2nd body
    Pos3 direction = Pos3Handler::subtract(position1, position2);

    // if initial direction is zero – set it to any arbitrary axis (we choose X)
    if ((direction.x == 0.0f) && (direction.y == 0.0f) && (direction.z == 0.0f))
    {
        direction.x = 1.0f;
    }

    // set the first support as initial point of the new simplex
    a = simplex[0] = minkowskiSumSupport(o1, o2, direction);

    if (Pos3Handler::dotProduct(a, direction) <= 0)
    {
        return false; // no collision
    }

    direction = Pos3Handler::negate(a); // The next search direction is always towards the origin, so the next search direction is negate(a)

    while (true)
    {
        a = simplex[++index] = minkowskiSumSupport(o1, o2, direction);

        if (Pos3Handler::dotProduct(a, direction) <= 0)
        {
            return false; // no collision
        }

        ao = Pos3Handler::negate(a); // from point A to Origin is just negative A

        // simplex has 2 points (a line segment, not a triangle yet)
        if (index < 2)
        {
            b = simplex[0];
            ab = Pos3Handler::subtract(b, a); // from point A to B
            direction = Pos3Handler::tripleProduct(ab, ao, ab); // normal to AB towards Origin

            if (Pos3Handler::lengthSquared(direction) == 0)
            {
                direction = Pos3Handler::perpendicular(ab);
            }

            continue; // skip to next iteration
        }

        b = simplex[1];
        c = simplex[0];
        ab = Pos3Handler::subtract(b, a); // from point A to B
        ac = Pos3Handler::subtract(c, a); // from point A to C

        acperp = Pos3Handler::tripleProduct(ab, ac, ac);

        if (Pos3Handler::dotProduct(acperp, ao) >= 0)
        {
            direction = acperp; // new direction is normal to AC towards Origin
        }
        else
        {
            abperp = Pos3Handler::tripleProduct(ac, ab, ab);

            if (Pos3Handler::dotProduct(abperp, ao) < 0)
            {
                return true; // collision
            }

            simplex[0] = simplex[1]; // swap first element (point C)

            direction = abperp; // new direction is normal to AB towards Origin
        }

        simplex[1] = simplex[2]; // swap element in the middle (point B)
        --index;
    }

    return false;
}

const Pos3 *
OctreeHandler::furthestPointAccordingToDirection(Octree* o, Pos3 &direction)
{
    Pos3 *furthest = (Pos3 *)o->getRoot();
    float maxProduct = Pos3Handler::dotProduct(direction, *furthest);

    o->foreach([&](const Pos3 *position) {
        float product = Pos3Handler::dotProduct(direction, *(Pos3 *)position);

        if (product > maxProduct)
        {
            maxProduct = product;
            furthest = (Pos3 *)position;
        }
    });

    return furthest;
}
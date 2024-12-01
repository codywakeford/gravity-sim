#include <SFML/Graphics.hpp>
#include <vector>
#include "Satellite.hpp"

#ifndef QUADTREE_HPP
#define QUADTREE_HPP

struct Rectangle {
    float x, y;
    float width, height;

    Rectangle(float x, float y, float width, float height)
        : x(x), y(y), width(width), height(height) {}


    bool contains(const Satellite& point) const {
        return (point.position.x >= x - width / 2 && point.position.x <= x + width / 2 &&
                point.position.y >= y - height / 2 && point.position.y <= y + height / 2);
    }

    bool intersects(const Rectangle& range) const {
        return !(range.x - range.width / 2 > x + width / 2 ||
                 range.x + range.width / 2 < x - width / 2 ||
                 range.y - range.height / 2 > y + height / 2 ||
                 range.y + range.height / 2 < y - height / 2);
    }
};

class Quadtree {
private:
    static const int CAPACITY = 4;
    Rectangle boundary;
    std::vector<Satellite> bodies;
    bool divided;

    Quadtree* northeast;
    Quadtree* northwest;
    Quadtree* southeast;
    Quadtree* southwest;

public:
    Quadtree(Rectangle boundary)
        : boundary(boundary), divided(false),
          northeast(nullptr), northwest(nullptr),
          southeast(nullptr), southwest(nullptr) {}

    ~Quadtree() {
        delete northeast;
        delete northwest;
        delete southeast;
        delete southwest;
    }

    void subdivide() {
        float x = boundary.x;
        float y = boundary.y;
        float w = boundary.width / 2;
        float h = boundary.height / 2;

        northeast = new Quadtree(Rectangle(x + w / 2, y - h / 2, w, h));
        northwest = new Quadtree(Rectangle(x - w / 2, y - h / 2, w, h));
        southeast = new Quadtree(Rectangle(x + w / 2, y + h / 2, w, h));
        southwest = new Quadtree(Rectangle(x - w / 2, y + h / 2, w, h));

        divided = true;
    }

    
    bool insert(const Satellite& body) {
        if (!boundary.contains(body)) {
            return false; // Point is out of bounds
        }

        if (bodies.size() < CAPACITY) {
            bodies.push_back(body);
            return true;
        }

        if (!divided) {
            subdivide();
        }

        if (northeast->insert(body) || northwest->insert(body) ||
            southeast->insert(body) || southwest->insert(body)) {
            return true;
        }

        return false; 
    }

    // Query points within a given range
    void query(const Rectangle& range, std::vector<Satellite>& found) const {
        if (!boundary.intersects(range)) {
            return;
        }

        for (const Satellite& body : bodies) {
            if (range.contains(body)) {
                found.push_back(body);
            }
        }

        if (divided) {
            northeast->query(range, found);
            northwest->query(range, found);
            southeast->query(range, found);
            southwest->query(range, found);
        }
    }
};

#endif
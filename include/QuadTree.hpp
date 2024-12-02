#include <SFML/Graphics.hpp>
#include <vector>
#include "collision_math.hpp"
#include "Satellite.hpp"
#include <memory>


#ifndef QUADTREE_HPP
#define QUADTREE_HPP

// OPTIONS //
const bool RENDER_QUADTREE = false;
////////////////////////////////////


struct Rectangle {
    float x, y;
    float width, height;

    Rectangle(float x, float y, float width, float height)
        : x(x), y(y), width(width), height(height) {}

    bool contains(const Satellite* body) const {
        if (!body) return false;

        // print(x);
        // print(y);
        // print(width);
        // print(height);

        return (
            body->position.x >= x - width / 2 && 
            body->position.x <= x + width / 2 &&
            body->position.y >= y - height / 2 && 
            body->position.y <= y + height / 2
        );

    }

    bool intersects(const Rectangle& range) const {
        return !(range.x - range.width / 2 > x + width / 2 ||
                 range.x + range.width / 2 < x - width / 2 ||
                 range.y - range.height / 2 > y + height / 2 ||
                 range.y + range.height / 2 < y - height / 2);
    }
    
    void render(sf::RenderWindow& window) const {
        if (!RENDER_QUADTREE) return;

        sf::RectangleShape shape(sf::Vector2f(width, height));
        shape.setOrigin(width / 2, height / 2); // Center the rectangle
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color::Transparent); // No fill color
        shape.setOutlineColor(sf::Color::Red);
        shape.setOutlineThickness(5);

        window.draw(shape);
    }
    

};

class Quadtree {
private:
    static const int CAPACITY = 2;
    std::vector<Satellite*> bodies;
    bool divided;

    Quadtree* northeast;
    Quadtree* northwest;
    Quadtree* southeast;
    Quadtree* southwest;

public:
    Rectangle boundary;
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

    void clear() {
        bodies.clear();
        if (divided) {
            northeast->clear();
            northwest->clear();
            southeast->clear();
            southwest->clear();
            delete northeast; northeast = nullptr;
            delete northwest; northwest = nullptr;
            delete southeast; southeast = nullptr;
            delete southwest; southwest = nullptr;
            divided = false;
        }
    }

    void render(sf::RenderWindow& window) {
        if (!divided) return;

        boundary.render(window);

        northeast->render(window);
        northwest->render(window);
        southeast->render(window);
        southwest->render(window);
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

    // Recursivly solves all collisions
    void resolve_collisions() {
        // Check collisions in the current node
        for (size_t i = 0; i < bodies.size(); ++i) {
            for (size_t j = i + 1; j < bodies.size(); ++j) {
                resolve_collision(*bodies[i], *bodies[j]);
            }
        }

        // Check collisions between this node's bodies and its children's bodies
        if (divided) {
            std::vector<Satellite*> childBodies;
            collect_bodies(childBodies);

            for (Satellite* body1 : bodies) {
                for (Satellite* body2 : childBodies) {
                    if (body1 == body2) continue;
                    resolve_collision(*body1, *body2);
                }
            }

            // Recursively resolve collisions in children
            northeast->resolve_collisions();
            northwest->resolve_collisions();
            southeast->resolve_collisions();
            southwest->resolve_collisions();
        }
    }

    void collect_bodies(std::vector<Satellite*>& out) const {
        out.insert(out.end(), bodies.begin(), bodies.end());
        if (divided) {
            northeast->collect_bodies(out);
            northwest->collect_bodies(out);
            southeast->collect_bodies(out);
            southwest->collect_bodies(out);
        }
    }

    bool insert(Satellite* body) {
        print(bodies.size());  

        if (!boundary.contains(body)) {
            return false;
        }

        if (bodies.size() < CAPACITY) {
            bodies.push_back(body);
            return true;
        }

        if (!divided) {
            subdivide();
        }

        for (auto it = bodies.begin(); it != bodies.end(); ) {
            Satellite* body = *it;
            if (northeast->insert(body) || northwest->insert(body) ||
                southeast->insert(body) || southwest->insert(body)) {
                it = bodies.erase(it); // Remove from parent if inserted
            } else {
                ++it;
            }
        }

        if (northeast->insert(body) || northwest->insert(body) ||
            southeast->insert(body) || southwest->insert(body)) {
            return true;
        }

        return false; 
    }
};


#endif
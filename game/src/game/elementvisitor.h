#pragma once

class Point;
class SuperPoint;
class Teleporter;

class ElementVisitor {
    public:
        virtual void visite(const Point& point) = 0;

        virtual void visite(const SuperPoint& superPoint) = 0;

        virtual void visite(const Teleporter& teleporter) = 0;
};
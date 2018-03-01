#pragma once

class Point;
class SuperPoint;
class Teleporter;

class ElementVisitor {
    public:
        /**
         * @brief Visite d'un point
         * @param point Point
         */
        virtual void visite(const Point& point) = 0;

        /**
         * @brief Visite d'un superpoint
         * @param superPoint SuperPoint
         */
        virtual void visite(const SuperPoint& superPoint) = 0;

        /**
         * @brief Visite d'un téléporteur
         * @param teleporter Teleporter
         */
        virtual void visite(const Teleporter& teleporter) = 0;
};
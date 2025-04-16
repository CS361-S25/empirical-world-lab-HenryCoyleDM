#ifndef ORG_H
#define ORG_H

#include "emp/math/Random.hpp"
#include "emp/tools/string_utils.hpp"

class Organism {
    private:
        double points;
        emp::Ptr<emp::Random> random;
        double reproduction_cost = 1000;

    public:
    Organism(emp::Ptr<emp::Random> _random, double _points=0.0) :
        points(_points), random(_random) {;}

    void SetPoints(double _in) {points = _in;}
    void AddPoints(double _in) {points += _in;}


    void Process(double points) {
        std::cout << "Processing" << std::endl; //feel free to get rid of this
        AddPoints(points);
    }

    emp::Ptr<Organism> CheckReproduction() {
        if (points >= reproduction_cost) {
            emp::Ptr<Organism> offspring = new Organism(*this);
            offspring->points = 0;
            points -= reproduction_cost;
            return offspring;
        } else {
            return nullptr;
        }
    }
};
#endif
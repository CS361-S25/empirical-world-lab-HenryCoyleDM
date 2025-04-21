#ifndef ORG_H
#define ORG_H

#include "emp/math/Random.hpp"
#include "emp/tools/string_utils.hpp"

class Organism {
    private:
        double points;
        emp::Ptr<emp::Random> random;
        // bool has_moved_this_generation = false;
        // this is daft

    protected:
        double reproduction_cost;

    public:
    Organism(emp::Ptr<emp::Random> _random, double _points=0.0) :
        points(_points), random(_random), reproduction_cost(1000)/*, has_moved_this_generation(false)*/ {}
    
    Organism(const Organism& obj) {
        random = obj.random;
        points = obj.points;
        reproduction_cost = 1000;
    }

    Organism(Organism* obj) {
        random = obj->random;
        points = obj-> points;
        reproduction_cost = 1000;
    }

    void SetPoints(double _in) {points = _in;}
    void AddPoints(double _in) {points += _in;}
    //void SetMovedThisGeneration(bool _has_moved_this_generation) {has_moved_this_generation = _has_moved_this_generation;}
    //bool IsMovedThisGeneration() {return has_moved_this_generation;}


    void Process(double points) {
        std::cout << "Processing. Reproduction cost is " << std::to_string(reproduction_cost) << std::endl; //feel free to get rid of this
        AddPoints(points);
        // has_moved_this_generation = false;
    }

    emp::Ptr<Organism> CheckReproduction() {
        std::cout << "Checking reproduction. Current score is " << std::to_string(points) << std::endl;
        if (points >= reproduction_cost) {
            emp::Ptr<Organism> offspring = new Organism(random, points);
            offspring->points = 0;
            points -= reproduction_cost;
            std::cout << "Created an offspring with score " << std::to_string(offspring->points) << " and reproduction_cost " << std::to_string(reproduction_cost) << std::endl;
            return offspring;
        } else {
            std::cout << "Could not reproduce." << std::endl;
            return nullptr;
        }
    }

    virtual void GetColor() {
        std::cout << "This organism is black" << std::endl;
        // return "black";
    }
};
#endif
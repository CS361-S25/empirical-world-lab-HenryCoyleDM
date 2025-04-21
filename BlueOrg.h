#include "Org.h"

class BlueOrg : public Organism {
    public:
    BlueOrg(emp::Ptr<emp::Random> _random, double _points=0.0) : Organism(_random, _points) {
        reproduction_cost = 500;
        std::cout << "Created a new blue organism with cost " << std::to_string(reproduction_cost);
        GetColor();
    }

    /*public:
    void GetColor() {
        std::cout << "This organism is blue" << std::endl;
        // return "blue";
    }*/
};
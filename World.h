#ifndef WORLD_H
#define WORLD_H

#include "emp/Evolve/World.hpp"
#include "emp/math/random_utils.hpp"
#include "emp/math/Random.hpp"

#include "Org.h"

class OrgWorld : public emp::World<Organism> {

    emp::Random &random;
    emp::Ptr<emp::Random> random_ptr;
    double points_per_update = 100;

    public:

    OrgWorld(emp::Random &_random) : emp::World<Organism>(_random), random(_random) {
        random_ptr.New(_random);
    }

    ~OrgWorld() {
    }

  void Update() {
      emp::World<Organism>::Update();
      emp::vector<size_t> schedule = emp::GetPermutation(random, GetSize());
      for (int i : schedule) {
        if (!IsOccupied(i)) {
            continue;
        }
        pop[i]->Process(points_per_update);
      }
      emp::vector<size_t> schedule_reproduction = emp::GetPermutation(random, GetSize());
      for (int i : schedule) {
        if (!IsOccupied(i)) {
            continue;
        }
        emp::Ptr<Organism> offspring = pop[i]->CheckReproduction();
        if (offspring) {
            DoBirth(*offspring, i);
        }
      }
      std::cout << "World contains " + std::to_string(GetNumOrgs()) << " organisms." << std::endl; //feel free to get rid of this
  }

};
#endif
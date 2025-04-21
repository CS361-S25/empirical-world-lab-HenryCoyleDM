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
      // process organisms
      emp::vector<size_t> schedule = emp::GetPermutation(random, GetSize());
      for (size_t i : schedule) {
        if (!IsOccupied(i)) {
            continue;
        }
        pop[i]->Process(points_per_update);
      }
      // move organisms
      emp::vector<size_t> schedule_move = emp::GetPermutation(random, GetSize());
      for (size_t i : schedule) {
        if (!IsOccupied(i)) {
          continue;
        }
        emp::Ptr<Organism> organism_at = ExtractOrganism(i);
        emp::WorldPosition NeighborPosition = GetRandomNeighborPos(i);
        // don't let an organism move into an occupied cell
        std::cout << "Organism at " << std::to_string(i) << " trying to move" << std::endl;
        if (!IsOccupied(NeighborPosition)/* && !organism_at->has_moved_this_generation*/) {
          //organism_at->SetMovedThisGeneration(true);
          AddOrgAt(organism_at, NeighborPosition);
          std::cout << "Organism moving to " << NeighborPosition.GetIndex() << std::endl;
        } else {
          AddOrgAt(organism_at, i);
        }
      }
      // reproduce
      emp::vector<size_t> schedule_reproduction = emp::GetPermutation(random, GetSize());
      for (size_t i : schedule) {
        if (!IsOccupied(i)) {
            continue;
        }
        std::cout << "Location " << std::to_string(i) << " is occupied" << std::endl;
        emp::Ptr<Organism> offspring = GetOrg(i).CheckReproduction();
        if (offspring != nullptr) {
          std::cout << "Organism at " << std::to_string(i) << " is reproducing" << std::endl;  
          DoBirth(*offspring, i);
          std::cout << "Did birth at " << std::to_string(i) << std::endl;
        } else {
          std::cout << "Organism at " << std::to_string(i) << " is not reproducing" << std::endl;
        }
      }
      std::cout << "World contains " + std::to_string(GetNumOrgs()) << " organisms." << std::endl; //feel free to get rid of this
  }

  // get the organism at position i and remove it
  public:
  emp::Ptr<Organism> ExtractOrganism(int i) {
    emp::Ptr<Organism> organism_at = pop[i];
    RemoveOrgAt(i);
    return organism_at;
  }

};
#endif
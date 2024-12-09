#include <iostream>
#include <chrono>
#include <vector>
#include "quadTree.h"

// Define a simple entity type for testing
struct CollidableEntity {
  int id;
  std::vector<int> midpoint;
  int size;
  int defense{};
  int attack{};
  std::vector<int> collidingEntities;
  std::string color;
};

struct Troop : public CollidableEntity {
  int movement{};
  int attackDistance{};
  int cost{};
  int foodCost{};
};

int main() {
  const int numTests = 1000;
  const int numEntities = 1000;
  double totalInsertionTime = 0.0;
  double totalQueryTime = 0.0;
  double totalRemovalTime = 0.0;

  for (int i = 0; i < numTests; ++i) {
    // Create a QuadTree with a width and height of 100 and a max depth of 5
    auto quadTree = createQuadTree<CollidableEntity>(100, 100, 5);

    // Create and insert test entities
    std::vector<CollidableEntity> entities;
    for (int j = 0; j < numEntities; ++j) {
      Troop entity = { j, { rand() % 100, rand() % 100 }, 5 };
      entities.push_back(entity);
    }


    // Measure insertion time
    auto start = std::chrono::high_resolution_clock::now();
    for (auto& entity : entities) {
      insertEntity(quadTree, &entity);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> insertionTime = end - start;
    totalInsertionTime += insertionTime.count();

    // Measure query time
    start = std::chrono::high_resolution_clock::now();
    std::vector<CollidableEntity*> result = queryRange(quadTree, 50, 50, 20);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> queryTime = end - start;
    totalQueryTime += queryTime.count();

    // Measure removal time
    start = std::chrono::high_resolution_clock::now();
    for (auto& entity : entities) {
      removeEntity(quadTree, &entity);
    }
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> removalTime = end - start;
    totalRemovalTime += removalTime.count();
  }

  std::cout << "Average insertion time: " << (totalInsertionTime / numTests) << " seconds\n";
  std::cout << "Average query time: " << (totalQueryTime / numTests) << " seconds\n";
  std::cout << "Average removal time: " << (totalRemovalTime / numTests) << " seconds\n";

  std::cout << "\nTESTING COMPLETE, TERMINATION IN PROGRESS" << std::endl;
  return 0;
}

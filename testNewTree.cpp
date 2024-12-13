#include <iostream>
#include <chrono>
#include <vector>
#include "NewQuadTree.h"

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

  Quad<CollidableEntity> center(Point(0,0), Point(1500,600));
  
  Troop initialEntity = { 1, { 150, 500 }, 5 }; 
  Node<CollidableEntity> initialEnter(Point(initialEntity.midpoint[0], initialEntity.midpoint[1]), initialEntity);
  center.insert(&initialEnter);

  for (int i=2; i<=6; ++i) {
    Troop entity = { i, { rand() % 100, rand() % 100 }, 5 };
    Node<CollidableEntity> toEnter(Point(entity.midpoint[0], entity.midpoint[1]), entity);
    center.insert(&toEnter);
  }
  
  Node<CollidableEntity>* foundNode = center.search(Point(150,500));
  std::cout << foundNode->data.midpoint[0] << std::endl;
  
/*
  for (int i = 0; i < numTests; ++i) {
    // Create a QuadTree with a width and height of 100 and a max depth of 5
    Quad<CollidableEntity> center(Point(0, 0), Point(1500, 600));

    // Create and insert test entities
    std::vector<CollidableEntity> entities;
    for (int j = 0; j < numEntities; ++j) {
      Troop entity = { j, { rand() % 100, rand() % 100 }, 5 };
      Node<CollidableEntity> toEnter(Point(entity.midpoint[0], entity.midpoint[1]), entity);
      center.insert(&toEnter);
    }

    // Measure insertion time
    auto start = std::chrono::high_resolution_clock::now();
    for (auto& entity : entities) {
      Node<CollidableEntity> toEnter(Point(entity.midpoint[0], entity.midpoint[1]), entity);
      center.insert(&toEnter);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> insertionTime = end - start;
    totalInsertionTime += insertionTime.count();

    // Measure query time
    start = std::chrono::high_resolution_clock::now();
    Node<CollidableEntity>* result = center.search(Point(50, 50));
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> queryTime = end - start;
    totalQueryTime += queryTime.count();

    // Measure removal time
    start = std::chrono::high_resolution_clock::now();
    // Assuming we have a remove function (not implemented in the provided code)
    // for (auto& entity : entities) {
    //     center.remove(&entity);
    // }
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> removalTime = end - start;
    totalRemovalTime += removalTime.count();
  }

  std::cout << "Average insertion time: " << (totalInsertionTime / numTests) << " seconds\n";
  std::cout << "Average query time: " << (totalQueryTime / numTests) << " seconds\n";
  std::cout << "Average removal time: " << (totalRemovalTime / numTests) << " seconds\n";

  std::cout << "\nTESTING COMPLETE, TERMINATION IN PROGRESS" << std::endl;
*/ 
 return 0;
}

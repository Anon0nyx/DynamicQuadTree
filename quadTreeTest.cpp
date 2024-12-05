#include <iostream>
#include <chrono>
#include "quadTree.h"

// Define a simple entity type for testing
struct TestEntity {
  int id;
  std::vector<int> midpoint;
  int size;
};

void printEntities(const std::vector<TestEntity*>& entities) {
  for (const auto& entity : entities) {
    std::cout << "Entity ID: " << entity->id << " at (" << entity->midpoint[0] << ", " << entity->midpoint[1] << ")\n";
  }
}

int main() {
  // Create a QuadTree with a width and height of 100 and a max depth of 5
  QuadTree<TestEntity> quadTree(100, 100, 5);

  // Create some test entities
  TestEntity entity1 = { 1, {10, 10}, 5 };
  TestEntity entity2 = { 2, {20, 20}, 5 };
  TestEntity entity3 = { 3, {30, 30}, 5 };
  TestEntity entity4 = { 4, {40, 40}, 5 };
  TestEntity entity5 = { 5, {50, 50}, 5 };

  // Measure insertion time
  auto start = std::chrono::high_resolution_clock::now();
  quadTree.insert(&entity1);
  quadTree.insert(&entity2);
  quadTree.insert(&entity3);
  quadTree.insert(&entity4);
  quadTree.insert(&entity5);
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> insertionTime = end - start;
  std::cout << "Insertion time: " << insertionTime.count() << " seconds\n";

  // Measure query time
  start = std::chrono::high_resolution_clock::now();
  std::vector<TestEntity*> result = quadTree.queryRange(25, 25, 20);
  end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> queryTime = end - start;
  std::cout << "Query time: " << queryTime.count() << " seconds\n";
  printEntities(result);

  // Measure removal time
  start = std::chrono::high_resolution_clock::now();
  quadTree.remove(&entity3);
  end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> removalTime = end - start;
  std::cout << "Removal time: " << removalTime.count() << " seconds\n";

  // Query again after removal
  std::cout << "\nAfter removing entity 3:\n";
  result = quadTree.queryRange(25, 25, 20);
  printEntities(result);

  return 0;
}

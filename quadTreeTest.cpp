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
  const int numTests = 1000;
  double totalInsertionTime = 0.0;
  double totalQueryTime = 0.0;
  double totalRemovalTime = 0.0;

  for (int i = 0; i < numTests; ++i) {
    // Create a QuadTree with a width and height of 100 and a max depth of 5
    auto quadTree = createQuadTree<TestEntity>(100, 100, 5);

    // Create some test entities
    TestEntity entity1 = { 1, {10, 10}, 5 };
    TestEntity entity2 = { 2, {20, 20}, 5 };
    TestEntity entity3 = { 3, {30, 30}, 5 };
    TestEntity entity4 = { 4, {40, 40}, 5 };
    TestEntity entity5 = { 5, {50, 50}, 5 };

    // Measure insertion time
    auto start = std::chrono::high_resolution_clock::now();
    insertEntity(quadTree, &entity1);
    insertEntity(quadTree, &entity2);
    insertEntity(quadTree, &entity3);
    insertEntity(quadTree, &entity4);
    insertEntity(quadTree, &entity5);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> insertionTime = end - start;
    totalInsertionTime += insertionTime.count();

    // Measure query time
    start = std::chrono::high_resolution_clock::now();
    std::vector<TestEntity*> result = queryRange(quadTree, 25, 25, 20);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> queryTime = end - start;
    totalQueryTime += queryTime.count();

    // Measure removal time
    start = std::chrono::high_resolution_clock::now();
    removeEntity(quadTree, &entity3);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> removalTime = end - start;
    totalRemovalTime += removalTime.count();
  }

  std::cout << "Average insertion time: " << (totalInsertionTime / numTests) << " seconds\n";
  std::cout << "Average query time: " << (totalQueryTime / numTests) << " seconds\n";
  std::cout << "Average removal time: " << (totalRemovalTime / numTests) << " seconds\n";

  return 0;
}

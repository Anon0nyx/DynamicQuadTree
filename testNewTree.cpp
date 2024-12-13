#include <iostream>
#include <chrono>
#include <vector>
#include <unordered_set>
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

  Troop entity2 = { 2, { 300, 400 }, 5 };
  Node<CollidableEntity> toEnter2(Point(entity2.midpoint[0], entity2.midpoint[1]), entity2);
  center.insert(&toEnter2);

  Troop entity3 = { 3, { 1400, 550 }, 5 };
  Node<CollidableEntity> toEnter3(Point(entity3.midpoint[0], entity3.midpoint[1]), entity3);
  center.insert(&toEnter3);

  Troop entity4 = { 4, { 900, 100 }, 5 };
  Node<CollidableEntity> toEnter4(Point(entity4.midpoint[0], entity4.midpoint[1]), entity4);
  center.insert(&toEnter4);

  Troop entity5 = { 5, { 1200, 300 }, 5 };
  Node<CollidableEntity> toEnter5(Point(entity5.midpoint[0], entity5.midpoint[1]), entity5);
  center.insert(&toEnter5);

  Troop entity6 = { 6, { 1400, 500 }, 5 };
  Node<CollidableEntity> toEnter6(Point(entity6.midpoint[0], entity6.midpoint[1]), entity6);
  center.insert(&toEnter6);
  
  Node<CollidableEntity>* foundNode = center.search(Point(150,500));
  std::cout << foundNode->data.midpoint[0] << std::endl;
  
  center.printIDs();

 return 0;
}

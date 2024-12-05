#ifndef QUAD_TREE_H
#define QUAD_TREE_H

#include <vector>
#include <algorithm>
#include <memory>

template <typename EntityType>
struct QuadTreeNode {
    int x, y, size;
    std::vector<EntityType*> entities;
    std::unique_ptr<QuadTreeNode<EntityType>> children[4];

    QuadTreeNode(int x, int y, int size) : x(x), y(y), size(size) {}
    bool isLeaf() const {
        return children[0] == nullptr;
    }
};

template <typename EntityType>
class QuadTree {
public:
    QuadTree(int width, int height, int maxDepth);
    ~QuadTree() = default;

    void insert(EntityType* entity);
    void remove(EntityType* entity);
    std::vector<EntityType*> queryRange(int x, int y, int range);

private:
    std::unique_ptr<QuadTreeNode<EntityType>> root;
    int maxDepth;

    void insert(QuadTreeNode<EntityType>* node, EntityType* entity, int depth);
    void remove(QuadTreeNode<EntityType>* node, EntityType* entity);
    void queryRange(QuadTreeNode<EntityType>* node, int x, int y, int range, std::vector<EntityType*>& result);
    void subdivide(QuadTreeNode<EntityType>* node);
    bool intersects(int x, int y, int range, QuadTreeNode<EntityType>* node);
};

#include "quadTreeImplementation.h"

#endif // QUAD_TREE_H

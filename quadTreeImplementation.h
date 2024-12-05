#ifndef QUAD_TREE_IMPL_H
#define QUAD_TREE_IMPL_H

#include "quadTree.h"

template <typename EntityType>
QuadTree<EntityType>::QuadTree(int width, int height, int maxDepth) : maxDepth(maxDepth) {
    root = std::make_unique<QuadTreeNode<EntityType>>(0, 0, std::max(width, height));
}

template <typename EntityType>
void QuadTree<EntityType>::insert(EntityType* entity) {
    insert(root.get(), entity, 0);
}

template <typename EntityType>
void QuadTree<EntityType>::remove(EntityType* entity) {
    remove(root.get(), entity);
}

template <typename EntityType>
std::vector<EntityType*> QuadTree<EntityType>::queryRange(int x, int y, int range) {
    std::vector<EntityType*> result;
    queryRange(root.get(), x, y, range, result);
    return result;
}

template <typename EntityType>
void QuadTree<EntityType>::insert(QuadTreeNode<EntityType>* node, EntityType* entity, int depth) {
    if (node->isLeaf()) {
        if (node->entities.size() < 4 || depth == maxDepth) {
            node->entities.push_back(entity);
        } else {
            subdivide(node);
            insert(node, entity, depth);
        }
    } else {
        int index = (entity->midpoint[0] > node->x + node->size / 2) + 2 * (entity->midpoint[1] > node->y + node->size / 2);
        insert(node->children[index].get(), entity, depth + 1);
    }
}

template <typename EntityType>
void QuadTree<EntityType>::remove(QuadTreeNode<EntityType>* node, EntityType* entity) {
    if (node->isLeaf()) {
        node->entities.erase(std::remove(node->entities.begin(), node->entities.end(), entity), node->entities.end());
    } else {
        int index = (entity->midpoint[0] > node->x + node->size / 2) + 2 * (entity->midpoint[1] > node->y + node->size / 2);
        remove(node->children[index].get(), entity);
    }
}

template <typename EntityType>
void QuadTree<EntityType>::queryRange(QuadTreeNode<EntityType>* node, int x, int y, int range, std::vector<EntityType*>& result) {
    if (!intersects(x, y, range, node)) return;

    for (auto& entity : node->entities) {
        int dx = entity->midpoint[0] - x;
        int dy = entity->midpoint[1] - y;
        if (dx * dx + dy * dy <= range * range) {
            result.push_back(entity);
        }
    }

    if (!node->isLeaf()) {
        for (auto& child : node->children) {
            queryRange(child.get(), x, y, range, result);
        }
    }
}

template <typename EntityType>
void QuadTree<EntityType>::subdivide(QuadTreeNode<EntityType>* node) {
    int halfSize = node->size / 2;
    node->children[0] = std::make_unique<QuadTreeNode<EntityType>>(node->x, node->y, halfSize);
    node->children[1] = std::make_unique<QuadTreeNode<EntityType>>(node->x + halfSize, node->y, halfSize);
    node->children[2] = std::make_unique<QuadTreeNode<EntityType>>(node->x, node->y + halfSize, halfSize);
    node->children[3] = std::make_unique<QuadTreeNode<EntityType>>(node->x + halfSize, node->y + halfSize, halfSize);

    for (auto& entity : node->entities) {
        int index = (entity->midpoint[0] > node->x + halfSize) + 2 * (entity->midpoint[1] > node->y + halfSize);
        node->children[index]->entities.push_back(entity);
    }
    node->entities.clear();
}

template <typename EntityType>
bool QuadTree<EntityType>::intersects(int x, int y, int range, QuadTreeNode<EntityType>* node) {
    return !(x + range < node->x || x - range > node->x + node->size || y + range < node->y || y - range > node->y + node->size);
}

#endif // QUAD_TREE_IMPL_H

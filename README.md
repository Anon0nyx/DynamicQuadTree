# City Sprint Application - Dynamic QuadTree

## Overview

The City Sprint application is undergoing a significant refactor to transform it into a robust game engine with additional networking capabilities. As part of this refactor, we are implementing a dynamic QuadTree to efficiently manage spatial entities within the game world.

## Purpose

The dynamic QuadTree is designed to handle the spatial partitioning of entities in the game world. This allows for efficient querying, insertion, and removal of entities, which is crucial for performance in a game engine. The QuadTree helps in optimizing collision detection, rendering, and other spatial queries by reducing the number of entities that need to be checked.

## Design

### QuadTree Structure

The QuadTree is a tree data structure in which each internal node has exactly four children. It is used to partition a two-dimensional space by recursively subdividing it into four quadrants or regions. This structure is particularly well-suited for managing spatial data in a game engine.

### Dynamic Nature

The QuadTree is dynamic, meaning it can grow and shrink as entities are added and removed. This flexibility is essential for a game engine where the number and position of entities can change frequently.

### Performance Metrics

To ensure the QuadTree performs efficiently, we measure the time taken for key operations such as insertion, querying, and removal of entities. These metrics help us identify and address any performance bottlenecks.

## Implementation

The QuadTree is implemented in C++ and integrated into the City Sprint application. Below is a snippet of the test code used to measure the performance of the QuadTree:


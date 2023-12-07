# C++ City Map Project

## Overview
This C++ project implements a simple city map representation using object-oriented programming and standard template library (STL). The program reads city names and distances between them from a file, constructs a map, and prints the adjacency list representation of the cities and their distances.

## Features
- **City_builder Class**: Represents a city with a name.
- **Distance_maker Class**: Represents a distance between two cities with a specified weight (distance in kilometers).
- **Map Class**: Manages cities and their distances, providing methods to add cities and distances, and print the map.

## Usage
1. Input the filename and directory containing the city map information.
2. The program reads the file, extracts city names and distances, and builds the city map.
3. The constructed city map is printed in the form of an adjacency list.

## How to Run
Compile the program using a C++ compiler (e.g., g++):

```bash
g++ -std=c++17 main.cpp -o city_map


input:
Sofia Plovdiv Burgas
150 250

output:
City: Sofia is connected to: Plovdiv(150) Burgas(250)
City: Plovdiv is connected to: Burgas(250)

#!/bin/bash

for map in maps/*/*.cub; do
    echo "Running: ./cub3D $map"
    valgrind ./cub3D "$map"
done


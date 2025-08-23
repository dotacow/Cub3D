#!/bin/bash

for map in maps/*/*.cub; do
    echo "Running: ./cub3D $map"
    ./cub3D "$map"
done


#!/usr/bin/env bash

echo "" > log.txt
for i in {1..1000}
do
    ./fem_tet_mesh_simulator --output_file "$i.bin" >> log.txt
done

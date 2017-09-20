#!/bin/bash


while true #could equivalently be while [ 1 ]
do
timeout 10 ../../../build/dev/eGwinn/cubeSim ../../../build/dev/eGwinn/Ball.yaml
done


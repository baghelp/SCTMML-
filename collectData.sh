#!/bin/bash


# for i1 in $(seq 1 3 9)
# do
# for i2 in $(seq 1 3 9)
# do
# for i3 in $(seq 1 3 9)
# do
# for i4 in $(seq 1 3 9)
# do
# for i5 in $(seq 1 3 9)
# do
# for i6 in $(seq 1 3 9)
# do
# for i7 in 1
# do
# for i8 in 1
# do
# for i9 in 1
# do
# for i10 in 1
# do
# for i11 in 1
# do
# for i12 in 1
# do
# sed -i "35s/.*/double rLength[12] = {$i1, $i2, $i3, $i4,/" cubeSim.h
# sed -i "36s/.*/$i5, $i6, $i7, $i8,$i9, $i10, $i11, $i12};/" cubeSim.h
# sudo ../../../bin/build.sh
# timeout 20 ../../../build/dev/eGwinn/cubeSim ../../../build/dev/eGwinn/Ball.yaml
#
# done
# done
# done
# done
# done
# done
# done
# done
# done
# done
# done
# done

for i1 in $(seq 1 8 9)
do
for i2 in $(seq 1 8 9)
do
for i3 in $(seq 1 8 9)
do
for i4 in $(seq 1 8 9)
do
for i5 in $(seq 1 8 9)
do
for i6 in $(seq 1 8 9)
do
for i7 in $(seq 1 8 9)
do
for i8 in $(seq 1 8 9)
do
for i9 in $(seq 1 8 9)
do
for i10 in $(seq 1 8 9)
do
for i11 in $(seq 1 8 9)
do
for i12 in $(seq 1 8 9)
do
sed -i "35s/.*/double rLength[12] = {$i1, $i2, $i3, $i4,/" cubeSim.h
sed -i "36s/.*/$i5, $i6, $i7, $i8,$i9, $i10, $i11, $i12};/" cubeSim.h
sudo ../../../bin/build.sh
timeout 15 ../../../build/dev/eGwinn/cubeSim ../../../build/dev/eGwinn/Ball.yaml

done
done
done
done
done
done
done
done
done
done
done
done


#   echo "double rLength[12] = {$i1, $i2, $i3, $i4, $i5, $i6, $i7, $i8, $i9, $i10,
# $i11, $i12 };"
#   

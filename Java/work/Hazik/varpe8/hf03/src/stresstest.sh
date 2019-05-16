#!/bin/bash

mkdir test
cd test

#Sok párhuzamos indítása
for (( i = 0; i < 250; i++ )); do
    java -cp ../bin Main 2>out$i.txt >/dev/null & #csak az errorokat logolja 
done

# megvárja a míg befelyezik
for job in `jobs -p`
do
    echo "wait $job"
    wait $job || let "echo err"
    echo "$job fin"
done

echo "vege"

#Egyberakja a logokat
find . -name 'out*.txt' -exec cat {} >all.txt \;

#Kiírj a ha vannak
echo "hibák: "
cat all.txt

#Takarítás
cd ../
rm -dr test
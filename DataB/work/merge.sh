#!/bin/bash

cat drop.sql > all.sql

echo -e "\n\n" >> all.sql
cat create.sql >> all.sql

echo -e "\n\n" >> all.sql
cat alter.sql >> all.sql

echo -e "\n\n" >> all.sql
lua insert.lua > insert.txt #lua futtatás
awk '!a[$0]++' insert.txt > insert.sql #duplázott sorok kiszedése
rm insert.txt
cat insert.sql >> all.sql

echo -e "\n\n" >> all.sql
cat query.sql >> all.sql

echo -e "\n\n" >> all.sql
cat view.sql >> all.sql

echo -e "\n\n" >> all.sql
cat trigger.sql >> all.sql
#!/bin/bash

echo "idejonajelszo" > fall.sql
cat $1 >> fall.sql

/home/itep/Programok/Oracle/sqlcl/bin/sql DB18_VARPET@//dboracle.itk.ppke.hu:1521/lab.itk.ppke.hu <fall.sql

rm fall.sql
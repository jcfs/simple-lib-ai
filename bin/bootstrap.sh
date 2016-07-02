#!/bin/bash

echo "Please type the project name: "
read project
echo -e "Creating new project [ $project ]"

project_upper=`echo $project | awk '{print toupper($0)}'`
project_lower=`echo $project | awk '{print tolower($0)}'`

echo -e "Project dir name: $project_lower"

cd test/
make clean > /dev/null
cp -R bootstrap $project_lower
cd $project_lower

rename "s/BootStrap/$project/" *
rename "s/bootstrap/$project_lower/" *

sed -i "s/BootStrap/$project/g" *
sed -i "s/bootstrap/$project_lower/g" *
sed -i "s/BOOTSTRAP/$project_upper/g" *

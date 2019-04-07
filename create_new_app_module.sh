#!/bin/sh

DIR=$(dirname "$(readlink -f "$0")")

MODULE_NAME=$1


if [ -d $DIR/mflower/${MODULE_NAME} ]; then
	echo "The module already exists"
	exit 1
fi


cp -r $DIR/templates/template_app_module/ $DIR/mflower/

mv $DIR/mflower/template_app_module/ $DIR/mflower/${MODULE_NAME}

mv $DIR/mflower/${MODULE_NAME}/include/mflower/MODULE_NAME $DIR/mflower/${MODULE_NAME}/include/mflower/${MODULE_NAME}

find $DIR/mflower/${MODULE_NAME} -type f -exec sed -i "s/MODULE_NAME/${MODULE_NAME}/g" {} \;


LINE="add_subdirectory(${MODULE_NAME})"
if [ ! $(grep $LINE $DIR/mflower/CMakeLists.txt) ]; then
	echo ${LINE} >> $DIR/mflower/CMakeLists.txt
fi


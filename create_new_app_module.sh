#!/bin/sh

DIR=$(dirname "$(readlink -f "$0")")

MODULE_NAME=$1


if [ -d $DIR/mflower-dev/${MODULE_NAME} ]; then
	echo "The module already exists"
	exit 1
fi


cp -r $DIR/templates/template_app_module/ $DIR/mflower-dev/

mv $DIR/mflower-dev/template_app_module/ $DIR/mflower-dev/${MODULE_NAME}

mv $DIR/mflower-dev/${MODULE_NAME}/include/mflower-dev/MODULE_NAME $DIR/mflower-dev/${MODULE_NAME}/include/mflower-dev/${MODULE_NAME}

find $DIR/mflower-dev/${MODULE_NAME} -type f -exec sed -i "s/MODULE_NAME/${MODULE_NAME}/g" {} \;


LINE="add_subdirectory(${MODULE_NAME})"
if [ ! $(grep $LINE $DIR/mflower-dev/CMakeLists.txt) ]; then
	echo ${LINE} >> $DIR/mflower-dev/CMakeLists.txt
fi


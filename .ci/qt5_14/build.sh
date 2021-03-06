#!/bin/bash

mkdir /usr/src/qgis/build
cd /usr/src/qgis/build || exit -1

CLANG_WARNINGS="-Wrange-loop-construct"

cmake -GNinja \
 -DWITH_QUICK=OFF \
 -DWITH_3D=ON \
 -DWITH_STAGED_PLUGINS=ON \
 -DWITH_GRASS=OFF \
 -DSUPPRESS_QT_WARNINGS=ON \
 -DENABLE_MODELTEST=ON \
 -DENABLE_PGTEST=ON \
 -DENABLE_SAGA_TESTS=ON \
 -DENABLE_MSSQLTEST=ON \
 -DWITH_QSPATIALITE=OFF \
 -DWITH_QWTPOLAR=OFF \
 -DWITH_APIDOC=OFF \
 -DWITH_ASTYLE=OFF \
 -DWITH_DESKTOP=ON \
 -DWITH_BINDINGS=ON \
 -DWITH_SERVER=ON \
 -DWITH_ORACLE=OFF \
 -DDISABLE_DEPRECATED=ON \
 -DCXX_EXTRA_FLAGS="${CLANG_WARNINGS}" \
 -DCMAKE_C_COMPILER=/bin/clang \
 -DCMAKE_CXX_COMPILER=/bin/clang++ \
 -DADD_CLAZY_CHECKS=ON \
 -DWERROR=TRUE \
 ..

ninja

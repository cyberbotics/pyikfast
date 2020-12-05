#!/bin/bash

BASE=${1}
EFFECTOR=${2}
EXTENSION=${3}

# Generate inverse kinematics files
cp /output/robot.urdf robot.urdf
source /opt/ros/kinetic/local_setup.bash
rosrun collada_urdf urdf_to_collada robot.urdf robot.dae
cat <<EOT >> robot.xml
<robot file="robot.dae">
  <Manipulator name="robot_workspace">
    <base>${BASE}</base>
    <effector>${EFFECTOR}</effector>
  </Manipulator>
</robot>
EOT
openrave.py --database inversekinematics --robot=robot.xml --iktype=transform6d --iktests=100

# Grap Python bind and `ikfast` generated files
cp /src/* /output
cp $(find -name '*.cpp') /output/ikfast_robot.cpp
cp $(find -name 'ikfast.h') /output/ikfast.h
sed -i "s/\[put_extension\]/${EXTENSION}/g" /output/setup.py
sed -i 's!#define IKFAST_COMPILE!// #define IKFAST_COMPILE!g' /output/ikfast_robot.cpp
sed -i 's!IKFAST_COMPILE_ASSERT(IKFAST!// IKFAST_COMPILE_ASSERT(IKFAST!g' /output/ikfast_robot.cpp
sed -i 's/isnan _isnan/isnan std::isnan/g' /output/ikfast_robot.cpp
sed -i 's/isinf _isinf/isinf std::isinf/g' /output/ikfast_robot.cpp
sed -i "s/\[put_extension\]/${EXTENSION}/g" /output/pyikfast.cpp
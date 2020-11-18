Work in progress!

Export URDF from Webots:
```
(right click on the robot in scene tree) > Export > (name it robot.urdf) > Save
```

Prepare *.dae and *.xml for ikfast:
```bash
[ -z "${NAME}" ] && "NAME is missing!"
[ -z "${EFFECTOR}" ] && "EFFECTOR is missing!"
[ -z "${BASE}" ] && "BASE is missing!"

sudo apt install -y ros-noetic-collada-urdf
source /opt/ros/noetic/local_setup.bash
rosrun collada_urdf urdf_to_collada ${NAME}.urdf ${NAME}.dae

cat <<EOT >> ${NAME}.xml
<robot file="${NAME}.dae">
        <Manipulator name="${NAME}_workspace">
          <base>${BASE}</base>
          <effector>${EFFECTOR}</effector>
        </Manipulator>
</robot>
EOT

docker run -v $PWD:/root -it hamzamerzic/openrave bash -c "openrave.py --database inversekinematics --robot=${NAME}.xml --iktype=transform6d --iktests=100"
```

Move `setup.py` and `ikfast.cpp` to the output directory and execute:
```bash
pip3 install .
```

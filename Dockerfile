FROM hamzamerzic/openrave

RUN apt-get -y update && \
  apt-get -y install lsb-core && \
  sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list' && \
  apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654 && \
  curl -sSL 'http://keyserver.ubuntu.com/pks/lookup?op=get&search=0xC1CF6E31E6BADE8868B172B4F42ED6FBAB17C654' | apt-key add - && \
  apt-get -y update && \
  apt install -y ros-kinetic-collada-urdf ros-kinetic-rosbash

RUN pip install lxml
COPY entrypoint.bash /entrypoint.bash
COPY round_collada_numbers.py /round_collada_numbers.py
COPY src /src
ENTRYPOINT ["/entrypoint.bash"]

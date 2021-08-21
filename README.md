# Binning ROS Node for image topic 



This simple node is capable of binning image topic and publish it under new name. Currently code doesn't accept any input arguments and it is programed to shrink image resolution exactly by half. You are welcome to make any adaptation for your use case.
It is important to note that the node is working on mono black and white 8 bit raw image topics only, therefore it might be required to use image_transport node before and do some adjustments if color required.



## Usage



Expected input topic name: **/camera_decompressed/image_raw**



Ouput topic name: **/camera/image_raw**



## Installation



Simple download this repository into your catkin workspace, under /src folder and run catkin_make or equivalent build command used for your workspace.

```
git clone https://github.com/tau-adl/image_binning_ros_node.git
cd ..
catkin_make
```

## Usage

Run with rosrun command, don't forget to source your shell before:
```
source ./devel/setup.bash
rosrun binning binning_node
``` 

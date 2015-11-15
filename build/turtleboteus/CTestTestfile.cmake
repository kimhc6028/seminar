# CMake generated Testfile for 
# Source directory: /home/mech-user/semi/src/robot-programming/turtleboteus
# Build directory: /home/mech-user/semi/build/turtleboteus
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
ADD_TEST(_ctest_turtleboteus_rostest_test_test-turtlebot.test "/home/mech-user/semi/build/turtleboteus/catkin_generated/env_cached.sh" "/usr/bin/python" "/opt/ros/indigo/share/catkin/cmake/test/run_tests.py" "/home/mech-user/semi/build/turtleboteus/test_results/turtleboteus/rostest-test_test-turtlebot.xml" "--return-code" "/opt/ros/indigo/share/rostest/cmake/../../../bin/rostest --pkgdir=/home/mech-user/semi/src/robot-programming/turtleboteus --package=turtleboteus --results-filename test_test-turtlebot.xml --results-base-dir \"/home/mech-user/semi/build/turtleboteus/test_results\" /home/mech-user/semi/src/robot-programming/turtleboteus/test/test-turtlebot.test ")
SUBDIRS(gtest)

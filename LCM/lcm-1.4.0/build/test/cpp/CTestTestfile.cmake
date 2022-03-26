# CMake generated Testfile for 
# Source directory: /home/urop/lcm-1.4.0/test/cpp
# Build directory: /home/urop/lcm-1.4.0/build/test/cpp
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(CPP::memq_test "/home/urop/lcm-1.4.0/build/test/cpp/test-cpp-memq_test")
add_test(CPP::client_server "/home/urop/miniconda3/bin/python" "/home/urop/lcm-1.4.0/test/cpp/../run_client_server_test.py" "/home/urop/lcm-1.4.0/build/test/c/test-c-server" "/home/urop/lcm-1.4.0/build/test/cpp/test-cpp-client")

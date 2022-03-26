# CMake generated Testfile for 
# Source directory: /home/urop/lcm-1.4.0/test/c
# Build directory: /home/urop/lcm-1.4.0/build/test/c
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(C::memq_test "/home/urop/lcm-1.4.0/build/test/c/test-c-memq_test")
add_test(C::eventlog_test "/home/urop/lcm-1.4.0/build/test/c/test-c-eventlog_test")
add_test(C::client_server "/home/urop/miniconda3/bin/python" "/home/urop/lcm-1.4.0/test/c/../run_client_server_test.py" "/home/urop/lcm-1.4.0/build/test/c/test-c-server" "/home/urop/lcm-1.4.0/build/test/c/test-c-client")

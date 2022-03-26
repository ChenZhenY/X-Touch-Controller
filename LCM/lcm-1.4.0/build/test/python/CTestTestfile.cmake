# CMake generated Testfile for 
# Source directory: /home/urop/lcm-1.4.0/test/python
# Build directory: /home/urop/lcm-1.4.0/build/test/python
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(Python::bool_test "/usr/bin/cmake" "-E" "env" "PYTHONPATH=/home/urop/lcm-1.4.0/build/test/types:/home/urop/lcm-1.4.0/build/lib/python3.9/site-packages" "/home/urop/miniconda3/bin/python" "/home/urop/lcm-1.4.0/test/python/bool_test.py")
add_test(Python::byte_array_test "/usr/bin/cmake" "-E" "env" "PYTHONPATH=/home/urop/lcm-1.4.0/build/test/types:/home/urop/lcm-1.4.0/build/lib/python3.9/site-packages" "/home/urop/miniconda3/bin/python" "/home/urop/lcm-1.4.0/test/python/byte_array_test.py")
add_test(Python::lcm_file_test "/usr/bin/cmake" "-E" "env" "PYTHONPATH=/home/urop/lcm-1.4.0/build/test/types:/home/urop/lcm-1.4.0/build/lib/python3.9/site-packages" "/home/urop/miniconda3/bin/python" "/home/urop/lcm-1.4.0/test/python/lcm_file_test.py")
add_test(Python::lcm_memq_test "/usr/bin/cmake" "-E" "env" "PYTHONPATH=/home/urop/lcm-1.4.0/build/test/types:/home/urop/lcm-1.4.0/build/lib/python3.9/site-packages" "/home/urop/miniconda3/bin/python" "/home/urop/lcm-1.4.0/test/python/lcm_memq_test.py")
add_test(Python::lcm_thread_test "/usr/bin/cmake" "-E" "env" "PYTHONPATH=/home/urop/lcm-1.4.0/build/test/types:/home/urop/lcm-1.4.0/build/lib/python3.9/site-packages" "/home/urop/miniconda3/bin/python" "/home/urop/lcm-1.4.0/test/python/lcm_thread_test.py")
add_test(Python::client_server "/usr/bin/cmake" "-E" "env" "PYTHONPATH=/home/urop/lcm-1.4.0/build/test/types:/home/urop/lcm-1.4.0/build/lib/python3.9/site-packages" "/home/urop/miniconda3/bin/python" "/home/urop/lcm-1.4.0/test/run_client_server_test.py" "/home/urop/lcm-1.4.0/build/test/c/test-c-server" "/home/urop/miniconda3/bin/python" "/home/urop/lcm-1.4.0/test/python/client.py")

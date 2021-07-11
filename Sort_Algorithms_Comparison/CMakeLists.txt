project(Semestralni_Prace)
cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 14)
add_executable(Semestralni_Prace main.cpp sort.hpp sortings/quickSort.cpp generator.hpp message.hpp sortings/bubbleSort.cpp sortings/mergeSort.cpp sortings/selectionSort.cpp sortings/countingSort.cpp sortings/insertionSort.cpp helpers.cpp)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(Semestralni_Prace Threads::Threads)

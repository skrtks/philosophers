cmake_minimum_required(VERSION 3.17)
project(philosophers C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-Wall -Werror -Wextra")

add_subdirectory(philo_one)
ADD_SUBDIRECTORY(philo_two)
add_subdirectory(philo_three)
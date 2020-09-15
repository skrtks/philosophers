cmake_minimum_required(VERSION 3.17)
project(philo_one C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-Wall -Werror -Wextra")

add_executable(philo_one main.c philosophers.h ft_strtoll.c ft_strtoll.h mutex.c utils.c philosophers.c utils_2.c)
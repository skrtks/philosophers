cmake_minimum_required(VERSION 3.17)
project(philo_two C)

set(CMAKE_C_STANDARD 99)

add_executable(philo_two main.c ft_strtoll.c
        ft_strtoll.h
        semaphore.c
        philosophers.c
        philosophers.h
        utils.c utils_2.c)
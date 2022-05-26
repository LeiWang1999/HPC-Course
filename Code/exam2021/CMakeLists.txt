add_executable(2021-exam1 exam1.c)
find_package(MPI) #make it REQUIRED, if you want
include_directories(SYSTEM ${MPI_INCLUDE_PATH})

target_link_libraries(2021-exam1
        PUBLIC
        ${MPI_C_LIBRARIES})

add_executable(2021-exam2 exam2.c)
target_link_libraries(2021-exam2
        PUBLIC
        ${MPI_C_LIBRARIES})

add_executable(2021-exam3 exam3.c)
target_link_libraries(2021-exam3
        PUBLIC
        ${MPI_C_LIBRARIES})

add_executable(2021-exam4 exam4.c)
target_link_libraries(2021-exam4
        PUBLIC
        ${MPI_C_LIBRARIES})

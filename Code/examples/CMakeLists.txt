find_package(MPI REQUIRED)

add_executable(0.helloworld 0.helloworld.cpp)
target_link_libraries(0.helloworld
        PUBLIC
        MPI::MPI_CXX
)

add_executable(1.messagePassing 1.messagePassing.cpp)
target_link_libraries(1.messagePassing
        PUBLIC
        MPI::MPI_CXX)

add_executable(2.costomizeDataType 2.costomizeDataType.cpp)
target_link_libraries(2.costomizeDataType
        PUBLIC
        MPI::MPI_CXX)

add_executable(3.timer 3.timer.cpp)
target_link_libraries(3.timer
        PUBLIC
        MPI::MPI_CXX)

add_executable(4.relaypassing 4.relaypassing.cpp)
target_link_libraries(4.relaypassing
        PUBLIC
        MPI::MPI_CXX)

add_executable(5.Jacobi_1 5.Jacobi_1.cpp)
target_link_libraries(5.Jacobi_1
        PUBLIC
        MPI::MPI_CXX)

add_executable(6.calculatePi 6.calculatePi.cpp)
target_link_libraries(6.calculatePi
        PUBLIC
        MPI::MPI_CXX)

find_package(MPI) #make it REQUIRED, if you want
include_directories(SYSTEM ${MPI_INCLUDE_PATH})

add_executable(triangleTransfer triangleTransfer.c)
target_link_libraries(triangleTransfer
        PUBLIC
        ${MPI_C_LIBRARIES})

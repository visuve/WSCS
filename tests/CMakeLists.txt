add_executable(wscs_tests "main.cpp")
target_link_libraries(wscs_tests LINK_PRIVATE wshf2 wsbc512 wssc8)

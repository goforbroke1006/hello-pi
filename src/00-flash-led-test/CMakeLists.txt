project(00-flash-led-test)

add_executable(${PROJECT_NAME} main.cpp ../myGPIO.h)

#target_link_libraries(${PROJECT_NAME} wiringPi)

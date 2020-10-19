idf_component_register(SRCS "app_main.c"
                            "core/main.c"
                            "core/lib.c"
                            "core/ESP32/basics.c"
                            "core/ESP32/acoustic/acoustic.c"
                            "core/ESP32/bh1750/bh1750.c"
                            "core/ESP32/mpu6050/mpu6050.c"
                            "core/ESP32/bme280/bme280.c"
                            "core/ESP32/gpio/gpio.c"
                            "core/ESP32/http-socket/http-socket.c"
                            "core/ESP32/tIntern/tIntern.c"
                    INCLUDE_DIRS ".")
                    
add_definitions(-DESP32 -DHTTP -DSHELLPRINT)

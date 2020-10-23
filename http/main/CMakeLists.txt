idf_component_register(SRCS "app_main.c"
                            "main.c"
                            "core/lib.c"
                            "core/ESP32/basics.c"
							"core/ESP32/wifi/wifi.c"
                            "core/ESP32/peripherals/gpio/gpio.c"
                            "core/ESP32/peripherals/i2c/i2c.c"
                            "core/ESP32/peripherals/spi/spi.c"
                            "core/ESP32/protocols/http/http.c"
                            "core/ESP32/sensors/internal/internal.c"
			     			"core/ESP32/sensors/bme280/bme280.c"
			     			"core/ESP32/sensors/mpu6050/mpu6050.c"
			     			"core/ESP32/sensors/bh1750/bh1750.c"
                            "core/ESP32/sensors/acoustic/acoustic.c"
                    INCLUDE_DIRS ".")
                    
add_definitions(-DESP32 -DMICROCONTROLLER -DHTTP -DSHELLPRINT)

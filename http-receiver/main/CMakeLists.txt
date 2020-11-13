idf_component_register(SRCS "app_main.c"
                            "main.c"
                            "core/lib.c"
                            "core/json/decoder-i2t-json.c"
                            "core/ESP32/basics.c"
							"core/ESP32/wifi/wifi.c"
							"core/ESP32/output/relay/relay.c"
                            "core/ESP32/peripherals/gpio/gpio.c"
                            "core/ESP32/peripherals/i2c/i2c.c"
                            "core/ESP32/peripherals/spi/spi.c"
                            "core/ESP32/protocols/http/http.c"
                    INCLUDE_DIRS ".")
                    
add_definitions(-DESP32 -DMICROCONTROLLER -DHTTP -DSHELLPRINT -DEXAMPLE)

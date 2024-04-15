#include <iostream>
#include <string>

#include "pico/stdlib.h"

#include "gcode.h"

#define EXPECT_EQUAL(a, b) if ((a) != (b)) { std::cout << "\n" << a << " != " << b << std::endl; test_ok = false; }

void gcodeBasicTest()
{
    std::string test_name("gcodeBasicTest");
    bool test_ok = true;

    std::cout << "= " << test_name << " =";

    // PREPARE
    std::string input("G0 X123 Y123");

    // ACT
    GCodeLineParser parser(input);
    bool parsing_successful = parser.parse();
    GCode gcode = parser.getGCode();

    // ASSERT
    EXPECT_EQUAL(parsing_successful, true)
    EXPECT_EQUAL(gcode.type, 'G')
    EXPECT_EQUAL(gcode.number, 0)
    EXPECT_EQUAL(gcode.x, 123.0)
    EXPECT_EQUAL(gcode.y, 123.0)
    EXPECT_EQUAL(gcode.i, 0.0)
    EXPECT_EQUAL(gcode.j, 0.1)

    if (test_ok)
        std::cout << " => OK";
    else
        std::cout << "\n";
}


int main()
{
    stdio_init_all();
    sleep_ms(2000);  // wait for uart...

    
    while (true) {
        gcodeBasicTest();
        sleep_ms(1000);
    }
}

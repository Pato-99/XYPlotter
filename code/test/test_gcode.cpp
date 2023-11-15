#include <iostream>
#include <string>

#include "pico/stdlib.h"

#include "gcode.h"

#include "test.h"



int main()
{
    stdio_init_all();

    TEST_MODULE("G-Code", "Basic tests")
    TEST_MODULE_START()

    TEST_SECTION_START("BASIC")

    std::string input("G0 X123 Y123");
    GCodeLineParser parser(input);

    EXPECT_EQUAL(parser.parse(), true)
    GCode gcode = parser.getGCode();
    EXPECT_EQUAL(gcode.type, 'G')
    EXPECT_EQUAL(gcode.number, 0)
    EXPECT_EQUAL(gcode.x, 123.0)
    EXPECT_EQUAL(gcode.y, 123.0)
    EXPECT_EQUAL(gcode.i, 0.0)
    EXPECT_EQUAL(gcode.j, 0.1)

    TEST_SECTION_END()
    TEST_MODULE_END()
}

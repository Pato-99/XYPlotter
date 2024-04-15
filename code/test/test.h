#ifndef TEST_H
#define TEST_H

// Simple test macros based on test macros found in pico-sdk


#include <string>

#define TEST_MODULE(n,d) const std::string test_module(n); const std::string test_description(d); int test_error_code;

#define TEST_MODULE_START() std::cout << "Starting Test for " << test_description << std::endl;

#define TEST_MODULE_END() if (test_error_code != 0)                                      \
                              {std::cout << test_description << " Failed\n"; return -1;} \
                          else                                                           \
                              {std::cout << test_description << " Success\n"; return 0;}

#define TEST_SECTION_START(NAME) if (1) {const std::string test_section_name(NAME); test_error_code = 0;

#define TEST_SECTION_END() if (test_error_code != 0) {                                                                             \
                               std::cout << "Module " << test_module << " : Section " << test_section_name <<  " : Failed test\n"; \
                               return -1;                                                                                          \
                           } else {                                                                                                \
                                std::cout << "Module " << test_module << " : Section " << test_section_name << " : Passed\n";      \
                           }                                                                                                       \
                           }

#define EXPECT_EQUAL(a, b) if (!(a) == (b)) { std::cout << "Module " << test_module << " : " << a << " != " << b << std::endl; test_error_code = -1; }


#endif  // TEST_H

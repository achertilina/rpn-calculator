find_package(GTest REQUIRED)

# Создаем тестовый исполняемый файл
add_executable(rpn_tests test_rpn.cpp ../src/rpn.cpp)

# Подключаем директории с заголовками
target_include_directories(rpn_tests PRIVATE ../include)

# Линкуем с GoogleTest
target_link_libraries(rpn_tests GTest::gtest GTest::gtest_main)

# Добавляем тест в CTest
add_test(NAME RPN_Tests COMMAND rpn_tests)
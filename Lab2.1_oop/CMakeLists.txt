# CMakeList.txt: проект CMake для Lab2.1_oop; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта.
add_executable (Lab2.1_oop "lab2.1_main.cpp" "message_queue/Message_Queue.h" "message_queue/Message_Queue.cpp" "message/Message.h" "message/Message.cpp" "input/input_funcs.h" "input/input_funcs.cpp" "message_queue_list/Message_Queue_List.cpp" "message_queue_list/Message_Queue_List.h" "menu_funcs/menu_funcs.cpp" "menu_funcs/menu_funcs.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Lab2.1_oop PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.

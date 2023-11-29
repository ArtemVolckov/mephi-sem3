# ищем в системе пакет Catch2 для тестирования
# необходимо предварительно установить через пакетный менеджер (напр. sudo apt install catch2),
# или скачать из гит-репозитория https://github.com/catchorg/Catch2
find_package(Catch2 2 REQUIRED)

add_compile_options(--coverage)
add_link_options(--coverage)
set(DATABASE_SOURCE
    databasehost.cpp
)

add_library(Database STATIC
    ${DATABASE_SOURCE}
)

target_link_libraries(Database PRIVATE
    Qt5::Core
    Qt5::Quick
    Qt5::Sql
    Models
)

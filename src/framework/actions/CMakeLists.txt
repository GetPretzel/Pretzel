set(ACTIONS_SOURCES
    actioncontroller.cpp
    actioncontroller.h
)

add_library(Actions STATIC
    ${ACTIONS_SOURCES}
)

target_link_libraries(Actions PRIVATE
    Qt5::Core
    Qt5::Widgets
)

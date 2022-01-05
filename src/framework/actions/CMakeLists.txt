set(ACTIONS_SOURCES
    actioncontroller.cpp
    actioncontroller.h
    # papplication.cpp
)

add_library(Actions STATIC
    ${ACTIONS_SOURCES}
)

target_link_libraries(Actions PRIVATE
    Qt5::Core
    # Qt5::Gui
    Qt5::Quick
)

set(ACTIONS_SOURCES
    actioncontroller.cpp
    actioncontroller.h
)

set(ACTIONS_RESOURCES
    actions.qrc
)

add_library(Actions STATIC
    ${ACTIONS_SOURCES}
    ${ACTIONS_RESOURCES}
)

target_link_libraries(Actions PRIVATE
    Qt5::Core
    Qt5::Quick
)

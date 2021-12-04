add_subdirectory(ui)

set(SOURCES ${SOURCES}
    main.cpp
    ui/register/register.cpp
)

set(RESOURCES ${RESOURCES}
    ui/ui.qrc
)

add_executable(Pretzel
    ${SOURCES}
    ${RESOURCES}
)

target_link_libraries(Pretzel PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Quick
    Qt5::Sql
    KDAB::kddockwidgets
)

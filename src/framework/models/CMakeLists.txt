set(MODELS_SOURCE
    profilesmodel.cpp
    profilesmodel.h
)

add_library(Models STATIC
    ${MODELS_SOURCE}
)

target_link_libraries(Models PRIVATE
    Qt5::Core
    Qt5::Quick
)


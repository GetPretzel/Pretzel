set(MODELS_SOURCE
    itemsmodel.cpp
    itemsmodel.h
    itempropertiesmodel.cpp
    itempropertiesmodel.h
    profilesmodel.cpp
    profilesmodel.h
    propertiesmodel.cpp
    propertiesmodel.h
    stockmodel.cpp
    stockmodel.h
)

add_library(Models STATIC
    ${MODELS_SOURCE}
)

target_link_libraries(Models PRIVATE
    Qt5::Core
    Qt5::Quick
    Qt5::Sql
    Database
)


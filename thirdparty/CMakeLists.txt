set(KDDockWidgets_STATIC ON CACHE BOOL "Build static versions of the libraries" FORCE)
set(KDDockWidgets_QTQUICK ON CACHE BOOL "Build for QtQuick instead of QtWidgets" FORCE)
set(KDDockWidgets_EXAMPLES OFF CACHE BOOL "Build the examples" FORCE)
add_subdirectory(KDDockWidgets)

add_subdirectory(SortFilterProxyModel)

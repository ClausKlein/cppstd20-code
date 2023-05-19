set(cxx_sources
    #XXX always40.cpp
    #XXX always41.cpp
    #XXX always42.cpp
    #XXX always42inherit.cpp
    #TODO(CK): color.cpp
    formatbool.cpp formatgerman.cpp formatperf.cpp
)

add_tests(cxx_sources)

target_link_libraries(formatbool PRIVATE fmt::fmt)
target_link_libraries(formatgerman PRIVATE fmt::fmt)
target_link_libraries(formatperf PRIVATE fmt::fmt)

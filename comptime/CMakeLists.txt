set(cxx_sources
    comptimestring.cpp #NOTE: std::format used
    consteval1.cpp
    #XXX consteval2.cpp
    constinit.cpp
    #FIXME fiasco.cpp
    isconsteval.cpp
    mergevalues.cpp
    mergevaluessz.cpp
    #XXX returnvector.cpp
    #TODO no main: truth.cpp
    vector.cpp
)

add_tests(cxx_sources)

target_link_libraries(comptimestring PRIVATE fmt::fmt)

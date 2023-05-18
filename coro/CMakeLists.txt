set(cxx_sources
    awaiter.cpp
    coreturn.cpp
    coro.cpp
    coro2.cpp
    #syncstream coroasync1.cpp
    #syncstream coroasync2.cpp
    #syncstream coroasyncdebug.cpp
    corocoro.cpp
    corocorosub.cpp
    coromem.cpp
    #memory_resource coromempmr.cpp
    coroprio.cpp
    coroprio2.cpp
    cororange.cpp
    #XXX cororef.cpp
    corotrace.cpp
    corotraits.cpp
    coyield.cpp
    coyieldback.cpp
)

add_tests(cxx_sources)

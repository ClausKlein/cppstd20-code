set(cxx_sources
    #jthread atomicref.cpp
    #jthread atomicshared.cpp
    #jthread atomicticket.cpp
    #jthread atomicwait.cpp
    #jthread atomicweak.cpp
    #jthread barrier.cpp
    #jthread barrierstop.cpp
    #AddressSanitizer issues! begin.cpp
    #TODO bitops16.cpp
    #TODO bitops8.cpp
    #TODO chrono1.cpp
    #TODO chrono2.cpp
    #TODO chrono3.cpp
    #TODO chrono4.cpp
    #TODO chronoattr.cpp
    #TODO chronoclocks.cpp
    #TODO chronoconv.cpp
    #TODO chronocst.cpp
    #TODO chronoparse.cpp
    #TODO chronotz.cpp
    #jthread concstream.cpp
    #jthread latch.cpp
    #jthread latchready.cpp
    #XXX lexicothreeway.cpp
    minmax.cpp
    #TODO offsetzone.cpp
    #jthread semaphore.cpp
    #jthread semaphorenotify.cpp
    shift.cpp
    sourceloc.cpp
    spandyn.cpp
    spanfix.cpp
    spanview.cpp
    #stop_token stop.cpp
    #jthread stopcv.cpp
    swap.cpp
    #jthread syncfilestream.cpp
    #jthread syncfilestream2.cpp
    #jthread syncstream.cpp
    #execution unseq.cpp
)

add_tests(cxx_sources)

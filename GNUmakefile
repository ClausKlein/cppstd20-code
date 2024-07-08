export CC=gcc-14
export CXX=g++-14

.PHONY: all configure build test install format clean distclean
all: # test
	cmake --workflow --preset Release --fresh

configure:
	cmake --preset Release

build: configure
	cmake --build --preset Release

test: build
	ctest --preset Release

install: test
	cmake --build --preset Release --target install

format:
	git clang-format
	find . \( -type d -name build -o -name stagedir -o -name out \) -prune -o \( -name '*.cmake' -o -name '*.cmake.in' -o -name CMakeLists.txt \) -print > .cmakefiles.log
	cmake-format -i `cat .cmakefiles.log`
	ls -1 *.json >> .cmakefiles.log

clean:
	cmake --build --preset Release --target clean

distclean:
	rm -rf out .cmakefiles.log

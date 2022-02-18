# Makefile

LIBNAME=configpp
TARGET=lib$(LIBNAME).so

INCLUDEDIR=/usr/local/include/
LIBDIR=/usr/local/lib/

CXXSOURCE=$(wildcard *.cpp src/*.cpp)
HXXSOURCE=$(wildcard *.hpp src/*.hpp)
OBJ=$(CXXSOURCE:.cpp=.o)
 
CXX=g++
CXXFLAGS=-c -std=c++2a -m64

OPT_FLAGS =-O2
OPT_FLAGS +=-finline-functions
OPT_FLAGS +=-funroll-loops

all:$(LIBNAME) $(TARGET)

install: all
	cp $(HXXSOURCE) $(INCLUDEDIR)
	mv $(LIBNAME) $(INCLUDEDIR)
	mv $(TARGET) $(LIBDIR)

$(LIBNAME):
	echo "#include <${LIBNAME}.hpp>" > $(LIBNAME)

$(TARGET): $(LIBNAME).cpp $(HXXSOURCE)
	$(CXX) -fPIC -shared -o $@ $< $(CXXFLAGS) $(OPT_FLAGS)

%.o: %.cpp %.hpp
	$(CXX) -fPIC -o $@ $< $(CXXFLAGS) $(OPT_FLAGS)

clean:
	rm -rf *.o $(TARGET) $(LIBNAME) *~ src/*.o src/*~

uninstall:
	rm $(INCLUDEDIR)$(HXXSOURCE)
	rm $(INCLUDEDIR)$(LIBNAME)
	rm $(LIBDIR)$(TARGET)

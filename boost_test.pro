TEMPLATE = app
CONFIG -= qt
CONFIG -= app_bundle
CONFIG += console

CONFIG += c++17
QMAKE_CXXFLAGS += -std=c++17

SOURCES += \
    ./Simulation/analysis.cpp \
    ./test/main.cpp

HEADERS += \
    ./Simulation/analysis.hpp \
    ./Simulation/parameters.hpp \
    ./Simulation/random_thijs.hpp \
    ./Simulation/rndutils.hpp \
    ./Simulation/simulation.hpp \
    ./Simulation/voronoi.hpp \
    ./test/catch.h \
    ./Simulation/node_2d.hpp \
    ./Simulation/node_3d.hpp \
    ./Simulation/node_base.hpp

CONFIG += debug_and_release

TARGET=TEST.app

QMAKE_CXXFLAGS += --coverage
QMAKE_LFLAGS += --coverage

QMAKE_POST_LINK = rm -f "*.gcda"

CONFIG(debug, debug|release) {
  # gcov
  QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
}

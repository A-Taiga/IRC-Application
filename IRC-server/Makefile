CXX=g++
CXXFLAGS= -std=c++20 -Wunused $(shell fltk-config --cxxflags)
LDFLAGS= $(shell fltk-config --ldflags)
OBJ_DIR = obj/
VPATH= server:gui:$(OBJ_DIR)

objects = main.o mainWindow.o topBar.o tabs.o \
			serverTab.o bottomBar.o state.o
server_objects = server.o user.o



all: main

main: $(objects) $(server_objects)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)main.o: main.cpp mainWindow.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJ_DIR)mainWindow.o: mainWindow.cpp topBar.hpp tabs.hpp bottomBar.hpp server.hpp state.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJ_DIR)topBar.o: topBar.cpp 
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJ_DIR)tabs.o: tabs.cpp serverTab.hpp bottomBar.hpp server.hpp state.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJ_DIR)serverTab.o: serverTab.cpp bottomBar.hpp server.hpp state.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJ_DIR)bottomBar.o: bottomBar.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJ_DIR)state.o: state.cpp server.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJ_DIR)server.o: server.cpp user.hpp utility.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJ_DIR)user.o: user.cpp utility.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: run clean
run:
	./main

clean:
	-rm main *.o $(OBJ_DIR)*.o

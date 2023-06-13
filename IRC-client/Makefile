CXX=g++
CXXFLAGS= -std=c++20 -Wunused $(shell fltk-config --cxxflags)
LDFLAGS= $(shell fltk-config --ldflags)
OBJ_DIR = obj/
VPATH= client:gui:$(OBJ_DIR)

objects = main.o client.o mainWindow.o tempArea.o
client_objects = client.o msgHandler.o

.PHONY: clean

all: main
 
main: $(objects) $(client_objects)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
$(OBJ_DIR)main.o: main.cpp client.hpp msgHandler.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
$(OBJ_DIR)mainWindow.o: mainWindow.cpp tempArea.hpp msgHandler.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
$(OBJ_DIR)client.o: client.cpp utility.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
$(OBJ_DIR)tempArea.o: tempArea.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
$(OBJ_DIR)msgHandler.o: msgHandler.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	-rm main *.o $(OBJ_DIR)*.o

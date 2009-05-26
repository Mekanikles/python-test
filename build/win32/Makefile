SAGE=../../../..
HOME=$(SAGE)/Git/python-test
SOURCES=
SOURCES+=$(HOME)/src/SageModule.c
SOURCES+=$(HOME)/src/Physics.c
SOURCES+=$(HOME)/src/Main.c
SOURCES+=$(HOME)/src/Script.c
SOURCES+=$(HOME)/src/GameObject.c
SOURCES+=$(HOME)/src/Graphics.c
SOURCES+=$(HOME)/src/Logic.c
SOURCES+=$(HOME)/src/World.c
SOURCES+=$(HOME)/src/LinkedList.c
SOURCES+=$(HOME)/src/Timer.c
SOURCES+=$(HOME)/src/Engine.c


TARGET=$(HOME)/bin/python-test.exe

CXX     = gcc
CXXFLAGS =  -Wall #-O3 -ffast-math
ifeq ($(DEBUGSYMBOLS), YES)
	CXXFLAGS += -g
	CXXFLAGS += -DDEBUGSYMBOLS=YES
endif		

CFLAGS = -I$(HOME)/include -IC:/WINDOWS/include -I"$(PY_HOME)/include" -I"$(PY_HOME)/include/Stackless"

LIBS = C:/WINDOWS/lib/libglfw.a
LIBS += -lopengl32
LIBS += "$(PY_HOME)/libs/python26.lib"
LIBS += "$(PY_HOME)/python26.dll"

OBJECTS=$(SOURCES:.c=.o)

all: $(TARGET)

%.o: %.c
	$(CXX) $(CXXFLAGS) -c $(CFLAGS) $< -o $@

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(LFLAGS) $(LIBS) -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)


SAGE=../../../..
HOME=$(SAGE)/POC/PhysTest
SOURCES=
SOURCES+=$(HOME)/src/SageModule.c
SOURCES+=$(HOME)/src/Physics.c
SOURCES+=$(HOME)/src/Main.c
SOURCES+=$(HOME)/src/Script.c
SOURCES+=$(HOME)/src/GameObject.c
SOURCES+=$(HOME)/src/Graphics.c
SOURCES+=$(HOME)/src/Logic.c

TARGET=$(HOME)/bin/phystest.exe

CXX     = gcc
CXXFLAGS =  -Wall #-O3 -ffast-math
ifeq ($(DEBUGSYMBOLS), YES)
	CXXFLAGS += -g
	CXXFLAGS += -DDEBUGSYMBOLS=YES
endif		

CFLAGS = -I$(HOME)/include -I$(SAGE)/external/glfw/include -I"$(PY_HOME)/include"

LIBS = $(SAGE)/external/glfw/lib/win32/libglfw.a
LIBS += -lopengl32
LIBS += "$(PY_HOME)/libs/libpython26.a"

OBJECTS=$(SOURCES:.c=.o)

all: $(TARGET)

%.o: %.c
	$(CXX) $(CXXFLAGS) -c $(CFLAGS) $< -o $@

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(LFLAGS) $(LIBS) -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)


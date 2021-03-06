CXX       := g++
CXX_FLAGS := -std=c++17 -ggdb

BIN     := bin
SRC     := src
INCLUDE := include

LIBRARIES   :=
EXECUTABLE  := Poeisis.exe


all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp \
					$(SRC)/shapes/*.cpp \
					$(SRC)/rendering/*.cpp \
					$(SRC)/resource_handling/*.cpp \
					$(SRC)/game/particles/*.cpp \
					$(SRC)/game/scene/*.cpp \
					libs/glad.c
	$(CXX) $(CXX_FLAGS) -I$(SRC) $^ -o $@ $(LIBRARIES) -lGL -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor -lGLEW

clean:
	-rm $(BIN)/*
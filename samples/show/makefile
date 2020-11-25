.PHONY: clean dirs

OBJ = obj
SRC = ../../src
INCLUDE = ../../include

all: dirs ./show

./show: main.cpp \
	$(OBJ)/data_frame.o \
	$(OBJ)/parser.o \
	$(OBJ)/row.o
	clang++ -Wall -std=c++17 $^ -o $@ -I$(INCLUDE)

$(OBJ)/data_frame.o: $(SRC)/data_frame.cpp
	clang++ -Wall -std=c++17 -c $< -o $@

$(OBJ)/parser.o: $(SRC)/parser.cpp
	clang++ -Wall -std=c++17 -c $< -o $@

$(OBJ)/row.o: $(SRC)/row.cpp
	clang++ -Wall -std=c++17 -c $< -o $@

dirs:
	mkdir -p $(OBJ)

clean:
	rm -rf $(OBJ) ./show

state:
	wc $(SRC)/*

HEAD_DIR                = src/Headers
SRC_DIR                 = src/Sources
BIN_DIR                 = bin
OBJ_DIR                 = obj
MAIN                    = $(BIN_DIR)/main
DRIVER_CPP              = $(SRC_DIR)/driver.cpp
DRIVER_OBJ              = $(OBJ_DIR)/driver.o
GENERICISTREAMBUF_CPP   = $(SRC_DIR)/GenericIStreamBuf.cpp
GENERICISTREAMBUF_OBJ   = $(OBJ_DIR)/GenericIStreamBuf.o
GENERICISTREAM_CPP      = $(SRC_DIR)/GenericIStream.cpp
GENERICISTREAM_OBJ      = $(OBJ_DIR)/GenericIStream.o
GENERICOSTREAM_CPP      = $(SRC_DIR)/GenericOStream.cpp
GENERICOSTREAM_OBJ      = $(OBJ_DIR)/GenericOStream.o
GENERICSTREAMBUF_CPP    = $(SRC_DIR)/GenericStreamBuf.cpp
GENERICSTREAMBUF_OBJ    = $(OBJ_DIR)/GenericStreamBuf.o

OBJ_BUILD               = g++ -c -std=c++11 -Wall -I$(HEAD_DIR) -o $@ $^

main: $(MAIN)

$(MAIN): $(DRIVER_OBJ) $(GENERICISTREAMBUF_OBJ) $(GENERICISTREAM_OBJ) $(GENERICOSTREAM_OBJ) $(GENERICSTREAMBUF_OBJ) | $(BIN_DIR)
	g++ -o $@ $^

$(DRIVER_OBJ): $(DRIVER_CPP) | $(SRC_DIR)
	$(OBJ_BUILD)

$(GENERICISTREAMBUF_OBJ): $(GENERICISTREAMBUF_CPP) | $(SRC_DIR)
	$(OBJ_BUILD)

$(GENERICISTREAM_OBJ): $(GENERICISTREAM_CPP) | $(SRC_DIR)
	$(OBJ_BUILD)

$(GENERICOSTREAM_OBJ): $(GENERICOSTREAM_CPP) | $(SRC_DIR)
	$(OBJ_BUILD)

$(GENERICSTREAMBUF_OBJ): $(GENERICSTREAMBUF_CPP) | $(SRC_DIR)
	$(OBJ_BUILD)

#obj/*: src/Sources/* | obj
#	for i in $^; do\
#	    echo g++ -c -std=c++11 -Wall -I$(PWD)/src/Headers -o obj/$$(basename $${i%.*}).o $$i;\
#	    g++ -c -std=c++11 -Wall -I$(PWD)/src/Headers -o obj/$$(basename $${i%.*}).o $$i;\
#	done

$(BIN_DIR):
	mkdir -p $@

$(OBJ_DIR):
	mkdir -p $@

clean:
	rm -f $(BIN_DIR)/* $(OBJ_DIR)/*


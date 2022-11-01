CC = clang

OUT = mineblockz

SRC = src/*.c

CFLAGS ?=
LIBS ?=

.PHONY: all
all: $(OUT)

$(OUT): $(SRC)
	clang $(SRC) $(CFLAGS) $(LIBS) -o $(OUT)

.PHONY: clean
clean:
	rm -f $(OUT)
.PHONY: run
run: $(OUT)
	./$(OUT)
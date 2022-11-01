CC = gcc
CC_WINDOWS = x86_64-w64-mingw32-gcc

OUT_LINUX = mineblockz
OUT_WINDOWS = mineblockz.exe

SRC = src/*.c

CFLAGS_WINDOWS ?= -Llibs/windows/bin -Ilibs/windows/include
CFLAGS_LINUX ?= 

LIBS_LINUX ?= -lglfw -lGL -lglut -lGLEW
LIBS_WINDOWS ?= -lopengl32 -lglew32 -lglfw3dll

VERSION = v0.1-ALPHA

.PHONY: all
linux: $(OUT_LINUX)
.PHONY: windows
windows: $(OUT_WINDOWS)
.PHONY: winpkg
winpkg: $(OUT_WINDOWS)
	mkdir -p windows_packager
	cp $(OUT_WINDOWS) windows_packager
	cp libs/windows/bin/glew32.dll windows_packager
	cp libs/windows/bin/glfw3.dll windows_packager
	cp assets/ -r windows_packager/

	cd windows_packager && zip -r mineblockz-$(VERSION)-win32.zip $(OUT_WINDOWS) glew32.dll glfw3.dll assets/ && mv mineblockz-$(VERSION)-win32.zip ../
	rm -rf windows_packager

.PHONY: linuxpkg
linuxpkg: 
	zip -r mineblockz-$(VERSION)-linux.zip $(OUT_LINUX) assets/

$(OUT_LINUX): $(SRC)
	$(CC) $(SRC) $(CFLAGS_LINUX) $(LIBS_LINUX) -o $(OUT_LINUX)

$(OUT_WINDOWS): $(SRC)
	$(CC_WINDOWS) $(SRC) $(CFLAGS_WINDOWS) $(LIBS_WINDOWS) -o $(OUT_WINDOWS)

.PHONY: clean
clean:
	rm -f $(OUT)
.PHONY: run
run: $(OUT)
	./$(OUT)
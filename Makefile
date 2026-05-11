BUILD_DIR := build

.PHONY: all configure build clean run

all: build

configure:
	cmake -B $(BUILD_DIR) -S .

build: configure
	cmake --build $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

run: build
	./$(BUILD_DIR)/hello
.PHONY: all clean build

build:
	@if [ ! -d project ]; then \
		echo "Create project directory"; \
		mkdir project; \
	fi

	@echo "Build solution"
	cmake . -B project

clean:
	@if [ -d bin ]; then \
		echo "Clear bin directory"; \
		rm -rf bin/*; \
	fi

	@if [ -d project ]; then \
		echo "Clear project directory"; \
		rm -rf project/*; \
	fi

all: clean build
.PHONY: all clean build

all: clean build

clean:
	@if [ -d bin ]; then \
		echo "Clear bin directory"; \
		rm -rf bin/*; \
	fi
	@if [ -d project ]; then \
		echo "Clear project directory"; \
		rm -rf project/*; \
	else \
		echo "Create project directory"; \
		mkdir project; \
	fi

build:
	echo "Build solution"
	cmake . -B project

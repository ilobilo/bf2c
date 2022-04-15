CPP = clang++
TARGET = bf2c

CPPFLAGS = -std=gnu++20 -Wall -Werror -Wextra
MAINCPP = main.cpp

all: $(TARGET)

$(TARGET):
	$(CPP) $(CPPFLAGS) $(MAINCPP) -o $(TARGET)

clean:
	rm -f $(TARGET)
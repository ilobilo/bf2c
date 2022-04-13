CPP = clang++
OUT = bf2c

CPPFLAGS = -Wall -Werror -Wextra
MAINCPP = main.cpp

all: $(OUT)

$(OUT):
	$(CPP) $(CPPFLAGS) $(MAINCPP) -o $(OUT)

clean:
	rm $(OUT)
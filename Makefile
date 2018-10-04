CC       = g++
CXXFLAGS = -Wall -O2 -std=c++17 -I/include -Ithird_party/URLParser
LDFLAGS  = -lnana -lX11 -lpthread -lrt -ldl -lfreetype -lXft -lfontconfig -lasound -lpng -lstdc++fs

all: ksh-util

ksh-util: main.cpp gui/form.cpp
	$(CC) -o $@ $^ $(CXXFLAGS) $(LDFLAGS)

.PHONY: clean
clean:
	rm ksh-util
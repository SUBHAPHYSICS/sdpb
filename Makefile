SOURCES := $(wildcard src/*.cpp) $(wildcard mpack/*.cpp)
HEADERS := $(wildcard src/*.h) $(wildcard mpack/*.h)
OBJECTS := $(patsubst %.cpp,obj/%.o,$(SOURCES))
RESULT  = sdp-bootstrap

CC = g++
CFLAGS = -g -O2 -Wall -ansi -L/home/dsd/lib -I./mpack -I/home/dsd/include -I/home/dsd/include/boost -fopenmp -D___MPACK_BUILD_WITH_GMP___
RM = rm -f

.SUFFIXES: .cpp .o

$(RESULT): $(OBJECTS)
	$(CC) $(CFLAGS) -lgomp -lmblas_gmp -lmlapack_gmp -lgmp -lgmpxx -lmpc -lboost_serialization -lboost_system -lboost_filesystem -lboost_timer -lboost_program_options -o $@ $^

obj/%.o: %.cpp
	g++ $(CFLAGS) -c -o $@ $<

clean:
	$(RM) -r obj

obj:
	@mkdir -p $@/src
	@mkdir -p $@/mpack

foo:
	echo $(OBJECTS)

$(OBJECTS): $(HEADERS) | obj

CFLAGS += -MMD
-include $(OBJECTS:.o=.d)

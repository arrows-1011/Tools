CXX 		:= g++
CXXFLAGS	:= -Wall -O2 -std=c++11
TARGET 		:= api
SRCS		:= $(shell ls *.cpp)
HEADS		:= $(shell ls *.h)
OBJS		:= $(SRCS:.cpp=.o)
RESULT		:= result.txt
RM		:= rm -f

all: .cxx.o run clean

run: $(OBJS) $(HEADS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
	./$(TARGET) > $(RESULT)

.cxx.o: $(SRCS)
	$(CXX) $(CXXFLAGS) -c $(SRCS)

clean:
	$(RM) $(TARGET) $(OBJS)

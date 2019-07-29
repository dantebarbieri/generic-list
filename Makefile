CXX = g++
INCLUDES= -I./
CXXFLAGS = -g $(INCLUDES)
OBJ = Node.o
LINKFLAGS= -lcppunit

testlists: TestLists.cpp $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ TestLists.cpp $(OBJ) $(LINKFLAGS) $(LINKFLAGSLOG4) $(LIBLOG)

# Default compile

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

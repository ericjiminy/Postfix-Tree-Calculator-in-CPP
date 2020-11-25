# Eric Chun - jc2ppp - 10/5/20 - Makefile

CXX = clang++ $(CXXFLAGS)
CXXFLAGS = -Wall
DEBUG = -g
OBJECTS = TreeCalc.o TreeCalcTest.o TreeNode.o

a.out: $(OBJECTS)
	$(CXX) $(DEBUG) $(OBJECTS) -o a.out

TreeCalc.o: TreeCalc.cpp TreeCalc.h TreeNode.h
TreeCalcTest.o: TreeCalcTest.cpp TreeCalc.h TreeNode.h
TreeNode.o: TreeNode.cpp TreeNode.h

.PHONY: clean
clean:
	-rm -f *.o *~ a.out

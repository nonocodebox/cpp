FLAGS = -Wall -g

all: demo

demo: DemoMyMatrix

DemoMyMatrix:DemoMyMatrix.o Matrix.o RegMatrix.o SparseMatrix.o MyMatrix.o
	g++ $(FLAGS) DemoMyMatrix.o Matrix.o RegMatrix.o SparseMatrix.o MyMatrix.o -o DemoMyMatrix

DemoMyMatrix.o: DemoMyMatrix.cpp
	g++ $(FLAGS) -c DemoMyMatrix.cpp

SparseMatrix.o: SparseMatrix.cpp SparseMatrix.h Matrix.h Map.h
	g++ $(FLAGS) -c SparseMatrix.cpp
	
RegMatrix.o: RegMatrix.cpp RegMatrix.h Matrix.h Map.h
	g++ $(FLAGS) -c RegMatrix.cpp

Matrix.o: Matrix.cpp Matrix.h Map.h
	g++ $(FLAGS) -c Matrix.cpp

MyMatrix.o: MyMatrix.cpp MyMatrix.h SparseMatrix.h RegMatrix.h Matrix.h Map.h
	g++ $(FLAGS) -c MyMatrix.cpp
	
clean:
	rm -f *.o DemoMyMatrix
	
clean_tar:
	rm -f ex2.tar

# ==== tar ====
tar: ex2.tar

ex2.tar: Matrix.cpp Matrix.h SparseMatrix.cpp SparseMatrix.h RegMatrix.cpp RegMatrix.h MyMatrix.cpp \
		 MyMatrix.h Makefile
	tar cvf ex2.tar Matrix.cpp Matrix.h SparseMatrix.cpp SparseMatrix.h RegMatrix.cpp RegMatrix.h \
	MyMatrix.cpp MyMatrix.h Makefile

.PHONY: all demo clean clean_tar tar

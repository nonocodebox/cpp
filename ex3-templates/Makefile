FLAGS = -std=c++11 -Wall -g

all: GenericMatrixDriver

GenericMatrixDriver: GenericMatrixDriver.o Rational.o ExceptionBadSize.o ExceptionBadInput.o 
	g++ $(FLAGS) GenericMatrixDriver.o Rational.o ExceptionBadSize.o ExceptionBadInput.o -o GenericMatrixDriver

GenericMatrixDriver.o: GenericMatrixDriver.cpp Matrix.hpp Rational.h
	g++ $(FLAGS) -c GenericMatrixDriver.cpp

Rational.o: Rational.cpp Rational.h ExceptionBadInput.h
	g++ $(FLAGS) -c Rational.cpp

ExceptionBadSize.o: ExceptionBadSize.cpp ExceptionBadSize.h
	g++ $(FLAGS) -c ExceptionBadSize.cpp

ExceptionBadInput.o: ExceptionBadInput.cpp ExceptionBadInput.h
	g++ $(FLAGS) -c ExceptionBadInput.cpp

clean:
	rm -f *.o GenericMatrixDriver

# ==== tar ====
tar: ex3.tar

ex3.tar: Matrix.hpp ExceptionBadSize.h  ExceptionBadSize.cpp ExceptionBadInput.h ExceptionBadInput.cpp \
		 Rational.cpp Makefile
	tar cvf ex3.tar Matrix.hpp ExceptionBadSize.h  ExceptionBadSize.cpp ExceptionBadInput.h ExceptionBadInput.cpp \
		Rational.cpp Makefile

clean_tar:
	rm -f ex3.tar

.PHONY: all clean clean_tar tar

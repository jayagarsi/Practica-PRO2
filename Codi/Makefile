OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11

program.exe: program.o Cjt_especies.o Cjt_clusters.o Especie.o 
	g++ -o program.exe *.o 

Cjt_clusters.o: Cjt_clusters.cc Cjt_clusters.hh BinTree.hh
	g++ -c Cjt_clusters.cc $(OPCIONS)

Cjt_especies.o: Cjt_especies.cc Cjt_especies.hh Cjt_clusters.hh Especie.hh
	g++ -c Cjt_especies.cc $(OPCIONS) 

Especie.o: Especie.cc Especie.hh
	g++ -c Especie.cc $(OPCIONS)

program.o: program.cc Cjt_especies.hh Cjt_clusters.hh Especie.hh
	g++ -c program.cc $(OPCIONS) 

clean:
	rm -f *.o
	rm -f *.exe

compress:
	tar -cfv practica.tar program.cc *.hh *cc

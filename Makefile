__start__: etap2
	export LD_LIBRARY_PATH="./libs"; ./interp_etap2

etap2: obj interp_etap2 __plugin__
	@echo "Uruchom serwer graficzny, a potem:"
	@echo "  export LD_LIBRARY_PATH=\"./libs\"; ./interp_etap2"

obj:
	mkdir obj


__lines_for_space__:
	@echo
	@echo
	@echo
	@echo
	@echo


__plugin__:
	cd plugin; make

CPPFLAGS=-Wall -pedantic -std=c++17 -Iinc
LDFLAGS=-Wall

# Build mode (DEBUG=1 for -g -O0, else -O2)
DEBUG ?= 1
ifeq ($(DEBUG),1)
CPPFLAGS += -g -O0 -DDEBUG
LDFLAGS  += -g
else
CPPFLAGS += -O2 -DNDEBUG
endif




interp: obj/main.o obj/Cuboid.o obj/Scene.o obj/ComChannel.o obj/XMLReader.o
	g++ ${LDFLAGS} -o interp obj/main.o obj/Cuboid.o obj/Scene.o obj/ComChannel.o obj/XMLReader.o -ldl

obj/main.o: src/main.cpp inc/AbstractInterp4Command.hh inc/AbstractScene.hh\
            inc/AbstractComChannel.hh inc/Cuboid.hh inc/Scene.hh inc/ComChannel.hh inc/XMLReader.hh
	g++ -c ${CPPFLAGS} -o obj/main.o src/main.cpp

obj/Cuboid.o: src/Cuboid.cpp inc/Cuboid.hh inc/AbstractMobileObj.hh
	g++ -c ${CPPFLAGS} -o obj/Cuboid.o src/Cuboid.cpp

obj/Scene.o: src/Scene.cpp inc/Scene.hh inc/AbstractScene.hh
	g++ -c ${CPPFLAGS} -o obj/Scene.o src/Scene.cpp

obj/ComChannel.o: src/ComChannel.cpp inc/ComChannel.hh inc/AbstractComChannel.hh
	g++ -c ${CPPFLAGS} -o obj/ComChannel.o src/ComChannel.cpp

obj/XMLReader.o: src/XMLReader.cpp inc/XMLReader.hh
	g++ -c ${CPPFLAGS} -o obj/XMLReader.o src/XMLReader.cpp

interp_etap2: obj/main_etap2.o obj/Cuboid.o obj/Scene.o obj/ComChannel.o obj/XMLReader.o obj/CommandInterpreter.o
	g++ ${LDFLAGS} -rdynamic -o interp_etap2 obj/main_etap2.o obj/Cuboid.o obj/Scene.o obj/ComChannel.o obj/XMLReader.o obj/CommandInterpreter.o -ldl

.PHONY: debug release
debug:
	$(MAKE) clean
	$(MAKE) etap2 DEBUG=1

release:
	$(MAKE) clean
	$(MAKE) etap2 DEBUG=0

obj/main_etap2.o: src/main_etap2.cpp inc/Scene.hh inc/Cuboid.hh inc/ComChannel.hh inc/XMLReader.hh inc/CommandInterpreter.hh
	g++ -c ${CPPFLAGS} -o obj/main_etap2.o src/main_etap2.cpp

obj/CommandInterpreter.o: src/CommandInterpreter.cpp inc/CommandInterpreter.hh inc/AbstractInterp4Command.hh inc/AbstractScene.hh inc/AbstractComChannel.hh
	g++ -c ${CPPFLAGS} -o obj/CommandInterpreter.o src/CommandInterpreter.cpp

doc:
	cd dox; make

clean:
	rm -f obj/* interp interp_etap2 core*


clean_plugin:
	cd plugin; make clean

cleanall: clean
	cd plugin; make cleanall
	cd dox; make cleanall
	rm -f libs/*
	find . -name \*~ -print -exec rm {} \;

help:
	@echo
	@echo "  Lista podcelow dla polecenia make"
	@echo 
	@echo "        - (wywolanie bez specyfikacji celu) wymusza"
	@echo "          kompilacje i uruchomienie programu."
	@echo "  clean    - usuwa produkty kompilacji oraz program"
	@echo "  clean_plugin - usuwa plugin"
	@echo "  cleanall - wykonuje wszystkie operacje dla podcelu clean oraz clean_plugin"
	@echo "             oprocz tego usuwa wszystkie kopie (pliki, ktorych nazwa "
	@echo "             konczy sie znakiem ~)."
	@echo "  help  - wyswietla niniejszy komunikat"
	@echo
	@echo " Przykladowe wywolania dla poszczegolnych wariantow. "
	@echo "  make           # kompilacja i uruchomienie programu."
	@echo "  make clean     # usuwa produkty kompilacji."
	@echo
 

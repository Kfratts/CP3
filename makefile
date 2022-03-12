COURSE = cs240
SEMESTER = spring2022
CP_NUMBER = 3
LASTNAME = Fratto
GITUSERID = Kfratts
EXE = MarchMadness

REPODIR = ../$(COURSE)-$(SEMESTER)-cp$(CP_NUMBER)-$(GITUSERID)
TARFILE = CP$(CP_NUMBER)_$(LASTNAME)_$(USER)_$(GITUSERID).tar

FLAGS = -Wall -Wextra -g
# FLAGS = -Wall -O3
CC = g++
BIN = bin
OBJ = obj

all: $(BIN)/$(EXE)

$(BIN)/$(EXE): $(OBJ)/MarchMadness.o
	$(CC) $(FLAGS) $(OBJ)/MarchMadness.o -o $@

$(OBJ)/MarchMadness.o: MarchMadness.cpp
	$(CC) $(FLAGS) -c MarchMadness.cpp -o $@


tar:	clean
	tar cvvf $(TARFILE) $(REPODIR)
	gzip $(TARFILE)

clean:
	rm -f $(OBJ)/*.o $(BIN)/$(EXE) *.tar.gz

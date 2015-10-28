################################################################################
#
# Fichier makefile pour labo sur OpenMP.
#
# Auteurs: Guy Tremblay.
#   
# Cree a l'hiver 2011 pour le cours INF5171, pour les exercices initialement
# developpes a l'hiver 2009 pour le cours INF7235.
#
################################################################################



#
# Differentes variables pour execution via le makefile.
#
MAIN=pi
N=1000000
NBT=10

#MAIN=max
#N=10000
#NBT=10

#MAIN=somme-1-a-n
#N=20
#NBT=10


# Pour que l'erreur d'execution ne termine pas le reste du makefile.
.IGNORE:

CC     = cc
CFLAGS = -fopenmp -std=c99 -lm
RM     = rm -f

# Les divers fichiers objets.
TMPFILES = TAGS *~ *.o 


#
# Cibles principales.
#

default: run

compile: $(MAIN)

run: compile
	./$(MAIN) $(N) $(NBT)

pi: pi.o
	$(CC) $(CFLAGS) -o pi pi.o

max: max.o
	$(CC) $(CFLAGS) -o max max.o

somme-1-a-n: somme-1-a-n.o
	$(CC) $(CFLAGS) -o somme-1-a-n somme-1-a-n.o

diffusion: diffusion.o
	$(CC) $(CFLAGS) -o diffusion diffusion.o

run_diffusion:
	export NB_ITERATIONS_IMPRESSION=10; ./diffusion 20 100 1 10 4


#
# Regle implicite pour compilation des fichiers .c
#
.c.o:
	$(CC) -c $(CFLAGS) $<


#
# Dependances pour les divers fichiers auxiliaires.
#

$(TEST): $(TEST).o $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TEST) $(TEST).o  $(OBJECTS)

clean:
	@$(RM) $(TMPFILES) pi somme-1-a-n max hello-prive nbo nbo2 diffusion diffusion-spmd nbo-prive res pi2-prive pi2-opt-prive pi2 mandelbrot fibo-prive foo nested-prive nested-hierarchique-prive somme-1-a-n-task-prive



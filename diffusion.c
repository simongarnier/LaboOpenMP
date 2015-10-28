/** Programme parallele pour simuler la diffusion de la chaleur dans
    un cylindre.

    On simule un cylindre de metal avec une source de chaleur
    constante aux deux extremites. L'approximation numerique se fait
    par une discretisation spatiale (de points du cylindre) et
    temporelle (evolution de la temperature en fonction du temps).
    Pour simplifier, on suppose que le cylindre est de longueur 1!

    @param Nombre de points a utiliser pour discretiser le cylindre
    @param Nombre d'iterations a simuler
    @param Temperature extremite gauche
    @param Temperature extremite droite
    @param Nombre de threads a utiliser

    @name diffusion
    @author Guy Tremblay

    @memo Inspiree de la solution MPI presentee dans "Patterns for
    Parallel Programming", de Mattson. Sanders et Massingill,
    Addison-Wesley, 2005
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <omp.h>


///////////////////////////////////////////////////////
// Procedures auxiliaires.
///////////////////////////////////////////////////////

void initialiser( double cyl[], int n, double gauche, double droite )
{
  cyl[0] = gauche;
  for( int i = 1; i < n-1; i++ ) {
    cyl[i] = 0.0;
  }
  cyl[n-1] = droite;
}

int nbIterationsImpression = 0;

void imprimer( double cyl[], int n, int numIt )
{
  printf( "cyl {%d}::\n", numIt  );
  for ( int i = 0; i < n; i++ ) {
    printf( "%6.2f ", cyl[i] );
  }
  printf( "\n" );
}

//
///////////////////////////////////////////////////////
// Procedure principale de diffusion.
///////////////////////////////////////////////////////

void diffuser( double cyl[], int nbp, int nbit, double gauche, double droite )
{
  // On cree un tableau auxiliaire pour representer le cylindre au
  // temps suivant, d'ou le "p1" (plus 1).
  double *cylp1 = malloc( sizeof(double) * nbp );
  initialiser( cylp1, nbp, gauche, droite );


  // On repete pendant le nombre d'iterations desirees.
  for ( int k = 0; k < nbit; k++ ) {

    // On calcule la prochaine approximation (temporelle).
    cylp1[0] = cyl[0];
    for ( int i = 1; i < nbp-1; i++ ) {
      cylp1[i] = 0.5 * (cyl[i-1] + cyl[i+1]);
    }
    cylp1[nbp-1] = cyl[nbp-1];

    // On interchange le role des deux tableaux.
    double *temp = cylp1; cylp1 = cyl; cyl = temp;

    // De temps en temps, on imprime.
    if ( k > 0 && nbIterationsImpression != 0 && k % nbIterationsImpression == 0 ) {
      imprimer( cyl, nbp, k );
    }

  }
}

//
///////////////////////////////////////////////////////
// Programme principal.
///////////////////////////////////////////////////////

int main( int argc, char *argv[] ) 
{
  // On obtient et on valide les arguments du programme.
  if ( argc < 6 ) {
     printf( "usage:\n" );
     printf( "  %s nbp nbit gauche droite nbThreads\n", argv[0] );
     printf( "  nbp       : Nombre de points a utiliser\n" );
     printf( "  nbit      : Nombre d'iterations a simuler\n" );
     printf( "  gauche    : Temperature extremite gauche\n" );
     printf( "  droite    : Temperature extremite droite\n" );
     printf( "  nbThreads : Nombre de threads a utiliser\n" );
     printf( "" );
     printf( "Il faut aussi definir NB_ITERATIONS_IMPRESSION!\n" );
     return(-1);
  }

  int nbp = atoi( argv[1] );
  assert( nbp > 0 );

  int nbit = atoi( argv[2] );
  assert( nbit > 0 );

  double gauche = atof( argv[3] );
  double droite = atof( argv[4] );

  // On fixe le nombre de threads a utiliser.
  int nb_threads = atoi( argv[5] );
  assert( nb_threads > 0 );  
  omp_set_dynamic(0);
  omp_set_num_threads(nb_threads);

 
  // On alloue l'espace pour le tableau de valeurs representant le
  // cylindre et on les initialise.
  double *cyl = malloc( sizeof(double) * nbp );
  initialiser( cyl, nbp, gauche, droite );

  // On indique si, de temps en temps, il faut imprimer pour voir l'evolution.
  char *s = getenv("NB_ITERATIONS_IMPRESSION");
  if ( s != NULL && strcmp(s, "") != 0 ) {
    nbIterationsImpression = atoi(s);
  }

 
  // On diffuse pendant le nombre d'iterations requis.
  diffuser( cyl, nbp, nbit, gauche, droite );


  // On emet le resultat sur stdout, si demande.
  if ( nbIterationsImpression != 0 ) {
    imprimer( cyl, nbp, nbit );
  }

  return( 0 );
}

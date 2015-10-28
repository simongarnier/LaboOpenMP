/** Programme qui calcule le maximum d'une serie de valeurs contenues
    dans un tableau. 

    Les nombres sont generes de facon aleatoire. Une valeur maximum
    est ensuite mise a une position aleatoire dans le tableau, ce qui
    permet de connaitre de facon certaine le maximum attendu, d'ou
    l'assertion a la fin du programme.

    @param Taille du tableau a creer et a fouiller
    @param Nombre de threads a utiliser

    @name max
    @author Guy Tremblay
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <omp.h>

#define DEBUG 0

//
// Taille maximum du tableau pour les valeurs, lequel tableau est
// alloue de facon statique, pour simplifier le code.
//
#define N 1000000

int main( int argc, char *argv[] ) 
{
  // On obtient les arguments du programme.
  assert( argc >= 3 );
  int n = atoi( argv[1] );
  assert( n <= N );
  int nb_threads = atoi( argv[2] );
  assert( nb_threads > 0 );

  // On definit le tableau (aleatoirement).
  int a[N];
  for( int i = 0; i < n; i++ ) {
    a[i] = rand();
  }
  a[rand() % n] = RAND_MAX;

  // On fixe le nombre de threads a utiliser.
  omp_set_dynamic(1);
  omp_set_num_threads( nb_threads );


  // On part la minuterie.
  double debut = omp_get_wtime();

  // On recherche le maximum.
  int max = a[0];
  {
    for ( int i = 1; i < n; i++ ) {
        if ( a[i] > max ) {
          max = a[i];
        }
    }
  }

  // On arrete la minuterie.
  double fin = omp_get_wtime();

  // On imprime le resultat (simplement pour donner du feedback).
  printf( "\n" );
  printf( "Valeur max resultante = %d\n", max );

  // On verifie que c'est bien la bonne valeur.
  assert( max == RAND_MAX);

  printf( "Temps requis (avec %d threads): %f s\n", nb_threads, fin - debut );
  return( 0 );
}

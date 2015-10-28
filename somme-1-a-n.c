/** Programme qui calcule la valeur de 1 + 2 + ... + n. 

    Ce calcul s'effectue de facon recursive avec une approche
    dichotomique equilibree (decomposition en deux sous-problemes de
    taille equivalente).

    @param Valeur de n.
    @param Nombre de threads a utiliser

    @name somme-1-a-n
    @author Guy Tremblay
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <omp.h>

int somme( int i, int j )
{
  omp_get_thread_num();
  printf( "Thread %2d: somme( %4d, %4d )\n", omp_get_thread_num(), i, j );

  if ( i == j ) {
    return( i );
  } else {
    int mid = (i + j) / 2;
    int r1, r2;
      r1 = somme( i, mid );
      r2 = somme( mid+1, j );
    printf( "Thread %2d: somme( %4d, %4d ) => %4d \n", omp_get_thread_num(), i, j, r1+r2 );
    return( r1 + r2 );
  }
}


int main( int argc, char *argv[] ) 
{
  // On obtient les arguments du programme.
  assert( argc >= 3 );
  int n = atoi( argv[1] );
  assert( n > 0 );
  int nb_threads = atoi( argv[2] );
  assert( nb_threads > 0 );
  
  // On fixe le nombre de threads a utiliser.
  omp_set_dynamic(0);
  omp_set_num_threads( nb_threads );
  
  // On calcule la somme avec la fonction recursive.
  int res;
  {
    res = somme( 1, n );
  }
  
  // On imprime le resultat.
  printf( "\n" );
  printf( "1 + 2 + ... + %d (%d threads) = %d\n", n, nb_threads, res );

  // On verifie le resultat.
  assert( res == (n * (n+1) / 2) );
  
  return( 0 );
}

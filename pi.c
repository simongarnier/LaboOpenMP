/** Programme qui calcule la valeur de pi.

    La valeur de pi est obtenue en calculant la valeur de l'integrale
    (par l'intermediaire d'une approximation numerique) de la fonction
    4/(x^2 + 1) entre les bornes 0.0 et 1.0.

    @param Nombre de rectangles a utiliser pour approximer l'integrale
    @param Nombre de threads a utiliser

    @name pi
    @author Guy Tremblay
*/


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <omp.h>


// Valeur precise pour pi. Utilisee pour le calcul de l'erreur.
double PI = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679821480865132823066470938;


int main( int argc, char *argv[] ) 
{
  // On obtient les arguments du programme.
  assert( argc >= 2 );
  int nb_rectangles = atoi( argv[1] );
  assert( nb_rectangles > 0 );
  int nb_threads = atoi( argv[2] );
  assert( nb_threads > 0 );

  // On fixe le nombre de threads a utiliser.
  omp_set_dynamic(1);
  omp_set_num_threads(nb_threads);
 
  int vrai_nb_threads;

  // On part la minuterie.
  double debut = omp_get_wtime();

  // On calcule l'integral desiree.
  double largeur = 1.0 / (double) nb_rectangles;
  double somme = 0.0;

  {
    vrai_nb_threads = omp_get_num_threads();
    for ( int i = 0; i < nb_rectangles; i++ ) {
      double x = (i + 0.5) * largeur;  // Point milieu
      double fx = 4.0 / (1.0 + x*x);   // Hauteur au point milieu
      somme += fx;
    }
  }
  double pi = largeur * somme;
  
  // On arrete la minuterie.
  double fin = omp_get_wtime();

  // On imprime les resultats.
  printf( "\n" );
  printf( "Calcul pi avec %d intervalle(s) et %d thread(s) (sur %d threads demandes):\n", nb_rectangles, vrai_nb_threads, nb_threads );
  printf( "\tpi     = %.20f\n", pi );

  printf( "\terreur = %.20f\n\n", pi-PI );
  printf( "Temps requis: %8.3f s\n", fin - debut );
  return( 0 );
}

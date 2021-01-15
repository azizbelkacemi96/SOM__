#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "main.h"



void allocation_tab(int n);
void vecteur_moyen(int n);
void min_v(double k);
void max_v(double k);
void normalisation(int i,int size);
double* init_rand_w();
void init_shuffle(int n);
void shuffle(int n);
double distance_eql(double *a1, double *a2, int n);
void calc_alpha(int it_n, int tot_it);
#define SQR(x) ((x)*(x))

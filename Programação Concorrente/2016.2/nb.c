//  !	N-Body
/*	!
 *  \Copyright (C) 2016  Adan Pereira Gomes and Daniel Boso
 *  \Released under the GNU General Public License 2.0
 */
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

/*
 * pRNG based on http://www.cs.wm.edu/~va/software/park/park.html
 */
#define MODULUS    2147483647
#define MULTIPLIER 48271
#define DEFAULT    123456789

typedef struct {
    double x, y, z;
    double mass;
} Particle;

typedef struct {
    double xold, yold, zold;
    double fx, fy, fz;
} ParticleV;

Particle  * particles;   /* Particles */
ParticleV * pv;          /* Particle velocity */

static long seed = DEFAULT;
double global_max_f;
double dt, dt_old, dt_tmp; /* Alterado de static para global */
unsigned npart, num_threads; /* Number of threads used for simulating */
unsigned range;
pthread_mutex_t global_mutex;

double Random(void)
/* ----------------------------------------------------------------
 * Random returns a pseudo-random real number uniformly distributed
 * between 0.0 and 1.0.
 * ----------------------------------------------------------------
 */
{
  const long Q = MODULUS / MULTIPLIER;
  const long R = MODULUS % MULTIPLIER;
        long t;

  t = MULTIPLIER * (seed % Q) - R * (seed / Q);
  if (t > 0)
    seed = t;
  else
    seed = t + MODULUS;
  return ((double) seed / MODULUS);
}

/*
 * End of the pRNG algorithm
 */

static void    *InitParticles(void*);
static void    *ComputeForces(void*);
static void    *ComputeNewPos(void*);
static void    ParallelFunc(void*);

int main(int argc, char **argv)
{
    fprintf(stdout, "\nSIMULANDO\n");
    int         i;
    unsigned    cnt;         /* number of times in loop */
    double      sim_t;       /* Simulation time */

    if(argc != 4){
		printf("Wrong number of parameters.\nUsage: nbody num_bodies timesteps num_threads\n");
		exit(1);
	}

	npart = (unsigned)atoi(argv[1]);
	cnt = (unsigned)atoi(argv[2]);
	num_threads = (unsigned)atoi(argv[3]);

	dt = 0.001;
	dt_old = 0.001;
	dt_tmp = 0.0;
	range = npart / num_threads;

    /* Allocate memory for particles */
    particles = (Particle *) malloc(sizeof(Particle)*npart);
    pv = (ParticleV *) malloc(sizeof(ParticleV)*npart);

    if(particles == NULL || pv == NULL){
		fprintf(stdout, "ERROR: Failed to allocate memory to particles.\n");
		exit(1);
	}

    /* Init mutex */
    pthread_mutex_init(&global_mutex, NULL);

    /* Generate the initial values */
    ParallelFunc(&InitParticles);
    //ParallelInitParticles();
    sim_t = 0.0;

    while (cnt--) {
      /* Compute forces (2D only) */
      ParallelFunc(&ComputeForces);
      /* Once we have the forces, we compute the changes in position */
      ParallelFunc(&ComputeNewPos);
//      sim_t += dt_tmp;
    }

//    for (i = 0; i < npart; i++) {
//        fprintf(stdout,"%.5lf %.5lf\n", particles[i].x, particles[i].y);
//    }

    pthread_mutex_destroy(&global_mutex);

    free(particles);
    free(pv);
    //free(threads);

    return 0;
}

static void *InitParticles(void *tid)
{
    unsigned begin_range = range * ((unsigned)(intptr_t)tid);
    unsigned end_range = begin_range + range;

    if (((unsigned)(intptr_t)tid) == num_threads - 1 && num_threads % 2 != 0) {
        end_range = npart;
    }

    int i;
    for (i = begin_range; i != end_range; ++i) {
        particles[i].x	  = Random();
        particles[i].y	  = Random();
        particles[i].z	  = Random();
        particles[i].mass = 1.0;
        pv[i].xold	  = particles[i].x;
        pv[i].yold	  = particles[i].y;
        pv[i].zold	  = particles[i].z;
        pv[i].fx	  = 0;
        pv[i].fy	  = 0;
        pv[i].fz	  = 0;
    }
}

static void *ComputeForces(void *tid) {
    unsigned begin_range = range * ((unsigned)(intptr_t)tid);
    unsigned end_range = begin_range + range;

    if (((unsigned)(intptr_t)tid) == num_threads - 1 && num_threads % 2 != 0) {
        end_range = npart;
    }

    double max_f;
    int i;
    max_f = 0.0;
    for (i = begin_range; i != end_range; ++i) {
        int j;
        double xi, yi, mi, rx, ry, mj, r, fx, fy, rmin;
        rmin = 100.0;
        xi   = particles[i].x;
        yi   = particles[i].y;
        fx   = 0.0;
        fy   = 0.0;
        for (j = 0; j != npart; j++) {
            rx = xi - particles[j].x;
            ry = yi - particles[j].y;
            mj = particles[j].mass;
            r  = rx * rx + ry * ry;
            /* ignore overlap and same particle */
            if (r == 0.0) continue;
            if (r < rmin) rmin = r;
            r  = r * sqrt(r);
            fx -= mj * rx / r;
            fy -= mj * ry / r;
        }
        pv[i].fx += fx;
        pv[i].fy += fy;
        fx = sqrt(fx*fx + fy*fy)/rmin;
        if (fx > max_f) max_f = fx;
  }
  pthread_mutex_lock(&global_mutex);
  if (max_f > global_max_f) global_max_f = max_f;
  pthread_mutex_unlock(&global_mutex);
}

static void *ComputeNewPos(void *tid) {
    unsigned begin_range = range * ((unsigned)(intptr_t)tid);
    unsigned end_range = begin_range + range;

    if (((unsigned)(intptr_t)tid) == num_threads - 1 && num_threads % 2 != 0) {
        end_range = npart;
    }

    int i;
    double a0, a1, a2;
    double dt_new;
    a0	 = 2.0 / (dt * (dt + dt_old));
    a2	 = 2.0 / (dt_old * (dt + dt_old));
    a1	 = -(a0 + a2);
    for (i = begin_range; i != end_range; ++i) {
        double xi, yi;
        xi	           = particles[i].x;
        yi	           = particles[i].y;
        particles[i].x = (pv[i].fx - a1 * xi - a2 * pv[i].xold) / a0;
        particles[i].y = (pv[i].fy - a1 * yi - a2 * pv[i].yold) / a0;
        pv[i].xold     = xi;
        pv[i].yold     = yi;
        pv[i].fx       = 0;
        pv[i].fy       = 0;
    }
    dt_new = 1.0/sqrt(global_max_f);
    /* Set a minimum: */
    if (dt_new < 1.0e-6) dt_new = 1.0e-6;
    /* Modify time step */
    if (dt_new < dt) {
        dt_old = dt;
        dt     = dt_new;
    }
    else if (dt_new > 4.0 * dt) {
        dt_old = dt;
        dt    *= 2.0;
    }
    pthread_mutex_lock(&global_mutex);
    if (dt_old != dt_tmp) dt_tmp = dt_old;
    pthread_mutex_unlock(&global_mutex);
}

static void ParallelFunc(void* function) {
    pthread_t threads[num_threads];
    unsigned i;
    for (i = 0; i != num_threads; ++i) {
        pthread_create(&threads[i], NULL, function, (void*)(intptr_t)(i));
    }
    for (i = 0; i != num_threads; ++i) {
        pthread_join(threads[i], NULL);
    }
}

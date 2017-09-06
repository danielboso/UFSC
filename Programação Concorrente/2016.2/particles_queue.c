#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>


/**
 * Particle structure. Actually it's a point.
 */
typedef struct {
    int x;
    int y;
} particle_t;

/**
 * Queue structure for particles
 */
typedef struct {
  particle_t* contents;
  size_t begin;
  size_t end;
} queue_t;

/**
 * Allocs content for queue
 */
void init_particle_queue(queue_t* queue, size_t size) {
  queue->contents = (particle_t*)malloc(sizeof(particle_t)*size);
  queue->begin = 0;
  queue->end = 0;
}

/**
 * Dequeues a particle
 */
particle_t* dequeue(queue_t* queue) {
  if (queue->end == queue->begin) {
    return NULL;
  }
  particle_t* particle = &queue->contents[queue->begin];
  ++(queue->begin);
  return particle;
}

/**
 * Enqueue data
 */
void enqueue(queue_t* queue, particle_t particle) {
  queue->contents[queue->end] = particle;
  ++(queue->end);
}

/**
 * Gets queue size
 */
size_t queue_size(queue_t* queue) {
  return queue->end - queue->begin;
}


int main(void) {
    queue_t queue;
    init_particle_queue(&queue, 10);

    int xs[10] = {0, 3, 6, 12, -4, 7, 4, 2, 1, 3};
    int ys[10] = {-4, 123, -33, 42, 60, 0, 0, 2};

    for (int i = 0; i < 10; ++i) {
        particle_t particle;
        particle.x = xs[i];
        particle.y = ys[i];
        enqueue(&queue, particle);
    }

    for (int i = 0; i < 10; ++i) {
        particle_t particle = *dequeue(&queue);
        printf("particles[%d]:\n"
                "\tx: %d\n"
                "\ty: %d\n",
                i,
                particle.x,
                particle.y
              );
    }
}


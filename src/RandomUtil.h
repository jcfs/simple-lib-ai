#ifndef RANDOMUTIL_H
#define RANDOMUTIL_H

#include <ctime>
#include <cstdlib>

class RandomUtil {

  public:
    static float nextFloat() {
      srand (static_cast <unsigned> (time(0)));
      return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    }

    static float nextClampedFloat() {
      srand (static_cast <unsigned> (time(0)));
      return nextFloat() - nextFloat();
    }

    static bool nextBoolean() {
      srand (static_cast <unsigned> (time(0)));
      return rand() % 2 == 1;
    }
};


#endif

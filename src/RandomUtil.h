#ifndef RANDOMUTIL_H
#define RANDOMUTIL_H

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
};


#endif

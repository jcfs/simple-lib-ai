#ifndef TICKTACKTOEVALIDATOR_H
#define TICKTACKTOEVALIDATOR_H

#define CIRCLE  1
#define CROSS  -1
#define BLANK   0

#define NOT_OVER -3

class TicTacToeValidator {
  public:
    static int validate(char * game);
};

#endif

#ifndef XORAGENT_H
#define XORAGENT_H

#include <string>

#include "../../src/Agent.h"

using namespace std;

class XorAgent: public Agent {
	private:
		float m_error;
  public:
    XorAgent(Genome * genome, NetworkConfiguration * configuration);
    ~XorAgent();
    void update();
    bool isAlive(){ return false; }
    bool isDead(){ return false; }
    string toString();
		float getError() { return m_error; }

};


#endif

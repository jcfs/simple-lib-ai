#ifndef AGENTFACTORY_H
#define AGENTFACTORY_H

class AgentFactory {
  public:
    virtual ~AgentFactory(){}
    // pure virtual method (interface)
    virtual Agent * newInstance(Genome * genome, NetworkConfiguration * configuration) = 0;
};


#endif

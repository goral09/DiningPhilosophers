#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include "Fork.h"

class Philosopher
{
    public:
        Philosopher(int _id, Fork* leftFork, 
        	Fork* rightFork);
        Philosopher(int _id, Fork* leftFork);
        virtual ~Philosopher();
        bool isDoneEating();
        void setLeftNeighbour(Philosopher* left);
        void setRightNeighbour(Philosopher* right);
        int sayYourNameBitch();
        void acquireForks();
        void iAmEating();
        bool hasBothForks();
        void lockForks();
        //void releaseForks();
    protected:
    	Fork* giveLeftFork();
        Fork* giveRightFork();
        void takeLeftFork();
        void takeRightFork();
    private:
        int _id;
        bool full;
        Fork* leftFork;
        Fork* rightFork;
        Philosopher* leftNeighbour;
        Philosopher* rightNeighbour;
};

#endif // PHILOSOPHER_H

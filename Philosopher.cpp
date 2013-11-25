#include "Philosopher.h"
#include <cstdio>

Philosopher::Philosopher(int _id2, Fork* leftFork2, Fork* rightFork2)
{
    _id = _id2;
    leftFork = leftFork2;
    rightFork = rightFork2;
    full = false;
    leftNeighbour = NULL;
    rightNeighbour = NULL;
    //printf("\nIn the constructor, _id: %d", _id);
    //printf("\tWith forks: %d AND %d", leftFork -> getId(), rightFork -> getId());
}

Philosopher::Philosopher(int _id2, Fork* leftFork2)
{
	_id = _id2;
	leftFork = leftFork2;
	rightFork = NULL;
	full = false;
	leftNeighbour = NULL;
	rightNeighbour = NULL;
}

Philosopher::~Philosopher()
{
	leftNeighbour = NULL;
	rightNeighbour = NULL;
	full = false;
	_id = -1;
    leftFork = NULL;
    rightFork = NULL;
}

int Philosopher::sayYourNameBitch() 
{
	return _id;
}
void Philosopher::setLeftNeighbour(Philosopher* left)
{
	leftNeighbour = left;
}
void Philosopher::setRightNeighbour(Philosopher* right)
{
	rightNeighbour = right;
}
Fork* Philosopher::giveLeftFork()
{
	if(leftFork -> isDirty() == 1){
		leftFork -> setAsClean();
		Fork* tmp = leftFork;
		leftFork = NULL;
		return tmp;
	}
	else
		return NULL;
}

Fork* Philosopher::giveRightFork()
{
	if(rightFork -> isDirty() == 1){
		rightFork -> setAsClean();
		Fork* tmp = rightFork;
		rightFork = NULL;
		return tmp;
	}
	else
		return NULL;
}

void Philosopher::takeLeftFork()
{
	leftFork = leftNeighbour -> giveRightFork();
}

void Philosopher::takeRightFork()
{
	rightFork = rightNeighbour -> giveLeftFork();
}
void Philosopher::acquireForks()
{
	//printf("%s\n", (leftFork == NULL ? "leftFork is NULL" : "leftFork is Not NULL" ));
	//printf("%s\n", (rightFork == NULL ? "rightFork is NULL" : "rightFork is Not NULL" ));

	if(leftFork != NULL && rightFork == NULL)
		takeRightFork();
	else if(rightFork != NULL && leftFork == NULL)
		takeLeftFork();
	else if(rightFork == NULL && leftFork == NULL){
		takeLeftFork();
		takeRightFork();
	}

}

void Philosopher::iAmEating()
{
	//printf("\nPhilosopher %d is eating...", _id);
	//printf("\tPhilosopher %d is done eating.\t", _id);
	if(rightFork != NULL) rightFork -> setAsDirty();
	if(leftFork !=NULL) leftFork -> setAsDirty();
	full = true;
}

bool Philosopher::isDoneEating()
{
	return full;
}

bool Philosopher::hasBothForks()
{
	return (leftFork != NULL && rightFork != NULL);
}
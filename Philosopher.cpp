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
	leftFork -> lock();
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
	if(left != NULL)
		leftNeighbour = left;
}
void Philosopher::setRightNeighbour(Philosopher* right)
{
	if(right != NULL)
		rightNeighbour = right;
}
Fork* Philosopher::giveLeftFork()
{
	Fork* tmp = NULL;
	if(leftFork != NULL) {
		if((leftFork -> isDirty()) == true){
			leftFork -> setAsClean();
			tmp = leftFork;
			//(*leftFork).unlock();
			leftFork = NULL;
			return tmp;
		}
	}
	else
		return NULL;
}

Fork* Philosopher::giveRightFork()
{
	Fork* tmp = NULL;
	if(rightFork != NULL) {
		if((rightFork -> isDirty()) == true){
			rightFork -> setAsClean();
			tmp = rightFork;
			//(*rightFork).unlock();
			rightFork = NULL;
			return tmp;
		}
	}
	else
		return NULL;
}
void Philosopher::lockForks(){
	//printf("Locking left fork\n");
	int resLockLeft = leftFork -> lock();
	if( resLockLeft != 0) 
		printf("Problem with locking left fork: %d\n", resLockLeft);
	int resLockRight = rightFork -> lock();
	//printf("Locking right fork\n");
	if(resLockRight != 0)
		printf("Problem with locking left fork: %d\n", resLockRight);
}

//void Philosopher::releaseForks(){
	//leftFork -> unlock();
	//rightFork -> unlock();
//}
void Philosopher::takeLeftFork()
{
	if(leftFork == NULL && leftNeighbour != NULL)
		leftFork = leftNeighbour -> giveRightFork();
	//int resLeftLock = leftFork -> lock();
	//printf("Left fork lock %d\n", resLeftLock );
}

void Philosopher::takeRightFork()
{
	if(rightFork == NULL && rightNeighbour != NULL)
		rightFork = rightNeighbour -> giveLeftFork();
	//int resRightLock = rightFork -> lock();
	//printf("Right fork lock %d\n", resRightLock );
}
void Philosopher::acquireForks()
{
	//printf("%s\n", (leftFork == NULL ? "leftFork is NULL" : "leftFork is Not NULL" ));
	//printf("%s\n", (rightFork == NULL ? "rightFork is NULL" : "rightFork is Not NULL" ));

	if(rightFork == NULL)
		takeRightFork();
	else if(leftFork == NULL)
		takeLeftFork();
	else if(rightFork == NULL && leftFork == NULL){
		takeLeftFork();
		takeRightFork();
	}

}

void Philosopher::iAmEating()
{;
	//printf("\nPhilosopher %d is eating...", _id);
	//printf("\tPhilosopher %d is done eating.\t", _id);
	rightFork -> setAsDirty();
	leftFork -> setAsDirty();
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
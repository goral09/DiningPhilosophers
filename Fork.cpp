#include "Fork.h"
#include <pthread.h>
#include <stdio.h>

Fork::Fork(int _id2, bool isClean2) 
{
	_id = _id2;
	isClean = isClean2;
	mutex = PTHREAD_MUTEX_INITIALIZER;
}
Fork:: Fork(){

}
Fork::~Fork()
{
	pthread_mutex_destroy(&mutex);
}

bool Fork::isDirty() 
{
	return !isClean;
}
void Fork::setAsClean() {
	pthread_mutex_unlock(&mutex);
	isClean = true;	
}

void Fork::setAsDirty() {
	isClean = false;
}

int Fork::getId(){
	return _id;
}

int Fork::lock(){
	return pthread_mutex_lock(&mutex);
}

int Fork::tryLock(){
	return pthread_mutex_trylock(&mutex);
}

//int Fork::unlock(){
//	return pthread_mutex_unlock(&mutex);
//}
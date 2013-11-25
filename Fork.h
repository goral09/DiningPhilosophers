#ifndef FORK_H
#define FORK_H

#include <pthread.h>

class Fork
{
public:
	Fork();
	Fork(int _id, bool isClean);
	void setAsClean();
	void setAsDirty();
	bool isDirty();
	int getId();
	virtual ~Fork();
	int lock();
	int tryLock();
	int unlock();
protected:
private:
	int _id;
	bool isClean;
	pthread_mutex_t mutex;
};

#endif  //FORK_H
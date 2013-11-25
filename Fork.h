#ifndef FORK_H
#define FORK_H

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
protected:
private:
	int _id;
	bool isClean;
};

#endif  //FORK_H
#include "Fork.h"

Fork::Fork(int _id2, bool isClean2) 
{
	_id = _id2;
	isClean = isClean2;
}
Fork:: Fork(){

}
Fork::~Fork()
{

}

bool Fork::isDirty() 
{
	return !isClean;
}
void Fork::setAsClean() {
	isClean = true;
}

void Fork::setAsDirty() {
	isClean = false;
}

int Fork::getId(){
	return _id;
}
#include "Evertable.h"

bool Evertable::isEverted(){
	return Everted;
}
bool Evertable::Evert(){
	Everted = !Everted;
	return Everted;
}
IND_Entity2d * Evertable::getEntity(){
	return Entity;
}
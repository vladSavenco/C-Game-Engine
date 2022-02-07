#include "DataEvent.h"

DataEvent::DataEvent()
{

}

DataEvent::DataEvent(std::string myType, int amnt, dEvent spec)
{
	type = myType;
	ammount = amnt;
	eSpec = spec;
}

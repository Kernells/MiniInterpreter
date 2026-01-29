#include "Reporter.h"

using namespace Reporter;

// Message throwing function for info, warnings, and errors.

void Reporter::ThrowMessage(std::string message, int type) { // Type 0 = Info, Type 1 = Warning, Type 2 = Error	

	switch (type) {
	case 0:
	{
		std::cout << "[INFO] " << message << std::endl;
	}
	case 1:
	{
		std::cout << "[WARNING] " << message << std::endl;
	}
	case 2:
	{
		std::cout << "[ERROR] " << message << std::endl;
	}
	}
}

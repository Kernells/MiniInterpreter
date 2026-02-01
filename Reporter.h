#pragma once
#include <string>
#include <iostream>

namespace Reporter
{
	extern void ThrowMessage(std::string message, int type); // Type 0 = Info, Type 1 = Warning, Type 2 = Error	
	extern void ThrowException(int type, std::string arg); // Type 0 = Invalid Stack Address
};


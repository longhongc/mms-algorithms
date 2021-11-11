#ifndef UTIL_H
#define UTIL_H

#include <string>
#include "map.h"


void log(const std::string& text); 
void log(const NodePosition& cell, const std::string& text=""); 

#endif

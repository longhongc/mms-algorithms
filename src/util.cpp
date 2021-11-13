#include <iostream>
#include "util.h"

void log(const std::string& text){
    std::cerr << text << std::endl; 
}

void log(const NodePosition& cell, const std::string& label){
    std::cerr << label 
              << "(" 
              << std::to_string(cell.x) 
              << ","
              << std::to_string(cell.y)
              << ")"
              << std::endl; 
}

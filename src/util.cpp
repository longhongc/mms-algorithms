#include <iostream>
#include "util.h"

/* --------------------------------------------------------------------------*/
/**
 * @Brief debug logger for string output on mouse simulator
 *
 * @Param text: the output string 
 */
/* --------------------------------------------------------------------------*/
void log(const std::string& text){
    std::cerr << text << std::endl; 
}

/* --------------------------------------------------------------------------*/
/**
 * @Brief debug logger for NodePosition and a label descibing the NodePosition 
 *
 * @Param cell
 * @Param label
 */
/* --------------------------------------------------------------------------*/
void log(const NodePosition& cell, const std::string& label){
    std::cerr << label 
              << "(" 
              << std::to_string(cell.x) 
              << ","
              << std::to_string(cell.y)
              << ")"
              << std::endl; 
}

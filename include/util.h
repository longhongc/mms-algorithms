/**
 * @file util.h
 * @Brief utility functions for debugging   
 * @author Chang-Hong Chen(longhongc@gmail.com), Prateek Verma(verma@termpmail.umd.edu)
 * @version 2.1.0
 * @date 2021-11-13
 */
#ifndef UTIL_H
#define UTIL_H

#include <string>
#include "map.h"

/* --------------------------------------------------------------------------*/
/**
 * @Brief debug logger for string output on mouse simulator
 *
 * @Param text: the output string 
 */
/* --------------------------------------------------------------------------*/
void log(const std::string& text); 

/* --------------------------------------------------------------------------*/
/**
 * @Brief debug logger for NodePosition and a label descibing the NodePosition 
 *
 * @Param cell
 * @Param label
 */
/* --------------------------------------------------------------------------*/
void log(const NodePosition& cell, const std::string& text=""); 

#endif

/**
 * @file online_DFS.cpp
 * @Brief mouse using online_DFS to solve a maze 
 * @author Chang-Hong Chen(longhongc@gmail.com), Prateek Verma(verma@termpmail.umd.edu)
 * @version 2.1.0
 * @date 2021-11-13
 */

#include "API.h"
#include "mouse.h"
#include "util.h"

int main(){
    Mouse mouse; 
    bool find_path = mouse.online_DFS_search();
    if(not find_path){
        log("Maze no solution!!!"); 
    }else{
        log("Success"); 
    }
      
    return 0; 
}

/**
 * @file offline_DFS.cpp
 * @Brief mouse using offline_DFS to solve a maze 
 * @author Chang-Hong Chen(longhongc@gmail.com), Prateek Verma(verma@termpmail.umd.edu)
 * @version 2.1.0
 * @date 2021-11-13
 */

#include "API.h"
#include "mouse.h"
#include "util.h"

int main(){
    Mouse mouse; 
    bool arrived_goal = false; 
    while(not arrived_goal){
        mouse.reset_search(); 
        bool find_path = mouse.offline_DFS_search();
        if(find_path){
            arrived_goal = mouse.follow_path();
        }else{
            log("Maze no solution!!!"); 
            break; 
        }
    }
    log("Success"); 

    return 0; 
}

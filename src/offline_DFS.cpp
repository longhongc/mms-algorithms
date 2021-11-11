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

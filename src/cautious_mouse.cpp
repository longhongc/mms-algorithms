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
            log("find_path failed"); 
            break; 
        }
    }

    // while(not mouse.at_goal){
    //     auto m_path = mouse.search_with_DFS(); 
    //     bool finish = mouse.follow_path(m_path);
    //     if(not finish){
    //         mouse.reset_search(); 
    //     }
    // }
    //
    return 0; 
}

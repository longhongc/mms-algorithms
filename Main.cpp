#include "API.h"
#include "Mouse.h"

int main(){
    Mouse mouse; 
    bool success = mouse.search_with_DFS();
    if(success){
        mouse.follow_path();
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

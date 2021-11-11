#include "API.h"
#include "mouse.h"
#include "util.h"

int main(){
    Mouse mouse; 
    bool find_path = mouse.online_DFS_search();
    if(not find_path){
        log("maze no solution!!!"); 
    }
      
    return 0; 
}

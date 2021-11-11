#include "API.h"
#include "mouse.h"
#include "util.h"

int main(){
    Mouse mouse; 
    bool find_path = mouse.online_DFS_search();
      
    return 0; 
}

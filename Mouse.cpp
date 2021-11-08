#include <algorithm>
#include "Mouse.h"
#include "API.h"

bool Mouse::search_with_DFS(){

    auto search_cell = m_current_cell; 

    while(true){
        if(not m_belief_map.cell_visited(search_cell)){
            m_path.push_back(search_cell); 
            m_visited.push_back(search_cell); 
            m_belief_map.set_cell_visited(search_cell); 
            // API::setColor(search_cell.x, search_cell.y, 'a'); 

            if(search_cell.x == m_goal_cell.x && search_cell.y == m_goal_cell.y){
                log("success"); 
                return true; 
            }
        }

        if(m_path.empty()){
            log("fail"); 
            return false; 
        }

        Node_Pos next_search_cell; 
        if(m_belief_map.cell_north_valid(search_cell)){
            next_search_cell= {search_cell.x, search_cell.y+1}; 

        }else if(m_belief_map.cell_east_valid(search_cell)){
            next_search_cell= {search_cell.x+1, search_cell.y}; 

        }else if(m_belief_map.cell_south_valid(search_cell)){
            next_search_cell= {search_cell.x, search_cell.y-1}; 

        }else if(m_belief_map.cell_west_valid(search_cell)){
            next_search_cell= {search_cell.x-1, search_cell.y}; 

        }else{
            m_path.pop_back(); 
            next_search_cell = m_path.back(); 
            API::setColor(search_cell.x, search_cell.y, 'k'); 
        }

        search_cell = next_search_cell; 
        // log(std::to_string(search_cell.x) + ", " +  std::to_string(search_cell.y)); 
    }
    

}
bool Mouse::follow_path(){
    // for(auto &cell: m_path){
    //     API::setColor(cell.x, cell.y, 'a'); 
    // }
    return false; 
}
void Mouse::reset_search(){

    m_path.clear(); 
    m_visited.clear(); 
}




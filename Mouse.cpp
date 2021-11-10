#include <algorithm>
#include "Mouse.h"
#include "API.h"

bool Mouse::search_with_DFS(){

    auto search_cell = m_current_cell; 
    //log(std::to_string(search_cell.x) + ", " +  std::to_string(search_cell.y)); 
    if(m_belief_map.cell_visited(search_cell)){
        //log("start visit"); 
    }else{
        //log("start not visit"); 

    }

    while(true){
        if(not m_belief_map.cell_visited(search_cell)){
            m_path.push_back(search_cell); 
            m_visited.push_back(search_cell); 
            m_belief_map.set_cell_visited(search_cell); 
            API::setColor(search_cell.x, search_cell.y, 'a'); 

            if(search_cell.x == m_goal_cell.x && search_cell.y == m_goal_cell.y){
                //log(std::to_string(m_path.size())); 
                //log("success"); 
                // m_belief_map.clear_all_visited(); 
                //API::clearAllColor(); 
                return true; 
            }
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

            if(m_path.empty()){
                return false; 
            }

            next_search_cell = m_path.back(); 
            API::setColor(next_search_cell.x, next_search_cell.y, 'y'); 
            log("back step"+std::to_string(next_search_cell.x) + ", " +  std::to_string(next_search_cell.y)); 
        }

        search_cell = next_search_cell; 
    }
    

}
bool Mouse::follow_path(){
    //log(std::to_string(m_path.size())); 
    for(auto &cell: m_path){
        // m_real_map.set_cell_visited(m_current_cell); 
        bool move_success = move_to_cell(cell); 
        if(not move_success){
            //log("hit wall"); 
            //log(std::to_string(m_current_cell.x) + ", " +  std::to_string(m_current_cell.y)); 
            //log("next cell" + std::to_string(cell.x) + ", " +  std::to_string(cell.y)); 
            // m_real_map.clear_cell_visited(m_current_cell); 
            return false; 
        }
        m_current_cell = cell; 
        //API::setColor(m_current_cell.x, m_current_cell.y, 'a'); 
    }
    //log("Arrive goal"); 
    return true; 
}
void Mouse::reset_search(){

    m_path.clear(); 
    m_visited.clear(); 
    m_real_map.set_start(m_current_cell); 
    m_belief_map = m_real_map; 
    API::clearAllColor(); 
    return; 
}

bool Mouse::move_to_cell(Node_Pos cell){
    update_walls(); 
    Direction next_direction = m_direction; 
    if(cell.y > m_current_cell.y){
        //log("north"); 
        next_direction = Direction::North; 

    }else if(cell.x > m_current_cell.x){
        //log("east"); 
        next_direction = Direction::East; 

    }else if(cell.y < m_current_cell.y){
        //log("south"); 
        next_direction = Direction::South; 

    }else if(cell.x < m_current_cell.x){
        //log("west"); 
        next_direction = Direction::West; 

    }
    else{
        return true; 
    }


    change_direction(next_direction); 

    bool update_success = update_walls(); 
    if (not update_success){
        return false; 
    }

    API::moveForward(); 
    return true; 
}

bool Mouse::update_walls(){
    //log(std::to_string(m_current_cell.x) + ", " +  std::to_string(m_current_cell.y)); 
    Direction wall_direction = m_direction;  
    if(API::wallLeft()){
        //log("wall Left"); 
        wall_direction = direction_left(m_direction); 
        m_real_map.set_cell_wall(m_current_cell, wall_direction); 
    }

    if(API::wallRight()){
        //log("wall right"); 
        wall_direction = direction_right(m_direction);
        m_real_map.set_cell_wall(m_current_cell, wall_direction); 
    }

    if(API::wallFront()){
        //log("wall front"); 
        wall_direction = m_direction;  
        m_real_map.set_cell_wall(m_current_cell, wall_direction); 
        return false; 
    }

    return true; 
}

void Mouse::change_direction(Direction direction){
    if(direction == direction_left(m_direction)){
        //log("turn left"); 
        API::turnLeft(); 

    }else if(direction == direction_right(m_direction)){
        //log("turn right"); 
        API::turnRight(); 

    }else if(direction != m_direction){
        //log("turn opposite"); 
        API::turnLeft(); 
        API::turnLeft(); 
    }
    m_direction = direction; 
    return; 
}




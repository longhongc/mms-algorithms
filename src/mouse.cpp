#include <algorithm>
#include "mouse.h"
#include "util.h"
#include "API.h"

bool Mouse::offline_DFS_search(){

    auto search_cell = m_current_cell; 
    //log(search_cell); 
    
    while(true){
        if(not m_belief_map.cell_visited(search_cell)){
            m_goal_path.push_back(search_cell); 
            m_visited.push_back(search_cell); 
            m_belief_map.set_cell_visited(search_cell); 
            API::setColor(search_cell.x, search_cell.y, 'a'); 

            if(search_cell.x == m_goal_cell.x && search_cell.y == m_goal_cell.y){
                //log(std::to_string(m_goal_path.size())); 
                //log("success"); 
                // m_belief_map.clear_all_visited(); 
                //API::clearAllColor(); 
                return true; 
            }
        }

        NodePosition next_search_cell; 
        if(m_belief_map.cell_north_valid(search_cell)){
            next_search_cell = {search_cell.x, search_cell.y+1}; 

        }else if(m_belief_map.cell_east_valid(search_cell)){
            next_search_cell = {search_cell.x+1, search_cell.y}; 

        }else if(m_belief_map.cell_south_valid(search_cell)){
            next_search_cell = {search_cell.x, search_cell.y-1}; 

        }else if(m_belief_map.cell_west_valid(search_cell)){
            next_search_cell = {search_cell.x-1, search_cell.y}; 

        }else{
            m_goal_path.pop_back(); 

            if(m_goal_path.empty()){
                return false; 
            }

            next_search_cell = m_goal_path.back(); 
            API::setColor(next_search_cell.x, next_search_cell.y, 'Y'); 
            log(next_search_cell, "backtrack: "); 
        }

        search_cell = next_search_cell; 
    }
}

bool Mouse::online_DFS_search(){
    std::vector<NodePosition> node_stack;    
    node_stack.push_back(m_current_cell); 

    while(true){
        if(m_current_cell == m_goal_cell){
            log("success"); 
            return true; 
        }
        //m_visited.push(current_node.pos); 
        m_real_map.set_cell_visited(m_current_cell); 
        m_goal_path.push_back(m_current_cell); 
        API::setColor(m_current_cell.x, m_current_cell.y, 'a'); 

        update_walls(); 
        int child_num = 0; 
        if(m_real_map.cell_north_valid(m_current_cell)){
            NodePosition child_cell{m_current_cell.x, m_current_cell.y+1}; 
            m_real_map.set_cell_parent(child_cell, m_current_cell); 
            node_stack.push_back(child_cell); 
            child_num++; 

        }
        if(m_real_map.cell_east_valid(m_current_cell)){
            NodePosition child_cell{m_current_cell.x+1, m_current_cell.y}; 
            m_real_map.set_cell_parent(child_cell, m_current_cell); 
            node_stack.push_back(child_cell); 
            child_num++; 

        }
        if(m_real_map.cell_south_valid(m_current_cell)){
            NodePosition child_cell{m_current_cell.x, m_current_cell.y-1}; 
            m_real_map.set_cell_parent(child_cell, m_current_cell); 
            node_stack.push_back(child_cell); 
            child_num++; 

        }
        if(m_real_map.cell_west_valid(m_current_cell)){
            NodePosition child_cell{m_current_cell.x-1, m_current_cell.y}; 
            m_real_map.set_cell_parent(child_cell, m_current_cell); 
            node_stack.push_back(child_cell); 
            child_num++; 

        }

        NodePosition next_search_cell = node_stack.back(); 
        node_stack.pop_back(); 

        if(node_stack.empty()){
            log("find path failed"); 
            return false; 
        }

        if(child_num == 0){
            NodePosition intersection_cell = m_real_map.get_cell_parent(next_search_cell); 
            while(m_current_cell != intersection_cell){
                NodePosition parent_cell = m_real_map.get_cell_parent(m_current_cell); 
                move_to_cell(parent_cell); 
                m_goal_path.pop_back(); 
                API::setColor(m_current_cell.x, m_current_cell.y, 'k'); 
                m_current_cell = parent_cell; 
            }
        }

        move_to_cell(next_search_cell); 
        m_current_cell = next_search_cell; 
    }
    
}
bool Mouse::follow_path(){
    for(auto &cell: m_goal_path){
        // m_real_map.set_cell_visited(m_current_cell); 
        update_walls(); 
        bool move_success = move_to_cell(cell); 
        if(not move_success){
            //log("hit wall"); 
            log(m_current_cell); 
            //log(cell); 
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

    m_goal_path.clear(); 
    m_visited.clear(); 
    m_real_map.set_start(m_current_cell); 
    m_belief_map = m_real_map; 
    API::clearAllColor(); 
}

bool Mouse::move_to_cell(NodePosition cell){
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
    //log(m_current_cell); 
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
}




#include "mouse.h"
#include "util.h"
#include "API.h"

bool Mouse::online_DFS_search(){
    std::vector<NodePosition> node_stack;    
    node_stack.push_back(m_current_cell); 

    int count = 0; 
    while(true){
        API::setText(m_current_cell.x, m_current_cell.y, std::to_string(count)); 

        // goal found
        if(m_current_cell == m_goal_cell){
            reach_goal = true; 
            // color notation green: reaching the goal 
            API::setColor(m_current_cell.x, m_current_cell.y, 'g'); 
            return true; 
        }

        m_real_map.set_cell_visited(m_current_cell); 
        m_goal_path.push_back(m_current_cell); 
        count++; 
        // color notation gray: cells along the path
        API::setColor(m_current_cell.x, m_current_cell.y, 'a'); 

        // find available adjacent cells and add all of them to stack
        // mark the current cell as the parent of child cells
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

        NodePosition next_search_cell; 

        // pop out the cell that is already consider dead (all four direction unavailable)
        do{
            next_search_cell = node_stack.back(); 
            node_stack.pop_back(); 

            // pop out the start cell, no solution
            if(node_stack.empty()){
                return false; 
            }

            if(not m_real_map.cell_dead(next_search_cell)){
                // color notation orange: next search cell
                API::setColor(next_search_cell.x, next_search_cell.y, 'o'); 
            }else{
                // color notation dark red: dead cell
                API::setColor(next_search_cell.x, next_search_cell.y, 'R'); 
                log(next_search_cell, "Dead Cell: "); 
            }
        }
        while(m_real_map.cell_dead(next_search_cell)); 

        // do backtracking, if the current cell is not the parent of the next target cell
        NodePosition intersection_cell = m_real_map.get_cell_parent(next_search_cell); 
        while(m_current_cell != intersection_cell){
            log(m_current_cell, "Backtrack: "); 
            NodePosition parent_cell = m_real_map.get_cell_parent(m_current_cell); 
            move_to_cell(parent_cell); 
            m_goal_path.pop_back(); 
            // color notation dark gray: cells after backtracking
            API::setColor(m_current_cell.x, m_current_cell.y, 'A'); 
            m_current_cell = parent_cell; 
        }

        move_to_cell(next_search_cell); 
        m_current_cell = next_search_cell; 
    }
    
}

bool Mouse::offline_DFS_search(){
    while(not reach_goal){
        // reset and update belief map
        reset_search(); 
        // DFS search in belief map
        bool find_path = search_belief_map();
        if(find_path){
            // follow the path generated from the belief map
            reach_goal = follow_path();
        }else{
            return false; 
        }
    }
    return true; 
}

void Mouse::reset_search(){

    m_goal_path.clear(); 
    m_real_map.set_start(m_current_cell); 
    // update belief map with new detected walls 
    m_belief_map = m_real_map; 
    API::clearAllColor(); 
    API::clearAllText(); 
    API::setColor(m_goal_cell.x, m_goal_cell.y, 'y'); 
    API::setText(m_goal_cell.x, m_goal_cell.y, "goal"); 
}

bool Mouse::search_belief_map(){

    auto search_cell = m_current_cell; 
    int count = 0; 
    
    while(true){
        if(not m_belief_map.cell_visited(search_cell)){
            API::setText(search_cell.x, search_cell.y, std::to_string(count)); 
            m_goal_path.push_back(search_cell); 
            m_belief_map.set_cell_visited(search_cell); 
            count++; 

            // goal found
            if(search_cell.x == m_goal_cell.x && search_cell.y == m_goal_cell.y){
                return true; 
            }else{
                // color notation gray: cells along the path
                API::setColor(search_cell.x, search_cell.y, 'a'); 
            }
        }

        // find available adjacent cells in the order of N, E, S, W, and add to stack 
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
            // no adjcent cells available, do backtracking
            // color notation dark gray: cells after backtracking
            API::setColor(search_cell.x, search_cell.y, 'A'); 
            m_goal_path.pop_back(); 
            // pop out the start cell, no solution
            if(m_goal_path.empty()){
                return false; 
            }

            next_search_cell = m_goal_path.back(); 
            log(next_search_cell, "Backtrack: "); 
        }

        search_cell = next_search_cell; 
    }
}

bool Mouse::follow_path(){
    for(auto &cell: m_goal_path){
        // detect the wall in current cell
        update_walls(); 
        // color notation orange: next search cell
        API::setColor(cell.x, cell.y, 'o'); 
        // move to next cell on the path
        bool move_success = move_to_cell(cell); 
        if(not move_success){
            //log("hit wall"); 
            return false; 
        }
        // color notation black: cells after passing through
        API::setColor(cell.x, cell.y, 'k'); 
        m_current_cell = cell; 
    }
    // color notation green: reaching the goal 
    API::setColor(m_current_cell.x, m_current_cell.y, 'g'); 
    return true; 
}


bool Mouse::move_to_cell(NodePosition cell){
    // find the direction of the next cell relative to current cell
    Direction next_direction = m_direction; 
    if(cell.y > m_current_cell.y){
        // log("north"); 
        next_direction = Direction::North; 

    }else if(cell.x > m_current_cell.x){
        // log("east"); 
        next_direction = Direction::East; 

    }else if(cell.y < m_current_cell.y){
        // log("south"); 
        next_direction = Direction::South; 

    }else if(cell.x < m_current_cell.x){
        // log("west"); 
        next_direction = Direction::West; 

    }
    else{
        // stay at the same cell 
        return true; 
    }


    // change direction to face the next cell
    change_direction(next_direction); 

    if(API::wallFront()){
        // fail to move to next cell
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




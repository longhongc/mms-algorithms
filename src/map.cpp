#include "map.h"
#include "util.h"
#include "API.h"

Direction direction_left(Direction current){
    switch(current){
        case Direction::North: 
            return Direction::West; 

        case Direction::East: 
            return Direction::North; 

        case Direction::South: 
            return Direction::East; 

        case Direction::West: 
            return Direction::South; 
    }
} 

Direction direction_right(Direction current){ 
    switch(current){
        case Direction::North: 
            return Direction::East; 

        case Direction::East: 
            return Direction::South; 

        case Direction::South: 
            return Direction::West; 

        case Direction::West: 
            return Direction::North; 
    }
}

void Map::set_default(){
    for(int i=0; i<m_maze_width; i++){
        for(int j=0; j<m_maze_height; j++){
            m_map[j][i].pos = {i, j}; 
        }
    }
    // default belief m_map
    //     --------
    //     |      |
    //     |      |
    //     |      |
    //     --------
    // North wall
    for(int i=0; i<m_maze_width; i++){
        m_map[m_maze_height-1][i].north_wall = true; 
    }
    // East wall
    for(int j=0; j<m_maze_height; j++){
        m_map[j][m_maze_width-1].east_wall = true;  
    }
    // South wall
    for(int i=0; i<m_maze_width; i++){
        m_map[0][i].south_wall = true; 
    }
    // West wall
    for(int j=0; j<m_maze_height; j++){
        m_map[j][0].west_wall = true;  
    }
    // start node wall
    //m_map[0][0].east_wall = true; 
    
    API::setColor(m_goal.x, m_goal.y, 'o'); 
}

void Map::set_cell_visited(NodePosition cell){
    m_map[cell.y][cell.x].visited = true; 
}

void Map::clear_cell_visited(NodePosition cell){
    m_map[cell.y][cell.x].visited = false; 
}

void Map::clear_all_visited(){
    for(int i=0; i<m_maze_width; i++){
        for(int j=0; j<m_maze_height; j++){
            m_map[j][i].visited = false; 
        }
    }
}

void Map::set_cell_wall(NodePosition cell, Direction direction){
    switch(direction){
        case Direction::North:
            m_map[cell.y][cell.x].north_wall = true; 
            if(cell.y != m_maze_height-1){
                m_map[cell.y+1][cell.x].south_wall = true; 
            }
            API::setWall(cell.x, cell.y, 'n'); 
            //log("wall north"); 
            break; 
        case Direction::East:
            m_map[cell.y][cell.x].east_wall = true; 
            if(cell.x != m_maze_width-1){
                m_map[cell.y][cell.x+1].west_wall = true; 
            }
            API::setWall(cell.x, cell.y, 'e'); 
            //log("wall east"); 
            break; 
        case Direction::South:
            m_map[cell.y][cell.x].south_wall = true; 
            if(cell.y != 0){
                m_map[cell.y-1][cell.x].north_wall = true; 
            }
            API::setWall(cell.x, cell.y, 's'); 
            //log("wall south"); 
            break; 
        case Direction::West:
            m_map[cell.y][cell.x].west_wall = true; 
            if(cell.x != 0){
                m_map[cell.y][cell.x-1].east_wall = true; 
            }
            API::setWall(cell.x, cell.y, 'w'); 
            //log("wall west"); 
            break; 
    }

}

void Map::set_cell_parent(NodePosition cell, NodePosition parent){
    m_map[cell.y][cell.x].parent = m_map[parent.y][parent.x].pos; 
}
NodePosition Map::get_cell_parent(NodePosition cell){
    return m_map[cell.y][cell.x].parent; 
}


void Map::set_start(NodePosition start){
    m_start = start; 
}

bool Map::cell_north_valid(NodePosition cell){
    if(cell.y == m_maze_height-1){
        return false; 
    }

    return not (m_map[cell.y][cell.x].north_wall || m_map[cell.y+1][cell.x].visited); 
}
bool Map::cell_east_valid(NodePosition cell){ 
    if(cell.x == m_maze_width-1){
        return false; 
    }

    return not (m_map[cell.y][cell.x].east_wall || m_map[cell.y][cell.x+1].visited); 
}
bool Map::cell_south_valid(NodePosition cell){ 
    if(cell.y == 0){
        return false; 
    }

    return not (m_map[cell.y][cell.x].south_wall || m_map[cell.y-1][cell.x].visited); 
}
bool Map::cell_west_valid(NodePosition cell){ 
    if(cell.x == 0){
        return false; 
    }

    return not (m_map[cell.y][cell.x].west_wall || m_map[cell.y][cell.x-1].visited); 
}


bool Map::cell_visited(NodePosition cell){
    return m_map[cell.y][cell.x].visited; 
}

bool Map::cell_dead(NodePosition cell){
    if(cell_north_valid(cell) ||
       cell_east_valid(cell) ||
       cell_south_valid(cell) ||
       cell_west_valid(cell)){

        return false; 
    }
            
    return true; 
}
 

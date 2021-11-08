#include <iostream>
#include "Util.h"

void log(const std::string& text){
    std::cerr << text << std::endl; 
}

void Map::set_default_map(){
    for(int i=0; i<m_maze_width; i++){
        for(int j=0; j<m_maze_height; j++){
            m_map[j][i].pos = {i, j}; 
        }
    }
    // default belief m_map
    //     --------
    //     |      |
    //     |      |
    //     | |    |
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
    m_map[0][0].east_wall = true; 

    return; 
}

void Map::set_cell_visited(Node_Pos cell){
    m_map[cell.y][cell.x].visited = true; 
    return; 
}

void Map::set_cell_wall(Node_Pos cell, Direction direction){
    switch(direction){
        case Direction::North:
            m_map[cell.y][cell.x].north_wall = true; 
        case Direction::East:
            m_map[cell.y][cell.x].east_wall = true; 
        case Direction::South:
            m_map[cell.y][cell.x].south_wall = true; 
        case Direction::West:
            m_map[cell.y][cell.x].west_wall = true; 

        default:
            log("set wall error"); 
    }

}

bool Map::cell_north_valid(Node_Pos cell){
    if(cell.y == m_maze_height-1){
        return false; 
    }

    return not (m_map[cell.y][cell.x].north_wall || m_map[cell.y+1][cell.x].visited); 
}
bool Map::cell_east_valid(Node_Pos cell){ 
    if(cell.x == m_maze_width-1){
        return false; 
    }

    return not (m_map[cell.y][cell.x].east_wall || m_map[cell.y][cell.x+1].visited); 
}
bool Map::cell_south_valid(Node_Pos cell){ 
    if(cell.y == 0){
        return false; 
    }

    return not (m_map[cell.y][cell.x].south_wall || m_map[cell.y-1][cell.x].visited); 
}
bool Map::cell_west_valid(Node_Pos cell){ 
    if(cell.x == 0){
        return false; 
    }

    return not (m_map[cell.y][cell.x].west_wall || m_map[cell.y][cell.x-1].visited); 
}


bool Map::cell_visited(Node_Pos cell){
    return m_map[cell.y][cell.x].visited; 
}
 

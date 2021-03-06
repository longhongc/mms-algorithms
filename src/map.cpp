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
        API::setWall(i, m_maze_height-1, 'n'); 
    }
    // East wall
    for(int j=0; j<m_maze_height; j++){
        m_map[j][m_maze_width-1].east_wall = true;  
        API::setWall(m_maze_width-1, j, 'e'); 
    }
    // South wall
    for(int i=0; i<m_maze_width; i++){
        m_map[0][i].south_wall = true; 
        API::setWall(i, 0, 's'); 
    }
    // West wall
    for(int j=0; j<m_maze_height; j++){
        m_map[j][0].west_wall = true;  
        API::setWall(0, j, 'w'); 
    }

    API::setText(m_goal.x, m_goal.y, "goal"); 
    API::setColor(m_goal.x, m_goal.y, 'y'); 
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
            //log("wall north"); 
            m_map[cell.y][cell.x].north_wall = true; 
            // mark south wall of north cell 
            if(cell.y != m_maze_height-1){
                m_map[cell.y+1][cell.x].south_wall = true; 
            }
            API::setWall(cell.x, cell.y, 'n'); 
            break; 
        case Direction::East:
            //log("wall east"); 
            m_map[cell.y][cell.x].east_wall = true; 
            // mark west wall of east cell 
            if(cell.x != m_maze_width-1){
                m_map[cell.y][cell.x+1].west_wall = true; 
            }
            API::setWall(cell.x, cell.y, 'e'); 
            break; 
        case Direction::South:
            //log("wall south"); 
            m_map[cell.y][cell.x].south_wall = true; 
            // mark north wall of south cell 
            if(cell.y != 0){
                m_map[cell.y-1][cell.x].north_wall = true; 
            }
            API::setWall(cell.x, cell.y, 's'); 
            break; 
        case Direction::West:
            //log("wall west"); 
            m_map[cell.y][cell.x].west_wall = true; 
            // mark east wall of west cell 
            if(cell.x != 0){
                m_map[cell.y][cell.x-1].east_wall = true; 
            }
            API::setWall(cell.x, cell.y, 'w'); 
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
    // no north cell for the celing row
    if(cell.y == m_maze_height-1){
        return false; 
    }

    return not (m_map[cell.y][cell.x].north_wall || m_map[cell.y+1][cell.x].visited); 
}
bool Map::cell_east_valid(NodePosition cell){ 
    // no east cell for the rightmost column
    if(cell.x == m_maze_width-1){
        return false; 
    }

    return not (m_map[cell.y][cell.x].east_wall || m_map[cell.y][cell.x+1].visited); 
}
bool Map::cell_south_valid(NodePosition cell){ 
    // no south cell for the bottom row
    if(cell.y == 0){
        return false; 
    }

    return not (m_map[cell.y][cell.x].south_wall || m_map[cell.y-1][cell.x].visited); 
}
bool Map::cell_west_valid(NodePosition cell){ 
    // no west cell for the leftmost column
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
 

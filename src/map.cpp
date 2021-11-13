#include "map.h"
#include "util.h"
#include "API.h"

/* --------------------------------------------------------------------------*/
/**
 * @Brief Calculating the left direction of a Direction
 *        Implement this because the mouse in simulator can only detect relative walls of its direction, ie: left, right, front
 *        Map relative direction (left, right) to absolute direction (North, East, South, West)
 *
 * @Param current: the input direction
 *
 * @Returns the left direction  
 */
/* --------------------------------------------------------------------------*/
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

/* --------------------------------------------------------------------------*/
/**
 * @Brief Calculating the right direction of a Direction
 *        Implement this because the mouse in simulator can only detect relative walls of its direction, ie: left, right, front
 *        Map relative direction (left, right) to absolute direction (North, East, South, West)
 *
 * @Param current: the input direction
 *
 * @Returns the right direction 
 */
/* --------------------------------------------------------------------------*/
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

/* --------------------------------------------------------------------------*/
/**
 * @Brief Set up a default map with walls surrounding it 
 */
/* --------------------------------------------------------------------------*/
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

/* --------------------------------------------------------------------------*/
/**
 * @Brief Set a cell in the map as visited
 *
 * @Param cell: a node position (x, y) on the map
 */
/* --------------------------------------------------------------------------*/
void Map::set_cell_visited(NodePosition cell){
    m_map[cell.y][cell.x].visited = true; 
}

/* --------------------------------------------------------------------------*/
/**
 * @Brief Mark a cell unvisited
 *
 * @Param cell: a node position (x, y) on the map
 */
/* --------------------------------------------------------------------------*/
void Map::clear_cell_visited(NodePosition cell){
    m_map[cell.y][cell.x].visited = false; 
}

/* --------------------------------------------------------------------------*/
/**
 * @Brief Mark all the cells unvisited
 */
/* --------------------------------------------------------------------------*/
void Map::clear_all_visited(){
    for(int i=0; i<m_maze_width; i++){
        for(int j=0; j<m_maze_height; j++){
            m_map[j][i].visited = false; 
        }
    }
}

/* --------------------------------------------------------------------------*/
/**
 * @Brief Mark the detected wall around the cell
 *        Also mark the wall of the adjacent cell
 *
 * @Param cell: a node position (x, y) on the map
 * @Param direction: the detected wall absolute direction (North, East, South, West)
 */
/* --------------------------------------------------------------------------*/
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

/* --------------------------------------------------------------------------*/
/**
 * @Brief Set the previous cell on the path as its parent cell 
 *
 * @Param cell: the current node position (x, y)
 * @Param parent: the previous node position on the path, ie: (x-1, y)
 */
/* --------------------------------------------------------------------------*/
void Map::set_cell_parent(NodePosition cell, NodePosition parent){
    m_map[cell.y][cell.x].parent = m_map[parent.y][parent.x].pos; 
}

/* --------------------------------------------------------------------------*/
/**
 * @Brief Get the node position of the previous cell on the path
 *
 * @Param cell: the current node position (x, y)
 *
 * @Returns parent cell node position   
 */
/* --------------------------------------------------------------------------*/
NodePosition Map::get_cell_parent(NodePosition cell){
    return m_map[cell.y][cell.x].parent; 
}


/* --------------------------------------------------------------------------*/
/**
 * @Brief Set the node position of the starting cell  
 *
 * @Param start: a node position (x, y) on the map
 */
/* --------------------------------------------------------------------------*/
void Map::set_start(NodePosition start){
    m_start = start; 
}

/* --------------------------------------------------------------------------*/
/**
 * @Brief Check if the availability of the adjacent cell in abosolute direction
 *               
 * @Param cell: the current node position (x, y)
 *
 * @Returns true if no walls in the abosoute direction or the adjacent cell is not visited 
 */
/* --------------------------------------------------------------------------*/
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

/* --------------------------------------------------------------------------*/
/**
 * @Brief Check if a cell has been visited
 *
 * @Param cell: a node position (x, y) on the map
 *
 * @Returns true if a cell is marked as visited  
 */
/* --------------------------------------------------------------------------*/
bool Map::cell_visited(NodePosition cell){
    return m_map[cell.y][cell.x].visited; 
}

/* --------------------------------------------------------------------------*/
/**
 * @Brief Check if a cell is a dead end   
 *
 * @Param cell: a node position (x, y) on the map
 *
 * @Returns false if one of the direction is valid   
 */
/* --------------------------------------------------------------------------*/
bool Map::cell_dead(NodePosition cell){
    if(cell_north_valid(cell) ||
       cell_east_valid(cell) ||
       cell_south_valid(cell) ||
       cell_west_valid(cell)){

        return false; 
    }
            
    return true; 
}
 

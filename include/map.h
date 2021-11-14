/**
 * @file map.h
 * @Brief All the information relating to the maze 
 * @author Chang-Hong Chen(longhongc@gmail.com), Prateek Verma(verma@termpmail.umd.edu)
 * @date 2021-11-13
 */

#ifndef MAP_H
#define MAP_H

#include <array>

/* --------------------------------------------------------------------------*/
/**
 * @Brief The position (x, y) of a cell
 */
/* --------------------------------------------------------------------------*/
struct NodePosition{
    int x = 0; 
    int y = 0; 
    bool operator==(const NodePosition &rhs) const{
        return this->x == rhs.x && this->y == rhs.y; 
    }
    bool operator!=(const NodePosition &rhs) const{
        return this->x != rhs.x || this->y != rhs.y; 
    }

}; 

/* --------------------------------------------------------------------------*/
/**
 * @Brief The complete information of a cell
 */
/* --------------------------------------------------------------------------*/
struct Node{
    NodePosition pos; // the current postion (x, y)
    NodePosition parent; // the previous cell position on the path 

    // define the wall of a cell in absolute direction
    bool north_wall = false; 
    bool east_wall = false; 
    bool south_wall = false; 
    bool west_wall = false; 
    bool visited = false; 
}; 

/* --------------------------------------------------------------------------*/
/**
 * @Brief Define the absolute direction
 *        Up -> North 
 *        Right -> East 
 *        Down -> South 
 *        Left -> West 
 */
/* --------------------------------------------------------------------------*/
enum class Direction{North, East, South, West}; 

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
Direction direction_left(Direction current); 

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

Direction direction_right(Direction current); 

/* --------------------------------------------------------------------------*/
/**
 * @Brief The complete information of a maze map
 */
/* --------------------------------------------------------------------------*/
class Map{
    public:
        Map(NodePosition start={0, 0}, NodePosition goal={8, 8})
            :m_start{start}, m_goal{goal}{
        }

        /* --------------------------------------------------------------------------*/
        /**
         * @Brief Set up a default map with walls surrounding it 
         */
        /* --------------------------------------------------------------------------*/
        void set_default(); 

        /* --------------------------------------------------------------------------*/
        /**
         * @Brief Set a cell in the map as visited
         *
         * @Param cell: a node position (x, y) on the map
         */
        /* --------------------------------------------------------------------------*/
        void set_cell_visited(NodePosition cell); 

        /* --------------------------------------------------------------------------*/
        /**
         * @Brief Mark a cell unvisited
         *
         * @Param cell: a node position (x, y) on the map
         */
        /* --------------------------------------------------------------------------*/
        void clear_cell_visited(NodePosition cell); 

        /* --------------------------------------------------------------------------*/
        /**
         * @Brief Mark all the cells unvisited
         */
        /* --------------------------------------------------------------------------*/
        void clear_all_visited(); 

        /* --------------------------------------------------------------------------*/
        /**
         * @Brief Mark the detected wall around the cell
         *        Also mark the wall of the adjacent cell
         *
         * @Param cell: a node position (x, y) on the map
         * @Param direction: the detected wall absolute direction (North, East, South, West)
         */
        /* --------------------------------------------------------------------------*/
        void set_cell_wall(NodePosition cell, Direction direction); 

        /* --------------------------------------------------------------------------*/
        /**
         * @Brief Set the previous cell on the path as its parent cell 
         *
         * @Param cell: the current node position (x, y)
         * @Param parent: the previous node position on the path, ie: (x-1, y)
         */
        /* --------------------------------------------------------------------------*/
        void set_cell_parent(NodePosition cell, NodePosition parent); 

        /* --------------------------------------------------------------------------*/
        /**
         * @Brief Get the node position of the previous cell on the path
         *
         * @Param cell: the current node position (x, y)
         *
         * @Returns parent cell node position   
         */
        /* --------------------------------------------------------------------------*/
        NodePosition get_cell_parent(NodePosition cell); 

        /* --------------------------------------------------------------------------*/
        /**
         * @Brief Set the node position of the starting cell  
         *
         * @Param start: a node position (x, y) on the map
         */
        /* --------------------------------------------------------------------------*/
        void set_start(NodePosition start); 

        /* --------------------------------------------------------------------------*/
        /**
         * @Brief Check if the availability of the adjacent cell in abosolute direction
         *               
         * @Param cell: the current node position (x, y)
         *
         * @Returns true if no walls in the abosoute direction or the adjacent cell is not visited 
         */
        /* --------------------------------------------------------------------------*/
        bool cell_north_valid(NodePosition cell); 
        bool cell_east_valid(NodePosition cell); 
        bool cell_south_valid(NodePosition cell); 
        bool cell_west_valid(NodePosition cell); 

        /* --------------------------------------------------------------------------*/
        /**
         * @Brief Check if a cell has been visited
         *
         * @Param cell: a node position (x, y) on the map
         *
         * @Returns true if a cell is marked as visited  
         */
        /* --------------------------------------------------------------------------*/
        bool cell_visited(NodePosition cell); 

        /* --------------------------------------------------------------------------*/
        /**
         * @Brief Check if a cell is a dead end   
         *
         * @Param cell: a node position (x, y) on the map
         *
         * @Returns false if one of the direction is valid   
         */
        /* --------------------------------------------------------------------------*/
        bool cell_dead(NodePosition cell); 

    private:
        static const int m_maze_width = 16; 
        static const int m_maze_height = 16; 

        std::array<std::array<Node, m_maze_width>, m_maze_height> m_map;
        NodePosition m_start; 
        NodePosition m_goal; 
}; 

#endif

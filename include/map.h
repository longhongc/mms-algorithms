#ifndef MAP_H
#define MAP_H

#include <array>

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

struct Node{
    NodePosition pos; 
    NodePosition parent; 
    bool north_wall = false; 
    bool east_wall = false; 
    bool south_wall = false; 
    bool west_wall = false; 
    bool visited = false; 
}; 

enum class Direction{North, East, South, West}; 

Direction direction_left(Direction current); 
Direction direction_right(Direction current); 

class Map{
    public:
        Map(NodePosition start={0, 0}, NodePosition goal={8, 8})
            :m_start{start}, m_goal{goal}{
        }

        void set_default(); 
        void set_cell_visited(NodePosition cell); 
        void clear_cell_visited(NodePosition cell); 
        void clear_all_visited(); 

        void set_cell_wall(NodePosition cell, Direction direction); 
        void set_cell_parent(NodePosition cell, NodePosition parent); 
        NodePosition get_cell_parent(NodePosition cell); 

        void set_start(NodePosition start); 

        bool cell_north_valid(NodePosition cell); 
        bool cell_east_valid(NodePosition cell); 
        bool cell_south_valid(NodePosition cell); 
        bool cell_west_valid(NodePosition cell); 
        bool cell_visited(NodePosition cell); 

        bool cell_dead(NodePosition cell); 

    private:
        static const int m_maze_width = 16; 
        static const int m_maze_height = 16; 

        std::array<std::array<Node, m_maze_width>, m_maze_height> m_map;
        NodePosition m_start; 
        NodePosition m_goal; 
}; 

#endif

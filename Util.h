#ifndef NODE_H
#define NODE_H

#include <string>
#include <array>

struct Node_Pos{
    int x = 0; 
    int y = 0; 
}; 

struct Node{
    Node_Pos pos; 
    bool north_wall = false; 
    bool east_wall = false; 
    bool south_wall = false; 
    bool west_wall = false; 
    bool visited = false; 
}; 

enum class Direction{North, East, South, West}; 

class Map{
    public:
        Map(Node_Pos start={0, 0}, Node_Pos goal={8, 8})
                          :m_start{start}, m_goal{goal}{
        }

        void set_default_map(); 
        void set_cell_visited(Node_Pos cell); 
        void set_cell_wall(Node_Pos cell, Direction direction); 

        bool cell_north_valid(Node_Pos cell); 
        bool cell_east_valid(Node_Pos cell); 
        bool cell_south_valid(Node_Pos cell); 
        bool cell_west_valid(Node_Pos cell); 
        bool cell_visited(Node_Pos cell); 

    private:
        static const int m_maze_width = 16; 
        static const int m_maze_height = 16; 

        std::array<std::array<Node, m_maze_width>, m_maze_height> m_map;
        Node_Pos m_start; 
        Node_Pos m_goal; 
}; 

void log(const std::string& text); 



#endif

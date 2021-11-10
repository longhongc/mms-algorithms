#ifndef MOUSE_H
#define MOUSE_H

#include <vector>

#include "map.h"

class Mouse{
    public: 
        Mouse()
            :find_goal{false},
             m_current_cell{0, 0},
             m_goal_cell{8, 8},
             m_direction{Direction::North},
             m_belief_map(m_current_cell, m_goal_cell), 
             m_real_map(m_current_cell, m_goal_cell) {

            m_belief_map.set_default();  
            m_real_map.set_default();  

        }

        bool search_with_DFS(); 
        bool follow_path(); 
        void reset_search(); 

        bool find_goal; 

    private: 
        bool move_to_cell(NodePosition cell); 
        bool update_walls(); 
        void change_direction(Direction direction); 
        NodePosition m_current_cell; 
        NodePosition m_goal_cell; 

        Direction m_direction; 

        Map m_belief_map; 
        Map m_real_map; 
 

        std::vector<NodePosition> m_path; 
        std::vector<NodePosition> m_visited; 
}; 
#endif
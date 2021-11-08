#ifndef MOUSE_H
#define MOUSE_H

#include <vector>

#include "Util.h"

class Mouse{
    public: 
        Mouse(): m_current_cell{0, 0}, m_goal_cell{8, 8}{
            m_belief_map = Map(m_current_cell, m_goal_cell); 
            m_belief_map.set_default_map();  

        }

        bool search_with_DFS(); 
        bool follow_path(); 
        void reset_search(); 

        bool find_goal; 

    private: 
        Node_Pos m_current_cell; 
        Node_Pos m_goal_cell; 

        Map m_belief_map; 
 

        std::vector<Node_Pos> m_path; 
        std::vector<Node_Pos> m_visited; 
}; 
#endif

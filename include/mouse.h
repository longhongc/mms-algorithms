#ifndef MOUSE_H
#define MOUSE_H

#include <vector>

#include "map.h"

/* --------------------------------------------------------------------------*/
/**
 * @Brief A mouse with several searching methods and information of a default map
 */
/* --------------------------------------------------------------------------*/
class Mouse{
    public: 
        Mouse()
            :m_current_cell{0, 0},
             m_goal_cell{8, 8},
             m_direction{Direction::North},
             m_belief_map(m_current_cell, m_goal_cell), 
             m_real_map(m_current_cell, m_goal_cell), 
             reach_goal{false} {

            m_belief_map.set_default();  
            m_real_map.set_default();  

        }

        bool offline_DFS_search(); 
        bool online_DFS_search(); 


    private: 
        void reset_search(); 
        bool search_belief_map(); 
        bool follow_path(); 
        bool move_to_cell(NodePosition cell); 
        bool update_walls(); 
        void change_direction(Direction direction); 
        NodePosition m_current_cell; 
        NodePosition m_goal_cell; 

        // abosolute direction of the mouse
        Direction m_direction; 

        // empty map without real wall information 
        Map m_belief_map; 
        // updated map with detected walls information in the maze
        Map m_real_map; 
 
        // a path from start to the goal
        std::vector<NodePosition> m_goal_path; 

        bool reach_goal; 
}; 
#endif

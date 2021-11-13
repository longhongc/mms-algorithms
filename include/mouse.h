/**
 * @file mouse.h
 * @Brief the mouse behavior class 
 * @author Chang-Hong Chen(longhongc@gmail.com), Prateek Verma(verma@termpmail.umd.edu)
 * @version 2.1.0
 * @date 2021-11-13
 */

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

        // search algorithms
        /* --------------------------------------------------------------------------*/
        /**
         * @Brief The DFS algorithm that explore the node tree and move at the same time using real-time data from the real map  
         *        Color notation: gray is the DFS path, cell after backtracking will become dark gray 
         *                        orange is the next target cell on the stack
         *                        dark red is for the dead cell
         *
         * @Returns true if a path to goal has been found  
         */
        /* --------------------------------------------------------------------------*/
        bool offline_DFS_search(); 

        /* --------------------------------------------------------------------------*/
        /**
         * @Brief The DFS serach algorithm that construct search path with the default/updated belief map of the mouse
         *        Move the mouse with the constructed path util it encounters a new wall not on the belief map or finds the goal
         *
         * @Returns   
         */
        /* --------------------------------------------------------------------------*/
        bool online_DFS_search(); 


    private: 
        /* --------------------------------------------------------------------------*/
        /**
         * @Brief Reset states for a new run of offline DFS 
         *        Reset all the previous path
         *        Set current cell as new start cell
         *        Update the belief map with the real wall data on the real map
         */
        /* --------------------------------------------------------------------------*/
        void reset_search(); 

        /* --------------------------------------------------------------------------*/
        /**
         * @Brief The DFS serach algorithm that search with the default/updated belief map of the mouse
         *        Color notation: gray is the DFS path, cell after backtracking will become dark gray 
         *
         * @Returns true if a path to goal has been found  
         */
        /* --------------------------------------------------------------------------*/
        bool search_belief_map(); 

        /* --------------------------------------------------------------------------*/
        /**
         * @Brief the mouse will move along a give path m_goal_path generated from the offline DFS
         *
         * @Returns true if the mouse arrive the goal cell, false if the mouse hits a wall not in its belief map  
         */
        /* --------------------------------------------------------------------------*/
        bool follow_path(); 

        /* --------------------------------------------------------------------------*/
        /**
         * @Brief Move the mouse to next cell on the path
         *
         * @Param cell: a node position (x, y) on the map
         *
         * @Returns true if the move success, false if there is a wall in front of it    
         */
        /* --------------------------------------------------------------------------*/
        bool move_to_cell(NodePosition cell); 

        /* --------------------------------------------------------------------------*/
        /**
         * @Brief Mark the walls of a cell on the real map through relative wall detection from the mouse 
         *
         * @Returns false if a wall is in front of the mouse   
         */
        /* --------------------------------------------------------------------------*/
        bool update_walls(); 

        /* --------------------------------------------------------------------------*/
        /**
         * @Brief  Change the direction of the mouse
         *
         * @Param direction: target direction
         */
        /* --------------------------------------------------------------------------*/
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

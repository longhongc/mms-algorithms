# mms-algorithms
Implement path finding algorithms using Micromouse simulator  
[Micromouse simulator](https://github.com/mackorone/mms)

### Algorithms:  
- [**Online DFS**](#online-dfs): grow DFS tree while exploring the maze      
- [**Offline DFS**](#offline-dfs): plan DFS path on a belief map then move along the generated path and update new observations to the belief map       

## Build 
```
mkdir build
cd build  
cmake .. && make  
```
## Run
Fill the edit mouse configuration in mms simulator

![mms_run_configuration](https://user-images.githubusercontent.com/28807825/141685015-08d0c26d-0234-48be-93fb-0ca3689399a8.png)

## Algorithms
### Online DFS
![online_DFS](https://github.com/longhongc/mms-algorithms/blob/master/videos/online_DFS.gif)  
<pre>
Yello: unreached goal 
Green: reached goal 
Orange: next search cell 
Gray: traveled path
Dark Gray: backtracked cells
Dark Red: dead cells
</pre>
 
The mouse starts from the start cell, and along the path pushes all child cells of current cell to a node stack. It pops the top of the stack and set it as the next cell to explore. After iterations of exploration when it enters a dead end, it will find its next searching cell by poping the stack again until there is an available cell to explore. The mouse will follow its trail and backtrack to the parent of the available cell and move to that available cell to continue its exploration until it finds the goal or searches all the cells if the maze is unsolvable. 

The red line is where backtracking happens.  
![online_DFS_graph](https://github.com/longhongc/mms-algorithms/blob/master/videos/online_DFS_graph.png)  

In the implementation, I added some feature that the mouse will recognize that some cells are actually dead ends, and it will discard those cells when poping from the node stack. The dark red color labels the cells that the mouse thinks are unavailable.

### Offline DFS
![offline_DFS](https://github.com/longhongc/mms-algorithms/blob/master/videos/offline_DFS.gif)  
<pre>
Yello: unreached goal 
Green: reached goal 
Orange: next search cell 
Gray: path generated from belief map
Dark Gray: backtracked cells
</pre>

The mouse first constructs a belief map from the default map. It then runs the DFS search on this imaginary map. After the path to goal is generated, the mouse will follow the path. It will soon be blocked by newly discoverd wall that is not on its belief map. It will update its map with the newly discoverd wall then run the DFS on the belief map again. After iterataions of searching on belief map and following the generated map, it will either find the goal or fail becuase of the unsolvable map. 


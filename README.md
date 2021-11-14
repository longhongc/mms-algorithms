# mms-algorithms
Implement path finding algorithms using Micromouse simulator  
[Micromouse simulator](https://github.com/mackorone/mms)

### Algorithms:  
- [**Online DFS**](#online-dfs): grow DFS tree while exploring the maze      
- [**Offline DFS**](#offline-dfs): pre-plan DFS path on a belief map then move along the path and update new observations to the belief map       

## Build 
```
mkdir build
cd build  
cmake .. && make  
```
## Run
Fill the executable file name in run command

![Screenshot from 2021-11-11 13-22-23](https://user-images.githubusercontent.com/28807825/141351305-df904dfe-25ce-42ff-aeb6-d9f3b5eab3f5.png)

## Algorithms
### Online DFS
![online_DFS](https://github.com/longhongc/mms-algorithms/blob/master/videos/online_DFS.gif)  
<pre>
color notation: 
    yello: unreached goal 
    green: reached goal 
    orange: next available search cell 
    gray: traveled path
    dark gray: backtracked cells
    dark red: dead cells
</pre>
 
The mouse starts from the start cell, and along the path pushes all child cells of current cell to a node stack. It pops the top of the stack and set it as the next cell to explore. After iterations of exploration when it enters a dead end, it will find its next searching cell by poping the stack again until there is an available cell to explore. The mouse will follow its trail and backtrack to the parent of the available cell and move to that available cell to continue its exploration until it finds the goal or searches all the cells if the maze is unsolvable. 

The red line is where backtracking happens.  
![online_DFS_graph](https://github.com/longhongc/mms-algorithms/blob/master/videos/online_DFS_graph.png)  

In the implementation, I added some feature that the mouse will recognize some cells are actually an dead end, and it will ditch those cells when poping from the node stack. The dark red color labels the cells that the mouse thinks are unavailable.

### Offline DFS
![offline_DFS](https://github.com/longhongc/mms-algorithms/blob/master/videos/offline_DFS.gif)  
<pre>
color notation: 
    yello: unreached goal 
    green: reached goal 
    orange: next available search cell 
    gray: traveled path
    dark gray: backtracked cells
    dark red: dead cells
</pre>

The mouse first constructs a belief map from the default map. It then runs the DFS search on this imaginary map. After the path to goal is generated, the mouse will follow the path. It will soon be blocked by newly discoverd wall that is not on its belief map. It will update its map with the newly discoverd wall then run the DFS on the belief map again. After iterataions of searching on belief map and following the generated map, it will either find the goal or fail becuase of the unsolvable map. 


# mms-algorithms
Implement path finding algorithms using Micromouse simulator  
[Micromouse simulator](https://github.com/mackorone/mms)

### Algorithms:  
- [**Online DFS**](#online-dfs)      
![online_DFS](./videos/online_DFS.gif)
- [**Offline DFS**](#offline-dfs)    
![offline_DFS](./videos/offline_DFS.gif)

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
The mouse pushes child nodes of current node to a node stack, and pops the top of it to explore. After it finds out that this is a dead end, it will find its next searching node by poping the stack until there is an avialiable node to explore. The mouse will follow its trail and backtrack to the avaliable next searching node.

The red line is where backtracking happens.

### Offline DFS

# search.py
# ---------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
# 
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


"""
In search.py, you will implement generic search algorithms which are called by
Pacman agents (in searchAgents.py).
"""

import util

class SearchProblem:
    """
    This class outlines the structure of a search problem, but doesn't implement
    any of the methods (in object-oriented terminology: an abstract class).

    You do not need to change anything in this class, ever.
    """

    def getStartState(self):
        """
        Returns the start state for the search problem.
        """
        # util.raiseNotDefined()

    def isGoalState(self, state):
        """
          state: Search state

        Returns True if and only if the state is a valid goal state.
        """
        # util.raiseNotDefined()

    def getSuccessors(self, state):
        """
          state: Search state

        For a given state, this should return a list of triples, (successor,
        action, stepCost), where 'successor' is a successor to the current
        state, 'action' is the action required to get there, and 'stepCost' is
        the incremental cost of expanding to that successor.
        """
        # util.raiseNotDefined()

    def getCostOfActions(self, actions):
        """
         actions: A list of actions to take

        This method returns the total cost of a particular sequence of actions.
        The sequence must be composed of legal moves.
        """
        # util.raiseNotDefined()


def tinyMazeSearch(problem):
    """
    Returns a sequence of moves that solves tinyMaze.  For any other maze, the
    sequence of moves will be incorrect, so only use this for tinyMaze.
    """
    from game import Directions
    s = Directions.SOUTH
    w = Directions.WEST
    return  [s, s, w, s, w, w, s, w]

def depthFirstSearch(problem: SearchProblem):
    """
    Search the deepest nodes in the search tree first.

    Your search algorithm needs to return a list of actions that reaches the
    goal. Make sure to implement a graph search algorithm.

    To get started, you might want to try some of these simple commands to
    understand the search problem that is being passed in:

    print("Start:", problem.getStartState())
    print("Is the start a goal?", problem.isGoalState(problem.getStartState()))
    print("Start's successors:", problem.getSuccessors(problem.getStartState()))
    """
    "*** YOUR CODE HERE ***"
    from game import Directions

    S=util.Stack()
    parent={}
    visited={}
    init=problem.getStartState()
    p=(init,Directions.STOP,0)
    S.push(p)
    parent[p[0]]=None
    while 1:
        if S.isEmpty():
            return None
        p=S.pop()
        if parent[p[0]]==None:
            visited[p[0]]=[]
        else:
            midlist=visited[parent[p[0]]].copy()
            midlist.append(p[1])
            visited[p[0]]=midlist#标记为访问同时记录路径
        if problem.isGoalState(p[0]):
            break
        successors=problem.getSuccessors(p[0])
        for x in successors:
            if x[0] in visited:
                continue
            else:
                S.push(x)
                parent[x[0]]=p[0]
    return visited[p[0]]




def breadthFirstSearch(problem: SearchProblem):
    """Search the shallowest nodes in the search tree first."""
    "*** YOUR CODE HERE ***"
    from game import Directions

    visited=[]
    Q=util.Queue()
    start=problem.getStartState()
    Q.push((start,[]))
    while 1:
        if Q.isEmpty():
            return None
        state,action=Q.pop()
        if problem.isGoalState(state):
            break
        if state not in visited:#屏蔽掉已经访问过的
            visited.append(state)
            successors=problem.getSuccessors(state)
            for x in successors:
                if x[0] in visited:
                    continue
                else:
                    Q.push((x[0],action+[x[1]]))
    return action

def uniformCostSearch(problem: SearchProblem):
    """Search the node of least total cost first."""
    "*** YOUR CODE HERE ***"
    from game import Directions

    P=util.PriorityQueue()
    store={}
    visited={}
    parent={}
    init=problem.getStartState()
    parent[init]=None
    P.push(init,0)
    store[init]=[Directions.STOP,0]
    while 1:
        if P.isEmpty():
            return None
        loc=P.pop()
        if parent[loc]==None:
            visited[loc]=[]
        else:
            midlist=visited[parent[loc]].copy()
            midlist.append(store[loc][0])
            visited[loc]=midlist
        if problem.isGoalState(loc):
            break
        successors = problem.getSuccessors(loc)
        for x in successors:
            if x[0] in visited:
                continue
            else:
                P.update(x[0], x[2]+store[loc][1])
                if x[0] in store:
                    if x[2]+store[loc][1]<store[x[0]][1]:
                        store[x[0]][1]=x[2]+store[loc][1]
                        store[x[0]][0]=x[1]
                        parent[x[0]]=loc
                else:
                    store[x[0]]=[Directions.STOP,0]
                    store[x[0]][1] = x[2] + store[loc][1]
                    store[x[0]][0] = x[1]
                    parent[x[0]] = loc#存储到达该状态的耗散
    return visited[loc]

def nullHeuristic(state, problem=None):
    """
    A heuristic function estimates the cost from the current state to the nearest
    goal in the provided SearchProblem.  This heuristic is trivial.
    """
    return 0

def aStarSearch(problem: SearchProblem, heuristic=nullHeuristic):
    """Search the node that has the lowest combined cost and heuristic first."""
    "*** YOUR CODE HERE ***"
    visited = []
    Q = util.PriorityQueue()
    start = problem.getStartState()
    Q.push((start, []),0)
    while 1:
        if Q.isEmpty():
            return None
        state, action = Q.pop()
        if problem.isGoalState(state):
            break
        if state not in visited:
            visited.append(state)
            successors = problem.getSuccessors(state)
            for x in successors:
                if x[0] in visited:
                    continue
                else:
                    F=heuristic(x[0], problem)+problem.getCostOfActions(action + [x[1]])#将耗散值和估计距离的和作为权值
                    Q.push((x[0], action + [x[1]]),F)
    return action


# Abbreviations
bfs = breadthFirstSearch
dfs = depthFirstSearch
astar = aStarSearch
ucs = uniformCostSearch

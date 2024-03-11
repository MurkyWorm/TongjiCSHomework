# multiAgents.py
# --------------
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


from util import manhattanDistance
from game import Directions
import random, util

from game import Agent
from pacman import GameState

class ReflexAgent(Agent):
    """
    A reflex agent chooses an action at each choice point by examining
    its alternatives via a state evaluation function.

    The code below is provided as a guide.  You are welcome to change
    it in any way you see fit, so long as you don't touch our method
    headers.
    """


    def getAction(self, gameState: GameState):
        """
        You do not need to change this method, but you're welcome to.

        getAction chooses among the best options according to the evaluation function.

        Just like in the previous project, getAction takes a GameState and returns
        some Directions.X for some X in the set {NORTH, SOUTH, WEST, EAST, STOP}
        """
        # Collect legal moves and successor states
        legalMoves = gameState.getLegalActions()

        # Choose one of the best actions
        scores = [self.evaluationFunction(gameState, action) for action in legalMoves]
        bestScore = max(scores)
        bestIndices = [index for index in range(len(scores)) if scores[index] == bestScore]
        chosenIndex = random.choice(bestIndices) # Pick randomly among the best

        "Add more of your code here if you want to"

        return legalMoves[chosenIndex]

    def evaluationFunction(self, currentGameState: GameState, action):
        """
        Design a better evaluation function here.

        The evaluation function takes in the current and proposed successor
        GameStates (pacman.py) and returns a number, where higher numbers are better.

        The code below extracts some useful information from the state, like the
        remaining food (newFood) and Pacman position after moving (newPos).
        newScaredTimes holds the number of moves that each ghost will remain
        scared because of Pacman having eaten a power pellet.

        Print out these variables to see what you're getting, then combine them
        to create a masterful evaluation function.
        """
        # Useful information you can extract from a GameState (pacman.py)
        successorGameState = currentGameState.generatePacmanSuccessor(action)
        newPos = successorGameState.getPacmanPosition()
        newFood = successorGameState.getFood()
        newGhostStates = successorGameState.getGhostStates()
        newScaredTimes = [ghostState.scaredTimer for ghostState in newGhostStates]
        "*** YOUR CODE HERE ***"

        GhostLocation=newGhostStates[0].getPosition()
        x=abs(newPos[0]-GhostLocation[0])
        y=abs(newPos[1]-GhostLocation[1])
        dGhost=x+y#吃豆人和鬼的距离

        min=10000
        FoodLocation=newFood.asList()
        for i in FoodLocation:
            x = abs(newPos[0] - i[0])
            y = abs(newPos[1] - i[1])
            temp=x+y
            if min>temp:
                min=temp#最近的豆子

        num = newFood.count()

        if dGhost<=2:
            Evaluation=dGhost*100#如果鬼的距离过近，则以鬼为主要评价因素
            if num == 0:
                Evaluation = Evaluation+10
            else:
                Evaluation = Evaluation-num * 1 + 1.0 / min#次要以豆的距离为评价因素
            Evaluation=Evaluation-10000
        else:
            if num==0:
                Evaluation=10000
            else:
                Evaluation=-num*100+100.0/min#如果鬼的距离不近，以豆子信息为评价因素
        return  Evaluation

def scoreEvaluationFunction(currentGameState: GameState):
    """
    This default evaluation function just returns the score of the state.
    The score is the same one displayed in the Pacman GUI.

    This evaluation function is meant for use with adversarial search agents
    (not reflex agents).
    """
    return currentGameState.getScore()

class MultiAgentSearchAgent(Agent):
    """
    This class provides some common elements to all of your
    multi-agent searchers.  Any methods defined here will be available
    to the MinimaxPacmanAgent, AlphaBetaPacmanAgent & ExpectimaxPacmanAgent.

    You *do not* need to make any changes here, but you can if you want to
    add functionality to all your adversarial search agents.  Please do not
    remove anything, however.

    Note: this is an abstract class: one that should not be instantiated.  It's
    only partially specified, and designed to be extended.  Agent (game.py)
    is another abstract class.
    """

    def __init__(self, evalFn = 'scoreEvaluationFunction', depth = '2'):
        self.index = 0 # Pacman is always agent index 0
        self.evaluationFunction = util.lookup(evalFn, globals())
        self.depth = int(depth)

class MinimaxAgent(MultiAgentSearchAgent):
    """
    Your minimax agent (question 2)
    """

    def getAction(self, gameState: GameState):
        """
        Returns the minimax action from the current gameState using self.depth
        and self.evaluationFunction.

        Here are some method calls that might be useful when implementing minimax.

        gameState.getLegalActions(agentIndex):
        Returns a list of legal actions for an agent
        agentIndex=0 means Pacman, ghosts are >= 1

        gameState.generateSuccessor(agentIndex, action):
        Returns the successor game state after an agent takes an action

        gameState.getNumAgents():
        Returns the total number of agents in the game

        gameState.isWin():
        Returns whether or not the game state is a winning state

        gameState.isLose():
        Returns whether or not the game state is a losing state
        """
        "*** YOUR CODE HERE ***"
        numAgents=gameState.getNumAgents()
        value=self.minmaxSelect(gameState,numAgents,0)
        return value[1]

    def minmaxSelect(self,gameState: GameState,numAgents,layer):
        actionChoice='Stop'
        if gameState.isLose():
            return [self.evaluationFunction(gameState),'Stop']
        if gameState.isWin():
            return [self.evaluationFunction(gameState), 'Stop']#如果胜利或者失败，则不必递归下去
        if layer==numAgents*self.depth:
            return [self.evaluationFunction(gameState),actionChoice]#递归到最后一层时结束
        else:
            max=-100000
            maxAction='Stop'
            min=100000
            minAction='Stop'
            legalActions=gameState.getLegalActions(layer%numAgents)
            for action in legalActions:
                legalState=gameState.generateSuccessor(layer%numAgents, action)
                value=self.minmaxSelect(legalState,numAgents,layer+1)
                if max<value[0]:
                    max=value[0]
                    maxAction=action
                if min>value[0]:
                    min=value[0]
                    minAction=action#求出子状态的最大最小值和对应的行动
            if layer%numAgents==0:
                return [max,maxAction]
            else:
                return [min,minAction]#根据结点的类型返回对应值

class AlphaBetaAgent(MultiAgentSearchAgent):
    """
    Your minimax agent with alpha-beta pruning (question 3)
    """

    def getAction(self, gameState: GameState):
        """
        Returns the minimax action using self.depth and self.evaluationFunction
        """
        "*** YOUR CODE HERE ***"
        numAgents=gameState.getNumAgents()
        value=self.alphaBetaSelect(gameState,0,numAgents,[-100000],[100000])
        return value[1]

    def alphaBetaSelect(self,gameState: GameState,layer,numAgents,pAlpha:list,pBeta:list):
        """
        :param pAlpha: 父辈max结点的alpha值
        :param pBeta: 父辈min结点的beta值
        """
        if gameState.isLose():
            return [self.evaluationFunction(gameState),'Stop']
        if gameState.isWin():
            return [self.evaluationFunction(gameState), 'Stop']
        if layer==numAgents*self.depth:
            return [self.evaluationFunction(gameState), 'Stop']#同问题2
        alpha=-100000
        alphaAction='Stop'
        beta=100000
        betaAction='Stop'
        legalActions = gameState.getLegalActions(layer % numAgents)
        for action in legalActions:
            if layer % numAgents == 0:
                pAlpha.append(alpha)
            else:
                pBeta.append(beta)
            legalState = gameState.generateSuccessor(layer % numAgents, action)
            tem = self.alphaBetaSelect(legalState, layer + 1, numAgents, pAlpha, pBeta)#将该状态的alpha值或者beta值加入列表进行递归
            if layer%numAgents==0:
                if tem[0]>alpha:
                    alpha=tem[0]
                    alphaAction=action
            else:
                if tem[0]<beta:
                    beta=tem[0]
                    betaAction=action
            if layer % numAgents == 0:
                pAlpha.pop()
            else:
                pBeta.pop()
            flag=0
            if layer%numAgents!=0:
                for x in pAlpha:
                    if beta<x:
                        flag=1
                        break
            else:
                for x in pBeta:
                    if alpha>x:
                        flag=1
                        break
            if flag==1:
                break#如果不能更新父辈的alpha值或者beta值，则不必再扩展子节点
        if layer%numAgents==0:
            return [alpha,alphaAction]
        else:
            return [beta,betaAction]

class ExpectimaxAgent(MultiAgentSearchAgent):
    """
      Your expectimax agent (question 4)
    """

    def getAction(self, gameState: GameState):
        """
        Returns the expectimax action using self.depth and self.evaluationFunction

        All ghosts should be modeled as choosing uniformly at random from their
        legal moves.
        """
        "*** YOUR CODE HERE ***"
        numAgents = gameState.getNumAgents()
        value = self.ramdomSelect(gameState, numAgents, 0)
        return value[1]

    def ramdomSelect(self,gameState: GameState,numAgents,layer):
        actionChoice = 'Stop'
        if gameState.isLose():
            return [self.evaluationFunction(gameState), 'Stop']
        if gameState.isWin():
            return [self.evaluationFunction(gameState), 'Stop']
        if layer == numAgents * self.depth:
            return [self.evaluationFunction(gameState), actionChoice]
        else:
            max = -100000
            maxAction = 'Stop'
            min = 0
            minAction = 'Stop'
            legalActions = gameState.getLegalActions(layer % numAgents)
            i=0
            for action in legalActions:
                legalState = gameState.generateSuccessor(layer % numAgents, action)
                value = self.ramdomSelect(legalState, numAgents, layer + 1)
                if max < value[0]:
                    max = value[0]
                    maxAction = action
                min=min+value[0]
                i=i+1
            min=min/i#如果是min结点则该结点的值为子节点值的平均值
            if layer % numAgents == 0:
                return [max, maxAction]
            else:
                return [min, minAction]

def betterEvaluationFunction(currentGameState: GameState):
    """
    Your extreme ghost-hunting, pellet-nabbing, food-gobbling, unstoppable
    evaluation function (question 5).

    DESCRIPTION: <write something here so we know what you did>
    """
    "*** YOUR CODE HERE ***"
    if currentGameState.isWin():
        return 10000+random.random()#使吃掉最后一个后吃豆人知道去哪个地方，防止停在最后一个豆子前
    if currentGameState.isLose():
        return -10000
    walls=currentGameState.getWalls()
    pacmanPosition = currentGameState.getPacmanPosition()
    ghostStates = currentGameState.getGhostStates()
    scaredTimes = [ghostState.scaredTimer for ghostState in ghostStates]
    ghostLocations = currentGameState.getGhostPositions()
    food=currentGameState.getFood()#获取各项信息

    countWalls=0
    if walls[pacmanPosition[0]+1][pacmanPosition[1]]==True:
        countWalls=countWalls+1
    if walls[pacmanPosition[0]-1][pacmanPosition[1]]==True:
        countWalls=countWalls+1
    if walls[pacmanPosition[0]][pacmanPosition[1]+1]==True:
        countWalls=countWalls+1
    if walls[pacmanPosition[0]][pacmanPosition[1]-1]==True:
        countWalls=countWalls+1
    if countWalls==3:
        return -10000#如果是死胡同，返回一个很低的值
    dGhost=10000
    i=0
    for x in ghostLocations:
        if scaredTimes[i]<2:
            tem=abs(pacmanPosition[0]-x[0])+abs(pacmanPosition[1]-x[1])
            if tem<dGhost:
                dGhost=tem#计算最近的鬼的距离
        i=i+1
    min = 10000
    foodLocation = food.asList()
    min_x=0
    min_y=0
    for i in foodLocation:
        x = abs(pacmanPosition[0] - i[0])
        y = abs(pacmanPosition[1] - i[1])
        temp = x + y
        if min > temp:
            min = temp
            min_x=i[0]
            min_y=i[1]# 最近的豆子
    max=0
    for i in foodLocation:
        x = abs(min_x - i[0])
        y = abs(min_y - i[1])
        temp = x + y
        if max < temp:
            max = temp# 离最近豆子最远的豆子
    d=min+max#豆子距离的估计值
    num = food.count()
    if dGhost <= 2:
        Evaluation = dGhost * 100
        if num == 0:
            Evaluation = Evaluation + 10
        else:
            Evaluation = Evaluation - num * 1 + 1.0 / d
        Evaluation = Evaluation - 10000
    else:
        if num == 0:
            Evaluation = 10000
        else:
            Evaluation = -num * 100 + 100.0 / d#同问题1的赋值

    return Evaluation+random.random()/10000+currentGameState.getScore()#防止吃掉某个豆子后不知道去那里


# Abbreviation
better = betterEvaluationFunction

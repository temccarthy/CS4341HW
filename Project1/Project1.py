from SearchEnum import SearchEnum
import Graph
import sys
import Queue
from collections import OrderedDict
# Solution for Project 1 of CS 4341 - A2020 

# Cost functions for latter 5 searches
noCostFunc = lambda nodeList : -1
edgeCostFunc = (lambda nodeList : sum(map(lambda node1, node2 : node1.edges[node2.name], nodeList[:-1], nodeList[1:])))
heuristicCostFunc = lambda nodeList : nodeList[0].heuristic 
aStarCostFunc = lambda nodeList : edgeCostFunc(nodeList) + heuristicCostFunc(nodeList)
costFunctions = {
    SearchEnum.DEPTH_FIRST_SEARCH : noCostFunc,
    SearchEnum.BREADTH_FIRST_SEARCH : noCostFunc,
    SearchEnum.DEPTH_LIMITED_SEARCH : noCostFunc,
    SearchEnum.ITERATIVE_DEEPENING_SEARCH : noCostFunc,
    SearchEnum.UNIFORM_COST_SEARCH : edgeCostFunc,
    SearchEnum.GREEDY_SEARCH : heuristicCostFunc,
    SearchEnum.A_STAR : aStarCostFunc,
    SearchEnum.HILL_CLIMBING : heuristicCostFunc,
    SearchEnum.BEAM_SEARCH : heuristicCostFunc,
}
iterativeLimit = 0 # Limit to use for iterative deepening search

def iterativeDeepening(problem):
    """
    Loop calling the general search function with iterated depth limit to implement Iterative Deepening Search. Return the node from the initial state to the final state.

    Parameters
    ----------
    problem : Graph.Graph
        The graph to use Iterative Deepening Search on.
    
    """
    global iterativeLimit 
    iterativeLimit = 1
    generalReturn = General_Search(problem, SearchEnum.ITERATIVE_DEEPENING_SEARCH)
    while(not generalReturn):
        iterativeLimit += 1
        generalReturn = General_Search(problem, SearchEnum.ITERATIVE_DEEPENING_SEARCH)
    iterativeLimit = 0
    return generalReturn
def General_Search(problem, search):
    """
    Return the solution node or failure to reach node G from node S. Also outputs the expanded nodes and the queues before each expansion.
    
    Parameters
    ----------
    problem : Graph.Graph
        The graph to search from S to G.
    search : SearchEnum.SearchEnum
        The search method to use to search the graph.
    """
    initialState = 'S' # name of the initial state
    finalState = 'G' # Name of the final state

    print("\tExpanded\tQueue")
    if (search == SearchEnum.ITERATIVE_DEEPENING_SEARCH):
        print("L=" + str(iterativeLimit), end="")

    queue = Queue.Queue(Queue.Node([problem.getState(initialState)], costFunctions[search]([problem.getState(initialState)])))
    explored = []
    while len(queue.nodes) > 0:
        oldQueue = str(queue)
        node = queue.Remove_Front()
        explored.append(node.Terminal_State())
        print("\t" + node.Terminal_State() + "\t\t" + oldQueue)
        if node.Terminal_State() == finalState:
            return node
        openedNodes = node.Expand(costFunctions[search], problem, explored, queue)
        isFinished = expand_queue(queue,openedNodes,problem, search)
        if isFinished : # Handle the iterative deepening search return flow. 
            return isFinished
    return False
def expand_queue(queue, newNodesToAddToQueue, problem, search):
    """
    Add the new nodes created from the opened nodes to the queue based on the search strategy. Return the node to a solution if found, false otherwise.

    Parameters
    ----------
    queue : Queue.Queue
        The queue containing the possible nodes to expand upon for the search.
    newNodesToAddToQueue : list[Queue.node]
        The list of nodes to add to the queue.
    problem : Graph.Graph
        The graph to search from S to G.
    search : SearchEnum.SearchEnum
        The search method to use to search the graph.
    """
    # Add new nodes to queue based on which search is being done.
    if search == SearchEnum.DEPTH_FIRST_SEARCH:
        # The solution for Dept-1st search is already provided here in the line below. This should help you realize what you need to do for other search methods. 
        queue.insertNodesAtFront(newNodesToAddToQueue)
    elif search == SearchEnum.BREADTH_FIRST_SEARCH:
        """
        Include your solution for Breadth-1st search here. Hint: 1 line of code (a call to a function provided) sufficies.
        """
    elif search == SearchEnum.DEPTH_LIMITED_SEARCH:
        lengthLimit = 3 # Depth limit + 1 for root
        # Don't add any nodes that go beyond this limit 
        """
        Include your solution for Depth-limited here. Hint: 1 line of code (a call to a function provided) sufficies, but you can have more lines if you need to.
        """
    elif search == SearchEnum.ITERATIVE_DEEPENING_SEARCH:
        # If starting the iterative deepening search, then start the loop. Otherwise, expand queue until the filter results in an empty queue.
        if(iterativeLimit == 0): 
            return iterativeDeepening(problem) # Need to return the node here because of the nested General_Search calls in the iterativeDeepening function.
        else: 
            """
            Include your solution for Depth-limited here. Hint: 1 line of code (a call to a function provided) sufficies, but you can have more lines if you need to.
            """
    elif search == SearchEnum.UNIFORM_COST_SEARCH:
        # The solution for Uniform-Cost search is already provided here in the 3 lines below. This should help you realize what you need to do for other search methods. 
        queue.insertNodesAtEnd(newNodesToAddToQueue)
        queue.sortByCost()
        queue.removeRedundantNodes()
    elif search == SearchEnum.GREEDY_SEARCH:
        """
        Include your solution for Greedy search here. Hint: 3 lines of code suffice, but you can have more or less lines of code if you need to.
        You only need to call functions already provided in the code files.
        """
    elif search == SearchEnum.A_STAR:
        """
        Include your solution for A* search here. Hint: 3 lines of code suffice, but you can have more or less lines of code if you need to.
        You only need to call functions already provided in the code files.
        """
    elif search == SearchEnum.HILL_CLIMBING:
        """
        Include your solution for Hill Crimbing (without backtracking) search here. Hint: 3 lines of code suffice, but you can have more or less lines of code if you need to.
        You only need to call functions already provided in the code files.
        """
    elif search == SearchEnum.BEAM_SEARCH:
        """
        Include your solution for Beam search here. Hint: 3-4 lines of code suffice, but you can have more or less lines of code if you need to.
        You only need to call functions already provided in the code files.
        Hint: Note that you'll know that all nodes in a level have been explored when the queue contains only nodes (i.e., paths) of the same length.
        """
    return False
def main(filename):
    """
    Entry point for this program. Parses the input and then runs each search on the parsed graph.

    Parameters
    ----------
    filename : str
        The name of the file with graph input to search
    """ 

    graph = readInput(filename)

    for search in SearchEnum:
        print(search.value)
        result = General_Search(graph, search)
        if (not result):
            print("failure to find path between S and G")
        else:
            print("\tgoal reached!")
            print("\n\tsolution found: " + result.stateString())
        print()
def readInput(filename):
    """
    Build the graph from the given input file.

    Parameters
    ----------
    filename : str
        The name of the file with input to parse into a graph.
    """

    parsedGraph = Graph.Graph()
    isHeuristicSection = False # True if processing the heuristic values for the graph. False otherwise.
    sectionDivider = "#####"
    minCharsInLine = 3 # Each line with data must have at least 3 characters
    with open(filename, 'r') as input:
        for line in input.readlines():
            if (len(line) > minCharsInLine):
                line = line.strip()
                if(sectionDivider in line):
                    isHeuristicSection = True
                elif(isHeuristicSection):
                    state, heurStr = line.split(' ')
                    heuristic = float(heurStr)
                    parsedGraph.setHeuristic(state, heuristic)
                else:
                    state1, state2, costStr = line.split(' ')
                    cost = float(costStr)
                    parsedGraph.addStatesAndEdge(state1,state2, cost)
    for state_key in parsedGraph.states:
        state = parsedGraph.states[state_key]
        state.edges = OrderedDict(sorted(state.edges.items()))
    return parsedGraph   
if __name__ == "__main__": 
    if len(sys.argv) == 2:
        main(sys.argv[1])
    else:
        print("Must input the filename with the graph input to search.")

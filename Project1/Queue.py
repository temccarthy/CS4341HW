import Graph
class Queue:
    """
    A class used to represent the list of nodes that are options for further expansion in the search.

    ...
    
    Attributes
    ----------
    nodes : list[Queue.node]
        the list of nodes that are options for expansion.
    isCostUsed : bool
        True if cost is used to order the nodes. False otherwise.

    Methods
    -------
    Remove_Front()
        Remove and return the front of the queue.
    insertNodesAtEnd(nodes)
        Insert the given nodes at the end of the queue in the given order.
    insertNodesAtFront(nodes)
        Insert the given nodes at the front of the queue in the given order.
    sortByCost()
        Sort the nodes by their cost attributes. Tiebreakers in order are: alphabetical ending node name, node length, lexicographic node names
    keepBestNodes(numnodesToKeep)
        Remove all but numnodesToKeep least cost nodes from this queue, keeping the nodes in order prior to function call.
    areNodePathLengthsEqual()
        Returns true if the length of all the node paths in the queue are the same.
    removeRedundantNodes()
        Remove nodes from the queue that have a greater or equal cost than a node to the same state already in this queue.
    """

    nodes : list
    isCostUsed : bool 
   # costFunc : function # Function that takes in a list of nodes and produces a cost
    def __init__(self, initialNode):
        """
        Parameters
        ----------
        initialState : Graph.State
            The starting node for the search.
        initialCost : float
            The cost of this initial queue.
        """

        self.nodes = []
        self.isCostUsed = initialNode.cost >= 0
        self.nodes = [initialNode]
    def Remove_Front(self):
        """
        Remove and return the front of this queue.
        """

        front = self.nodes[0]
        self.nodes = self.nodes[1:]
        return front
    def insertNodesAtEnd(self, nodes):
        """
        Insert the given nodes in their given order at the end of the queue.

        Parameters
        ----------
        nodes : list[Queue.node]
            The nodes to add to the queue.
        """

        self.nodes.extend(nodes)
    def insertNodesAtFront(self, nodes):
        """
        Insert the given nodes in their given order at the front of the queue.

        Parameters
        ----------
        nodes : list[Queue.node]
            The nodes to add to the queue.
        """

        nodes.extend(self.nodes)
        self.nodes = nodes
    def sortByCost(self):
        """
        Sort the nodes in the queue by their cost attributes. 
        
        First sorts by the cost of each node. Then if cost is equal, the tiebreakers in order are: 
        alphabetical ending node name, node length, lexicographic node names
        """

        self.nodes = sorted(self.nodes, key=lambda node: (node.cost, node.path[0].name, len(node.path), (list(map(lambda state: state.name, node.path)))))
    def __str__(self) -> str:
        strToReturn = ""
        for node in self.nodes:
            strToReturn += str(node.cost) if self.isCostUsed else ""
            strToReturn += str(node)
        strToReturn = strToReturn.replace(" ", "").replace('[', '<').replace(']', '> ').replace("'","")
        strToReturn = "[" + strToReturn + "]"
        return strToReturn[:-2] + strToReturn[-1]
    def keepBestNodes(self, numNodesToKeep):
        """
        Remove nodes from the queue until only numnodesToKeep number of nodes are left in the same order as they were initially.

        Parameters
        ----------
        numNodesToKeep : int
            The number of nodes to keep in the queue.
        """
        keptNodes = []
        for i in range(numNodesToKeep):
            if(len(self.nodes) > 0):
                costsEnumerated = list(enumerate(map(lambda node : node.cost, self.nodes),0))
                minIndex = min(costsEnumerated, key=lambda cost : cost[1])[0]
                keptNodes.append((minIndex, self.nodes[minIndex]))
                del self.nodes[minIndex]
        self.nodes = list(map(lambda node : node[1], sorted(keptNodes,key=lambda node : node[0])))
    def areNodePathLengthsEqual(self):
        """
        Returns true if the length of all the nodes in the queue are the same.
        """
        numNodes = len(self.nodes)
        if(numNodes == 0):
            return True
        firstNodePathLength = len(self.nodes[0].path)
        return len(list(filter(lambda node: len(node.path) == firstNodePathLength, self.nodes))) == numNodes
    def removeRedundantNodes(self):
        """
        Remove nodes that end at the same state as a node already in the queue for a higher or equal cost. 
        """
        bestSeen = {}
        indicesToRemove = []
        for index in range(len(self.nodes)):
            nodeName = self.nodes[index].Terminal_State()
            if nodeName in bestSeen and self.nodes[index] != bestSeen[nodeName] and self.nodes[index].cost >= bestSeen[nodeName][0].cost:
                indicesToRemove.append(index)
            else:
                if nodeName in bestSeen:
                    indicesToRemove.append(bestSeen[nodeName][1])
                bestSeen[nodeName] = ((self.nodes[index]), index)
        indicesToRemove.reverse()
        for index in indicesToRemove:
            del self.nodes[index]
class Node:
    """
    A class used to represent an ordered list of nodes as a node traversing the graph. The first node is the current state.

    ...

    Attributes
    ----------
    path : list[Graph.State]
        The ordered list of states that create the path to this node starting at the last state in the list and ending at the first state.
    cost : float
        The cost of this node in the context of the search. 
    
    Methods
    -------
    Expand()
        Return the names of the states that are adjacent to the current state and not already present in the node.
    nodeString()
        Return a string describing the nodes traversed from left-to-right.
    """

    path : list 
    cost : float 
    def __init__(self, path : list, cost : float):
        """
        Parameters
        ----------
        path : list[Graph.State]
            The list of states that make up the path to this node.
        cost : float
            The cost of this node in the context of the search it was created in.
        """

        self.path = path
        self.cost = cost    
    def Expand(self, costFunc, problem, explored, queue):
        """
        Return the new nodes created from expanding this node.

        Parameters
        ----------
        costFunc : list[Graph.Node] -> float
            The function used to calculate the cost of a list of nodes based on the search method.
        problem : Graph.Graph
            The graph to convert the child state names to states.
        """

        uniqueChildStates = []
        nodesSeen = list(map(lambda node: node.name, self.path))
        for child in self.path[0].edges:
            if child not in nodesSeen and child not in explored: # check explored and current path
                uniqueChildStates.append(problem.getState(child))
        newNodes = []
        for node in uniqueChildStates:
            oldPath = self.path.copy()
            oldPath.insert(0, node)
            newNodes.append(Node(oldPath,costFunc(oldPath)))
        return newNodes  
    def __str__(self):
        return str(list(map(lambda state : state.name, self.path)))
    def stateString(self):
        """
        Return a string describing the states traversed from left-to-right.
        """
        toReturn = ""
        for state in self.path:
            toReturn = state.name + " - " + toReturn 
        return toReturn[:-3]
    def Terminal_State(self):
        """
        Return the terminal state of the path
        """

        return self.path[0].name
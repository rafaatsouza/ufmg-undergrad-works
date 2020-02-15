import networkx as nx

class GraphLib:
	def __init__(self):
		self.graph = nx.Graph()

	def addEdge(self, fileA, fileB):
		try:
			edge = self.graph[fileA][fileB]
			newEdgeWeight = edge['weight'] + 1
			self.graph.add_edge(fileA, fileB, weight=newEdgeWeight)
		except KeyError as e:
			self.graph.add_edge(fileA, fileB, weight=1)
		
	def testFunc(self):
		self.addEdge('B', 'D')
		self.addEdge('B', 'D')
		self.addEdge('A', 'C')
		self.addEdge('C', 'D')
		self.addEdge('A', 'B')
		self.addEdge('C', 'B')
		print(self.getHeaviestEdge())
		print(self.getMostRelatedNode())

	def getHeaviestEdge(self):
		maxWeight = 0

		for edge in self.graph.edges:
			actualEdge = self.graph[edge[0]][edge[1]]
			if(actualEdge['weight'] > maxWeight):
				heaviestEdge = edge[0],edge[1]
				maxWeight = actualEdge['weight']
		return heaviestEdge, maxWeight

	def getMostRelatedNode(self):
		maxRelated = 0

		for node in self.graph.nodes:
			neighborCount = sum(1 for neighbor in nx.neighbors(self.graph, node))
			if(neighborCount > maxRelated):
				maxRelated = neighborCount
				mostRelatedNode = node
		return mostRelatedNode, maxRelated

	def GetMostImportantFile(self):
		print('Removing edges with weight 1, as they might not indicate precise connections')
		removedCount = 0
		total = 0
		removeList = []
		for edge in self.graph.edges:
			actualEdge = self.graph[edge[0]][edge[1]]
			if actualEdge['weight'] == 1:
				removeList.append((edge[0], edge[1]))
				removeList.append((edge[1], edge[0]))
				removedCount += 2
			total += 1
		print('Total number of edges: %d' % total)
		self.graph.remove_edges_from(removeList)
		print('Removed %d edges' % removedCount)
		total -= removedCount
		print('Remaining total number of edges: %d' % total)
		print('Removing edges with weight lesser than or equal to the Median')
		listSize = 0
		weightList = []
		for edge in self.graph.edges:
			actualEdge = self.graph[edge[0]][edge[1]]
			if actualEdge['weight'] in weightList:
				continue
			else:
				weightList.append(actualEdge['weight'])
				listSize += 1		
		medianIndex = int(listSize/2)
		median = weightList[medianIndex]
		print('Median value found was %d' % median)
		removedCount = 0
		removeList = []
		for edge in self.graph.edges:
			actualEdge = self.graph[edge[0]][edge[1]]
			if actualEdge['weight'] >= median:
				removeList.append((edge[0], edge[1]))
				removeList.append((edge[1], edge[0]))
				removedCount += 2
		self.graph.remove_edges_from(removeList)
		print('Removed %d edges' % removedCount)
		total -= removedCount
		print('Remaining total number of edges: %d' % total)
		print('Most important file is the resulting file with most connections')
		mostRelatedNode = self.getMostRelatedNode()
		return mostRelatedNode
		#print('Meaning that, from all meaningful connections, %s holds a ratio of %f' % (mostRelatedNode[0], mostRelatedNode[1]/total))

class Vertex:
	def __init__(self):
		self.edges = []
		self.color = -1

	def append(self, v):
		self.edges.append(v)

	def setColor(self, newColor):
		self.color = newColor
	    
	def getEdges(self):
		return self.edges
	
	def getColor(self):
	    return self.color


# algorithm for graph coloring
# Stated with code from https://www.geeksforgeeks.org/graph-coloring-set-2-greedy-algorithm/#

def addEdge(adj, v, w):
	
	adj[v].append(w)
	
	# Note: the graph is undirected
	adj[w].append(v)

# Assigns colors (starting from 0) to all
# vertices and prints the assignment of colors
def greedyColoring(g1, adj, V):

	# Assign the first color to first vertex
	adj[0].setColor(0)


	# A temporary array to store the available colors.
	# True value of available[cr] would mean that the
	# color cr is assigned to one of its adjacent vertices
	available = [False] * V

	# Assign colors to remaining V-1 vertices
	for u in range(1, V):
		
		# Process all adjacent vertices and
		# flag their colors as unavailable
		for i in adj[u].getEdges():
			if(g1[i].getColor() != -1):
				available[g1[i].getColor()] = True

		# Find the first available color
		cr = 0
		while cr < V:
			if (available[cr] == False):
				break
			
			cr += 1
			
		# Assign the found color
		adj[u].setColor(cr)

		# Reset the values back to false
		# for the next iteration
		for i in adj[u].getEdges():
			available[g1[i].getColor()] = False

def read_file(file_path):
	with open(file_path, 'r') as file:
		vCount = int(file.readline())
		newGraph = [Vertex() for i in range(vCount)]
		lines = file.readlines()
		for line in lines:
			intList = list(map(int, line.split()))
			#print(intList)
			addEdge(newGraph, intList[0], intList[1])
		
	return newGraph
        

# Driver Code
if __name__ == '__main__':

	g1 = read_file('nonOptimal_Heuristic.txt')
	
	##############################################################################################
	# Heuristic Method
    # sort the vertices based on the size of their edges list
	sorted_vertices = sorted(g1, key=lambda vertex: -len(vertex.getEdges()))
	
	#################################################################################################
	# #Brute Force Method
	# sorted_vertices = g1
	
	###################################################################################################


	# Color graph
	greedyColoring(g1, sorted_vertices, len(g1))

	
    # Print the result
	print("Coloring of graph 1 ")
	for u in range(len(g1)):
		print("Vertex", u, " ---> Color", g1[u].getColor())


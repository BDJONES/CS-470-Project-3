'''
1) Initialize the result as {}
2) Consider a set of all edges in given graph.  Let the set be E.
3) Do following while E is not empty
...a) Pick an arbitrary edge (u, v) from set E and add 'u' and 'v' to result
...b) Remove all edges from E which are either incident on u or v.
4) Return result
*/

Input: file containing rows of 3 values and 1 number for number of vertices.

'''
import sys
import ast
from collections import defaultdict
from operator import itemgetter


def generate_edges(graph):
    edges = []
    for node in graph: 
        for neighbour in graph[node]:
            if (node,neighbour) and (neighbour, node) not in edges:
                edges.append((node,neighbour))
    return edges

def count_degrees(edges, vertices):
    degrees = {}
    for v in vertices:
        degrees[v] = 0
    for edge in edges:
        degrees[edge[0]] = degrees[edge[0]] + 1
        degrees[edge[1]] = degrees[edge[1]] + 1
    return degrees

def verify_vertex_cover(cover, edges):
    for edge in edges:
        in_cover = False;
        for vertex in cover:
            if edge[0] == vertex or edge[1] == vertex: 
                    in_cover = True;
        if in_cover == False:
            return False
    return True


def vertex_cover_degrees(graph, res):
    edges = generate_edges(graph)
    degrees = count_degrees(edges, list(dict(graph).keys()))
    degrees_sorted = sorted(degrees.items(), key=itemgetter(1), reverse=True)
    cover_ = []
    for v in degrees_sorted:
        cover_.append(v[0])
        if verify_vertex_cover(cover_, edges):
            res.append(cover_)
            return
 
# Main
g = {}
result = []
with open(sys.argv[1]) as f:
    data = f.read()

g = ast.literal_eval(data)

print(g)
g_size = len(g)

vertex_cover_degrees(g, result)
print (result)


#With the big graph dataset, the program will run for a very very long time.

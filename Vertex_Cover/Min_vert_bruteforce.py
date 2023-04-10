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


def start_subsets(set_, k):
    curr_subset = []
    res = []
    generate_subsets(set_, curr_subset, res, k, 0)
    return res

def generate_subsets(set_, curr_subset, subsets_, k, next_index):
    if len(curr_subset) == int(k):
        subsets_.append(curr_subset)
        return
    if next_index + 1 <= len(set_):
        curr_subset_exclude = curr_subset.copy()
        curr_subset.append(set_[next_index])
        generate_subsets(set_, curr_subset, subsets_, k, next_index+1)
        generate_subsets(set_, curr_subset_exclude, subsets_, k, next_index+1)

def generate_edges(graph):
    edges = []
    for node in graph: 
        for neighbour in graph[node]:
            if (node,neighbour) and (neighbour, node) not in edges:
                edges.append((node,neighbour))
    return edges

def verify_vertex_cover(cover, edges):
    for edge in edges:
        in_cover = False;
        for vertex in cover:
            if edge[0] == vertex or edge[1] == vertex: 
                    in_cover = True;
        if in_cover == False:
            return False
    return True

def vertex_cover_brute(graph, res):
    vertices = list(dict(graph).keys())
    k = len(vertices)
    edges = generate_edges(graph)
    for i in range(1, k):
        subsets_ = start_subsets(vertices, i)
        for s in subsets_:
            if verify_vertex_cover(s, edges) == True:
                res.append(s)
                return
            
 
# Main
g = {}
result = []
with open(sys.argv[1]) as f:
    data = f.read()

g = ast.literal_eval(data)

print(g)

vertex_cover_brute(g, result)
print (result)

#With the big graph dataset, the program will run for a very very long time.

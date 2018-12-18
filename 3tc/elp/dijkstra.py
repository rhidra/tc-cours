#!/usr/bin/python3

from collections import defaultdict, deque


class Graph(object):
    def __init__(self):
        self.nodes = set()
        self.edges = defaultdict(list)
        self.distances = {}
    def __repr__(self):
        return "(nodes="+str(self.nodes)+";edges="+str(self.edges)+")"


    def add_node(self, value):
        self.nodes.add(value)

    def add_edge(self, from_node, to_node, distance):
        self.edges[from_node].append(to_node)
        self.edges[to_node].append(from_node)
        self.distances[(from_node, to_node)] = distance


def dijkstra(graph, initial):
    visited = {initial: 0}
    path = {}

    nodes = set(graph.nodes)

    while nodes:
        min_node = None
        for node in nodes:
            if node in visited:
                if min_node is None:
                    min_node = node
                elif visited[node] < visited[min_node]:
                    min_node = node
        if min_node is None:
            break

        nodes.remove(min_node)
        current_weight = visited[min_node]

        for edge in graph.edges[min_node]:
            try:
                weight = current_weight + graph.distances[(min_node, edge)]
            except:
                continue
            if edge not in visited or weight < visited[edge]:
                visited[edge] = weight
                path[edge] = min_node

    return visited, path


def shortest_path(graph, origin, destination):
    visited, paths = dijkstra(graph, origin)
    full_path = deque()
    print("paths=", paths)
    _destination = paths[destination]

    while _destination != origin:
        full_path.appendleft(_destination)
        _destination = paths[_destination]

    full_path.appendleft(origin)
    full_path.append(destination)

    return visited[destination], list(full_path)

# if __name__ == '__main__':
#     graph = Graph()
#
#     for node in ['A', 'B', 'C', 'D', 'E', 'F', 'G']:
#         graph.add_node(node)
#
#     graph.add_edge('A', 'B', 1)
#     graph.add_edge('A', 'C', 1)
#     graph.add_edge('B', 'D', 1)
#     graph.add_edge('C', 'D', 1)
#     graph.add_edge('B', 'E', 1)
#     graph.add_edge('D', 'E', 1)
#     graph.add_edge('E', 'F', 1)
#     graph.add_edge('F', 'G', 1)
#
# print("graph=",graph)
# cost, path = shortest_path(graph, 'A', 'D')
#
# for node in path:
#     print(node)

links = [(11, 6), (0, 9), (1, 2), (0, 1), (10, 1), (11, 5), (2, 3), (4, 5), (8, 9), (6, 7), (7, 8), (0, 6), (3, 4), (0, 2), (11, 7), (0, 8), (0, 4), (9, 10), (0, 5), (0, 7), (0, 3), (0, 10), (5, 6)]

graph = Graph()

for node in range(0, 12):
    graph.add_node(node)
for link in links:
    graph.add_edge(link[0], link[1], 1)
print("graph=",graph)
cost, path = shortest_path(graph, 0, 11)
print(cost, path)

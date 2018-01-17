#!/usr/bin/env python3
import sys
import matplotlib.pyplot as plt


class Graph:
    def __init__(self, name):
        self.name = name
        self.x_s = []
        self.memory_usages = []
        self.times_in_ms = []

    def add_values(self, x_s, mem_usg, time):
        self.x_s.append(x_s)
        self.memory_usages.append(mem_usg)
        self.times_in_ms.append(time)

    def sort(self):
        self.x_s, self.memory_usages, self.times_in_ms = zip(*sorted(
            zip(self.x_s, self.memory_usages, self.times_in_ms)))

def parse_values(results):
    agrep_graph = Graph('agrep')
    edlib_graph = Graph('edlib')
    for line in results.split('\n'):
        a_split, e_split = line.rstrip().split('|')
        for graph, data in zip([agrep_graph, edlib_graph], line.split('|')):
            values = data.rstrip().split(';')
            graph.add_values(int(values[0]), int(values[1]), int(values[2]))
    agrep_graph.sort()
    edlib_graph.sort()
    return agrep_graph, edlib_graph


def draw_graphs(graphs, x_axis):
    agrep_graph, edlib_graph = graphs
    draw_graph(agrep_graph, edlib_graph, agrep_graph.memory_usages, edlib_graph.memory_usages, x_axis,
               'Memorijsko zauzeće [kB]')
    draw_graph(agrep_graph, edlib_graph, agrep_graph.times_in_ms, edlib_graph.times_in_ms, x_axis,
               'Trajanje programa [ms]')

def draw_graph(agrep: Graph, edlib: Graph, agrep_y, edlib_y, x_axis, y_axis):
    plt.figure(dpi=200)
    plt.plot(agrep.x_s, agrep_y, c='b', label=agrep.name)
    plt.scatter(agrep.x_s, agrep_y, c='b')
    plt.plot(edlib.x_s, edlib_y, c='r', label=edlib.name)
    plt.scatter(edlib.x_s, edlib_y, c='r')
    plt.xlabel(x_axis)
    plt.ylabel(y_axis)
    plt.legend()
    plt.show()


# print(sys.argv[1])
if len(sys.argv) != 3:
    print("Expected following arguments: [results (agrep|edlib)] [x axis]!")
draw_graphs(parse_values(sys.argv[1]), sys.argv[2])

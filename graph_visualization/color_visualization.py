from datetime import datetime

import networkx
import networkx as nx
import numpy as np
import pandas as pd
from bokeh.io import show, save
from bokeh.models import (Circle, MultiLine, NodesAndLinkedEdges, Range1d)
from bokeh.palettes import Spectral4, Spectral11
from bokeh.plotting import figure
from bokeh.plotting import from_networkx


def load_data(file_name, n=10):
    edges = set()

    i = 0

    with open(file_name) as f:
        lines = f.readlines()

        for line in lines:
            words = line.split(',')
            # for every word in every line
            for word in words[2:]:
                edges.add((words[0], word))
            # if i > float('inf'):
            if i > n:
                break
            i += 1
    return edges


def generate_graph(edges):
    df = pd.DataFrame(edges, columns=['source', 'target'])
    G = nx.from_pandas_edgelist(df, 'source', 'target')
    return G


def setup_node_sizes(G, degrees, attribute_name):
    # adjust degree so that the nodes with very small degrees are still visible
    number_to_adjust_by = 5
    adjusted_node_size = dict([(node, (1 - np.exp(-(degree + 30) / 1000)) * 150) for (node, degree) in degrees.items()])
    nx.set_node_attributes(G, name=attribute_name, values=adjusted_node_size)


def setup_node_colors(G, degrees, attribute_name):
    max_color = np.max(np.fromiter(degrees.values(), dtype=int))

    n = 10

    mapping = {}

    for (key, m) in degrees.items():
        v = int(np.round(np.log(m) / np.log(max_color) * n))

        mapping[key] = Spectral11[v]

    networkx.set_node_attributes(G, mapping, attribute_name)


if __name__ == '__main__':
    print(datetime.now(), "Starting loading file")
    edges = load_data("save4.txt", n=100)
    print(datetime.now(), "Finshed loading")

    print(datetime.now(), "Generate graph")
    G = generate_graph(edges)
    print(datetime.now(), "Finished generating graph")

    degrees = dict(nx.degree(G))
    nx.set_node_attributes(G, name='LinkNum', values=degrees)

    print(datetime.now(), "Setting up node sizes")
    size_by_this_attribute = 'adjusted_node_size'
    setup_node_sizes(G, degrees, size_by_this_attribute)
    print(datetime.now(), "Finished setting up node sizes")

    print(datetime.now(), "Setting up node colors")
    color_by_this_attribute = 'modularity_color'
    setup_node_colors(G, degrees, color_by_this_attribute)
    print(datetime.now(), "Finished setting up node sizes")

    # Choose colors for node and edge highlighting
    node_highlight_color = Spectral4[2]
    edge_highlight_color = Spectral4[2]

    title = 'Wikipedia Network'

    # Categories will appear when hovering over each node
    HOVER_TOOLTIPS = [
        ("WikiEntry", "@index"),
        ("LinkNum", "@LinkNum")
    ]

    plot = figure(tooltips=HOVER_TOOLTIPS,
                  tools="pan,wheel_zoom,save,reset,tap", active_scroll='wheel_zoom',
                  x_range=Range1d(-1000.1, 1000.1), y_range=Range1d(-1000.1, 1000.1),
                  title=title,
                  plot_width=2000,
                  plot_height=2000
                  )

    print(datetime.now(), "Generating network graphics")
    n = G.number_of_nodes()
    print("Number of nodes", n)

    scale = 1000

    start = datetime.now()

    network_graph = from_networkx(G, nx.spring_layout, scale=scale, center=(0, 0))
    print(datetime.now(), "Finished Generating network graphics", datetime.now() - start)

    # for nodes
    network_graph.node_renderer.glyph = Circle(size=size_by_this_attribute, fill_color=color_by_this_attribute,
                                               fill_alpha=0.7,
                                               line_color=None)
    network_graph.node_renderer.hover_glyph = Circle(size=size_by_this_attribute, fill_color=node_highlight_color,
                                                     line_width=2)
    network_graph.node_renderer.selection_glyph = Circle(size=size_by_this_attribute, fill_color=node_highlight_color,
                                                         line_width=2)

    # for edges
    # Set edge opacity and width
    network_graph.edge_renderer.glyph = MultiLine(line_alpha=0.5, line_width=0.3)
    # Set edge highlight colors
    network_graph.edge_renderer.selection_glyph = MultiLine(line_color=edge_highlight_color, line_width=0.5)
    network_graph.edge_renderer.hover_glyph = MultiLine(line_color=edge_highlight_color, line_width=0.5)

    # INTERACTIVE
    network_graph.selection_policy = NodesAndLinkedEdges()
    network_graph.inspection_policy = NodesAndLinkedEdges()

    plot.renderers.append(network_graph)
    print(datetime.now(), "Saving plot")
    save(plot, filename=f"{title}.html")
    print(datetime.now(), "Finished saving plot")

    print(datetime.now(), "Showing plot")
    show(plot)
    print(datetime.now(), "Finished showing plot")

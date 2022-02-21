# Final Project Proposal
## Team Contract (mjuston2-linj2-bingyan2-austinl8)
### Leading Question:
We are going to build a Wikipedia search engine. It is a searching tool for a selected collection of Wikipedia articles. The goal of the graph is to help figure out the correlation between articles. As input, we will pass in a starting article and the end article desired and then our program will be able to return the shortest path between the article and print that chain. This would help people to understand how topics are correlated to each other. This graph could be helpful for research applications where finding topic ideas or connections are necessary. 

### Dataset Acquisition and Processing
The dataset we will be using is the English Wikipedia. We will be using Python to web scrape Wikipedia to create our own local database which is more lightweight than the Wikipedia Dumps, which we would have preferred to use; however, the database files are too large and are formatted in XML which makes it much harder to read in C++ without a library. 

The [Python Web scraper](https://github-dev.cs.illinois.edu/cs225-sp21/mjuston2-linj2-bingyan2-austinl8/blob/master/wikipedia_scrapper.py) will be using a BFS to collect the titles of the articles as well as the links in the body of the article. The Python web scraper will be using BeautifulSoup to extract the HTML contents of the pages. The number of links will be defined as the weight of the node and the links to other articles will be the edges/children of that node. The local database will be stored as a txt file in the format: “Article name”, Number of links, links ….

![](./images/database.png)

### Graph Algorithms
For our graph traversal, we propose implementing a basic BFS using an iterator. We expect our iterator constructor input to be a starting wiki entry node. We expect that incrementing our iterator will update its internal position to a new wiki entry node until there are no nodes left to traverse.

For our first algorithm, we propose implementing the PageRank algorithm, based on the relationship between wiki entries. We expect the input to PageRank to be our graph of connected wiki entries. We expect the output to be the Markov chain of our graph after reaching convergence, calculated using power iteration, this will provide us with a more concrete weight for our nodes instead of just using the number of links in the Wiki article as the weights.

For our second algorithm, we propose implementing Dijkstra’s Algorithm. We expect the input to be a starting and ending Wiki entry. We expect the output to be the least-weighted path between these two inputs, with edge weights being determined by the number of links pointing from one wiki entry node to the other or by the PageRank weights. Our target runtime complexity is O(V + E log(V)), where V is the number of nodes and E is the number of edges. This will be achieved using a min-priority queue.

As an extra algorithm we decided to implement the Stronly Connected Algorithm based by Kosaraju's algorithm. This algorithm, in directed graphs, allows us to find the connected nodes where there is a path between all pairs of vertices. The full graph is placed as an input of the algorithm and as an output a list of vectors (sorted in descending order of number of vertices in component) is outputed.

For our final extra algorithm, we propose generating a 2D graph visualization (implemeted in Python) with nodes representing Wiki entries and edges weighted with the number of links leading from one to the next. We expect the input to be the full graph dataset and the ouput to be an HTML representation of the graph, where the larger nodes represent the nodes with the largest amount of connecting links and the smallest are the leafs.

### Timeline
Our team has a weekly meeting on Friday night, and the meeting will also be a check-in point within our group.

- WEEK 1 April 9 - April 16 : 
    - Data acquisition and processing, graph building
    - Write class documentation
- WEEK 2 April 16 - April 23 : 
    - Implement Breadth-First Search for traversals
    - Implement PageRank Algorithm
    - Mid-project check in with project mentor
- WEEK 3 April 23 - April 30 : 
    - Implement Dijkstra’s Algorithm that finds the connecting path between articles
- WEEK 4 April 30 - May 7 : 
    - Visualize search result
    - Possibly implement Betweenness Centrality Algorithm
    - Report writing
- WEEK 5 May 7 - May 12 :
    - Workday
    - May 10 Record presentation video 
    - May 11 ALL the final project deliverables are up to GitHub

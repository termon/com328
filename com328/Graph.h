/**********************************************************************
 * Name        : Graph.h
 * Author      : a.mccaughey@ulster.ac.uk
 * Version     : 1.1
 * Description : Provides a Graph ADT based on an adjacency matrix
 *
 *********************************************************************/

#ifndef GRAPH_H
#define GRAPH_H

#include <cctype>
#include <set>
#include <iomanip>

#include "Array.h"
#include "ArrayList.h"
#include "ArrayStack.h"
#include "ArrayQueue.h"


class Graph {
public:
	Graph(int size = 10, bool dir = false);

	bool addVertex(std::string label);
	bool addEdge(std::string slabel, std::string elabel, int weight);
	bool removeEdge(std::string slabel, std::string elabel);
	void transClose(int weight);
	void spanningTree(std::string label);
	bool stepsTo(std::string src, std::string dst, int steps) const;

	ArrayList<std::string> dfs(std::string start);
	ArrayList<std::string> bfs(std::string start);

	void print(std::ostream & out) const;
	bool isDirected() const;
	bool vertexExists(std::string l) const;

private:
	struct Vertex {
		std::string label;
		bool visited;

		Vertex(std::string l = "") : label(l), visited{ false } {}
	};

	Array< Vertex >		 vertices;
	Array< Array<int> >  matrix;
	int count;
	bool directed;

	// private member functions
	int findVertex(std::string label) const;
	void resetVisitedVertices();
	int adjacentUnvisitedVertex(int v);
	bool stepsTo(int src, int dst, int steps) const;
};

// -------------------------------------- Graph.cpp ---------------------------------------

// PreCondition: size > 0
// PostCondition: a new graph of specified size is created
Graph::Graph(int size, bool dir) : vertices(size), matrix(size), count{ 0 }, directed{ dir } {
	for (int i = 0; i < matrix.length(); i++) {
		matrix[i] = Array<int>(size);
		for (int y = 0; y < matrix[i].length(); y++) {
			matrix[i][y] = 0;
		}
	}
}

// PreCondition: count < vertices.length()
// PostCondition: a new vertex is added to Graph vertex 
bool Graph::addVertex(std::string label) {
	if (count < vertices.length()) {
		vertices[count++] = Vertex(label);
		return true;
	}
	return false;
}

// PreCondition:  vertices are valid
// PostCondition: edge is added to graph and returns true if vertices are valid
//                otherwise graph is not modified and returns false
bool Graph::addEdge(std::string slabel, std::string elabel, int weight = 1) {
	int s = findVertex(slabel);
	int e = findVertex(elabel);
	if (s != -1 && e != -1) {
		matrix[s][e] = weight;
		// if not a directed graph edge is two way
		if (!isDirected()) {
			matrix[e][s] = weight;
		}
		return true;
	}
	return false;
}

// PreCondition:  vertices are valid
// PostCondition: edge is removed from graph and returns true if vertices are valid
//                otherwise graph is not modified and returns false
bool Graph::removeEdge(std::string slabel, std::string elabel) {
	int s = findVertex(slabel);
	int e = findVertex(elabel);
	if (s != -1 && e != -1) {
		matrix[s][e] = 0;
		// if not a directed graph edge is two way
		if (!isDirected()) {
			matrix[e][s] = 0;
		}
		return true;
	}
	return false;
}

// PostCondtion: return true if graph is directed and false otherwise
bool Graph::isDirected() const {
	return directed;
}

// PreCondition: start is a valid vertex
// PostCondition: print vertices visited using breadth first search
ArrayList<std::string>  Graph::bfs(std::string start) {
	resetVisitedVertices();

	ArrayList<std::string> path(vertices.length());

	Queue<int> que;
	int v = findVertex(start); // locate starting vertex

	// if start vertex doesnt exist then exit
	if (v == -1) {
		return path;
	}
	// mark vertex as visited and add to queue	
	vertices[v].visited = true;
	que.enqueue(v);

	// add vertex label to result path
	path.add(vertices[v].label);

	// while there are vertices to search
	while (!que.isEmpty()) {
		// search adjacent vertices
		while ((v = adjacentUnvisitedVertex(que.peek())) != -1) {
			// mark vertex as visited and add to queue
			vertices[v].visited = true;
			que.enqueue(v);
			// add vertex label to result list
			path.add(vertices[v].label);
		}
		que.dequeue();		// finished with this vertex
	}
	resetVisitedVertices();	// reset visited vertices
	return path; // return path result list
}


// PreCondition: start is a valid vertex
// PostCondition: print vertices visited in depth first search
ArrayList<std::string> Graph::dfs(std::string start) {
	resetVisitedVertices();

	ArrayList<std::string> path;
	Stack<int> stk;
	int v = findVertex(start); // locate starting vertex

	// if start vertex doesnt exist then exit
	if (v == -1) {
		return path;
	}

	// mark vertex as visited and add to stack
	vertices[v].visited = true;
	stk.push(v);

	// add vertex label to result list
	path.add(vertices[v].label);

	// while there are vertices to search
	while (!stk.isEmpty()) {
		// search all adjacent vertices
		while ((v = adjacentUnvisitedVertex(stk.top())) != -1) {
			// mark adjacent vertex as visited and add to stack
			vertices[v].visited = true;
			stk.push(v);
			// add vertex label to result list
			path.add(vertices[v].label);
		}
		stk.pop();			// finished with this vertex
	}

	resetVisitedVertices();	// reset visited vertices
	return path; // return path result list
}

// PostCondition: return true if vertex with specified label exists, otherwise false
bool Graph::vertexExists(std::string l) const {
	return (findVertex(l) != -1);
}

// PostCondition: print Graph matrix to specified output stream
void Graph::print(std::ostream & out) const {
	// print top label row
	if (isDirected()){ 
		std::cout << "Directed Graph\n";
	} else { 
		std::cout << "Undirected Graph\n";
	}
	std::cout << std::setw(4) << " ";

	for (int i = 0; i < count; i++) {
		std::cout << std::setw(4) << vertices[i].label.substr(0, 3);
	}
	std::cout << std::endl;

	for (int i = 0; i < count; i++) {
		std::cout << std::setw(4) << vertices[i].label.substr(0, 3);
		for (int y = 0; y < count; y++) {
			if (matrix[i][y] == 0) {
				std::cout << std::setw(4) << " ";
			} else {
				std::cout << std::setw(4) << matrix[i][y];
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}


// PostCondition: compute transitive closure of Graph
void Graph::transClose(int weight = 2) {
	int i, j, k;

	for (i = 0; i < count; i++) {
		for (j = 0; j < count; j++) {
			if (matrix[j][i] > 0) {
				for (k = 0; k < count; k++) {
					if (matrix[i][k] > 0) {
						matrix[j][k] = weight;
					}
				} // for
			} // if
		} // for
	} // for
} //

// PostCondition:: determine if there is a path between src and dst in
//                 specified number of steps
bool Graph::stepsTo(std::string src, std::string dst, int steps) const {
	int s = findVertex(src);
	int d = findVertex(dst);
	return (s != -1 && d != -1) ? stepsTo(s, d, steps) : false;
}

// PostCondition: Calculate a Spanning Tree of the graph 
//                and print out the Vertices and the arcs required
void Graph::spanningTree(std::string label) {
	Stack<int> stk;
	int v = findVertex(label);

	vertices[v].visited = true;
	std::cout << "mst: ";
	stk.push(v);

	while (!stk.isEmpty()) {
		int cv = stk.top();
		v = adjacentUnvisitedVertex(cv);
		if (v == -1) {
			stk.pop();
		} else {
			vertices[v].visited = true;
			stk.push(v);
			std::cout << vertices[cv].label << vertices[v].label << " ";
		}
	}
	std::cout << std::endl;
	resetVisitedVertices();
}



// ------------------ Private member functions -------------------------

// PostCondition: visited flag for each Vertex is reset
void Graph::resetVisitedVertices() {
	for (int i = 0; i < count; i++) {
		vertices[i].visited = false;
	}
}

// PreCondition: v >= 0 && v < count
// PostCondtion: return the index of an unvisited vertex adjacent to v
//               or -1 if no unvisited vertex available
int Graph::adjacentUnvisitedVertex(int v) {
	for (int i = 0; i < count; i++) {
		if (matrix[v][i] > 0 && (!vertices[i].visited)) {
			return i;
		}
	}
	return -1;
}


// PreCondition: v is contained in vertices
// PostConditon: index of vertex with specified label is returned
int Graph::findVertex(std::string label) const {
	for (int i = 0; i < vertices.length(); i++) {
		if (vertices[i].label == label) {
			return i;
		}
	}
	return -1;
}

// PostCondition: determine if there is a path between src and dst in specified steps
bool Graph::stepsTo(int src, int dst, int steps) const {
	bool result = false;
	if (steps == 1) {
		result = matrix[src][dst] > 0;
	}
	else if (matrix[src][dst] > 0) {
		result = true;
	}
	else {
		for (int i = 0; i < count - 1; i++) {
			if ((matrix[src][i] > 0) && stepsTo(i, dst, steps - 1)) {
				result = true;
			}
		}
	}
	return result;
}

// PreCondition: None
// PostCondition: overload << operator to output Graph on ostream
template <class T>
std::ostream& operator <<(std::ostream& output, const Graph & g) {
    g.print(output);
    return output;  // for multiple << operators.
}

#endif

/*
* Library Test Cases Using the Catch 2 Test Library
* https://github.com/catchorg/Catch2/
*
* LibraryTestCases.cpp
*
* Updated on: 30 January 2018
* Author: aiden
*/

// important to add this definition and then include the library
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

// Library Header files 
#include "Cell.h"
#include "Set.h"
#include "FluentSet.h"

#include "Array.h"

#include "ArrayCollection.h"
#include "FluentCollection.h"

#include "ArrayStack.h"
#include "FluentStack.h"

#include "ArrayQueue.h"
#include "FluentQueue.h"

#include "DoubleLinkedList.h"
#include "LinkedList.h"
#include "ArrayList.h"
#include "FluentList.h"
#include "OrderedList.h"

#include "Database.h"
#include "FluentDatabase.h"

#include "BinaryTree.h"
#include "FluentTree.h"

#include "BinaryHeap.h"
//#include "BinaryHeap2.h"
#include "FluentBinaryHeap.h"

#include "HashTableOpen.h"
#include "HashTableChaining.h"

#include "Graph.h"
#include "Search.h"
#include "Sort.h"

#include <iostream>
#include <string>

//#include <algorithm>
//#include <functional>
//#include <array>
//#include <iterator>
//#include <set> 

/**
 *  Cell Test Axioms
 */
TEST_CASE("Cell Axioms", "[Cell]")
{
	SECTION("Test Length")
	{
		auto orig = 5;
		auto upat = 10;

		Cell<int>  c{ orig };
		Cell<int>  c1 = c;

		REQUIRE(c.read() == orig);
		c.write(upat);
		REQUIRE(c.read() == upat);

	}
}

/**
 *  Array Test Axioms
 */
TEST_CASE("Array Axioms", "[Array]")
{
	SECTION("Test Length")
	{
		auto length = 5;
		Array<int> a(length);

		REQUIRE(a.length() == length);
	}

	SECTION("Test [] access")
	{
		Array<int> a(5);
		a[0] = 1;
		a[a.length() - 1] = 5;
		
		REQUIRE(a[0] == 1);
		REQUIRE(a[a.length() - 1] == 5);
	}

	SECTION("Test Resize")
	{
		Array<int> a(3);	
		a.resize(5);

		REQUIRE(a.length() == 5);
	}

	SECTION("Test Resize Doesn't Destroy Contents")
	{
		Array<int> a(3); a[0] = 1; a[1] = 2; a[2] = 3;
		a.resize(5);
	
		REQUIRE(a.length() == 5);
		REQUIRE(a[0] == 1);
		REQUIRE(a[1] == 2);
		REQUIRE(a[2] == 3);
	}

	SECTION("Test Contruct from c array")
	{
		int ca[5]; ca[0] = 1; ca[4] = 5;

		Array<int> a(5, ca);
		REQUIRE(a.length() == 5);
		REQUIRE(a[0] == ca[0]);
		REQUIRE(a[4] == ca[4]);
	}

	SECTION("Test Contruct from Array")
	{
		Array<int> a(3);
		a[0] = 1; a[1] = 2; a[2] = 3;

		Array<int> ca(a);
		REQUIRE(a.length() == ca.length());
		REQUIRE(a[0] == ca[0]);
		REQUIRE(a[1] == ca[1]);
		REQUIRE(a[2] == ca[2]);
	}


	SECTION("Test out of bounds exception")
	{
		Array<int> a(1);
		a[0] = 0;

		REQUIRE_THROWS(a[1] = 1);
	}

}

/**
 *  Stack Test Axioms
 */
TEST_CASE("Stack Axioms", "[Stack]")
{
	// setup test
	Stack<std::string> s;
	s.push("apple"); s.push("orange"); s.push("pear");

	SECTION("test size")
	{	
		REQUIRE(s.size() == 3);
	}

	SECTION("clear stack")
	{
		s.clear();
		REQUIRE(s.isEmpty() == true);
	}

	SECTION("top stack")
	{
		REQUIRE(s.top() == std::string("pear"));
	}

	SECTION("pop stack then size")
	{
		s.pop();
		REQUIRE(s.size() == 2);
	}
	
	SECTION("pop then top")
	{
		s.pop();
		REQUIRE(s.top() == std::string("orange"));
	}
}

/**
 *  Queue Test Axioms
 */
TEST_CASE("Queue Axioms", "[Queue]")
{
	FluentQueue<std::string> q;

	SECTION("Test Create and Size is 0")
	{
		REQUIRE(q.size() == 0);
	}

	SECTION("Test Enqueue")
	{
		REQUIRE(q.enqueue("apple").enqueue("orange").enqueue("pear").size() == 3);
	}

	SECTION("Test Enqueue Then Clear")
	{
		REQUIRE(q.enqueue("apple").enqueue("orange").enqueue("pear").clear().size() == 0);
	}

	SECTION("Test Enqueue Then Peek")
	{
		REQUIRE(q.enqueue("apple").enqueue("orange").enqueue("pear").peek() == std::string("apple"));
	}

	SECTION("Test Enqueue Deqeue Then Peek")
	{
		REQUIRE(q.enqueue("apple").enqueue("orange").enqueue("pear").dequeue().peek() == std::string("orange"));
	}
}

/**
 *  Set Test Axioms
 */
TEST_CASE("Set Axioms", "[Set]")
{
	FluentSet<std::string> s;

	SECTION("TestSetAddSize")
	{
		REQUIRE(s.add("apple").add("orange").add("pear").add("apple").size() == 3);
	}

	SECTION("TestSetCount")
	{
		REQUIRE(s.add("orange").add("pear").add("apple").count("apple") == 1);
	}

	SECTION("TestSetRemove")
	{
		REQUIRE(s.add("orange").add("pear").add("apple").remove("apple").size() == 2);
	}

	SECTION("TestSetClear")
	{
		REQUIRE(s.add("orange").add("pear").add("apple").clear().size() == 0);
	}

	SECTION("TestSetEquality")
	{
		FluentSet<std::string> r;
		REQUIRE(s.add("orange").add("pear").add("apple") == r.add("apple").add("pear").add("orange"));
	}
}

/**
 *  Database Test Axioms
 */
TEST_CASE("Database Axioms", "[Database]")
{
	Database<std::string> d;

	SECTION("TestAddRemoveThenGet")
	{
		d.add("apple");
		d.add("orange");
		d.prev();
		REQUIRE(d.get() == std::string{"apple"});
		d.remove();
		REQUIRE(d.get() == std::string{ "orange" });
	}

	SECTION("TestAddThenSize")
	{
		d.add("apple");
		d.add("orange");
		d.add("pear");		
		REQUIRE(d.size() == 3);
	}

	SECTION("TestAddRemoveThenSize")
	{
		d.add("apple");
		d.add("orange"); 
		d.add("pear"); 
		d.remove();
		d.remove();
		d.remove();
		REQUIRE(d.size() == 0);
	}

	SECTION("TestAddThenSet")
	{
		d.add("apple");
		d.set("APPLE");
		REQUIRE(d.get() == std::string("APPLE"));
	}

	SECTION("TestAddThenGet")
	{
		d.add("apple");
		d.add("orange");
		d.add("pear");
		REQUIRE(d.get() == std::string("pear"));
	}


	SECTION("TestAddClearThenSize")
	{
		d.add("apple");
		d.add("orange");
		d.add("pear");
		d.clear();

		REQUIRE(d.size() == 0);
	}

	SECTION("TestAddClearThenNextFails")
	{
		d.add("apple");
		d.add("orange");
		d.add("pear");
		d.clear();

		REQUIRE(d.next() == false);
	}

	SECTION("TestAddClearThenPrevFails")
	{
		d.add("apple");
		d.add("orange");
		d.add("pear");
		d.clear();

		REQUIRE(d.prev() == false);
	}

	SECTION("TestRemoveFailsOnEmptyRemove")
	{
		try {
			// this operation should fail as there is nothing to remove
			FluentDatabase<std::string>().remove();
		}
		catch (std::out_of_range e) {
			REQUIRE(true == true);
		}
	}

	SECTION("TestRemoveFailsOnEmptyRetrieve")
	{
		try {
			// this operation should fail as there is nothing to retrieve
			FluentDatabase<std::string>().get();
		}
		catch (std::out_of_range e) {
			REQUIRE(true == true);
		}
	}

	SECTION("TestDatabaseCopyConstructor")
	{
		// test database copy constructor
		Database<std::string> d;
		d.add("apple");

		REQUIRE(FluentDatabase<std::string>(d).get() == std::string("apple"));
	}

	SECTION("Test File Serialize and Deserialize")
	{
		Database<std::string> d;
		d.add("10"); d.add("20"); d.first(); d.add("5");
		d.save(std::string{ "test.txt" });
		d.first();

		Database<std::string> r;
		r.load(std::string{ "test.txt" });
		r.first();

		REQUIRE(d.size() == r.size());
		REQUIRE(d.get() == r.get());
	}
}

/**
 *  Collection Test Axioms
 */
TEST_CASE("Collection Axioms", "[Collection]")
{
	FluentCollection<std::string> c;
	c.add("apple").add("orange").add("pear");

	SECTION("TestCollectionAddSize")
	{
		REQUIRE(c.size() == 3);
	}

	SECTION("TestCollectionCount")
	{
		REQUIRE(c.add("apple").count("apple") == 2);
		REQUIRE(c.add("grape").count("grape") == 1);
		REQUIRE(c.count("na") == 0);
	}

	SECTION("TestCollectionRemove")
	{
		REQUIRE(c.remove("apple").size() == 2);
	}

	SECTION("TestCollectionClear")
	{
		REQUIRE(c.clear().size() == 0);
	}

	SECTION("TestCollectionEquality")
	{
		FluentCollection<std::string> o;
		o.add("apple").add("orange").add("pear");

		REQUIRE(c == o);
	}
}

/**
 *  FluentList Test Axioms
 */
TEST_CASE("FluentList Axioms", "[FluentList]")
{
	FluentList<int> l;

	SECTION("SizeTest")
	{
		REQUIRE(l.size() == 0);
	}

	SECTION("Empty Test")
	{
		REQUIRE(l.isEmpty() == true);
	}

	SECTION("Empty Test")
	{
		REQUIRE(l.add(0, 1).size() == 1);
	}

	SECTION("AddThenNotEmpty")
	{
		REQUIRE(l.add(0, 1).isEmpty() == false);
	}

	SECTION("Add Then Get")
	{
		REQUIRE(l.add(1).add(2).get(1) == 2);
	}

	SECTION("Add Remove Then Size")
	{
		REQUIRE(l.add(0, 1).remove(0).size() == 0);
	}

	SECTION("Test Equal")
	{
		FluentList<int> r;
		r.add(0, 1);

		REQUIRE(l.add(0,1) == r);
	}

	SECTION("Test Clear then equal")
	{
		REQUIRE(l.add(1).clear() == FluentList<int>());
	}

	SECTION("Test Invalid Remove")
	{
		try {
			FluentList<int>().remove(0);
		}
		catch (std::out_of_range e) {
			REQUIRE(true == true);
		}
	}

	SECTION("Test Set Out of Range")
	{
		try {
			FluentList<int>().set(0, 1);
		}
		catch (std::out_of_range e) {
			REQUIRE(true == true);
		}
	}
}

/**
 *  LinkedList Test Axioms
 */
TEST_CASE("LinkedList Axioms", "[LinkedList]")
{
	LinkedList<int> l;
	l.add(0,1);
	l.add(1,2);
	
	SECTION("SizeTest")
	{
		REQUIRE(l.size() == 2);
	}

	SECTION("Clear Test")
	{
		l.clear();
		REQUIRE(l.isEmpty() == true);
	}

	SECTION("NotEmpty")
	{
		REQUIRE(l.isEmpty() == false);
	}

	SECTION("Add Then Get")
	{
		l.add(3);
		REQUIRE(l.get(2) == 3);
	}

	SECTION("Remove Then Size")
	{
		l.remove(0);
		REQUIRE(l.size() == 1);
	}

	SECTION("Test Equal")
	{
		LinkedList<int> r;
		r.add(0, 1);
		r.add(1, 2);

		REQUIRE(l == r);
	}

	SECTION("Test Clear then equal")
	{
		l.clear();

		REQUIRE(l == LinkedList<int>());
	}

	SECTION("Test Invalid Remove")
	{
		try {
			l.remove(2);
		}
		catch (std::out_of_range e) {
			REQUIRE(true == true);
		}
	}

	SECTION("Test Set Out of Range")
	{
		try {
			l.set(2, 1);
		}
		catch (std::out_of_range e) {
			REQUIRE(true == true);
		}
	}
}

/**
 *  DoubleLinkedList Test Axioms
 */
TEST_CASE("DoubleLinkedList Axioms", "[DoubleLinkedList]")
{
	DLinkedList<int> l;
	l.add(0,1);
	l.add(1,2);

	SECTION("SizeTest")
	{
		REQUIRE(l.size() == 2);
	}

	SECTION("Clear Test")
	{
		l.clear();
		REQUIRE(l.isEmpty() == true);
	}

	SECTION("NotEmpty")
	{
		REQUIRE(l.isEmpty() == false);
	}

	SECTION("Add Then Get")
	{
		l.add(3);
		REQUIRE(l.get(2) == 3);
	}

	SECTION("Remove Then Size")
	{
		l.remove(0);
		REQUIRE(l.size() == 1);
	}

	SECTION("Test Equal")
	{
		DLinkedList<int> r;
		r.add(0, 1);
		r.add(1, 2);

		REQUIRE(l == r);
	}

	SECTION("Test Invalid Remove")
	{
		try {
			l.remove(2);
		}
		catch (std::out_of_range e) {
			REQUIRE(true == true);
		}
	}

	SECTION("Test Set Out of Range")
	{
		try {
			l.set(2, 1);
		}
		catch (std::out_of_range e) {
			REQUIRE(true == true);
		}
	}
}

/**
 *  ArrayList Test Axioms
 */
TEST_CASE("ArrayList Axioms", "[ArrayList]")
{
	ArrayList<int> l;

	SECTION("SizeTest")
	{
		REQUIRE(l.size() == 0);
	}

	SECTION("Test Copy Constructor")
	{
		ArrayList<int> a;
		a.add(1);
		a.add(3);
		a.add(2);

		ArrayList<int> c(a);

		REQUIRE(a == c);
	}


	SECTION("Test Assignment Operator")
	{
		ArrayList<int> a;
		a.add(1);
		a.add(3);
		a.add(2);

		ArrayList<int> c;
		c = a;

		REQUIRE(a == c);
	}

	SECTION("Empty Test")
	{
		REQUIRE(l.isEmpty() == true);
	}

	SECTION("AddThenSizeIsOne")
	{
		l.add(0, 1);
		REQUIRE(l.size() == 1);
	}

	SECTION("AddThenNotEmpty")
	{
		l.add(0, 1);
		REQUIRE(l.isEmpty() == false);
	}

	SECTION("Add Then Get")
	{
		l.add(1);
		l.add(2);
		REQUIRE(l.get(1) == 2);
	}

	SECTION("Add Remove Then Size")
	{
		l.add(0, 1);
		l.remove(0);

		REQUIRE(l.size() == 0);
	}

	SECTION("Test Equal")
	{
		ArrayList<int> r;
		r.add(0, 1);
		l.add(0, 1);
		
		REQUIRE(l == r);
	}

	SECTION("Test Not Equal")
	{
		ArrayList<int> r;
		r.add(0, 1);
		l.add(0, 2);

		REQUIRE(l != r);
	}

	SECTION("Test Clear then equal")
	{
		l.add(1);
		l.clear();
		REQUIRE(l == ArrayList<int>());
	}

	SECTION("Test Invalid Remove")
	{
		REQUIRE_THROWS(l.remove(0));
	}

	SECTION("Test Set Out of Range")
	{
		REQUIRE_THROWS(l.set(0, 1));
	}

	SECTION("Test Reverse")
	{
		l.add(1); l.add(2); l.add(3);
		ArrayList<int> r = l.reverse();
		ArrayList<int> rr = r.reverse();

		// verify list is reversed
		REQUIRE(r.get(0) == 3);
		REQUIRE(r.get(1) == 2);
		REQUIRE(r.get(2) == 1);

		// reverse of reverse of original list == original list
		REQUIRE(rr == l);
	}

	SECTION("Test Take")
	{
		l.add(1); l.add(2); l.add(3);
		ArrayList<int> t = l.take(1);

		// verify length of list
		REQUIRE(t.size() == 1);
		// verify only element is 1
		REQUIRE(t.get(0) == 1);
	}

	SECTION("Test Drop")
	{
		l.add(1); l.add(2); l.add(3);
		ArrayList<int> d = l.drop(2);

		// verify length of list
		REQUIRE(d.size() == 1);
		// verify only element is 1
		REQUIRE(d.get(0) == 3);
	}

	SECTION("Test Drop Take Reverse")
	{
		l.add(1); l.add(2); l.add(3);
		
		ArrayList<int> r = l.reverse();

		// verify lists are equal
		REQUIRE(l.take(1) == r.drop(2));
	}

	SECTION("Test Invalid Take")
	{
		l.add(1); l.add(2); l.add(3);
		
		// check exception thrown when taking invalid quantity
		REQUIRE_THROWS(l.take(4));
	}

	SECTION("Test Invalid Drop")
	{
		l.add(1); l.add(2); l.add(3);

		// check exception thrown when dropping invalid quantity
		REQUIRE_THROWS(l.drop(4));
	}


	SECTION("Test Concat")
	{
		l.add(1); l.add(2); l.add(3);
		ArrayList<int> o(2); o.add(4); o.add(5);

		ArrayList<int> c = l.concat(o);

		// check new list is correct size and first and last elements
		REQUIRE(c.size() == (l.size() + o.size()));
		REQUIRE(c.get(0) == 1);
		REQUIRE(c.get(4) == 5);
	}

	SECTION("Test mid")
	{
		l.add(1); l.add(2); l.add(3); l.add(4);
		
		ArrayList<int> m = l.mid(0,2);

		// check new list is correct size and first and last elements
		REQUIRE(m.size() == 2);
		REQUIRE(m.get(1) == 2);
	}
}

/**
 *  Ordered List Test Axioms
 */
TEST_CASE("Ordered List Axioms", "[OrderedList]")
{
	OrderedList<int> o;
	
	SECTION("TestAddThenGet")
	{
		o.add(2); o.add(1); o.add(0);
		REQUIRE(o.get(0) == 0);
		REQUIRE(o.get(2) == 2);
	}

	SECTION("Call Invalid Set operation")
	{
		try {
			o.set(0, 0);
		}
		catch (std::exception e) {
			REQUIRE(true == true);
		}
	}

	SECTION("Test Equality")
	{
		OrderedList<int> o; o.add(2); o.add(1); o.add(0);
		OrderedList<int> p; p.add(2); p.add(1); p.add(0);
		REQUIRE(o == p);	
	}

	SECTION("Test Copy Constructor Equality")
	{
		ArrayList<int> a; a.add(2); a.add(1); a.add(0);		
		OrderedList<int> c(a);		
		OrderedList<int> o; o.add(2); o.add(1); o.add(0);
		
		REQUIRE(c == o);
	}
}

/**
 *  BinaryHeap Test Axioms
 */
TEST_CASE("Binary Heap Axioms", "[BinaryHeap]")
{
	BinaryHeap<int> h;
	h.insert(3); h.insert(5); h.insert(2); h.insert(7);

	SECTION("Insert then find")
	{
		REQUIRE(h.find() == 2);
	}

	SECTION("Delete then find")
	{
		h.deleteMin();
		REQUIRE(h.find() == 3);
	}

	SECTION("Constructor - array")
	{
		Array<int> a(4); a[0] = 6; a[1] = 3; a[2] = 4; a[3] = 1;
		BinaryHeap<int> ah(a);

		REQUIRE(ah.find() == 1);
	}
}


/**
 *  BinaryTree Test Axioms
 */
TEST_CASE("Binary Tree Axioms", "[BinaryTree]")
{
	FluentTree< int, BinaryTree<int> > t;

	SECTION("Test Size")
	{
		REQUIRE(t.size() == 0);
	}

	SECTION("Test IsEmpty")
	{
		REQUIRE(t.isEmpty() == true);
	}

	SECTION("Test Not Empty After Add")
	{
		REQUIRE(t.insert(1).isEmpty() == false);
	}

	SECTION("Test Add then Size")
	{
		REQUIRE(t.insert(1).insert(2).insert(3).size() == 3);
	}
	
	SECTION("Test Find Element")
	{
		REQUIRE(t.insert(1).insert(2).find(1) == true);
	}
	
	SECTION("Test Find Non Existent Element")
	{
		REQUIRE(t.insert(1).insert(2).find(3) == false);
	}

	SECTION("Test Remove")
	{
		REQUIRE(t.insert(1).remove(0).size() == 0);
	}
}

/**
 *  HashTable Test Axioms
 */
TEST_CASE("Hash Table Axioms","[HashTable]")
{
	HashTable<std::string> table;

	table.add("apple", "APPLE");
	table.add("orange", "ORANGE");
	table.add("pear", "PEAR");
	table.add("grape", "GRAPE");

	SECTION("TestAddThenFind")
	{
		std::string v;
		REQUIRE((table.find("apple", v) && v == "APPLE"));
	}

	SECTION("")
	{
		table.remove("pear");
		std::string v;
		REQUIRE(table.find("pear", v) == false);
	}

}

/**
 *  Graph Test Axioms
 */
TEST_CASE("Graph Axioms","[Graph]")
{
	Graph g(7, true);
	
	g.addVertex("ATH"); // Athens
	g.addVertex("BFS"); // Belfast
	g.addVertex("CDG"); // Paris
	g.addVertex("DUB"); // Dublin
	g.addVertex("FCO"); // Rome
	g.addVertex("FRA"); // Frankfurt
	g.addVertex("LHR"); // London

	g.addEdge("BFS","DUB");
	g.addEdge("BFS","FRA");

	g.addEdge("DUB","BFS");
	g.addEdge("DUB","CDG");

	g.addEdge("LHR","FRA");
	g.addEdge("LHR","FCO");

	g.addEdge("CDG","LHR");
	
	g.addEdge("FRA", "LHR");
	g.addEdge("FRA","FCO");

	g.addEdge("FCO","ATH");

	g.addEdge("ATH", "FRA");

	SECTION("Test Direct Steps To")
	{
		REQUIRE(g.stepsTo("BFS", "DUB", 1) == true);
	}
	
	SECTION("Test Indirect StepsTo")
	{
		REQUIRE(g.stepsTo("BFS", "CDG", 2));
	}

	SECTION("Test No Route")
	{
		REQUIRE(g.stepsTo("BFS", "FCO", 1) == false);

	}

	SECTION("Test DFS and BFS")
	{
		Graph g(6, true);

		g.addVertex("A"); 
		g.addVertex("B"); 
		g.addVertex("C"); 
		g.addVertex("D"); 
		g.addVertex("E"); 
		g.addVertex("F"); 

		g.addEdge("A","D");
		g.addEdge("B","A");
		g.addEdge("C","A");
		g.addEdge("C","B");
		g.addEdge("D","F");
		g.addEdge("E","A");
		g.addEdge("E","B");
		g.addEdge("E","F");

		// expected BFS path
		ArrayList<std::string> b;
		b.add("C"); b.add("A"); b.add("B"); b.add("D"); b.add("F");
	
		// expected DFS path 
		ArrayList<std::string> d;
		d.add("C"); d.add("A"); d.add("D"); d.add("F"); d.add("B");
	
		REQUIRE(g.bfs("C") == b);
		REQUIRE(g.dfs("C") == d);
	}
}


/**
 *  Sort Test Axioms
 */
TEST_CASE("Sort Axioms","[Sort]")
{
	Array<int> a(10);
	a[0] = 27; a[1] = 13; a[2] = 42; a[3] = 16; a[4] = 24; a[5] = 75; a[6] = 2; a[7] = 18; a[8] = 34; a[9] = 9;
	
	SECTION("InsertionSort")
	{
		insertionSort(a);
		REQUIRE(a[0] == 2);
		REQUIRE(a[9] == 75);
		
	}	
	SECTION("SelectionSort")
	{
		selectionSort(a);
		REQUIRE(a[0] == 2);
		REQUIRE(a[9] == 75);
	
	}
}

/**
* Ordered Search Axioms
*/
TEST_CASE("Ordered Search Axioms", "[Search]")
{
	// arrange an ordered 10 element array
	Array<int> oa(10);
	oa[0] = 5; oa[1] = 10; oa[2] = 13; oa[3] = 21; oa[4] = 21; oa[5] = 29; oa[6] = 34; oa[7] = 38; oa[8] = 45; oa[9] = 60;
	
	//loadFromFile<int>(oa, "ordered.txt");

	SECTION("Binary Search Success")
	{
		//assert that array is ordered
		REQUIRE(isOrdered<int>(oa) == true);

		//assert that 5 is found at position 0
		REQUIRE(binarySearch<int>(oa,5) == 0);

		// assert that 60 is found at postion 9
		REQUIRE(binarySearch<int>(oa,60) == 9);
	}

	SECTION("Binary Search Failure")
	{
		//assert that 100 is not found
		REQUIRE(binarySearch<int>(oa,100) == -1);
	}

	SECTION("Count ordered occurrence exists")
	{
		//assert that 21 occurs twice
		REQUIRE(countOccurrenceOrdered<int>(oa,21) == 2);		
	}

	SECTION("Count ordered occurence non existent")
	{
		//assert that 100 is not found
		REQUIRE(countOccurrenceOrdered<int>(oa,100) == 0);
	} 
}


/**
 * UnOrdered Search Axioms
 */
TEST_CASE("UnOrdered Search Axioms", "[Search]")
{
	// arrange an ordered 10 element int array
	Array<int> ua(10);
	ua[0] = 5; ua[1] = 10; ua[2] = 3; ua[3] = 11; ua[4] = 7; ua[5] = 9; ua[6] = 3; ua[7] = 18; ua[8] = 5; ua[9] = 20;

	// arrange an unordered 5 element string array
	Array<std::string> uas(5);
	uas[0] = "tue"; uas[1] = "mon"; uas[2] = "sun" ; uas[3] = "fri"; uas[4] = "sat";
	//loadFromFile<std::string>(ua, "words.txt");


	SECTION("Sequential Search Success")
	{
		//assert that 5 is found at position 0
		REQUIRE(sequentialSearch<int>(ua,5) == 0);

		// assert that 20 is found at postion 9
		REQUIRE(sequentialSearch<int>(ua,20) == 9);

		//assert that tue is found at position 0
		REQUIRE(sequentialSearch<std::string>(uas,"tue") == 0);

		// assert that sat is found at postion 4
		REQUIRE(sequentialSearch<std::string>(uas,"sat") == 4);

	}

	SECTION("Sequential Search Failure")
	{
		//assert that 100 is not found in int array
		REQUIRE(sequentialSearch<int>(ua,100) == -1);

		// assert that "wed" is not found in string array
		REQUIRE(sequentialSearch<std::string>(uas,"wed") == -1);
	}

	SECTION("Count occurence exists")
	{
		//assert that 3 is found twice
		REQUIRE(countOccurrence<int>(ua,3) == 2);

		// assert that "tue" is found once
		REQUIRE(countOccurrence<std::string>(uas,"tue") == 1);
	}

	SECTION("Count occurence non-existent")
	{
		//assert that counting occurrence of 100 returns 0
		REQUIRE(countOccurrence<int>(ua,100) == 0);

		// assert that counting occurence of "wed" returns 0
		REQUIRE(countOccurrence<std::string>(uas,"wed") == 0);
	}

	SECTION("containsAll Success")
	{
		// create the keys array
		Array<int> keys(2);

		// populate the keys that are found		
		keys[0] = 3; keys[1] = 7;

		//assert that 2 and 6 are contained in array
		REQUIRE(containsAll<int>(ua, keys) == true);
	}

	SECTION("containsAll Failure")
	{
		// create the keys array
		Array<int> keys(2);
		// populate the keys that are not found
		keys[0] = 1; keys[1] = 6;
		
		//assert that 1 and 6 are not contained in array
		REQUIRE(containsAll<int>(ua, keys) == false);
	}

}

// ----------- Main method calls catch and menu ------------

int main(int argc, char* argv[]) {

	// run the tests
	int result = Catch::Session().run(argc, argv);

	// ---------------------------------------------------
	std::cout << std::endl << "Press enter to quit";
	std::cin.sync(); // flush input buffer
	std::cin.ignore(); // ignore what user enters


	return result;
}

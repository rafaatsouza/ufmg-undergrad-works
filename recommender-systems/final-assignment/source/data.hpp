#include <cmath>
#include <fstream>
#include <iostream>

#ifndef _STRING_
#include "stringMethods.hpp"
#endif

#ifndef _GRAPH_
#include "graph.hpp"
#endif

#define _DATA_
#define EVALUATION_SIZE 70 // Percentage of the data set used to evaluate the recommender system
#define RANK_SIZE 23 // The rank size used to recommend a "top-n ranking"
#define THRESHOLD_RATE 3 // Threshold identifying positive and negative rates (rate > THRESHOLD_RATE is positive).

/* ------------- Dataset ------------ */
#define RATINGS "DataSet/ratings.csv"
#define BOOK_CONTENT "DataSet/books.csv"
#define BOOK_TAGS "DataSet/book_tags.csv"
/* ---------------------------------- */

using namespace std;

typedef map<int, int> Mii;

/*
	Used to get the string related to a series of a book. The dataset is not standardized.
	This function solves those inconsistencies.
*/
string getBookSeries(string s);

// Read tags for all books, and insert them into a set of tags of a book.
void readBookTags(Mii &IDS, Graph &G);

/*
	- Read books content from the dataset. The content contains:
		-> Authors
		-> Tags
		-> Average rate

	- The function also returns the total number of books in the variable
	  start. It is used to build the graph, modifiyng users' ids.
	  (View description on graph.h).
*/
Graph readContent(int *start);

/*
	Read ratings given by users to books, and build a graph G (view graph structure in grap.h).
	The graph G2 contains the test set, that is, pairs (user,book) used in the recommender system
	to generate ranks. In the end, the rates of each (user,book) from G2 are used to calculate
	errors between the real rank and the rank generated by the recommender system.
*/
void readRatings(Graph &G, Graph &G2, int start);
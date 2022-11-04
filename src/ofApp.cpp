#include "ofApp.h"

// Define root node
Node* root = NULL;

// Define list of values to be inserted into tree
vector<int> inputValues;

// Counter for values to be inserted
int c = 0;

// Initialize input value list
void vectorInit() {
	for (int i = 1; i < 51; i++) {
		inputValues.push_back(i);
	}

	// Returns a random list of unique values
	random_shuffle(inputValues.begin(), inputValues.end());
}

// Custom function to insert node into tree
void insert(int data) {

	// Allocate a temporary node
	Node* tempNode = (Node*)malloc(sizeof(Node));
	
	// Declare current and parent nodes for future use in recursion
	Node* current;
	Node* parent;

	// Initialize temporary node
	tempNode->data = data;
	tempNode->left = NULL;
	tempNode->right = NULL;

	// If there isn't a root node yet, set the root node to tempNode. This will only occur the first time insert() is called
	if (root == NULL) {
		root = tempNode;
	}
	else {
		// Set the 'current' node to the root node initially
		current = root;

		// Set the 'parent' node to null initially
		parent = NULL;

		// Find a spot for the node
		while (1) {
			// Traverse the tree in search of an empty spot
			
			// Parent will serve as the 'pivot' for comparing the incoming value with the current node
			parent = current;

			// Check if the incoming value is less than the current parent node, if so, it belongs to the left of it
			if (data < parent->data) {

				// Set the current node to the previous current node's child, thus, 'moving' to the left
				current = current->left;

				// If the spot is empty, then simply add the value to the spot. Otherwise, keep the ~"recursion" going (not truly recursive)
				if (current == NULL) {
					parent->left = tempNode;
					return;
				}
			}
			else {
				// If the incoming value doesn't fall into the previous condition, then it belongs to the right of its parent node
				current = current->right;

				if (current == NULL) {
					parent->right = tempNode;
					return;
				}
			}
		}
	}
}

// Function to 'traverse' the tree, or 'navigate' it. Also doubles as a function to count the number of elements, and add them together
// The function will receive a reference to the root node initially, this reference will be given recursively until the end of the tree
// The call stack will handle the recursive nature of the function, so when a null node is found, it backtracks by itself 
// Count and sum are also passed as references to make it easier to update their values
// This function is called 'inorder traversal'. Consequently displaying values in ascending order
void traversal(Node* root, int* count, int* sum) {
	if (root != NULL) {
		traversal(root->left, count, sum);
		printf("%d ", root->data);
		(*count)++;
		(*sum) += root->data;
		traversal(root->right, count, sum);
	}
}

// Custom function using Open Framework's methods to display the tree as a graphic
// This function behaves similarly to 'traversal', in its recursive nature
void ofApp::printTree(int x, int y, Node* root, int index) {
	if (root != NULL) {
		ofSetColor(255, 69, 0); // Sets color of 'thing' to be drawn
		ofDrawCircle(x, y, 15); // Draw circle at x, y with radius 15

		if (root->left != NULL) {
			ofDrawLine(x, y, x - y / (index + 1), y + 50); // If there is a node to the left, draw a line from root to root->left
		}

		if (root->right != NULL) {
			ofDrawLine(x, y, x + y / (index + 1), y + 50); // If there is a node to the right, draw a line from root to root->right
		}

		ofSetColor(255, 255, 255); // Set the text's color to white
		font.drawStringCentered(ofToString(root->data), x, y); // Display the node's value at x, y

		// Based on the node's 'index', calculate a new index value, to display the nodes in an increasingly shorter distance from each other
		int left = 2 * index + 1;
		int right = 2 * index + 2;

		// Recursively call the printTree function, giving it the next x and y positions, the next node, and next left and right indexes
		ofApp::printTree((x - y / (index + 1)), y + 50, root->left, left);

		ofApp::printTree((x + y / (index + 1)), y + 50, root->right, right);
	}
}

// This function returns the depth of the tree. Which is calculated recursively
int treeDepth(Node* root) { 
	if (root == NULL)
		return 0; // If the given node is null, break out

	int leftDepth = treeDepth(root->left); // Recursively search left, eventually will return 0
	int rightDepth = treeDepth(root->right); // Recursively search right, eventually will return 0

	// Return the larger value to the "next" (more like previous) iteration, which will ultimately return the result
	if (leftDepth > rightDepth)
		return leftDepth + 1;
	else
		return rightDepth + 1;
}

//-------------------------------------------------------------- Open frameworks function. Runs once at the start of the program
void ofApp::setup(){
	ofBackground(12, 12, 12); // Set background color
	ofSetWindowTitle("Visualizacao - Arvore"); // Set window title
	ofSetFrameRate(60); // Set frame rate
	ofSetCircleResolution(40); // Set number of steps for a circle, making it look smoother
	ofSetWindowPosition(320, 180); // Set window position

	font.load("Roboto-Regular.ttf", 12); // Load a font to display text

	vectorInit(); // Call the input vector initializer
}

//-------------------------------------------------------------- Open frameworks function. Runs every frame, set by the framerate
void ofApp::draw(){
	ofApp::printTree(640, 200, root, 0);
}

//-------------------------------------------------------------- Open frameworks function. Listens to keyboard input
void ofApp::keyPressed(int key) {
	// Press A to insert a new node into the tree
	// 97 == 'A'
	if (key == 97) {
		// Declare a node count and sum variables
		int nodeCount = 0, sum = 0;

		// Clear the terminal - ONLY ON WINDOWS
		system("cls");

		// Insert a value from the inputValues array using 'c' as an index, ensuring no duplicates
		insert(inputValues[c]);
		c++;

		// Traverse the tree
		traversal(root, &nodeCount, &sum);

		// Display the results
		cout << "\nContagem: " << nodeCount << "\nSomatoria: " << sum << "\nProfundidade: " << treeDepth(root) << endl;
	}
}
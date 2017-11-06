// CONNOR BESSELL, CSCE 221: 503
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

void printTree ( vector< vector<int> > tree, int height, string selectFile ) {
	
	if ( height >= 4 ) {
		
		cout << "Large input size, outputting to corresponding file\n";
		string selectFiled = "OUTPUTFILES/" + selectFile + ".txt";
		cout << "Directory path: " << selectFiled << "\n";
		ofstream oFile;
		oFile.open( selectFiled );
		
		oFile << "[";
		unsigned int rowTemp = 0;
		for ( unsigned int row = 0; row < tree.size(); row++ ) {
		
			for ( unsigned int col = 0; col < tree[row].size(); col++ ) {
			
				if ( row != rowTemp ) { oFile << "]\n["; }
				oFile << " " << tree[row][col] << " ";
				rowTemp = row;
			
				}
			}
		oFile << "]\n";
		
		oFile.close();
		
		}
	
	else {
	
		cout << "[";
		unsigned int rowTemp = 0;
		for ( unsigned int row = 0; row < tree.size(); row++ ) {
		
			for ( unsigned int col = 0; col < tree[row].size(); col++ ) {
			
				if ( row != rowTemp ) { cout << "]\n["; }
				cout << " " << tree[row][col] << " ";
				rowTemp = row;
			
				}
			}
		cout << "]\n";
	
	}
	
}

void findTreeValue ( vector< vector<int> > tree, int n, int height ) {
	
	unsigned int row = 0, col = 0, searchCost = 1;
			
	while ( row <= height ) {
			
		if ( n == tree[row][col] ) { 
				
			cout << "Found " << n <<  " at: [" << row << "][" << col << "]\n";
			cout << "Search cost = " << searchCost << "\n";
			return; 
				
			}
				
		else if ( n < tree[row][col] ) { row = row + 1; col = 2 * col; ++searchCost;  }
			
		else { row = row + 1; col = (2 * col) + 1; ++searchCost; }
		
		}
	
	cout << n << " was not found\n";
	return;
}

void insertTreeValue ( vector< vector<int> > &tree, int n, int height ) {
	
	vector<int> vt ( exp2( height + 1 ) );
	
	unsigned int row = 0, col = 0;
	
	while ( row <= height ) {
			
		if ( n == tree[row][col] ) { 
				
			cout << n << " all ready exists in the tree\n";
			return; 
				
			}
				
		else if ( n < tree[row][col] ) { row = row + 1; col = 2 * col; }
			
		else if ( n > tree[row][col]) { row = row + 1; col = (2 * col) + 1; }
		
		else { vt[col] = n; tree.push_back( vt ); return; }
		
		}
	
	cout << n << " was not inserted\n";
	return;
}

void deleteTreeValue ( vector< vector<int> > &tree, int n, int height ) {
	
	unsigned int row = 0, col = 0;
			
	while ( row <= height ) {
			
		if ( n == tree[row][col] ) { 
				
			tree[row][col] = 0;
			return; 
				
			}
				
		else if ( n < tree[row][col] ) { row = row + 1; col = 2 * col; }
			
		else { row = row + 1; col = (2 * col) + 1; }
		
		}
	
	cout << n << " was not found so it can not be deleted\n";
	return;
	
}

int main(  ) {
		
	int operation, iVal;
	bool more;
	string selectFile, selectFiled;
	flag0:
	cout << "This program takes input integers and creates a balanced BST every time\n";
	cout << "It requires data sorted in assending to work properly\n";
	cout << "It can also handle inputs that are not powers of 2\n";
	cout << "Note: 0 = null for the scope of this program\n";
	cout << "\tno need to specify the directory or file suffix, I got you covered!\n";
	cout << "\t(1 - 12)(p, r, l) --- Example inputs: 2p , 4l , 12r \ninput: ";
	cin >> selectFile;
	
	selectFiled = "INPUTFILES/" + selectFile + ".txt";

	ifstream iFile( selectFiled );

	if ( ! iFile ) { cout << "NO SUCH FILE EXISTS\n"; goto flag0; }

	vector<int> v;
	int data;

	while ( iFile >> data ) { v.push_back( data ); }
	sort( v.begin(), v.end() );  
	
	cout << "Sorted vector:  ";
	for ( unsigned int owo = 0; owo < v.size(); ++owo ) {
		cout << v.at( owo ) << "  ";
		}
	cout << "\nSize = " << v.size() << "\n";
	
	int height = floor( log2( v.size() ) );
	cout << "Height = " << height << "\n";
	
	vector< vector<int> > vv;
	vector<int> vt;
	
	int searchCost = 1, totalSearchCost = 0;
	int sizeFactor, nexus, j, tempCost;
	int i = 0;
	while( i <= height ) {
		
		sizeFactor = ( v.size() - 1 ) / ( exp2( i + 1 ) );
		// cout << "sizeFactor = " << sizeFactor << "\n";
		vt.push_back( v.at( sizeFactor ) );
			
			j = 1;
			while ( j <= ( exp2( i ) - 1 ) ) {
				
				nexus = j * ( ( v.size() - 1 ) / ( exp2( i ) - 1 ) );
				// cout << "nexus = " << nexus << "\n";
				vt.push_back( v.at( nexus - sizeFactor ) );
				
				++j;
				}
		
		tempCost = j * searchCost;
		cout << "current searchCost = " << tempCost << "\n";
		totalSearchCost = totalSearchCost + tempCost;
		vv.push_back( vt );	
		vt.clear();
		++i;
		++searchCost;
		}
	
	cout << "totalSearchCost = " << totalSearchCost << "\n";
	cout << "averageSearchCost = " << totalSearchCost / v.size() << "\n";
	// cout << "Row 0 size = " << vv.at(0).size() << "\n";
	// cout << "Row 1 size = " << vv.at(1).size() << "\n";
	// cout << "Row 2 size = " << vv.at(2).size() << "\n";
	// cout << "Row 3 size = " << vv.at(3).size() << "\n";
	
	cout << "BST vector vv level by level: \n";
	printTree( vv, height, selectFile );
	
	
	// Accounting for Dupes
	int n;
	i = 0;
	for ( unsigned int row = 0; row < vv.size(); row++ ) {
		
		for ( unsigned int col = 0; col < vv[row].size(); col++ ) {
			
			n = vv[row][col];
			
			for ( unsigned int r = row; r < vv.size(); r++ ) {
		
				for ( unsigned int c = col+1; c < vv[r].size(); c++ ) {
					
					if ( n == vv[r][c] ) { 
						
						vv[r][c] = 0;
						
						}
					
					}
				}
		
			}
		}
	
	cout << "BST vector vv level by level accounting for dupes: \n";
	printTree( vv, height, selectFile );
	
	
	// Balancing the tree
	for ( unsigned int row = 0; row < vv.size(); row++ ) {
		
		for ( unsigned int col = 0; col < vv[row].size(); col++ ) {
			
			if ( ( vv[row][col] == 0 ) && ( row < height ) ) {
				
				// cout << "Zero found\n";
				
				if ( vv[ row + 1 ][ 2 * col ] > 0 ) {
					
					vv[row][col] = vv[ row + 1 ][ 2 * col ];
					vv[ row + 1 ][ 2 * col ] = 0;
					
					}
					
				if ( vv[ row + 1 ][ (2 * col) + 1 ] > 0 ) {
					
					vv[row][col] = vv[ row + 1 ][ (2 * col) + 1 ];
					vv[ row + 1 ][ (2 * col) + 1 ] = 0;
					
					}
				
				}
		
			}
		}
	
	cout << "FINAL BST vector vv level by level: \n";
	printTree( vv, height, selectFile );
	
	flag1:
	cout << "Choose a tree operation: 1 = find , 2 = insert , 3 = delete , 4 = new tree\n";
	cout << "\t( Type any other number to quit )\n";
	cin >> operation;
	
	if ( operation == 1 ) { 
		
		cout << "find what value? : \n";
		cin >> iVal;
		findTreeValue( vv, iVal, height ); 
		cout << "Try another? : 1 = Yes , 0 = No\n";
		cin >> more;
		
		if ( more == 1 ) { goto flag1; }
		
		}
		
	else if ( operation == 2 ) {
		
		cout << "insert what value? : \n";
		cin >> iVal;
		insertTreeValue( vv, iVal, height );
		printTree( vv, height, selectFile );
		cout << "Try another? : 1 = Yes , 0 = No\n";
		cin >> more;
		
		if ( more == 1 ) { goto flag1; }
		
		}
		
	else if ( operation == 3 ) {
		
		cout << "delete what value? : \n";
		cin >> iVal;
		deleteTreeValue( vv, iVal, height );
		printTree( vv, height, selectFile );
		cout << "Try another? : 1 = Yes , 0 = No\n";
		cin >> more;
		
		if ( more == 1 ) { goto flag1; }
		
		}
	
	else if ( operation == 4 ) {
		
		cout << "Really make a new tree? : 1 = Yes, 0 = No\n";
		cin >> more;
		
		if ( more == 1 ) { goto flag0; }
		else { goto flag1; }
		
		}
	
	return 0;	
}


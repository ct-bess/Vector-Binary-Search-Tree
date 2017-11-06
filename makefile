all: YeaBoy

YeaBoy: Balanced_BST.cpp
	g++ -std=c++11 Balanced_BST.cpp -o a

clean:
	rm *.o a

all:
	./conv.rb
	g++-4.9 collected.cpp -o it -std=c++11

all:
	./compile.rb
	g++-4.9 compiled.cpp -o it -std=c++11

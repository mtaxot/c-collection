all:
	@gcc -O3 -Wall test-list.c list.c -o test-list
	@gcc -O3 -Wall test-map.c map.c -o test-map
	@gcc -O3 -Wall test-array.c array.c -o test-array
clean:
	@rm -rf test-list test-map test-array

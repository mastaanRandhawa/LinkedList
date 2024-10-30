test_list: list.c test_list.c
	gcc -o $@ list.c test_list.c -I.

clean:
	rm -f test_list

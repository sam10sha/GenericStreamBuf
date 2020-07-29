main: bin/main

bin/main: obj/* | bin
	g++ -o $@ $^

obj/*: src/Sources/* | obj
	for i in $^; do\
	    echo g++ -c -std=c++11 -Wall -I$(PWD)/src/Headers -o obj/$$(basename $${i%.*}).o $$i;\
	    g++ -c -std=c++11 -Wall -I$(PWD)/src/Headers -o obj/$$(basename $${i%.*}).o $$i;\
	done

bin:
	mkdir -p $@

obj:
	mkdir -p $@

clean:
	rm -f bin/* obj/*


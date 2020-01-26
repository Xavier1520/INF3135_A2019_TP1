tournament: tournament.c
	gcc -o tournament tournament.c

html:
	pandoc -f markdown -t html README.md

.PHONY: test

test:
	bats check.bats

clean:
	rm -rf *.o *.out *.html *.swp *.save

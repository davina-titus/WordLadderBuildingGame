build:
	gcc -g main.c -o ladders.exe

run_fun:
	./ladders.exe -p ON -n 4 -d dictionary.txt -s RAND -f RAND

run:
	./ladders.exe

run_play:
	./ladders.exe -p ON -n 5 -d dictionary.txt -s flame -f spark

run_solve:
	./ladders.exe -n 4 -d dictionary.txt -s data -f code

run_simple3:
	./ladders.exe -n 3 -d simple3.txt -s toe -f ear

run_simple4:
	./ladders.exe -n 4 -d simple4.txt -s data -f code

run_simple5:
	./ladders.exe -n 5 -d simple5.txt -s spark -f shank

valgrind:
	valgrind --leak-check=full --track-origins=yes ./ladders.exe -n 3 -d simple3.txt -s toe -f ear

run_redirect:
	./ladders.exe -p ON -n 5 -d dictionary.txt -s flame -f spark < gameplayDemoInputs.txt

clean:
	rm -f ladders.exe	gcc -g main.c -o ladders.exe

run_fun:
	./ladders.exe -p ON -n 4 -d dictionary.txt -s RAND -f RAND

    

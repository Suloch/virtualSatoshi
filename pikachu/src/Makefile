default:
	gcc -g machine.c instruction.c utils.c main.c -o build/pikachu

test:
	gcc -g machine.c instruction.c utils.c ../test/test.c ../test/test_mvi.c ../test/test_mov.c -o build/t

clean:
	rm build/pikachu

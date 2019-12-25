default:
	gcc -g machine.c instruction.c utils.c main.c -o build/pikachu

test:
	gcc -g machine.c instruction.c utils.c ../test/test.c ../test/test_and.c ../test/test_or.c ../test/test_mvi.c ../test/test_mov.c ../test/test_cmp.c ../test/execute.c -o build/t

clean:
	rm build/pikachu

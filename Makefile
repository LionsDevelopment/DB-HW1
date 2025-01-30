all: 
	g++ -Wall main.cpp Database.cpp -o main
clean:
	-rm main
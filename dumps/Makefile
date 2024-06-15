CXX := g++
OBJECTS := ./build/main.o ./build/server.o

blazeCoin: $(OBJECTS)
	$(CXX) $(OBJECTS) -o ./bin/blazeCoin

./build/%.o: ./src/%.cpp
	$(CXX) -c $< -o $@

clean:
	rm ./build/*.o ./bin/blazeCoin

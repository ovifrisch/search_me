CPP := g++
CFLAGS := -Wall -Werror
DEPS := Database.h
objs := main.o Database.o

search_me: $(objs)
	$(CPP) $(CFLAGS) -o $@ $^

%.o: %.cpp $(DEPS)
	$(CPP) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(objs)

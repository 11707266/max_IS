all: tool_td
tool_td: tool_td.cpp IS.h
	g++ -o tool_td tool_td.cpp 

tool: tool.cpp 
	g++ -o tool tool.cpp 

clean:
	rm -f tool tool_td *.o

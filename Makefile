CXX = gcc
CXXFLAGS = -std=c++14 -g -Wall -MMD -DDEBUG
OBJECTS = academicbuilding.o board.o controller.o dice.o gym.o main.o ownableproperty.o player.o residence.o square.o subject.o unownableproperty.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = watopoly

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS} # reads the .d files and reruns dependencies

clean :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}

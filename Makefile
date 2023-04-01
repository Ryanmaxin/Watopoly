CXX = gcc
CXXFLAGS = -std=c++14 -g -Wall -MMD
OBJECTS = academicbuilding.o board.o controller.o dice.o gym.o main.o observer.o ownableproperty.o player.o residence.o squares.o subject.o textdisplay.o unownableproperty.o view.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = Watopoly

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS} # reads the .d files and reruns dependencies

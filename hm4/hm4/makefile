# makefile for airport

CCC = g++
CXXFLAGs = -Wall -g -std=c++0x
CXXLINK = $(CCC)
LIBS =
OBJS = main.o Lists.o Message.o Follower.o Leader.o SocialNetwork.o
TARGET = MamatNet
RM = rm -f

$(TARGET): $(OBJS)
	$(CXXLINK) -o $(TARGET) $(OBJS) $(LIBS)
	
# Creating object files using default rules
	
Lists.o: Lists.C Lists.H defs.H
Message.o: Message.C Message.H Lists.H defs.H
Follower.o: Follower.H Follower.C Message.H Lists.H defs.H
Leader.o: Leader.H Leader.C Follower.H Message.H Lists.H defs.H
SocialNetwork.o: SocialNetwork.H Leader.H Follower.H Message.H Lists.H defs.H
main.o: main.C SocialNetwork.H Leader.H Follower.H Message.H Lists.H defs.H

#Cleaning old files before new make
clean:
	$(RM) $(TARGET) *.o *.bak *~ "#"* core


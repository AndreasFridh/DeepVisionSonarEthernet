CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g -ggdb -ffunction-sections -O0 -std=c++14 -D LINUX

SRCS=EthernetSonar.cpp EthernetSonarAPI.cpp DVSFileWriter.cpp JSONFileWriter.cpp DSSPParser.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: EthernetSonarExample

EthernetSonarExample: $(OBJS)
	$(CXX) $(LDFLAGS) -o EthernetSonar $(OBJS) $(LDLIBS)

depend: .depend

.depend: $(SRCS)
	$(RM) ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) *~ .depend

include .depend

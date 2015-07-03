CC = clang++

BUILDDIR = build

CFLAGS = 

CPPFLAGS = -std=c++14 -stdlib=libc++

$(BUILDDIR)/libevent.so : $(BUILDDIR) $(BUILDDIR)/libevent.o \
$(BUILDDIR)/libevent.hh
	$(CC) $(CFLAGS) $(CPPFLAGS) -shared $(BUILDDIR)/libevent.o -o \
	$(BUILDDIR)/libevent.so

$(BUILDDIR)/libevent.hh : libevent.hh
	cp libevent.hh $(BUILDDIR)/libevent.hh
	
$(BUILDDIR)/libevent.o : libevent.cc libevent.hh
	$(CC) $(CFLAGS) $(CPPFLAGS) -fpic -c libevent.cc -o \
	$(BUILDDIR)/libevent.o
	
$(BUILDDIR) : 
	mkdir $(BUILDDIR)
	
.PHONY : clean

clean : 
	rm build/*
CC = clang++

BUILDDIR = build

CFLAGS = 

CPPFLAGS = -std=c++14 -stdlib=libc++
	
$(BUILDDIR)/liblogging.so : $(BUILDDIR) $(BUILDDIR)/liblogging.o \
$(BUILDDIR)/liblogging.hh
	$(CC) -shared $(BUILDDIR)/liblogging.o -o $(BUILDDIR)/liblogging.so
	
$(BUILDDIR)/liblogging.o : liblogging.cc liblogging.hh
	$(CC) $(CFLAGS) $(CPPFLAGS) -fpic -c liblogging.cc -o \
	$(BUILDDIR)/liblogging.o
	
$(BUILDDIR)/liblogging.hh : liblogging.hh
	cp liblogging.hh $(BUILDDIR)/liblogging.hh
	
$(BUILDDIR) :
	mkdir $(BUILDDIR)

.PHONY : clean install
clean : $(BUILDDIR)
	-rm $(BUILDDIR)/*
	
install : 
	

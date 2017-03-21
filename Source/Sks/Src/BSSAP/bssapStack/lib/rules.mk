#
# standard rules and dependencies
#
$(obj): %.o: $(ROOT_DIR)%.c $(genhdr)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

$(module): $(obj) $(genhdr) $(genobj)
	$(LD) -r -o $@ $(obj) $(genobj)

$(library): $(obj) $(genhdr) $(genobj)
	$(RM) $(library) && $(AR) $(ARFLAGS) $(library) $(obj) $(genobj) && $(RANLIB) $(library)

clean:
	rm -f $(obj) $(exe) $(module) $(genhdr) $(genobj) $(library)

%.i: %.c
	$(CPP) $(CPPFLAGS) $< -o $@

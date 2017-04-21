CFLAGS := -Wall

override-hosts.so: override-hosts.c
	$(CC) $(CFLAGS) -fPIC -shared -ldl $+ -o $@

.PHONY: clean
clean:
	rm -rf override-hosts.so

.PHONY: test
test: override-hosts.so
	LD_PRELOAD=$(CURDIR)/override-hosts.so \
	OVERRIDE_HOSTS_FROM=example.org,example.com \
	OVERRIDE_HOSTS_TO=127.0.0.1 \
	./test.py

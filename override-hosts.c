#define _GNU_SOURCE
#include <netdb.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static typeof(getaddrinfo) *real_getaddrinfo;
static char *hosts;
static char *target;
size_t hosts_len;

__attribute__((constructor))
static void initialize() {
	hosts = getenv("OVERRIDE_HOSTS_FROM");
	assert(hosts != 0);
	hosts_len = strlen(hosts);
	target = getenv("OVERRIDE_HOSTS_TO");
	assert(target != 0);
	real_getaddrinfo = dlsym(RTLD_NEXT, "getaddrinfo");
}

int getaddrinfo(const char *node, const char *service, const struct addrinfo *hints, struct addrinfo **res) {
	size_t node_len = strlen(node);
	char *pos_str = memmem(hosts, hosts_len, node, node_len);
	if (pos_str != 0) {
		// Ensure that found match contains full hostname
		if (pos_str != hosts && *(pos_str - 1) != ',') {
			// If it's not at the beginning of list, it must be preceded by comma
			pos_str = 0;
		} else {
			char char_after = *(pos_str + node_len);
			if (char_after != ',' && char_after != '\0') {
				// It must be followed by either comma or `\0` (end of string)
				pos_str = 0;
			}
		}
		if (pos_str != 0) {
			node = target;
		}
	}
	return real_getaddrinfo(node, service, hints, res);
}

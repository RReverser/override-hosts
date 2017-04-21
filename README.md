# override-hosts

Small shared library utility to temporarily override list of hosts to specific IP/host (only one target for now). This is useful when you want to override hostname or IP to visit `https://...` website, as just changing `Host` header is not enough due to SNI checks.

It's kinda like `/etc/hosts` but for one-off temporary overrides without `sudo` permissions.

If you're using `curl`, you should use built-in `curl --resolve ...` option instead, as it provides the same functionality in a safer way.

Usage (Linux only):

```bash
LD_PRELOAD=$(pwd)/override-hosts.so \
OVERRIDE_HOSTS_FROM=example.org,example.com \
OVERRIDE_HOSTS_TO=127.0.0.1 \
your_command
```

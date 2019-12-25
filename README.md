# libvdeslirp
libslirp for Linux made easy peasy

## Slirp

Originally designed to provide PPP/SLIP over terminal lines, slirp is a general purpose TCP-IP emulator widely used
by virtual machine hypervisors to provide virtual networking services.

Qemu, virtualbox, user-mode linux include slirp to provide the guest os with a virtual network while requiring neither
configuration nor privileged services on the host.

The qemu team has split their implementation of slirp from the main Qemu project and released it as a library
named `libslirp`.

This project wraps the libslirp code in a library featuring a clean and simple interface.

## Installation Prerequisites:

[libslirp](https://gitlab.freedesktop.org/slirp/libslirp).

Libslirp can be installed from its git repository. 
Alternatively, it is a package in Debian Sid thus users of this distribution can simply add the packet:

```sh
apt-get install libslirp0 libslirp-dec
```

## install libvdeslirp

```sh
$ mkdir build
$ cd build
$ cmake ..
$ make
$sudo make install
```

## libvdeslirp tutorial

### libvdesplirp's Hello World

The simplest way to use the library is the following:

setup:
```C
#include <slirp/libslirp.h>
...
SlirpConfig slirpcfg;
struct vdeslirp *myslirp;
vdeslirp_init(&slirpcfg, VDE_INIT_DEFAULT);
myslirp = vdeslirp_open(&slirpcfg);
```
send and receive packets (ethernet packets as if it were a tap interface):
```C
n = vdeslirp_send(myslirp, sendbuf, sendlen);
...
n = vdeslirp_recv(myslirp, recvbuf, recvlen);
```

poll/select or similar system calls can be used to wait for new incoming packets,
use the return value of `vdeslirp_fd(myslirp)` as the file descriptor.

at the end:
```C
vdeslirp_close(myslirp);
```

### include the header file

```C
#include <slirp/libslirp.h>
```

### set up slirp configuration

The confuguration parameters for Slirp are defined in a `SlirpConfig` structure (as defined by libslirp):
```C
typedef struct SlirpConfig {
    /* Version must be provided */
    uint32_t version;
    /*
     * Fields introduced in SlirpConfig version 1 begin
     */
    int restricted;
    bool in_enabled;
    struct in_addr vnetwork;
    struct in_addr vnetmask;
    struct in_addr vhost;
    bool in6_enabled;
    struct in6_addr vprefix_addr6;
    uint8_t vprefix_len;
    struct in6_addr vhost6;
    const char *vhostname;
    const char *tftp_server_name;
    const char *tftp_path;
    const char *bootfile;
    struct in_addr vdhcp_start;
    struct in_addr vnameserver;
    struct in6_addr vnameserver6;
    const char **vdnssearch;
    const char *vdomainname;
    /* Default: IF_MTU_DEFAULT */
    size_t if_mtu;
    /* Default: IF_MRU_DEFAULT */
    size_t if_mru;
    /* Prohibit connecting to 127.0.0.1:* */
    bool disable_host_loopback;
    /*
     * Enable emulation code (*warning*: this code isn't safe, it is not
     * recommended to enable it)
     */
    bool enable_emu;
    /*
     * Fields introduced in SlirpConfig version 2 begin
     */
} SlirpConfig;
```

Programmers can set all the fields one by one if they wish. libvdeslirp provides some functions to ease this task.

```C
void vdeslirp_init(SlirpConfig *cfg, int flags);
```

The simplest way to set up a `SlirpConfig` structure is:

```C
SlirpConfig slirpcfg;
vdeslirp_init(&slirpcfg, VDE_INIT_DEFAULT);
```

This provides suitable default values for all the parameters:
```
SLIRP configuration
version       1
ipv4-enable   1
ipv4-network  10.0.2.0
ipv4-netmask  255.255.255.0
ipv4-host     10.0.2.2
ipv6-enabled  1
ipv6-prefix   fd00::
ipv6-preflen  64
ipv6-host     fd00::2
hostname      slirp
tftp-servname (null)
tftp-path     (null)
bootfile      (null)
dhcp-start    10.0.2.15
ipv4-vDNS     10.0.2.3
ipv6-vDNS     fd00::3
vDNS-search
vdomainname   (null)
MTU(0=def)    0
MTU(0=def)    0
disable-lback 0
enable-emu    0
```

Obviously, each field of the structure can be updated to fit the usage needs.

A different approach is to initialize an empty structure and then set the fields one by one.
The following code cleans the slirpcfg structure (just the version field is set to 1.
```C
SlirpConfig slirpcfg;
vdeslirp_init(&slirpcfg, 0);
```

The functions `vdeslirp_setvprefix` and `vdeslirp_setvprefix6` define the netmasks and prefixes for IPv4 and IPv6.
These function are usually called after the redefinition of `vhost` or `vhost6`.
`vdeslirp_setvprefix` redefines the network prefix of `vnetwork`, `vdhcp_start` and `vnameserver` while
`vdeslirp_setvprefix6`  redefines the network prefix for `vprefix_addr6` and `vnameserver6`.

e.g.:
```C
SlirpConfig slirpcfg;
vdeslirp_init(&slirpcfg, VDE_INIT_DEFAULT);
inet_pton(AF_INET,"10.1.1.2", &(slirpcfg.vhost));
vdeslirp_setvprefix(&slirpcfg, 24);
```
redefines the ipv4 addresses as follows:
```
ipv4-network  10.1.1.0
ipv4-netmask  255.255.255.0
ipv4-host     10.1.1.2
dhcp-start    10.1.1.15
ipv4-vDNS     10.1.1.3
```

### After the configuration: usage of slirp.

There is nothing more to add than what have been already said in the *hello sorld* example above.

Start the slirp service:
```C
myslirp = vdeslirp_open(&slirpcfg);
```
send and receive packets (ethernet packets as if it were a tap interface):
```C
n = vdeslirp_send(myslirp, sendbuf, sendlen);
...
n = vdeslirp_recv(myslirp, recvbuf, recvlen);
```

poll/select or similar system calls can be used to wait for new incoming packets,
use the return value of `vdeslirp_fd(myslirp)` as the file descriptor.

at the end:
```C
vdeslirp_close(myslirp);
```

### Port forward

The function `vdeslirp_add_fwd` redirects a UDP or TCP port of the host to a port to a virtual service
connected to the slirp network.

e.g.
```C
in_addr ipv4_any;
in_addr ipv4_host;
inet_pton(AF_INET,"0.0.0.0", &(ipv4_any));
inet_pton(AF_INET,"10.0.2.15", &(ipv4_host));
vdeslirp_add_fwd(myslirp, 0, ipv4_any, 2222, ipv4_host, 22);
```

All the TCP connections addressed to host's port 2222 will be redirected to 10.0.2.15 to port 22.

The function `vdeslirp_remove_fwd` deletes a port forward definition.

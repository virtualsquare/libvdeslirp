<!--
.\" Copyright (C) 2019 VirtualSquare. Project Leader: Renzo Davoli
.\"
.\" This is free documentation; you can redistribute it and/or
.\" modify it under the terms of the GNU General Public License,
.\" as published by the Free Software Foundation, either version 2
.\" of the License, or (at your option) any later version.
.\"
.\" The GNU General Public License's references to "object code"
.\" and "executables" are to be interpreted as the output of any
.\" document formatting or typesetting system, including
.\" intermediate and printed output.
.\"
.\" This manual is distributed in the hope that it will be useful,
.\" but WITHOUT ANY WARRANTY; without even the implied warranty of
.\" MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
.\" GNU General Public License for more details.
.\"
.\" You should have received a copy of the GNU General Public
.\" License along with this manual; if not, write to the Free
.\" Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston,
.\" MA 02110-1301 USA.
.\"
-->

# NAME

vdeslirp_open, vdeslirp_send, vdeslirp_recv, vdeslirp_fd, vdeslirp_close - simple API for slirp

# SYNOPSIS

`#include *libvdeslirp.h*`

`struct vdeslirp *vdeslirp_open(SlirpConfig *`_cfg_`);`

`ssize_t vdeslirp_send(struct vdeslirp *`_slirp_`, const void *`_buf_`, size_t ` _count_`);`

`ssize_t vdeslirp_recv(struct vdeslirp *`_slirp_`, void *`_buf_`, size_t ` _count_`);`

`int vdeslirp_fd(struct vdeslirp *`_slirp_`);`

`int vdeslirp_close(struct vdeslirp *`_slirp_`);`

These functions are provided by libvdeslirp. Link with -lvdeslirp.

# DESCRIPTION

Slirp  is  a TCP/IP emulator. Slirp generates a virtual network using standard
user privileges (no need for root access or CAP_NET_ADMIN). 
This implementation uses libslirp.

  `vdeslirp_open` creates a slirp network.
The `SlirpConfig` structure is defined by libslirp and contains the following fields:

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

  `libvdeslirp` provides helper functions to fill in the fields of this structure, see `libvdeslirpcfg`(3).

Programs using `libvdeslirp` can send and receive packets using `vdeslirp_send`
and `vdeslirp_recv` as if they were  connected to host network (commonly the
Internet) by a NAT/Masquerading router.  `vdeslirp_fd` provides a valid
file descriptor which can be used to  wait  for  incoming packets  (using
select or poll) and `vdeslirp_close` terminates a slirp network created by
`vdeslirp_open`.

# RETURN VALUE

`vdeslirp_open`  returns  the `struct vdeslirp` pointer in case of success. NULL is returned otherwise.
The return value of `vdeslirp_open` is the descriptor that must be passed as first argument to
all the other functions of this man page.
`vdeslirp_send` and `vdeslirp_recv` return the number of bytes sent or received, -1
in case of error.  `vdeslirp_fd` returns a valid file descriptor which can be
used to  wait  for  incoming packets  (using select or poll).  `vdeslirp_close`
returns zero in case of success, -1 in case of error.  In case of failure,
`errno` is set to indicate the type of error.

# SEE ALSO

`libvdeslirpfwd`(3), `libvdeslirpcfg`(3)

# BUGS

Bug reports should be addressed to *info@virtualsquare.org\*

# AUTHOR

VirtualSquare. Project leader: Renzo Davoli.


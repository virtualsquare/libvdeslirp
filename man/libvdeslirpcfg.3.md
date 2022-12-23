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

vdeslirp_init, vdeslirp_setvprefix, vdeslirp_setvprefix6 - simple API for slirp: configuration helpers

# SYNOPSIS

`#include *libvdeslirp.h*`

`#define VDE_INIT_DEFAULT 1`

`void vdeslirp_init(SlirpConfig *`_cfg_`, int ` _flags_`);`

`void vdeslirp_setvprefix(SlirpConfig *`_cfg_`, int ` _prefix_`);`

`void vdeslirp_setvprefix6(SlirpConfig *`_cfg_`, int ` _prefix6_`);`

These functions are provided by libvdeslirp. Link with -lvdeslirp.

# DESCRIPTION

These functions are configuration helpers for `libvdeslirp`(3).
The fields of the SlirpConfig has been described in the `libvdeslirp`(3) manpage.

`vdeslirp_init` clears the `SlirpConfig` configuration structure `cfg` and sets the
version number. If `flags` is set to `VDE_INIT_DEFAULT` then it sets default values to
all the fields of `cfg`. These default values are suitable for most applications.

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
MRU(0=def)    0
disable-lback 0
enable-emu    0
```

The functions `vdeslirp_setvprefix` and `vdeslirp_setvprefix6` define the
netmasks and prefixes for IPv4 and IPv6.  These function are usually called
after the redefinition of `vhost` or `vhost6`.  `vdeslirp_setvprefix` redefines
the network prefix of `vnetwork`, `vdhcp_start` and `vnameserver` while
`vdeslirp_setvprefix6`  redefines the network prefix for `vprefix_addr6` and
`vnameserver6`.

# SEE ALSO

`libvdeslirp`(3)

# BUGS

Bug reports should be addressed to *info@virtualsquare.org\*

# AUTHOR

VirtualSquare. Project leader: Renzo Davoli.


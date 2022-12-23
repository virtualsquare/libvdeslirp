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

vdeslirp_add_fwd, vdeslirp_remove_fwd, vdeslirp_add_unixfwd, vdeslirp_remove_unixfwd, vdeslirp_add_cmdexec - simple API for slirp, port forwarding

# SYNOPSIS

`#include *libvdeslirp.h*`

`int vdeslirp_add_fwd(struct vdeslirp *`_slirp_`, int ` _is_udp_`, struct in_addr ` _host_addr_`, int ` _host_port_`, struct in_addr ` _guest_addr_`, int ` _guest_port_`);`

`int vdeslirp_remove_fwd(struct vdeslirp *`_slirp_`, int ` _is_udp_`, struct in_addr ` _host_addr_`, int ` _host_port_`); `

`int vdeslirp_add_unixfwd(struct vdeslirp *`_slirp_`, char *`_path_`, struct in_addr ` _guest_addr_`, int ` _guest_port_`); `

`int vdeslirp_remove_unixfwd(struct vdeslirp *`_slirp_`, struct in_addr ` _guest_addr_`, int ` _guest_port_`); `

`int vdeslirp_add_cmdexec(struct vdeslirp *`_slirp_`, const char *`_cmdline_`, struct in_addr *`_guest_addr_`, int ` _guest_port_`);`

`int vdeslirp_remove_cmdexec(struct vdeslirp *`_slirp_`, struct in_addr ` _guest_addr_`, int ` _guest_port_`); `

# DESCRIPTION

Slirp, see libvdelirp(3), is a TCP/IP emulator. Slirp generates a virtual
network using standard user privileges (no need for root access of
CAP_NET_ADMIN).  These functions manage port forwarding services.

`vdeslirp_add_fwd`  and  `vdeslirp_remove_fwd`  respectively  add and remove
udp or tcp port forwarding services (depending upon the value of is_udp).
_host_addr_ and _host_port_ are the IP address and port number bound for the
service in  the  host  system.  All  the  connections  or  datagrams to
_host_addr_ and _host_port_ will be diverted to _guest_addr_ and _guest_port_
in the slirp virtual network.

`vdeslirp_add_unixfwd` and `vdeslirp_remove_unixfwd` respectively add and
remove a forwarding service towards a `PF_UNIX` stream  socket on  the  hosting
system.  All the connections from a node of the virtual network to _guest_addr_
and _guest_port_ will be diverted to the `PF_UNIX` bound to the pathname
path. This feature is commonly used to run X-window  clients  in  the  virtual
network (e.g. the value of path could be `/tmp/.X11-unix/X0`).

If libslirp does not support `slirp_add_unix`, `vdeslirp_add_unixfwd` is implemented
by a workaround based on `nc`(1).

`vdeslirp_cmd_fwd` adds a forwarding service to a command. A TCP connection to
_guest_addr_ and _guest_port_ activates the command _cmdline_. Data exchanged
on the TCP connection is forwarded as stdin/stdout to the command.

`vdeslirp_remove_cmdexec` removes a command forwarding service.

# RETURN VALUE

All these functions return 0 in case of success, -1 otherwise (and `errno` is set consequently).
`vdeslirp_remove_cmdexec` and `vdeslirp_remove_unixfwd` return -1 and
set errno to `ENOSYS` if libslirp does not support `slirp_remove_guestfwd`.

# SEE ALSO

`libvdeslirp`(3), `libvdeslirpcfg`(3)

# BUGS

Bug reports should be addressed to *info@virtualsquare.org\*

# AUTHOR

VirtualSquare. Project leader: Renzo Davoli.

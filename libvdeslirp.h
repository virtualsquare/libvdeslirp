#ifndef VDESLIRP_H
#define VDESLIRP_H
#include <slirp/libslirp.h>

struct vdeslirp;

#define VDE_INIT_DEFAULT 1
void vdeslirp_init(struct SlirpConfig *cfg, int flags);

void vdeslirp_setvprefix(struct SlirpConfig *cfg, int prefix);
void vdeslirp_setvprefix6(struct SlirpConfig *cfg, int prefix6);

struct vdeslirp *vdeslirp_open(struct SlirpConfig *cfg);
ssize_t vdeslirp_send(struct vdeslirp *slirp, const void *buf, size_t count);
ssize_t vdeslirp_recv(struct vdeslirp *slirp, void *buf, size_t count);
int vdeslirp_fd(struct vdeslirp *slirp);
int vdeslirp_close(struct vdeslirp *slirp);

int vdeslirp_add_fwd(struct vdeslirp *slirp, int is_udp,
    struct in_addr host_addr, int host_port,
    struct in_addr guest_addr, int guest_port);
int vdeslirp_remove_fwd(struct vdeslirp *slirp, int is_udp,
    struct in_addr host_addr, int host_port);

int vdeslirp_add_unixfwd(struct vdeslirp *slirp,
    struct in_addr guest_addr, int guest_port, char *path);
int vdeslirp_remove_unixfwd(struct vdeslirp *slirp,
    struct in_addr guest_addr, int guest_port);

int vdeslirp_add_cmdexec(struct vdeslirp *slirp, const void *args,
    struct in_addr guest_addr, int guest_port);

#endif

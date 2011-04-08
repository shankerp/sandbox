/*
 *  * Simple `echo' pseudo-device KLD
 *   *
 *    * Murray Stokely
 *     */

#define MIN(a,b) (((a) < (b)) ? (a) : (b))

#include <sys/types.h>
#include <sys/module.h>
#include <sys/systm.h>  /* uprintf */
#include <sys/errno.h>
#include <sys/param.h>  /* defines used in kernel.h */
#include <sys/kernel.h> /* types used in module initialization */
#include <sys/conf.h>   /* cdevsw struct */
#include <sys/uio.h>    /* uio struct */
#include <sys/malloc.h>

#define BUFFERSIZE 256

/* Function prototypes */
d_open_t    echo_open;
d_close_t   echo_close;
d_read_t    echo_read;
d_write_t   echo_write;

/* Character device entry points */
static struct cdevsw echo_cdevsw = {
    echo_open,
    echo_close,
    echo_read,
    echo_write,
    noioctl,
    nopoll,
    nommap,
    nostrategy,
    "echo",
    33,              /* reserved for lkms - /usr/src/sys/conf/majors */
    nodump,
    nopsize,
    D_TTY,
    -1
};

typedef struct s_echo {
    char msg[BUFFERSIZE];
    int len;
} t_echo;

/* vars */
static dev_t sdev;
static int count;
static t_echo *echomsg;

MALLOC_DECLARE(M_ECHOBUF);
MALLOC_DEFINE(M_ECHOBUF, "echobuffer", "buffer for echo module");

/*
 *  * This function is called by the kld[un]load(2) system calls to
 *   * determine what actions to take when a module is loaded or unloaded.
 *    */

static int
echo_loader(struct module *m, int what, void *arg)
{
    int err = 0;

    switch (what) {
    case MOD_LOAD:                /* kldload */
        sdev = make_dev(&echo_cdevsw,
            0,
            UID_ROOT,
            GID_WHEEL,
            0600,
            "echo");
        /* kmalloc memory for use by this driver */
        MALLOC(echomsg, t_echo *, sizeof(t_echo), M_ECHOBUF, M_WAITOK);
        printf("Echo device loaded.\n");
        break;
    case MOD_UNLOAD:
        destroy_dev(sdev);
        FREE(echomsg,M_ECHOBUF);
        printf("Echo device unloaded.\n");
        break;
    default:
        err = EOPNOTSUPP;
        break;
    }
    return(err);
}

int
echo_open(dev_t dev, int oflags, int devtype, struct proc *p)
{
    int err = 0;

    uprintf("Opened device \"echo\" successfully.\n");
    return(err);
}

int
echo_close(dev_t dev, int fflag, int devtype, struct proc *p)
{
    uprintf("Closing device \"echo.\"\n");
    return(0);
}

/*
 *  * The read function just takes the buf that was saved via
 *   * echo_write() and returns it to userland for accessing.
 *    * uio(9)
 *     */

int
echo_read(dev_t dev, struct uio *uio, int ioflag)
{
    int err = 0;
    int amt;

    /*
 *      * How big is this read operation?  Either as big as the user wants,
 *           * or as big as the remaining data
 *                */
    amt = MIN(uio->uio_resid, (echomsg->len - uio->uio_offset > 0) ?
        echomsg->len - uio->uio_offset : 0);
    if ((err = uiomove(echomsg->msg + uio->uio_offset,amt,uio)) != 0) {
        uprintf("uiomove failed!\n");
    }
    return(err);
}

/*
 *  * echo_write takes in a character string and saves it
 *   * to buf for later accessing.
 *    */

int
echo_write(dev_t dev, struct uio *uio, int ioflag)
{
    int err = 0;

    /* Copy the string in from user memory to kernel memory */
    err = copyin(uio->uio_iov->iov_base, echomsg->msg,
        MIN(uio->uio_iov->iov_len, BUFFERSIZE - 1));

    /* Now we need to null terminate, then record the length */
    *(echomsg->msg + MIN(uio->uio_iov->iov_len, BUFFERSIZE - 1)) = 0;
    echomsg->len = MIN(uio->uio_iov->iov_len, BUFFERSIZE);

    if (err != 0) {
        uprintf("Write failed: bad address!\n");
    }
    count++;
    return(err);
}

DEV_MODULE(echo,echo_loader,NULL);

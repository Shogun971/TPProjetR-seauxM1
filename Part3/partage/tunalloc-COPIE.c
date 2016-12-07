#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/ioctl.h>

#include <unistd.h>
#include <fcntl.h>
#include <linux/if.h>
#include <linux/if_tun.h>


#define BUFF_SIZE 1024

int tun_alloc(char *dev)
{
  struct ifreq ifr;
  int fd, err;

  if( (fd = open("/dev/net/tun", O_RDWR)) < 0 ){
    perror("alloc tun");
    exit(1);
  }

  memset(&ifr, 0, sizeof(ifr));

  /* Flags: IFF_TUN   - TUN device (no Ethernet headers)
   *        IFF_TAP   - TAP device
   *
   *        IFF_NO_PI - Do not provide packet information
   */
  ifr.ifr_flags = IFF_TUN|IFF_NO_PI;
  if( *dev )
    strncpy(ifr.ifr_name, dev, IFNAMSIZ);

  if( (err = ioctl(fd, TUNSETIFF, (void *) &ifr)) < 0 ){
    close(fd);
    return err;
  }
  strcpy(dev, ifr.ifr_name);
  return fd;
}

void persist_copy(int src, int dst){
	char buffer[BUFF_SIZE];
	ssize_t done = read(src, buffer, BUFF_SIZE);
	done = write(dst, buffer, BUFF_SIZE);
}

/*int main (int argc, char** argv){
	int tun;
	char buffer[500];
	if(argc <= 1){
		fprintf(stderr,"Need an argument !\n");
		exit(EXIT_FAILURE);
	}
	strcpy(buffer, argv[1]);
	tun = tun_alloc(buffer);
	while(1){
		persist_copy(tun, 1);
	}
  return 0;
}*/

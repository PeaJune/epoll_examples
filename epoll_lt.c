#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/epoll.h>

#define MAX_EVENTS 10

int main()
{
	int nfds = 0;
	int epfd = 0;
	struct epoll_event r_event;
	struct epoll_event wait_events[MAX_EVENTS];
	int ret = 0;
	int i = 0;

	epfd = epoll_create1(0);
	if(epfd < 0)
	{
		printf("epoll create failed.!\n");	
		return epfd;
	}
	r_event.data.fd = fileno(stdin);
	r_event.events = EPOLLIN;/*default is LT mode*/

	ret = epoll_ctl(epfd, EPOLL_CTL_ADD, fileno(stdin), &r_event);
	if(ret < 0)
	{
		printf("add monitor file descriptor failed!\n");
		return ret;
	}

	while(1)
	{
		nfds = epoll_wait(epfd, wait_events, MAX_EVENTS, -1);
		if(nfds < 0)
		{
			printf("epoll wait occur error.\n");
			continue;
		}
		for(i=0; i<nfds; i++)
		{
			if(wait_events[i].data.fd == fileno(stdin))
			{
				printf("read data...\n");
			}
		}
	}

	return 0;
}





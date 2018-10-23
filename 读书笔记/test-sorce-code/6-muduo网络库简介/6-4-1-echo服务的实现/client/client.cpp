#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define ERR_EIXT(m) \
        do \
        {  \
            perror(m); \
            exit(EXIT_FAILURE); \
        } while(0)

#define max(x,y) (x>y?x:y)

struct packet {
    int len;
    char buf[1024];
};

ssize_t readn(int fd, void *buf, size_t count)
{
    size_t nleft = count;
    ssize_t nread;
    char *bufp = (char*) buf;

    while(nleft > 0) {
        if((nread = read(fd, bufp, nleft)) < 0) {
            if(errno == EINTR)  //EINTR baio shi zhu se cao zuo
                continue;
            return -1;
        } else if(nread == 0)
            return count - nleft;
        bufp += nread;
        nleft -= nread;
    }

    return count;
}

ssize_t writen(int fd, const void *buf, size_t count)
{
    size_t nleft = count;
    ssize_t nwritten;
    char *bufp = (char*) buf;

    while(nleft > 0) {
        if((nwritten = write(fd, bufp, nleft)) < 0) {
            if(errno == EINTR)
                continue;
            return -1;
        } else if(nwritten == 0)
            return count - nleft;
        bufp += nwritten;
        nleft -= nwritten;
    }

    return count;
}

ssize_t recv_peek(int sockfd, void *buf, size_t len)
{
    while(1) {
        int ret = recv(sockfd, buf, len, MSG_PEEK);
        if(ret == -1 && errno == EINTR) continue;

        return ret;
    }
}

ssize_t readline(int sockfd, void *buf, size_t maxline)
{
    int ret;
    int nread;
    char *bufp = static_cast<char *>(buf);
    int nleft = maxline;

    while(1) {
        ret = recv_peek(sockfd, bufp, nleft);
        if(ret < 0) return ret;
        else if(ret == 0) return ret;
        nread = ret;
        int i;
        for(i = 0; i < nread; ++i) {
            if(bufp[i] == '\n') {
                ret = readn(sockfd, bufp, i+1);
                if(ret != i+1)
                    ERR_EIXT("readn failed");
                return ret;
            }
        }
        if(nread > nleft) exit(EXIT_FAILURE);
        nleft -= nread;
        ret = readn(sockfd, bufp, nread);
        if(ret != nread)
            ERR_EIXT("readn failed");
        bufp += nread;
    }

    return -1;
}

void echo_cli(int sock)
{
    fd_set rset;
    FD_ZERO(&rset);

    int nready;
    int fd_stdin = fileno(stdin);   //STD_FILENO == 0
    int maxfd = max(fd_stdin, sock);

    char sendbuf[1024] = {0};
    char recvbuf[1024] = {0};

    int stdineof = 0;
    while(1) {
        if(stdineof == 0)
            FD_SET(fd_stdin, &rset);
        FD_SET(sock, &rset);
        nready = select(maxfd+1, &rset, NULL, NULL, NULL);
        if(nready == -1) ERR_EIXT("select");
        if(nready == 0) continue;
        if(FD_ISSET(sock, &rset)) {
            int ret = readline(sock, recvbuf, sizeof(recvbuf)); //conn是已连接套接字, 是主动套接字
            if(ret == -1) ERR_EIXT("read failed");
            else if(ret == 0) {
                printf("server close\n");
                break;
            } 
            fputs(recvbuf, stdout);
            memset(recvbuf, 0, sizeof(recvbuf));
        }
        if(FD_ISSET(fd_stdin, &rset)) {
            if(fgets(sendbuf, sizeof(sendbuf), stdin) == NULL) {
                stdineof = 1;
                shutdown(sock, SHUT_WR);
            } else {
                writen(sock, sendbuf, strlen(sendbuf));
                memset(sendbuf, 0, sizeof(sendbuf));
            }
        }
    }

    // close(sock);
}

int main(int argc, char const *argv[])
{
    int sock;
    if((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0 )
        ERR_EIXT("socket failed");

    struct  sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(2007);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);   //INADDR_ANY表示本机的任意地址, 网络字节序
    // servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); //显示指定本机的IP地址
    // inet_aton("127.0.0.1", &servaddr.sin_addr)
    if(connect(sock, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
        ERR_EIXT("connect failed");

    echo_cli(sock);

    return 0;
}
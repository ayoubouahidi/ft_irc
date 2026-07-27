Initially
---------
Monitor:
EPOLLIN

        |
        v

Need to send message
--------------------
send()

        |
        +---- all sent
        |         |
        |         v
        |      stay on EPOLLIN
        |
        +---- partial/EAGAIN
                  |
                  v
          store in writeBuffer
          enable EPOLLOUT

                  |
                  v

epoll_wait()
returns EPOLLOUT

                  |
                  v

flushWriteBuffer()

        |
        +---- buffer still has data
        |         |
        |         v
        |   keep EPOLLOUT enabled
        |
        +---- buffer becomes empty
                  |
                  v
          disable EPOLLOUT
          back to EPOLLIN only
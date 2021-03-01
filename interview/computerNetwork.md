### tcp如何保证有序, 不丢失,不重复

> 发送方每次发送数据时,tcp给每个数据包分配一个序列号(发送方把已发送的数据包保留的缓冲区中),在略大于RTT的时间内等待接收方发送回来的序列号ACK进行确认,若没有收到ACK发送法就会重传数据包,若收到确认则释放该数据包占用的缓冲区. 
>
> 接收方收到数据包后验证校验和,若不正确则丢弃包等待超时重传过来的数据包.利用序列号保证接受数据的顺序.
>
> 接受放对比接受缓存区和数据的序列号,若发现有重复数据则将数据丢弃,并将需要请求的数据序列号做为确认号返回
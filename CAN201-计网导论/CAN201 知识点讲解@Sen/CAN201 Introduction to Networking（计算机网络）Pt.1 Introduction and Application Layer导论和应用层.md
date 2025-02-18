- [1.Introduction](#1introduction)
  - [1.1 What is the network(什么是网络）](#11-what-is-the-network什么是网络)
  - [1.2 How does the network work（网络如何工作）](#12-how-does-the-network-work网络如何工作)
    - [1.2.1 Physical media/physical medium（物理媒体/物理介质）](#121-physical-mediaphysical-medium物理媒体物理介质)
      - [1.2.1.1 Guided media（导引型媒体）](#1211-guided-media导引型媒体)
      - [1.2.1.2 Unguided media（非导引型媒体）](#1212-unguided-media非导引型媒体)
    - [1.2.2 Different methods to accessed the Internet（不同的接入网络的方法）](#122-different-methods-to-accessed-the-internet不同的接入网络的方法)
      - [1.2.2.1 Dial-up Interenet access（PSTN）（拨号上网）](#1221-dial-up-interenet-accesspstn拨号上网)
      - [1.2.2.2 Digital subscriber line（DSL）（数字用户线路）](#1222-digital-subscriber-linedsl数字用户线路)
      - [1.2.2.3 Hybrid fiber coax（HFC）（混合光纤同轴电缆）](#1223-hybrid-fiber-coaxhfc混合光纤同轴电缆)
      - [1.2.2.4 Fiber to the home（FTTH）（光纤到户）](#1224-fiber-to-the-homeftth光纤到户)
      - [1.2.2.5 Wireless access networks（无线接入网络）](#1225-wireless-access-networks无线接入网络)
    - [1.2.3 How to deliver the data via the Internet（如何通过网络传输信息）](#123-how-to-deliver-the-data-via-the-internet如何通过网络传输信息)
      - [1.2.3.1 Protocols（协议）](#1231-protocols协议)
      - [1.2.3.2 Current Internet structure（当前互联网结构）](#1232-current-internet-structure当前互联网结构)
      - [1.2.3.3 Internet protocol stack（互联网协议栈）](#1233-internet-protocol-stack互联网协议栈)
  - [1.3 How to evaluate the performance（如何评估网络的表现）](#13-how-to-evaluate-the-performance如何评估网络的表现)
    - [1.3.1 Delay（延迟）](#131-delay延迟)
    - [1.3.2 Packet loss（丢包率）](#132-packet-loss丢包率)
    - [1.3.3 Throughput（吞吐量）](#133-throughput吞吐量)
- [2. Application Layer（应用层）](#2-application-layer应用层)
  - [2.1 Introduction to Application Layer](#21-introduction-to-application-layer)
  - [2.2 Principles of Network Applications（网络应用原理）](#22-principles-of-network-applications网络应用原理)
    - [2.2.1 Sockets（套接字）](#221-sockets套接字)
    - [2.2.2 Identifier（标识符）](#222-identifier标识符)
    - [2.2.3 Architectures for applications（应用的架构）](#223-architectures-for-applications应用的架构)
      - [2.2.3.1 Client-server（客户端-服务器架构）](#2231-client-server客户端-服务器架构)
      - [2.2.3.2 Peer-to-peer（P2P，对等网络架构）](#2232-peer-to-peerp2p对等网络架构)
    - [2.2.4 Application-layer protocol defines（应用层协议的定义）](#224-application-layer-protocol-defines应用层协议的定义)
    - [2.2.5 Transport service requirements（传输服务的需求）](#225-transport-service-requirements传输服务的需求)
      - [2.2.5.1 Internet transport protocols services（互联网传输协议服务）](#2251-internet-transport-protocols-services互联网传输协议服务)
  - [2.3 Web Application](#23-web-application)
    - [2.3.1 HTTP 1.1](#231-http-11)
      - [2.3.1.1 HTTP general request format（HTTP请求信息的通用格式）](#2311-http-general-request-formathttp请求信息的通用格式)
      - [2.3.1.2 HTTP request method（HTTP请求方法）](#2312-http-request-methodhttp请求方法)
      - [2.3.1.3 HTTP request headers（HTTP请求头部）](#2313-http-request-headershttp请求头部)
      - [2.3.1.4 HTTP response message format（HTTP响应信息的格式）](#2314-http-response-message-formathttp响应信息的格式)
    - [2.3.2 Cookies](#232-cookies)
    - [2.3.3 Web caches（Web缓存）](#233-web-cachesweb缓存)
    - [2.3.4 RESTful API](#234-restful-api)
    - [2.3.5 HTTP/2](#235-http2)
    - [2.3.6 HTTP/3](#236-http3)
  - [2.4 DNS （Domain Name System，域名系统）](#24-dns-domain-name-system域名系统)
    - [2.4.1 A distributed, hierarchical database（一个分布式和分层数据库结构）](#241-a-distributed-hierarchical-database一个分布式和分层数据库结构)
    - [2.4.2 Iterated query and Recursive query（迭代查询和递归查询）](#242-iterated-query-and-recursive-query迭代查询和递归查询)
    - [2.4.3 Caching, Updating records（缓存和记录更新）](#243-caching-updating-records缓存和记录更新)
    - [2.4.4 DNS protocol，messages](#244-dns-protocolmessages)
  - [2.4 P2P Applications](#24-p2p-applications)
    - [2.4.1 Pure P2P architecture（纯P2P架构）](#241-pure-p2p-architecture纯p2p架构)
    - [2.4.2 BitTorrent](#242-bittorrent)
  - [2.5 Socket Programming](#25-socket-programming)

# 1.Introduction
## 1.1 What is the network(什么是网络）
因特网是一个世界范围内的计算机网络，它是一个互联了遍及全世界数十亿计算设备的网络。它为参与者提供了沟通和连接的手段。
参与者可能是设备也可以是服务。这些设备包括传统的PC、服务器等，也包括如今的智能手机、平板、手表、汽车、温度调节装置等）。服务包括Web服务、电子邮件服务、域名解析服务等。

## 1.2 How does the network work（网络如何工作）
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/05e9ded144a9465ca97cb4294a5cfb23.png)
网络通过相应的介质来传输数据，在特定的网络架构下采用相应的方法进行传输的。不同的介质和网络架构可能需要采用不同的传输方法，以实现有效的数据传输和通信。
网络的构成可以描述为：用户连接到ISP（互联网服务提供商）的网络，数据经过ISP的网络中的节点进行传输，最终到达目标主机（host）。
### 1.2.1 Physical media/physical medium（物理媒体/物理介质）
物理媒体/物理介质可以分为两种类型：
1.Guided media（导引型媒体），电波沿着固体媒体前行，如Twisted pair（双绞铜线）、Coaxial cable（同轴电缆）、Fiber optic cable（光纤电缆）等
2.Unguided media（非导引型媒体），电波在空气或外层空间中传播，例如无线局域网或数字卫星频道等。无线电波可以在空气中自由传播，这是无线通信中的一种常见特征。

#### 1.2.1.1 Guided media（导引型媒体）
1.Twisted pair（TP）（双绞线）
一种常见的有线传输介质，由两根绝缘的铜线组成。Category 5规格可以支持最高传输速率为100 Mbps（百兆以太网）和1 Gbps（千兆以太网）的以太网。
Category 6规格支持最高传输速率为10 Gbps（万兆以太网）的以太网。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/72e337eeb46d47b68fd35dd539e593dc.png)


2.Coaxial cable（同轴电缆）
由两个同心的铜导体构成，可以进行双向传输，用于宽带传输，比如HFC（Hybrid Fiber-Coax）网络。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/6aaf345c5c444750b246810d5f392ba4.png)

3.Fiber optic cable（光纤电缆）
使用玻璃纤维来传输光脉冲（每个脉冲代表一个bit），可以实现高速的点对点传输（10-100 Gbps的传输速度），具有较低的误码率（光纤传输系统中使用的repeaters（中继器）可以被放置得比较远）和良好的抗电磁干扰能力。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/e613717e1e074de68cf2519c3a0a319b.png)
#### 1.2.1.2 Unguided media（非导引型媒体）
使用无线电波作为信号传输的物理媒体便可以不需要无力的导线而是通过电磁波进行传输。
无线通信是双向的。
但是无限传播受周围传播环境的影响，如信号的反射、物体的遮挡以及干扰等。
应用有：Wireless Lan（无线局域网）如WiFi，54 Mbps – 9.6Gbps
Wide-area（广域无线网）如cellular（蜂窝网络），4G：100 Mbps
5G：1Gbps
Satellite（卫星通信）每个频道45Mbps，大约270msec的端到端延迟

### 1.2.2 Different methods to accessed the Internet（不同的接入网络的方法）
#### 1.2.2.1 Dial-up Interenet access（PSTN）（拨号上网）
拨号上网是一种使用公共交换电话网（PSTN）设施来与互联网服务提供商（ISP）建立连接的方式。用户通过拨打传统电话线路上的电话号码，使用调制解调器（modem）将音频信号转换成数据发送给路由器或计算机，同时将来自这些设备的信号编码后发送到另一个调制解调器。这种方式允许用户通过普通电话线路接入互联网。
但是带宽相对较低，每秒传输的数据量为56Kbs。

#### 1.2.2.2 Digital subscriber line（DSL）（数字用户线路）
DSL信号传输到中央局的DSL接入复用器（DSLAM），数据通过DSL电话线进入互联网，而语音信号则可以继续传输到电话网络。
一般用户对下载的需求大于上传的需求，因此这里一般会使用ADSL（Asymmetric Digital Subscriber Line， 非对称数字用户线路），上行和下行传输速率不对称，下行传输速率通常要高于上行传输速率。一般上行速率小于1Mbps，而下行速率一般小于10Mbps。

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/c68f5eb8fca64cda878811558fb5f1d6.png)


如何实现语音信号和数据同时传输的呢？
使用了Frequency division multiplexing (FDM)（频分复用）技术，将电话线的频谱分成多个频段，其中一部分用于传输数据，另一部分用于传输语音信号。这样就实现了在同一条电话线上同时传输数据和语音，而且它们之间不会相互干扰。

#### 1.2.2.3 Hybrid fiber coax（HFC）（混合光纤同轴电缆）
使用光纤和同轴电缆结合的网络架构，光纤用于传输信号到各个节点，然后通过同轴电缆将信号传送到用户家庭。
因此由于光纤的传输距离较长，它可以支持更长的传输距离。也可以提供更高的带宽，但依旧是ADSL，上行2Mbps，下行30Mbps。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/12485954ee1d43d2b3f499419a117f32.png)

#### 1.2.2.4 Fiber to the home（FTTH）（光纤到户）
使用the passive optical networks（PONs）（被动光网络）分布架构。将光信号从中心局传输到多个用户。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/f513e33bcca74cc88fd8d1ba88e90352.png)
#### 1.2.2.5 Wireless access networks（无线接入网络）
需要使用Base Stations（基站）提供信号。
应用包括Wireless Lans、Wide-area wireless 、 Li-Fi、 STARLINK

### 1.2.3 How to deliver the data via the Internet（如何通过网络传输信息）
网络的边界是Host（主机），主机包括Clients（客户端）和Servers（服务器）。其中Clients（客户端）包含PC、智能手机等，他们接受、发送和处理网络数据。Servers（服务器）通常位于数据中心中，提供各种网络服务。连接客户端设备和服务器到网络的物理通信介质，可以是有线的或者无线的通信链路。

网络核心是连接整个网络的主干部分。网络核心承载着大量的数据流量，负责在不同的边缘网络之间进行数据交换和传输。在网络核心中，通常会有大型的路由器、交换机和其他网络设备，用于实现数据的高效传输和路由。其中路由器负责传输数据包并决定数据包的转发路径。
Mesh of interconnected routers（互连路由器的网状结构）：计算机网络中的路由器之间形成的网状连接结构，每个路由器都与其他路由器相连，以便在网络中进行数据传输和路由。
Packet-switching（分组交换）：主机将应用层消息break（分割）成小的packet（数据包），这些packet（数据包）在网络中被独立传输。packet（数据包）在路由器之间通过交换转发，沿着从源到目的地的路径传输。
Routing（路由）和Forwarding（转发）是计算机网络的两个核心功能。Routing（路由）：确定数据包从源到目的地所采取的路径。Forwarding（转发）：将数据包从路由器的输入端口移动到适当的输出端口。路由器的不同端口会与其他路由器的端口进行长期连接，以构建一个网络中的路由路径。这些连接可以是物理连接，比如通过网线或光纤。也可以是逻辑连接，比如通过虚拟专用网络（VPN）或者其他网络协议来实现。这些连接的建立和维护是为了确保路由器之间能够相互通信和交换路由信息，以便确定最佳的数据包传输路径。通过这些连接，路由器可以交换路由信息、更新路由表、协商最佳路径等，从而实现数据包的正确转发和路由。
这些路由器之间的连接都属于网络层，网络层负责数据包的路由、转发和网络间通信，以确保数据能够在不同的网络之间传输和交换。
我们再详细介绍一下Packet-switching（分组交换）中的过程——store and forward（存储转发），整个数据包必须先到达路由器，然后才能被转发到下一个链路。这意味着数据包必须先完全存储在路由器的缓冲区中，然后再被转发到下一个节点。
假设我们的带宽为$R$ bps（传输速率$R$ bps），而传输的数据包的长度为$L$，那么Transmission Delay（传输延迟）为$L/R$ s。End-to-End Delay（端到端延迟）：在零传播延迟的情况下，端到端延迟为 $2L/R$。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/7f7b3630611742fb86c2d763c96e2019.png)
One-hop Transmission Delay（一跳传输延迟）: 以一个跳（一个路由器到另一个路由器）为例，数据包长度（$L$）和传输速率（$R$），传输延迟为$L/R$s。
存储转发中，数据包必须先完全存储在路由器的缓冲区中，因此可能存在由于无法及时将路由器里缓冲区里的数据包全部转发出去而缓冲区里的数据包一直在增加的情况，也就是到达链路的数据包的速率（即到达率）超过了链路的传输速率时，就会导致：
1.数据包排队等待传输：余的数据包将会在链路上排队等待传输。这会导致数据包在缓冲区中积压，等待机会被传输出去。
2.数据包丢失：如果缓冲区的内存空间不足以容纳所有排队等待传输的数据包，当内存（缓冲区）已满时，新到达的数据包将会被dropped（丢弃）/lost（丢失），这可能会导致数据丢失和传输错误。

Circuit switching（电路交换）：在通信开始之前会建立一条专用的通信路径（即电路），并且在通信过程中保持这条路径的连通性。在通信过程中，这条电路将会一直被保留并且独占，当没有被用于传输数据的时候其状态就是空闲的。传统的电话网络就是一个典型的电路交换网络。
在电路交换中有两种常见的多路复用技术：FDM和TDM
FDM：Frequency Division Multiplexing（频分多路复用），将多个信号通过不同的频率进行复用，每个通信连接被分配一个不同的频率带宽，这些频率带宽互不重叠，因此它们可以共存于同一传输介质中。在接收端，通过对不同频率进行解调，可以将各个信号分离出来。常用于传统的模拟电路交换系统中。
TDM：Time Division Multiplexing（时分多路复用），将多个信号通过时间片进行复用，每个通信连接被分配一个时间片，不同的通信连接轮流占用传输介质的时间。这样，多个通信连接可以共享同一传输介质，每个连接在自己的时间片内进行传输。在接收端，通过对时间片进行解析，可以将各个信号分离出来。TDM常常用于数字电路交换系统中。
分组交换允许更多用户同时使用网络，因为它能够更高效地利用网络资源，分组交换中不同用户的多个数据包可以同时共享网络资源，而电路交换中，会因为没有数据传输而导致空闲从而对网络资源的利用较低。
在分组交换中，多个用户可以共享同一条传输线路，因此在35个用户中同时超过10个用户使用的概率可以使用排列组合进行计算：$\sum_{i=11}^{35} C_{35}^ip^i(1-p)^{35-i}=0.0004$
当然当用户越大于35，这个概率会越来越大。

与电路交换相比，分组交换
优势：
1.资源共享：分组交换允许多个用户共享网络资源，这样可以更有效地利用带宽和设备。
2.简化：分组交换相比电路交换更简单，不需要进行通话建立的过程，因此更灵活和高效。
劣势：
1.过度拥塞可能：在分组交换网络中，由于数据包竞争网络资源，可能会导致过度拥塞，进而引起延迟和丢包。
2.需要可靠数据传输和拥塞控制的协议：为了保证数据传输的可靠性和网络的稳定性，需要使用一些协议和机制来进行拥塞控制和数据传输的可靠性保障。

如何实现类似电路交换的行为：
1.带宽保证：可以通过为特定的数据流分配固定的带宽来实现类似电路交换的行为，这样可以保证这些数据流的传输质量和稳定性。
2.开发新方法：为了更好地实现类似电路交换的行为，需要开发新的技术和方法，以满足特定应用场景的需求，例如实时音视频通信等。

#### 1.2.3.1 Protocols（协议）
协议定义了网络实体之间发送和接收消息的format（格式）和order（顺序），以及在消息传输和接收过程中采取的行动。换句话说，协议规定了网络设备之间如何进行通信和交互。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/8ef963bff42d430c8c07a754976fda69.png)
#### 1.2.3.2 Current Internet structure（当前互联网结构）
终端系统是通过接入互联网服务提供商（ISP）连接到互联网的，这些ISP包括居民、公司和大学的ISP。接入ISP需要相互连接，以便任意两台主机可以相互发送数据包，这样形成的网络结构非常复杂。互联网的发展是由经济和国家政策推动的。
由于连接所以ISP是不现实的，因此我们将每个access ISP（接入ISP）连接到一个global transit ISP（全球性的传输ISP）。这些全球性的传输ISP通常被称为骨干网（Backbone Network）。客户ISP和提供商ISP之间存在经济协议，客户ISP向提供商ISP支付费用以获取连接和接入全球互联网基础设施的权限，而提供商ISP则负责将数据包传递到客户网络并提供各种服务。当然只有一个全球ISP的方案不够好，我们可以把它拆成多个部分，这样可以更好处理和分发全球范围内的网络流量，更好地满足特定地区地需求，也更容易管理和监管，并且也可以避免单点故障地风险，提高网络的安全性和可靠性。在此基础上，通过IXP（Internet Exchange Point，互联网交换点），ISP相互连接和交换数据流量，提高互联网的效率和可靠性。而在ISP和access net（接入网络）中间还可以有一层regional net（区域性网络）这些网络可以是由政府、企业、学术机构或其他实体建立的，旨在为特定地区的用户提供连接和服务。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/ba167f699b00428c9f0c9a9da7740270.png)
下图所示的是一个更偏向我们生活的网络组成
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/fad69b7157b94f4696aa20694e34f771.png)
其中Tier-1 ISP是指全球范围内拥有大规模网络覆盖的ISP，如中国电信、Sprint、AT&T、NTT等。它们通常具有国家和国际范围的网络覆盖能力。
而Google是内容提供商网络，这是指像谷歌这样的内容提供商所拥有的私有网络，用于连接其数据中心到互联网，通常绕过Tier-1商业ISP和区域性ISP。

#### 1.2.3.3 Internet protocol stack（互联网协议栈）
应用层（application）：支持网络应用程序的运行，如FTP（文件传输协议）、SMTP（简单邮件传输协议）、HTTP（超文本传输协议）等。
传输层（transport）：负责进程之间的数据传输，常见的协议有TCP（传输控制协议）和UDP（用户数据报协议）。
网络层（network）：负责数据报文从源到目的地的路由传输，主要协议是IP（互联网协议）以及路由协议。
链路层（link）：负责相邻网络元素之间的数据传输，常见的协议包括Ethernet（以太网）、802.11（WiFi）、PPP（点对点协议）等。
物理层（physical）：负责在传输介质上传输比特，即将数据转化为物理信号进行传输。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/11cc449a9bd640dea750ce613f32630f.png)
SO/OSI参考模型是国际标准化组织（ISO）和开放系统互联（OSI）组织定义的一种网络协议层次结构，用于描述计算机网络中不同层级的功能和交互。该模型包括七个层级，从物理层到应用层，分别是物理层、数据链路层、网络层、传输层、会话层、表示层和应用层。
表示层（presentation）：负责让应用程序能够解释数据的含义，例如加密、压缩以及特定机器的约定。
会话层（session）：负责数据交换的同步、检查点和数据交换的恢复。
该模型指出互联网协议栈中缺少这两个层级，因此如果需要这些功能，就必须在应用层中实现。因此，对于ISO/OSI参考模型中的表示层和会话层提供的服务，如果在互联网协议栈中需要的话，就需要在应用层中进行实现。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/c510553afb8c43e8a3c3e2bebf282ae1.png)
下图是描述网络中数据传输的过程。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/59b121b2992f40448283f83d8f3415f2.png)
Message（消息）: 在应用层，指的是用户数据或应用程序数据单元。在网络通信中，消息是应用程序要发送或接收的数据单元。
Segment（分段）: 在传输层，指的是在数据传输过程中将消息分割成更小的单元以便传输的过程。TCP协议就会将消息分割成多个段进行传输。
Datagram（数据报）: 在网络层，指的是在网络上通过不同的路径传输的数据单元。IP协议中使用数据报进行数据传输。
Frame（帧）: 在数据链路层，指的是将数据报封装成帧，加上帧头和帧尾等控制信息，以便在物理层上传输。例如，在以太网中，数据报会被封装成以太网帧进行传输。

通过分层，将整个系统分解为多个相互关联但相对独立的层级，每个层级负责特定的功能。这样做有助于降低系统的复杂性，使得系统更易于理解和管理。

## 1.3 How to evaluate the performance（如何评估网络的表现）
三个指标：Package Loss（丢包率）、Delay（延迟）、Bandwidth（带宽）。
丢包和延迟发生是因为数据包到达packet arrival rate（路由器的速率）暂时超过了output link capacity（输出链路的容量）时，就会出现数据包排队的情况，这种情况导致一些数据包在路由器的缓冲区中等待传输。这是延迟的一方面，如果这种情况一直发生，导致排队的数据包超出了路由器的free buffers（空闲缓冲区）时，这些数据包就无法被储存下来，这些数据包就会被丢弃，从而出现丢包率。

### 1.3.1 Delay（延迟）
延迟有四部分组成
表达式为：$d_{nodal} = d_{proc} + d_{queue} + d_{trans} + d_{prop}$
$d_{proc}$是数据包在节点内部处理的延迟，包括路由器或交换机对数据包进行处理，包括检查比特错误（check bit errors）和确定输出链路（determine output link）。这些处理过程通常需要的时间非常短，通常在毫秒级别以下。
$d_{queue}$是数据包在输出链路等待传输的时间延迟,当数据包到达路由器的输出队列时，如果输出链路繁忙或者缓冲区已满，数据包就需要在输出队列中等待传输,这个等待传输的时间延迟就是队列延迟（queueing delay），这个延迟的长短取决于路由器的拥塞程度，如果路由器的输出链路非常繁忙，那么数据包在队列中等待的时间就会更长。
$d_{trans}$是数据包在传输链路上传输所需的时间延迟，取决于数据包的长度和链路的带宽。公式为$d_{trans}=L/R$，其中$L$代表数据包的长度，$R$代表链路的带宽。
$d_{prop}$是数据包在传播介质上传播所需的时间延迟，取决于传播介质的长度和传播速度。公式为$d_{prop}=d/s$，其中$d$代表物理链路的长度，$s$代表传播速度。
Traffic intensity（流量强度）能反映Queueing delay（排队延迟），其中流量强度的公式为：$La/R$，其中$R$是带宽，$L$是每个数据包的长度，$a$是平均数据包到达速率。
当$La/R$接近0时，表示平均排队延迟很小，即数据包能够很快地得到传输。
当$La/R$接近于 1 时，表示平均排队延迟变得很大，即数据包需要在队列中等待较长时间才能得到传输。
当$La/R$大于 1 时，表示有更多的数据包到达而无法被及时传输，这会导致平均延迟变得无限大。

### 1.3.2 Packet loss（丢包率）
当一个数据包到达一个已经满了的缓冲区（队列）时，它会被丢弃，也就是说，它会被丢失。这种情况通常发生在网络中的路由器或交换机等设备上，当缓冲区已满无法容纳更多数据包时，新到达的数据包就会被丢弃。
丢失的数据包可能会由之前的节点进行重传，也有可能由源端系统进行重传，或者干脆不进行重传。重传的目的是为了确保数据的可靠传输，尽管丢失的数据包会带来一定的性能损失和网络负担，但重传可以帮助恢复丢失的数据包，确保数据的完整性和可靠性。

### 1.3.3 Throughput（吞吐量）
在发送方和接收方之间传输比特的速率（比特/时间单位）。它可以用来衡量网络或通信系统的性能和效率。
吞吐量可以分为两种：
1.instantaneous throughput（瞬时吞吐量）：指在某一时刻的传输速率，它反映了当前的传输性能。
2.average throughput（平均吞吐量）：指在较长时间段内的平均传输速率，它可以更好地反映系统的整体性能。平均吞吐量的计算可以涉及到一段时间内传输的总比特数，除以这段时间的长度来得到平均速率。
在整个数据传输路径中，存在一个特定的链路，它成为了限制数据从发送端到接收端传输速率的瓶颈。换句话说一个传输路径中的吞吐量由最小的传输速度决定。
在一般的场景中，端到端吞吐量被限制为$R_c,R_s,R$中的最小值，其中$R_c$代表发送端的发送速率，$R_s$代表接收端的接收速率，$R$代表链路的带宽。一般$R_c$和$R_s$是此时的瓶颈。

# 2. Application Layer（应用层）
## 2.1 Introduction to Application Layer
应用层是TCP/IP协议栈的最顶层，是最接近用户的一层。
它提供了各种各样的网络协议以支持用户在网络上进行数据Transmit（发送）和Receive（接受）。它还提供了各种各样的网络应用程序。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/11cc449a9bd640dea750ce613f32630f.png)
应用层提供了大量的协议，如图所示。
HTTP (HyperText Transfer Protocol) - 用于从服务器传输超文本到本地浏览器的传输协议。
WebSocket - 提供全双工通信渠道，允许服务器主动向客户端发送数据。
WebRTC (Web Real-Time Communication) - 允许网页浏览器进行实时通信，如视频、音频和数据共享。
MQTT (Message Queuing Telemetry Transport) - 轻量级的消息传输协议，适用于低带宽、高延迟或不可靠的网络环境。
AMQP (Advanced Message Queuing Protocol) - 用于在分布式系统中进行消息队列通信的协议。
SMTP (Simple Mail Transfer Protocol) - 用于发送电子邮件的协议。
IMAP (Internet Message Access Protocol) - 用于从邮件服务器检索电子邮件的协议。
POP3 (Post Office Protocol version 3) - 用于从邮件服务器下载电子邮件的协议。
FTP (File Transfer Protocol) - 用于在网络上进行文件传输的协议。
SSH (Secure Shell) - 提供加密的网络服务，用于远程登录和其他安全网络服务。
RPC (Remote Procedure Call) - 允许一个程序调用另一个程序的函数或过程，而不需要了解底层网络技术。![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/8095b4316f5d4becb715843078bb1674.png)
应用层可以轻松定制，这意味着不同的设备可以进行不同的定制，以满足特定设备的需求和功能。

## 2.2 Principles of Network Applications（网络应用原理）
在TCP/IP协议栈的网络中一般使用socket（套接字）作为应用程序和网络之间的接口，每个程序都有一个identifier（标识符，通常是IP地址和端口号）和一组protocols（协议，规定了数据如何在网络中传输）。然后程序通过socket（套接字）与网络连接。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/072687dedd354987818c245e293deccf.png)
### 2.2.1 Sockets（套接字）
进程通过它的套接字发送和接收消息。
套接字类似于门，允许进程将消息推送出去，就像将消息从门里推出去一样。发送进程依赖于另一侧门后面的传输基础设施将消息传递给接收进程的套接字。
下图展示它们之间的关系，应用层的程序负责实现特定的网络应用。网络层包括传输层、网络层、链路层和物理层，它们由操作系统控制和管理。传输层负责在网络中的数据传输，网络层负责数据包的路由和转发，链路层负责物理介质上的数据传输，物理层负责传输介质的物理特性。套接字作为应用层与传输层之间的接口，允许应用程序与网络进行数据交换和通信。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/dab212a8ee4a4d45a46e2e413c024fb3.png)
### 2.2.2 Identifier（标识符）
进程需要一个标识符，这样可以确保网络上的数据包能够准确地传递到指定的进程。
主机设备有唯一的32位IPv4地址和/或128位IPv6地址。
IPv4是在上个世纪70年代开发的，当时互联网还处于早期阶段。IPv4采用32位地址，最多可以容纳约42亿个不同的IP地址。然而，随着互联网的迅速发展，IP地址的需求迅速增长，导致IPv4地址空间逐渐枯竭。为了解决IPv4地址空间不足的问题，IPv6应运而生。IPv6采用128位地址，这意味着它提供了远远超过IPv4的地址空间，几乎可以满足任何规模的互联网需求。
下面给出一个IPv4和IPv6地址与端口号的示例：
IPv4:port         192.168.1.100:80 这表示IPv4地址为192.168.1.100，端口号为80。
IPv6:port         [240e:3a1:4cb1:69d0:f40c:4269:74a2:7ea3]:80这表示IPv6地址为240e:3a1:4cb1:69d0:f40c:4269:74a2:7ea3，端口号为80。IPv6地址用方括号括起来，以便清楚地将地址与端口号区分开来。其实我们可以发现地址和端口号用":"分割，而IPv4地址由4组8位的十进制数构成，每组之间使用点号"."进行分割，所以地址和端口号的分割不会混淆。但是IPv6地址由8组16位的十六进制数构成，每组之间使用冒号":"进行分割，所以需要用方括号将地址括起来以清楚分割。

### 2.2.3 Architectures for applications（应用的架构）
#### 2.2.3.1 Client-server（客户端-服务器架构）
Server（服务器）：
服务器是一台始终处于开机状态的主机，具有永久的IP地址。它通常具有高性能和分布式计算能力，用于提供各种服务。
服务器进程会一直处于Listen（监听状态），等待客户端的连接请求。
Client（客户端）：
客户端是连接到服务器获取服务的主机。它们可能是intermittently（间断性地）连接到互联网，通常具有动态IP地址。
客户端不会直接与其他客户端进行通信，而是通过与服务器建立连接来获取所需的服务。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/ab84bc67b5c2498a9dba9b54d658ed6a.png)
因此在这种架构下可以通过一下几种方式区分服务器和客户端：
1.服务器通常具有永久的IP地址，而客户端可能具有动态IP地址。
2.服务器进程通常会一直处于监听状态，等待客户端的连接请求。而客户端通常是通过发起连接来获取服务，而不是一直处于监听状态。
3.服务器通常会监听特定的端口，而客户端会使用选择一个未被占用的端口作为源端口发送请求与服务器进行通信。
4.服务器通常具有提供服务的能力，如网站托管、数据库访问、文件存储等，而客户端通常是获取这些服务的一方。
#### 2.2.3.2 Peer-to-peer（P2P，对等网络架构）
端系统直接交换数据，不需要始终开启的中心服务器。
客户端和服务器进程可以在同一主机上运行。
端系统可以相互请求和提供服务，具有self scalability（自我扩展性）。
Self scalability（自我扩展性）指新的对等节点加入网络时，会带来新的服务能力（额外的存储空间、计算能力或者带宽等资源），同时也会带来对现有服务的新需求（请求特定的文件或者资源）。
端系统可以是intermittently（间断性）连接的，并且具有动态IP地址。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/4c799b2174b34a109c95406cfd4ce073.png)
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/d73aa32dbc2041009706c3f4616b81cc.png)
关于著名的P2P软件迅雷及BT下载的科普可以看下面两个视频：
https://www.bilibili.com/video/BV1tm421W7Fv/?spm_id_from=333.337.search-card.all.click&vd_source=3e562ebba9d60af0c036a8e95b29f3c1
https://www.bilibili.com/video/BV1VyyUYVEMq?spm_id_from=333.788.recommend_more_video.-1&vd_source=3e562ebba9d60af0c036a8e95b29f3c1

### 2.2.4 Application-layer protocol defines（应用层协议的定义）
应用层协议可以基于CS（客户端-服务器）架构或者P2P（对等）架构。
它定义了交换信息的种类，包含request（请求）和response（响应）等。
它规定了消息的syntax（语法），包括消息中包含哪些字段以及这些字段是如何界定的。
它定义了消息中字段信息的semantics（含义），即数据的意义和解释。
它还定义了消息的时序，即消息何时以及如何被发送和接收。
应用层的协议分两种协议：open protocols（开放协议）和private protocols（私有协议）。
open protocols（开放协议）：是由RFCs定义的，允许不同系统和应用程序之间的互操作性。例如：HTTP，SMTP，FTP。
private protocols（私有协议）：这些协议是由特定的公司或者组织开发，用于内部使用或者特定的应用程序。例如：Skype，在线游戏等。

### 2.2.5 Transport service requirements（传输服务的需求）
1.Data Integrity（数据完整性）
需要100%可靠的数据传输。
可以允许一定程度的数据丢失。比如在线直播偶尔卡顿不会严重影响用户体验。
2.Throughput（吞吐量）
有些应用需要最低限度的吞吐量才能有效运行，比如在线游戏需要一定的吞吐量才能保证游戏的流畅。
3.Timing（时序）
有些应用需要低延迟。比如在线游戏需要低延迟，但是邮件之类的可以允许延迟。
4.Security（安全性）
有些应用需要encryption（加密）来保护数据的机密性。
数据完整性检查可以确保数据在传输过程中没有被篡改。
下图举了一些例子进一步说明上面的需求。文件传输、电子邮件、网络文档都不允许数据丢失，对吞吐量要求是弹性的，对延迟无要求。
而实时视频/音频，下载视频/音频允许略微的数据丢失，吞吐量要根据视频/音频的质量，实时的对延迟要求较高，而下载就可以允许延迟较大了。
而对于互动游戏，允许略微的数据丢失，对吞吐量有最低要求，要求低延迟。（例如我们游戏一般会显示Ping，代表了网络延迟时间，单位一般是ms，而我们网络卡顿的时候游戏一般会提示丢包率或者延迟的具体信息）
而我们的一些日常文字信息与前面的文件传输类似，但是可能有时候我们需要这个信息是实时的。
对于音频和视频的传输，音频可能需要5kbps到1Mbps的吞吐量，而视频可能需要从10kbps到10Mbps或更高的吞吐量，但具体还是看音频和视频的质量。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/032c8bb414ee40bc950fa6aaf5228516.png)
#### 2.2.5.1 Internet transport protocols services（互联网传输协议服务）
TCP service：
可靠的传输：TCP提供了可靠的数据传输，确保数据从发送端到接收端的可靠交付，以及按顺序交付。
流量控制：TCP通过流量控制机制，确保发送方不会发送过多的数据导致接收方无法处理，从而避免网络congestion（拥塞）和数据丢失。
congestion（拥塞）控制：TCP具有拥塞控制机制，当网络出现拥塞时，会限制发送方的数据发送速率，以避免网络负载过重导致丢包和网络性能下降。
不提供的特性：TCP不提供严格的时序保证、最小吞吐量保证和安全性。
面向连接的：TCP是一种面向连接的协议，需要在客户端和服务器之间建立连接，然后才能进行数据传输。

UDP service：
不可靠的数据传输：UDP提供的是不可靠的数据传输，数据可能会丢失、重复或者无序到达。
不提供的特性：UDP不提供可靠性、流量控制、congestion（拥塞）控制、时序保证、最小吞吐量保证、安全性或连接设置等功能。
看上去UDP不理想，但是在一些实时性要求高的场合，比如音频/视频传输、在线游戏等，UDP因为其的简单快速而得到了广泛应用。

下图展示了一些应用和其对应的传输协议。大部分都使用TCP但是多媒体和网络语音中可能使用UDP。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/13c3342d497245e28865966fc02aca20.png)
由于TCP和UDP不提供加密，所以数据以明文形式传输到互联网上。这就意味着敏感信息（如密码）可能会以明文形式通过网络传输，存在被窃听和篡改的风险。因此可以使用SSL。SSL提供了对TCP连接的加密，确保数据在传输过程中是加密的，同时提供数据完整性和终端身份验证。SSL位于应用层，应用程序可以使用SSL库来与TCP通信，实现加密的数据传输。通过使用SSL套接字API，应用程序可以将明文密码转换为加密密码，然后通过加密的方式传输到互联网上，从而提高了密码传输的安全性。这一部分将在别的文章里进行介绍。

## 2.3 Web Application
Web浏览器和Web服务器之间传输数据通常使用HTTP（超文本传输协议），HTTP传输的一般是HTML（超文本标记语言）文档，HTML（超文本标记语言）用于创建网页内容。

WWW（World Wide Web，万维网），它是由网页、网站和Web应用程序组成的一个庞大的信息空间。这些网页通过互联网相互连接，并可以通过URL（uniform resource locator，统一资源定位器）访问。而HTTP是用于在Web上进行数据通信的协议。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/d70c6e5a76874dc8a6f5aaaf286968d8.png)
网页通常由一个基础的HTML文件构成，这个文件可以引用多种类型的资源，并通过URL（uniform resource locator，统一资源定位器）进行访问。这些资源包括：
HTML files：超文本标记语言文件，用于定义网页的结构和内容。
CSS files：层叠样式表文件，用于控制网页的布局和样式。
Images：图像文件，用于在网页上显示视觉内容。
Voice：音频文件，用于提供声音内容。
Javascript：一种编程语言，用于实现网页的动态交互功能。
Java applet：Java小程序，虽然现在较少使用，但过去用于在网页上运行小型应用程序。
Multimedia files：多媒体文件，如视频和音频，用于提供丰富的媒体内容。

### 2.3.1 HTTP 1.1
HTTP：hypertext transfer protocol （超文本传输协议），是一种应用层协议。使用客户端/服务器模型。客户端通常是指浏览器，它向Web服务器发送HTTP请求，并接收服务器返回的HTTP响应，客户端会呈现相应的Web对象，这一过程的传输都使用HTTP协议。服务器是指Web服务器，它接收来自客户端的HTTP请求，并使用HTTP协议向客户端发送相应的Web对象。

HTTP 1.1使用TCP协议进行通信。客户端通过在服务器的端口80（对于HTTPS是443）上创建一个套接字来发起TCP连接。服务器接受来自客户端的TCP连接。一旦建立了TCP连接，客户端和服务器之间就可以交换HTTP消息，这些消息是应用层协议消息，用于请求和响应Web对象。当所有的HTTP消息都被传输完毕后，TCP连接会被关闭。这样可以释放资源并结束通信会话。

HTTP是“无状态”的，这意味着服务器不会在请求之间保留关于客户端过去请求的任何信息。与保持“状态”的协议相比，HTTP的“无状态”特性使得协议更加简单。保持“状态”的协议需要维护客户端和服务器之间的交互历史（状态），这会增加复杂性和资源开销。当服务器或客户端发生崩溃时，它们对“状态”的保存可能会不一致，需要进行协调。

#### 2.3.1.1 HTTP general request format（HTTP请求信息的通用格式）
下图展示了HTTP请求信息的通用格式，它由request line（请求行）、header lines（头部行）和body（主体）构成。图上的sp是space character（空格），cr是carriage return character（回车），lf是line-feed character（换行）。回车和换行的区别如下：在打字机时代，回车指令会将打字头移回到行首，而不会移动到下一行。在计算机中，回车通常表示将光标移动到当前行的开头。换行指令会将打字头移动到下一行的开头，而不会改变水平位置。在计算机中，换行通常表示将光标移动到下一行的开头。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/cbe2a214c9ef40b5aabf5dc181ae998d.png)
Request line（请求行）包含method（方法）、URI（Uniform Resource Identifier，统一资源标识符）、version（版本）。方法指定了对资源执行的操作，如GET、POST等。URI指定了请求的资源。版本指定了使用的HTTP协议版本。
GET请求一般用于请求服务器发送资源，请求页面或数据。参数通过URL传递，附加在URL后面，以问号（?）开始，各个参数之间用&分隔。可以被缓存、收藏为书签、保留在浏览器历史记录中。这个方法适用于获取数据，不适用于修改数据。
POST请求一般用于向服务器提交数据，通常用于表单提交。参数通过请求体（body）传递，不会显示在URL中。不会被缓存，也不能收藏为书签或保留在浏览器历史记录中。这个方法适用于提交数据，如用户登录、注册信息、上传文件等。
URI（Uniform Resource Identifier，统一资源标识符）提供了一种在网络中定位资源的通用方法，用于标识资源的位置或名称。URI 可以是绝对的，也可以是相对的。绝对的 URI 包括了定位资源所需的所有信息，而相对的 URI 则需要结合一个基础 URI 来确定资源的位置。
URL（Uniform Resource Locator，统一资源定位符）是URI的一种特定类型，专门用于定位资源。它提供了资源在互联网上的具体位置。URL 总是绝对的，包含了完整的信息，如协议类型（如 http、https、ftp 等）、域名、端口号（如果有的话）、路径以及可能的查询字符串和片段标识符。URL 用于指定一个资源的位置，使得浏览器或其他客户端能够直接访问该资源。
前面说URI还用于标识资源的名称，通过的是URN（Uniform Resource Name，统一资源名称）。

Header lines（头部行）包含一个或多个头部字段，每个字段由header field name（字段名）、冒号、value（字段值）和cr if（回车换行符）组成。头部字段提供了关于请求的额外信息，如客户端信息、内容类型、认证信息等。

Body（主体），也被称为entity body（实体主体），它包含了请求的主题数据，如表单数据、文件上传内容等。主体后面也会有一个cr if（回车换行符），以表示主体的结束。

我们发现这里HTTP请求中不包含IP地址，是因为HTTP是一个应用层协议，它依赖于传输层协议（如TCP或UDP）来处理网络地址和路由。

比如下图就展示了Wireshark抓包工具捕获的一个HTTP GET请求的详细信息。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/e05d15717cd943289014e5e602397900.png)
请求行表示了使用GET方法请求资源，HTTP版本为1.1。
Host: www.feimax.com请求的主机名，即服务器的域名。告诉服务器请求的是哪个网站。
Connection: keep-alive连接管理，keep-alive表示客户端希望保持连接不断开，以便可以复用同一个TCP连接发送多个请求。
Upgrade-Insecure-Requests：1告诉服务器客户端希望使用HTTPS而不是HTTP。这是一个安全特性，用于自动将不安全的请求升级为安全的HTTPS请求。
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7)AppleWebKit/537.36 (KHTML, like Gecko) Chrome/86.0.4240.75 Safari/537.36这个头部字段提供了客户端浏览器的详细信息，包括浏览器类型、版本、操作系统和渲染引擎。这有助于服务器确定如何最佳地呈现内容。
Accept:text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,/;q=0.8,application/signed-exchange;v=b3;q=0.9告诉服务器客户端能够处理的内容类型。这里列出了多种内容类型，包括HTML、XHTML、XML、AVIF、WebP、APNG图片格式，以及所有其他类型，后者的优先级较低。
Accept-Encoding: gzip, deflate指示客户端能够处理的压缩格式。在这里，客户端表示它可以处理gzip和deflate压缩算法，这允许服务器压缩响应数据，减少传输数据量。
Accept-Language: zh-CN,zh;q=0.9告诉服务器客户端偏好的语言。在这里，客户端首选简体中文（zh-CN），如果简体中文不可用，也可以接受繁体中文（zh）。
这里出现了很多q=0.9，这里q参数用于表示内容的优先级，表示客户端对某种类型、语言或编码的偏好程度。q=1表示最高优先级，客户端最偏好这种类型、语言或编码。q=0表示客户端不接受这种类型、语言或编码。这个值是一个从0到1的数。所以以最后一个头部字段为例，如果简体中文（zh-CN）不可用，客户端也接受繁体中文（zh），优先级略低，因为q值为0.9。而没有指定就是默认值1，即前面的简体中文就是没有指定使用默认值1。

在我们点击Wireshark的Show packet bytes后，我们可以看到数据包的原始字节。
下图所示我们就可以看到数据包的十六进制表示和对应的ASCII字符。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/93eced04145d405baebe501f23bafe60.png)
#### 2.3.1.2 HTTP request method（HTTP请求方法）
我们需要网络协议进行CRUD操作，CRUD指的是四种操作：
Create（创建）：在服务器上创建新的资源。
Read（读取）：从服务器获取资源或数据。
Update（更新）：修改服务器上的现有资源。
Delete（删除）：从服务器删除资源。
CRUD操作的对象通常是resource（资源）、data（数据）、information（信息）。
HTTP通过方法从而完成这些操作：
GET：请求指定资源的表示形式。GET请求应该只用于获取数据，而不会引起服务器上的状态变化。
POST：向指定资源提交要被处理的数据，通常用于表单提交，可以引起服务器上的状态变化。
PUT：将请求体中的数据替换指定资源的内容。
DELETE：删除指定的资源。
HEAD：与GET方法一样，但服务器在响应中只返回头部信息，不返回实体的主体部分。
TRACE：请求服务器回显请求消息，用于诊断和验证中间网关或代理服务器。
OPTIONS：请求服务器返回该资源所支持的HTTP方法。
CONNECT：将连接改为管道方式的代理服务器。通常用于SSL加密服务器的连接（HTTPS）。
PATCH：对指定资源进行部分修改。
前面五种方法是HTTP1.0就定义的，而这些方法在HTTP1.1得到了保留并进行了改进和扩展，并且引入了下面四种新的方法以支持HTTP1.1引入的一些新特性比如Persistent Connections（持久连接）、Pipelining（管道化请求），以支持更复杂的Web应用程序需求。

#### 2.3.1.3 HTTP request headers（HTTP请求头部）
它们是一些键值对，用于携带关于请求和客户端的元数据。其中包括：
Host name：指定要访问的主机名，它允许在同一台服务器上托管多个域名的虚拟主机根据不同的域名提供不同的网站。
Authentication：用于在请求中传递身份验证信息，以便服务器可以验证客户端的身份。
Content types：指定请求的内容类型，例如JSON、XML、表单数据等。
User-agent information：包含关于客户端应用程序的信息，例如操作系统、浏览器版本等。
Caching / Cookies：用于控制缓存和传输过程中的Cookie信息。
Types of connections：指定请求的连接类型，例如保持连接或关闭连接。
等。

Types of connections分两种，一种是Non-persistent HTTP（非持久连接HTTP）:
在非持久连接中，每个HTTP请求都会建立一个新的TCP连接。每个TCP连接只能发送一个对象（如一个网页或一个图片）。在对象传输完毕后，TCP连接会立即关闭。如果需要下载多个对象，就需要建立多个TCP连接，这可能会导致额外的连接建立和关闭的开销。另一种是Persistent HTTP（持久连接HTTP）:在持久连接中，客户端和服务器之间的TCP连接可以被重复使用，多个HTTP请求和响应可以在同一个TCP连接上进行。这样就避免了建立和关闭多个TCP连接的开销，提高了性能和效率。

在Non-persistent HTTP（非持久连接HTTP）中，服务器响应所需要的时间计算方式如下：
RTT（Round Trip Time）：往返时延，指的是从客户端发送一个小数据包到服务器，然后服务器返回响应所需的时间。
HTTP响应时间：在非持久连接的情况下，服务器响应一个HTTP请求所需的时间包括以下几个部分：
一个RTT用于建立TCP连接：客户端发送连接请求到服务器，服务器接受请求并建立连接的时间。
一个RTT用于HTTP请求和服务器的部分响应返回：客户端发送HTTP请求到服务器，服务器接收请求并返回部分响应的时间。
文件传输时间：服务器发送完整的文件内容到客户端所需的时间。
因此非持久连接的HTTP的响应时间= 2 * RTT + 文件传输时间。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/4a93699d27ec407d8c021aa9a4fb679f.png)
Non-persistent HTTP（非持久连接HTTP）的缺点：
1.每个对象都需要两个RTT。
2.操作系统对每个TCP的连接都有开销。
3.浏览器通常会使用并行的TCP连接来获取引用对象，从而提高了性能。

Persistent HTTP（持久连接HTTP）的缺点：
1.服务器在发送响应后会保持连接处于打开状态，这可能会占用服务器资源。
2.同一客户端和服务器之间的后续HTTP消息都需要通过已经打开的连接发送，这可能会导致连接的持续时间过长。
3.客户端在遇到引用对象时会立即发送请求，这可能会导致过多的并行请求，增加服务器的负载。
4.尽管持久连接可以减少每个对象的RTT，但仍然可能需要至少一个RTT来获取所有引用的对象。

#### 2.3.1.4 HTTP response message format（HTTP响应信息的格式）
HTTP响应信息的格式由status line（状态行）、response headers（响应头部）、response body（响应体）三部分组成。
所以它们最大的区别在于第一行，这里的status line由version、sp、status code（请求处理结果的数字代码）、status text（状态代码的简短描述，如“OK”）、ct、lf组成。
下图右边便展示了一个结果，HTTP/1.1 200 OK表示HTTP版本为1.1，状态码为200，状态文本为“OK”。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/4cb804f1a72a40fca521cde409a87d57.png)
Status code（状态代码）出现在服务器到客户端响应消息的第一行——状态行。
一些常见的状态代码如下：
200 OK: 表示服务器成功处理了客户端的请求，服务器返回的内容在响应体中。
301 Move Permanently: 表示请求的资源已被永久移动到新的位置。客户端应该使用新的URL重新发起请求。
400 Bad Request: 表示服务器无法理解客户端发送的请求，通常是因为请求语法错误。
404 Not Found: 表示服务器无法找到请求的资源，即请求的URL对应的页面或文件不存在。
505 HTTP Version Not Supported: 表示服务器不支持客户端所使用的HTTP协议版本。

HTTP状态码的主要类别有五个：
1. 1xx: Informational（信息性状态码）：表示请求已接收，且服务器正在处理。这类状态码通常用于指示临时响应，并且请求可能还在处理中。

2. 2xx: Success（成功状态码）：表示请求已成功被服务器接收、理解、并接受。这是最理想的结果，意味着请求已经成功处理，例如：
200 OK：请求成功处理。
201 Created：请求成功，并且服务器创建了新的资源。
204 No Content：请求成功，但响应体中没有内容。

3. 3xx: Redirection（重定向状态码）：表示为了完成请求，客户端需要采取进一步的行动。这类状态码通常用于告诉客户端资源的位置已经改变，例如：
301 Moved Permanently：资源已被永久移动到新位置。
302 Found：资源临时移动到新位置。
304 Not Modified：自从上次请求后，资源没有被修改。

4. 4xx: Client Error（客户端错误状态码）：表示请求包含错误的语法或无法被服务器完成。这类状态码通常用于指示客户端的问题，例如：
400 Bad Request：服务器无法理解请求。
401 Unauthorized：请求需要用户的身份验证。
403 Forbidden：服务器拒绝请求。
404 Not Found：服务器找不到请求的资源。

5. 5xx: Server Error（服务器错误状态码）：表示服务器在处理请求的过程中遇到了错误，无法完成请求。这类状态码通常用于指示服务器的问题，例如：
500 Internal Server Error：服务器遇到了一个意外情况，无法完成请求。
501 Not Implemented：服务器不支持请求的功能。
503 Service Unavailable：服务器暂时无法处理请求，可能是由于过载或维护。

下图展示了更多状态码。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/ba798554a3f94626aae11a9d80fad7a7.png)
### 2.3.2 Cookies
由于HTTP是“stateless”的，所以服务器无法记住之前的请求。因此网站会使用cookies从而实现持续的会话状态或跟踪用户状态。通过Cookies保持住了用户的状态和信息，如登录状态、购物车内容等。
cookies有四个部分组成：
1. 在HTTP响应消息中的cookie头部行（cookie header line of HTTP response message）：当服务器向客户端发送HTTP响应时，可以通过在响应头部中添加Set-Cookie字段来设置cookie，将需要在客户端保持的状态信息发送给客户端。
2. 在下一个HTTP请求消息中的cookie头部行（cookie header line in next HTTP request message）：客户端在发送下一个HTTP请求时，会在请求头部中添加Cookie字段，将之前服务器发送的cookie信息发送回服务器，以便服务器识别客户端的状态。
3. 用户主机上由用户浏览器管理的cookie文件（cookie file kept on user’s host, managed by user’s browser）：浏览器会将服务器发送的cookie信息保存在用户主机上的cookie文件中，以便在后续访问时发送给服务器。
4. 网站后端的数据库（back-end database at Web site）：服务器端会维护一个数据库或其他数据存储机制，用于存储与每个客户端相关的状态信息，以便在收到客户端发送的cookie信息时能够识别客户端并恢复其状态。

例如小白首次访问亚马逊网站时，亚马逊网站会为小白创建一个unique ID（唯一的标识符），通常是通过生成一个唯一的cookie来实现。这个cookie会在服务器端生成，并通过HTTP响应的Set-Cookie头部发送给小白的浏览器。浏览器会将这个cookie保存在小白的计算机上，以便在将来的访问中发送回服务器。
同时，亚马逊网站还会在后端数据库中为小白的唯一标识符创建一个条目，这个条目会用来存储与小白相关的状态信息，例如购物车内容、个人偏好设置等等。这样，当小白再次访问亚马逊网站时，服务器就可以通过小白的唯一标识符识别他，并恢复他之前的状态和信息，为他提供个性化的服务和体验。
下图便展示了这一过程。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/b3b3e01385934205a2e11cf97f1bb701.png)
Cookies的用途：
1. Authorization（授权）：Cookies可以用来存储用户的登录状态，这样用户就不需要在每次访问网站时都重新登录。
2. Recommendations（推荐）：通过分析用户的浏览和购买历史，Cookies可以帮助网站为用户提供个性化的推荐。
3. User session state（用户会话状态）：Cookies可以用于跟踪用户的会话信息，比如在购物网站上跟踪用户添加到购物车的商品。
4. 其他：如记录用户的偏好设置、提供个性化内容等。

因此，Cookies允许网站了解很多关于您的信息：由于Cookies可以存储用户的浏览习惯和偏好，它们可以被用来收集用户的个人信息和行为数据。为了保护隐私，建议用户定期清理浏览器中的Cookies。
下图展示的便是Cookie。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/3502a418a2f948da91509413fa26d7fc.png)
### 2.3.3 Web caches（Web缓存）
Web caches（Web缓存）机制使用proxy server（代理服务器）作为客户端和origin server的中间层来缓存内容，储存常用资源的副本，以便更快地提供给客户端。
Proxy Server（代理服务器）：位于客户端和原始服务器之间的服务器，它可以接收客户端的请求并代表客户端向原始服务器请求资源。
Origin Server（原始服务器）：拥有资源原始副本的服务器，客户端最终想要获取资源的地方。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/5c3fce4556d54ec487479925c75e8e76.png)
对于原始请求的客户端来说，缓存充当了服务器的角色。当客户端发起请求时，缓存可以响应这个请求，提供所需的资源，而不需要直接向原始服务器请求。这样可以减少对原始服务器的负载，提高响应速度，并且节省网络带宽。
对于原始服务器来说，缓存充当了客户端的角色。缓存会向原始服务器发起请求，获取原始服务器上的资源，并将这些资源保存起来，以便在将来有其他客户端需要时能够快速地提供。这样可以减少对原始服务器的请求压力，同时提高整体的网络性能。
通常情况下，缓存是由Internet Service Provider (ISP)、大学、公司或者住宅区的网络服务提供商等实体来安装和管理的。这些实体会在网络中的关键位置设置缓存，以便为其用户提供更快速、高效的网络访问体验，并且减轻整体网络负载。

因此Web caches（Web缓存）的优点如下：
1.缩短客户端请求的响应时间。
2.减少机构接入链路上的流量。
3.通过在Internet中设置大量的缓存，可以使得那些内容提供者资源有限的实体能够有效地提供内容。这也包括了P2P文件共享，通过P2P网络，用户可以共享自己的资源，从而实现更高效的内容传输和分享。

为了保持Web缓存的优势，又能一直保持正确的最新版本资源，因此需要进行检查。HTTP协议中定义了conditional GET机制，其目标是在缓存中存在最新版本的资源时，不发送该资源的副本，从而避免了对象传输延迟和降低了链路利用率（当资源是最新的无需更新，便无需再传输因此避免了数据传输延迟，无需返回完整的资源内容从而降低了链路利用率）。
具体实现步骤如下：缓存在发起HTTP请求时会在请求头中指定上次缓存的资源日期，使用If-modified-since: \<date>字段。
服务器在收到这样的请求后，会检查请求中指定的日期与服务器上资源的最新修改日期对比，如果缓存的资源仍然是最新的，服务器会返回一个HTTP/1.0 304 Not Modified的响应，表示不需要重新传输资源。
如果服务器判断缓存的资源已经过期，或者是缓存中没有这个资源的副本，服务器会返回完整的资源内容，状态码为200 OK。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/bbfb804fc50f4b9b9442368111cf4c70.png)

### 2.3.4 RESTful API
HTML用于定义网页的结构和内容，API可以允许网页与服务器或其他服务器进行数据交换。它们都是组成网页的重要部分，当然除了HTML和API还有其他技术和资源组成了网络，前文提及到了CSS、JavaScript等都是网络的组成部分。

RESTful API（Representational State Transfer Application Programming Interface）是一种基于REST架构原则设计的API，是目前大部分开发者正使用的。它是一组推荐的API设计风格和规则，旨在提供一种简单、灵活和可扩展的方式来构建Web服务。其中包括：
1.使用标准的HTTP方法（GET、POST、PUT、DELETE等）对资源进行操作。
2.资源通过统一资源标识符（URI）进行标识，每个URI代表一个资源。
3.无状态性，即服务器不会在请求之间存储客户端的会话信息。
4.使用标准的HTTP状态码来表示请求的结果。

由此可见，RESTful API的设计使得它能够更好地利用HTTP传输协议，从而更方便地实现网页内容的呈现和交互。

例子如下：
Retrieving User Information（获取用户信息）：
通过发送GET请求： GET /users/123，这可以从服务器获取ID为123的用户的信息。
Creating a New User（创建新用户）：
通过发送POST请求：POST /users，请求体使用JSON数据格式，从而发送用户的信息，这可以在服务器上创建一个新的用户。
Updating User Information（更新用户信息）: 
通过发送PUT请求： PUT /users/123，请求体使用JSON数据格式，从而包含更新的用户信息，这可以更新ID为123的用户的信息。
Deleting a User（删除用户）：
通过发送DELETE请求：DELETE /users/123，这可以删除ID为123的用户。

下面展示几个RESTful的错误例子：
请求：GET /getUser?id=123
使用动词在URI中，应该使用名词而不是动词来表示资源。
请求：POST /users/getUserInfo
使用了POST请求来获取用户信息，应该使用GET请求。
请求：GET /users/updateEmail?id=123&email=newemail@example.com
在URI中包含了"updateEmail"这个动作，应该使用HTTP方法来表示对资源的操作，而不是将操作包含在URI中。

### 2.3.5 HTTP/2
HTTP/2是HTTP协议的下一代版本，它引入了一些重要的特性和改进，旨在提高Web性能和效率。细节如下：
Multiplexing（多路复用）：HTTP/2允许在单个连接上同时发送多个请求，从而减少了连接的数量，提高了性能并降低了延迟。
Header Compression（头部压缩）：HTTP/2使用了一种称为HPACK的算法来压缩HTTP头部信息，从而减少了数据传输时的开销，并改善了页面加载时间。
Server Push（服务器推送）：HTTP/2允许服务器在客户端请求之前主动推送资源，从而加快页面加载速度。例如，服务器可以在发送HTML响应时，主动推送相关的CSS、JavaScript或图像资源，减少客户端请求的往返时间，提高性能。
Binary Framing（二进制分帧）：HTTP/2使用二进制格式而不是文本格式来传输数据，这使得数据在传输过程中更加高效，更容易解析，同时也减少了错误的可能性。

### 2.3.6 HTTP/3
Based on QUIC Protocol（基于QUIC协议）：HTTP/3使用QUIC协议，该协议使用UDP而不是TCP作为传输层协议，从而减少了连接建立时间，并在高延迟网络环境中提供更好的性能。
Improved Multiplexing（改进的多路复用）：HTTP/3消除了在HTTP/2中出现的头部阻塞问题，进一步提升了性能。这意味着即使一个请求出现延迟，也不会影响其他请求的处理，从而提高了并行处理能力。
Better Connection Resumption（更好的连接恢复）：HTTP/3具有更快的连接恢复和继续功能，即使网络发生变化（如从Wi-Fi切换到移动数据），也能够更快地恢复连接，提供更好的用户体验。
Built-in Security（内置安全性）：HTTP/3默认集成了TLS（传输层安全）协议，用于对数据进行加密和安全传输。

## 2.4 DNS （Domain Name System，域名系统）
我们前面知道了数据传输，通过IP地址和端口号建立连接。我们可以输入百度的IP地址直接访问百度，但是我们平时输入的一般都是www.baidu.com而不是对应的IP地址，因为IP地址难以记忆，而www.baidu.com正是domin name（域名）。电脑中有hosts文件（Windows：C:\Windows\System32\drivers\etc\目录下，Unix-like： /etc/ 目录下）记录了IP地址和域名的映射关系。所以当我们输入www.baidu.com后，电脑会在hosts文件中寻找对应的IP地址，从而建立了连接，成功访问了百度。所以这个hosts文件如何更新呢？这就要借助DNS服务器，将对应的域名解析为相应的IP地址。这便是DNS。

DNS是一种应用层协议，它采用客户端/服务器架构，使用UDP协议并默认端口号为53。
resolve（解析）域名又称name/address translation（名称/地址转换）的两种方式：通过本地的hosts文件或通过与name servers（名称服务器，名称服务器就是DNS服务器）通信。
DNS使用分布式数据库的方式来存储域名和IP地址的映射关系。这些数据库被实现为许多名称服务器的层次结构，这种层次结构使得DNS系统能够高效地进行域名解析，并且具有一定的容错能力和可扩展性。例如当你查询一个域名的对应IP时，一个服务器会告诉你去哪一个服务器，这个服务器可能会告诉你去下一个服务器，再下一个服务器会告诉你具体的IP地址。

DNS服务包括以下功能：
1.Hostname to IP address translation（主机名到IP地址的转换）。这一步使用Address Record（A记录）完成，它是一种在DNS数据库中的数据结构。
2.Host aliasing（主机别名），这一步将一个主机名映射到另一个主机名，从而实现主机名的别名或重定向。这一步包括Canonical names（规范名称），指向实际的主机名。还包括Alias names（别名），主机的替代名称，用于提供更易记的名称。这一步使用cname record（Canonical Name Record）完成，这种数据结构可以让多个域名指向同一个IP地址。
3.Mail server aliasing（邮件服务器别名），用于指定邮件服务器的主机名，允许邮件系统找到接收特定域名邮件的邮件服务器。它使用的数据结构是mx record（Mail Exchange Record）。
4.Load Distribution（负载均衡），DNS可以将请求分配到多个服务器，以实现负载均衡和高可用性。
5.Replicated Web servers（复制的Web服务器），多个IP地址对应一个名称，允许实现多个服务器共享同一个域名，提高网站的可靠性和性能。比如当一个服务器故障时，DNS可以停止解析到那个服务器的IP，将流量转移到其他服务器。前面负载均衡也指出了，DNS服务器会根据当前的网络状况和服务器负载来决定指向哪个IP地址。

### 2.4.1 A distributed, hierarchical database（一个分布式和分层数据库结构）
那我们现在说DNS的结构。如果DNS是中心化的，那么会有以下几个问题：
1.如果出现single point of failure（单点故障），整个DNS都会受到影响。
2.所有的DNS都集中在一个地方，那么这个地方将承受巨大的流量压力。
3.网络传输和距离有关，所以如果集中在一个地方，必定会存在因为距离而导致网络延迟高而解析速度慢的问题出现。
4.在维护上集中管理的维护成本也跟分散式的相比更高。
因此DNS是a distributed, hierarchical database（一个分布式和分层数据库结构）
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/cf06c731b41e46e9a8a852882d0e8b18.png)
首先Root DNS servers（根DNS服务器）是DNS层次结构的最顶层，它们知道所有顶级域名（如.com、.org、.edu）的权威DNS服务器的位置。
下面是一些顶级域名的权威DNS服务器，例如com DNS servers（.com域名的DNS服务器）。它们下面还管理各自顶级域名下的二级域名，例如（yahoo.com、amazon.com等）。
再下一层便是各个域名的权威DNS服务器，它们存储了各自域名下的详细DNS记录，包括A记录、CNAME记录等。

所以当一个客户端向获取www.amazon.com的IP地址时，客户端首先向根DNS服务器发送查询，请求找到负责.com域名的DNS服务器，再接着向负责.com域名的DNS服务器发送查询，请求找到负责amazon.com域名的DNS服务器，最后向amazon.com的DNS服务器发送查询，以获取www.amazon.com的具体IP地址。

回到现实应用中，当本地DNS服务器无法解析某个域名时，它会联系根域名服务器以获取帮助。如果根域名服务器不知道某个域名的映射，它会联系相应的权威名称服务器。根域名服务器获取域名到IP地址的映射。根域名服务器将获取到的映射信息返回给本地DNS服务器。
下图展示了全球13个逻辑上的根域名服务器，每个根域名服务器都有多个副本。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/5916d373bae34691b6514e0813921fc9.png)
TLD servers（Top-level domain servers，顶级域名服务器）负责管理顶级域名，比如com，org，net，edu等。它还负责管理各个国家代码顶级域名，比如cn，uk，fr，ca，jp等。
Authoritative DNS servers（权威DNS服务器）是指组织自身维护的DNS服务器，用于提供对该组织命名主机的权威主机名到IP地址的映射。这些服务器可以由组织自己或者服务提供商进行维护管理。
Local DNS name server（本地DNS名称服务器）是指属于特定网络（如住宅ISP、公司、大学等）的DNS服务器，它并不严格属于DNS层次结构中的任何一级。每个ISP都会拥有自己的本地DNS名称服务器，有时也被称为“默认名称服务器”。当主机发起DNS查询时，查询会发送到它所在网络的本地DNS服务器。本地DNS服务器通常会维护一个本地缓存，其中包含最近的主机名到IP地址的映射，以便加快解析速度。然而，这些缓存中的信息可能已经过时。本地DNS服务器还充当代理，它会将查询转发到DNS层次结构中的其他级别。

### 2.4.2 Iterated query and Recursive query（迭代查询和递归查询）
Iterated query（迭代查询）：
当一个DNS服务器不知道所请求的域名时，它会告诉请求者去询问另一个DNS服务器。
如图所示，请求主机向本地DNS服务器发送查询请求。如果本地DNS服务器不知道答案，它会向根DNS服务器发送查询。根DNS服务器告诉本地DNS服务器去询问顶级域DNS服务器。本地DNS服务器向TLD DNS服务器发送查询。TLD DNS服务器告诉本地DNS服务器去询问权威DNS服务器。本地DNS服务器向权威DNS服务器发送查询。权威DNS服务器返回域名对应的IP地址。本地DNS服务器将IP地址返回给请求主机。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/ab08cb7031884b3c842da34dfffa51ba.png)
Recursive query（递归查询）
被查询的DNS服务器（如本地DNS服务器）会代表客户端（如用户的电脑）进行后续的查询，直到找到所需的记录或确定记录不存在。
这意味着名称解析的负担被放在了被联系的DNS服务器上。服务器需要处理查询并可能进行额外的查询，这可能导致DNS层次结构的上层（如根DNS服务器和TLD DNS服务器）承受较重的负载，因为它们需要处理大量的查询请求。
如图所示，请求主机向本地DNS服务器发送查询请求。如果本地DNS服务器不知道答案，它会向根DNS服务器发送查询。根DNS服务器如果不知道答案，根DNS服务器会向TLD DNS服务器发送查询。如果TLD DNS服务器不知道答案，TLD DNS服务器会向权威DNS服务器发送查询。最后权威DNS服务器将IP地址返回给TLD DNS服务器，TLD DNS服务器将这个IP地址返回给根DNS服务器，根DNS服务器将这个IP地址返回给本地DNS服务器，本地服务器再返回给请求主机。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/e7a4cbd36f0e4855be9342494db2c4f5.png)
 dig +trace是一个命令行工具，用于显示从客户端到权威DNS服务器的完整递归查询过程。

### 2.4.3 Caching, Updating records（缓存和记录更新）
一旦任何一个DNS名称服务器学习到了域名到IP地址的映射关系，它会将这些映射信息缓存起来。缓存中的条目会在一定时间后（TTL，time to live，生存时间）过期并消失。通常，顶级域名服务器的信息会被缓存在本地名称服务器中，这样就不需要经常访问根名称服务器。
然而，由于缓存中的条目可能会过时，如果某个主机的IP地址发生了变化，这个变化可能需要等到所有TTL过期后才能在整个互联网中得到更新。
为了解决这个问题，IETF提出了更新/通知机制的标准，其中的一个标准便是RFC 2136。

DNS是一个分布式数据库，用于存储资源记录（RR， resource records）。资源记录的格式通常为(name, value, type, ttl)。
这里如果type=A，便是A记录，代表主机地址记录，name是主机名，value是对应的IP地址。
如果type = CNAME，便是CNAME记录，指向“规范”（真实）名称，name是别名，value是规范名称，也就是真实的目标主机名。
如果type = NS，代表域名服务器记录，name是域名（例如foo.com），value是该域名的权威名称服务器的主机名。
如果type=MX，便是MX记录，代表邮件交换记录，value是与name相关联的邮件服务器的名称。

我们可以使用nslookup命令去查询一个域名对应的IP地址，如下图所示。
当我们使用不同的网络我们获得的DNS解析的IP地址可能不同，如下图所示。前两次都是使用学校的两个不同的网络查询的，它们返回的是路由器的默认网关IP地址，因为它们都是内网。而第三个不是内网，返回的IP地址就不会是前面一样的私有IP了。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/7f5e2fe7cebd4dbd867419b4727a1783.png)
我们还可以使用whois命令去获取域名的注册信息。如下图所示。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/cfd9df92bd8d4aff914d45b7dc3f9a23.png)
### 2.4.4 DNS protocol，messages
DNS的查询和回复信息共享相同的信息格式。如下图所示。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/8a5aec95b6e0436f8aa941d53edad165.png)
第一行是消息头，包含关键的元数据，用于标识和处理DNS消息。信息头包含identification（标识）和flags（标志）。Identification（标识）是一个16位的数字，用于唯一标识一个查询。当服务器回复查询时，会使用相同的标识符，以便客户端能够将回复与原始查询匹配。一个16位的数字，用于唯一标识一个查询。当服务器回复查询时，会使用相同的标识符，以便客户端能够将回复与原始查询匹配。包含多个标志位，用于控制消息的行为和状态。其中包括：
1.指示信息是查询还是回复。
2.客户端希望服务器执行递归查询。
3.服务器能够执行递归查询。
4.回复是否来自权威DNS服务器。
\# questions（问题数量），表示消息中包含的查询问题数量。
\# answer RRs（回答资源记录数量），表示消息中包含的答案资源记录的数量。
\# authority RRs（权威资源记录数量），表示消息中包含的权威资源记录的数量，这些记录指出了哪个服务器是某个域名的权威服务器。
\# additional RRs（附加资源记录数量），表示消息中包含的附加资源记录的数量，这些记录提供了额外的信息，如DNS服务器的地址。
questions，包含客户端提出的查询问题，可以有一个或多个。查询中包含域名和查询类型的字段，指定了要查询的域名和查询的资源类型（如A记录、MX记录等）。
answers，包含包含对查询问题的响应，可以有一个或多个资源记录，提供了查询域名的解析结果。
authority，提供权威信息，指出哪个DNS服务器是某个域名的权威服务器。
additional info，提供额外的DNS记录，可能包括额外的NS记录或其他类型的记录。

下图展示了wireshark抓包抓取的DNS查询数据包的具体情况。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/2120af0702164d92b7f484a836c66ef4.png)
第一行的Transaction ID（事务ID）等同于Identification（标识）。
下一行Flags字段中的每一位都代表一个特定的标志。细节如下：
1.QR（Query/Response）：这是最高位，如果是0，则消息是查询（Query）；如果是1，则消息是响应（Response）。在0x0100中，这个位是0，表示这是一个查询。
2.Opcode：接下来的4位用于指定操作码。在这里，0000表示这是一个标准查询（Standard query），意味着一个普通的请求，用于获取资源记录。
3.AA (Authoritative Answer)：如果设置（1），表示响应来自权威DNS服务器。在这里，这个位是0，表示这不是权威答案。
4.TC (Truncated)：如果设置（1），表示消息被截断，可能是因为响应数据太大而无法在单个UDP数据包中发送。。在这里，这个位是0，表示消息没有被截断。
5.RD (Recursion Desired)：如果设置（1），表示客户端希望服务器执行递归查询。。在这里，这个位是1，表示客户端希望进行递归查询。
6.RA (Recursion Available)：如果设置（1），表示服务器支持递归查询。。在这里，这个位是0，表示服务器不支持递归查询。
7.Z：保留位，通常不使用。
8.AD (Authenticated Data)：如果设置（1），表示响应是经过验证的。在这里，这个位是0，表示数据未经过验证。
9.CD (Checking Disabled)：如果设置（1），表示客户端不希望进行DNSSEC验证。在这里，这个位是0，表示没有禁用检查。

下图展示了与上面DNS请求相对应的回复。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/a850ac6d00da46b8a63bbb3f00feef90.png)

那我现在如何向DNS插入记录呢？假设现在有一个新的网站域名 “feimax.com”
首先，你需要在DNS注册商（例如net.cn）处注册feimax.com这个域名。通常情况下，你不需要自己设置NS记录，因为注册商会为你设置好。然后，你需要向DNS中插入A记录，将feimax.com指向你的主机的IP地址，这样当有人访问feimax.com时，DNS就能够将其解析为相应的IP地址。接着，你还需要插入MX记录，用于指定与feimax.com相关联的邮件服务器的名称。

## 2.4 P2P Applications
### 2.4.1 Pure P2P architecture（纯P2P架构）
没有始终在线的服务器，而是允许任意终端系统直接进行通信。此外，对等网络中的节点（对等方）可能会频繁地改变IP地址。典型的纯P2P架构的例子包括文件分发（BitTorrent）、流媒体（比如KanKan）、VoIP通信（比如Skype）。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/8ffc2c16589f410ab93358eef3218a40.png)
我们前面说过P2P和C/S的区别，现在我们具体比较一下两者在文件分发上的时间。
其中$F$表示要分发的文件的大小，$u_s$表示服务器上传能力，$d_i$表示对等方的下载能力，$u_i$表示对等方的上传能力。
在C/S架构中，服务器必须依次发送（上传）N份文件副本。所以发送一份副本的时间是$F/u_s$。发送N份副本的时间是$NF/u_s$。
每个客户端必须下载文件副本。所以客户端花费的最多时间是由客户端下载速度最小的决定的。最大客户端下载时间：$F/d_{min}$。
因此最后的分发时间取决于这两个因素，但因为最后还会有其他一些问题，所以最后分发时间$D_{C-S}>max\{NF/u_s, F/d_{min}\}$。
在P2P架构中，在分发的开始，只有服务器具有文件。因此服务器必须至少发送该文件一次，但是与C/S不同，可能这个文件的比特不需要由该服务器发送，对等方在它们之间也可以发送这些比特。因此，最小的上传时间是$F/u_s$。
对于客户端，与C/S架构类似，最大客户端时间决定了这一部分的最小时间：$F/d_{min}$。
最后我们观察到在整个系统中，总上传能力等于服务器的上传能力加上每个单独的对等方的上传能力，这一起其实是文件需要上传的总大小，即NF。它不会以快于总下载速度的时间完成。因此这样计算的最小的分发时间至少是$NF/(u_s+ Σu_i)$。
所以最后的分发时间$D_{P2P}>max\{F/u_s,F/d_{min},NF/(u_s+ Σu_i)\}$
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/17084844a393429aa2f2387220d94cad.png)
为了更清楚比较C/S架构和P2P架构的最小分发时间，其中假定所有的对等方具有相同的上传速率$u$，$F/u = 1小时$，$u_s = 10u$，$d_{min}≥u_s$。因此，在一个小时中一个对等方能够传输整个文件，该服务器的传输速率是对等方上传速率的10倍，而且对等方的下载速率被设置得足够大，使之不会产生影响。下图中我们可以看到，对于C/S架构，随着对等方数量增加，分发时间呈线性增加并没有界。然而，对于P2P架构，最小分发时间不仅总是小于C/S架构的分发时间，而且对于任意的对等方数量N，总是小于1小时。关键原因是：对等方除了下载还进行了上传。

### 2.4.2 BitTorrent
BitTorrent是一种用于文件分发的流行P2P协议。在BitTorrent网络中，文件被分割为多个等长度的文件块（chunks），典型的块长度为256KB。，每个参与下载的对等方可以发送和接收这些文件块。
Tracker是BitTorrent网络中的一个中心服务器，它负责维护所有参与特定文件共享的对等方的列表。
Torrent或Swarm指的是一组参与特定文件共享的对等方，它们之间通过交换文件块来共享和下载文件。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/7d17d54697ae42cd9015e92bdaab0451.png)
BitTorrent中文件共享的基本流程如下：当一个用户想要分享一个文件或一组文件时，他首先创建一个.torrent文件。这个.torrent文件是一个小文件，其中包含了关于要分享的文件的metadata（元数据）信息，以及关于协调文件分发的tracker（跟踪器）的信息。
下载者首先获取这个.torrent文件，然后连接到指定的tracker（跟踪器）。tracker（跟踪器）会告诉下载者从哪些其他对等方下载文件的各个部分。这样，下载者可以通过连接到其他对等方来获取文件的不同部分，从而实现文件的高效分发和下载。
其中.torrent文件的metadata（元数据）信息包含了以下几个部分：
1.SHA-1 hashes of all pieces（对所有文件块的SHA-1哈希值），这些哈希值用于验证文件块的完整性，确保下载的文件块没有被篡改或损坏。
2.A mapping of the pieces to files（文件块与原始文件的映射关系），这个映射表明了每个文件块在原始文件中的位置，以便下载者可以根据需要获取特定的文件块。
3.Piece size（文件块的大小），这个信息指明了每个文件块的大小，下载者需要根据这个信息来正确地组装文件块以获取完整的文件。
4.Length of the file（文件的长度），这个信息表示了要分享的文件的总长度，下载者可以根据这个信息来了解文件的大小。
5.A tracker reference（tracker的引用），这个信息包含了tracker的地址或者其他信息，下载者可以根据这个引用来连接到tracker并获取其他对等方的信息，以便进行文件的下载和共享。

当一个对等方加入一个Torrent时，它可能还没有任何文件块，但会随着时间从其他对等方那里积累文件块。它会向Tracker注册以获取其他对等方的列表，并连接到其中的一部分对等方（也称为“邻居”）。
在下载文件的过程中，对等方会将已经下载的文件块上传给其他对等方，以帮助其他对等方完成文件的下载。
对等方可能会改变它们之间交换文件块的伙伴，以便更好地获取文件块并提高下载速度。
对等方可能会动态地加入和退出Torrent。
一旦一个对等方拥有了整个文件，它可能会选择离开Torrent，也可能选择继续留在Torrent继续帮助其他对等方完成文件的下载。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/74c056e961104b53a89c308992a882f6.png)
BitTorrent网络中几种角色：
Seeder（种子，发布者）：一个提供完整文件的对等方。当一个对等方拥有完整的文件，并且愿意与其他对等方分享这个完整文件时，它被称为一个Seeder。
Initial Seeder（原始发布者）：一个提供原始副本的对等方。在一个Torrent刚开始时就拥有完整文件并愿意分享的对等方。
Leecher（水蛭，下载者）：一个正在下载文件但并没有完整文件的对等方。Leecher从其他对等方那里获取文件块，并在下载完成之前不会分享自己拥有的文件块。当Leecher拥有了完整的文件，它可以开始分享文件块给其他下载者，从而成为一个Seeder。随着时间的推移，每个下载者最终会通过获取所有的文件块并组装文件来成为一个发布者（Seeder）。在这个过程中，下载者会验证文件的“checksum”（校验和），确保文件的完整性和正确性。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/c39724ab773044cdae6f690afffd726f.png)
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/06ab4714c3d14cac8e32ebd1ad02ca76.png)

从前面的叙述中，我们其实可以发现BitTorrent的piece selection policy（文件块选择策略）很重要：
文件块选择的顺序对性能至关重要，有效的文件块选择策略可以帮助提高下载效率和文件完整性。不当的策略可能导致对等方无法完成文件下载，如果使用了低效的文件块选择策略，那么可能会出现每个对等方都拥有相同一组容易获取的文件块，但却缺少其他文件块。如果原始种子（original seed）被提前关闭，文件可能无法完全下载。
下图展示了其中的几种情况。第一种情况节点之间有少量的文件分片重叠，这是理想的情况，因为它允许有效的资源共享而不会浪费太多带宽。第二种情况节点之间有大量的文件分片重叠，这可能导致带宽浪费，因为相同的数据被多次传输。第三种情况节点之间没有文件分片重叠，这在P2P网络中是不利的，因为没有数据可以共享，每个节点都必须从初始种子（或其它节点）下载完整的文件。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/5f0b4d72eed34b99b701e853e7c49351.png)

一般情况下，采用Rarest First（最稀缺优先）策略，优先请求那些最不常见的文件分片（确保最常见的文件块留到最后再下载），以确保网络中的多样性并加快整体下载速度。
在特殊情况下，采用Random First Piece（随即首个分片）策略。在下载开始时，随机选择第一个文件分片，这有助于快速开始下载过程并利用网络中的上传能力。（当一个对等方刚开始参与文件下载时，它可能没有任何文件块可以与其他对等方交换。在这种情况下，对等方需要尽快获取一个完整的文件块，以便开始与其他对等方进行文件块交换并加速整个文件的下载过程。）
在特殊情况下，当下载接近完成时，采取不同的策略（在文件下载接近完成时，缺失的文件块会从每一个拥有这些文件块的对等方处请求下载，这样做的目的是为了确保在文件下载接近完成时，任何一个拥有缺失文件块的对等方都有机会向下载方提供这些文件块，从而避免因为某个对等方传输速率较慢而导致整个文件无法完成下载的情况发生。虽然会存在一些带宽浪费，但实际上这种浪费并不会太多。）来优化最后几个分片的下载，确保所有节点都能尽快完成下载，这种策略叫Endgame Mode（结束游戏模式）。

BitTorrent中还有两个算法，这两个算法是内置的激励机制。
1.Choking algorithm是暂时拒绝上传文件块的行为。这是BitTorrent协议中用来处理"free riders（免费骑车者）"（即那些只下载而不上传的人）的一种重要策略。同时一个下载者会根据其他对等方的上传速度和响应性能，选择一些对等方进行优先上传，而对其他对等方进行阻塞，确保网络资源被合理利用。这种Tit-for-tat strategy（以牙还牙策略）来源于博弈论。
2.Optimistic unchoking过程中涉及一个对等方，我们称其为Alice，向当前以最高上传速率发送文件块的四个对等方发送文件块。与此同时，其他对等方被Alice“阻塞”，意味着它们不会从Alice那里接收文件块。从Alice那里接收文件块的前四个对等方每隔10秒进行重新评估，以确保使用最有效的连接。此外，每30秒，Alice会随机选择另一个对等方，并开始向其发送文件块，从而“乐观地解除阻塞”这个对等方。这个新选择的对等方可能会加入前四个对等方，取代先前选择的对等方之一。
使用这个算法有助于发现当前未使用的连接，这些连接可能提供比当前使用的连接更好的上传速率。并允许向新对等方提供最低限度的服务，有助于维护一个健康和稳健的文件共享网络。

对于完成了文件下载的对等方，它会进入Upload-Only mode（纯上传模式），即只能向其他对等方上传文件块。在这种模式下，一个对等方会选择向那些具有最佳上传速率的对等方上传文件块。这样做的目的是确保文件块能够更快地被复制到其他对等方，从而加速文件块的传播，同时也能够快速地创建新的seeders。

## 2.5 Socket Programming
我们现在学习如何创建使用sockets（套接字）进行交流的C/S程序。
对于两种不同的传输服务有对应的两种套接字类型：
UDP：不可靠的datagrams（数据报）服务。
TCP：可靠的、面向字节流的服务。
下面是一个应用的例子：
1.客户端从键盘读取一行字符（数据），并将数据发送给服务器。
2.服务器接收数据并将字符转换为大写。
3.服务器将修改后的数据发送给客户端。
4.客户端接收修改后的数据并在屏幕上显示该行数据

我们先说UDP的Socket programming。
UDP是一种无连接的传输协议，它在进行客户端和服务器之间的通信时不需要建立连接。在使用UDP时，发送数据之前不需要进行握手操作。发送方会显式地将IP目标地址和端口号附加到每个数据包上，而接收方则从接收到的数据包中提取发送方的IP地址和端口号。
由于UDP是一种无连接的协议，所以传输的数据可能会丢失或者以非顺序的方式接收到。从应用程序的角度来看，UDP提供了在客户端和服务器之间传输数据块（也称为“数据报”）的不可靠传输。

下图展示了UDP的Socket programming。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/4a9c8e64f6444dcab8a69a698bc74956.png)
接下来的代码实现了上面说的将小写字符改为大写字符的例子。
server端：
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/d27a061671ab4ceb857f4ae35708f65d.png)
client端：
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/807c321d08074ec888e73943bbb0ec37.png)

现在讨论TCP的Socket programming。
客户端必须与服务器进行联系。服务器进程必须首先在运行状态下，并且已经创建了一个等待客户端联系的套接字（门）。
客户端通过以下步骤与服务器联系：创建TCP套接字，指定服务器进程的IP地址和端口号。当客户端创建套接字时，客户端TCP与服务器TCP建立连接。
当客户端联系服务器时，服务器TCP为服务器进程创建一个新的套接字，以便与特定的客户端进行通信。允许服务器与多个客户端进行通信。源端口号用于区分不同的客户端。
从应用程序的角度来看，TCP提供了在客户端和服务器之间可靠、按顺序的字节流传输（类似于管道）。

下图展示了TCP的Socket programming。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/132f2fb19817457595006f435a09a8e7.png)
接下来的代码实现了上面说的将小写字符改为大写字符的例子。
server端：
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/c473fb13aa854f8f9eef5f16e75506c6.png)
client端：
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/acc120907c264edcb9eede23796c9561.png)


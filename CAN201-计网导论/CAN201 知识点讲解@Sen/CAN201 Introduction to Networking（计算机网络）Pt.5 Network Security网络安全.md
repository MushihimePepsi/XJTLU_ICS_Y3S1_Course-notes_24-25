- [6. Network Security（网络安全）](#6-network-security网络安全)
  - [6.1 What is network security（什么是网络安全）](#61-what-is-network-security什么是网络安全)
  - [6.2 Principles of cryptography（密码学的原则）](#62-principles-of-cryptography密码学的原则)
    - [6.2.1 Breaking an encryption scheme（破解加密方案）](#621-breaking-an-encryption-scheme破解加密方案)
    - [6.2.2 Symmetric key cryptography（对称密钥加密）](#622-symmetric-key-cryptography对称密钥加密)
      - [6.2.2.1 DES（Data Encryption Standard，数据加密标准）](#6221-desdata-encryption-standard数据加密标准)
      - [6.2.2.2 AES（Advanced Encryption Standard，高级加密标准）](#6222-aesadvanced-encryption-standard高级加密标准)
    - [6.2.3 Public key cryptography（公共密钥加密）](#623-public-key-cryptography公共密钥加密)
      - [6.2.3.1 RSA（Rivest, Shamir, Adleman）](#6231-rsarivest-shamir-adleman)
  - [6.3 Authentication and Message integrity（认证和信息完整性）](#63-authentication-and-message-integrity认证和信息完整性)
    - [6.3.1 Authentication（认证）](#631-authentication认证)
    - [6.3.2 Message integrity（信息完整性）](#632-message-integrity信息完整性)
      - [6.3.2.1 Digital signatures（数字签名）](#6321-digital-signatures数字签名)
      - [6.3.2.2 Message digests（信息摘要）](#6322-message-digests信息摘要)
  - [6.4 Securing e-mail](#64-securing-e-mail)
  - [6.5 Securing TCP connections：SSL](#65-securing-tcp-connectionsssl)
    - [6.5.1 Toy SSL（简单安全套接层）](#651-toy-ssl简单安全套接层)
      - [6.5.1.1 Handshake（握手阶段）](#6511-handshake握手阶段)
      - [6.5.1.2 Key derivation（密钥派生阶段）](#6512-key-derivation密钥派生阶段)
      - [6.5.1.3 Data transfer（数据传输阶段）](#6513-data-transfer数据传输阶段)
      - [6.5.1.4 Connection closure（连接关闭阶段）](#6514-connection-closure连接关闭阶段)
      - [6.5.1.5 Summary](#6515-summary)
    - [6.5.2 Real SSL](#652-real-ssl)
  - [6.6 Network layer security：IPsec](#66-network-layer-securityipsec)
    - [6.6.1 Virtual Private Networks（VPNs，虚拟专用网络）](#661-virtual-private-networksvpns虚拟专用网络)
    - [6.6.2 IPsec services（IPsec的服务）](#662-ipsec-servicesipsec的服务)
    - [6.6.3 IPsec mode（IPsec的工作模式）](#663-ipsec-modeipsec的工作模式)
      - [6.6.3.1 Transport mode（传输模式）](#6631-transport-mode传输模式)
      - [6.6.3.2 Tunneling mode（隧道模式）](#6632-tunneling-mode隧道模式)
    - [6.6.4 Security associations（SAs，安全关联）](#664-security-associationssas安全关联)
    - [6.6.5 IPsec datagram](#665-ipsec-datagram)
    - [6.6.6 Summary](#666-summary)
  - [6.7 Operational security：firewalls and IDS（运行安全：防火墙和入侵检测系统IDS）](#67-operational-securityfirewalls-and-ids运行安全防火墙和入侵检测系统ids)
    - [6.7.1 Firewalls（防火墙）](#671-firewalls防火墙)
      - [6.7.1.1 Stateless packet filters（无状态数据包过滤器）](#6711-stateless-packet-filters无状态数据包过滤器)
      - [6.7.1.2 Stateful packet filters（有状态数据包过滤器）](#6712-stateful-packet-filters有状态数据包过滤器)
      - [6.7.1.3 Application gateways（应用程序网关）](#6713-application-gateways应用程序网关)
      - [6.7.1.4 Limitations of firewalls, gateways](#6714-limitations-of-firewalls-gateways)
    - [6.7.2 Intrusion detection systems（入侵检测系统）](#672-intrusion-detection-systems入侵检测系统)

# 6. Network Security（网络安全）
## 6.1 What is network security（什么是网络安全）
网络安全涉及以下几个重要概念：
1.Confidentiality（保密性）：在通信过程中，只有发送方和预期的接收方能够理解消息的内容。为了实现保密性，发送方会对消息进行加密，而接收方则会对消息进行解密，从而确保只有授权的人能够理解消息内容。
2.Authentication（身份验证）：发送方和接收方希望确认彼此的身份，以确保通信的安全性。
3.Message integrity（信息完整性）：发送方和接收方希望确保消息在未经检测的情况下在传输过程中或之后没有被篡改。
4.Access and availability（访问和可用性）：网络服务必须对用户可访问和可用。

在网络安全的世界中经常有三个角色：Alice，Bob，Trudy。
Alice和Bob：通常被描述为通信双方，有时也被描述为恋人。他们是网络中合法的通信双方，他们希望能够安全地进行通信，保护通信内容的保密性、完整性和身份验证。
Trudy：通常被描述为一个intruder（入侵者）或者恶意的第三方，可能会拦截、删除或者篡改Alice和Bob之间的通信。
如图所示。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/9e2701f30f7842e1a1da3c8efe1a702a.png)
在实际应用中，Bob和Alice可以代表任何需要进行安全通信的实体，包括但不限于以下情况：
Web浏览器/服务器进行电子交易（例如在线购物）：Bob和Alice可以分别代表购物者和商家，他们希望在进行在线交易时能够安全地传输支付信息和订单详情。
在线银行客户端/服务器：在进行在线银行业务时，Bob和Alice可以分别代表银行客户和银行服务器，他们希望能够安全地进行资金转移和账户查询等操作。
DNS服务器：在域名解析过程中，Bob和Alice可以分别代表客户端和DNS服务器，他们希望能够确保域名解析的安全性和准确性。
交换路由表更新的路由器：在网络路由过程中，Bob和Alice可以分别代表不同的路由器，他们希望能够安全地交换路由信息，防止被篡改或者伪造。

网络安全中“坏人”可能采取的行动有很多，例如：
Eavesdrop（窃听）：恶意第三方拦截并监听通信双方之间的消息。
Insert（插入）：恶意第三方可以在通信连接中主动插入虚假的消息或数据，从而破坏通信的完整性和真实性。
Impersonation（冒充）：恶意第三方可以伪造通信中的源地址或其他字段，以假冒通信的合法参与者，从而进行欺骗或攻击。
Hijacking（劫持）：指的是恶意第三方试图“接管”正在进行的通信连接，通过移除发送方或接收方，将自己插入到通信中，从而获取通信的控制权。
Denial of service（拒绝服务）：恶意第三方可以通过各种手段，例如资源过载，来阻止其他用户使用特定的网络服务，从而导致服务不可用或无法正常使用。

## 6.2 Principles of cryptography（密码学的原则）
如图所示。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/2c17be351c514cd9be0b6cd74e425574.png)
在密码学中，我们将$K_A$当作Alice的加密钥匙，$K_B$当作Bob的解密钥匙。
plaintext（明文）经过Alice使用$K_A$和encryption algorithm（加密算法）从而加密成ciphertext（密文），然后在Bob这使用$K_B$和decryption（解密算法）从而得到plaintext（明文）。
我们一般用$m$表示plaintext message（明文信息）。
$K_A(m)$表示用$K_A$加密的ciphertext（密文）。
所以$m=K_B(K_A(m))$

### 6.2.1 Breaking an encryption scheme（破解加密方案）
当考虑Trudy破解Bob和Alice之间的加密方案的难易程度时，可以根据入侵者所拥有的信息分为三种不同的情况。
1.Cipher-text only attack（唯密文攻击）：Trudy拥有密文并对其进行分析。她可以使用两种方法来尝试破解加密算法：
Brute force（暴力破解）：通过尝试所有可能的密钥来解密密文。
Statistical analysis（统计分析）：通过分析密文的统计特征和模式来推断可能的密钥或明文内容。
2.Known-plaintext attack（已知明文攻击）：Trudy拥有与密文对应的明文。例如，在单字母替换密码中，Trudy可以通过已知的明文和密文对来确定字母的对应关系，从而破解密码。
3.Choosen-plaintext attack（选择明文攻击）：Trudy可以选择明文消息并获取其对应的密文形式。这使得攻击者能够分析加密算法的行为和特性，从而推断出密钥或者加密过程的信息。

### 6.2.2 Symmetric key cryptography（对称密钥加密）
Bob和Alice共享同一个（symmetric对称的）密钥：$K_S$
例如，密钥可以是mono alphabetic substitution cipher（单字母替换密码）中的替换模式，这种加密技术的每个字母被另一个字母替换。
那Bob和Alice如何就密钥值达成一致呢？
这是一个关键问题，因为在对称加密中，安全地共享密钥是一个挑战。如果密钥在传输过程中被截获，那么加密的安全性就会受到威胁。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/4e4efaecf30f41c09e6fc16d0d6d4f1b.png)


Caesar cipher（凯撒密码）是一种简单的替换加密方法，它通过对明文中的每个字母进行位移来生成密文。具体步骤如下：
对于英文文本，凯撒密码会将每个明文种的字母按照字母表顺序向后移动k个位置（allowing wraparound，允许环绕），其中k是一个固定的整数（密钥）。
举例来说，如果k=3，那么明文中的字母a将被替换为字母d，b将被替换为e，依此类推。这样就生成了对应的密文。

这种简单加密方案就是substitution cipher（替代密码），具体来说Caesar cipher（凯撒密码）是monoalphabetic cipher（单字母替代密码）。
在这种加密方案中，每个字母都被替换为另一个字母，而且加密密钥是一个从26个字母到26个字母的映射。也就是说，加密密钥是一个将明文字母映射到密文字母的规则。
如下图所示。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/6a4104b8628846448c5aa75e90b906be.png)
一个更加sophisticated（复杂的）加密方式便是polyalphabetic substitution cipher（多表替换密码）。
多表替换密码使用了多个替换密码表（$M_1,M_2,...M_n$）以及循环模式来对明文进行加密。
具体来说，加密密钥包含了$n$个替代密码表以及一个循环模式。对于明文里的每个字符，都会按照循环模式选择下一个替代密码表来进行替代。
举例来说，如果$n=4$，循环模式是$M_1.M_3,M_4,M_3,M_2$，对于明文“dog”，加密过程是d 用 $M_1$，o 用 $M_3$， g 用 $M_4$。

#### 6.2.2.1 DES（Data Encryption Standard，数据加密标准）
对称密钥加密算法常用的算法是DES（Data Encryption Standard，数据加密标准）算法。
在加密过程开始时，输入的64位数据会经过一个初始permutation（置换），以打乱数据位的顺序。
DES算法包含16个相同的rounds（轮次），每个轮次都应用相同的加密函数。每个轮次使用不同的48位密钥（$K_1$到$K_{16}$），56位密钥被分成16个48位的子密钥，每个子密钥用于一个轮次。而且每一轮数据会进行左右置换，从而形成新的左右两部分。
在16个轮次加密结束后，数据会进行一个最终置换，从而恢复数据位的原始位置。
具体过程如下图所示。

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/1b13190a2cd44faaa6bef4c1a5b23dc3.png)
DES算法作为美国国家标准技术研究所（NIST）于1993年发布的加密标准。DES使用56位密钥和64位明文输入，采用分组密码和密码块链接模式。由于计算能力的提升，DES的56位密钥长度已经不足以提供足够的安全性。在DES挑战中，人们成功地在不到一天的时间内通过穷举法破解了一个使用56位密钥加密的短语，这凸显了DES的安全性不足。
为了加强DES的安全性，人们提出了3DES（Triple DES）算法。3DES使用了三个不同的密钥对数据进行三次加密，大大提高了安全性。

#### 6.2.2.2 AES（Advanced Encryption Standard，高级加密标准）
2001年11月取代了DES（数据加密标准）。
AES算法使用128位的数据块进行加密处理，并支持使用128位、192位或256位的密钥。
使用暴力破解的电脑对DES破解需要花费1s的情况下，破解AES需要花费149万亿年。

### 6.2.3 Public key cryptography（公共密钥加密）
对称密钥加密算法需要发送方和接收方共享一个秘密密钥。那么问题来了，如果发送方和接收方之前从未见过面，他们如何在第一次通信时就达成共识并获得这个共享的密钥呢？这就是对称密钥加密算法所面临的一个挑战。
公钥加密算法采用了一种截然不同的方法来解决这个问题。它使用了Diffie-Hellman和RSA等算法，发送方和接收方不需要共享一个秘密密钥。在公钥加密算法中，每个人都有一对密钥：一个公钥和一个私钥。公钥是公开的，所有人都可以知道，而私钥则只有接收方知道。
当发送方想要发送加密消息给接收方时，他们可以使用接收方的公钥对消息进行加密。只有接收方拥有相应的私钥才能解密这条消息。
如下图所示。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/527551c20961492cb6a8ce3f3be2d374.png)
因此现在公钥加密算法需要满足两个条件：
1.公钥$K^+_B$和私钥$K_B^-$满足$K_B^-(K_B^+(m))=m$。
2.无法利用公钥$K^+_B$去计算私钥$K_B^-$。

#### 6.2.3.1 RSA（Rivest, Shamir, Adleman）
这是一种基于大数分解难题的非对称加密算法，它使用公钥和私钥进行加密和解密。
RSA算法的核心是modular arithmetic（模运算）。
当我们说$x \ mod \ n$，意思是x除以n得到的余数。
模运算有以下规律：
$[(a \ mod \ n) + (b \ mod \ n)]  \ mod \  n = (a + b)  \ mod \ n$
$[(a \ mod \ n) - (b \ mod \ n)]  \ mod \ n = (a  - b) \ mod \  n$
$[(a \ mod \ n) * (b \ mod \ n)] \ mod \ n = (a * b) \ mod \ n$
我们主要用到的是以下规律：
$(a \ mod \ n)^d \ mod \ n = a^d \ mod \ n$
例如：$x=14,n=10,d=2$
$(x \ mod \ n)^d \ mod \ n = 4^2 \ mod \  10 = 6$
$x^d = 14^2 = 196$，$x^d \ mod \ 10 = 6$

RSA算法会先将bit转换为对应的整数，也就是加密信息相当于是加密这个对应的整数。
例如$m = 10010001$，那这个信息可以转换为十进制数$145$。

具体步骤如下：
1.选择两个大prime number（素数）$p$和$q$。这两个素数通常会非常大，比如每个素数都有1024位。
2.计算$n = pq$，以及$z = (p-1)(q-1)$。
3.选择一个整数$e$（$e<n$），并且$e$与$z$没有公共因子，也就是说它们互质。
4.选择一个整数$d$，使得$ed-1$能够被$z$整除，或者说$ed \ mod \ z = 1$。
5.生成的公钥就是由$(n,e)$组成，而私钥则是由$(n,d)$组成。

现在我们将这个公钥和密钥放到加密和解密中：
1.加密明文$m(m<n)$，
加密得到密文$c = m ^ e \ mod \ n$
2.解密密文$c$，
解密得到明文$m = c ^ d \ mod \ n$
我们可以发现$m = (m ^ e \ mod \ n)^ d \ mod \ n$

具体示例如下：
Bob选择$p=5,q=7$计算得到$n=35,z=24$，所以选择了$e=5$，然后选择了$d=29$
现在加密8-bit的信息。
明文是00001100所以对应的$m=12$，$m^e=24832$，所以密文$c=m^e \ mod \ n = 17$
当收到密文17后，我们进行解密。
$c=17, c ^d = 481968572106750915091411825223071697$，所以明文$m=c^d \ mod \ n = 12$

为什么$c^d \ mod \ n = m$，$c = m^e \ mod \ n$？
这里有一个模运算的规律：$x^y \ mod n = x^{(y \ mod \ z)} \ mod \ n$，其中$n= pq,z = (p-1)(q-1)$。
因此，$c^d \ mod \ n = (m^e \ mod \ n)^d \ mod \ n=m^{ed} \  mod \ n = m ^ {(ed \ mod \ z)} \ mod \ n = m ^ 1 \ mod \ n=m$（最后一步是因为$m<n$）

RSA还有一个重要性质：$K_B^-(K_B^+(m)) = m = K_B^+(K_B^-(m))$
证明如下： $(m^e \ mod \ n)^d \ mod \ n = m^{ed} \ mod \ n = m^{de} \ mod \ n= (m^d \ mod \ n)^e \ mod \ n$

我们现在保证了前面说的两个条件的第一条，现在我们来看在知道Bob的公钥$(n,e)$的情况下，有多难去确定私钥$d$。
要想知道私钥$d$，实际上是要找到$n$的因子，而不知道$n$的两个因子$p$和$q$。这是一个非常困难的问题，因为大数的因数分解是一项非常复杂的计算任务。

RSA中的幂运算是计算密集型的，而DES加密算法至少比RSA快100倍。因此，在实际应用中，可以使用公钥加密算法来建立安全连接，然后建立第二个对称会话密钥，用于加密数据。
在这种情况下，Bob和Alice使用RSA来交换对称密钥KS。一旦双方都拥有了KS，他们就会使用对称密钥加密算法来进行通信，因为对称密钥加密算法在加密和解密速度上通常比公钥加密算法快得多。
因此我们使用混合加密，使用非对称加密算法来安全地交换对称密钥，对称加密算法来加密实际的数据通信，从而兼顾了安全性和效率。

## 6.3 Authentication and Message integrity（认证和信息完整性）
### 6.3.1 Authentication（认证）
Authentication protocol（认证协议）1.0：Alice说“我是Alice”。
在这种简单的认证协议下，存在一个潜在的安全漏洞，即在网络环境中，由于缺乏直接的身份验证，Trudy可以冒充Alice，而Bob无法直接验证真实身份。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/53fdcdacbfda42ea907cce9213deae2b.png)
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/7744d878631f4c12b806cc7491d42876.png)
现在Authentication protocol（认证协议）2.0：Alice在声明身份的同时，数据包包含她的源IP地址。
同样这里存在安全隐患。Trudy可以伪造一个包含AliceIP地址的数据包，并在其中声明自己是Alice。这种行为被称为IP spoofing（IP欺骗）。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/092e1f5456d342b2bbce4cbd6841d7b8.png)
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/6453bd68e11a43d7b37b879e70ca813b.png)
现在Authentication protocol（认证协议）3.0：Alice现在声明身份的时候还发送私密密码来证明她的身份。
但这里还存在问题，Trudy可以records（截获）Alice的认证数据包，然后稍后将这个数据包发送给鲍勃，以冒充爱丽丝。这种行为叫playback attack（重放攻击）。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/65f0e00c303d4ce3ae7e6ab013f836cf.png)
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/dce0d8c8258642fcb20c6c44f7dc373f.png)
那我们如果将密码进行加密呢？
Authentication protocol（认证协议）3.1：Alice现在声明身份的时候发送的是加密的密码。
这种方式无法解决上述所说的playback attack（重放攻击）。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/a60e7de0aaa2404e9bd64e0ce964117e.png)
我们现在尝试Authentication protocol（认证协议）4.0尝试能解决playback attack（重放攻击）问题：
我们现在使用nonce（一次性随机数）$R$。
Bob现在会发送一个一次性随机数$R$给Alice，Alice必须使用他们之间共享的秘密密钥加密这个随机数并返回给Bob。这样，Bob可以确认Alice是活跃的。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/1b8e911b285e4ce5a9b1c59ab7784821.png)
但这种协议还是存在问题。例如，如果攻击者能够截获共享密钥，或者如果爱丽丝的响应时间可以被精确预测，那么这种协议可能仍然面临安全风险。

Authentication protocol（认证协议）4.0使用的是对称密钥加密，那我们是否可以使用公共密钥加密来提高安全性呢？
Authentication protocol（认证协议）5.0：使用nonce（一次性随机数）$R$和公共密钥加密。
Alice首先声明她的身份，然后Bob发送给Alice一个nonce（一次性随机数）$R$，爱丽丝使用她的私钥$K_A^-$加密nonce（一次性随机数）$R$并发送结果$K_A^-(R)$给Bob。然后Bob发送一条信息给Alice，让Alice将公钥$K_A^+$发给Bob。Bob在收到$K_A^+$后，使用$K_A^+$进行解密，得到$K_A^+(K_A^-(R))=R$。
如果解密结果与原始的一次性随机数$R$相匹配，说明与Bob通信的的确是Alice。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/38a6788c8a28440e83bc0e6455378db1.png)
但这还是存在一个安全漏洞，这个漏洞允许man（or woman）in the middle attack（中间人攻击）。
man（or woman）in the middle attack（中间人攻击）是Trudy作为中间人冒充Alice与Bob通信，同时冒充Bob与爱丽丝通信。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/2a867bf6f6094cadb985e05686122547.png)
这种攻击很难被检测到，因为Bob和Alice都会收到对方发送的所有信息。问题在于Trudy作为中间人，也会收到所有的消息。

### 6.3.2 Message integrity（信息完整性）
#### 6.3.2.1 Digital signatures（数字签名）
数字签名是一种cryptographic technique（密码学技术），类似于手写签名的作用：
发送方（比如Bob）使用数字签名技术对文件进行签名，从而确认他是文件的所有者或创建者。 
数字签名是verifiable（可验证）且nonforgeable（不可伪造的）：接收方（比如Alice）可以向他人证明，只有Bob而不是任何其他人（包括Alice在内）对文件进行了签名。

简单的对信息$m$进行数字签名的方法如下：
Bob使用它的私钥$K_B^-$对信息$m$加密，从而创建一个“签名”信息$K_B^-(m)$
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/4cec4a839c1d46d6b0291da26352a10a.png)
首先假设Alice收到了信息$m$以及使用Bob的私钥进行签名的数字签名$K_B^-(m)$。
Alice使用Bob的公钥$K_B^+$对数字签名$K_B^-(m)$进行解密，然后检查$K_B^+(K_B^-(m))$是否等于$m$。如果$K_B^+(K_B^-(m))=m$，那么就意味着对消息$m$进行签名的人必须使用了Bob的私钥。
因此，Alice可以确认以下几点：
1.Bob签署了消息m。
2.没有其他人签署了消息m。
3.Bob签署了消息m而不是其他消息m’。
这种特性被称为non-repudiation（不可否认性），意味着Alice可以携带消息$m$和数字签名$K_B^-(m)$到法庭上，证明消息m是由Bob签署的。

#### 6.3.2.2 Message digests（信息摘要）
由于使用公钥加密长消息的计算成本较高，因此消息摘要的目标是生成fixed-length（固定长度）且easy-to-compute（易于计算）的数字“指纹”。
具体来说，对消息$m$应用哈希函数H会产生一个固定长度的消息摘要，记为$H(m)$。

哈希函数的一些属性包括：
1.多对一：多个不同的消息可能会产生相同的消息摘要，这称为哈希碰撞。
2.产生固定长度的消息摘要（指纹）。
3.给定消息摘要x，计算出使得x = H(m)的消息m在计算上是不可行的。即从信息摘要逆向推导出原始信息的过程是困难的。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/38e904d4e77f438b99cdb25ed06dc057.png)
因此我们现在结合信息摘要到数字签名上，即通过加密信息摘要实现数字签名。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/98902afdcc3a43b89f0d1364e5387bfb.png)
Bob首先对他的原始信息$m$应用一个哈希函数$H$从而生成信息摘要$H(m)$。Bob使用他的私钥对信息摘要进行加密生成数字签名$K_B^-(m)$。

Alice接收到加密的信息摘要和Bob的公钥。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/de385415fcf44b02bd0cb27c1593a50f.png)
爱丽丝使用Bob的公钥解密收到的数字签名，恢复出信息摘要$H(m)$。爱丽丝对收到的原始信息$m$再次应用哈希函数，生成新的信息摘要$H(m)$。如果两者相等，则验证了消息的完整性和Bob的身份。

Checksum（校验和）和哈希函数有一些相似的地方，但并不完全相同：
1.生成了一个固定长度的摘要（16位的信息和）。
2.是多对一的。
但是Checksum（校验和）很容易找到其他不同的信息与以一个信息有一样的哈希值，如下图例子所示。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/5e4238b6d49b415dbcdc754fda872c80.png)
哈希函数算法中常用的是MD5和SHA-1。
MD5（Message Digest Algorithm 5）是一种广泛使用的哈希函数，它能够以4步过程计算出128位的消息摘要。MD5算法的特性之一是，对于任意的128位字符串x，构造一个使得其MD5哈希等于x的消息m似乎是困难的。
另外一种常用的哈希函数是SHA-1（Secure Hash Algorithm 1），它是美国国家标准技术研究所（NIST）发布的标准（FIPS PUB 180-1）。SHA-1算法能够生成160位的消息摘要。

我们现在再回到之前Authentication protocol（认证协议）5.0中。如果我们直接将这里的数字证书的方式加进通信之中，我们依然无法解决man（or woman）in the middle attack（中间人攻击）。
例如：
Trudy伪造了一封电子邮件订单，假装是Bob发送的订购四份意大利辣香肠披萨的订单，并用自己的私钥对订单进行签名。接着，Trudy将伪造的订单发送给了披萨店，并同时发送了她自己的公钥，但声称这是Bob的公钥。
披萨店收到订单后，使用所谓的Bob的公钥来验证签名，并认为这是Bob发送的订单，于是按照订单要求将四份意大利辣香肠披萨送到了Bob的地址。
然而，实际上Bob并不喜欢意大利辣香肠披萨，而这个订单是由Trudy伪造的。

因此需要像现实世界有第三方权威认证。即Public-key certification（公钥认证）。
在Public-key certification（公钥认证）中，certification authority（CA，数字证书颁发机构）负责将公钥与特定实体$E$（比如个人、路由器等）进行绑定。
具体步骤如下：
实体$E$（比如个人、路由器等）向CA注册其公钥，并提供“身份证明”以证明自己的身份。CA在确认实体$E$的身份后，会创建一个certificate（数字证书），将实体$E$与其公钥进行绑定，并由CA进行数字签名。这个certificate（数字证书）包含了实体$E$的公钥，并且经过了CA的数字签名，以确保数字证书的真实性和完整性。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/3b3d2044e56a470089719a5564505acd.png)
当Alice需要Bob的公钥时，她可以获取Bob的证书。
Alice获取Bob的证书，这可以来自Bob本人或其他地方。
Alice使用认证机构的公钥解密Bob的证书，从而获取Bob的公钥。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/1b5730bcda04439da41824309fc5013c.png)

## 6.4 Securing e-mail
Alice想要发送一个保密的电子邮件给Bob。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/707e326e5ee04d28a312a3a42998b037.png)
Alice首先使用一个随机生成的堆成私钥$K_S$来加密信息$m$，得到$K_S(m)$。
再使用Bob的公钥$K_B^+$加密对称私钥$K_S$，得到$K_B^+(K_S)$。
将加密后的信息$K_S(m)$和$K_B^+(K_S)$一起发送给Bob。
Bob收到后可以使用自己的私钥$K_B^-$解密得到$K_S$然后再对用解密得到的对称密钥解密加密的信息从而得到信息$m$。

Alice想要提供发送者身份验证和消息完整性。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/89584844df1840d4902b79dd63b7359f.png)
Alice使用哈希函数生成信息对应的信息摘要。
Alice再使用她的私钥$K_A^-$对信息摘要进行加密，生成数字签名$K_A^-(H(m))$。
Alice将原始消息和数字签名一起发送。
Bob收到后，使用Alice的公钥$K_A^+$对$K_A^-(H(m))$进行解密从而得到$H(m)$，并使用相同的哈希函数计算收到的信息$m$的信息摘要$H(m)$，然后对两者进行比较。

因此这两步合在一起就完成了一个安全的信息发送。
Alice希望确保她的电子邮件内容保密，发送者的身份得到验证，以及消息在传输过程中的完整性。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/29f7e04b757d4270a5e78e5e62631052.png)
在这个过程中，Alice使用了自己的私钥，Bob的公钥，以及新创建的对称密钥。

## 6.5 Securing TCP connections：SSL
SSL（Secure Sockets Layer）是一种广泛部署的安全协议，它被几乎所有的浏览器和网络服务器支持，并且通常用于保护Web通信。
SSL协议的实现最初由Netscape公司提出，并在1994年由Taher Elgamal等人发表了相关的机制。后来，SSL协议的进化版本是TLS（Transport Layer Security），它在RFC 2246中进行了标准化。
SSL/TLS协议最初的目标是为Web电子商务交易提供安全保障，包括加密敏感信息、Web服务器认证以及可选的客户端认证。此外，SSL/TLS协议还可以应用到所有基于TCP的应用程序中，提供安全的通信接口。

SSL提供了confidentiality（保密性）、integrity（完整性）、authentication（认证）。

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/03694a3b7c0448f5a920715cbbf1db0b.png)

SSL提供应用程序编程接口(API)给应用程序。在C和Java编程语言中，SSL库/类可以随时使用。

### 6.5.1 Toy SSL（简单安全套接层）
Toy SSL（简单安全套接层）是一个简单的安全通道协议。
该协议包括四个阶段，分别是：
1.Handshake（握手）：Alice和Bob使用各自的证书和私钥来相互认证，并交换生成一个共享的秘密。
2.Key derivation（密钥派生阶段）：Alice和Bob使用共享的秘密来派生一组密钥，这些密钥将用于对通信数据进行加密和解密。
3.Data transfer（数据传输阶段）：要传输的数据被分割成一系列的记录，每个记录将使用在密钥派生阶段生成的密钥进行加密，以确保数据在传输过程中的保密性和完整性。
4.Connection closure（连接关闭阶段）：在关闭连接时，双方会发送特殊的消息来安全地终止通信连接，以确保最后的数据传输完整性和安全性。

#### 6.5.1.1 Handshake（握手阶段）
Alice需要做以下几件事情：
1.与Bob建立一个TCP连接。
2.验证Bob确实是Bob。
3.给Bob发送一个master secret key（主密钥）。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/2b13bc61c0cf48e1875e73f61f9e6628.png)
MS是Master Secret是Alice想要分享给Bob的共享秘密。EMS是加密的master secret key（主密钥），因为是使用Bob的公钥加密的，所以只有Bob才能够解密获取master secret key（主密钥）。

#### 6.5.1.2 Key derivation（密钥派生阶段）
考虑到使用同一个密钥进行多个加密操作是不安全的。
因此对message authentication code（MAC，信息身份验证码）和加密使用不同的密钥。
注意：这里的MAC不是前面链路层里的MAC。
MAC的计算方式如下：
$MAC = H（m+s）$，其中$m$是信息，$s$是MAC密钥，两者结合在一起后通过哈希函数$H$进行处理。

从MS（Master Secret）中生成四个密钥：
1.$K_c$用于客户端到服务器的数据加密。
2.$M_c$用于客户端到服务器的数据的MAC。
3.$K_s$用于服务器到客户端的数据加密。
4.$M_s$用于服务器到客户端的数据的MAC。

Key Derivation Function（KDF，密钥派生函数）用于从主密钥生成子密钥。
KDF使用master secret（MS）以及可能一些额外的随机数据来创建这些密钥。

####  6.5.1.3 Data transfer（数据传输阶段）
要传输的数据被分割成一系列的记录进行传输。

为什么不直接以恒定流的形式加密数据？
这是因为在TCP传输过程中，数据通常是以数据包（packet）的形式进行传输的，而不是恒定的流。因此，在TCP层面上直接对数据进行加密是不太实际的。另外，在网络传输中，数据包的大小和传输速率是变化的，所以直接对恒定流进行加密不符合实际情况。
如何在数据传输过程中保证消息的完整性？如果将消息认证码（MAC）放在数据的末尾，那么在所有数据被处理之前，接收方将无法验证消息的完整性。比如在即时通讯中，接收方如何在显示消息之前对所有发送的字节进行完整性检查呢？因此，需要一种机制来确保消息在传输过程中的完整性。

我们的解决方案就是将数据流分割成一系列的records（记录），每个记录携带一个消息认证码（MAC）。
这样接收方可以在每个记录到达时立即对其进行处理，而不需要等到所有数据都到达后再进行处理。然而，这种方法的一个问题是接收方需要能够区分记录中的消息认证码和数据，因此需要使用可变长度的记录。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/49e49f2ecd9347b0a323963766d1999d.png)
我们现在有一个新的问题，攻击者可以捕获并重放记录，或者重新排序记录，从而对通信造成干扰。
为了解决这个问题，可以将序列号包含在MAC中，即MAC$= H(M_x, sequence || data)$，这样可以确保每个记录的完整性和顺序性。
注意：记录中并不需要包含序列号字段，而是将序列号与数据一起作为MAC的输入。

然而，即使使用了序列号，攻击者仍然可以通过重放所有记录来进行攻击。为了进一步加强安全性，可以引入nonce（一次性数字）。通过在每个记录中包含一个nonce，并在MAC计算中使用该nonce，可以确保每个记录只能被处理一次，从而防止重放攻击。

#### 6.5.1.4 Connection closure（连接关闭阶段）
但我们现在依然有一个问题，在传统的TCP连接中，中间人攻击者可以伪造TCP连接关闭段（FIN），导致通信双方中的一方或双方认为数据比实际少。为了解决这个问题，可以使用不同的记录类型来表示数据传输和连接关闭，例如使用类型0表示数据记录，使用类型1表示连接关闭记录。

所以我们现在得到了MAC$= H(M_x, sequence || type || data)$。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/70d49875a310471eb1863f35b6643e37.png)

#### 6.5.1.5 Summary
因此Alice先与Bob建立TCP连接。
然后Bob发送他的数字证书和一个nonce（一次性数字），从而验证Bob的身份与保证会话的唯一性。
然后Alice用Bob的公钥加密后给Bob发送一个master secret key（主密钥）。
然后Alice发送第一个数据包，类型为0，序列号为1。
然后Alice发送第二个数据包，类型为0，序列号为2。
然后Bob发送第一个数据包，类型为0，序列号为1。
然后Alice发送第三个数据包，类型为0，序列号为3。
然后Alice发送关闭信息，类型为1，序列号为4，表示想要关闭SSL对话。
最后Alice发送关闭信息，类型为1，序列号为2，确认关闭SSL对话。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/f2e463c5477844fcb769e6f897e5bced.png)
我们现在还需要考虑几个问题：
1.字段的长度是多少？
2.使用哪种加密协议？
3.客户端和服务器需要进行协商以确定加密选择的算法。

因此有SSL cipher suite，指的是SSL协议中使用的一组加密算法和协议组合。
它包括以下几个部分：
1.Public-key algorithm（公钥算法）。
2.Symmetric encryption algorithm（对称加密算法）。
3.MAC algorithm（MAC算法）。
SSL协议支持多种cipher suites，通常在通信开始时，客户端和服务器会进行协商，以确定双方支持的cipher suite。客户端会提供一系列支持的cipher suites，而服务器会从中选择一种最适合的cipher suite。

在SSL中，常见的对称加密算法包括：
DES（Data Encryption Standard）：是一种Block cipher（块密码），以64位分组的方式进行加密和解密。
3DES（Triple Data Encryption Standard）：是一种Block cipher（块密码），通过对数据进行三次DES加密来增强安全性。
RC2（Rivest Cipher 2）：是一种Block cipher（块密码），以变长的密钥对数据进行加密和解密。
RC4（Rivest Cipher 4）：是一种Stream cipher（流密码），以变长的密钥对数据进行加密和解密。
块密码和流密码的区别在于块密码以固定长度的数据块为单位进行加密，而流密码以比特流为单位进行加密。
常见的公钥加密算法包括RSA。

### 6.5.2 Real SSL
在现实中SSL的握手阶段需要完成以下目标：
1.Server Authentication（服务器认证）：客户端验证服务器的身份，以确保其正在与预期的服务器进行通信，而不是中间人或恶意攻击者。
2.Negotiation：agree on crypto algorithms（协商）：定双方将使用的加密算法和参数。
3.Establish keys（建立密钥）：客户端和服务器将使用协商得到的参数来生成会话密钥，用于加密和解密通信中的数据。
4.Client authentication（客户端认证）：这一步不是必须的。在一些情况下，服务器可能需要验证客户端的身份。

具体过程如下：
1.客户端发送支持的加密算法列表，以及客户端的随机数。
2.服务器从客户端发送的加密算法列表中选择一个，并向客户端返回选择的加密算法、服务器的数字证书以及服务器的随机数。
3.客户端验证服务器的数字证书，提取服务器的公钥，生成预主密钥（pre_master_secret），然后使用服务器的公钥对预主密钥进行加密，并发送给服务器。
4.客户端和服务器分别使用预主密钥和各自的随机数计算出加密密钥和消息认证码（MAC）密钥。
5.客户端将所有握手消息的MAC值发送给服务器，用于验证握手消息的完整性。
6.服务器将所有握手消息的MAC值发送给客户端，用于验证握手消息的完整性。

在第一步，客户端通常会以明文形式发送一系列加密算法，其中包括一些强加密算法和一些弱加密算法。
中间人攻击者可以删除客户端发送的加密算法列表中的强加密算法，从而迫使客户端和服务器使用较弱的加密算法进行通信。
最后两个步骤（第5步和第6步）的目的是防止这种中间人攻击。在这两步中，客户端和服务器会相互发送握手消息的消息认证码（MAC），以验证握手消息的完整性。
因此最后两步的信息是加密的。

那为什么需要使用两个分别的随机数呢？
这样做的目的是为了防止有中间人攻击者能够截获并重放先前的握手消息。
每次连接都使用不同的随机数，因此会导致不同的会话密钥，从而使加密密钥不同，导致中间人攻击者无法成功地重放先前的通信。

因此真实的SSL连接的情况如下。红色部分都是加密的。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/0e4d7922700342649908440e8f6ae636.png)

## 6.6 Network layer security：IPsec
当发送实体加密数据报的有效载荷时，可以包括各种类型的数据，例如TCP或UDP段、ICMP消息、OSPF消息等。加密确保了从一个实体发送到另一个实体的所有数据（包括网页、电子邮件、P2P文件传输、TCP SYN数据包以及任何其他形式的通信）都对任何试图拦截或“嗅探”网络流量的第三方进行了隐藏。
网络层保密性正式实现了对所有网络实体之间通信安全的全面覆盖。

### 6.6.1 Virtual Private Networks（VPNs，虚拟专用网络）
机构通常需要私人网络以确保其内部通信和数据的安全性和保密性。而部署一个完全与公共互联网分离的独立物理网络成本较高，需要独立的路由器、链路和DNS基础设施。
机构可以使用VPN将其办公室之间的流量发送到公共互联网上。在进入公共互联网之前，流量会被加密，确保其保持安全和私密。这使得机构能够在不需要维护独立的物理网络的情况下获得私人网络的安全性优势。
通过VPN发送的流量在公共互联网上逻辑上与其他流量分开，进一步增强了机构通信的隐私性和安全性。
下图展示了一个VPN（虚拟专用网络）。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/2c1e4129f9294ad48404e155bbd4c748.png)
### 6.6.2 IPsec services（IPsec的服务）
IPsec（Internet Protocol Security）提供了一系列安全性服务，其中包括：
1.Data integrity（数据完整性）。
2.Origin authentication（发起者认证）。
3.Replay attack prevention（防止重放攻击）。
4.Confidentity（保密性）。

IPsec通过两种不同的协议来提供不同的服务模型：
Authentication Header（AH，认证头）：提供源认证和数据完整性，但不提供保密性。
Encapsulation Security Payload（ESP，封装安全载荷）：提供源认证、数据完整性和保密性。这个比AH更为广泛使用。

### 6.6.3 IPsec mode（IPsec的工作模式）
#### 6.6.3.1 Transport mode（传输模式）
Transport mode（传输模式/主机模式）是IPsec数据包由端系统发出并由端系统接收。这意味着加密和解密过程发生在端系统的主机上，而不是在中间的路由器或防火墙上。
IPsec传输模式保护IP数据包中的高层协议，如TCP、UDP、ICMP等。

IPsec封装在IP数据包的IP头之后，但位于传输层（如TCP或UDP）头之前。这种模式通常用于端到端的通信，其中两个通信端点都需要配置IPsec。传输模式适用于以下场景：
远程访问VPN，其中远程用户通过VPN连接到公司网络。
站点到站点的VPN，其中两个远程站点通过VPN连接。
直接在两台主机之间建立安全连接。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/6bd330e58f3b4627ad67c1acf25dad16.png)
#### 6.6.3.2 Tunneling mode（隧道模式）
Tunneling mode（隧道模式）是在两个网络之间创建一个加密的隧道，通过公共网络（如互联网）安全地传输数据。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/49142d833d0746baa2fdd16f1e89f263.png)
边缘路由器是IPsec感知的，意味着它们能够识别和处理IPsec封装的数据包。这些路由器负责在两个网络之间创建和管理加密隧道。
主机（如计算机或服务器）也是IPsec感知的，它们能够直接使用IPsec服务。这意味着主机可以参与IPsec隧道的建立和维护。

IPsec在网络层（IP层）创建一个虚拟的点对点连接。数据包被封装在新的IP头内，然后通过公共网络传输。在接收端，数据包被解封装，恢复原始数据。

因此我们现在有两种工作模式和两种协议，我们现在将它们排列组合获得的四种结果，都是IPsec的可选方案，即：
Host mode with AH（传输模式+AH）
Host mode with ESP（传输模式+ESP）
Tunnel mode with AH（隧道模式+AH）
Tunnel mode with ESP（传输模式+ESP）
其中Tunnel mode with ESP（传输模式+ESP）是最常用且在许多情况下最重要的配置。

### 6.6.4 Security associations（SAs，安全关联）
Security associations（SAs，安全关联）是在发送数据之前从发送方到接收方实体建立的。安全关联是simplex（单向的），即为每个方向建立一个逻辑连接。
发送和接收实体会维护有关安全关联的状态信息。需要注意的是，TCP端点也会维护状态信息，但IP是无连接的，而IPsec是面向连接的。
下图展示了一个从路由器$R_1$到路由器$R_2$建立安全关联的例子。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/1aee650635614dc499a5d0f38ee9736c.png)
$R_1$为SA存储了以下信息：
1.一个32位的标识符: Security Parameter Index (SPI，安全参数索引)，用于唯一标识一个SA。
2.发起SA的接口(200.168.1.100)。
3.目的地SA的接口(193.68.2.23)。
4.使用的加密类型 ：例如3DES加密算法与CBC（密码块链）模式。
5.用于加密的密钥。
用于数据完整性检查的类型：例如使用MD5的HMAC（消息认证码）。
6.用于认证的密钥。
这里$R_2$也会创建一个对应的安全关联。

在IPsec中，Security Association Database（SAD，安全关联库）是用来

通过建立安全关联，通信双方可以协商和确认使用的安全参数，包括加密算法、认证机制和密钥等。这样可以确保数据在传输过程中不被篡改、窃听或伪造，并且确保通信双方的身份得到验证。从而确保IPsec通信的安全性和完整性。
存储和管理安全关联（SA）状态信息的地方。每个通信端点都会在SAD中维护与其相关的安全关联，以便在处理IPsec数据报时能够找到相应的安全关联信息。

在一个特定的网络拓扑中，如果有n个销售人员，那么在路由器R1的SAD中会有2+2n个安全关联。当路由器R1发送IPsec数据报时，它会访问SAD来确定如何处理数据报。而当IPsec数据报到达路由器R2时，R2会检查数据报中的安全参数索引（SPI），然后使用这个SPI去SAD中索引相应的安全关联信息，并根据这些信息来处理数据报。

### 6.6.5 IPsec datagram
我们接下来讨论是最常用的隧道模式+ESP协议。
在隧道模式下，整个原始IP数据报被封装在一个新的IP数据报中，并通过ESP进行加密和认证。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/b5cd6688e43d468d86d94612607b04e6.png)
蓝色部分是原始数据包部分，这部分使用ESP进行加密。从原始的IP头开始，一直到ESP尾部，ESP尾部包含了padding（填充）、pad length（填充长度）、next header（下一个头部字段）。
padding（填充）：用于确保ESP数据报的长度是加密块大小的整数倍，这是某些加密算法的要求。
pad length（填充长度）：指示填充的大小。
next header（下一个头部字段）：指示原始IP数据报的下一个协议字段。
ESP hdr（ESP头部）：ESP头部包含了安全参数，如SPI（Security Parameters Index，安全参数索引）和序列号（Seq #），用于加密和认证过程。
SPI：是一个32位的值，用于唯一标识一个特定的安全关联（SA），即两个通信实体之间的安全策略。
Seq #（序列号）：用于确保数据报的顺序，对于新的安全关联（SA），发送方将序列号初始化为0。每次在SA上发送数据报时，发送方会递增序列号计数器，并将其放置在序列号字段中。序列号的目的是防止攻击者窃听并重放数据包，因为接收到的重复、经过认证的IP数据包可能会干扰服务。这不是跟踪所有接收到的数据包实现的，而是使用一个window（窗口）来处理序列号，从而目标端检查是否有重复的数据包。
ESP MAC（ESP消息认证码）：用于验证数据报的完整性和真实性，确保数据在传输过程中没有被篡改。
然后这个数据包被封装在一个新的数据包内，所以添加了一个新的IP头部，包含了隧道的源和目的IP地址。使用了一个共享的在安全关联中配置的密钥来创建。

在下图这样的场景中。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/42d8573c04014e049e1be21beb8ad4b8.png)
首先$R_1$将原始数据报的后面附加一个ESP（Encapsulating Security Payload）尾部字段，这个尾部字段包含了原始数据报的所有头部字段。然后，使用安全关联中指定的算法和密钥对结果进行加密。
然后将加密后的数据量的前面附加一个ESP头部，从而形成了所谓的"enchilada"。ESP头部包含了有关加密和认证的必要信息。
接着对整个"enchilada"进行认证，使用安全关联中指定的算法和密钥生成认证MAC。
然后将认证MAC附加到"enchilada"的后面，形成了负载。
最后在负载的前面创建一个全新的IP头部，包括所有经典的IPv4头部字段，然后将负载附加到这个IP头部的后面。

Security Policy Database（SPD，安全策略数据库），SPD中的策略指示了发送实体在发送特定数据报时是否应该使用IPsec协议（加密和认证）或者普通的IP协议（未加密和未认证）。
此外，SPD还需要指示发送实体应该使用哪个安全关联（SA）来保护数据报。这些信息可能基于数据报的源IP地址、目的IP地址以及协议号等条件来确定。
与SPD不同，安全关联数据库（SAD，Security Association Database）中存储了关于如何处理特定安全关联的信息。这些信息包括了加密算法、密钥等细节，指示了如何对数据报进行加密和认证。
因此，SPD中存储了关于对于到达的数据报应该执行什么样的安全策略，而SAD中存储了关于如何执行这些安全策略的详细信息。

### 6.6.6 Summary
Trudy不知道密钥，因此她无法解密IPsec加密的数据报，因此她无法查看原始数据报的内容。
IPsec保护了源IP地址、目的IP地址、传输协议和应用程序端口等信息，因此Trudy也无法查看这些信息。
IPsec提供了数据完整性保护，因此Trudy无法在不被检测到的情况下对数据报进行修改。
IPsec提供了身份验证，因此Trudy无法伪装成R1，使用R1的IP地址进行通信。
IPsec使用序列号来防止重放攻击，因此Trudy无法成功地重放数据报。

之前的例子展示了手动建立IPsec安全关联（SA）的过程，包括了安全关联的参数和密钥等信息。
然而，当涉及到具有数百个终端点的VPN时，手动密钥协商变得不切实际。因此，IPsec引入了IKE协议，其规范定义在RFC 5996中。
IKE消息交换用于协商算法、密钥和安全参数索引（SPI号）。
IPsec可以使用AH（认证头）协议、ESP（封装安全载荷）协议，或者两者同时使用。
AH协议提供数据完整性和源认证，用于验证数据报的完整性并确认发送方的身份。
ESP协议除了提供AH协议的功能外，还额外提供了加密功能，用于保护数据报的机密性。
IPsec的对等体可以是两个终端系统、两个路由器/防火墙，或者是一个路由器/防火墙和一个终端系统，这意味着IPsec可以在各种网络设备之间建立安全通信。

## 6.7 Operational security：firewalls and IDS（运行安全：防火墙和入侵检测系统IDS）
### 6.7.1 Firewalls（防火墙）
防火墙将组织的内部网络与更大的互联网隔离开来，以保护内部网络不受外部威胁的影响。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/f73e948b1b85478dbc8112ebfaa482bf.png)
防火墙被用来区分“好家伙”和“坏家伙”。“好家伙”指的是受信任的内部网络用户，而“坏家伙”则指的是不受信任的外部互联网用户。防火墙的作用是确保只有合法的、符合安全策略的流量能够进入内部网络，从而保护组织的信息资产免受潜在的网络攻击和入侵。

防火墙的作用包括：
1.Prevent denial of service attacks（避免拒绝服务攻击）：防火墙可以防止SYN洪水攻击，这是一种攻击者通过建立大量伪造的TCP连接，使得系统没有足够资源来处理真实的连接请求的攻击方式。
2.Prevent illegal modification/access of internal data（组织对内部数据的非法修改和访问）：例如，防火墙可以防止攻击者替换CIA的主页等非法行为。
3.Allow only authorized access to inside network（仅允许授权访问内部网络）：防火墙可以设置认证用户/主机的白名单，只允许经过授权的用户或主机访问内部网络资源。

防火墙的类型有：
1.Stateless packet filters（无状态数据包过滤器）。
2.Stateful packet filters（有状态数据包过滤器）。
3.Application gateways（应用程序网关）。

#### 6.7.1.1 Stateless packet filters（无状态数据包过滤器）
内部网络通过路由防火墙连接到互联网。
路由器按数据包逐个进行过滤，根据以下内容做出转发/丢弃决定：
1.源IP地址、目标IP地址。
2.TCP/UDP源和目标端口号。
3.ICMP信息类型。
4.TCP SYN和ACK位。

下面给出几个例子：
例1：阻止具有IP协议字段 = 17且源或目标端口 = 23的数据报文的进出。
结果：所有传入、传出的UDP流量和Telnet连接都被阻止。
IP协议字段为17代表UDP协议，端口号为23通常是Telnet服务的端口号。因此，这个规则的作用是阻止所有使用UDP协议且目标或源端口为23的数据报文进出网络。
例2：阻止具有ACK=0的入站TCP段。
结果：防止外部客户端与内部客户端建立TCP连接，但允许内部客户端连接到外部。
因为ACK=0的数据段通常用于建立连接的初始握手。
例3：丢弃所有发往任意IP地址的端口80（HTTP服务的默认端口）的出站数据包。结果：阻止内部网络的用户访问互联网上的网页。
例4：丢弃所有发往除130.207.244.203（机构公共Web服务器的IP地址）端口80之外的任意IP地址的入站TCP SYN包。
结果：只有该特定Web服务器的TCP连接被接受，其他所有TCP连接都被阻止。
例5：丢弃所有入站的UDP数据包，除了DNS（域名系统）和路由器广播。
结果：防止网络电台等基于UDP的服务占用过多的带宽。
例6：丢弃所有发往“广播”地址（例如130.207.255.255）的ICMP（Internet控制消息协议）数据包。
结果：避免电脑被Smurf攻击（DOS攻击的一种）。
例7：丢弃所有出站的ICMP TTL（生存时间）过期的流量。
结果：防止外部用户使用Traceroute来探测网络的拓扑结构。

Access Control Lists（ACL，访问控制列表）：它定义了哪些类型的网络流量被允许或拒绝通过网络设备。这些规则按照从上到下的顺序应用于进入的网络数据包。每条规则都是一个（动作，条件）对，类似于OpenFlow转发表。
如下图所示。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/ef3a7418e5824ea9b6845e6d0561bfd3.png)
因此最后一行将所有其他未明确允许的流量拒绝（从上到下的顺序）。

#### 6.7.1.2 Stateful packet filters（有状态数据包过滤器）
无状态包过滤是一种简单的过滤机制，它不会跟踪网络连接的状态。它根据预定义的规则对每个数据包进行评估，但不考虑数据包的上下文或之前的网络活动。
这种方法可能会允许一些“无意义”的数据包通过，例如，即使没有建立TCP连接，也允许目标端口为80（HTTP服务的默认端口）且ACK位设置的数据包通过。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/facd8b3844104f81bc8d7e21ea0f129e.png)
有状态包过滤是一种更高级的过滤机制，它会跟踪每个TCP连接的状态。这种过滤方式能够理解网络连接的上下文，包括连接的建立和终止。
确定传入和传出的数据包是否“有意义”，即是否与已建立的连接相匹配。
对不活跃的连接进行超时处理，不再允许相关数据包通过。

所以现在ACL添加了最后一项，要求在允许特定数据包通过之前，需要首先检查连接状态表。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/b06123e44d76493a9be6acc5ab6b87e7.png)
#### 6.7.1.3 Application gateways（应用程序网关）
应用网关可以可以根据具体的应用层协议（如HTTP、FTP、Telnet等）对数据进行检查和过滤，而不仅仅局限于传统的IP、TCP和UDP字段。
例如：允许特定的内部用户通过Telnet访问外部网络。
过程如下：
1.要求所有Telnet用户通过应用网关进行Telnet连接。这样可以集中控制和监控Telnet流量。
2.对于经过授权的用户，应用网关会为其建立到目标主机的Telnet连接，并在两个连接之间转发数据。
3.路由器上的过滤器会阻止所有非应用网关发起的Telnet连接。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/5cea6ce57cb54c1a9e65489fb30a819c.png)
#### 6.7.1.4 Limitations of firewalls, gateways
关于防火墙和网关的局限性如下：
1.IP欺骗：路由器无法确定数据包是否真的来自所声称的源地址。这意味着攻击者可以伪装数据包的源IP地址，绕过防火墙的检测。
2.如果多个应用程序需要特殊处理，那么每个应用程序都需要有自己的应用程序网关。这可能导致部署复杂性和管理开销的增加。
3.客户端软件必须知道如何与网关进行通信。例如，必须在Web浏览器中设置代理的IP地址。
4.过滤器通常对UDP使用全有或全无的策略，这意味着UDP数据包要么完全被允许通过，要么被完全阻止，缺乏细粒度的控制。
5.在通信与外部世界的程度和安全级别之间存在权衡。增加安全性可能会限制与外部世界的通信，而开放通信可能会降低安全性。
6.许多高度保护的站点仍然遭受攻击，这表明即使有防火墙和网关的保护，仍然存在安全漏洞和挑战。

### 6.7.2 Intrusion detection systems（入侵检测系统）
这是一种用于监视网络或系统活动并检测可能的安全事件或违规行为的安全工具。
数据包过滤器通常只检查TCP/IP头部信息，而不深入检查数据包的内容。
而IDS会进行深度数据包检查，例如对数据包中的字符字符串进行检查，以便与已知的病毒或攻击字符串数据库进行比对。
它还可以检查多个数据包之间的关联，以识别可能的攻击模式或行为，包括port scanning（端口扫描）、network mapping（网络映射）、Dos attack（拒绝服务攻击）。
在不同的网络位置部署多个IDS可以提供更全面的安全监控。如下图所示。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/6f69ffa4988847d392680dc5e9ff7e39.png)

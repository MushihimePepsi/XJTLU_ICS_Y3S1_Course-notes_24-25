- [6. 设计概念](#6-设计概念)
  - [6.1 Principle](#61-principle)
  - [6.2 Concepts](#62-concepts)
    - [6.2.1 General design concepts（常见的设计概念）](#621-general-design-concepts常见的设计概念)
      - [6.2.1.1 Abstraction（抽象）](#6211-abstraction抽象)
      - [6.2.1.2 Modularity（模块化）](#6212-modularity模块化)
      - [6.2.1.3 Functional independence（功能独立性）](#6213-functional-independence功能独立性)
        - [6.2.1.3.1 Coupling（耦合）](#62131-coupling耦合)
        - [6.2.1.3.2 Cohesion（内聚）](#62132-cohesion内聚)
      - [6.2.1.4 Object-oriented-design（面向对象设计）](#6214-object-oriented-design面向对象设计)
  - [6.3 Practices](#63-practices)
    - [6.3.1 架构设计元素](#631-架构设计元素)
    - [6.3.2 接口设计元素](#632-接口设计元素)
    - [6.3.3 组件级设计元素](#633-组件级设计元素)
    - [6.3.4 部署级设计元素](#634-部署级设计元素)
- [7. 软件设计](#7-软件设计)
  - [7.1 Architecture Design（体系结构设计）](#71-architecture-design体系结构设计)
    - [7.1.1 The Basics](#711-the-basics)
    - [7.1.2 为什么体系结构重要？](#712-为什么体系结构重要)
    - [7.1.3 不同视图](#713-不同视图)
    - [7.1.4 Architecture Patterns（体系结构模式）](#714-architecture-patterns体系结构模式)
      - [7.1.4.1 The MVC Pattern（Model-View-Controller pattern，模型-视图-控制器模式）](#7141-the-mvc-patternmodel-view-controller-pattern模型-视图-控制器模式)
      - [7.1.4.2 Layered Pattern（分层模式）](#7142-layered-pattern分层模式)
      - [7.1.4.3 The Repository Pattern（知识库模式）](#7143-the-repository-pattern知识库模式)
      - [7.1.4.4 The Client-server Pattern（客户-服务器模式）](#7144-the-client-server-pattern客户-服务器模式)
      - [7.1.4.5 The Pipe and Filter Pattern（管道和过滤器模式）](#7145-the-pipe-and-filter-pattern管道和过滤器模式)
  - [7.2 Component-level Design（组件级别设计）](#72-component-level-design组件级别设计)
    - [7.2.1 The basics](#721-the-basics)
    - [7.2.2 不同视图](#722-不同视图)
      - [7.2.2.1 Object-oriented view（面向对象视图）](#7221-object-oriented-view面向对象视图)
      - [7.2.2.2 Traditional View（传统视图）](#7222-traditional-view传统视图)
      - [7.2.2.3 Process-related View（过程视图）](#7223-process-related-view过程视图)
  - [7.3 User Interface Design（用户界面设计）](#73-user-interface-design用户界面设计)
    - [7.3.1 什么是用户界面设计？](#731-什么是用户界面设计)
    - [7.3.2 用户界面设计的重要性](#732-用户界面设计的重要性)
    - [7.3.3 The Golden Rules（黄金规则）](#733-the-golden-rules黄金规则)
      - [7.3.3.1 Place the user in control（将用户置于控制之下）](#7331-place-the-user-in-control将用户置于控制之下)
      - [7.3.3.2 Reduce the User's Memory Load（减少用户记忆负担）](#7332-reduce-the-users-memory-load减少用户记忆负担)
      - [7.3.3.3 Consist Interface（保持界面一致性）](#7333-consist-interface保持界面一致性)
    - [7.3.4 User Interface Design Process](#734-user-interface-design-process)
    - [7.3.5 User Interface Design Issues](#735-user-interface-design-issues)
      - [7.3.5.1 Response Time Issues](#7351-response-time-issues)
      - [7.3.5.2 Help facilities Issues](#7352-help-facilities-issues)
      - [7.3.5.3 Error Handling Issues](#7353-error-handling-issues)
      - [7.3.5.4 Accessibility Issues](#7354-accessibility-issues)
      - [7.3.5.5 Internationalization](#7355-internationalization)
    - [7.3.6 User Interface Design Evaluation](#736-user-interface-design-evaluation)

# 6. 设计概念
软件设计涵盖了一系列原则、概念和实践，旨在促使高质量系统或产品的开发。设计的目标是产生一个模型或表示，具备以下特征：
坚固性（无错误）。
实用性（有用或有价值）。
愉悦性（愉快的体验）。

软件设计是建模活动中的最后一个软件工程行为，为构建阶段（代码生成和测试）奠定了基础。它是一个将用户需求转化为适当形式的过程，以帮助程序员进行软件编码和实施。实际上，需求和设计是相互关联的。特别是，在设计过程中通常会澄清需求。

下图展示了从需求到设计的过程。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/192fabd251be41a3a2438012303b5589.png)
组件级设计：将软件架构的结构元素转化为软件组件的过程性描述。
接口设计：描述软件如何与与其进行交互操作的系统以及使用软件的人类进行通信。
架构设计：定义了软件的主要结构元素之间的关系，以及可以用于实现系统需求的架构风格和模式，以及影响架构实现方式的约束条件。
数据设计/类设计：将类模型转化为设计类实现以及实现所需的数据结构。

## 6.1 Principle
设计过程中的质量控制目标：
1.设计应该实现需求模型中包含的所有明确要求，并且必须满足利益相关者所期望的所有隐含要求。
2.设计应该对于那些生成代码以及测试和支持软件的人员来说是一份可读的、易于理解的指南。
3.设计应该从实施的角度全面展现软件的数据、功能和行为领域，以便能够全面理解软件的实现。

软件设计的重要性如下：
1.缺陷预防：在设计阶段早期实施质量控制有助于识别和解决潜在问题，避免它们进入开发的后期阶段。
2.成本效益：在设计阶段修复缺陷通常比在编码后或更糟的是在部署后修复要便宜得多。
3.提高用户满意度：经过质量控制的良好设计的软件产品更有可能满足用户的需求和期望。
4.增强可靠性、合规性和标准遵从、文档化和可追溯性等等。

软件设计的质量控制因素如下：
1.功能性：评估程序的功能集和能力、交付的功能的通用性以及整个系统的安全性。
2.可用性：通过考虑人为因素、整体美感、一致性和文档化来评估。
3.可靠性：通过测量故障的频率和严重程度、输出结果的准确性、平均故障间隔时间（MTTF）、从故障中恢复的能力以及程序的可预测性来评估。
4.性能：使用处理速度、响应时间、资源消耗、吞吐量和效率来进行衡量。
5.支持性：结合了可扩展性、适应性和可维护性。这三个属性代表了更常见的术语——可维护性，此外还包括可测试性、兼容性、可配置性、系统安装的便捷性以及问题定位的便捷性。

八个良好设计的技术标准：
1.设计应该展现出一种架构，这种架构 (1) 使用了可识别的架构风格或模式创建， (2) 由表现良好的设计特征的组件组成， (3) 可以以渐进的方式实施，从而促进实施和测试。
2.设计应该是模块化的；也就是说，软件应该被逻辑地划分为元素或子系统。
3.设计应该包含数据、架构、接口和组件的明确表示。
4.设计应该导致适合于要实现的类的数据结构，并且应该从可识别的数据模式中绘制。
5.设计应该导致组件具有独立的功能特性。
6.设计应该导致界面减少组件之间以及与外部环境之间的连接的复杂性。
7.设计应该使用可重复的方法来推导，这种方法受到软件需求分析期间获得的信息的驱动。
8.设计应该使用有效传达其含义的符号表示。

## 6.2 Concepts
设计概念是指导软件系统创建和组织的基本思想和原则。
它涵盖了用于确保软件系统满足功能需求、保持高质量并适应未来变化的指导原则和方法论。
它指导与体系结构、组件交互和用户体验相关的决策，最终塑造了系统的效果和可用性。

### 6.2.1 General design concepts（常见的设计概念）
General design concepts（常见的设计概念）有：
Abstraction（抽象）。
Modularity（模块化）。
Functional Independence（功能独立性），这包含Coupling（耦合）和Cohesion（内聚）。
Object-oriented design（面向对象设计）。

#### 6.2.1.1 Abstraction（抽象）
抽象是一个设计概念，其重点在于通过突出关键特征并隐藏不必要的细节，来简化复杂系统。
Abstraction is a design concept that focuses on simplifying complex systems by highlighting essential features while hiding unnecessary details.
抽象的层级越高，细节就越少。
The higher the level, the less the detail.
在最高层次的抽象中，一个概念/方法/解决方案会以问题环境的语言以广泛的术语陈述。
At the highest level of abstraction, a concept/approach/solution is stated in broad terms using the language of the problem environment.
在较低层次的抽象中，会提供更详细的概念/方法/解决方案描述。
At lower levels of abstraction, a more detailed description of the concept/approach/solution is provided.
例如这个例子：
最高层级：车。
中等层级：小米Su7.
较低层级：小米Su7 Ultra。

数据抽象是一种命名的数据集合，用来描述一个数据对象。
如图所示。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/8017a7a009e14af9a440fc106214684d.png)
过程抽象指的是具有特定和有限功能的一系列指令。过程抽象的名称暗示了这些功能，但具体细节被省略了。
如图所示。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/81e30fea6eca418cac40ad10d2af0486.png)
#### 6.2.1.2 Modularity（模块化）
模块化设计有助于更好地组织复杂系统。它基本上将相似或相关的功能聚集在一起，建立边界并为通信提供接口。
It basically clusters similar or relative functions together, sets up boundaries and provides interfaces for communication.
以手机作为一个被模块化的复杂系统的例子，模块化设计有助于将手机的各个功能模块化，例如处理器模块、摄像头模块、显示屏模块等。
模块化增加了制造效率并节省时间。
模块化允许系统部分的开发可以独立进行，因此减少了开发时间。
然而，系统中过多的模块会增加模块集成的复杂性。

对于相同的需求集，更多的模块意味着单个模块的规模更小。然而，随着模块数量的增加，与整合模块相关的工作量（成本）也会增加。下图边展示了这样的关系。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/76a6ede2cd454ab1b4efbf0d9070906e.png)

#### 6.2.1.3 Functional independence（功能独立性）
功能独立性指的是软件模块或组件在系统内部能够独立运行的程度。它具有两个关键属性：
低Coupling（耦合）：模块对其他模块的依赖性很小，可以在不需要与外部组件大量交互的情况下运行。这意味着对一个模块的修改不太可能影响其他模块。
高Cohesion（内聚）：模块专注于一个单一、明确定义的任务或责任，确保其内部元素紧密协作，并为共同目标做出贡献。
Low Coupling: The module has minimal dependencies on other modules, allowing it to function without needing to interact heavily with external components. This means that changes in one module are less likely to impact others.
High Cohesion: The module is focused on a single, well-defined task or responsibility, ensuring that its internal elements work together closely and contribute to a common purpose.

##### 6.2.1.3.1 Coupling（耦合）
耦合指的是不同模块或组件之间相互依赖的程度。
通过将模块设计成松散耦合的形式，可以独立地解决和修改模块，这意味着模块之间的依赖性较小。低耦合意味着模块在很大程度上是相互独立的，并且通常通过明确定义的接口进行交互。

下图展示了一个高耦合性例子（反面教材）：
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/29cb05db59644b65985817486297ec55.png)
当我们将Author类里的skypeID变量名修改，Editor类也需要做出对应修改否则会报错，因为Editor类直接访问了Author类里的私有变量，这便是tight coupling（高耦合性）
我们把它改为loose coupling（低耦合性）：
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/9109c5be54924c818c1f432fabbb77c1.png)
现在我们调用Author类里的getSkypeID()方法来获取Author类里的变量的值，这样我们就介绍了类之间的依赖。如果 Author 类中的 skypeName 变量名再次更改，只要 getSkypeID() 方法的签名保持不变，Editor 类就不需要做任何修改。

下面展示了另一个loose coupling（低耦合性）的例子：

```java
class Book {
    private String title;
    public Book(String title) {
        this.title = title;
    }
    public String getTitle() {
        return this.title;
    }
}

class Library {
    public void displayBookTitle(Book book) {
        System.out.println("Book title: " + book.getTitle());
    }
}
```

我们还可以通过Interface（接口）来实现loose coupling（低耦合性）。
例子如下。
原来的代码：

```java
public class Car {
    @Override
    public void move() {
        System.out.println("Car is moving");
    }
}
class Traveler {
    Car c = new Car();
    public void startJourney() {
        c.move();
    }
}
```
我们可以通过加入一个Vehicle接口从而为Traveler设置不同的车辆对象。Traveler 通过 Vehicle 接口的 move 方法来启动旅程，而不需要关心具体是哪种车辆。从而实现了loose coupling（低耦合性）。
代码如下：

```java
interface Vehicle {
    void move();
}

class Car implements Vehicle {
    public void move() {
        System.out.println("Car is moving");
    }
}

class Bike implements Vehicle {
    public void move() {
        System.out.println("Bike is moving");
    }
}

class Traveler {
    private Vehicle v;

    public void setV(Vehicle v) {
        this.v = v;
    }

    public Vehicle getV() {
        return v;
    }

    public void startJourney() {
        v.move();
    }
}
```

##### 6.2.1.3.2 Cohesion（内聚）
下面我们介绍cohesion（内聚）。
内聚性指的是单个模块或组件的责任是多么相关和集中。
High cohesion（高内聚性）也有助于功能独立性，因为它确保模块专注并且自包含。通常意味着模块内的元素共同工作以执行单一的任务或功能。
内聚性的类型包括：Method Cohesion（方法内聚），Class Cohesion（类内聚），Module Cohesion（模块内聚），Component Cohesion（组件内聚）等。
我们将重点讨论方法内聚和类内聚。

类内聚指的是一个类实现了一个单一的概念或抽象，所有元素都有助于支持这个概念。
高内聚的类通常更容易理解和更稳定。
如下图所示。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/6a1e8332344b47ff844bcc3942d4131b.png)
左边这些方法之间没有明显的关联，它们可以属于不同的类。这种设计被称为低内聚，因为它违反了单一职责原则（Single Responsibility Principle），而右边这种设计被称为高内聚，因为每个类都有明确的职责，并且类内的方法都与这个职责紧密相关。

下面展示了一个与上面差不多的例子：
low cohesion（低内聚性）：
```java
class DownloadAndStore{
	void donwloadFromInternet(){
		//...
	}
	void parseDate(){
		//...
	}
	void storeIntoDatabase(){
		//...
	}
	void doEverything(){
		downloadFromInternet();
		parseData():
		storeIntoDatabase():
	}
}
```
high cohesion（高内聚性）：

```java
class InternetDownloader {
    public void downloadFromInternet() {
        // ...
    }
}
class DataParser {
    public void parseData() {
        // ...
    }
}
class DatabaseStorer {
    public void storeIntoDatabase() {
        // ...
    }
}
class DownloadAndStore {
    public void doEverything() {
        new InternetDownloader().downloadFromInternet();
        new DataParser().parseData();
        new DatabaseStorer().storeIntoDatabase();
    }
}
```
方法内聚和类内聚同理，方法低内聚可以理解成一个方法做了多件事情，方法高内聚便是将这个方法拆成多个方法，从而每一个方法对应一件事情。例如前面这个例子便是方法高内聚。没有使用一个方法进行下载、解析和存储，而是分别使用了三个不同的方法。

#### 6.2.1.4 Object-oriented-design（面向对象设计）
面向对象设计是一种软件设计方法，它将系统组织为一组相互交互的对象，每个对象代表特定领域内的类的一个实例。
Object-Oriented Design is a software design approach that organizes a system as a collection of interacting objects, each representing an instance of a class within a specific domain.
这些对象封装了数据（属性）和行为（方法），促进了模块化、可重用性和可扩展性。
These objects encapsulate both data (attributes) and behavior (methods), promoting modularity, reusability, and scalability.

例子如下：我们现在要创建一个图书馆里的图书管理系统。这个系统允许：
1.允许用户搜索和借阅书籍。
2.跟踪书籍的借阅和可用状态。
3.允许管理员添加新书。
设计步骤如下：
1.确定类。即书、用户、图书馆。
2.确定类之间的关系。图书馆包含多本书籍，用户可以借阅多本书籍等。
3.确定类里的属性和方法。书籍类可能具有属性如标题、作者等，以及方法如借阅（borrow()）、归还（returnBook()）等。

Object-oriented-design（面向对象设计）原则：
1.Encapsulation（封装）：每个类封装了其数据和方法，允许对其属性进行受控访问。例如，书籍类（Book）控制对其是否可借阅（isAvailable）属性的访问。
2.Inheritance（继承）：在更复杂的系统中，我们可能会有类似数字图书和纸质图书的类，它们从书籍类继承而来。
3.Polymorphism（多态）：不同类型的书籍或用户可能需要根据特定的需求重写方法以实现特定的行为。
## 6.3 Practices
设计模型可以被看作是一个详细的框架，一组方法，指导软件系统从分析到实现的开发过程。它包括以下元素（方面）：
数据设计元素，架构设计元素，接口设计元素，组件级设计元素，部署级设计元素。
数据设计元素是软件工程活动中的一个重要部分，它创建了一个数据和/或信息的模型，以高层次的抽象表示（即客户/用户对数据的视图）。
这个模型随后会逐步细化为更具体的实现表示，以便计算机系统进行处理。在电子商务系统等应用中，数据设计元素的不同层次包括：
业务级别：定义高层次的目标（增加销售额、优化库存、提升满意度），并识别所需的数据（产品、客户、订单、库存等）。
应用级别：为核心功能设计数据使用（产品目录、订单处理、库存管理、推荐引擎等）。
程序组件级别：实现数据结构（例如产品、客户、订单、库存、推荐引擎等）。这些数据结构将作为变量在计算机系统中进行处理。

### 6.3.1 架构设计元素
软件的架构设计相当于房屋的平面图。平面图描述了房间的总体布局，它们的大小、形状和彼此之间的关系，以及允许进出房间的门窗。
平面图为我们提供了房子的整体视图。架构设计元素为我们提供了软件的整体视图。
架构设计元素的来源包括三个方面：
关于软件应用领域的信息，用于构建软件；
特定需求模型元素，如用例或分析类，它们之间的关系和协作，解决当前问题；
可用的架构风格和模式。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/b5d9ce308f8546e6ac6a2ba38f7a7b62.png)

### 6.3.2 接口设计元素
软件的界面设计类似于房屋的门窗和外部设施的详细图纸（和规格说明）。
软件的界面设计元素描述了信息如何进入和离开系统，以及在作为架构一部分定义的组件之间如何进行通信。
其中包括三个重要的元素：
用户界面（UI）。
与其他系统、设备、网络或其他信息生产者或消费者之间的外部接口。
不同设计组件之间的内部接口，用于实现系统内部各个部分之间的通信和协作。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/387caa9c9a364e11a7b7b237313462db.png)
### 6.3.3 组件级设计元素
组件级设计对于软件来说相当于房屋中每个房间的详细图纸（和规格说明）。
软件的组件级设计完整描述了每个软件组件（例如对象）的内部细节。在软件工程中，组件通常以UML图的形式进行表示。
一个组件的设计细节可以在许多不同的抽象级别上进行建模，例如流程图或框图可以用来描述组件的详细过程流程。也可以是下面这种图。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/db9ef8fa1e0349fabf5a7c2903ce2f96.png)

### 6.3.4 部署级设计元素
部署级别的设计元素指示了软件功能和子系统将如何在支持软件的物理计算环境中进行分配。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/8823fc38cdd045729379661306125d42.png)

# 7. 软件设计
## 7.1 Architecture Design（体系结构设计）
### 7.1.1 The Basics
体系结构设计关注于理解系统应该如何组织，并设计系统的整体结构。它是软件设计过程中的第一个阶段，也是设计和需求工程之间的关键环节。软件架构设计有助于识别系统中的主要结构组件以及它们之间的关系。这一设计过程的输出是对体系结构模型。
下图展示了打包机器人控制系统的体系结构。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/92772fb75206432cb0a31c817806f7b8.png)
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/1d30b5d351af498eaade748ca1de386a.png)
体系结构在两个不同抽象级别上的设计：
1.Architecture in the small（小规模架构）关注的是单个程序的架构。在这个层面上，我们关注的是如何将一个单个程序分解成组件。这章主要关注程序体系架构。
2.Architecture in the large（大规模架构）关注的是复杂企业系统的架构，这些系统包括其他系统、程序和程序组件。这些企业系统分布在不同的计算机上，可能由不同的公司拥有和管理。

### 7.1.2 为什么体系结构重要？
体系结构对性能、稳健性、可分布性和可维护性都有影响。
在体系结构中，单个组件负责实现功能性需求。
系统架构则负责满足非功能性需求。

设计并描述软件体系结构有以下三点好处：
1.利益相关者交流。体系结构可以作为系统利益相关者讨论的焦点。
2.系统分析。软件体系结构使得分析系统是否能够满足其非功能性需求成为可能。
3.大规模重用。体系结构可能会被多个系统重复使用。开发产品线架构，使得一系列产品都能够共享同一架构。

### 7.1.3 不同视图
1.Logical view（逻辑视图）：展示了系统中的关键抽象，通常以对象或对象类的形式呈现。
2.Process view（过程视图）：展示了系统在运行时是如何由相互交互的进程组成的。
3.Development view（开发视图）：展示了软件在开发过程中是如何进行分解的。
4Physical view（物理视图）：展示了系统的硬件结构以及软件组件在系统中如何分布在处理器之间。

下图展示了火车自动售票系统的逻辑视图。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/4bc70907a5994808b2b9b7e897ac7e7b.png)
下图展示了对应的过程视图。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/0f9c8ff2531541a984ac8d55df521804.png)
下图展示了对应的开发视图。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/7a877f1fccc145e1b4101a194396f59d.png)
下图展示了对应的物理视图。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/075c69950b88408ba0773afea41b067d.png)
### 7.1.4 Architecture Patterns（体系结构模式）
模式是表示、分享和重用知识的手段。
体系结构模式是对良好设计实践的一种风格化描述，它已经在不同环境中经过尝试和测试。
An architectural pattern is a stylized description of good design practice, which has been tried and tested in different environments. 
模式应该包括关于它们何时有用以及何时不有用的信息。
Patterns should include information about when they are and when the are not useful.
模式可以通过表格和图形描述来呈现。
Patterns may be represented using tabular and graphical descriptions.

#### 7.1.4.1 The MVC Pattern（Model-View-Controller pattern，模型-视图-控制器模式）
模型-视图-控制器（MVC）模式是许多基于Web的系统中用于管理交互的基础。它包括三个主要的相互关联的组件：
Model（模型）：这是模式的核心组件，直接管理应用程序的数据、逻辑和规则。
View（视图）：可以是信息的任何输出表示，比如图表或图示。
Controller（控制器）：接受输入并将其转换为对模型或视图的命令，使视图和模型之间能够相互连接。
下图展示了用MVC展现一个体系结构的逻辑视图。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/9111643a9d1c401598a23e28362f5e0a.png)
下图展示了用MVC展示一个体系结构的开发视图。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/531aefc4a63045bf8519e2089101d073.png)
下图是MVC模式的模式手册。 
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/b17908845e1244f89bf3d3c8d76f8125.png)
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/38173b72a4c04244b1a64a7d2c3d7510.png)
下图展示了MVC模式的组织。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/7d91c687f8904cf280d93bcd53b239aa.png)
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/c05fcf0a2ef94deca60dadb5c3fcb1a6.png)
下图展示了MVC模型的体系结构。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/4855796fdbe64f0e8cb8587309381534.png)
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/20890c4c041f4df7884d436fd3f8be1b.png)
#### 7.1.4.2 Layered Pattern（分层模式）
Layered Pattern（分层模式）是指将系统功能组织成独立的层次，每个层次仅依赖于其beneath（下方）的层次所提供的设施和服务。
Layered Pattern: the system functionality is organized into separate layers, and each layer only relies on the facilities and services offered by the layer immediately beneath it. 
这种分层的方法支持系统的渐进式开发。随着每个层次的开发，该层次提供的一些服务可能会向用户开放。
This layered approach supports the incremental development of systems. As a layer is developed, some of the services provided by that layer may be made available to users. 
然而，分层模式在高性能应用中表现不佳，因为需要通过多个层次来满足业务请求，这样效率较低。但在预算紧张和时间限制严格的情况下，分层模式是一个不错的选择。
Performs poorly in the high-performance applications, because it is not efficient to go through multiple layers to fulfil a business request. It is a good choice for situations with a very tight budget and time constraints.

下图展示了一个通用的分层模式体系结构。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/da01ecb352674911a2d1a18deffd48ff.png)
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/5fcd39fc41b147d9b385a8eb3b591772.png)
下图展示了一个具体的分层模式体系结构。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/fe2a31e994104cb497afba69b1a8bff1.png)
下图对分层模式体系结构进行了描述。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/49de10398407447cbe1eaa25fc906d1f.png)
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/64a1e7e962fd4c21b9686e8ccb28769c.png)
#### 7.1.4.3 The Repository Pattern（知识库模式）
描述如下。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/f70ffa7437a8452c96ebd6d2f7eb2a76.png)
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/15ec31fd5d9248e5b6f5ac6924b07488.png)
下图展示了面向IDE的知识库模式体系结构。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/5c61f149bc09413f8833aaeb26efbca2.png)
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/aad5702d1e744bb8bfd38076cc1b070b.png)

#### 7.1.4.4 The Client-server Pattern（客户-服务器模式）
描述如下。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/d97bcc146daf4175a2dad85168f2f08b.png)
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/bcece4a227a045928a12974cfdde8e2b.png)
下图展示了一个电影库的客户的客户-服务器模式体系结构。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/161534d2e56449169083b4e915e4acac.png)
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/2299e4878da6441e9c6748ad35de18d6.png)
#### 7.1.4.5 The Pipe and Filter Pattern（管道和过滤器模式）
描述如下。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/fab1d7b931624118a7fb4376c6adbffc.png)
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/6e2aaec73ce947258d61a60fcef59d02.png)
下图展示了一个例子。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/0b2b53c0f24144259c8df39746333ee9.png)
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/72967aa7203c4599a41051fad2f659c6.png)
## 7.2 Component-level Design（组件级别设计）
### 7.2.1 The basics
组件级设计发生在架构设计的第一轮迭代完成之后。在体系结构设计阶段，会定义一套完整的软件组件。
组件级设计会定义分配给每个软件组件的数据结构、算法、接口特征和通信机制。
组件级设计可以使用一些中间表示形式（例如图形、表格或基于文本的表示），这些表示形式可以被转换为源代码。

软件组件是计算机软件的模块化构建块。它可以被用来进行正确性和一致性的审查，以确保与其他组件的一致性。可以被用来评估数据结构、接口和算法是否能够正常工作。软件组件应该提供足够的信息来指导实现。

### 7.2.2 不同视图
组件级别设计有三种不同视图：
1.Object-oriented view（面向对象视图）
2.Conventional view（传统视图）
3.Process view（过程视图）

#### 7.2.2.1 Object-oriented view（面向对象视图）
焦点：面向对象视图的重点是将对象视为软件的基本构建块。对象封装了数据和行为，代表着实体或概念。
关键概念：包括封装、继承、多态和抽象。类定义了对象的结构和行为。
优势：促进了可重用性、模块化和可维护性。它特别适用于复杂系统，其中真实世界建模是有益的。
用途：在现代软件开发中被广泛采用，特别是对于需要进行大量数据操作和复杂交互的应用程序。

下面给出一个客户信息管理的例子。
面向对象视图的类和对象如下：
CustomerProfile: 代表了客户的个人资料。
它包括了一些属性，比如customerID（客户ID）、name（姓名）、contactDetails（联系方式）、purchaseHistory（购买历史）。
还包括了方法，比如updateContactDetails()（更新联系方式）、addPurchaseRecord()（添加购买记录）。
ProfileManager: 负责处理与客户个人资料相关的操作。
它包括了一些属性，比如ManagerID（管理者ID）、name（姓名）、contactDetails（联系方式）、Position（职位）。
还包括了方法，比如createProfile(CustomerProfile)（创建客户个人资料）、updateProfile(customerID, CustomerProfile)（更新客户个人资料）、getProfile(customerID)（获取客户个人资料）。

#### 7.2.2.2 Traditional View（传统视图）
焦点：传统视图强调了一种自顶向下的软件设计方法，侧重于函数或过程以及它们之间的数据流。
关键概念：软件被结构化成执行特定任务的函数或过程。它依赖于编程结构中的顺序、选择和迭代。
优势：简单直接，特别适用于线性和较少复杂的应用程序。对于小规模项目来说更容易跟踪。
用途：在软件开发历史的早期阶段更为普遍，适用于具有明确操作顺序的应用程序，比如批处理。

下面给出同样情景的传统视图的例子：
createCustomerProfile(customerID, name, contactDetails): 这个过程用于创建一个新的客户个人资料。
updateCustomerProfile(customerID, updatedDetails): 这个过程用于更新现有客户个人资料。
retrieveCustomerProfile(customerID): 这个过程用于检索特定客户个人资料的详细信息。

#### 7.2.2.3 Process-related View（过程视图）
焦点：过程相关的视图关注软件组件在运行时的行为。它着眼于组件在执行过程中的操作方式，特别是涉及到进程和线程。
关键概念：包括进程管理、进程间通信、并发性、同步和资源管理。
优势：对于理解系统性能、可扩展性和可靠性至关重要。在需要关注实时处理、并发性和资源管理的系统中至关重要。
用途：适用于复杂、分布式或实时系统，其中理解动态行为对系统性能和可靠性至关重要。

下面给出同样情景的过程视图的例子：
初始化过程：在系统启动时加载产品目录和用户数据。
订单处理工作流程：涉及验证购物车、计算总成本以及启动支付过程。
支付处理：处理授权、支付详细信息的验证以及支付确认。必须管理并发处理以处理同时进行的交易。
通知和日志记录：向客户发送订单确认，以及针对每笔交易更新系统日志。

对比如下：
面向对象视图：侧重于将系统建模为一组相互交互的对象，每个对象封装了与在线购物相关的数据和行为。
传统视图：将系统结构化为一系列执行特定任务的过程或函数，比如添加产品、下订单和处理支付等。
过程视图：从系统的运行时行为角度来看待系统，特别关注它如何处理订单和支付的流程，并管理并发性和系统资源。
## 7.3 User Interface Design（用户界面设计）
### 7.3.1 什么是用户界面设计？
用户界面设计创造了人与计算机之间的有效沟通媒介。
User interface design creates an effective communication medium between a human and a computer.

### 7.3.2 用户界面设计的重要性
1.设计不良的用户界面会迫使用户犯错。
A poorly designed user interface will force user to commit  mistakes.
2.即使计算能力或内容再好，用户仍然可能因为使用设计不良的界面而感到沮丧。
Users can get easily frustrated using a poorly designed  interface regardless of computational power or content.

### 7.3.3 The Golden Rules（黄金规则）
1.Place the user in ocntrol（将用户置于控制之下）。
2.Reduce the user's memory（降低用户的记忆负担）。
3.Make the interface consistent（保持界面一致性）。

#### 7.3.3.1 Place the user in control（将用户置于控制之下）
它可以实现为以下几个规则：
1.以不迫使用户进行不必要或不希望的操作的方式定义交互模式。
Define interaction modes in a way that does not force a user into  unnecessary or undesired actions
2.提供灵活的交互方式。由于不同用户有不同的交互偏好，应该提供选择。
Provide for flexible interaction. Because different users have different interaction preferences, choices should be provided.
3.允许用户的交互可以被中断和撤销。
Allow user interaction to be interruptible and undoable.
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/ce01a8061ef443a88382d8dbca0b925b.png)
这包含（1）用户的操作可以被撤销，即具有“宽容性”，并提供“撤销”功能。
Make actions reversible – be forgiving- Undo。
（2）当用户错误地选择了系统功能时，“撤销”功能可以极大地帮助用户。在这种情况下，撤销功能就像一个“紧急出口”，让用户能够退出不想要的状态，从而避免产生不必要的后果。
‘Undo’ can be extremely helpful when users choose system function by mistake. In this case, the undo function serves as an ’emergency exit,’ allowing users to leave the unwanted state.
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/0f252179ff8347849c0e8dd8ff726556.png)

4.设计界面时要考虑直接与屏幕上出现的对象进行交互。
Design for direct interaction with object that appear on the screen.
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/aba27cc819cd41dc8609ab72e474bd3b.png)
5.显示系统状态的可见性。当用户了解系统当前的运行状态并且定期得到有关过程状态的反馈时，用户更愿意宽容。
Show the visibility of system status.Users are much more forgiving when they have information about what is going on and are given periodic feedback about the status of the process.
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/834cf8d8ccbb4ecfb98d1b0183c0e3ba.png)

#### 7.3.3.2 Reduce the User's Memory Load（减少用户记忆负担）
它可以实现为以下几个规则：
1.减少对短期记忆的需求。
Reduce demand on short-term memory.
用户界面应该被设计成减少用户需要记住过去操作、输入和结果的要求。
The interface should be designed to reduce the requirement to remember past actions, input and results.
2.建立有意义的默认设置。
Establish meaningful defaults.
默认值应该是大多数用户所期望的。
Default should be what the majority of your users will want.
使用智能默认设置，例如根据地理位置自动设置默认值，或者进行自动计算以提供更智能的默认设置。
Use smart defaults (geolocation, automatic calculation).
不要在需要用户关注的输入字段（例如订阅通讯或接受使用条款）中使用默认设置。
Don’t use defaults for input fields that require user attention such as signing up to newsletters or accepting terms of use.
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/52e067b5b72a4c40b7560aff7805e633.png)

3.界面的视觉布局应该基于现实世界的隐喻。
The visual layout of the interface should be based on a real-world metaphor.
在用户界面设计中使用隐喻可以让用户在真实世界和数字体验之间建立联系。
Using metaphors in UI design allows users to create a connection between the real world and digital experiences.
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/da605e5100df4fbf90b1ec4860e70c1a.png)
#### 7.3.3.3 Consist Interface（保持界面一致性）
所有的视觉信息都按照设计规则进行组织，并且这些规则在所有屏幕显示中都得到保持。
All visual information is organized according to design rules that are maintained throughout all screen displays.
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/006c222048f24ddfa8034ad756592e40.png)
### 7.3.4 User Interface Design Process
可以用一个螺旋模型来表示UI设计的过程，如下图所示。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/d8afca23882b462f98454d2d13f34f2c.png)

### 7.3.5 User Interface Design Issues
UI设计可能存在的问题如下：
1.Response time（响应时间）：系统响应时间有两个重要特征：长度和变异性。
System response time has 2 important characteristics: length and variability. 
2.Help facilities（帮助设施）：对所有系统功能必须提供帮助。包括帮助菜单和打印文档。
Help must be available for all system functions. Include help menus, print documents.
3.Error handling（错误处理）：在用户可以理解的语言中描述问题。永远不要责怪用户造成错误。
Describe the problem in a language the user can understand. Never blame the user for the error that occurred.
4.Application accessibility（可访问性）：特别是对于身体上有挑战的人士。
Especially for the physically challenged. 
5.Internationalization（国际化）：Unicode标准旨在解决管理数十种自然语言和数百种字符和符号的挑战。
The Unicode standard has been developed to address the daunting challenge of managing dozens of natural languages with hundred of characters and symbols.

#### 7.3.5.1 Response Time Issues
Length（长度）：根据报道，47%的消费者希望网页在两秒钟或更短的时间内加载完成。用户对性能和可用性问题（如加载时间、小图像和网络可用性）会感到非常沮丧。
Variability（变异性）：变异性指的是响应时间与平均响应时间的偏差，从许多方面来看，这是最重要的响应时间特征。

#### 7.3.5.2 Help facilities Issues
对所有系统功能必须提供帮助。包括帮助菜单和打印文档。

#### 7.3.5.3 Error Handling Issues
每个错误消息或警告都应具备以下特点：
1.用用户可以理解的术语描述问题。
2.提供恢复错误的建设性建议。
3.指示错误可能的负面后果，比如数据文件可能被损坏，以便用户可以检查并确保这些问题没有发生，或者在必要时进行修正。

#### 7.3.5.4 Accessibility Issues
示例如下：
小屏幕和虚拟键盘：智能手机的显示屏和虚拟键盘相对较小，这可能会对某些用户的操作体验造成影响。
依赖语音或其他声音信号的应用：一些应用程序可能依赖语音输入或声音反馈，这对听力有障碍的用户来说可能是个问题。
视力、听力和操作能力的限制：视力不佳、色盲、听力损失或手指不灵活的用户在使用应用程序时可能会遇到困难。
操作系统的可访问性功能：Android和iOS操作系统提供了许多可访问性功能，并且可以在线获取关于如何构建可访问性应用程序的建议。
用户测试：在进行用户测试时，应尝试找到那些视力、听力等不完美的人，包括不同年龄段的测试者。老年人通常在使用触摸屏方面的能力较弱。

#### 7.3.5.5 Internationalization
用户界面应该被设计成能够适应所有使用软件的人的通用核心功能。

### 7.3.6 User Interface Design Evaluation
一旦设计师完成了用户界面的原型设计，就需要对其进行测试和评估，以确保它能够满足用户的需求和期望。
如下图所示。而且尽量设计和评估由不同的人完成。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/c71097e0500241b585f94953507b9a6a.png)
衡量UI设计的可用性包含三个方面：
1.Effectiveness（有效性）：
描述用户实现特定目标的准确性和完整性。
衡量标准包括quality of solution（解决方案的质量）和error rates（错误率）。
2.Efficiency（效率）：
关注有效性与实现目标所消耗资源之间的关系。
衡量标准包括task completion time（完成任务所需的时间）、learning time（学习时间）和number of clicks（点击次数）。
3.Satisfaction（满意度）：
关注用户使用系统的舒适度以及对系统的积极态度。
衡量标准包括attitude rating scales（态度评级量表）。
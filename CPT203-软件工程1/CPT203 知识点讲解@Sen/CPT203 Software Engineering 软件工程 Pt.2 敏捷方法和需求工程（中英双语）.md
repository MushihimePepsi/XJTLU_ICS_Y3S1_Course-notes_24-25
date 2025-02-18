- [3. Aglie methods（敏捷方法）](#3-aglie-methods敏捷方法)
  - [3.1 Aglie methods（敏捷方法）](#31-aglie-methods敏捷方法)
    - [3.1.1 特点](#311-特点)
    - [3.1.2 优点](#312-优点)
    - [3.1.3 缺点](#313-缺点)
    - [3.1.4 原则](#314-原则)
    - [3.1.5 计划驱动与敏捷方法的对比](#315-计划驱动与敏捷方法的对比)
  - [3.2 Scrum](#32-scrum)
    - [3.2.1 Scrum roles](#321-scrum-roles)
    - [3.2.2 Scrum Activities and Artifacts](#322-scrum-activities-and-artifacts)
      - [3.2.2.1 Product Backlog（待办列表）](#3221-product-backlog待办列表)
      - [3.2.2.2 Product Backlog Grooming（待办列表的精细化）](#3222-product-backlog-grooming待办列表的精细化)
    - [3.2.2.3 Sprint（冲刺）](#3223-sprint冲刺)
      - [3.2.2.4 Sprint Planning](#3224-sprint-planning)
      - [3.2.2.5 Sprint Execution](#3225-sprint-execution)
      - [3.2.2.6 Daily Scrum（每日Scrum会议）](#3226-daily-scrum每日scrum会议)
      - [3.2.2.7 Done（已完成）](#3227-done已完成)
      - [3.2.2.8 Sprint Review](#3228-sprint-review)
      - [3.2.2.9 Sprint Retrospective](#3229-sprint-retrospective)
- [4. 需求工程](#4-需求工程)
  - [4.1 Software Specification Processes](#41-software-specification-processes)
  - [4.2 需求抽取](#42-需求抽取)
    - [4.2.1 User Requirements（用户需求）](#421-user-requirements用户需求)
    - [4.2.2 System Requirements（系统需求）](#422-system-requirements系统需求)
    - [4.2.3 Functional Requirements（功能性需求）](#423-functional-requirements功能性需求)
    - [4.2.4 Non-functional Requirements（非功能性需求）](#424-non-functional-requirements非功能性需求)
    - [4.2.5 Emergent System Properties（新出现的系统特性）](#425-emergent-system-properties新出现的系统特性)
    - [4.2.6 Feasibility Study（可行性研究）](#426-feasibility-study可行性研究)
  - [4.3 Requirements Elicitation and Analysis（需求获取和分析）](#43-requirements-elicitation-and-analysis需求获取和分析)
    - [4.3.1 Requirement Discovery（需求发现）](#431-requirement-discovery需求发现)
      - [4.3.1.1 Interview（访谈）](#4311-interview访谈)
      - [4.3.1.2 Scenarios（故事和场景）](#4312-scenarios故事和场景)
      - [4.3.1.3 Ethnography（人种学调查）](#4313-ethnography人种学调查)
    - [4.3.2 Requirements Specification（需求规格说明）](#432-requirements-specification需求规格说明)
      - [4.3.2.1 Natural Language Specification（自然语言规格说明）](#4321-natural-language-specification自然语言规格说明)
      - [4.3.2.2 Structured Specification（结构化规则说明）](#4322-structured-specification结构化规则说明)
    - [4.2.3 Software Requirements Document（SRD，软件需求文档化）](#423-software-requirements-documentsrd软件需求文档化)
    - [4.2.4 Requirements Validation（需求确认）](#424-requirements-validation需求确认)

# 3. Aglie methods（敏捷方法）
由于企业现在在全球快速变化的环境中运营，它们必须对新的机遇和市场、经济状况的变化以及竞争性产品和服务的出现做出反应。这对软件开发有重大影响，意味着软件开发需要更加灵活和快速响应变化。软件开发需要能够适应不断变化的需求和市场，以及迅速推出新功能和服务来满足市场的需求。因此，软件开发需要更加注重敏捷性、灵活性和创新性，以便与快速变化的商业环境保持同步。

许多企业愿意在软件质量和需求上做出妥协，以实现他们所需软件的更快部署。具体来说：
很难得出一个完整的稳定的软件需求集。最初的需求必然会发生变化。
尽快交付系统，让用户获得经验并发现更清晰的真实需求。
由于外部因素的影响，需求可能会迅速而不可预测地发生变化。

传统的软件开发流程往往要求在开始设计和实现之前完全规范化需求，这种方式不适合于快速变化的需求环境。因为当需求发生变化或者出现需求问题时，系统的设计或实现必须重新调整和重新测试。

因此快速软件开发不断被接受并逐渐被称为敏捷开发或敏捷方法。这些敏捷方法的设计目的是快速产出有用的软件。

## 3.1 Aglie methods（敏捷方法）
### 3.1.1 特点
所有已经提出的敏捷方法都具有如下这些共同的特性：
1.软件规格、设计和实现过程交织在一起。没有详细的系统规格说明，设计文档化被最小化或者由用于实现系统的编程环境自动生成。用户需求文档是对最重要的系统特性的概览定义。
2.系统按照一系列增量进行开发。最终用户和其它系统利益相关者参与每个增量的规格说明和评估。他们可能会提出对于软件的变更要求以及应当在系统的后续版本中实现的新需求。
3.使用广泛的工具来支持开发过程。可以使用的工具包括自动化测试工具、支持配置管理和系统集成的工具、用户界面自动化构造工具。

The software is not developed as a single unit but as a series of increments, with each increment including new system functionality.
Fundamental characteristics:
1.The processes are interleaved.
2.Minimum documentation.
3.Developed in a series of versions, or increments, with system stakeholders involvement.
4.System user interfaces are often developed using an interactive development system that allows the interface design to be quickly created.

快速软件开发的其他方法，包括：
自适应软件开发：这是一种注重灵活性和快速响应变化的软件开发方法，强调持续交付和不断调整以满足需求变化。
敏捷方法：这是一种强调团队合作、快速反馈和持续交付价值的软件开发方法，如Scrum、极限编程等。
螺旋模型：这是一种结合了迭代和逐步增量开发的软件开发方法，强调风险管理和迭代开发。
统一软件开发过程：这是一种软件工程方法，旨在提高软件开发的质量和效率，强调模型驱动的开发和过程管理。

而计划驱动的开发方法，通常用于开发大型、长期存在的软件项目。具体特点包括：仔细的项目规划、正式化的质量保证、使用CASE工具支持的分析和设计方法、受控和严格的软件开发流程。

### 3.1.2 优点
敏捷方法的优点如下：
1.敏捷方法允许开发团队专注于软件本身而不是设计和文档编写。
2.敏捷方法普遍依赖于增量式的软件规范、开发和交付。
3.敏捷方法最适合应用程序开发，因为系统需求在开发过程中经常发生快速变化。
4.敏捷方法旨在快速向客户交付可工作的软件，客户可以在后续迭代中提出新的需求和变更，这样能更好地满足客户需求。
1.Agile allowed the development team to focus on the software itself rather than on its design and documentation.
2.Universally rely on an incremental approach to software specification, development, and delivery. 
3.They are best suited to application development where the system requirements usually change rapidly during the development process.
4.They are intended to deliver working software quickly to customers, who can then propose new and changed requirements to be included in later iterations of the system.

### 3.1.3 缺点
缺点：
1.成功与否取决于是否有一个愿意并且能够花时间与开发团队合作，并且能够代表所有系统利益相关者的客户。
2.个别团队成员可能并不适合进行密集的参与。
3.对变更进行优先级排序可能会非常困难，特别是对于有许多利益相关者的系统而言。
4.保持简单需要额外的工作。
5.一些组织难以接受由开发团队定义的非正式流程。
6.软件需求文档通常是客户和供应商（软件公司）之间合同的一部分。
7.由于增量式规范是敏捷方法固有的特点，为这种类型的开发编写合同可能会很困难。
8.敏捷方法必须依赖于一种合同，其中客户支付系统开发所需的时间，而不是特定一组需求的开发。
9.如果出现问题，可能会产生关于责任和额外时间、资源支付的争议。
1.Its success depends on having a customer who is willing and able to spend time with the development team and who can represent all system stakeholders.
2.Individual team members may not have suitable personalities for the intense involvement.
3.Prioritizing changes can be extremely difficult, especially in systems for which there are many stakeholders.
4.Maintaining simplicity requires extra work.
5.It is difficult for some organization to accept informal processes defined by development teams.
6.The software requirements document is usually part of the contract between the customer and the supplier (software company).
7.Because incremental specification is inherent in agile methods, writing contracts for this type of development may be difficult.
8.Agile methods must rely on contracts in which the customer pays for the time required for system development rather than the development of a specific set of requirements.
9.If problems arise then there may be difficult disputes over who is to blame and who should pay for the extra time and resources required to resolve the problems.
主要问题是：1.不适合例如嵌入式系统工程或者大型复杂系统的开发。
2.敏捷开发的非正式性与大型企业中通常使用的基于法律的合同定义不相符。
3.敏捷方法最适合于新的软件开发而不是软件维护。然而，大型企业软件成本大部分来自于对于已有软件软件系统的维护。
4.敏捷方法适用于小的、同处异地的团队，然而当前的很多软件开发都包含全球分布的开发团队。

敏捷方法在软件维护上也会遇到一些挑战：
正式文档通常被认为可以促进系统的演进和维护，但实际上，正式文档往往没有及时更新，这可能会影响系统的可维护性。
敏捷方法的支持者认为编写过时的文档是浪费时间。他们强调敏捷方法的核心是快速响应变化，因此过时的文档可能会成为负担，不如将精力集中在实际的软件开发和维护上。
实现可维护的软件的关键在于编写高质量、可读性强的代码。敏捷方法强调通过编写清晰易懂的代码来实现软件的可维护性，而不是依赖过时的文档。
关键文档是系统需求文档，它告诉软件工程师系统应该做什么。在敏捷方法中，系统需求文档被视为关键的指导性文档，它为开发人员提供了开发方向和目标。

在软件交付后，保持客户参与可能是主要困难之一。敏捷方法强调与客户的密切合作和反馈，但在软件交付后，客户的持续参与可能会成为挑战。
另一个可能出现的问题是保持开发团队的连续性。敏捷方法依赖于团队成员对系统的理解，而不是依赖文档。如果敏捷开发团队解散，那么隐含的知识可能会丢失，新团队成员可能难以建立对系统及其组件的相同理解。
The main difficulty after software delivery is likely to be keeping customers involved in the process.The other problem that is likely to arise is maintaining continuity of the development team. Agile methods rely on team members understanding aspects of the system without having to consult documentation. 
If an agile development team is broken up, then this implicit knowledge is lost and it is difficult for new team members to build up the same understanding of the system and its components.
在维护中主要是以下3类问题：
1.缺少产品文档。
2.保持客户参与。
3.开发团队的延续性。

### 3.1.4 原则
敏捷方法背后的理念被写入了敏捷宣言，由许多领先的敏捷方法开发者共同制定：
个体和交互优先于流程和工具。
可工作的软件优先于详尽的文档。
与客户的合作优先于合同谈判。
对变化的响应优先于遵循计划。

敏捷方法的原则如下：
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/5e5583b5cd55412fb7eec98bd2fafa66.png)
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/a07df969dc4340e7b6eb7aef8469c115.jpeg#pic_center)
### 3.1.5 计划驱动与敏捷方法的对比
对于选择计划驱动还是敏捷方法进行开发，可以从以下方面进行考虑：
1.需要详细的规格说明和设计吗？
2.增量式开发策略是否现实？
3.系统的规模有多大？
4.正在开发的系统是什么类型？
5.可用的技术和工具是什么？
6.团队的组织结构是怎样的？
7.组织内部文化问题是什么？
8.可用的技能组合是什么？
9.外部法规有哪些？
10.系统的生命周期是多久？

## 3.2 Scrum
敏捷方法包括：
极限编程（Extreme Programming，简称XP）。
Scrum。
Crystal。
自适应软件开发（Adaptive Software Development）。
DSDM（Dynamic Systems Development Method）。
特征驱动开发（Feature Driven Development）。
这些敏捷方法都基于增量式开发和交付的概念，但在具体的过程和方法上有所不同。然而，它们都遵循敏捷宣言中的一套原则，因此有很多共同之处。

我们这一节将具体介绍Scrum方法。

Scrum并不是一个标准化的过程，而是一个组织和管理工作的框架。Scrum框架基于一组价值观、原则和实践，为组织提供了基础，组织可以根据自身情况添加相关工程实践的独特实现，以及特定的方法来实现Scrum实践。

### 3.2.1 Scrum roles
首先Scrum架构中有三种重要角色：
1.Product owner（产品负责人）负责确定开发的内容以及开发的顺序。
2.Scrum Master（Scrum 大师）负责指导团队根据更广泛的Scrum框架创建和遵循自己的流程。
3.Development team（开发团队）负责确定如何交付产品负责人所要求的内容。
1.The product owner is responsible for what will be developed and in what order.
2.The Scrum Master is responsible for guiding the team in creating and following its own process based on the broader Scrum framework.
3.The development team is responsible for determining how to deliver what the product owner has asked for.

产品负责人是唯一的权威，负责决定要构建哪些特性和功能，以及构建它们的顺序。
产品负责人维护并向所有其他参与者传达清晰的愿景，说明Scrum团队试图实现什么目标。
产品负责人对正在开发或维护的解决方案的整体成功负责。
产品负责人确保最有价值的工作得以进行。
产品负责人积极与ScrumMaster和开发团队合作，以确保团队能够理解和实现最有价值的工作。
产品负责人需要及时回答团队提出的问题。
The single authority responsible for deciding which features and functionality to build and the order in which to build them.
The product owner maintains and communicates to all other participants a clear vision of what the Scrum team is trying to achieve.
The product owner is responsible for the overall success of the solution being developed or maintained.
To make sure that the most valuable work is always performed.
The product owner actively collaborates with the ScrumMaster and development team.
Must be available to answer questions soon after they are posed.

ScrumMaster帮助所有参与者理解和接受Scrum的价值观、原则和实践。
作为一名教练，ScrumMaster提供过程领导，并帮助Scrum团队和整个组织发展他们自己的高绩效、组织特定的Scrum方法。
ScrumMaster协助组织应对在Scrum采用过程中可能出现的挑战性变革管理过程。
作为促进者，ScrumMaster帮助团队解决问题，并改进其使用Scrum的方式。
ScrumMaster负责保护团队免受外部干扰，并在消除妨碍团队生产力的障碍方面发挥领导作用。
ScrumMaster没有权力对团队施加控制，因此这个角色与传统的项目经理或开发经理的角色并不相同。
ScrumMaster的作用更像是引导者和领导者，而不是管理者。
Helps everyone involved understand and embrace the Scrum values, principles, and practices.
Acts as a coach, providing process leadership and helping the Scrum team and the rest of the organization develop their own high performance, organization-specific Scrum approach.
The ScrumMaster helps the organization through the challenging change management process that can occur during a Scrum adoption.
As a facilitator, the ScrumMaster helps the team resolve issues and make improvements to its use of Scrum.
Also responsible for protecting the team from outside interference and takes a leadership role in removing impediments that inhibit team productivity.
The ScrumMaster has no authority to exert control over the team, so this role is not the same as the traditional role of project manager or development manager.
The ScrumMaster functions as a leader, not a manager.

开发团队是一个多样化、跨职能的人员集合，他们负责设计、构建和测试所需的产品。
开发团队自我组织，以确定实现产品负责人设定目标的最佳方式。
一般来说，开发团队的规模通常为五到九人。
开发团队的成员必须集体拥有生产高质量、可工作软件所需的所有技能。
对于需要更大团队规模的开发工作，团队成员可以被组织成几个团队，每个团队由九名或更少的成员组成。
Scrum defines the role of a development team, which is simply a diverse, cross-functional collection of people who are responsible for designing, building, and testing the desired product.
The development team self-organizes to determine the best way to accomplish the goal set out by the product owner.
The development team is typically five to nine people in size.
Its members must collectively have all the skills needed to produce good quality, working software.
For development efforts that require much larger team size, team members can be organized into several teams with each team nine or fewer team members.

### 3.2.2 Scrum Activities and Artifacts
在Scrum框架中，有一些特定的活动和成果，用于支持团队的协作和交付价值。
下图展示了Scrum框架。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/7f36b3b66e084eb0894dfe0f06a0a335.png)
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/fefb78a37bdc49ff92dd8a4efb5f9164.png)
#### 3.2.2.1 Product Backlog（待办列表）
Product Backlog（产品代办列表）是由产品负责人（Product Owner）负责确定和管理的，它包含了需要开发的功能、改进和其他工作项。产品待办列表是一个优先级排序的列表，其中包含了所有需要开发的功能和任务，以及它们的优先级顺序。
The product owner, with input from the rest of the Scrum team and stakeholders, is ultimately responsible for determining and managing the sequence of works (product backlog items) and communicating it in the form of a prioritized (or ordered) list known as the product backlog.
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/13ee0d2d869f4480857cc9f3253b49c9.png)


在新产品开发中，产品待办列表的条目最初是满足产品负责人的愿景所需的功能。对于持续的产品开发，产品待办列表可能还包括新功能、对现有功能的更改、需要修复的缺陷、技术改进等内容。产品负责人与内部和外部利益相关者合作，收集和定义产品待办列表的条目。高价值的条目出现在产品待办列表的顶部，而较低价值的条目则出现在底部。而产品列表是一个不断演变的成果。随着业务条件的变化，或者Scrum团队对产品的理解增加，产品负责人可以添加、删除和修改条目。在实践中，许多团队使用相对大小的度量方式，例如story points（故事点）或ideal days（理想天数），来表达条目的大小。
On new-product development the product backlog items initially are features required to meet the product owner’s vision. 
For ongoing product development, the product backlog might also contain new features, changes to existing features, defects needing repair, technical improvements, and so on.
Product owner collaborates with internal and external stakeholders to gather and define the product backlog items.
High-value items appear at the top of the product backlog and the lower value items appear toward the bottom. 
The product backlog is a constantly evolving artifact. Items can be added, deleted, and revised by the product owner as business conditions change, or as the Scrum team’s understanding of the product grows.
In practice, many teams use a relative size measure such as story points or ideal days to express the item size.

下面两个例子展示了待办列表中的具体条目。这包含user story（角色故事）、描述和对应的acceptance criteria（验收标准）。
例1：用户故事: 在线用户注册
描述: 作为用户，我希望能够在线注册，以便我可以进行在线购物
验收标准:
只有当用户填写所有必填字段时，用户才能注册
在注册时使用的电子邮件不能是免费的电子邮件
用户在成功注册后将收到一封通知电子邮件

例2：用户故事: 搜索客户
描述: 作为市场经理，我想要搜索客户，以便我可以给他们打电话
验收标准:
正向测试: 当我在搜索框中输入“Eddie”并点击搜索按钮时，我将在网格中看到所有包含“Eddie”的条目
负向测试: 当我在搜索框中输入“ABC”并点击搜索按钮时，我将在网格中看到没有条目
附加功能: 如果没有结果，显示一条消息
附加功能: 如果返回了大量结果，显示分页
附加功能: 用户可以点击网格的列标题对信息进行排序

#### 3.2.2.2 Product Backlog Grooming（待办列表的精细化）
团队对产品待办列表中的条目进行创建、细化、估算和优先级排序的活动。
The activity of creating and refining product backlog items, estimating them, and prioritizing them is known as grooming.
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/933d3abf541742e396640ea8ac2ab315.png)
### 3.2.2.3 Sprint（冲刺）
在Scrum中，工作以最长为一个日历月的迭代或周期中进行，这个周期被称为Sprint或冲刺。
团队在每个Sprint中专注于完成一定量的工作，以便在Sprint结束时交付可触摸的价值给客户或用户。
每个Sprint都被设置为一个时间盒，因此它们都有固定的开始和结束日期。
它们的持续时间应该相同。
一个新的Sprint紧随上一个Sprint的完成而开始。
In Scrum, work is performed in iterations or cycles of up to a calendar month called sprints.
The work completed in each sprint should create something of tangible value to the customer or user.
Sprints are timeboxed so they always have a fixed start and end date, and generally.
They should all be of the same duration.
A new sprint immediately follows the completion of the previous sprint.
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/5a42cb3075094e3fb98f908b025552d5.png)
#### 3.2.2.4 Sprint Planning
产品待办列表可能代表了很多周甚至数月的工作。为了完成产品待办列表中的所有条目，需要进行一系列的Sprint。
Sprint Planning是由产品负责人、开发团队和ScrumMaster共同进行的活动。在这个活动中，团队将根据产品待办列表中的条目，确定在下一个Sprint中要构建的最重要的子集。
A product backlog may represent many weeks or months of work. To complete all the items in the product backlog, a series of sprints are to be carried out.
To determine the most important subset of product backlog items to build in the next sprint, the product owner, development team, and ScrumMaster perform sprint planning.

在Sprint Planning期间，产品负责人和开发团队就Sprint目标达成达成一致，明确了即将到来的Sprint应该实现的目标。基于Sprint目标，开发团队审查产品待办列表，并确定团队可以在可持续的工作节奏下，在即将到来的Sprint中实际完成的高优先级条目。
During sprint planning, the product owner and development team agree on a sprint goal that defines what the upcoming sprint is supposed to achieve.
Based on the sprint goal, the development team reviews the product backlog and determines the high priority items that the team can realistically accomplish in the upcoming sprint while working at a sustainable pace.

在Sprint Planning期间，许多开发团队会将每个目标特性细分为一组任务。这些任务的集合，以及它们关联的产品待办列表条目，形成了一个称为sprint backlog（Sprint待办列表）的第二个待办列表。
Sprint待办列表包含了在当前Sprint中需要完成的所有任务，以及与这些任务相关联的产品待办列表条目。团队会对这些任务提供估算（通常是以小时为单位）来评估完成每个任务所需的工作量。
Many development teams break down each targeted feature into a set of tasks. The collection of these tasks, along with their associated product backlog items, forms a second backlog called the sprint backlog.
The team provides an estimate (typically in hours) of the effort required to complete each task.

总的来说：在Sprint规划期间，团队会选择一个产品待办列表条目（尽可能是由产品负责人定义的下一个最重要的条目），将这个条目细分为任务，并确定所选的条目是否能够合理地在Sprint期间完成（与其他目标为同一Sprint的条目结合在一起）。如果所选的条目可以完成，并且还有能力完成更多的工作，团队会重复这个过程，直到团队没有能力再做更多的工作为止。
In summary: Select a product backlog item (whenever possible, the next most-important item as defined by the product owner), break the item down into tasks, and determine if the selected item will reasonably fit within the sprint (in combination with other items targeted for the same sprint). If it does fit and there is more capacity to complete work, repeat the cycle until the team is out of capacity to do any more work.

#### 3.2.2.5 Sprint Execution
在Sprint执行阶段，一旦Scrum团队完成了Sprint规划并就下一个Sprint的内容达成一致，开发团队开始进行所有必要的任务级工作，以完成功能的开发。
在这个阶段，“完成”意味着团队有很高的信心，所有为生产高质量功能所必需的工作都已经完成。
团队成员会定义他们自己的任务级工作，然后以他们认为最有利于实现Sprint目标的方式进行自组织。
Once the Scrum team finishes sprint planning and agrees on the content of the next sprint, the development team performs all the task-level work necessary to get the features done.
“Done” means there is a high degree of confidence that all the work necessary for producing good-quality features has been completed. 
Team members define their own task-level work and then self-organize in any manner they feel is best for achieving the sprint goal.

#### 3.2.2.6 Daily Scrum（每日Scrum会议）
每天的Sprint期间，理想情况下在相同的时间，开发团队成员会举行一个时间限定（15分钟或更短）的每日Scrum会议。
这个会议是一个检视和调整的活动，有时也被称为每日站会，因为通常的做法是在会议期间大家都站着，以促进简洁。
Each day of the sprint, ideally at the same time, the development team members hold a timeboxed (15 minutes or less) daily scrum.
This inspect-and-adapt activity is sometimes referred to as the daily stand up because of the common practice of everyone standing up during the meeting to help promote brevity.

在每日Scrum会议中，Scrum Master起到促进作用，而每个团队成员轮流回答以下三个问题：
1.我自上次每日Scrum会议以来完成了什么工作？
2.我计划在下次每日Scrum会议之前要处理什么工作？
3.有哪些障碍或阻碍正在阻止我取得进展？
ScrumMaster facilitating and each team member taking turns answering three questions: 
1.What did I accomplish since the last daily scrum? 
2.What do I plan to work on by the next daily scrum? 
3.What are the obstacles or impediments that are preventing me from making progress? 

每日Scrum会议的目的是让每个人都了解整体情况，包括他们在朝着Sprint目标的进展情况，他们希望对接下来一天的工作计划做出的任何修改，以及需要解决的问题。
The purpose is for everyone to understands the big picture of what is occurring, how they are progressing toward the sprint goal, any modifications they want to make to their plans for the upcoming day’s work, and what issues need to be addressed.

在每日Scrum会议中，团队成员不会解决问题，而是分享他们的进展、计划和遇到的问题。任何问题都会在每日Scrum会议之后与感兴趣的小组成员讨论。此外，会议也用于在开发团队成员之间传达Sprint待办列表条目的状态。通过这种方式，每日Scrum会议有助于团队了解整体情况，协调工作，及时解决问题，并确保团队朝着Sprint目标稳步前进。 
Not a problem-solving activity。
Talk about problems after the daily scrum and do so with a small group of interested member.
Communicate the status of sprint backlog items among the development team members.
It is an inspection, synchronization, and adaptive daily planning activity that helps a self-organizing team do its job better.

#### 3.2.2.7 Done（已完成）
“已完成的定义”指的是Sprint的结果作为一个潜在可交付的产品增量，也就是说，无论Scrum团队同意要做的工作都确实按照他们约定的“已完成的定义”来完成。
这个定义明确了完成的工作具有良好质量并且潜在可交付的程度。
简而言之，“已完成的定义”确保团队所完成的工作达到了一定的质量标准，并且可以作为潜在的可交付产品增量。
Sprint results as a potentially shippable product increment, meaning that whatever the Scrum team agreed to do is really done according to its agreed upon definition of done.
This definition specifies the degree of confidence that the work completed is of good quality and is potentially shippable. 
A bare-minimum definition of done should yield a complete slice of product functionality that is designed, built, integrated, tested, and documented.

“潜在可交付的”并不意味着所构建的东西必须实际上被交付。
交付是一个商业决策，经常受到诸如以下因素的影响：
我们是否有足够的功能或足够的客户工作流来证明客户部署的必要性？
考虑到我们刚刚在两周前发布了一个版本，我们的客户是否能够接受另一个变化？
“potentially shippable” does not mean that what got built must actually be shipped. Shipping is a business decision, which is frequently influenced by things such as: Do we have enough features or enough of a customer workflow to justify a customer deployment?
Can our customers absorb another change given that we just gave them a release two weeks ago? 

#### 3.2.2.8 Sprint Review
Sprint Review是Sprint结束时的一项重要活动，用于检视和调整正在构建的产品。
在Sprint Review中，参与者包括Scrum团队、利益相关者、赞助者、客户以及其他团队的感兴趣成员。这个活动的关键在于参与者之间进行的对话和讨论。
Sprint review is to inspect and adapt the product that is being built.
Critical to this activity is the conversation that takes place among its participants, which include the Scrum team, stakeholders, sponsors, customers, and interested members of other teams.

Sprint Review是专注于在整体开发工作的背景下审视刚刚完成的功能的活动。
在Sprint Review中，所有参与者都可以清晰地了解正在发生的事情，并有机会指导即将到来的开发工作，以确保创建最符合业务需求的解决方案。
Focused on reviewing the just-completed features in the context of the overall development effort.
Everyone in attendance gets clear visibility into what is occurring and has an opportunity to help guide the forthcoming development to ensure that the most business-appropriate solution is created.

#### 3.2.2.9 Sprint Retrospective
Sprint Retrospective是Sprint结束时的第二项检视和调整活动，通常在Sprint Review之后、下一个Sprint规划之前进行。在Sprint Retrospective中，开发团队、ScrumMaster和产品负责人讨论Scrum和相关技术实践的工作情况，以及存在的问题。重点是持续的过程改进。在Sprint Retrospective结束时，Scrum团队应该已经确定并承诺了一系列实际可行的过程改进行动。
The second inspect-and-adapt activity at the end of the sprint.
Frequently occurs after the sprint review and before the next sprint planning.
Sprint retrospective is an opportunity to inspect and adapt the process.
The development team, ScrumMaster, and product owner discuss what is and is not working with Scrum and associated technical practices. 
The focus is on the continuous process improvement.
At the end of a sprint retrospective the Scrum team should have identified and committed to a practical number of process improvement actions.

# 4. 需求工程
软件规格说明是详细描述软件系统功能、约束和交互的过程。它作为设计和开发阶段的蓝图。其目的在于确保所有利益相关者清楚地了解软件系统应该做什么以及它将如何执行。
软件规格说明的输出是软件需求文档，它作为流程的下一个活动的输入。
系统的需求是对系统应该做什么的描述，反映了客户对系统的需求。找出、分析、记录和检查这些需求和约束的过程被称为软件规格说明（有时也称为需求工程）。

软件规格说明的重要性：
清晰和理解：为所有利益相关者提供了对系统需求的清晰和详细描述。
开发指南：作为开发人员的路线图，确保系统按照规定的需求进行构建。
测试基础：为创建测试用例和根据需求验证系统提供了参考。
风险降低：在开发过程的早期阶段识别潜在问题和模糊之处，降低后期进行昂贵更改的风险。
Clarity and Understanding: Provides a clear and detailed description of system requirements for all stakeholders.
Guidance for Development: Acts as a roadmap for developers, ensuring that the system is built according to specified requirements.
Basis for Testing: Provides a reference for creating test cases and validating the system against requirements.
Risk Reduction: Identifies potential issues and ambiguities early in the development process, reducing the risk of costly changes later.

## 4.1 Software Specification Processes
下图展示了需求工程的过程，第二章已经介绍过。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/b45f76493fea46649cd00090eb9844c3.png)
其包含四个高等级活动：
1.可行性研究：用于确定所提议的系统在技术上、经济上和运营上是否可行。
结果：可行性报告，提供是否继续进行项目的建议。
2.需求征集和分析：用于收集、分析和完善软件系统的需求。
结果：一套经过分析和完善的需求，以确保清晰、完整和可行。
3.需求规格：将收集和分析的需求以清晰和结构化的格式进行文档化。
结果：详细的软件需求文档（SRD），提供了对系统功能和约束的清晰和全面的描述。
4.需求验证：确保文档化的需求准确反映了利益相关者的需求和期望。
结果：经过审查和批准的验证需求，确保它们准确地反映了所需的系统。
1.Feasibility study: To determine whether the proposed system is technically, economically, and operationally feasible.
Outcome: A feasibility report that provides a recommendation on whether to proceed with the project. 
2.Requirements elicitation and analysis: To gather, analyze, and refine the requirements for the software system.
Outcome: A comprehensive set of requirements that have been analyzed and refined to ensure clarity, completeness, and feasibility. 
3.Requirements specification: To document the gathered and analyzed requirements in a clear and structured format.
Outcome: A detailed Software Requirements Document (SRD) that provides a clear and comprehensive description of the system’s functionalities and constraints.
4.Requirements validation: To ensure that the documented requirements accurately reflect the needs and expectations of stakeholders.
Outcome: Validated requirements that have been reviewed and approved by stakeholders, ensuring they accurately reflect the desired system. 

需求工程包含3个关键活动：通过与利益相关者交换发现需求（抽取和分析）；将这些需求转换为标准格式（规格说明）；检查需求是否实际上定义了客户所要的系统（确认）。
下图描述了实践中这三个活动的相互交织。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/4692697566244b98b5f549c126418073.png)
## 4.2 需求抽取
需求可以以高层次、抽象的方式描述，即系统应该提供的服务或对系统的约束。另一方面，它也可以是对系统功能的详细、正式的定义。
工程师当与非技术人员（如最终用户和业务利益相关者）进行沟通时，使用高层次描述；当与技术人员（如软件开发人员、架构师和技术利益相关者）进行沟通时，使用详细描述。
The requirements can be described in a high-level, abstract statement of a service that a system should provide or a constraint on a system. At the other extreme, it is a detailed, formal definition of a system function.
In high-level description when communicating with non-technical personnel such as end-users and business stakeholders.
In detail description when communicating with technical personnel such as software developers, architects, and technical stakeholders.

### 4.2.1 User Requirements（用户需求）
用户需求是指描述用户从系统中需要什么的需求。它们集中于能够使用户实现其目标的功能和特性。
User requirements describe what the users need from the system. They focus on the functionalities and features that will enable users to achieve their goals. 
特点包括：用户中心：强调最终用户的需求和观点，关注他们的使用体验和目标实现。
功能性：描述系统应该在高层次上做什么，即关注系统的功能和特性。
非技术性：通常用最终用户和利益相关者能够理解的语言书写，而不涉及技术细节。
Characteristics:User-Centric: Emphasize the needs and perspectives of the end-users.
Functional: Describe what the system should do in high-level.
Non-Technical: Typically written in a language understandable by users and stakeholders. 

下面给出例子：
例1：对于电子商务平台：
用户应该能够搜索产品。
用户应该能够将产品添加到购物车中。
用户应该能够使用各种支付方式完成购买。
例2：对于社交媒体应用：
用户应该能够创建和编辑个人资料。
用户应该能够发布更新和分享内容。
用户应该能够发送和接收消息。

用户在定义用户需求中扮演着主要的贡献者角色，因为他们最了解自己的需求以及系统应该如何支持他们的任务。
收集用户需求的技术包括：
采访：与用户进行一对一的采访，以获取详细的见解。
调查和问卷调查：使用调查来从更广泛的受众中收集意见。
研讨会和焦点小组：促进协作讨论，以获取不同的观点。
观察：观察用户在其自然环境中的工作流程和挑战，以了解他们的需求。
用户故事和使用案例：以用户故事和使用案例的形式记录需求，以捕捉用户与系统的交互。

### 4.2.2 System Requirements（系统需求）
系统需求描述了系统的技术规格和约束，它们侧重于通过添加技术细节来完善用户需求。
System requirements describe the technical specifications and constraints of the system. They focus on refining user requirements by adding technical details. 
特点包括：系统中心：强调系统的架构、设计和技术细节。
功能性和非功能性：包括系统应该做什么以及它应该如何执行。
技术性：用开发人员和技术利益相关者能够理解的语言书写。
Characteristics: System-Centric: Emphasize the architecture, design, and technical details of the system.
Functional and Non-Functional: Include both what the system should do and how it should perform.
Technical: Written in a language understandable by developers and technical stakeholders.

下面给出一个例子将分别给出其的用户需求和系统需求，通过这个例子我们可以更好理解两者的区别：
医疗保健系统中关于药品管理报告：
用户需求：MHC-PMS需要生成每月的管理报告，显示每个诊所在该月内开出的药品成本。
系统需求：
1.在每个月的最后一个工作日，系统需要生成一份总结报告，包括开出的药品、药品成本以及开药的诊所。
2.系统应在每个月最后一个工作日的17:30之后自动生成报告，以便打印。
3.每个诊所都需要生成一份报告，报告中应列出每种药品的名称、处方总数、开出的剂量数量以及药品的总成本。
4.如果药品有不同的剂量单位（例如，10毫克、20毫克），则需要为每个剂量单位分别生成报告。
5.所有成本报告的访问权限应限制在管理访问控制列表上列出的授权用户。

### 4.2.3 Functional Requirements（功能性需求）
软件需求通常被分类为功能性需求和非功能性需求。
功能性需求：描述系统必须执行的具体行为和功能。它们详细说明系统应该做什么来满足用户的需求。
非功能性需求：描述系统的运行特性和约束。它们详细说明系统应该如何执行，而不是应该做什么。非功能性需求通常适用于整个系统，而不是单个系统特性或服务。
Functional requirements: describe the specific behaviors and functions that a system must perform. They detail what the system should do to meet the needs of its users.
Non-functional requirements: describe the system’s operational qualities and constraints. They detail how the system should perform rather than what it should do. Non-functional requirements often apply to the system as a whole, rather than individual system features or services. 

在用户需求中，功能性需求通常以抽象的方式描述，以便系统用户能够理解。
When expressed as user requirements , functional requirements are usually described in an abstract way that can be understood by system users.
更具体的功能性系统需求则会详细描述系统的功能、输入和输出、异常情况等。
More specific functional system requirements describe the system functions, its inputs and outputs, exceptions, etc., in detail. 

下面给出功能性需求的例子，情景与前面的MHC-PMS医疗系统一致：
1.用户应该能够搜索所有诊所的预约列表。
2.系统应该每天为每个诊所生成一个当天预约的病人名单。
3.使用系统的每位员工应该通过他们的八位数字员工编号得到唯一标识。

系统的功能性需求规范应该既完整又一致：
完整性意味着所有用户需要的服务都应该被定义清楚。一致性意味着需求不应该存在矛盾的定义。然而，在实践中，对于大型复杂系统来说，要实现需求的一致性和完整性几乎是不可能的。这是因为在为复杂系统编写规范时很容易出现错误和遗漏，而且大型系统中有许多利益相关者，这些利益相关者拥有不同甚至矛盾的需求。

功能性需求的特点如下：
行为性：功能性需求关注系统必须执行的动作和操作。
用户中心：通常源自用户需求和使用案例。
具体且可衡量：需求清晰定义，并且可以进行正确性测试。
Behavioral: Focus on the actions and operations that the system must perform. 
User-Centric: Often derived from user needs and use cases. 
Specific and Measurable: Clearly defined and can be tested for correctness.
### 4.2.4 Non-functional Requirements（非功能性需求）
非功能性需求，顾名思义，是指那些与系统向用户提供的具体服务或操作无直接关系的需求。
这些需求通常涉及系统的特性，如可靠性、响应时间、可扩展性、安全性或可用性等。通常会规定系统整体的约束特性。
Non-functional requirements, as the name suggests, are requirements that are not directly concerned with the specific service or operation delivered by the system to its users.
System properties such as reliability, response time, scalability, security, or availability.
Usually specify constrain characteristics of the system as a whole.

通常比单个功能性需求更为关键，因为未能满足非功能性需求可能意味着整个系统无法使用。
未能满足非功能性需求可能导致整个系统无法使用。
非功能性需求的实现可能会在整个系统中复杂地分散开来。
它们可能会影响系统的整体架构，而不仅仅是单个组件。
单个非功能性需求可能会产生多个相关的功能性需求。

非功能性需求的特点如下： 
质量属性：非功能性需求关注系统的性能、安全性、可用性、可靠性、可扩展性等属性。
系统中心：通常源自技术和业务约束。
可衡量：可以量化并进行合规性测试。
Quality Attributes: Focus on performance, security, usability, reliability, scalability, and other attributes. 
System-Centric: Often derived from technical and business constraints. 
Measurable: Can be quantified and tested for compliance.

非功能性需求的分类如下：
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/feb4f1ef7841400b846e52ff19a6259b.png)
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/d069eaea942a41f2be582e35b8de4e62.jpeg#pic_center)
产品需求：这些需求指定或限制软件的行为。
组织需求：这些需求是从客户和开发组织的政策和程序中衍生出来的广泛系统需求。
外部需求：这个广泛的分类涵盖了所有从系统外部因素和其开发过程中衍生出来的需求。

例子如下，接之前的MHC-PMS医疗系统：
产品需求：MHC-PMS系统应在正常工作时间内（周一至周五，08:30至17:30）对所有诊所开放。在正常工作时间内，系统的停机时间在任何一天内不得超过五秒。
组织需求：MHC-PMS系统的用户应使用他们的卫生当局身份卡进行身份验证。
外部需求：系统应当按照HStan-03-2006-priv中的要求实现病人隐私条款。

非功能性需求的测试性需要具体：
错误例子如下：系统应该易于医务人员使用，并且应该组织得使用户错误最小化。
正确例子如下：医务人员在接受四小时培训后应能够使用系统的所有功能。在此培训后，受过培训的用户在系统使用过程中的平均错误次数不应超过每小时两次。

下图展示了非功能性需求的度量。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/1bea444dac97441e8804c905851d972d.png)
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/38b4fd9103cc41e19e22804f3538990e.png)

可测试的非功能性需求具有以下特点：
具体性：清晰地定义了预期的内容。
可衡量性：提供可以量化的度量标准。
可实现性：在项目约束条件内是现实和可达成的。
相关性：与系统的目标和目的直接相关。
上下文：指定了需求应该满足的上下文环境。

下面给出一个可测试的非功能性需求的例子：
例1：系统在峰值负载条件下应能够以每秒处理1,000笔交易，并在2秒内给出响应时间。
这个需求具体明确，可量化，可在上下文中实现，并且可以使用性能测试工具进行测试。

下面给出一个不可测试的非功能性需求的例子：
例1：可用性：系统应该用户友好且直观。
这个需求是模糊的和主观的。它没有提供具体的测试标准或度量标准。术语“用户友好和直观”是主观的，并且容易引起不同用户对什么构成用户友好性的不同看法。这个例子缺乏具体的度量标准，不能提供可用于评估可用性的具体、可量化的标准。此外，这个需求也不清楚系统的哪些方面应该是用户友好的，也没有说明如何衡量直观性。
对于这个例子中我们现在进行改进：
系统应该在至少50名用户样本进行的用户反馈调查中，达到至少80%的系统可用性评分（SUS分数）。
这个改进后的陈述明确了可用性度量标准（SUS分数）、用户反馈调查，并提供了目标分数（80%）。它指定了至少50名用户的样本大小，因此具有可测试性，可以用于评估系统的可用性。
也可以改进成：用户应该能够在第一次尝试中，在3分钟内完成主要任务（例如，下订单），且不超过两次错误。
这个改进后的陈述明确了主要任务的完成（例如，下订单），并且提供了可量化的度量标准，即3分钟内完成且不超过两次错误。它指定了在第一次尝试中完成主要任务的上下文环境，因此具有可测试性，可以用于评估系统的可用性。

### 4.2.5 Emergent System Properties（新出现的系统特性）
新出现的系统特性指的是从系统组件的相互作用和集体行为中产生的特征。这些特性不是单个组件所能归因的，而是从整个系统中产生的。
Emergent system properties are characteristics that arise from the interactions and collective behavior of the system components. These properties are not attributable to any single component but emerge from the system as a whole.
例如：
性能：指的是系统的整体速度和效率。
可靠性：这涉及系统在时间和不同条件下正确运行的能力。
安全性：这包括系统保护数据和抵抗潜在攻击的能力。
可扩展性：这涉及系统在不降低性能的情况下处理增加的负载的能力。
Performance: Overall speed and efficiency of the system.
Reliability: The system’s ability to function correctly over time and under varying conditions.
Security: The system’s ability to protect data and resist attacks.
Scalability: The system’s ability to handle increased load without degrading performance.

突出新出现的系统特性的重要性包括：
1.系统范围影响：新出现的特性影响整个系统，对其整体成功至关重要。
2.可见性和意识：明确突出这些需求可以确保所有利益相关者意识到它们的重要性和影响。
3.设计考虑：与新出现特性相关的非功能性需求通常会影响架构和设计决策。
4.测试和验证：这些需求需要特定的测试策略，以确保系统满足期望的性能和可靠性标准。
5.风险管理：早识别和解决这些需求有助于减轻与系统性能和可靠性相关的风险。
1.System-Wide Impact: Emergent properties affect the entire system and are critical to its overall success. 
2.Visibility and Awareness: Explicitly highlighting these requirements ensures that all stakeholders are aware of their importance and impact.
3.Design Considerations: Non-functional requirements related to emergent properties often influence architectural and design decisions.
4.Testing and Validation: These requirements need specific testing strategies to ensure that the system meets the desired performance and reliability standards.
5.Risk Management: Identifying and addressing these requirements early helps mitigate risks associated with system performance and reliability. 

### 4.2.6 Feasibility Study（可行性研究）
可行性研究是在项目启动前进行的评估，用于确定项目的可行性。这通常包括技术可行性、经济可行性和运营可行性的评估。
技术可行性包括评估技术栈、技术资源和所需技能，识别潜在的技术挑战和风险，并确定项目是否在技术上可行。
经济可行性包括成本效益分析，将估计成本与预期收益进行比较，评估所需的财务资源和可用资源，以确定项目是否在经济上可行。
运营可行性包括评估系统与组织运营的契合度，评估组织支持和维护系统的能力，以确定项目是否在运营上可行。

## 4.3 Requirements Elicitation and Analysis（需求获取和分析）
需求获取和分析是指软件工程师与客户和系统最终用户合作，以了解以下内容：应用领域、系统应该提供的服务、系统所需的性能、硬件约束等。
可能涉及组织中各种不同类型的人员，包括：与系统进行交互的最终用户、组织中其他受影响的人员、开发或维护其他相关系统的工程师、业务经理、领域专家、工会代表。

需求获取和分析是一个迭代的过程，不是一次性完成的，而是需要不断地从一个活动向其他活动提供反馈。
下图展示了需求抽取和分析过程。![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/aece571bd44e442cbaf973cc6d152fd7.png)

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/4716ce3f7ab74f1782d1b1aa4ad66434.png)
需求发现：这是与系统利益相关者进行互动，以发现他们的需求的过程。
需求分类和组织：这个活动将不结构化的需求集合进行分类和组织，将相关的需求归类到一起，并将它们组织成一致的群组。
最常见的分类方法是利用系统架构模型来识别子系统，并将需求与每个子系统关联起来。
需求优先级确定和协商：当涉及多个利益相关者时，需求可能会发生冲突。这个活动涉及确定需求的优先级，并通过协商找到和解决需求之间的冲突。
需求规格化：在这个阶段，需求会被详细地记录和规范化，以便后续的开发和测试。
Requirements discovery - This is the process of interacting with stakeholders of the system to discover their requirements.
Requirements classification and organization - This activity takes the unstructured collection of requirements, groups related requirements, and organizes them into coherent clusters.
The most common way of grouping requirements is to use a model of the system architecture to identify sub-systems and to associate requirements with each sub-system.
Requirements prioritization and negotiation - When multiple stakeholders are involved, requirements will conflict. This activity is concerned with prioritizing requirements and finding and resolving requirements conflicts through negotiation.
Requirements specification - The requirements are documented and input into the next round of the spiral.

这个阶段的挑战有：
1.利益相关者通常除了最一般的术语外并不清楚他们从计算机系统中想要什么；他们可能会发现很难明确表达需求；他们可能会提出不切实际的要求，因为他们不知道什么是可行的，什么是不可行的。
2.系统中的利益相关者以自己的术语表达需求，并带有对自己工作的隐含知识。
3.不同的利益相关者有不同的需求和优先级，并且可能以不同的方式表达这些需求，其中一些需求可能存在共性和冲突。
4.政治因素可能影响系统的需求。
5.经济和商业环境是动态的。

### 4.3.1 Requirement Discovery（需求发现）
需求发现是指收集有关所需系统和现有系统的信息，并从这些信息中提炼用户和系统需求的过程。在需求发现阶段，信息的来源包括文档、利益相关者和类似系统的规格说明。常用的方法包括访谈、观察、场景分析和原型制作。

利益相关者涵盖了从系统最终用户到管理人员再到外部监管机构的范围。例如：精神保健患者信息系统的利益相关者包括：患者，医生，护士，医疗接待人员，IT工作人员，医疗伦理管理者，医疗管理者，医疗记录工作人员。

#### 4.3.1.1 Interview（访谈）
大多数需求工程都包含与利益相关者的正式或非正式访谈。需求工程团队与系统利益相关者进行面谈，向他们提出关于他们目前使用的系统以及将要开发的系统的问题。从这些问题的答案中得出需求。
访谈又可以分成两种：
封闭式访谈：利益相关者回答一组预定义的问题。
开放式访谈：没有预定义的议程。需求工程团队与系统利益相关者探讨一系列与系统相关的问题。

访谈的优点如下：
1.对利益相关者的工作内容有一个整体的了解。
2.了解他们可能如何与新系统进行交互。
3.了解他们在当前系统中面临的困难。

访谈可能存在的困难如下：
应用专家使用特定于领域的术语和行话，通常以精确而微妙的方式使用这些术语，这容易让需求工程师误解。
一些领域知识对于利益相关者来说可能非常熟悉，以至于他们要么觉得很难解释，要么认为这些知识是如此基础和普遍，以至于不值得提及。

因为在组织中不同人之间存在微妙的权力关系。这可能导致一些人不愿意坦诚地讨论可能影响需求的政治和组织问题。

有效的访谈者具有以下两个特点：
1.开放心态，对需求没有预设观念，愿意倾听利益相关者的意见和需求。
2.他们应该通过提出引导性问题、提出需求建议，或者共同探讨原型系统等方式来引导面谈，促进讨论的展开。

访谈获取的信息是对系统的其他信息的补充，这些信息可能来自描述业务流程或现有系统的文档、用户观察等。

#### 4.3.1.2 Scenarios（故事和场景）
系统用户可以理解并批评与软件系统交互的场景。利用基于场景的讨论所获得的信息来制定实际的系统需求。场景是对交互会话的描述。每个场景通常涵盖一个或少数几个可能的交互。场景从交互概述开始。在需求获取过程中，会逐步添加细节，以创建该交互的完整描述。

例如我们可以从下面的示例场景中获得需求。
初始假设：患者已经见过医疗接待员，接待员在系统中创建了记录并收集了患者的个人信息（姓名、地址、年龄等）。一名护士登录系统并正在收集医疗历史。
正常流程：护士通过姓氏搜索患者。如果存在多个相同姓氏的患者，则使用名字（英文的名）和出生日期来识别患者。
护士选择菜单选项以添加医疗历史。
护士按照系统的提示输入以下信息：其他医疗咨询（自由文本输入），精神健康问题（自由文本输入），现有的医疗状况（护士从菜单中选择状况），当前服用的药物（从菜单中选择），过敏反应（自由文本），家庭生活（填写表格）。
可能出现的问题：如果患者的记录不存在或无法找到，护士应创建新记录并记录个人信息。
如果患者的病情或药物没有在菜单中列出，护士应选择“其他”选项并输入自由文本描述病情/药物。
如果患者不能或不愿意提供医疗历史信息，护士应输入自由文本记录患者的无法/不愿意提供信息的情况。系统应打印标准排除表格，说明缺乏信息可能导致治疗受限或延迟。这应由患者签字并交给患者。
其他活动：在输入信息时，其他工作人员可以查阅记录，但不能编辑。
系统完成后的状态：用户已登录。
包括医疗历史在内的患者记录已输入数据库。
系统日志中添加了一条记录，显示会话的开始和结束时间以及参与的护士。

基于场景的需求获取涉及与利益相关者合作，以确定场景并捕获要包含在这些场景中的细节。场景可以以文本形式编写，并辅以图表、屏幕截图等。或者，也可以采用更结构化的方法，如事件场景或用例。用例识别了系统与其用户或其他系统之间的个体交互。每个用例都应该有文本描述的文档。然后，可以将用例与UML中的其他模型进行关联，以更详细地开发场景。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/b617b6fceff1429b80cbd16370b08166.png)

下面展示了一个用例，情景是设置咨询。
"设置咨询"允许两个或更多个在不同办公室工作的医生同时查看同一份记录。一个医生通过从在线医生的下拉菜单中选择相关人员来启动咨询。然后患者的记录会显示在他们的屏幕上，但只有发起咨询的医生可以编辑记录。另外，还会创建一个文本聊天窗口来帮助协调行动。假设会另外设置电话会议以进行语音通信。

用例侧重于系统交互，因此不太适合引发下列内容：
1.约束。
2.高层业务。
3.非功能性需求。
4.领域需求。

#### 4.3.1.3 Ethnography（人种学调查）
系统是在社会和组织环境中使用的，软件系统的需求可能是由这种环境衍生或受到限制的。满足这些社会和组织需求通常对系统的成功至关重要。Ethnography（人种学调查）是一种观察技术，可用于理解运营过程，并帮助推导这些过程的支持需求。分析人员将自己沉浸在工作环境中，观察参与者实际参与的任务。帮助发现反映人们实际工作方式的隐含系统需求。

Ethnography（人种学调查）特别适合发现以下两种类型的需求：
从人们实际工作方式中推导出的需求，而不是流程定义所规定的工作方式。
从人们合作和对其他人活动的意识中推导出的需求。

Ethnography（人种学调查）侧重于最终用户，这种方法：
并非总是适用于发现组织或领域需求。
也并非总能够识别应该添加到系统中的新功能。

### 4.3.2 Requirements Specification（需求规格说明）
Requirements Specification（需求规格说明）是指将用户和系统需求写入需求文档的过程。用户和系统需求应该清晰、无歧义、易于理解、完整和一致。利益相关者以不同的方式解释需求，并且需求中通常存在固有的冲突和不一致性。系统的用户需求应该以一种不需要详细技术知识就能理解的方式描述系统的功能性和非功能性需求。仅指定系统的外部行为，不应包括系统架构或设计的细节。用自然语言、简单的表格、表单和直观的图表来编写用户需求。系统需求是用户需求的扩展版本。系统需求提供详细说明并解释系统应该如何满足用户需求。
The process of writing down the user and system requirements in a requirements document.
The user and system requirements should be clear, unambiguous, easy to understand, complete, and consistent.
Stakeholders interpret the requirements in different ways and there are often inherent conflicts and inconsistencies in the requirements.
The user requirements for a system should describe the functional and nonfunctional requirements in a way they are understandable by system users who don’t have detailed technical knowledge.
Specify only the external behavior of the system.
Should not include details of the system architecture or design.
Write user requirements in natural language, with simple tables, forms, and intuitive diagrams.
System requirements are expanded versions of the user requirements.
System requirements add detail and explain how the user requirements should be provided by the system.

系统需求可以作为系统实施合同的一部分。需求规格描述系统的外部行为和操作约束。系统需求可以用自然语言编写，但也可以使用基于表单、图形系统模型或数学系统模型的其他符号。图形模型在需要展示状态如何变化或需要描述一系列操作时最有用。

比如：系统必须及时生成月度报告。
每月佣金必须在每月的最后一天计算。
而错误的例子如下：为了缩短响应时间，应将配置数据预加载到内存缓存中。

在需求规格说明中难以完全排除所有设计信息的原因。以下是对每个原因的解释：

你可能需要设计系统的初始架构来帮助构建需求规格说明。系统需求根据构成系统的不同子系统进行组织。系统可能需要与现有系统进行互操作，这会对设计施加限制并对新系统施加要求。使用特定的架构来满足非功能性需求可能是必要的。

#### 4.3.2.1 Natural Language Specification（自然语言规格说明）
自然语言规格说明是表达性强、直观且通用的。但也可能存在模糊和歧义，其含义取决于读者的背景。
为了降低在使用自然语言进行需求规格说明时的误解，可以使用以下方式：
1.发明一个标准格式，并确保所有需求定义符合该格式。标准化格式可以减少遗漏，并使需求更容易检查。
2.使用语言一致性来区分强制性和期望性的需求。
3.使用文本高亮来标出需求的关键部分。
4.不要假设读者理解技术软件工程语言。
5.为每个用户需求关联一个理由。这个理由应该解释为什么包含了这个需求。

#### 4.3.2.2 Structured Specification（结构化规则说明）
这是一种使用预定义的结构或模板以自然语言撰写系统需求的方式。
用户需求可以被写在卡片上，每张卡片上写一个需求。每张卡片上可能有多个字段，例如需求的理由、对其他需求的依赖关系、需求的来源、支持材料等等。
下图展示了胰岛素泵的结构化规则说明。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/0b9a4f9d7fb54aabba94ba40450f5718.png)
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/97b36d14153c4f768ea8798395d00edb.png)

我们也可以使用表格或图形模型来克服自然语言的局限性，以展示计算、系统状态变化、系统交互和执行顺序。而表格特别适用于存在多种可能的情况时。
例如上面的胰岛素泵例子中我们可以用表格呈现如下规则说明。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/2476139891cf420bbe76d5840e0fd1fe.png)
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/9412569c353e4afdaf05dd8d33e7d919.png)

前面说的用况是一种图形化模型和结构化文本描述用户与系统交互的方式。也是一种进行规格说明的方式。

### 4.2.3 Software Requirements Document（SRD，软件需求文档化）
Software Requirements Document（SRD，软件需求文档化），有时称为Software  Requirement Specification（SRS，软件需求规格说明），它是一个正式的文件，用于捕获和规定软件系统的功能性和非功能性需求。它作为开发团队和其他利益相关者的蓝图。
它可以促进利益相关者之间，包括客户、开发人员和测试人员之间的清晰沟通。为软件的设计、开发和测试提供了详细的指南。作为利益相关者之间关于系统预期功能和约束的合同协议。
A Software Requirements Document (SRD) is a formal document that captures and specifies the functional and nonfunctional requirements of a software system. It serves as a blueprint for the development team and other stakeholders.
Purpose: 
Communication: Facilitates clear communication between stakeholders, including clients, developers, and testers.
Guidance: Provides a detailed guide for the design, development, and testing of the software.
Agreement: Acts as a contractual agreement between stakeholders on the expected functionalities and constraints of the system.

在外部承包商开发软件系统时，需求文档至关重要。针对需求相对稳定的业务系统，编写详细的需求文档是合适的。对于采用敏捷开发方法的项目，需求变化非常迅速，以至于需求文档一经编写就已经过时。然而，即使是在这种情况下，编写一个简短的支持性文档来定义系统的业务和可靠性需求仍然是有益的。

需求文档的重要性：
清晰和理解：确保所有利益相关者对系统需求有清晰共享的理解。
项目规划：有助于项目规划，包括资源分配、时间线估计和风险管理。
范围管理：通过清晰地定义包含和排除的内容，有助于管理项目范围，防止范围蔓延。
测试基础：为创建测试用例提供基础，并验证系统是否满足指定的需求。
变更管理：在项目生命周期中便于管理对需求的变更。

需求文档的用户如下：
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/02d20e3f85f44a63ae1ca6dd7e540de5.png)
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/7cce01968297483ea11ff70bb87d958f.png)
创建软件需求文档的最佳实践：
吸引利益相关者：让所有相关的利益相关者参与需求收集过程，以确保全面覆盖。
清晰明了：使用清晰而明确的语言，以避免误解。
优先级需求：确定并对关键需求进行优先排序，以确保首先解决最重要的方面。
使用多种技术：结合不同的技术（例如访谈、调查、研讨会）全面收集需求。
验证和核实：持续与利益相关者验证和核实需求，以确保准确性和完整性。
保持可追溯性：确保每个需求都可以追溯到其来源，并贯穿整个开发过程。
迭代细化：根据反馈和测试结果，迭代地完善需求。
Engage Stakeholders: Involve all relevant stakeholders in the requirements gathering process to ensure comprehensive coverage.
Be Clear and Unambiguous: Use clear and precise language to avoid misunderstandings.
Prioritize Requirements: Identify and prioritize critical requirements to ensure that the most important aspects are addressed first.
Use Multiple Techniques: Combine different techniques (e.g., interviews, surveys, workshops) to gather requirements comprehensively.
Validate and Verify: Continuously validate and verify requirements with stakeholders to ensure accuracy and completeness.
Maintain Traceability: Ensure that each requirement can be traced back to its source and throughout the development process.
Iterative Refinement: Refine the requirements iteratively based on feedback and testing results.

在软件需求文档（SRD）中规定合适的细节级别对于确保清晰性、有效沟通和项目成功结果是重要的。软件需求文档应该提供足够细节以指导开发的同时保持清晰和可管理。
平衡细节和可管理性的方式如下：
避免过度规范化：提供过多细节可能会使文档笨重且难以管理。
避免不足规范化：提供过少细节可能会导致需求的误解和遗漏。
使用视觉辅助工具：使用图表、模型和表格来更清晰地传达复杂信息。
迭代细化：根据反馈和测试结果持续完善需求。

Specifying the right level of detail in a Software Requirements Document (SRD) is critical for ensuring clarity, effective communication, and successful project outcomes. The SRD should provide sufficient detail to guide development while remaining clear and manageable.
Balancing Detail and Manageability：
Avoid Over-Specification: Providing too much detail can make the document cumbersome and difficult to manage.
Avoid Under-Specification: Providing too little detail can lead to misunderstandings and gaps in the requirements.
Use Visual Aids: Use diagrams, models, and tables to convey complex information more clearly.
Iterative Refinement: Continuously refine the requirements based on feedback and testing results.

影响软件需求文档细节级别的因素如下：
项目复杂性：更复杂的项目通常需要更详细的需求文档。
利益相关者需求：不同的利益相关者根据其角色和责任可能需要不同级别的细节。
开发方法论：选择的开发方法论（例如敏捷、瀑布模型）会影响所需的细节级别。
法规和合规要求：受到法规要求约束的项目可能需要更详细的文档记录，以满足法律和合规性要求。
风险管理：高风险的项目可能需要更详细的需求文档，以减轻潜在问题。
Project Complexity: More complex projects typically require more detailed requirements.
Stakeholder Needs: Different stakeholders may require varying levels of detail based on their roles and responsibilities.
Development Methodology: The chosen development methodology (e.g., Agile, Waterfall) can influence the level of detail needed.
Regulatory and Compliance Requirements: Projects subject to regulatory requirements may need more detailed documentation.
Risk Management: High-risk projects may require more detailed requirements to mitigate potential issues.

例如：开发重要系统、外包项目、医疗仪器控制系统需要更多细节。
而内部软件开发、使用敏捷方法开发、社交媒体平台开发可以少一些细节。

需求文档的结构如下：
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/7081f8f22d3148b8a3c153956fe349aa.png)

### 4.2.4 Requirements Validation（需求确认）
需求验证是指检查需求是否正确地定义了客户真正想要的系统。
Requirements validation is the process of checking that requirements correctly define the system that the customer really wants.

这一过程的重要性在于，如果在开发过程中或者系统投入使用后发现了软件需求文档（SRD）中的错误，可能会导致大量的重复工作成本。

不同类型的检查方式如下：
1.有效性检查：这是指对需求文档中相关利益相关者提出的功能进行验证，以确保这些功能与系统需要执行的任务相一致。
2.一致性检查：这是指对需求文档中的各项需求进行验证，以确保它们之间没有冲突。也就是说，需求文档中不应该存在相互矛盾的约束条件或对同一系统功能的不同描述。
3.完整性检查：确保其中包含了系统用户所期望的所有功能和约束条件的需求。
4.现实性检查：这是指利用现有技术知识对需求进行检查，以确保这些需求在现实中可以实际实现。
5.可验证性：为了减少客户和承包商之间的争议，系统需求应该被写成可以验证的形式。
1.Validity checks：The functions proposed by stakeholders should be aligned with what the system needs to perform. You may find later that there are additional or different functions are required instead.
2.Consistency checks：Requirements in the document should not conflict. That is, there should not be contradictory constraints or different descriptions of the same system function. 
3.Completeness checks：The requirements document should include requirements that define all functions and the constraints intended by the system user.
4.Realism checks：Using knowledge of existing technology, the requirements should be checked to ensure that they can be implemented realistically. 
5.Verifiability：To reduce the potential for dispute between customer and contractor, system requirements should always be written so that they are verifiable. 

需求验证的技术手段如下：
1.需求审查：通过由一个团队的审查者系统性地分析需求，检查其中是否存在错误和不一致之处。
2.原型验证：这种方法是通过向最终用户和客户展示系统的可执行模型来进行验证。
3.测试用例生成：需求应该是可测试的。如果在验证过程中设计了与需求相关的测试用例，通常会揭示出需求中的问题。如果很难或几乎不可能设计测试用例，通常意味着这些需求在实施过程中会面临困难，因此需要重新考虑。
1.Requirements reviews：The requirements are analyzed systematically by a team of reviewers who check for errors and inconsistencies.
2.Prototyping：In this approach to validation, an executable model of the system in question is demonstrated to end-users and customers.
3.Test-case generation:Requirements should be testable. If the tests for the requirements are devised as part of the validation process, this often reveals requirements problems. If a test is difficult or impossible to design, this usually means that the requirements will be difficult to implement and should be reconsidered.
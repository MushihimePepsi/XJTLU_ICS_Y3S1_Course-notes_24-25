- [1.Introduction](#1introduction)
  - [1.1 What software engineering is and why it is important（什么是软件工程，为什么它很重要）](#11-what-software-engineering-is-and-why-it-is-important什么是软件工程为什么它很重要)
    - [1.1 We can’t run the modern world without software（我们的世界离不开软件）](#11-we-cant-run-the-modern-world-without-software我们的世界离不开软件)
    - [1.1.1 What is Software Engineering？（什么是软件工程）](#111-what-is-software-engineering什么是软件工程)
  - [1.2 The development of different types of software systems may require different software engineering techniques（开发不同类型的软件系统可能需要不同的软件工程技术）](#12-the-development-of-different-types-of-software-systems-may-require-different-software-engineering-techniques开发不同类型的软件系统可能需要不同的软件工程技术)
  - [1.3 Web-BASED software engineering（互联网软件工程）](#13-web-based-software-engineering互联网软件工程)
  - [1.4 Some ethical and professional issues that are important for software engineers（对于软件工程师很重要的道德和职业问题）](#14-some-ethical-and-professional-issues-that-are-important-for-software-engineers对于软件工程师很重要的道德和职业问题)
- [2. Software Process （软件过程）](#2-software-process-软件过程)
  - [2.1 Software Process Models（软件过程模型）](#21-software-process-models软件过程模型)
    - [2.1.1 The Waterfall Model（瀑布模型）](#211-the-waterfall-model瀑布模型)
    - [2.1.2 Incremental Model（增量式开发）](#212-incremental-model增量式开发)
    - [2.1.3 Reuse-oriented software engineering（集成与配置）](#213-reuse-oriented-software-engineering集成与配置)
  - [2.2 过程活动](#22-过程活动)
    - [2.2.1 Software specification（软件规格说明）](#221-software-specification软件规格说明)
    - [2.2.2 Software design and implementation（软件设计和实现）](#222-software-design-and-implementation软件设计和实现)
    - [2.2.3 Software validation（软件确认）](#223-software-validation软件确认)
    - [2.2.4 Software evolution（软件演化）](#224-software-evolution软件演化)

# 1.Introduction
这一部分是一个概述，介绍了专业软件工程并定义了一些软件工程的概念，还简要讨论软件工程职业道德方面的问题。

## 1.1 What software engineering is and why it is important（什么是软件工程，为什么它很重要）
### 1.1 We can’t run the modern world without software（我们的世界离不开软件）
软件工程对于政府、社会、国内和国际企业、机构的正常运转都是至关重要的。现在的世界离开软件就无法运转了。
国家基础设施和公共服务都是基于计算机的系统控制的，大多数电子产品都包括计算机和控制软件，工业制造和分销已经完全计算机化了，金融系统也是这样。娱乐业，包括音乐产业、计算机游戏产业、电影和电视产业，也是一个软件密集型的产业。
National infrastructures and utilities are controlled by computer-based systems and most electrical products include a computer and controlling software.
Industrial manufacturing and distribution is completely computerized, as is the financial system. 
Entertainment, including the music industry, computer games, and film and television, is software intensive.

软件是抽象的、不可触摸的，它不受物质材料的限制，也不受物理定律或加工的制约：
优点：一方面使软件工程得以简化，因为软件的潜能不受物理因素的限制；
缺点：另一方面，由于缺乏自然约束，软件系统也很容易变得极为复杂理解它会很困难，改变它价格高昂。
Software systems are abstract and intangible. They are not constrained by the properties of materials, governed by physical laws, or by manufacturing processes.
This simplifies software engineering, as there are no natural limits to the potential of software.
However, because of the lack of physical constraints, software systems can quickly become extremely complex, difficult to understand, and expensive to change.

### 1.1.1 What is Software Engineering？（什么是软件工程）
专业开发与个人化开发的关键区别在于，专业开软件除了开发者之外还有其他用户会使用，而且专业化软件通常都是由团队而非个人开发的。专业化软件在其生命周期内要不断维护和修改。
软件工程的目的是支持专业化的软件开发，而非个人变成。它包括支持程序规格说明、设计和演化的相关技术，而这些通常都与个人化的软件开发无关。

软件工程是一门工程学科，设计软件生产的各个方面，从出的系统规格说明直到投入使用后的系统维护，都属于软件工程。
Software engineering is an engineering discipline that is 
concerned with all aspects of software production
软件工程师都会在其工作中运用系统化、有组织的方法，因为这通常是开发高质量软件最有效的方法。
As a software engineer, you apply software development process when developing a software system.

软件失效很多都源于以下两方面的因素：
1.不断增长的系统复杂性。
2.未有效采用软件工程方法。
1.Increasing demands
2.Low expectations (you don’t expect the software to grow into a giant beast)

一个专业软件经常有以下特征：
1.严格的用户需求
2.准确性和数据完整性
3.更高的安全标准
4.对于高负载的稳定性
5.需要技术支持等
1.Strict user requirements
2.Required accuracy and data integrity
3.Higher security standard
4.Stable performance for heavy load
5.Required technical support, etc.


一个好的软件的基本属性：
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/e369dcdc6b5a43aabdf910638cd0d124.jpeg#pic_center)
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/e3271b43983d487c86bc81967c72c0b6.png#pic_center)
两种软件产品：
1.通用软件产品，有软件开发组织开发，在市场上公开销售，可以独立使用。这类软件产品包括移动应用、数据库软件、字处理软件、绘图软件以及项目管理工具等。还包括用于特定目的的的所谓的“垂直”应用产品，如图书馆信息系统、财务系统等。
2.定制化软件产品，受特定的客户委托，由软件承包商专门为这类客户设计和实现。这类软件包括电子设备的的控制系统、空中交通管制系统等。
1.Generic software products：These are systems that are produced by a development organization and sold on the open market to any customer who is able to buy them.
2.Customized software products：These are systems that are commissioned by a particular customer. A software contractor develops the software especially for that customer.
然而，这两类产品之间的界限正在变得越来越模糊。

软件不会像硬件一样因为长时间使用而磨损（wear out）。
从理论上讲，软件的故障率曲线应该呈现出图表中所示的“理想化曲线”的形式。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/dc4b1b4cba20410cbc04ba5bed385ec6.png#pic_center)

软件虽然不会磨损但是它可能会出现退化
Software doesn’t wear out. But it does deteriorate.

在软件生命周期中，当对软件进行修改和更新时，可能会引入新的错误，导致软件的故障率暂时上升，形成尖峰。在这种情况下，软件的性能和稳定性可能会暂时受到影响。
在错误被修复之前，如果又有新的修改请求，可能会导致故障率曲线再次出现尖峰。这种情况下，软件的故障率曲线可能会出现多次波动，直到软件恢复到原始的稳定状态。
During its life, software will undergo change. As changes are made, it is likely that errors will be introduced, causing the failure rate curve to spike as shown in the “actual curve”.
Before the curve can return to the original steady-state failure rate, another change is requested, causing the curve to spike again.
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/0fc43bdc56404f009504c66427149741.png#pic_center)
因此为了减少故障率，我们有两种方案：
1.减少软件变更
通过与利益相关者密切合作，确保需求被正确定义，以减少软件变更的需求。
Work closely with the stakeholder to ensure requirements are correctly defined.
改进需求研究方法，以获得更好的需求研究结果。
Improve requirement study approach to achieve better requirements study.

2.减少变更后的副作用
需要确保软件具有模块化的设计，这样对一个模块的变更不会对其他模块产生太多的副作用。
The software should be modular so that changes will not have a lot of side effects to other part of the software.
软件必须具有可维护性
The software must be maintainable.
需要进行全面的测试，以减少错误。
Comprehensive testing should put in place to  reduce errors.

软件工程之所以重要的两方面原因：
1.个人和社会正越来越多地依赖于先进的软件系统。这就要求我们能够以经济而且快速的方式开发出可靠、可信的系统。
2.从长远来看，运用软件工程方法和技术开发专业化的软件系统，比单纯作为个人变成羡慕编写程序更加便宜。无法有效应用软件工程方法将会导致更高的测试、质量保障和长期维护的成本。
1.More and more, individuals and society rely on advanced  software systems. We need to be able to produce reliable and trustworthy systems economically and quickly.
2.It is usually cheaper, in the long run, to use software engineering methods and techniques for software systems rather than just write the programs as if it was a personal programming project. For most types of systems, the majority of costs are the costs of changing the software after it has gone into use.

软件工程中所使用的系统化方法有时被称为“软件过程”。软件过程是指实现软件产品开发的活动序列。所有的软件过程都包含以下4项基本活动：
1.软件规格说明，其中客户和工程师定义所要开发的软件以及对其运行的约束；
2.软件开发，对软件进行设计和编程实现；
3.软件确定，对软件进行检查以确保它是客户所需要的；
4.软件演化，对软件进行修改以反映客户和市场需求的变化。
1.Software specification
2.Software development
3.Software validation
4.Software evolution

后一节将会解释不同类型的系统需要不同的软件开发过程。例如，飞机上所使用的实时软件必须在开发之前确定完整的规格说明。而在电子商务系统中，规格说明和程序通常时一起开发的。因此，根据所开发的软件类型的不同，这些通用的开发活动可以以不同的方式进行组织，并且以不同的详细程度进行描述。

软件工程与计算机科学和系统工程相关
1.计算机科学关注支撑计算机和软件系统的基础理论和方法。
2.系统工程关注复杂系统的开发和演化的各个方面。

## 1.2 The development of different types of software systems may require different software engineering techniques（开发不同类型的软件系统可能需要不同的软件工程技术）
软件工程是生产软件的系统化的方法，它考虑了现实的成本、进度、可靠性问题，以及软件客户和开发者的需要。所使用的特定的方法、工具和技术取决于开发软件的组织、软件的类型以及开发过程中所设计的人。没有一个通用的软件工程方法和技术适用于所有的系统和公司。
因此，软件工程并不是一种固定的、铁板一块的方法，而是根据具体情况进行灵活调整和实施的。不同的组织、软件类型和开发团队可能会采用不同的方法和实践，以满足特定的成本、进度、质量和需求。
Software engineering is a systematic approach to the production of software that takes into account practical cost, schedule, and dependability issues, as well as the needs of software customers and producers. 
How this systematic approach is actually implemented varies 
dramatically depending on: 
1.The organization developing the software.
2.The type of software.
3.The people involved in the development process.

在考虑哪种软件工程方法和技术最重要时，也许最重要的因素时所开发的应用的类型。存在许多不同类型的应用：
1.独立的应用
2.基于事务的交互式应用
3.嵌入式控制系统
4.批处理系统 
5.娱乐软件 
6.建模和仿真系统 
7.数据处理和分析系统 
1.Stand-alone applications
2.Interactive transaction-based applications
3.Embedded contrl systems
4.Batch processing systems
5.Entertainment systems
6.Systems for modeling and simulation
7.Data collection systems

虽然不同类型的软件开发不同，但是下面的一些基本原则适用于所有类型的软件系统，无论采用何种开发技术：
1.软件系统开发过程应当是受管理的并且被开发人员所理解。软件开发组织应当对开发过程进行计划，并对要开发什么以及什么时候完成很清楚。当然，应当使用什么样的特定过程则取决于你所开发的软件类型。
2.可靠性和性能对所有类型的系统来说都很重要。软件应该按照所期待的方式运行，不会发生失效，并且在用户需要的时候是可用的。它在运行过程中应该确保安全，并且针对外部攻击尽可能保证信息安全。系统应当高效地运行并且不会浪费资源。
3.理解和管理系统规格说明和需求（软件应该做什么）是很重要的。你必须知道不同地客户和用户对于系统地期望是什么，然后你必须管理他们的期望以便能够在预算范围内按时交付一个有用的系统。
4.你应该尽可能高效地使用已有的资源。这就意味着，你应该在一些适当的地方复用已开发的软件，而不是重新写一个新软件。
1.Systems should be developed using a managed and understood 
development process. 
2.Dependability and performance are important for all types of system. 
3.Understanding and managing the software specification and 
requirements (what the software should do) are important. 
4.Where appropriate, you should reuse software that has already been 
developed rather than write new software.

## 1.3 Web-BASED software engineering（互联网软件工程）
最初，Web只是一种可以被广泛访问的信息源，对软件系统几乎没有影响。那时的软件系统在本地计算机上运行，且只是由同一组织内部的人访问。
后来浏览器添加了越来越多的功能。这就意味着基于Web的系统的开发允许用户通过浏览器而非特别开发的用户界面来访问这些系统。这就导致了大量通过Web访问、提供创新性服务的新系统产品的开发。这些系统通常依赖于广告赞助，广告显示在用户屏幕上，不需要用户直接付费。
除了这些系统产品，Web浏览器的发展使得浏览器可以运行小程序并且进行一些本地处理。这导致了业务和组织软件的变化。不同于将写好的软件部署在用户的个人计算机上运行，这些软件部署在Web服务器上。这就使得修改和升级软件变得更加便宜，因为不需要在每台个人计算机上安装软件。这也降低了成本，因为用户界面开发非常昂贵。因此，只要有可能，公司就会选择将软件系统移动到基于Web的交互模式上。
越来越多的软件运行在远端的“云”上而非本地的服务器上，并通过互联网访问。计算云是由大量相互连接并由许多用户共享的计算机系统组成的。用户并不购买软件而是按照软件的使用量进行付费，或者让用户免费访问并通过让用户观看在屏幕上展示的广告来获得回报。

软件组织中的这一变化已经对基于Web的系统的软件工程造成了巨大的影响。例如：
1.软件复用已经成为构建基于Web的系统的主流方法。当你构成这样的系统时需要考虑如何在已存在的软件构件和系统基础上装备系统，这些构件和系统经常捆绑在一个框架中。
2.人们普遍承认提前确定这些系统的所有需求是不切实际的。基于Web的系统总是增量开发和交付的。
3.软件可以是由面向服务的软件工程来实现，其中软件构件是独立的Web服务。
4.AJAX和HTML5等界面开发技术已经出现，这些技术支持Web浏览器中的复客户端界面的创建。

与其他的软件一样，前面讨论的软件工程的基本思想同样适用于基于Web的软件。基于Web的系统正变得越来越大，因此应对规模和复杂性的软件工程技术与这些系统相关。
## 1.4 Some ethical and professional issues that are important for software engineers（对于软件工程师很重要的道德和职业问题）
软件工程师必须坚持诚实正直的行为准则，这是不言而喻的。他们不能用所掌握的知识和技能做不诚实的事情，更不能给软件工程行业抹黑。然而，在有些方面，某些行为没有法律加以规范，只能靠职业道德来约束，这种约束是软弱无力的。其中包括：
1.保密
2.工作能力
3.知识产权
4.计算机滥用

1.Confidentiality
2.Competence
3.Intellectual property rights
4.Computer misuse


# 2. Software Process （软件过程）
软件过程是完成软件产品生产的一组相互关联的活动。因为有许多不同类型的软件系统，所以没有适用于所有类型的软件工程方法，因此没有适用于所有类型的软件过程。虽然有许多不同的软件过程，但它们都都包含前面说的4哥最基本的软件工程活动：
1.软件规格说明。软件的功能以及对于软件允许的约束必须在这里进行定义。
2.软件开发。必须开发出符合规则说明的软件。
3.软件确认。软件必须通过确认来确保软件所作的是客户是想要的。
4.软件演化。软件必须通过演化来满足不断变化的客户需求。
There are many different software processes, but all must include four activities that are fundamental to software engineering:
1.Software specification
2.Software development
3.Software validation
4.Software evolution


软件过程是复杂的，没有一个理想的过程适用于所有情况。
大多数组织都会根据组织内部人员的能力和正在开发的系统的特定特征，制定适合自身的软件过程。
对于关键系统，需要一个非常结构化的开发过程。
对于非关键系统，且需求快速变化的情况下，一个不太正式、灵活的过程可能更有效。
有很多软件过程的种类，主要包括以下几类：
线性和顺序模型：如瀑布模型和V模型，按照严格的顺序和阶段进行开发。
迭代和增量模型：包括增量式、迭代式和螺旋式等模型，通过反复迭代和增量开发来逐步完善软件。
敏捷模型：如Scrum、Kanban、极限编程（XP），强调快速响应变化和灵活性。
原型模型：包括一次性原型和演化性原型，通过原型开发来理解和验证需求。
组件化模型：如基于组件的开发（CBD），通过组件化的方式进行软件开发。
形式化方法：如形式化规约和模型检查，采用形式化的方式进行软件开发和验证。
混合模型：如敏捷-瀑布混合、DevOps，结合不同方法的混合模型。
快速应用开发（RAD）模型：如RAD模型、DSDM，强调快速开发和迭代。
精益模型：如精益软件开发，强调精简和高效的软件开发过程。
 Linear and Sequential Models: Waterfall, V-Model
Iterative and Incremental Models: Incremental, Iterative, Spiral
Agile Models: Scrum, Kanban, Extreme Programming (XP)
Prototyping Models: Throwaway Prototyping, Evolutionary Prototyping
Component-Based Models: Component-Based Development (CBD)
Formal Methods: Formal Specification, Model Checking
Hybrid Models: Agile-Waterfall Hybrid, DevOps
Rapid Application Development (RAD) Models: RAD Model, DSDM
Lean Models: Lean Software Development

## 2.1 Software Process Models（软件过程模型）
软件过程模型是对软件过程的简化表达。它讨论了非常一般的过程模型，并从架构的角度呈现这些模型，而不是特定活动的细节。这些通用模型并不是对软件过程的最终描述，而是对过程的抽象，可用于解释软件开发的不同方法。可以把它们看作是过程框架，可以扩展和适应以创建更具体的软件工程过程。软件过程是实际执行任务和活动的过程，而软件过程模型提供了指导这一执行的结构化框架。该模型确保遵循最佳实践，管理风险，维持质量，从而导致更可预测、高效和成功的软件开发项目。换句话说，软件过程模型的作用是确保软件开发过程中遵循最佳实践，有效管理风险，保证质量，从而提高软件开发项目的可预测性、效率和成功率。
A software process model is a simplified representation of a software process.
Discuss very general process models and present these from an architectural perspective, framework of the process rather than the details of specific activities.
These generic models are not definitive descriptions of software processes, they are abstractions of the process that can be used to explain different approaches to software development.
You can think of them as process frameworks that may be extended and adapted to create more specific software engineering processes.
While the software process is the actual execution of tasks .
and activities, the software process model provides the 
structured framework that guides this execution. 
The model ensures that best practices are followed, risks are managed, and quality is maintained, leading to more predictable, efficient, and successful software development projects.

我们将在本章讨论三个通用模型：
1.瀑布模型。该模型包含了基本的过程活动（即规格说明、开发、确认、演化），并将它们表示为独立的过程阶段，例如需求规格说明、软件设计、实现、测试。
2.增量式开发。该方法使得规格说明、开发和确认活动交错进行。系统开发体现为一系列的版本（增量），每个版本在前一版本的基础上增加一些功能。
3.集成和配置。改方法依赖于可复用的构件或系统。系统开发过程关注在新的使用环境中配置这些构件并将它们集成为一个系统。
The waterfall model - This takes the fundamental process activities of specification, development, validation, and evolution and represents them as separate process phases such as requirements specification, software design, implementation, testing, and so on.
Incremental development - This approach interleaves the activities of specification, development, and validation. The system is developed as a series of versions (increments), with each version adding functionality to the previous version.
Reuse-oriented software engineering - This approach is based on the existence of a significant number of reusable components. The system development process focuses on integrating these components into a system rather than developing them from scratch.

这些软件过程模型并不是相互排斥的，通常会一起使用，特别是在大型系统开发项目中。例如系统的核心需求，设计系统的软件体系结构以支持这些需求。这是不能增量式开发的。这些大系统中的子系统可以使用不同的开发方法。系统中的一些部分已经得到了很好的理解，可以使用基于瀑布模型的过程进行规格说明和开发，或者可以作为成品系统买入并进行配置。而那些难以提前清楚刻画的部分则要采用增量的开发方式。

### 2.1.1 The Waterfall Model（瀑布模型）
瀑布模型是一种线性和顺序的软件开发方法。它按照明确定义的阶段进行，每个阶段都有特定的交付成果和审查流程。
The Waterfall Model is a linear and sequential approach to software development. It progresses through distinct phases, each with specific deliverables and review processes.
下图展示了瀑布模型中的阶段。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/4c21439ebc804910af1f134c7c651610.png)
瀑布模型中的阶段直接反映一下这些基本的软件开发活动。
1.需求分析和定义。通过咨询系统用户建立系统的服务、约束和目标，详细定义这些信息并作为系统的规格说明。
2.系统和软件设计。系统设计过程将需求分配到硬件或软件系统上，建立一个总体的系统体系结构。软件设计设计识别并描述基本软件系统抽象以及它们之间的关系。
3.实现和单元测试。在此阶段，将软件设计时限为一组程序或程序单元。单元测试验证每个单元是否满足其规格说明。
4.集成和系统测试。各个程序单元或程序被集成为一个完整的系统，并进行测试以保证软件需求都得到了满足。测试之后，软件系统被交付给客户。
5.运行和维护。通常这是时间最长的一个生命周期阶段。系统被安装并投入实践使用。维护包括修复没有在生命周期早期阶段发现的错误、改进系统单元的实现、随着新需求的发现而对系统的服务进行提升。
1.Requirements analysis and definition 
Objective: Gather and document all functional and nonfunctional requirements.
Deliverables: Requirements Specification Document.
Activities: Stakeholder interviews, surveys, and requirement workshops.
2. System and software design
Objective: Create a detailed design based on the requirements.
Deliverables: System Architecture Document, Design Specifications.
Activities: Architectural design, database design, user interface design.
3.Implementation and unit testing
Objective: Translate design documents into actual code.
Deliverables: Source code, code documentation.
Activities: Coding, unit testing, code reviews.
4.Integration and system testing
Objective: Integrate all modules and test the complete system.
Deliverables: Test plans, test cases, test reports.
Activities: Integration testing, system testing, user acceptance testing.
5.Operation and maintenance
Objective: Deploy the system to the production environment and provide ongoing support and enhancements.
Deliverables: Deployment plan, user manuals, maintenance reports, update patches.
Activities: Installation, configuration, user training, bug fixes, performance improvements, feature updates.

瀑布模型的特点如下：
1.线性和顺序性：每个阶段必须在下一个阶段开始之前完成。
2.文档驱动：在每个阶段都要产生大量的文档。
3.阶段特定的交付成果：每个阶段都有特定的交付成果和里程碑。
4.审查和批准：每个阶段在进行到下一个阶段之前需要进行审查和批准。
1.Linear and Sequential: Each phase must be completed before the 
next one begins.
2.Documentation-Driven: Extensive documentation is produced at 
each stage.
3.Phase-Specific Deliverables: Each phase has specific deliverables and 
milestones.
4.Review and Approval: Each phase requires review and approval 
before proceeding to the next.

原则上，每个阶段的结果是一个或多个经过批准的文档。下一个阶段不应该在前一个阶段完成之前开始。
实际上，这些阶段会有重叠，并且彼此之间会相互提供信息。
软件过程不是简单的线性模型，而是涉及从一个阶段到另一个阶段的反馈。每个阶段产生的文档可能需要修改以反映所做的更改。
由于制作和批准文档的成本高昂，迭代可能会很昂贵并涉及大量的重做工作。因此，在进行了少量迭代之后，通常会冻结开发的部分内容，比如规格说明，并继续后续的开发阶段。问题可能被留待以后解决，被忽视，或者被绕过。这种过早冻结开发任务可能意味着系统无法提供用户期望的功能。
在软件的最终生命周期阶段（运行和维护阶段），软件被投入使用后发现了原始软件需求中的错误和遗漏。程序和设计错误也会出现，并且新功能的需求会被确定。因此，系统必须不断演进以保持其有用性。进行这些变更（软件维护）可能需要重复之前的过程阶段。
瀑布模型中的文档在每个阶段都会产生，这使得整个过程对管理者来说是可见的，因此管理者可以监控进展情况并与开发计划进行比较。然而，瀑布模型的主要问题在于将项目划分为不同的阶段缺乏灵活性。在过程的早期阶段就必须做出承诺，这使得难以对变化的客户需求做出响应。从原则上讲，瀑布模型只应在需求被充分理解且在系统开发过程中不太可能发生根本性变化时使用。
在瀑布模型的软件开发过程中，如果在软件验证阶段意识到有遗漏的需求，通常情况下很难立刻进行修改。因此，如果发现了遗漏的需求，可能需要通过变更控制流程来记录并评估影响，并在后续的版本中进行修正。

优点如下：
1.简单易用：瀑布模型的结构清晰易懂，易于实施和管理。
2.可预测性和规划性：瀑布模型允许在项目开始阶段进行详细的规划，从而可以更准确地估计成本、时间和资源。
3.文档化：每个阶段都需要全面的文档记录，有助于未来的维护和知识传递，提供了项目发展的清晰记录。
4.纪律和控制：瀑布模型的线性和顺序性强化了软件开发的纪律性。
5.资源管理：明确的阶段有助于更好地规划和分配资源，团队可以根据每个阶段所需的特定技能进行组织。
6.里程碑和交付物：每个阶段都有清晰的里程碑和交付物，更容易跟踪进展和管理项目的时间表。
7.风险管理：变更以受控的方式进行管理，任何变更都经过深入审查和记录。
1.Simplicity and Ease of Use
Clear Structure: The Waterfall Model is straightforward and easy to understand, making it simple to implement and manage.
Well-Defined Phases: Each phase of the Waterfall Model has a defined start and end point, which helps in understanding the project’s progress and managing the workflow.
2.Predictability and Planning
Detailed Planning: The model allows for detailed planning at the beginning of the project, which can lead to more accurate estimates of costs, timelines, and resources.
Predictable Outcomes: With well-defined phases and deliverables, the outcomes are more predictable, which is beneficial for stakeholders and project managers.
3.Documentation
Comprehensive Documentation: Each phase requires thorough documentation, which can be useful for future maintenance and knowledge transfer. This documentation provides a clear record of the project’s development.
Traceability: The documentation provides clear traceability of decisions and changes, making it easier to track the project’s history and understand the rationale behind design choices.
4.Discipline and Control
Structured Approach: The linear and sequential nature of the Waterfall Model enforces a disciplined approach to 
software development
Phase Completion: The requirement to complete each phase before moving on ensures that all aspects of the project are 
thoroughly reviewed and approved.
5.Resource Management
Resource Allocation: The clear phases allow for better planning and allocation of resources.
Skill Utilization: Teams can be organized based on the specific skills required for each phase.
6.Milestones and Deliverables
Clear Milestones: Clear milestones and deliverables for each phase, making it easier to track progress and manage project timelines.
Client Approval: Each phase can be reviewed and approved by the client, providing opportunities for feedback and ensuring that the project stays aligned with client expectations.
7.Risk Management
Controlled Changes: Changes are managed in a controlled manner, and any changes are thoroughly reviewed and documented.

缺点如下：
1.不灵活性：瀑布模型的线性结构使得难以在一个阶段完成后容纳变更，同时每个阶段必须在进入下一个阶段之前完成，因此任何阶段的延迟或问题都可能影响整个项目的时间表。
2.迟到的测试：测试通常在开发过程的后期进行，这意味着缺陷和问题往往在后期才被发现，使得修复变得更加昂贵和困难。
3.风险管理：瀑布模型本身不包括风险管理活动，因此对于存在高度不确定性或风险的项目来说，不太适合。
4.客户参与度：客户通常直到开发周期结束才能看到产品，这可能导致最终产品并不完全满足他们的需求或期望。
5.适应性：瀑布模型不太适合需求预期会演变或迭代开发有益的项目，同时对于范围蔓延的变更难以管理和整合，可能导致潜在的延迟和成本增加。
6.开销和文档化：过多的文档化可能耗时，并且可能导致延迟，尤其是在快节奏的项目中。同时，管理文档和阶段转换可能增加行政开销，这对于较小的项目可能不合理。
7.资源利用：在某些阶段资源可能被闲置，例如，在需求和设计阶段开发人员可能被闲置，而在实施阶段分析师和设计师可能会少些工作。同时，该模型不容易允许并行工作流，这可能导致资源利用效率低下。
8.较长的项目时间表：瀑布模型的顺序性可能导致较长的项目时间表，因为必须在下一个阶段开始之前完成每个阶段。最终产品仅在项目结束时交付，这可能延迟了对利益相关者和用户价值的实现。
1.Inflexibility
Rigid Structure: The linear nature of the Waterfall Model makes it difficult to accommodate changes once a phase is completed. 
Sequential Progression: Each phase must be completed before moving on to the next, which means that any delays or issues in one phase can impact the entire project timeline.
2.Late Testing
Late Problem Detection: Testing is conducted late in the development process, typically after the implementation phase. This means that defects and issues are often discovered late, making them more expensive and difficult to fix.
Limited Iterative Feedback: Since testing occurs at the end, there are limited opportunities for iterative feedback and improvements during the development process.
3.Risk Management
High Risk: The Waterfall Model does not inherently include risk management activities, making it less suitable for projects with high uncertainty or risk.
4.Customer Involvement
Limited Feedback: Customers typically do not see the product until the end of the development cycle, which can lead to a final product that does not fully meet their needs or expectations.
Assumption of Perfect Requirements: The model assumes that all requirements can be clearly defined at the beginning, which is often not the case in real-world projects. This can result in a misalignment between the final product and user needs.
5. Adaptability
Poor Adaptability: The Waterfall Model is not well-suited for projects where requirements are expected to evolve or where 
iterative development is beneficial.
Scope Creep: Changes in scope can be difficult to manage and integrate, leading to potential delays and increased costs.
6.Overhead and Documentation
Heavy Documentation: The emphasis on documentation can be time-consuming and may lead to delays, especially in fast-paced projects. The extensive documentation required can also become outdated quickly if changes are made.
Administrative Overhead: Managing documentation and phase transitions can add administrative overhead, which may not be justified for smaller projects.
7.Resource Utilization
Idle Resources: Resources may be underutilized during certain phases. For example, developers may be idle during the requirements and design phases, while analysts and designers may have less to do during the implementation phase.
Sequential Resource Allocation: The model does not easily allow for parallel workstreams, which can lead to inefficiencies in resource utilization.
8. Longer Project Timelines
Extended Timelines: The sequential nature of the Waterfall Model can lead to longer project timelines, as each phase must be completed before the next one begins.
Delayed Delivery: The final product is delivered only at the end of the project, which can delay the realization of value for stakeholders and users.

因此瀑布模型只适用于以下这些类型的系统：
1.嵌入式系统，其中软件必须与硬件系统连接和交互。由于硬件不灵活，将软件功能的决策推迟到开发时通常不可行。
2.关键性系统，要求对软件规格说明和设计的安全性和信息安全进行全面的分析。在这些系统中，规格说明和设计文档必须完整，使得这些分析成为可能。在实现阶段修复规格说明和设计中与安全相关的问题通常非常昂贵。
3.大型软件系统，属于更广阔的有多家合作企业共同开发的工程化系统的一部分。系统中的硬件可能使用相似的模型开发，相关企业发现使用同样的模型进行硬件和软件开发更容易一些。而且，由于涉及多家企业，可能需要完整的规格说明以使不同的子系统可以独立开发。

### 2.1.2 Incremental Model（增量式开发）
增量式开发是一种迭代的软件开发方法，其中系统是逐步构建的。每个增量都向系统添加功能部分，直到完整的产品被交付。
The Incremental Model is an iterative approach to software development where the system is built incrementally. Each increment adds functional pieces to the system until the complete product is delivered.
下图展示了增量式开发。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/05726af430a8490d97b102b6f547723f.png)
1.概述描述和规划：定义整体项目范围和高层需求，包括项目计划和高层需求文档。活动包括利益相关者访谈、需求研讨会和项目规划。
2.规格和规划：为每个增量计划详细的细节，包括具体的需求、设计和任务，交付成果包括增量计划和详细的增量需求。
3.设计和开发：为特定的增量设计和开发功能，交付成果包括设计文档、源代码和单元测试，活动包括架构设计、编码、单元测试和代码审查。
4.集成和验证：将新的增量与现有系统集成并进行测试，活动包括集成测试、系统测试和用户验收测试。
5.部署/增量：将增量部署到生产环境，交付成果包括部署的增量和用户手册，活动包括安装、配置和用户培训。
6.回顾和反馈：收集用户和利益相关者对已部署增量的反馈，交付成果包括反馈报告和更新的需求，活动包括用户反馈会议和需求更新。
7.下一个增量规划：根据反馈和更新的需求规划下一个增量，交付成果包括更新的项目计划和下一个增量的详细需求，活动包括需求分析、任务分解和资源分配。
1.Outline Description and Planning
Objective: Define the overall project scope and high-level requirements.
Deliverables: Project plan, high-level requirements document.
Activities: Stakeholder interviews, requirement workshops, project planning.
2.Specification and Planning
Objective: Plan the details for each increment, including specific requirements, design, and tasks.
Deliverables: Increment plan, detailed requirements for the increment.
Activities: Requirement analysis, task breakdown, resource allocation.
3.Design and Developmen
Objective: Design and develop the functionality for the specific increment.
Deliverables: Design documents, source code, unit tests.
Activities: Architectural design, coding, unit testing, code reviews.
4.Integration and Validation
Objective: Integrate the new increment with the existing system and perform testing.
Deliverables: Integrated system, test cases, test reports.
Activities: Integration testing, system testing, user acceptance testing.
5.Deployment/Increment
Objective: Deploy the increment to the production environment.
Deliverables: Deployed increment, user manuals.
Activities: Installation, configuration, user training.
6.Review and Feedback
Objective: Gather feedback from users and stakeholders for the deployed increment.
Deliverables: Feedback reports, updated requirements.
Activities: User feedback sessions, requirement updates.
7.Next Increment Planning
Objective: Plan the next increment based on feedback and updated requirements.
Deliverables: Updated project plan, detailed requirements for the next increment.
Activities: Requirement analysis, task breakdown, resource allocation.

增量式开发的特点如下：
1.迭代开发：项目被划分为小的、可管理的增量，每个增量都可以独立开发和交付。
2.早期交付：系统的功能部分可以早期和频繁地交付，而不是等到整个系统都开发完毕才交付。
3.用户反馈：定期从用户那里获得反馈，并将其纳入每个增量的开发过程中。
4.灵活性：更容易适应需求变更和反馈，因为每个增量都可以进行调整和改进。
5.风险管理：通过迭代开发，可以早期识别和缓解风险，从而提高项目的成功几率。
1.Iterative Development: The project is divided into smaller, manageable increments.
2.Early Delivery: Functional pieces of the system are delivered early and frequently.
3.User Feedback: Regular feedback from users is incorporated into each increment.
4.Flexibility: Easier to accommodate changes in requirements and feedback.
5.Risk Management: Early identification and mitigation of risks through iterative development.

增量开发基于这样一个理念：首先开发一个初始的实现版本，让用户进行评价，然后通过多个版本的演进来开发出一个合适的系统。
规格、开发和验证活动是交替进行的，而不是分开进行，并且在各个活动之间有快速的反馈。
增量软件开发是敏捷方法的基本组成部分，对于大多数商业、电子商务和个人系统来说，它比瀑布模型更好。大部分业务系统和软件产品都是这样的。
通过逐步开发软件，使得在开发过程中进行软件更改更加便宜和容易。
系统的每个增量或版本都包含客户需要的一些功能。通常，系统的早期增量包括最重要或最紧急需要的功能。这意味着客户可以在开发的相对早期阶段评估系统，以查看它是否提供了所需的功能。如果没有满足需求，那么只需更改当前的增量，并可能为以后的增量定义新功能。

它的优点如下：
1早期交付和反馈：
早期功能交付：增量模型允许在开发过程的早期交付系统的功能部分。
用户反馈：早期的增量可以由用户审查，提供宝贵的反馈，用于完善后续的增量。
2.灵活性和适应性：
适应变更：该模型灵活，比线性模型更容易适应需求变更。
迭代开发：增量模型的迭代性质允许对系统进行持续改进和完善。
3.风险管理：
降低风险：通过将项目分解为较小的增量，降低了风险。问题可以在开发过程的早期被识别并解决，最大程度地减小对整个项目的影响。
早期问题检测：在每个增量结束时进行测试，可以早期发现和解决缺陷和问题。
4.资源利用的改进：
并行开发：不同的增量可以并行开发，优化资源利用并缩短开发时间。
集中努力：团队可以专注于开发和完善每个增量中的特定功能或功能，从而提高产出质量。
5.更好的规划和估算：
较短的规划周期：规划较小的增量更易于管理，可以更频繁地进行，提高了估算和进度表的准确性。
里程碑和交付成果：每个增量提供清晰的里程碑和交付成果，更容易跟踪进度和管理项目。
6.客户和利益相关者的满意度：
定期交付：定期交付功能增量使客户和利益相关者保持参与并感到满意。他们可以看到实质性的进展，并在整个开发过程中提供反馈。
与期望的一致性：持续的用户反馈确保最终产品更加符合客户的期望和需求。
7.增强的质量：
持续测试：每个增量都经历测试，确保缺陷早期被发现和解决，从而提高最终产品的质量。
增量集成：集成和测试较小的增量降低了集成的复杂性，并有助于保持系统的稳定性。
8.可扩展性：
可扩展的方法：增量模型是可扩展的，适用于各种规模和复杂度的项目。特别适用于大型项目，一次交付整个系统是不切实际的情况。
1.Early Delivery and Feedback
Early Functional Delivery: The Incremental Model allows for the delivery of functional parts of the system early in the development process. 
User Feedback: Early increments can be reviewed by users, providing valuable feedback that can be used to refine subsequent increments. 
2.Flexibility and Adaptability
Accommodates Changes: The model is flexible and can accommodate changes in requirements more easily than linear models. 
Iterative Development: The iterative nature of the Incremental Model allows for continuous improvement and refinement of the system.
3.Risk Management
Reduced Risk: By breaking the project into smaller increments, risks are reduced. Issues can be identified and addressed early in the development process, minimizing the impact on the overall project.
Early Problem Detection: Testing is performed at the end of each increment, allowing for early detection and resolution of defects and issues.
4.Improved Resource Utilization
Parallel Development: Different increments can be developed in parallel, optimizing the use of resources and reducing 
development time.
Focused Efforts: Teams can focus on developing and refining specific features or functionalities in each increment, 
leading to higher quality outputs.
Strengths and Benefits
5.Better Planning and Estimation
Shorter Planning Cycles: Planning for smaller increments is more manageable and can be done more frequently, improving the accuracy of estimates and schedules.
Milestones and Deliverables: Each increment provides clear milestones and deliverables, making it easier to track progress and manage the project.
6.Customer and Stakeholder Satisfaction
Regular Deliveries: Regular deliveries of functional increments keep customers and stakeholders engaged and satisfied. They can see tangible progress and provide feedback throughout the development process.
Alignment with Expectations: Continuous user feedback ensures that the final product is more closely aligned with customer expectations and requirements.
7.Enhanced Quality
Continuous Testing: Each increment undergoes testing, ensuring that defects are identified and addressed early. This leads to a higher quality final product.
Incremental Integration: Integrating and testing smaller increments reduces the complexity of integration and helps maintain system stability.
8.Scalability
Scalable Approach: The Incremental Model is scalable and can be applied to projects of varying sizes and complexities. It is particularly effective for large-scale projects where delivering the entire system at once is impractical.

缺点如下：
1.集成复杂性：
集成挑战：随着多个增量随时间的推移而开发和集成，集成这些增量的复杂性可能会增加。确保所有增量能够无缝地协同工作可能具有挑战性。
依赖管理：管理增量之间的依赖关系可能很困难。一个增量的变更可能会影响其他增量，需要进行仔细的协调和沟通。
2.早期系统的不完整性：
部分功能：早期的增量可能只提供部分功能，这可能无法立即为所有利益相关者提供价值。
客户不满意：如果早期的增量不能满足用户期望或提供有限的功能，可能会导致不满和沮丧。
3.资源分配：
资源约束：有效地分配资源到多个增量可能具有挑战性。团队可能需要在开发新的增量的同时，维护和完善之前的增量之间取得平衡。
技能要求：不同的增量可能需要不同的技能，这使得需要一个多才多艺的团队或者有效地分配专业资源。
4.规划和协调：
需要详细的规划：虽然增量模型允许灵活性，但仍需要详细的规划和协调，以确保每个增量与整体项目目标一致。
复杂的调度：协调多个增量的开发、测试和集成可能会带来复杂的调度挑战。
5.范围蔓延的风险：
无控制的变更：在每个增量中纳入变更的灵活性可能会导致范围蔓延，如果变更没有得到仔细的管理和控制。
项目超支：如果变更频繁且重大，项目可能会出现成本和进度超支的情况。
6.增量交付：
相互依赖的增量：高度相互依赖的增量可能需要更多的工作，以确保一个增量的变更不会对其他增量产生不利影响。
延迟的完整功能：用户可能直到最终增量交付之前才能体验系统的全部功能，这可能会延迟实现完整的项目收益。
7.管理复杂性：
项目管理：管理增量项目可能比管理线性项目更加复杂。它需要仔细的规划、协调和监控，以确保所有增量与整体项目目标一致。
利益相关者管理：在开发多个增量的过程中保持利益相关者的参与和信息传达可能具有挑战性，特别是如果他们在早期增量中的期望没有得到满足。
1.Complexity in Integration
Integration Challenges: As multiple increments are developed and integrated over time, the complexity of integrating these increments can increase. Ensuring that all increments work seamlessly together can be challenging.
Dependency Management: Managing dependencies between increments can be difficult. Changes in one increment may impact others, requiring careful coordination and communication.
2.Incomplete Systems Early On
Partial Functionality: Early increments may deliver partial functionality, which may not provide immediate value to all stakeholders. 
Customer Dissatisfaction: If early increments do not meet user expectations or provide limited functionality, it can lead to dissatisfaction and frustration.
3.Resource Allocation
Resource Constraints: Allocating resources effectively across multiple increments can be challenging. Teams may need to balance working on new increments while maintaining and refining previous ones.
Skill Requirements: Different increments may require different skill sets, making it necessary to have a versatile team or to allocate specialized resources efficiently.
4.Planning and Coordination
Detailed Planning Required: While the Incremental Model allows for flexibility, it still requires detailed planning and coordination to ensure that each increment aligns with the overall project goals and objectives.
Complex Scheduling: Coordinating the development, testing, and integration of multiple increments can create complex scheduling challenges.
5.Risk of Scope Creep
Uncontrolled Changes: The flexibility to incorporate changes in each increment can lead to scope creep if changes are not carefully managed and controlled.
Project Overruns: If changes are frequent and significant, the project may experience cost and schedule overruns.
6.Incremental Delivery
Interdependent Increments: Increments that are highly interdependent may require more effort to ensure that changes in one increment do not adversely affect others.
Delayed Full Functionality: Users may not experience the full functionality of the system until the final increments are delivered, which can delay the realization of complete project benefits.
7.Management Complexity
Project Management: Managing an incremental project can be more complex than managing a linear project. It requires careful planning, coordination, and monitoring to ensure that all increments align with the overall 
project goals.
Stakeholder Management: Keeping stakeholders engaged and informed throughout the development of multiple increments can be challenging, especially if their expectations are not met in early increments.

下面展示一个使用增量式开发的例子——电子商务平台的开发。
初始规划：定义了高层需求和项目范围。
增量规划：计划第一个增量，包括基本的产品列表和用户注册功能。
设计和开发：设计和开发了第一个增量，并进行了单元测试。
集成和测试：将第一个增量与现有系统集成，并进行系统测试。
部署：将第一个增量部署到生产环境。
回顾和反馈：从用户和利益相关者那里收集反馈，并更新需求。
下一个增量规划：计划下一个增量，包括购物车和结账功能。
迭代过程：为后续的增量重复这个周期，添加支付处理、订单跟踪和用户评论等功能。

瀑布模型与增量式开发的比较：
1.需求稳定性：
增量模型：适用于具有不断发展和灵活需求的项目。允许根据反馈进行迭代改进。
瀑布模型：最适用于具有稳定和明确定义的需求，不太可能发生变化的项目。
2.项目规模和复杂性：
增量模型：适用于可以分解为较小、可管理的增量的大型复杂系统。
瀑布模型：更适用于较小、不太复杂的项目，或者那些复杂性已经被充分理解的项目。
3.早期交付功能：
增量模型：能够提供系统功能的早期交付，更早地为利益相关者提供价值。
瀑布模型：只有在开发周期结束时才能交付完整的功能。
4.风险管理：
增量模型：高风险项目通过迭代开发可以从早期识别和缓解风险中受益。
瀑布模型：较低风险的项目或那些风险已经被充分理解的项目更适合采用瀑布模型。
5.利益相关者参与：
增量模型：需要在整个开发过程中积极、持续地参与利益相关者，并持续获得他们的反馈。
瀑布模型：通常只在项目开始和结束阶段才能看到有限的利益相关者参与。
6.文档编制和审核：
增量模型：每个增量都进行持续的文档编制和合规性检查，以确保与需求的持续一致性。
瀑布模型：大量文档在每个阶段的前期和末期进行编制，这些文档可能不太适应变更。
7.灵活性和适应性：
增量模型：具有很高的灵活性，能够适应需求变更和反馈，适用于动态环境。
瀑布模型：灵活性较低；一旦一个阶段完成，很难纳入变更，因此适应性较差。
8.资源可用性：
增量模型：适用于资源有限的项目，可以根据项目需求逐步分配资源。
瀑布模型：更适用于整个生命周期内资源可用性持续稳定的项目。
9.维护和增强：
增量模型：适用于需要持续维护和增强的项目，因为每个增量都可以解决新需求。
瀑布模型：更适用于部署后需要最小维护的项目。
10.上市时间：
增量模型：适用于需要快速上市核心功能的项目，可以实现早期用户采用。
瀑布模型：更适用于上市时间不那么关键的项目。
11.法规和合规要求：
增量模型：受监管行业的项目受益于持续的合规性验证和调整。
瀑布模型：适用于具有充分理解的、稳定且不太可能发生变化的法规要求的项目。
12.并行开发：
增量模型：支持不同增量或模块的并行开发，可以加快整体进展速度。
瀑布模型：强调顺序开发，最小化并行活动。
13.以用户为中心的开发：
增量模型：适用于用户反馈对于完善需求和功能至关重要的项目。
瀑布模型：最适用于从一开始就有明确定义的用户需求的项目。
14.集成要求：
增量模型：适用于需要频繁集成新功能和组件的项目。
瀑布模型：更适用于在最后阶段之前几乎不需要集成的项目。
15.市场驱动开发：
增量模型：需要定期更新功能和改进的竞争市场受益于增量开发。
瀑布模型：更适用于市场稳定且不太频繁需要更新的情况。

### 2.1.3 Reuse-oriented software engineering（集成与配置）
在大多数软件项目中，都存在某种形式的非正式软件重用。这种非正式的重用不受所使用的开发过程的影响。
在21世纪，专注于重用现有软件的软件开发过程变得广泛使用。
重用导向的方法依赖于大量可重用的软件组件库和用于组合这些组件的集成框架。
In the majority of software projects, there are some forms of informal software reuse.
This informal reuse takes place irrespective of the development process that is used. 
In the 21st century, software development processes that focus on the reuse of existing software have become widely used. 
Reuse-oriented approaches rely on a large base of reusable software components and an integrating framework for the composition of these components.

下图展示了面向复用的软件工程。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/836a31adddd84bd79bad0bfcba3e6db6.png)
该过程包括以下这些阶段。
1.需求规格说明。系统的初始需求被提出。这些需求不需要进行细化，但是应当包含对于基本的需求以及想要的系统特性的简要描述。
2.软件发现和评估。给定软件需求的概要后，搜索提供所需要的功能的构件和系统。然后对候选的构件和系统进行评估，确定它们是否满足相应的基本需求以及是否适合用于当前系统。
3.需求精华。此阶段利用所发现的可复用构建和应用的信息对需求进行精化。对需求进行修改以反映可用的构件，而系统规格说明会被重新定义。如果无法进行修改，那么可能会重新进入构件分析活动来查找替代的解决方案。
4.应用系统配置。如果一个满足需求的成品应用系统是可用的，那么可以对该系统进行配置后使用以创建新系统。
5.构件适配和集成。如果没有成品系统，那么可以对各个可复用构件进行修改并开发新构件。接着，这些构件被集成到一起来创建系统。

以下三种类型的软件组件可以在这种模型中使用：
Web服务：按照服务标准开发的，可供远程调用的Web服务。
对象集合：作为一个包开发的对象集合，用于与诸如.NET或J2EE之类的组件框架集成。
独立软件系统：为在特定环境中使用而配置的独立软件系统。

它的优点如下：
1.减少需要开发的软件量，从而降低成本和风险。
2.通常也会导致软件交付速度更快。
1.Reducing the amount of software to be developed and so reducing 
cost and risks.
2.Usually also leads to faster delivery of the software. 

缺点如下：
1.必然会出现对需求的妥协，可能导致系统无法真正满足用户的实际需求。
2.此外，由于可重用组件的新版本不受使用组织控制，因此会失去对系统演进的一定控制。
1.However, requirements compromises are inevitable, and this may lead to a system that does not meet the real needs of users.
2.Furthermore, some control over the system evolution is lost as new versions of the reusable components are not under the control of the organization using them.

这三种模型分别可以对应于我的CPT205作业，我的CPT111作业，游戏引擎。

下面将给出一些场景，该选择什么模型以及原因也将一并给出。
航空航天和国防系统 
例子：飞机上的航空电子系统软件。
模型：瀑布模型。
原因：这些项目需要大量的前期规划、严格的法规合规性以及彻底的文档编制。瀑布模型的结构化方法确保在进入下一阶段之前满足所有需求。

医疗设备软件 
例子：MRI机器或患者监测系统的软件。 
模型：瀑布模型。
原因：医疗设备软件必须遵守严格的法规标准，并经过严格的测试和验证。瀑布模型的顺序阶段支持全面的文档编制和合规性检查。

电子商务平台 
例子：亚马逊、eBay。 
模型：增量式开发。
原因：电子商务平台需要不断发展以满足不断变化的市场需求和用户期望。增量式开发允许定期更新和发布新功能。

银行和金融系统 
例子：核心银行系统或金融交易处理系统。 
模型：瀑布模型。
原因：这些系统需要高可靠性、安全性和法规合规性。瀑布模型确保在系统投入运行之前所有需求都得到了明确定义和满足。

社交媒体应用 
例子：Facebook、Twitter。 
模型：增量式开发。
原因：社交媒体平台需要频繁更新和发布新功能以保持用户参与度。增量式开发支持迭代开发和持续用户反馈。

移动应用 
例子：像Fitbit这样的健身应用，或者像Evernote这样的生产力应用。 
模型：增量式开发。
原因：移动应用通常从核心功能开始，然后根据用户反馈和市场趋势添加新功能。增量式开发允许提前发布和迭代改进。

政府项目 
例子：国家税收管理系统或公共安全系统。 
模型：瀑布模型。
原因：政府项目通常有固定的需求和预算，需要进行大量的文档编制，并符合法规标准。瀑布模型的线性方法很好地满足了这些需求。

医疗管理系统 
例子：像 Epic 或 Cerner 这样的电子健康记录（EHR）系统。 
模型：增量式开发。
原因：这些系统需要适应不断变化的医疗法规和用户需求。增量式开发允许进行迭代更新和合规性调整。

教育软件 
例子：像Coursera或Khan Academy这样的在线学习平台。 
模型：增量式开发。
原因：教育软件需要根据用户反馈不断添加新课程、功能和改进。增量式开发允许定期更新和增强。

基础设施软件 
例子：用于电网管理或水处理设施的软件。 
模型：瀑布模型。
原因：这些项目需要详细的前期规划和严格的测试，以确保可靠性和安全性。瀑布模型提供了一种结构化的方法来满足这些要求。

## 2.2 过程活动
前文说过真实的软件过程中技术活动、协作活动以及管理活动交织在一起，其总体目标是完成一个软件系统的规格说明、设计、实现和测试。
4个基本的过程活动——规格说明、开发、确认、演化，在不同的开发过程中的组织方式也各不相同。

### 2.2.1 Software specification（软件规格说明）
软件规格或需求工程是理解和定义以下内容的过程：
系统需要提供哪些服务？系统操作和开发的约束条件。需求工程是软件过程中特别关键的阶段，因为在这个阶段出现的错误必然会导致系统设计和实施阶段的问题。

下图展示了需求工程过程。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/e89f65ce31d74f4e88cd329d6f403b8f.png)
软件规格过程的目标是产生一个经过同意的需求文档，明确了满足利益相关者需求的系统。
需求通常以两个层次的细节呈现：
最终用户和客户需要需求的高层次陈述；
系统开发人员需要更详细的系统规格。
需求工程过程中的主要活动包括：
1.可行性研究
2.需求获取和分析
3.需求规格
4.需求验证

### 2.2.2 Software design and implementation（软件设计和实现）
软件过程中的设计和实施阶段的目标是将系统规格转化为可执行的系统。 这个阶段通常涉及软件设计和编程的过程，但如果采用增量式开发方法，可能还涉及对软件规格的细化。
软件设计是对将要实施的软件结构、系统使用的数据模型和结构、系统组件之间的接口以及有时使用的算法的描述。
下图展示了设计过程的通用模型。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/ef47b33f828a4b51a2a09b075fd295a8.png)
设计师不会立即得出一个完整的设计，而是通过迭代的方式逐步完善设计。随着设计的不断发展，他们会逐渐增加形式和细节，并经常进行回溯，以纠正先前的设计。这种迭代的过程有助于确保设计的质量和完整性。
设计活动包括：
1.体系结构设计。将识别系统的总体结构、基本的构件（有时候也成为子系统或模块），它们之间的关系以及它们是如何分布的。
2.数据库设计。将设计系统的数据结构以及数据库中的数据表现方式。同样，这里的工作取决于是否要复用一个已经存在的数据库或者创建一个新的数据库。
3.接口设计。将定义系统构件间的接口。接口规格说明必须是无歧义的。有了精确的接口定义，一个构件就可以在无须了解另一个构件的具体实现的情况下使用该构件。针对接口规格说明达成一致后，各个构件就可以独立进行设计和开发了。
4.构件选取和设计。将搜索可复用的构件，如果没找到合适的构件那么就设计新的软件构件。此阶段的设计可能只是对构件进行简单的描述，而把实现细节留给程序员。也可以是确定要对一个可复用构件进行的一个修改列表，或者是用UML表示的一个详细的设计模型。接下来，设计模型可以被用于自动地生成实现。

设计输出的细节和表达方式会有很大的差异。
对于关键系统，必须产生详细的设计文档，其中包括精确和准确的系统描述。
如果采用模型驱动方法，这些输出可能主要是图表。
如果采用敏捷开发方法，设计过程的输出可能不是单独的规格说明文档，而是体现在程序代码中。
### 2.2.3 Software validation（软件确认）
软件验证，或者更一般地说，验证和确认，旨在证明以下内容：
1.系统符合其规格。
2.满足系统客户的期望。

验证技术包括：
1.程序测试：通过使用模拟测试数据执行系统来进行验证，这是主要的验证技术。
2.验证也可能涉及在软件过程的每个阶段（从用户需求定义到程序开发）进行检查的过程，比如检查和审查。

下图展示了计划驱动的软件过程中的测试阶段。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/aab54cf5659942c4852edcc848fa3b50.png)
这是一个三阶段的测试过程，首先是对系统组件进行测试，然后是对集成系统进行测试，最后是使用客户数据对系统进行测试。这种测试过程有助于确保系统在不同层面上都能正常运行并满足客户需求。
开发测试：系统的各个组件由系统开发人员进行测试。每个组件都是独立测试的，没有其他系统组件参与。
系统测试：系统组件被集成在一起形成完整的系统。这个过程关注的是发现由于组件之间意外的交互和组件接口问题而导致的错误。
验收测试 ：这是系统被接受用于运行之前的最后一个测试阶段。系统将使用系统客户提供的数据进行测试，而不是使用模拟测试数据。

组件开发和测试过程通常是交错进行的。程序员会自行创建测试数据，并在代码逐步开发过程中进行增量测试。
如果采用增量式开发方法，每个增量都应在开发过程中进行测试，这些测试是基于该增量的需求。
当使用计划驱动的软件过程（例如，对于关键系统开发）时，测试是由一组测试计划驱动的。独立的测试团队根据这些预先制定的测试计划进行工作。
### 2.2.4 Software evolution（软件演化）
一旦决定制造硬件，对硬件设计进行更改将非常昂贵。然而，软件可以在系统开发期间或之后的任何时候进行更改。即使进行广泛的更改，成本仍然远低于对系统硬件进行相应的更改。
历史上，软件开发过程和软件演化（软件维护）过程之间一直存在分歧。人们认为软件开发是一个创造性的活动，从最初的概念到最终的工作系统。然而，他们有时认为软件维护是乏味和不感兴趣的。
与两个独立的过程相比，更现实的是将软件工程视为一个演进过程。





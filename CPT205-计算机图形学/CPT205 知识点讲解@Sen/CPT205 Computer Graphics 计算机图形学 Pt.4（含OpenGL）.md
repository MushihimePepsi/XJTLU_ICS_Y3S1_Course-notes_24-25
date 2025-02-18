- [11. Clipping（裁剪）](#11-clipping裁剪)
  - [11.1 Concepts](#111-concepts)
  - [11.2 Clipping algorithms](#112-clipping-algorithms)
    - [11.2.1 2D Point Clipping](#1121-2d-point-clipping)
    - [11.2.2 2D line clipping](#1122-2d-line-clipping)
      - [11.2.2.1 Brute force clipping](#11221-brute-force-clipping)
      - [11.2.2.2 Cohen-Sutherland 2D line clipping](#11222-cohen-sutherland-2d-line-clipping)
      - [11.2.2.3 Cohen-Sutherland 3D line clipping](#11223-cohen-sutherland-3d-line-clipping)
      - [11.2.2.4 Liang-Barsky线段裁剪算法](#11224-liang-barsky线段裁剪算法)
  - [11.3 Polygon clipping](#113-polygon-clipping)
    - [11.3.1 Convexity and tessellation（使用三角形多边形去处理多边形）](#1131-convexity-and-tessellation使用三角形多边形去处理多边形)
  - [11.4 Pipeline clipping（管道裁剪）](#114-pipeline-clipping管道裁剪)
    - [11.4.1 Pipeline clipping of line segments（线段的管道裁剪）](#1141-pipeline-clipping-of-line-segments线段的管道裁剪)
    - [11.4.2 Pipeline clipping of polygons（多边形的管道裁剪）](#1142-pipeline-clipping-of-polygons多边形的管道裁剪)
      - [11.4.2.1 Bounding boxes（确定边界）](#11421-bounding-boxes确定边界)
  - [11.5 Other issues in clipping（裁剪中的其他问题）](#115-other-issues-in-clipping裁剪中的其他问题)
  - [11.6 OpenGL functions](#116-opengl-functions)
- [12.  Hidden-Surface Removal（隐藏面消除）](#12--hidden-surface-removal隐藏面消除)
  - [12.1 Concepts](#121-concepts)
  - [12.2 Hidden-surface removal algorithms](#122-hidden-surface-removal-algorithms)
    - [12.2.1 Object-space methods（对象空间方法）](#1221-object-space-methods对象空间方法)
      - [12.2.1.1 Painter’s algorithm](#12211-painters-algorithm)
        - [12.2.1.1.1 Painter’s algorithm的简单情况](#122111-painters-algorithm的简单情况)
        - [12.2.1.1.2 Painter’s algorithm的复杂情况](#122112-painters-algorithm的复杂情况)
      - [12.2.1.2 Back-face culling（背面剔除）](#12212-back-face-culling背面剔除)
    - [12.2.2 Image-space methods（图像空间方法）](#1222-image-space-methods图像空间方法)
      - [12.2.2.1 Z-buffer](#12221-z-buffer)
      - [12.2.2.2 Scan-line（扫描线算法）](#12222-scan-line扫描线算法)
        - [12.2.2.2.1 BSP tree（二叉空间分区树）](#122221-bsp-tree二叉空间分区树)
    - [12.2.3 Comparison](#1223-comparison)
  - [12.3 Hidden-surface removal in OpenGL](#123-hidden-surface-removal-in-opengl)

# 11. Clipping（裁剪）
## 11.1 Concepts
裁剪是指移除在裁剪窗口之外的对象或对象的部分，以确保只有位于裁剪窗口内的部分被渲染。
Rasterization（光栅化）又称scan conversion（扫描转换）是将高级对象描述转换为帧缓冲区中像素的颜色，即将几何图形转换为屏幕上的像素点。
图形系统（如OpenGL）会自动为我们执行裁剪和光栅化的过程，因此在使用OpenGL时，通常无需显式地调用特定的函数来执行裁剪和光栅化操作。

光栅化的成本随着创建的片段（候选像素）数量近似线性增长，因为每个像素都需要进行数学和逻辑运算。
如果我们只光栅化实际可见的部分，就可以节省大量昂贵的计算资源，因为现在执行的少量操作可以节省后续的大量计算。

下图是渲染管道，光栅化发生在建模、变换、视图变换、裁剪、投影变换、着色之后。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/8d40ca6c49694296b68a6c9a6e25e39b.png)
其中裁剪、变换、光栅化都是重要的任务，而有些任务会被推迟到片元处理阶段进行，这其中包含隐藏表面移除、Antialiasing（抗锯齿）。下图展示了隐藏表面移除、Antialiasing（抗锯齿）都发生在光栅化之后，这些是在fragment processing（片元处理）中进行的。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/fc3f1953de614ee1b6b11bd56f6c15f8.png)
下图展示了clipping window的过程
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/c910fed6e9664686b9bc8144739ea504.png)
clipping window（裁剪窗口）和viewport（视口）之间的区别：
裁剪窗口用于选择我们在虚拟的二维世界中想要看到的内容，它决定了渲染的范围。
视口则指示了渲染内容在输出设备上（或者显示窗口内）的位置和大小。
默认情况下，视口具有与我们创建的GLUT显示窗口相同的位置和尺寸。

下面的代码用于设置视口的位置和大小。其中，参数x和y表示视口在窗口中的左下角坐标，w和h表示视口的宽度和高度。
```cpp
void glViewport(GLint x, GLint y, GLsizei w, GLsizei h)
```
视口是OpenGL状态的一部分，它可以在渲染不同对象或重绘时进行更改。不同的窗口-视口变换可以用来调整场景的呈现方式。这意味着在OpenGL中，可以通过更改视口的位置和大小来调整场景在屏幕上的呈现方式，从而实现不同的视觉效果。
## 11.2 Clipping algorithms
不同的基本图元，如点、线和多边形，在裁剪过程中可能会被以不同的方式处理。
对于2D图形，裁剪窗口用于裁剪图元。
对于3D图形，裁剪体用于裁剪图元。
线段和多边形相对容易进行裁剪，但对于曲线和文本等复杂图元，通常需要先将其转换为线段和多边形，然后再进行裁剪。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/2ffd77379d7b4537a62fe6f1a70a8287.png)

### 11.2.1 2D Point Clipping
对于给定的点(x, y)，可以通过比较其坐标与裁剪窗口的边界来确定该点是在窗口内部还是外部。如果点的x坐标在裁剪窗口的x最小值和最大值之间，并且点的y坐标在裁剪窗口的y最小值和最大值之间，那么这个点就被认为是在窗口内部。反之，如果点的坐标不满足这个条件，那么这个点就被认为是在窗口外部。![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/6ddb0b9814904476bbe0699c584d8a5e.png)
### 11.2.2 2D line clipping
对于给定的线段，需要确定它是在裁剪窗口内部、外部还是部分在内部部分在外部。如果一条线段部分在裁剪窗口内部，就需要确定如何显示这部分线段。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/8f78f4d2aaa44c3f878b850237ff211a.png)
因此分类讨论：
简单情况，或者说Trivial cases（显然情况）：
Trivial accept（显然接受）：整个线段完全在裁剪窗口内部。
Trivial reject（显然拒绝）：整个线段完全在裁剪窗口的边界之外。
Non-trivial cases（非显然情况）：
1.一个端点在内部，另一个在外部。
2.两个端点都在外部，但不是“显然”在外部。
这两种都需要找到线段内部的部分。找到这部分的步骤如下：
1.计算线段与裁剪窗口边界的交点。
2.这些交点中，只有一到两个会在窗口的边界上。
3.这些交点中的一到两个点将成为所需线段的端点。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/907941c7ea6e4491abd029a19adfda30.png)
#### 11.2.2.1 Brute force clipping
使用斜率-截距公式（y = mx + b）来处理线段和四个裁剪边的交点。
这种方法适用于处理无限直线，因为斜率-截距公式可以很好地描述直线的特性。
这种方法无法处理垂直线。因为斜率-截距公式无法准确描述垂直线。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/0230e7fd54fb44499ce3738097b701a2.png)
下面的这张图中，使用了相似三角形去裁剪线段。
针对裁剪窗口的边缘（例如顶部边缘），需要找到线段与该边缘的交点（x’和y’）。可以利用$A/B=C/D, A= (x_2- x_1),B = (y_2- y_1),C = (x’ - x_1),D = (y’ - y_1) = (y_{max}- y_1)$，所以$C = A*D / B$，从而得到$x’ = x_1 + C,(x’, y’) = (x_1 + C, y_{max})$
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/a731e0462e844ef8b455f72849aa587f.png)
使用相似三角形方法需要进行以下操作：4次浮点数减法，1次浮点数乘法，1次浮点数除法 ，且这些操作需要重复执行4次（每条边执行一次）。

#### 11.2.2.2 Cohen-Sutherland 2D line clipping
这种方法的特点有：
1.有组织性。
2.高效。
3.能够计算出需要裁剪的线段的新端点。
方法如下：
1.为每个端点创建一个outcode（外部编码），其中包含有关该点相对于裁剪窗口的位置信息。
2.使用两个端点的外部编码来确定线段相对于裁剪窗口的配置。
3.如果需要，计算新的端点。
4.在3D空间中，可以通过使用6个面而不是4条边来扩展到3D空间。
其思想在于即尽可能排除不必要的情况，而不进行交点计算。
从裁剪窗口的四条边开始，这四条边将确定裁剪窗口的范围。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/85d98cac62a448f39dc3a91fe4e33fda.png)
情况1：线段的两个端点都在裁剪窗口的四条边内部。
Trivial accept直接接受这条线段，画出这条线。
条件是$x_1，x_2$在$x_{min}，x_{max}$之间且$y_1，y_2$在$y_{min}，y_{max}$之间
情况2：线段的两个端点都在裁剪窗口的四条边外部，并且在同一条边的同一侧。Trivial reject直接拒绝线段，不需要进行额外的裁剪操作。
条件是对于横坐标$x_1，x_2$小于$x_{min}$或$x_1，x_2$大于$x_{max}$
纵坐标$y_1，y_2$小于$y_{min}$或$y_1，y_2$大于$y_{max}$
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/70aec4be7a3e4c02917669d3bdd05b90.png)
情况3：线段的一个端点在内部，一个端点在外部。
在这种情况下，至少需要进行一次交点计算。
情况4：两个端点都在裁剪窗口外部的情况。
在这种情况下，线段可能有一部分在裁剪窗口内部，因此至少需要进行一次交点计算来确定线段在裁剪窗口内的部分。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/cfa3496ab5304dbe9da8a171f0774b28.png)
定义外部编码的过程如下：将裁剪平面分割成9个区域，并为每个区域分配一个4位的外部编码，用于表示相对于裁剪窗口的位置（左、右、下、上）。
对于每个线段端点，计算其外部编码。计算外部编码的方法是根据端点的坐标与裁剪窗口边界的关系来确定四个比特位（b0、b1、b2、b3）（排列的时候是$b_3b_2b_1b_0$，其中：
$b_0 = 1$ 如果 $x < x_{min}$，否则为 $0$
$b_1 = 1$ 如果 $x > x_{max}$，否则为 $0$
$b_2 = 1$ 如果 $y < y_{min}$，否则为 $0$
$b_3 = 1$ 如果 $y > y_{max}$，否则为 $0$
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/9d01c30bee9b45f58bfbb604a6d67e55.png)
计算外部编码需要进行最多4次减法操作，以确定端点相对于裁剪窗口的位置。

下面将对各种情况给出例子。
如图，情况1是AB，两个点都是$0000$，这种情况是Trivial accept。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/202e5b87c8e14e348848c6249003bbbc.png)
如图，情况3是CD，其中C点是$0000$，D点不是$0000$。
需要计算交点，以确定线段在裁剪窗口内的部分。
外部编码中的$1$的位置决定了需要与哪一条裁剪窗口边界进行交点计算。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/ffb1481b6a68456c9b021a794b80fe80.png)
如图，情况2是EF，其中E点和F点都不是$0000$，但是他们有一个共同位置的$1$。（这一步可以通过逻辑与运算AND进行判断）
这表明它们都在裁剪窗口的同一侧。如图在右侧。这种情况是Trivial reject。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/372f6703a43e4332a39795dc42ca7679.png)
如图，情况4是GH和IJ，这两条线段都有外部编码为$0001$和$1000$。进行逻辑与运算AND后得到$0$，这意味着线段GH和IJ的两个端点不在窗口的同一侧。
通过与窗口一侧之一相交来缩短线段，确定与窗口的新交点以缩短线段。
在必要时重新执行裁剪算法。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/1ead2e47d5b845e6854f4c7740bf2ae0.png)
当裁剪窗口相对于整个数据库来说比较小的时候，大多数线段都会在裁剪窗口的外部，因此可以根据它们的外部编码快速排除掉。这样可以提高算法的效率。
然而，当线段需要经过多个步骤进行缩短时，算法的效率可能会降低。因为在这种情况下，需要重新计算线段与裁剪窗口边界的交点，而且还需要计算新的外部编码。这样会导致额外的计算负担，降低了算法的效率。

#### 11.2.2.3 Cohen-Sutherland 3D line clipping
前面提到在3D空间中，可以通过使用6个面而不是4条边来扩展到3D空间。
因此我们可以使用6位的外部编码，6个平面和27个区域。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/a75009bd62014206a21244a05ab8640f.png)
#### 11.2.2.4 Liang-Barsky线段裁剪算法
该算法使用参数α来表示线段上的点$p(α) = (1-α)p_1 + αp_2$，其中$0≤α≤1$。具体表示为$x(α) = (1-α)x_1+ αx_2$,$y(α) = (1-α)y_1+ αy_2$通过观察α值的顺序来区分不同的情况，这是因为线段与裁剪窗口的边界线相交的情况取决于α值的顺序。
如图所示，在情况a中，α4代表线段与裁剪窗口右边界的相交点，α3代表线段与裁剪窗口上边界的相交点，α2代表线段与裁剪窗口左边界的相交点，α1代表线段与裁剪窗口下边界的相交点。当α4 > α3 > α2 > α1时，表示线段依次与裁剪窗口的右边界、上边界、左边界和下边界相交，这时需要对线段进行缩短以适应裁剪窗口。
在情况b中，α4代表线段与裁剪窗口右边界的相交点，α2代表线段与裁剪窗口左边界的相交点，α3代表线段与裁剪窗口上边界的相交点，α1代表线段与裁剪窗口下边界的相交点。当α4 > α2 > α3 > α1时，表示线段依次与裁剪窗口的右边界、左边界、上边界和下边界相交，这时线段会被拒绝，因为它并不与裁剪窗口相交。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/599e6fe2f3af4325b1e5beb924f4a8d0.png)
这个算法的优点如下：1.可以像Cohen-Sutherland算法一样轻松地接受或拒绝线段。
2.通过使用参数α的值，Liang-Barsky算法不需要像Cohen-Sutherland算法那样递归地进行裁剪。这意味着该算法在确定线段与裁剪窗口的相交情况时，不需要反复地进行递归计算，从而提高了算法的效率。
3.Liang-Barsky算法可以扩展到3D空间。

## 11.3 Polygon clipping
当我们将线段和平面的方程写成矩阵形式时，我们需要解以下方程组：
$p(α) = (1-α)p_1 + αp_2, 0≤α≤1$ 
$n⋅(p(α) – p0) = 0$
这个方程组表示了线段和平面的交点。在这里，$p(α)$表示线段上的点，$n$表示平面的法向量，$p_0$表示平面上的一个点。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/6f9e52bbecb14e0a99c613d2b7d8acf8.png)
对应于交点的参数α的值： $α = (n⋅(p_0 - p_1)) / (n⋅(p_2 - p_1))$。
这个公式需要进行6次乘法和1次除法运算。

在三维空间中进行一般的裁剪需要对线段进行与任意平面的相交计算。它可能不是像二维空间的那样是简单的矩形窗口。
如下图的这个倾斜视图。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/e7b64e420f1e4683937f03928ce3d917.png)
规范化是视图处理的一部分（在裁剪之前），但在规范化之后，我们需要对右平行六面体的各个面进行裁剪。
典型的相交计算现在只需要进行浮点数减法，例如判断x是否大于xmax。
规范化可以简化裁剪过程中的交点计算。
如下图的俯视图。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/e694cdcfb45c495d883fa34ac8a2f63d.png)
多边形裁剪没有线段裁剪那么简单：
裁剪一个线段最多产生一个线段。而裁剪一个多边形可能会产生多个多边形。如图所示。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/10a9c090f78744349c61c1de9c893e75.png)
然而，裁剪一个凸多边形最多会产生另一个多边形。因为是凸多边形的特性。

### 11.3.1 Convexity and tessellation（使用三角形多边形去处理多边形）
这种策略用一组三角形多边形（tessellation）来替换非凸（凹）多边形。如图所示。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/c95839cf82d74ab7a1b352b3acb64d2d.png)
非凸多边形可能会导致一些计算或渲染上的困难，因此将其替换为一组三角形多边形可以简化处理过程。
GLU库有关于tessellation的代码。

## 11.4 Pipeline clipping（管道裁剪）
### 11.4.1 Pipeline clipping of line segments（线段的管道裁剪）

将线段裁剪视为一个黑匣子，只需要知道它接受两个顶点作为输入，并产生裁剪后的线段的顶点作为输出，而不需要了解其具体的实现细节。如图所示。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/a5e1acbcd7604193b13d9fb231df4830.png)
在线段的管道裁剪过程中，可以将对窗口的每一侧进行裁剪看作是相互独立的过程，因此可以使用四个独立的裁剪器组成一个管道来处理线段的裁剪。如图所示。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/fcbf3bfb8fae4d3eb50aaa4be2770b55.png)
### 11.4.2 Pipeline clipping of polygons（多边形的管道裁剪）
在三维空间中，添加前后裁剪器来处理多边形的裁剪。
SGI几何引擎可能采用了特定的策略或算法来处理三维空间中多边形的管道裁剪。
在采用前后裁剪器的策略时，可能会引入一定的延迟，尽管增加的延迟很小。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/0030c365626a4921a74fb9dea6de2ed5.png)
#### 11.4.2.1 Bounding boxes（确定边界）
在多边形的顶点中找到最大和最小的 x 和 y 值，然后构建一个与坐标轴对齐的矩形，使得这个矩形能够包围住整个多边形。这样的方式计算也非常简单。如图所示。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/7087adf6883c458594e8caba032cffd3.png)
因此我们可以通过这个边框去接受或拒绝一个对象。如图所示，从而进行分类讨论。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/c4540fa8e7464f4daf5c78bc53772359.png)
## 11.5 Other issues in clipping（裁剪中的其他问题）
1.裁剪其他形状：包括圆形、椭圆、曲线等形状的裁剪。
2.对一个形状进行裁剪以适应另一个形状：这指的是将一个形状裁剪成适应另一个形状的大小和轮廓。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/580721b509674199bcf6a8b522278513.png)

3.裁剪内部区域:裁剪过程中需要考虑如何处理形状的内部区域。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/960205f95ec94dceba76e569ba0bacc4.png)

## 11.6 OpenGL functions
```cpp
glViewport(xvmin, yvmin, vpWidth, vpHeight);
```
OpenGL中使用glViewport函数来设置视口，该函数接受四个参数，分别是xvmin、yvmin、vpWidth和vpHeight，它们都是以整数屏幕坐标表示的，相对于显示窗口的左下角。
如果我们不调用glViewport函数，那么默认情况下，OpenGL会使用与显示窗口相同大小和位置的视口（即，整个GLUT窗口都用于OpenGL显示）。

如果我们想要设置裁剪窗口，可以通过下列的代码进行设置。前两行指定了投影矩阵为当前矩阵，并重置投影矩阵，以确保新的视图参数不会与旧的视图参数相混合。后面几行是不同类型的投影变换。
```cpp
glMatrixMode(GL_PROJECTION)
glLoadIdentity(); // reset, so that new viewing parameters
 				  // are not combined with old ones (if any)
gluOrtho2D(xwmin, xwmax, ywmin, ywmax);
glOrtho(xwmin, xwmax, ywmin, ywmax, near, far);
gluPerspective(vof, aspectratio, near, far);
glFrustum(xwmin, xwmax, ywmin, ywmax, near, far);
```
在设置了裁剪窗口后，裁剪窗口内的对象经过投影变换后会被映射到标准化设备坐标系中的范围为(-1,1)的区域内。

# 12.  Hidden-Surface Removal（隐藏面消除）
## 12.1 Concepts
Clipping（裁剪）和Hidden-Surface Removal（隐藏面消除）有很多共同之处：它们都涉及移除对于相机不可兼得物体或物体的部分。它们都可以排除不会在最终渲染图像中可见的部分，以提高渲染效率和减少不必要的计算。因此我们会尝试尽早进行可见性或遮挡测试，以在整个渲染流水线（比如光栅化）之前尽可能多地消除多边形。

Hidden-Surface Removal（有称Visible-Surface detection或Hidden-Surface Elimination）：显示所有可见面，不显示任何被遮挡的表面。

因此实现问题的核心是使用算法去判断哪些表面是可见的。我们稍后会介绍Hidden-Surface Removal的一些算法，比如Z-buffer等。我们将算法分成两类——Object-space methods（对象空间方法）和 Image-space methods（图像空间方法）。
Object-space methods（对象空间方法）是在对象的模型空间中进行隐藏面消除，它会确定哪些物体在其他物体的前面。
优点：1.在场景中的物体尺寸发生变化时，不需要重新计算隐藏面消除，因为它是在物体的模型空间中进行计算的。
2.它适用于静态场景，因为场景不会发生变化，
缺点：1.在某些情况下可能难以或不可能确定哪些物体在其他物体的前面。
Image-space methods（图像空间方法）是在屏幕空间中进行隐藏面消除，它会确定每个像素处可见的物体。
优点：1.它适用于动态场景，因为场景中的物体可能会发生变化。
缺点：1.当场景中的物体尺寸发生变化时，需要重新计算隐藏面消除，因为它是在屏幕空间中进行计算的。
## 12.2 Hidden-surface removal algorithms
### 12.2.1 Object-space methods（对象空间方法）
使用多边形（物体）之间的成对测试。
这个测试会先通过几何计算和碰撞检测算法来确定两个多边形是否相交，然后进一步计算遮挡的多边形之间的部分遮挡情况，从而确定每个多边形的可见部分。
下图展示了的便是Partially obscuring（部分遮挡）的情况。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/e26baefc21d04638a619a0ecf57556f1.png)

下图展示了Draw independently（独立绘制）的情况。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/7bb188dfbe0c45fda14ea2c982c939e8.png)
对象空间方法的时间复杂度是多项式级别的，随着多边形数量的增加，计算成本会呈二次方增长，即时间复杂度为$O(n^2)$。

#### 12.2.1.1 Painter’s algorithm
Painter’s algorithm是一种对象空间算法。
它通过以后至前的顺序来渲染多边形。这样靠近观察者的多边形会覆盖在远离观察者的多边形之上。
根据深度（z值）对表面/多边形进行排序。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/9a84958a9c9c43139598878c7b1e999a.png)
由于是将z值进行排序，因此排序所需要的算法的时间复杂度是O(n log n)。
并非每个多边形都在其他所有多边形的前面或后面，可能一些多边形可能会有重叠或相交的情况，使得排序变得更加复杂。
下图是将多边形按与COP的距离进行排序（COP是Center of Projection，即投影中心），箭头表示这个多边形的深度。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/41b5d2c225564a32b883fbddf75d0a13.png)
##### 12.2.1.1.1 Painter’s algorithm的简单情况
如上图所示，多边形A完全位于其他所有多边形的后面，可以首先绘制。除此之外，在z轴（深度）上重叠但在x或y轴上不重叠的多边形也可以独立绘制。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/08cc04494b2a40ab80ebc1d6b42f8ad3.png)
##### 12.2.1.1.2 Painter’s algorithm的复杂情况
复杂情况也有很多种情况，例如
在所有方向上都有重叠：即它们的投影在x、y和z轴上都有重叠。如图所示。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/338392194d334053b15016bcdadb925b.png)
Cyclic overlap（循环重叠）：多边形之间存在循环的重叠关系，即多边形A遮挡多边形B，多边形B遮挡多边形C，而多边形C又遮挡多边形A。如图所示。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/dcec7ed56e614a8190f556a21160db55.png)
Penetration（穿透）：即一个多边形的一部分在另一个多边形内部。如图所示。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/357cf7933c8c40ab8d22a86dcca10f02.png)
#### 12.2.1.2 Back-face culling（背面剔除）
该方法在比较多边形的位置和方向与观察方向v的过程种删除掉朝向摄像机背面的多边形。
这种删除过程最小化了隐藏面删除过程中的计算开销。
这种方法基本上十一中确定多边形可见性的测试，基于此测试，如果多边形不可见，可以将其删除。

具体步骤如下：假设物体是一个实体的多面体。
计算多边形的法向量$n$：
假设多边形的顶点按逆时针顺序排列。
对于三角形(abc)：$n = (ab) × (bc)$，即通过顶点坐标计算得到多边形的法向量。
如果$90°≥ θ ≥-90°$，即$v•n ≥ 0$，则多边形是一个可见面。
如果物体描述被转换为投影坐标，并且观察方向平行于观察$z_v$轴，即$n = (0,0,1,1)^T$，只需测试$n$的$z$分量的符号即可判断其的可见性。(当$z$分量为正，则表示多边形的法向量指向观察者，即多边形可见。当$z$分量分量为负，则表示多边形的法向量指向远离观察者，即多边形不可见。）
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/ca414af551874b84ba1a29505dca45b1.png)

因此当$v•n < 0$其中$v$是观察者方向$n$是多边形的法向量，剔除该多边形。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/73b22fa8bafa4ae6bd476d6f9a61bb3a.png)

但是该方法无法处理：1.由于多个物体造成的重叠的前向面
2.由于凹多边形造成的重叠的前向面
3.非多边形模型
4.非封闭对象
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/64be49f1eece4230b0208146e32aec8c.png)

下面是Back-face culling的一个例子
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/55b1aaf600104c7eb8b2bc88f60d0394.png)
所以对于$face_1$, $n_1·v = (2, 1, 2) · (1, 0, 1) = 2 + 0 + 2 = 4 > 0$，这是前向面。
对于$face_2$, $n_2 ·v = (-3, 1, -2) · (1, 0, 1) = -3 + 0 - 2 = -5 < 0$，这是背向面。因此要剔除。

### 12.2.2 Image-space methods（图像空间方法）
在一块$n×m$的屏幕上考虑$k$个多边形以找到最近的可见多边形。
所以它的时间复杂度为$O(nmk)$。
Ray tracing（光线追踪）、Z-buffer等方法都是图像空间方法。

#### 12.2.2.1 Z-buffer
在渲染过程中，当多个物体或多边形在屏幕上的某个像素位置发生重叠时，Z-buffer算法可以确定哪个物体或多边形是可见的，哪些是被遮挡的。
在图形硬件中，hidden-surface removal通常使用Z-buffer算法完成。
具体细节如下：Z-buffer是指一个与屏幕大小相同的二维数组，用于存储深度信息。这个数组的每个元素对应屏幕上的一个像素，用于存储该像素对应的深度值。
这是作为颜色缓冲区（帧缓冲区）的补充，颜色缓冲区用于存储要显示的像素的颜色值。
Z-buffer中的值通常表示深度（z值），用于确定物体在观察空间中的距离。
在Z-buffer算法中，Z-buffer的初始化非常重要。通常，Z-buffer会被初始化为远裁剪平面的值，即在裁剪之后的最大可能z值。
颜色缓冲区也需要进行初始化，通常将每个元素初始化为背景颜色值。
对于每个多边形，我们有一组由该多边形覆盖的像素值。这些像素值指的是多边形在屏幕上所覆盖的像素位置。对于每个像素，我们将其深度值（z值）与Z-buffer中已存储的值进行比较：如果当前像素的深度值小于Z-buffer中已存储的值，表示该像素更靠近观察者。我们就将当前像素的深度值替换Z-buffer中的值，并将当前像素的颜色值替换颜色缓冲区中的值。
针对图像中的所有多边形重复这个过程，确保每个像素对应的最近的可见物体被正确渲染。

Z-buffer算法的实现通常是在归一化坐标系中进行的，这样深度值可以从近裁剪平面的0到远裁剪平面的1进行范围化处理。
因此具体算法如下：1.初始化所有深度depth值为1.0，这表示初始时所有像素的深度值都设置为最大值，表示远离观察者的距离。同时，将刷新refresh值设置为背景颜色，表示初始时所有像素的颜色都是背景色。
2.获取当前像素位置的深度值depth(x,y)，计算当前像素位置的深度值z,如果z < depth(x,y)，即当前像素的深度值小于Z-buffer中已存储的深度值，表示当前像素更接近观察者,更新Z-buffer中的深度值depth(x,y)为z，并将刷新值refresh(x,y)设置为当前像素的颜色值$I_s$(x,y)。
```
If(z < depth(x,y))
 {
 depth(x,y) = z
 refresh(x,y) = I_s(x,y)
 }
```
关于像素的颜色值，在实际渲染过程中，需要使用相关的算法来计算深度值、光照效果、填充颜色和纹理等。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/8e29083d6638491798da5d36b7c1dcb8.png)
Z-Buffer的优点：
1.Z-buffer算法是最广泛使用的隐藏面消除算法。
2.它是一种基于图像空间的算法，按照多边形而不是像素进行操作。
3.通过逐个多边形地光栅化确定哪些多边形（或多边形的哪一部分）被绘制在屏幕上。
4.相对而言，Z-buffer算法在硬件或软件中的实现相对较容易。
内存需求：
1.Z-buffer算法依赖于一个称为Z-buffer或深度缓冲区的辅助缓冲区。
2.Z-buffer的宽度和高度与帧缓冲区相同。
3.每个单元格包含该像素位置处物体的z值（与观察者的距离）。

#### 12.2.2.2 Scan-line（扫描线算法）
通过逐行扫描屏幕并处理每个像素来进行渲染。
随着我们沿着扫描线移动，深度的变化满足方程式$a∆x + b∆y + c∆z = 0$。这里的$a、b、c$代表了多边形所在平面的法向量的分量，$∆x、∆y、∆z$分别代表在屏幕空间中$x、y、z$方向上的变化量。因此在扫描线上$∆y = 0$，$∆z = -(a/c)*∆x$。
这表明在屏幕空间中，当我们沿着扫描线移动时，z值的变化可以通过x值的变化来计算，而且这个计算只需要针对每个多边形进行一次。
图像空间算法的最坏情况性能与图元（primitives）的数量成正比。
Z-buffer算法的性能与光栅化生成的片元（fragments）数量成正比，而片元数量取决于光栅化多边形的面积。

如图。在Scan-line（扫描线算法）的具体实现中。
对于扫描线i：在这条扫描线上，不需要深度信息，因为它只会位于零个或一个多边形内部。因为这条扫描线上不存在多个多边形的重叠。
对于扫描线j：在这条扫描线上，只有当它位于多个多边形之间时才需要深度信息。因为可能存在多个多边形的重叠，所以需要深度信息来确定哪个多边形在另一个多边形的前面。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/02f44ec1a5b24f16be734ab46ba04f0c.png)
所以在具体实现中需要一个数据结构来存储以下内容：
1.每个多边形的标志（内部/外部），用于确定扫描线在多边形内部还是外部。
2.对于扫描线的增量结构，用于存储遇到的边界信息，这有助于确定多边形的轮廓和边界。
3.平面方程的参数，以便于进行深度和交点的计算。

##### 12.2.2.2.1 BSP tree（二叉空间分区树）
在许多实时应用程序中，比如游戏，我们希望尽可能减少应用程序中的物体数量，以便实现以下目的：
1.reduce burden on pipeline（减轻管线的负担）。
2.reduce traffic on bus（减少总线上的数据传输量）。
BSP tree通过递归地将空间分割为二叉树节点来实现空间的分区。每个节点都代表了空间中的一个区域，并且可以被用来判断物体是否在该区域内。
如图所示，这里有6个平行的平面，这里平面A将平面B和平面C与平面D、E和F分开。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/60a9aaec6b72429398e7ca2f736972a7.png)
可以继续递归地确定它们之间的空间关系：
平面C将平面B与平面A分开。而平面D又将平面E与平面F分开。
这种信息可以用来构建BSP树（二叉空间分区树），BSP树可以用于进行可见性测试（inside）和遮挡测试（outside）。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/0d34927e4d874ccdb0581c67f547ccfc.png)
这种数据结构也可以用在Painter’s algorithm，深度越大的面应该在列表的前面，深度越小的面应该在列表的后面。因此使用深度优先搜索，然后先遍历左子树或右子树，用深度优先搜索以便按照远近顺序访问面。

创建BSP树的步骤如下：1.任意的选择一个多边形。
2.使用多边形所在的平面来分割空间单元。这一步可能需要将多边形在与平面相交的地方进行切割，以确保每个空间单元只包含一个多边形片段。
3.持续这个过程，直到每个空间单元只包含一个多边形片段。
在这个过程中，选择分割平面的方式可能有多种，但是并没有一个有效的最优算法来构建BSP树。BSP树并不是唯一的，对于同一组多边形可能存在多种不同的BSP树构建方式。而“最优”通常指的是在构建BSP树时，希望得到一个平衡树，即每个节点的左右子树包含的多边形片段数量差别不大。

BP树在渲染中，位于观察点所在的一侧的物体不会遮挡位于观察点相对的一侧的物体。
渲染过程是对BSP树进行递归处理的。在每个节点从远处向近处进行渲染：
1.如果观察点位于分割平面的一侧，那么需要递归地进入不包含观察点的子树的一侧。通过测试观察点与分割平面的关系，可以确定哪些多边形是可见的，哪些是被遮挡的。
2.绘制位于分割平面上的多边形，并覆盖已经绘制的内容。
3.递归地进入包含观察点的子树的一侧。

例子如图所示。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/04075e7ac6a14429b88934a76250392c.png)

### 12.2.3 Comparison
由前面的知识我们可以发现Z-buffer算法和其他像素空间算法通常用于实时渲染，它们能够以每个像素为单位进行处理。而对象空间方法通常可以在静态场景中提前进行处理，然后在渲染时直接使用。
## 12.3 Hidden-surface removal in OpenGL
在OpenGL中，隐藏表面移除是通过z-buffer算法来实现的。这个算法会在渲染过程中保存深度信息，当对象或三角形被渲染时，只有最前面的对象会出现在图像中。该算法使用额外的缓冲区，即Z-buffer，来存储深度信息，当几何图形通过渲染管线时，Z-buffer会记录每个像素的深度值。（前文有详细叙述）
在mian（）方法中需要请求使用深度缓冲区：

```cpp
 glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH)
```

在初始化函数中需要启用深度测试：

```cpp
glEnable(GL_DEPTH_TEST)
```

在显示的回调函数中需要清除颜色缓冲区和深度缓冲区：

```cpp
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
```


OpenGL基本库提供了用于背面移除和深度缓冲区可见性测试的函数。此外，OpenGL还提供了用于线框显示的隐藏线移除函数，这有助于在线框模式下更清晰地显示场景。另外，OpenGL还支持Depth cueing（深度提示）技术，这个技术通过深度信息来增强场景深度感知，有助于提高场景的立体感和视觉效果。
背面移除函数：

```cpp
glEnable(GL_CULL_FACE);
glCullFace(GLenum);
```
第一行的函数用于启用面剔除。第二行的函数可以设置剔除的模式。参数 mode 包括 GL_BACK（剔除背面）、GL_FRONT（剔除正面）和GL_FRONT_AND_BACK（剔除正面和背面）。
默认情况下，glCullFace() 函数的默认值是 GL_BACK。因此，如果调用 glEnable(GL_CULL_FACE) 来启用面剔除，而没有显式调用 glCullFace() 来设置剔除模式，那么默认情况下会移除场景中的背面。

深度缓冲区的函数有：

```cpp
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
```
这个函数用于初始化窗口的显示模式。

```cpp
glClear(GL_DEPTH_BUFFER_BIT);
```
这个函数用于清除深度缓冲区。

```cpp
glEnable(GL_DEPTH_TEST);
glDisable(GL_DEPTH_TEST);
```
这两个函数分别用于启用和禁用深度测试。

由于这一步操作时在规范化之后的，所以深度值范围通常是[0.0, 1.0]。因此按我们前面所学的知识，为了更快处理，应该使用代码将深度缓冲区的值改为最大深度值1.0。

```cpp
 glClearDepth(maxDepth);
```

在投影坐标中，通常会将坐标规范化到范围[-1.0, 1.0]。而在深度值方面，位于近裁剪平面和远裁剪平面之间的深度值会进一步规范化到范围[0.0, 1.0]，其中0.0对应于近裁剪平面，1.0对应于远裁剪平面。
这两个裁剪平面也可以进行调整。下面的函数可以设置这两个平面。
```cpp
glDepthRange(nearNormDepth, farNormDepth);
```
nearNormDepth 和 farNormDepth 分别表示近裁剪平面和远裁剪平面的深度值。默认情况下，它们的值分别是0.0和1.0，而它们可以在范围[0.0, 1.0]内取值。

下面这个函数可以设置深度测试的条件。
```cpp
glDepthFunc(testCondition);
```
这里testCondition可以取得值如下：
GL_LESS：如果新像素的深度值小于当前深度缓冲区中的深度值，则通过深度测试。
GL_GREATER：如果新像素的深度值大于当前深度缓冲区中的深度值，则通过深度测试。
GL_EQUAL：如果新像素的深度值等于当前深度缓冲区中的深度值，则通过深度测试。
GL_NOTEQUAL：如果新像素的深度值不等于当前深度缓冲区中的深度值，则通过深度测试。
GL_LEQUAL：如果新像素的深度值小于或等于当前深度缓冲区中的深度值，则通过深度测试。
GL_GEQUAL：如果新像素的深度值大于或等于当前深度缓冲区中的深度值，则通过深度测试。
GL_NEVER：永远不通过深度测试，新像素将不会被绘制。
GL_ALWAYS：始终通过深度测试，新像素将始终被绘制。

深度缓冲区可以被设置为只读或者可以读写。通过下面的函数进行修改。
```cpp
glDepthMask(writeStatus);
```
当 writeStatus 为 GL_FALSE 时，深度缓冲区的写入模式被禁用，只能获取深度值用于比较。
这个功能在当使用复杂的背景并显示不同的前景对象时非常有用：
1.可以先将背景存储在深度缓冲区中，然后禁用写入模式以处理前景对象，从而生成一系列具有不同前景对象或一个对象在不同位置的帧，用于制作动画序列。
2.在显示透明对象时也很有用，因为透明对象的渲染通常需要按深度顺序进行，通过禁用写入模式可以更好地处理透明对象的渲染。

下面的函数负责控制渲染效果。
```cpp
glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
```
这个函数用于将对象的多边形模式设置为线框模式，即对象将以线框的形式呈现，包括可见的边和隐藏的边。

```cpp
glEnable(GL_FOG);
```
这个函数用于启用雾化效果，雾化效果可以根据物体到观察位置的距离来调整物体的亮度，从而产生视觉上的深度感。
```cpp
glFog{if}[v](GL_FOG_MODE, GL_LINEAR);
```
这个函数用于设置雾化模式为线性模式，即根据物体到观察位置的距离线性地调整颜色亮度，范围为[0.0, 1.0]，使远处的物体变暗。
```cpp
glFog{if}[v](GL_FOG_START, minDepth);
```
这个函数用于指定雾化效果的起始深度。
```cpp
 glFog{if}[v](GL_FOG_END, maxDepth);
```
这个函数用于指定雾化效果的结束深度。
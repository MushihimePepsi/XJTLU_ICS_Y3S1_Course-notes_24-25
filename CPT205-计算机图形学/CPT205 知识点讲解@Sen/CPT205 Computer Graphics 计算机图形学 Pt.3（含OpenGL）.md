- [9.Lighting and Materials（光照和材质）](#9lighting-and-materials光照和材质)
  - [9.1 Background](#91-background)
  - [9.2 Lighting sources（光源）](#92-lighting-sources光源)
    - [9.2.1 Point light（点光源）](#921-point-light点光源)
    - [9.2.2 Directional light（定向光源）](#922-directional-light定向光源)
    - [9.2.3 Spot light（聚光灯光源）](#923-spot-light聚光灯光源)
  - [9.3 Surface lighting effects（表面光照效应）](#93-surface-lighting-effects表面光照效应)
    - [9.3.1 Surface lighting effects：Ambient light（环境光对物体的影响）](#931-surface-lighting-effectsambient-light环境光对物体的影响)
    - [9.3.2 Surface lighting effects：Diffuse light（漫反射光对物体的影响）](#932-surface-lighting-effectsdiffuse-light漫反射光对物体的影响)
    - [9.3.3 Surface lighting effects：Specular reflectance（镜面反射光对物体的影响）](#933-surface-lighting-effectsspecular-reflectance镜面反射光对物体的影响)
    - [9.3.4 Surface lighting effects: Illustrated](#934-surface-lighting-effects-illustrated)
  - [9.4 Attenuation（衰减）](#94-attenuation衰减)
  - [9.5 Lighting model and shading（光照模型和着色）](#95-lighting-model-and-shading光照模型和着色)
    - [9.5.1 Lighting model（光照模型）](#951-lighting-model光照模型)
    - [9.5.2 Phong model](#952-phong-model)
    - [9.5.3 Polygonal Shading（多边形着色）](#953-polygonal-shading多边形着色)
      - [9.5.3.1 Vertex Shading（顶点着色）](#9531-vertex-shading顶点着色)
      - [9.5.3.2 Flat Shading/Constant shading（平面着色）](#9532-flat-shadingconstant-shading平面着色)
      - [9.5.3.3 Smooth Shading/Interpolative shading（平滑着色/插值着色）](#9533-smooth-shadinginterpolative-shading平滑着色插值着色)
      - [9.5.3.4 Gouraud Shading](#9534-gouraud-shading)
      - [9.5.3.5  Summary](#9535--summary)
  - [9.6 Material（材质）](#96-material材质)
    - [9.6.1 RGB values for lights and materials（光源和材质的RGB值）](#961-rgb-values-for-lights-and-materials光源和材质的rgb值)
    - [9.6.2 Material properties（材质属性）](#962-material-properties材质属性)
  - [9.7 Implementations in OpenGL（在OpenGL中实现）](#97-implementations-in-opengl在opengl中实现)
    - [9.7.1 OpenGL中的聚光灯](#971-opengl中的聚光灯)
    - [9.7.2 OpenGL中的多光源](#972-opengl中的多光源)
    - [9.7.3 OpenGL中的全局环境光](#973-opengl中的全局环境光)
    - [9.7.4 OpenGL中的本地视点和无限视点](#974-opengl中的本地视点和无限视点)
    - [9.7.5 OpenGL中的双面光照](#975-opengl中的双面光照)
    - [9.7.6 OpenGL中定义材质属性](#976-opengl中定义材质属性)
- [10. Texture Mapping（纹理贴图）](#10-texture-mapping纹理贴图)
  - [10.1 Concepts of texture mapping（纹理贴图的概念）](#101-concepts-of-texture-mapping纹理贴图的概念)
  - [10.2 Types of texture mapping（纹理映射的类型）](#102-types-of-texture-mapping纹理映射的类型)
  - [10.3 Specifying the texture（指定纹理）](#103-specifying-the-texture指定纹理)
  - [10.4 Magnification and minification （放大和缩小）](#104-magnification-and-minification-放大和缩小)
  - [10.5 Two-step mapping](#105-two-step-mapping)
    - [10.5.1 Two-part mapping（两部分映射）](#1051-two-part-mapping两部分映射)
      - [10.5.1.1 Cylindrical mapping（圆柱体映射）](#10511-cylindrical-mapping圆柱体映射)
      - [10.5.1.2 Spherical mapping（球体映射）](#10512-spherical-mapping球体映射)
      - [10.5.1.3 Box mapping（盒状映射）](#10513-box-mapping盒状映射)
    - [10.5.2 Second mapping](#1052-second-mapping)
      - [10.5.2.1 Aliasing（失真）](#10521-aliasing失真)
      - [10.5.2.2 Area averaging](#10522-area-averaging)
  - [10.6 Steps in texture mapping and OpenGL functions](#106-steps-in-texture-mapping-and-opengl-functions)
    - [10.6.1 OpenGL functions](#1061-opengl-functions)
    - [10.6.2 Texture mapping and the OpenGL pipeline](#1062-texture-mapping-and-the-opengl-pipeline)
    - [10.6.3 Specifying a texture image](#1063-specifying-a-texture-image)
    - [10.6.4 Defining image as a texture](#1064-defining-image-as-a-texture)
    - [10.6.5 Texture parameters](#1065-texture-parameters)
  - [10.7 Filtering, wrapping and modes（过滤，包裹和模式）](#107-filtering-wrapping-and-modes过滤包裹和模式)
    - [10.7.1 Filtering（过滤）](#1071-filtering过滤)
    - [10.7.2 Wrapping（包裹）](#1072-wrapping包裹)
    - [10.7.3 Mode（模式）](#1073-mode模式)
  - [10.8 Multiple levels of detail – Mipmapping](#108-multiple-levels-of-detail--mipmapping)
  - [10.9 Generating texture co-ordinates](#109-generating-texture-co-ordinates)

# 9.Lighting and Materials（光照和材质）
## 9.1 Background
通过生成透视投影，可以模拟出真实世界中物体的远近和大小关系并应用自然光照效果到可见表面上，可以使渲染的物体呈现出更加真实的外观，从而使渲染的场景呈现出逼真的透视效果。
实现计算机图形学中的Photorealism（照片级逼真度）还需要准确地表示物体表面的材质属性，并且要对光照效果进行物理学描述（例如光线在物体表面的反射、透射和散射，表面纹理以及阴影）。
## 9.2 Lighting sources（光源）
光源像对象一样具有一些数据，例如位置、方向、颜色、形状和reflectivity（反射性）。
描述光源的颜色时，通常会使用RGB颜色模型。对于每个颜色分量，可以分配一个数值来描述该颜色分量的强度或强度。

### 9.2.1 Point light（点光源）
点光源是光照模型中最简单的一种模型，用于模拟物体发出radiant（辐射）能量的光源。点光源通常由三个RGB颜色分量来指定其颜色，这代表了光源发出的单一颜色。
即使光源实际上很大，但如果它与场景中的物体距离不太近，那么可以将其视为点光源。这种简化处理可以使光照模型更加高效，并且在实际渲染中不会对视觉效果产生显著的影响。
点光源发出的光线是沿着radially diverging paths（径向发散路径）产生的，从光源位置向各个方向发散。
### 9.2.2 Directional light（定向光源）
定向光源也被称为infinitely distant light（无限远光源）或directional light（定向光）。这意味着光线是平行的，就好像来自无限远处的光源一样。
实际上的大型光源（比如太阳）离场景非常遥远，也可以近似为点发射器(点光源），因为它们的方向效应变化很小。这意味着即使光源距离很远，其光线的方向效应也几乎没有变化，因此可以简化为点光源的模型。
### 9.2.3 Spot light（聚光灯光源）
一个局部光源可以很容易地被修改，以产生一个spotlight（聚光灯）的光束。
如果一个物体位于光源的方向限制之外，那么它将不会受到该光源的照明。
通过指定一个向量方向和一个角度限制θl（从该向量方向开始测量），以及位置和颜色，可以设置一个聚光灯光源。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/d8451c06c3e54d9092637f7dab47ab98.png)
## 9.3 Surface lighting effects（表面光照效应）
光源发出的是一个频率分布，即光谱。ambient（环境光）、diffuse（漫反射光）和specular（镜面反射光）可能会有不同的频率分布。
例如，如果一个房间里有白色光源，而墙壁是红色的，那么散射的光线往往会呈现红色，尽管直接照射到物体上的光线是白色的。

### 9.3.1 Surface lighting effects：Ambient light（环境光对物体的影响）
环境光是一种一般性的背景非定向照明。每个物体都会使用其固有的强度进行显示，即一种非反射、自发光对象的世界。
因此，除非在创建对象时为其组成部分赋予不同的色调，否则每个对象都会显示为单色轮廓。这意味着在缺乏其他光照效果的情况下，物体将呈现出单色的外观。
环境光的组成部分是来自场景中各种表面反射光的光照效果。当环境光照射到一个表面时，它会均匀地在所有方向上散射。环境光被环境中的表面反射后，光线会被散射得非常均匀，以至于无法确定其具体的方向，看起来就好像来自各个方向一样。
在室内的背光照明中，由于大部分光线都是经过多次反射后才到达眼睛，所以有较大的环境光成分。而在室外的聚光灯照明中，由于大部分光线是沿着同一方向传播的，且在室外环境中很少有光线经过多次反射后到达眼睛，所以环境光成分很小。

### 9.3.2 Surface lighting effects：Diffuse light（漫反射光对物体的影响）
漫反射光是来自于一个方向的光线，因此如果光线垂直照射到表面上，那么表面会更亮，而如果光线斜射到表面上，那么表面会显得更暗。
一旦漫反射光线照射到表面上，它会在所有方向上均匀地散射，因此无论观察者的位置在哪里，漫反射光都会呈现相同的亮度。
任何来自特定位置或方向的光线通常都会有漫反射成分。
粗糙或颗粒状的表面会使反射光均匀地散射到所有方向，这种现象被称为diffuse reflection（漫反射）。
每个物体被认为呈现出一种晦暗、无光泽的表面，而所有物体都受到一个点光源的照明，这个点光源的光线均匀地向各个方向辐射。
影响照明的因素，包括点光源的强度、材料的漫反射系数以及光线的入射角度
### 9.3.3 Surface lighting effects：Specular reflectance（镜面反射光对物体的影响）
镜面反射光是来自于特定方向的光线，并且倾向于以特定方向反射。一个良好整理的激光束在高质量镜子上反射时会产生几乎100%的镜面反射。
具有高镜面反射成分的物体有闪亮的金属、塑料等，而几乎没有镜面反射成分的物体有粉笔、地毯等。
Specularity（镜面反射）可以被视为物体的shininess（光泽度）。
镜面反射效应可以在任何光滑的表面上观察到，而从表面反射出的光线往往具有与光源相同的颜色（例如，白光源反射在红苹果表面上会呈现出白色斑点）。
反射光的强度随着观察方向偏离反射方向而迅速减弱，对于完美的反射体（即完美的镜面），镜面反射光只出现在反射方向上。
影响反射光强度的因素，包括材料的镜面反射系数、观察角度相对于反射方向的角度，以及光源的强度。

### 9.3.4 Surface lighting effects: Illustrated
下图展示了图形学中模拟物体表面对光的反应如下。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/43f6d0b30b6d4b74b984ae95fee68c1b.png)
从左到右，依次是：
1.表面漫反射。
光线以不同角度从表面反射出去，没有特定的方向性。
2.漫反射上的镜面反射。
因此有一组光线以更集中的方向反射，代表镜面反射。
3.来自光源和其他表面的综合照明。
物体不仅受到直接光源的照明，还受到周围环境反射光的影响。

## 9.4 Attenuation（衰减）
关于点光源/位置光源的光线attenuation（衰减）以及距离对光线强度的影响。
对于定向光源，由于它们位于无限远处，因此不需要考虑光线的衰减，因为在距离上进行衰减没有意义。
对于理想光源，光线衰减与距离的平方成反比的关系。但为了增加灵活性，引入了距离衰减模型$f(d)= 1 / {k_c+k_ld+k_qd^2}$，其中包含了常数项、线性项和二次项。而$k_c$，$k_l$和$k_q$是三个浮点数表示这三个项。
## 9.5 Lighting model and shading（光照模型和着色）
### 9.5.1 Lighting model（光照模型）
光照模型（也称为照明或着色模型）用于计算物体表面受光照照射时的颜色。光照模型可以根据物体表面的光学特性（例如透明度、颜色反射系数和纹理参数）来计算表面的光照效果。
光照模型可以应用于每个投影位置，或者通过对表面进行插值来完成表面渲染，从而得到表面的颜色。
Surface rendering method（表面渲染方法）利用光照模型计算出的颜色来确定场景中所有投影位置的像素颜色。

### 9.5.2 Phong model
Phong模型是一种简单且计算速度快的光照模型，用于表面渲染。
其有三部分组成：分别是diffuse（漫反射）、specular（镜面反射）、ambient（环境光）。
使用四个向量：to light source（光源方向向量）$l$、to viewer（观察者方向向量）$v$、face normal（表面法线向量）$n$、perfect reflector（完美反射向量）$r$。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/6e406c824712430482c834ae7b43f4bf.png)
对每个点光源，有9个系数，分别是：
$l_{dr}$,$l_{dg}$,$l_{db}$,漫反射光的RGB颜色分量，$l_{sr}$,$l_{sg}$,$l_{sb}$,镜面反射光的RGB颜色分量，$l_{ar}$,$l_{ag}$,$l_{ab}$,环境光的RGB颜色分量。
材质属性与光源属性相匹配，有9个吸收系数，分别是：
$k_{dr}$,$k_{dg}$,$k_{db}$,漫反射光的吸收系数对应的RGB颜色分量，$k_{sr}$,$k_{sg}$,$k_{sb}$,镜面反射光的吸收系数对应的RGB颜色分量，$k_{ar}$,$k_{ag}$,$k_{ab}$,环境光的吸收系数对应的RGB颜色分量。
还有一个反光度系数$α$。

因此对于每个光源和每个颜色分量，Phong模型可以写成如下形式（不考虑距离项）：$I = k_dI_d  l · n  + k_s I_s (v · r )^α + k_a I_a$。其中$I$是最终颜色。并且对于每个颜色分类，需要将来自所有光源的贡献值相加。

### 9.5.3 Polygonal Shading（多边形着色）
#### 9.5.3.1 Vertex Shading（顶点着色）
在顶点着色中，着色计算是针对每个顶点进行的。这意味着每个顶点都会有自己的颜色，这些颜色会成为顶点的着色值，并且可以作为顶点属性传递给顶点着色器。另一种方法，即将参数传递给顶点着色器，并让它计算着色值。
默认情况下，如果将顶点着色值作为varing variable（可变的变量）传递给片元着色器，那么这些顶点着色值将在整个对象上进行插值，这就是smooth shading（平滑着色）。
我们也可以在整个多边形表面上使用相同的颜色或属性值，而不进行插值计算，这就是flat shading（平面着色）。

#### 9.5.3.2 Flat Shading/Constant shading（平面着色）
如果光照向量（$l$）、视角向量（$v$）和法线向量（$n$）是恒定不变的，那么对于每个多边形只需要进行一次着色计算，然后将得到的着色值分配给多边形上的每个点，而不需要进行插值计算。
多边形网格通常用于建模光滑表面，而flat shading通常会产生失望的效果，因为我们可以看到相邻多边形之间的着色差异。由于每个多边形都被分配相同的着色值，这种着色方式会导致在相邻多边形之间出现明显的着色不连续。如图所示。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/48b62be62bd841138b8a8e66559538d5.png)
#### 9.5.3.3 Smooth Shading/Interpolative shading（平滑着色/插值着色）
Rasteriser（光栅化器）会在多边形内部插值顶点上分配的颜色。
假设在光照计算中，每个顶点都会使用材质属性和顶点处计算得到的法线向量（$n$）、视角向量（$v$）和光源向量（$l$）进行光照计算，从而得到每个顶点的颜色。光栅化器可以使用这些颜色值来插值计算每个fragment（片元）的着色值。
如果光源是遥远的，并且观察者也是遥远的，或者没有镜面反射的话，那么平滑（或插值）着色将会使多边形呈现出恒定颜色。

#### 9.5.3.4 Gouraud Shading
在Gouraud着色中，顶点法线是通过计算网格顶点周围法线的平均值（$n=(n_1+n_2+n_3+n_4)/|n_1+n_2+n_3+n_4|$）来确定的。这些顶点法线用于计算每个顶点处的像素强度，使用任何光照模型来进行计算。
多边形边缘上所有点的强度是通过对顶点值进行加权平均（线性插值）的过程来计算的。
顶点强度值在多边形表面上是线性插值的。

#### 9.5.3.5  Summary
Gouraud着色是一种基于顶点的着色方法，顶点的颜色根据其表面法线和光照模型计算得出，然后在多边形的表面上进行线性插值，以产生平滑的着色效果。
平滑着色是一种基于片元的着色方法，每个片元的颜色是根据其表面法线和光照模型直接计算得出的，而不是通过顶点颜色的插值计算，每个片元处独立计算，从而实现了在多边形表面上的平滑着色效果。

## 9.6 Material（材质）
### 9.6.1 RGB values for lights and materials（光源和材质的RGB值）
光源的颜色分量所代表的含义与材质的颜色分量不同。
对于光源来说，这些数字代表每种颜色的百分比强度。如果光源的R、G和B值都为1.0，那么光源就是最亮的白色。如果R、G和B值为0.5，那么颜色仍然是白色，但只有一半的强度，因此看起来是灰色的。如果R=G=1而B=0（红色和绿色全强度，没有蓝色），那么光源会呈现出黄色。
对于材质来说，RGB值代表了材质对各种颜色光线的反射比例。如果R=1，G=0.5，B=0，那么这个材质会反射所有进入的红光，一半的进入绿光，以及没有进入的蓝光。
假设光源的颜色分量为$(R_L, G_L, B_L)$，而材质的对应颜色分量为$(R_M, G_M, B_M)$，那么忽略其他反射效应的情况下，到达眼睛的光线将由$(R_L*R_M, G_L*G_M, B_L*B_M)$给出。
相似地，当两个光源，分别为$(R_1, G_1, B_1)$和$(R_2, G_2, B_2)$被发送到眼睛时，它们的各个颜色分量会被简单地相加起来，得到$(R_1+R_2, G_1+G_2, B_1+B_2)$。如果相加的结果中有任何一个分量大于1（对应于一种颜色的亮度超过了显示设备能够显示的范围），那么这个分量将clamped(被限制)到1。

### 9.6.2 Material properties（材质属性）
光照模型可以根据反射的红、绿、蓝光的比例来近似材质的颜色。例如，一个完全是红色的球体会反射所有进入的红光，同时吸收所有绿光和蓝光。
当一个红色球体在白光（由相等比例的红、绿、蓝光组成）下被照射时，所有的红光都会被反射，从而我们看到的是红色的球体。同样地，当一个红色球体在纯红光下被观察时，它也会呈现红色。
当一个红色球体在纯绿光下被观察时，它会呈现黑色（因为所有的绿光被吸收，没有红光进入，因此也没有光被反射出来）。
材质和光源一样，也具有ambient（环境）、diffuse（漫反射）和specular（镜面反射）的特性。材质的环境反射会与每个进入的光源的环境光分量相结合，漫反射会与光源的漫反射分量相结合，镜面反射也有类似的处理方式。（这与前一节的公式类似）
环境和漫反射定义了材质的颜色，通常情况下它们是相似甚至相同的。
镜面反射通常是白色或灰色的，这样镜面高光就会成为光源的镜面强度的颜色。举例说明了当白光照射在一个光滑的红色塑料球体上时，大部分球体呈现红色，但是光亮的高光部分会呈现白色。
漫反射在决定我们感知物体颜色方面起着最重要的作用。
环境反射会影响物体的整体颜色。由于环境反射在物体直接受到照明的地方最亮，所以在物体没有直接照明的地方最为显著。物体的总环境反射受到全局环境光和各个光源的环境光的影响。
漫反射和环境反射不受观察点位置的影响。
物体的镜面反射产生了高光效果。与环境反射和漫反射不同，观察者所看到的镜面反射的量取决于观察点的位置。镜面反射最明亮的地方是在直接反射的角度处，这是根据Phong模型得出的结论。
## 9.7 Implementations in OpenGL（在OpenGL中实现）
glLight*()是用于指定光源属性的OpenGL命令，它可以用来设置光源的各种属性，比如颜色、位置、方向。它接受三个参数：
1.光源的标识符，用来指定是哪个光源的属性。
2.光源的属性，比如颜色、位置、方向等。
3.光源属性的期望值，用来指定所设置的属性的具体数值或者向量。

void glLight{if}[v](GLenum light, GLenum pname, TYPEparam)用于创建和设置光源属性。第一个参数指定光源的名字，第二个参数定义要设置的光源特性，TYPEparam参数表示要设置的光源特性的值，如果使用了向量版本，它是一个指向一组数值的指针；如果使用了非向量版本，它就是单个数值。（glLightf用于设置单个浮点数类型的光源属性而glLightfv用于设置一组浮点数类型的光源属性。）
下图展示了第二个参数可以指定的参数。前三种的这四个值分别表示光源的环境光颜色分量的强度，也就是RGBA。而position里的四个值中的前三个表示坐标位置，第四个代表光源的类型，当这个值为0时，表示光源是一个方向光源；当这个值不为0时，表示光源是一个点光源或者聚光灯。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/db251bbbc870403697ca676c5b44b83b.png)
例如设置一个光源0的漫反射白色光源，代码如下：
```cpp
GLfloat lightColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
```

方向光源被视为位于场景无限远处，其光线可以被认为是平行的。
位置光源被视为位于场景中的特定位置，其位置决定了其对场景的影响，光线的方向也会随着位置的变化而变化。例如现实生活中的台灯。
下面的代码给出了一个方向光源，因为其position的w是0：
```cpp
GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};
glLightfv(GL_LIGHT0, GL_POSITION, light_position);
```
当光源位置属性的w值为0.0时，表示对应的光源是一个方向光源，而(x, y, z)的值描述了光线的方向。这个方向会受到模型视图矩阵的变换影响。当光源位置属性的w值不为0时，表示光源是一个位置光源，而(x, y, z)的值指定了光源在齐次对象坐标系中的位置。这个位置会受到模型视图矩阵的变换影响，并且最终以眼坐标系的形式进行存储。
通过更改程序中相对于建模或观察变换设置灯光位置的点，可以实现以下三种效果：1.光源的位置相对于建模或观察变换是固定的。
2.光源相对于物体是移动的，但相对于观察者是固定的。
3.光源位置随着观察者的移动而改变，以保持相对于观察者的位置固定。

### 9.7.1 OpenGL中的聚光灯
聚光灯发出的光线只在锥形范围内有效，超出锥形范围的区域不会受到光照影响。
默认情况下，聚光灯特性是被禁用的，因为GL_SPOT_CUTOFF参数设置为180.0。这意味着光线会在锥形的所有方向发射，相当于没有聚光效果。GL_SPOT_CUTOFF参数的取值范围通常是0.0到90.0之间，除非特别设置为180.0。
下面的代码将聚光灯的cut-off parameter（切断参数）设置为45度，这意味着聚光灯将在一个45度的锥形范围内发光，超出这个范围的区域将不受影响。
```cpp
 glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45.0);
```
与之前描述的距离衰减类似，聚光灯也可以应用距离衰减，使得光线随着距离的增加而减弱。
可以设置GL_SPOT_EXPONENT参数来控制光线的集中度，即聚光灯光线在锥形内的集中程度。
锥体中心的光强度最高。它朝向圆锥体的边缘衰减，衰减程度由光线方向与从光源到被照射顶点的方向之间的夹角的余弦值以指数方式决定。因此，光斑指数越高，光源越聚焦。
与方向光和点光源类似，聚光灯的方向也会受到模型视图矩阵的影响，即聚光灯的方向会被视为一个法向量，并在模型视图矩阵下进行变换。

### 9.7.2 OpenGL中的多光源
在OpenGL场景中，可以使用多达8个光源（在某些OpenGL实现中可能会更多）。
由于OpenGL需要计算确定每个顶点从每个光源接收到的光线量，因此增加光源的数量会对性能产生不利影响。每个光源都需要进行光照计算，因此随着光源数量的增加，计算量也会相应增加，可能会影响渲染性能。
接下来的代码行定义了一个点光源和一个聚光灯：
```cpp
 GLfloat light1_ambient[] = {0.2, 0.2, 0.2, 1.0};
 GLfloat light1_diffuse[] = {1.0, 1.0, 1.0, 1.0};
 GLfloat light1_specular[] = {1.0, 1.0, 1.0, 1.0};
 GLfloat light1_position[] = {-2.0, 2.0, 1.0, 1.0};
 GLfloat spot_direction[] = {-1.0, -1.0, 0.0};
 glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
 glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
 glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
 glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
 glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.5);
 glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5);
 glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.2);
 glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45.0);
 glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
 glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 2.0);
 glEnable(GL_LIGHT1);
 glEnable(GL_LIGHT0);
```

### 9.7.3 OpenGL中的全局环境光
每个光源可以为场景贡献环境光。此外，还可以存在来自任何特定光源的其他环境光。
GL_LIGHT_MODEL_AMBIENT参数用于指定全局环境光的RGBA强度。
```cpp
 GLfloat lmodel_ambient[] = {0.2, 0.2, 0.2, 1.0};
 glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
```
在示例中，lmodel_ambient数组的值是GL_LIGHT_MODEL_AMBIENT的默认值。由于这些数值产生了一小部分白色环境光，即使在场景中没有添加特定的光源，我们仍然可以看到场景中的物体。
### 9.7.4 OpenGL中的本地视点和无限视点
视点的位置会影响镜面反射产生的高光的计算。
更具体地说，特定顶点处的高光强度取决于该顶点处的法线、从顶点到光源的方向以及从顶点到视点的方向。
视点位置不会随着光照命令的调用而实际移动。
本地视点通常会产生更加真实的结果，因为需要为每个顶点计算视点方向，但整体性能会降低。而无限视点则意味着视点与场景中任何顶点之间的方向保持不变，因此需要更少的计算性能。
默认情况下，假定为无限视点。如果需要切换到本地视点，可以使用以下代码：
```cpp
glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
```
这样会将视点放置在(0, 0, 0)位置。如果需要切换回无限视点，则可以传入GL_FALSE作为参数。

### 9.7.5 OpenGL中的双面光照
在光照设置中，通常只针对正面多边形进行光照条件的设置，而背面多边形通常不会被正确照亮。
对于球体这样的对象，通常只有正面会被看到，因为它们是球体的外部表面。因此，背面多边形的外观通常并不重要。
如果球体被切割以使其内部表面可见，那么我们可能希望根据定义的光照条件完全照亮内部表面；此外，我们可能还希望为背面提供不同的材质描述。
### 9.7.6 OpenGL中定义材质属性
大部分材质属性在概念上与用于创建光源的属性类似。
设置材质属性的机制与设置光源属性类似，只是使用的命令是glMaterial*()。例如
```cpp
void glMaterial{if}[v](GLenum face, GLenum pname, TYPEparam)
```
要设置特定的材质属性，需要使用glMaterial*()函数，并通过pname参数来指定要设置的具体材质属性，然后通过TYPEparam参数来指定所需的值。TYPEparam可以是一个指向数值组的指针（如果使用向量版本），也可以是实际的数值（如果使用非向量版本，仅适用于设置GL_SHININESS）。
pname的值如下。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/cb93bc06c9a14dac98b6c9bfc84bbab0.png)
注意GL_AMBIENT_AND_DIFFUSE选项允许同时设置环境光和漫反射材质颜色为相同的RGBA值。
通过为GL_EMISSION指定RGBA颜色，可以使对象看起来好像散发出该颜色的光。这个特性可以用来模拟场景中的灯和其他光源对象。
face参数可以取GL_FRONT、GL_BACK或GL_FRONT_AND_BACK，用于指示应用材质的对象的哪一面。
可以选择对物体的正面和背面多边形进行不同的光照计算。如果背面可能被看到，可以通过glMaterial*()函数的face参数为正面和背面表面提供不同的材质属性，从而影响它们在光照条件下的外观。
大部分由glMaterial*()设置的材质属性都是RGBA颜色。无论其他参数提供了怎样的alpha值，任何特定顶点的alpha值都是漫反射材质的alpha值，也就是使用glMaterial*()函数中GL_DIFFUSE指定的alpha值。
RGBA材质属性在颜色索引模式（指的是GL_COLOR_INDEXES）下不适用。

# 10. Texture Mapping（纹理贴图）
## 10.1 Concepts of texture mapping（纹理贴图的概念）
尽管图形卡可以每秒渲染超过1000万个多边形，但这可能仍然不足，或者可能存在其他处理现象的替代方法，比如云、草地、地形和皮肤等。
为了给物体增加细节，一种常见的方法是将图案映射到物体的几何描述上。将对象的细节纳入场景的方法称为纹理映射或图案映射。
纹理映射的难点在于，一个矩形纹理可能需要映射到非矩形的区域，而且这必须以合理的方式进行。
当纹理被映射时，由于应用了各种变换（旋转、平移、缩放和投影），它在屏幕上的显示可能会发生扭曲。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/0674bb2b603f4ca09e7875d569b2ac40.png)

## 10.2 Types of texture mapping（纹理映射的类型）
Texture Mapping（纹理映射）：使用图像来填充多边形的内部，以增加多边形表面的细节和真实感。
Environment Mapping（环境映射）：使用环境的图片作为纹理映射，可以模拟高度镜面反射的表面，从而使物体看起来更真实。
Bump Mapping（凹凸映射）：在渲染过程中模拟改变法向量的技术，通过对法向量进行微小的调整，来模拟物体表面的凹凸不平，从而增加物体的细节和真实感。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/aa92c5dd80ef436bb6a5ad7b04dad93d.png)

## 10.3 Specifying the texture（指定纹理）
常见纹理类型：1.Image Texture（图像纹理）：使用2D图像作为纹理。
2.Procedural Texture（过程纹理）：使用过程或程序生成纹理，而不是依赖于预先制作的图像。（实时渲染通常是过程纹理）
纹理可以是一维、二维或三维的图案。
纹理函数通常允许在模式中的每个位置指定颜色组件的数量。例如，每个颜色定义可以由四个RGBA组件、三个RGB组件、单一强度值（用于蓝色的阴影）、颜色表中的索引，或者单一亮度值（颜色的RGB组件的加权平均）组成。
纹理数组中的各个值通常被称为纹素（texels，texture elements），它们是构成纹理的基本元素。
其中纹素（texels，texture elements）指的是纹理图像中的最小单元，类似于像素（pixels）是图像中的最小单元一样它们代表了纹理图像中的各个点的颜色和属性。
## 10.4 Magnification and minification （放大和缩小）
Magnification（放大）：当一个texel（纹素）被映射到多个像素时，称为放大。这通常发生在纹理图像的尺寸比映射到的几何形状的尺寸小的情况下，需要将一个纹素的颜色值映射到多个像素上，这可能会导致纹理图像在屏幕上出现模糊或失真的情况。
Minification（缩小）：当一个像素被多个texels（纹素）所覆盖时，称为缩小。这通常发生在纹理图像的尺寸比映射到的几何形状的尺寸大的情况下，多个纹素的颜色值被映射到同一个像素上，这可能会导致纹理图像在屏幕上出现失真或细节丢失的情况。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/55312f4a6aad4880be671dbdc6cc479a.png)
由于纹理是由离散的texels（纹素）组成的，因此需要进行filtering（滤波）操作来将纹素映射到像素上。例如，如果多个纹素对应一个像素，它们会被平均处理以适应像素的大小；如果纹素边界跨越像素边界，那么适用纹素的加权平均值将被计算并映射到像素上。
由于这些复杂的计算，纹理映射可能需要大量的计算资源，因此许多专门的图形系统都包含了针对纹理映射的硬件支持，以提高效率并降低计算成本。

纹理映射技术通常是在渲染管线的最后阶段实现的。在渲染管线中，几何数据经过顶点着色器、裁剪器等处理后，最终的图元数量会变得相对较少。因此，当渲染到达纹理映射阶段时，需要处理的图元数量相对较小，这使得纹理映射的效率相对较高。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/d8dc734921374367a58d6592da531f4c.png)

## 10.5 Two-step mapping
尽管纹理映射的概念看似简单，即将一幅图像映射到一个表面上，但实际上涉及到了3或4个坐标系统的转换和映射。
涉及到的系统有：
Parametric co-ordinates（参数坐标系）：用于建模曲线和曲面的坐标系。
Texture co-ordinates（纹理坐标系）：用于标识纹理图像中要映射的点的坐标系。
Object or world coordinates（物体或世界坐标系）：概念上，纹理映射发生的地方。
Window co-ordinates（窗口坐标系）：最终生成最终图像的坐标系。（或者说是屏幕上像素的位置）![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/bf28d7adf54a4a489663492e7d881114.png)
在纹理映射中，基本问题是如何找到纹理坐标到表面上点的映射关系。考虑从纹理坐标到表面上点的映射，通常需要三个函数来描述这个过程，即 $x = x(s, t),y = y(s, t),z = z(s, t)$。然而，实际上我们更关心的是如何从表面上的点反向映射到纹理坐标。这意味着我们需要找到一个反向的映射关系，从表面上点的空间位置到纹理坐标(s, t)。
在纹理映射中，我们希望能够进行反向映射，即根据屏幕上的像素确定它对应于物体上的哪个点，或者根据物体上的点确定它对应于纹理上的哪个点。为了实现这样的反向映射，我们需要形式$s = s(x, y, z)$ 和 $t = t(x, y, z)$的映射。然而，这样的函数在一般情况下是很难找到的。

### 10.5.1 Two-part mapping（两部分映射）
复杂的表面映射问题分解为两个较简单的映射问题。在这里，首先将纹理映射到一个简单的中间形状，比如圆柱体，这个形状可能比原始的物体表面简单得多。然后，再将这个中间形状映射到实际的物体表面上，这样就将原始的复杂映射问题分解为两个较简单的映射问题。
例如，将纹理映射到圆柱体上，再到最终物体上。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/55b5df60c6df4950b575e24045e82965.png)
#### 10.5.1.1 Cylindrical mapping（圆柱体映射）
通过参数化的圆柱体公式$x = r*cos(2pi*u),y = r*sin(2pi*u),z = h*v$，可以将 (u, v) 空间中的一个矩形映射到世界坐标系中的一个半径为 $r$、高度为 $h$ 的圆柱体表面上。其中，$u$ 和 $v$是矩形在 $(u, v)$ 空间中的坐标，$r$是圆柱体的半径，$h$是圆柱体的高度。
$s = u$和$t = v$表示将纹理空间中的坐标直接映射到圆柱体表面上，即使用$(u, v)$空间中的坐标作为纹理坐标，从而实现了从纹理空间到圆柱体表面的映射。
#### 10.5.1.2 Spherical mapping（球体映射）
参数化的球体公式$x = r*cos(2pi*u)、y = r*sin(2pi*u)*cos(2pi*v)、z = r*sin(2pi*u)sin(2pi*v)$，可以将 (u, v) 空间中的一个区域映射到球体表面上。其中，$u$和$v$是球面上的参数，$r$是球体的半径。
类似于圆柱体映射，球形映射也将 $(u, v)$空间中的坐标直接映射到球体表面上，从而实现了从纹理空间到球体表面的映射。然而因为球体的表面是曲面，而纹理空间是平面，所以在将平面上的纹理映射到球体表面时，可能会出现一定程度的distortion（形变）。因此，在球形映射中，需要决定在球体表面上的哪些区域放置畸变，以最小化形变并实现有效的纹理映射。
球体映射通常用于环境贴图。

#### 10.5.1.3 Box mapping（盒状映射）
盒状映射是一种简单的纹理映射方法，通过使用简单的正交投影将纹理映射到立方体或长方体的表面上。
它也可以用于环境贴图。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/81c8379d19574066871481503eef4b9b.png)
### 10.5.2 Second mapping
将中间对象上的纹理或者属性映射到最终的目标空间上的过程。
该过程包括：
从中间对象到实际对象的法线映射，以确保在渲染过程中正确地处理光照和阴影。
从实际对象到中间对象的法线映射，以便在纹理编辑或者其他处理过程中正确地处理法线贴图等属性。
从中间对象的中心点到实际对象的向量映射，以便在渲染或者动画过程中正确地处理对象的位置或者运动。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/85074b139765422aa6ab21f651b9fdbe.png)
#### 10.5.2.1 Aliasing（失真）
对纹理进行点采样可能会导致图像中出现锯齿状或者失真的错误。这是因为点采样在纹理空间（通常是 u,v 或者 x,y,z 空间）中进行，而且也可能在纹理空间中进行点采样。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/e49d1f7353154767b7c8b373e0cd238f.png)

#### 10.5.2.2 Area averaging
这是一种更高级的纹理采样技术，可以用于减少图像或纹理中出现的锯齿状或失真效果。在这种技术中，对于每个像素，会考虑其周围区域内的纹理值，然后对这些值进行平均，以获得更平滑和连续的图像效果。
由于像素的预像（pre-image）是曲线状的，因此需要特别注意处理曲线状的像素的情况。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/7525c678b1464af38358a48bd0803c71.png)

## 10.6 Steps in texture mapping and OpenGL functions
进行纹理映射的三个主要步骤是：
1.指定纹理：
读取或生成图像
将图像分配给纹理
启用纹理
2.为顶点分配纹理坐标：
适当的映射函数由应用程序完成
3.指定纹理参数：
Mode（模式）指定纹理如何与物体表面上的颜色进行混合。
Filtering（过滤）指定纹理的过滤方式。
Wrapping（包裹）用于控制纹理坐标超出范围时的处理方式。

### 10.6.1 OpenGL functions
glTexImage2D(): 用于定义图像作为纹理。参数包括（type，level，colour等）。
glTexParameter*(): 用于指定纹理的过滤和包裹方式。
glTexEnv{fi}[v](): 用于指定纹理的模式（包括modulating（调制）、blending（混合）或decal（贴图））。
glTexCoord{1234}{sifd}{v}(): 用于指定纹理坐标。{1234}: 表示可以选择使用1、2、3或4个纹理坐标来指定顶点的纹理坐标。通常情况下，2D纹理使用2个坐标(s和t)，3D纹理使用3个坐标(s、t和r)，4D纹理使用4个坐标(s、t、r和q)。{v}: 表示指定纹理坐标的方式，v表示使用向量指定。在2D纹理中，通常只需要指定s和t坐标，而r坐标通常被设置为0，q坐标通常被设置为1。
{sifd}: 表示指定纹理坐标的数据类型，s表示单精度浮点数，i表示整数，f表示浮点数，d表示双精度浮点数。
glTexGen{ifd}[v](): 用于由OpenGL自动生成纹理坐标。
glHint(): 用于定义透视矫正提示。
glBindTexture(): 用于将命名纹理绑定到纹理目标上。

### 10.6.2 Texture mapping and the OpenGL pipeline
图像和几何图形经过各自独立的管线处理，然后在片元处理阶段合并。
“复杂”的纹理不会影响几何复杂性。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/6ec7fe00db8e48ae854519728e570f1d.png)

### 10.6.3 Specifying a texture image
从CPU内存中的纹理元素数组中定义纹理图像：
通过定义一个包含纹理元素（texels）的数组，可以在CPU内存中创建纹理图像的数据结构。例如，GLubyte my_texels[512][512][4] 表示一个512x512的纹理图像，每个像素由4个字节组成。
将纹理定义为任何其他像素映射：
可以将纹理定义为扫描图像或由应用程序生成的像素图。
启用纹理映射：
通过调用 glEnable(GL_TEXTURE_2D)，可以启用2D纹理映射功能。
OpenGL支持1到4维的纹理映射。
如图：
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/0aa5828214644cfb86412e4dbd6e128e.png)
### 10.6.4 Defining image as a texture
glTexImage2D(target, level, components, w, h, border, format, type, texels)用于定义图像作为纹理的函数。其中
target: 纹理的类型，例如 GL_TEXTURE_2D 表示2D纹理。
level: 用于纹理的mipmapping（多级纹理映射）的级别。当设置为0时，表示只使用最高分辨率的纹理，后续的级别将在后续讨论中进行。
components: 每个纹理元素中的颜色元素数量，取值范围为1到4，表示选择R、G、B和A分量中的哪些进行调制或混合。取值为1表示选择R分量，2表示选择R和A分量，3表示选择R、G和B分量，4表示选择R、G、B和A分量。
w和h分别表示图像的宽度和高度，单位为像素。
border 是用于平滑处理的参数，通常情况下取值为0。后续会进行讨论。
w 和 h 必须满足形式为 $2^m + 2^b$，其中 m 是整数，b 是 border 的值，尽管它们可以有不同的值。
纹理图像的最大尺寸取决于OpenGL的实现，但至少必须为64×64（或者带有borders的66×66）。
format 和 type 参数用于描述纹理图像数据的格式和数据类型。它们与 glDrawPixels() 函数具有相同的含义。实际上，纹理数据的格式与 glDrawPixels() 使用的数据格式相同。
format 参数可以取值为 GL_COLOR_INDEX, GL_RGB, GL_RGBA, GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA, GL_LUMINANCE, 或 GL_LUMINANCE_ALPHA。这些取值与 glDrawPixels() 中可用的格式相同，但不包括 GL_STENCIL_INDEX 和 GL_DEPTH_COMPONENT。
类似地，type 参数可以取值为 GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT, GL_UNSIGNED_INT, GL_FLOAT, 或 GL_BITMAP。
texels 是指向包含纹理图像数据的纹素数组的指针。这些数据描述了纹理图像本身以及它的border。
使用的例子如下：
```cpp
glTexImage2D(GL_TEXTURE_2D, 0, 3, 514, 514, 1, GL_RGB, GL_UNSIGNED_BYTE, my_texels);
```
表示创建一个二维纹理，颜色分量为3（即RGB），宽度为514，高度为514，边框宽度为1，纹理数据以RGB格式和无符号字节类型存储，纹理数据存储在my_texels数组中。
### 10.6.5 Texture parameters
确定纹理应用方式的各种参数：
Filter modes（过滤模式）：允许我们使用area averaging（区域平均）而不是point samples（点采样）。
Wrapping parameters（包裹参数）：定义了当纹理坐标 s 和 t 超出 [0,1] 范围时会发生什么。
Mode/environment parameters（模式/环境参数）：定义了纹理映射如何与着色交互。
Mipmapping（多级纹理处理）：允许我们使用多个分辨率（不同层次的细节）的纹理，从而在不同距离和角度下获得更好的纹理效果。
## 10.7 Filtering, wrapping and modes（过滤，包裹和模式）
### 10.7.1 Filtering（过滤）
允许我们指定多种过滤选项，以确定纹理采样的计算方式。这些选项在速度和图像质量之间提供不同的权衡。
我们可以独立地为放大和缩小指定过滤方法。
OpenGL可以在放大和缩小之间做出选择，以获得可能的最佳结果。
下面的例子中使用 glTexParameter*()来指定放大和缩小的纹理过滤方法：
```cpp
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
```
第二个参数可以是 GL_TEXTURE_MAG_FILTER 或GL_TEXTURE_MIN_FILTER，用于指示我们是在指定放大还是缩小的过滤方法。
第三个参数指定了具体的过滤方法，例如 GL_NEAREST 或 GL_LINEAR。
关于线性过滤的注意事项：线性过滤需要额外的纹素边框来进行边缘处的过滤处理（border = 1）。

### 10.7.2 Wrapping（包裹）
我们可以分配纹理坐标超出范围[0,1]，并在纹理映射中选择对其进行clamp（夹取）或repeat（重复）的处理方式。
当使用重复纹理时，例如在一个大平面上，纹理坐标从0.0到10.0延伸，我们会在屏幕上得到100个纹理的拼贴。在重复过程中，纹理坐标的整数部分被忽略，从而在表面上复制纹理图案。对于大多数重复纹理的应用，纹理的顶部应该与底部的纹素匹配，左右边缘也应该类似。

夹取纹理坐标的处理方式是：任何大于1.0的值都被设为1.0，任何小于0.0的值都被设为0.0。
夹取在需要在大表面上显示单个纹理的情况下非常有用。如果表面的纹理坐标范围从0.0到10.0，那么纹理的一个拷贝将出现在表面的一个角落。其余的表面将根据需要用纹理边界颜色来填充。

夹取：对于超出范围的纹理坐标，将其限制在0到1之间，大于1的值设为1，小于0的值设为0。
重复：对于超出范围的纹理坐标，使用取模运算将其限制在0到1之间。
两者的区别这里用一个例子去说明：
```cpp
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP)；
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT)；
```
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/c01eb84e5c6c468591002108624cf02d.png)
### 10.7.3 Mode（模式）
通过glTexEnv{fi}[v](GL_TEXTURE_ENV, prop, param)函数，可以控制纹理的应用方式。
GL_TEXTURE_ENV_MODE 模式：
GL_REPLACE：只使用纹理颜色。
GL_MODULATE：与计算出的阴影进行调制。
GL_BLEND：与环境颜色进行混合。
使用GL_TEXTURE_ENV_COLOR设置混合颜色。

通过提供适当的参数给glTexEnv{if}{v}(GLenum target, GLenum pname, TYPEparam)函数，可以选择以下三种方式来计算最终的RGBA值：
1.直接使用纹理颜色作为最终颜色，称为decal模式，即纹理被直接贴在片元上，就像贴纸一样。
2.使用纹理来调制或缩放片元颜色，有助于将光照效果与纹理效果相结合。
3.基于纹理值，将一个常量颜色与片元颜色进行混合。
其中 target 必须是GL_TEXTURE_ENV。如果 pname 是 GL_TEXTURE_ENV_MODE，TYPEparam 可以是GL_DECAL, 
GL_MODULATE, 或 GL_BLEND以指定纹理值如何与正在处理的片段的颜色值组合。在decal模式和三组分纹理中，纹理颜色会取代碎片颜色。在其他两种模式下或使用四分量纹理时，最终颜色是纹理值和片元值的组合。如果 pname 是GL_TEXTURE_ENV_COLOR，TYPEparam指定一个包含四个浮点值的数组，表示R、G、B和A分量。这些值仅在指定了GL_BLEND纹理函数时才会被使用。

## 10.8 Multiple levels of detail – Mipmapping
纹理对象在场景中的不同距离下会呈现不同的大小。当纹理对象从视点远离时，投影图像的大小会随之减小。
为了实现这一点，OpenGL需要对纹理图像进行滤波，以便将其缩小到适当的大小，以便映射到对象上，而不引入视觉上的干扰。
为了避免这种干扰，可以提前生成一系列预先经过滤波的纹理图像，分辨率逐渐减小，称为Mipmaps。这些Mipmaps可以在纹理被远离时使用，以保持视觉上的连续性和质量。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/ee2ef352f1a744bc8285f91cb14b45c5.png)
OpenGL会根据被映射对象的大小（以像素为单位）自动确定使用哪个级别的Mipmap纹理图像。
这种方法可以确保纹理图像的细节级别适合在屏幕上绘制的图像，随着对象图像变小，纹理图像的大小也会相应减小。
Mipmapping需要一些额外的计算来减少插值误差，但如果不使用Mipmapping，那么被映射到较小对象上的纹理可能会在对象移动时出现闪烁和闪烁。
为了使用Mipmapping，我们需要在最大尺寸和1×1尺寸之间提供所有2的幂次方大小的纹理。
举例来说，如果最高分辨率的纹理是64×16，那么我们还必须提供尺寸为32×8、16×4、8×2、4×1、2×1和1×1的纹理。
较小尺寸的纹理通常是经过滤波和平均处理的最大尺寸纹理的版本，其中较小纹理中的每个texe（纹素）l是对应较大纹理中四个texel（纹素）的平均值。
OpenGL不要求对较小尺寸纹理采用特定的计算方法，因此不同尺寸的纹理可以是完全不相关的。
在纹理定义过程中，通过调用glTexImage2D(GL_TEXTURE_*D, level, …)来声明Mipmap级别，每个纹理分辨率需要调用一次该函数，level参数会不同，同时还需要提供不同的宽度、高度和图像参数。
从零开始，level参数用于标识系列中指定的纹理，根据前面的例子，尺寸为64×16的最大纹理将使用level = 0声明，尺寸为32×8的纹理将使用level = 1声明，依此类推。
此外，为了使Mipmapped纹理生效，需要选择适当的过滤方法。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/087c874b8c174aedaef1cc915e1efd15.png)
Point Sampling（点采样）：
这是一种最简单的纹理过滤技术，其中每个像素直接从纹理中获取一个 texel（纹理元素）的值。这种方法在纹理被放大时会导致明显的像素化。

Linear Filtering（线性过滤）：
线性过滤是一种改进的纹理过滤技术，它通过取一个像素周围四个 texels 的平均值来计算该像素的颜色。这种方法可以减少像素化，但在纹理被缩小时仍然可能出现混叠。

Mipmapped Point Sampling（Mipmapped 点采样）：
在 mipmapping 中使用点采样，系统会根据像素与纹理的距离选择最合适的 mip level。这种方法在纹理被缩小时可以减少混叠，但在纹理被放大时仍然可能出现像素化。

Mipmapped Linear Filtering（Mipmapped 线性过滤）：
这是 mipmapping 与线性过滤的结合。系统不仅会选择最合适的 mip level，还会在选定的 mip level 内使用线性过滤来计算像素颜色。这种方法在纹理被放大或缩小时都能提供较好的视觉效果。

## 10.9 Generating texture co-ordinates
纹理坐标通常用s、t、r和q坐标来表示，以区分它们与物体坐标（x、y、z和w）的区别。对于2D纹理，通常使用s和t坐标。目前，r坐标被忽略（尽管它将来可能会有意义）。q坐标（类似于w）通常赋值为1，可用于创建齐次坐标。
我们需要指示纹理相对于要应用的片段应该如何对齐。我们可以像指定场景中的对象一样指定纹理坐标和几何坐标。
用于指定纹理坐标的命令glTexCoord*()类似于glVertex*()、glColor*()和glNormal*()。 它有类似的变体，并在glBegin()和glEnd()对之间的使用方式相同。
通常情况下，纹理坐标的取值范围在0到1之间。
void glTexCoord{1234}{sifd}[v](TYPE coords)函数用于设置当前的纹理坐标(s, t, r, q)。
后续调用glVertex*()函数将使这些顶点被赋予当前的纹理坐标。
使用glTexCoord2*()允许我们指定s和t；r和q分别被设置为0和1。我们可以分别提供坐标，或者使用向量版本的命令将它们提供为单个数组。在进行任何纹理映射之前，纹理坐标会被4x4纹理矩阵所乘。
在基于参数的纹理坐标系统中，我们需要在每个顶点处使用glTexCoord*()函数指定纹理坐标。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/e64390e9f93c46ec88181c8ffa2465d3.png)
OpenGL使用插值来处理纹理坐标，这意味着在纹理映射过程中，系统会自动计算并插入纹理坐标之间的中间值，以确保纹理在几何图形上的平滑映射。然而，由于插值的特性，有时候可能会出现纹理坐标的扭曲或失真。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/3822543153464ed19eefc5f5be2d3303.png)
OpenGL可以自动生成纹理坐标，通过glTexGen{ifd}[v](GLenum coord, GLenum pname, GLint param)函数。
通过指定一个平面，OpenGL可以根据距离平面的远近来生成纹理坐标。
参数coord可以是GL_S、GL_T、GL_R或GL_Q，用于指定需要生成纹理坐标的坐标轴。
参数pname表示生成模式，可以是GL_OBJECT_LINEAR（对象线性）、GL_EYE_LINEAR（视线性）或GL_SPHERE_MAP（用于环境贴图）。

在进行纹理坐标和颜色插值时，可以选择在屏幕空间中线性插值，或者使用深度/透视值进行插值（速度较慢），通过使用glHint(GL_PERSPECTIVE_CORRECTION_HINT, hint)函数，可以设置透视校正的提示类型，其中hint可以是GL_DONT_CARE、GL_NICEST或GL_FASTEST。
GL_DONT_CARE：表示对透视校正方式不做特别的优化。
GL_NICEST：表示使用最高质量的透视校正方式。
GL_FASTEST：表示使用最快速的透视校正方式。





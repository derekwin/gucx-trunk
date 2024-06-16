# gucx-trunk

按照ucx的思路设计成模块的形式
在api中涉及gcuxt的基础结构
选择编译对应计算库的模块时候，将interface注册到全局结构上。【ucx是注册到了数组里，实现了模块添加，这里实现为替换】
设置相应的判断函数，判断库接口函数是否正常。
1. 设置init函数，初始化驱动接口，此时就需要判断接口函数是否正常。
2. 


```
autoreconf -i

bash clean-autogen.sh

./configure --prefix=/home/liujinyao/proj/gucx-trunk-install --with-cncl=/usr/local/neuware

make -j64 install
```
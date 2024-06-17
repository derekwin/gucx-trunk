# gucx-trunk

```
autoreconf -i

bash clean-autogen.sh

./configure --prefix=/home/liujinyao/proj/gucx-trunk-install --with-cncl=/usr/local/neuware

source /opt/dtk/env.sh
./configure --prefix=/home/sdu/proj/gucx-trunk-install --with-rocm=/opt/dtk

./configure --prefix=/home/liujinyao/proj/gucx-trunk-install --with-cuda=/usr/local/cuda

make -j64 install
```
#Загрузить образ убунту 18.04
FROM ubuntu:18.04

# Установим обновления
RUN apt-get update

#Для сборки кликхауса понадобиться компилятор gcc9
RUN apt install software-properties-common
RUN add-apt-repository ppa:ubuntu-toolchain-r/test
RUN apt install gcc-9 g++-9
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-9 90 --slave /usr/bin/g++ g++ /usr/bin/g++-9

#Скопируем необходисые файлы исходники для сборки Кликхаус
RUN apt install git
RUN git clone https://github.com/artpaul/clickhouse-cpp.git

#Выполняем сборку Кликхауса из исходников
RUN mkdir build
RUN cd build
RUN cmake ../clickhouse-cpp
RUN make

#Откасимся назад
RUN cd~

#Установим qt
RUN apt-get install qt5-default
RUN apt-get install qtcreator
RUN apt install qtbase5-examples qtdeclarative5-examples

#Установим необходимые дополнительные модули
RUN apt-get install -y qtbase5-dev
RUN apt-get install -y qtdeclarative5-dev
RUN apt-get install -y libqt5charts5-dev
RUN apt-get install -y qml-module-qtcharts
RUN apt-get install -y qml-module-qtquick-controls2
RUN apt-get install -y qml-module-qtquick-controls
RUN apt-get install -y qml-module-qt-labs-settings

#Скопируем файлы исходного кода нашей программы
RUN git clone https://github.com/SLAVIK555/CHproject.git

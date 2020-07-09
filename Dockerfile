#Загрузить образ убунту 18.04
FROM ubuntu:18.04

# Установим обновления
RUN apt-get update

#add https support
RUN apt -y install apt-transport-https

# Установим gcc-9 and g++-9
RUN apt -y install build-essential
RUN apt -y install software-properties-common
RUN add-apt-repository ppa:ubuntu-toolchain-r/test
RUN apt-get -y install gcc-9 g++-9
RUN update-alternatives —install /usr/bin/gcc gcc /usr/bin/gcc-9 90 —slave /usr/bin/g++ g++ /usr/bin/g++-9

#git and cmake and python
RUN apt -y install git
RUN apt -y install cmake
RUN apt -y install python3-pip

#clone clickhouse
RUN mkdir newclickhouse
RUN cd newclickhouse
RUN git clone https://github.com/artpaul/clickhouse-cpp.git

#make clickhouse
RUN mkdir build
RUN cd build && cmake ../ch/clickhouse-cpp && make

#install python clickhouse-driver
RUN pip3 install clickhouse-driver[lz4]

#qt5
RUN apt -y install qt5-default
RUN apt -y install qtcreator

#Установим необходимые дополнительные модули
#RUN apt-get install -y qtbase5-dev
#RUN apt-get install -y qtdeclarative5-dev
#RUN apt-get install -y libqt5charts5-dev
#RUN apt-get install -y qml-module-qtcharts
#RUN apt-get install -y qml-module-qtquick-controls2
#RUN apt-get install -y qml-module-qtquick-controls
#RUN apt-get install -y qml-module-qt-labs-settings
#QCharts идет лесом, так как отрисовка графика в реальном времени в QCustomPlot удобнее

#Установим clickhouse-server и clickhouse-client
RUN apt-get install -y git cmake python ninja-build
RUN git clone --recursive https://github.com/ClickHouse/ClickHouse.git
RUN cd ClickHouse
RUN mkdir build
RUN cd build
RUN cmake ..
RUN ninja
RUN cd ..

#Запустим сервер и клиент кликхауса
RUN service clickhouse-server start
RUN clickhouse-client

#Скопируем файлы исходного кода нашей программы
RUN mkdir newclickhouse
RUN cd newclickhouse && git clone https://github.com/SLAVIK555/QCPtest.git

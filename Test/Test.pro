include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

QMAKE_CXXFLAGS_DEBUG *= -O0
QMAKE_CXXFLAGS += -O3
QMAKE_CXXFLAGS += -Werror -Wvla -Wall

INCLUDEPATH += $$PWD/../ModbusMaster

HEADERS += \
    ../ModbusMaster/FrameLayer.hpp \
    ../ModbusMaster/ModbusMaster.hpp \
    ../ModbusMaster/IDataLink.hpp \
    ../ModbusMaster/FrameRouter.hpp \
    ../ModbusMaster/RequestModel.hpp \
    ../ModbusMaster/Strategies/ReadRegistersStrategy.hpp \
    ../ModbusMaster/Framework/TransmitBase.hpp \    
    ../ModbusMaster/Framework/IReceive.hpp \
    ../ModbusMaster/Framework/FunctionCode.hpp \    
    ../ModbusMaster/Framework/ParameterType.hpp \    
    ../ModbusMaster/Strategies/IStrategy.hpp \
    ../ModbusMaster/Framework/Frame/IFrame.hpp \
    ../ModbusMaster/Framework/Frame/ReadRegistersFrame.hpp \
    ../ModbusMaster/Framework/Frame/FrameHeader.hpp \
    ../ModbusMaster/Framework/Frame/FrameRequestModel.hpp \
    ../ModbusMaster/Framework/IServiceable.hpp \
    ../ModbusMaster/Framework/Tick_t.hpp \
    ../ModbusMaster/Framework/IServiceable.hpp \
    ../ModbusMaster/IReadRegistersCallback.hpp \
    ../ModbusMaster/Framework/Frame/FrameContent.hpp

SOURCES += \
    main.cpp \    
    ../ModbusMaster/ModbusMaster.cpp \
    ../ModbusMaster/FrameRouter.cpp \
    ../ModbusMaster/RequestModel.cpp \
    ../ModbusMaster/FrameLayer.cpp \
    ../ModbusMaster/Strategies/ReadRegistersStrategy.cpp \    
    Test_Framework_TransmitReceive.cpp \    
    Test_FrameRouter.cpp \
    ../ModbusMaster/Framework/Frame/ReadRegistersFrame.cpp \
    Test_ReadRegistersStrategy.cpp \
    ../ModbusMaster/Framework/Frame/FrameHeader.cpp \
    ../ModbusMaster/Framework/Frame/FrameRequestModel.cpp \
    Test_IntegrationTest.cpp \
    ../ModbusMaster/Framework/Frame/FrameContent.cpp

# ModbusMaster
One Modbus Master implementation to rule them all!  

# Thoughts
### Register VS Parameter
I imagine a parameter as an abstraction from one or more modbus registers.  
A parameter is that you access and use from the application code, where the underlying registers is what is read and written on the protocol.  
Practically a parameter will simply consist of a modbus start address and a length.  

# Diagram
Simple diagram which shows my initial thoughts.  
Not really UML, not really a flow chard, not really a sequence diagram.  Just my thoughts through an UML tool.  
Can be edited with https://draw.io

# Initial specification notes
* ModbusMaster must support following modbus functions codes.
  * Read Input Registers (4)
  * Read Holding Registers (3)
  * Write Single Register (6)
  * Write Multiple Registers (10)

* ModbusMaster must be designed in a way that makes it easy to add further function codes.

* ModbusMaster shall not be specifc to any hardware.

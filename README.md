# ModbusMaster
One Modbus Master implementation to rule them all!  

# Thoughts
This design will give some issues when reading the response.  
As the frames are very specific to their functioncode, the framelayer cannot handle the parsing alone..

### Register VS Parameter
I imagine a parameter as an abstraction from one or more modbus registers.
A parameter is that you access and use from the application code, where the underlying registers is what is read and written on the protocol.
Practically a parameter will simply consist of a modbus start address and a length.

A parameter will ofcourse only contain consecutive registers, and registers of the the type (type as in holding/input).

### Types
Now that i am trying to abstract the function codes a little, maybe i could come up with a more abstracted name for holding and input..

### Framework
The idea of this folder, is that modules in there will be reuseable for my upcoming slave implementation.
Maybe I should just name it common right away?

### Performance
Is it too expensice to pass values around as std::vector?

# Diagram
Simple diagram which shows my initial thoughts.  
Not really UML, not really a flow chard, not really a sequence diagram.  Just my thoughts through an UML tool.  
Can be edited with https://draw.io

# Initial specification notes
* ModbusMaster must support following modbus functions codes.
  * Read Input Registers (4)
  * Read Holding Registers (3)
  * Write Single Register (6) (Do we really need this one?)
  * Write Multiple Registers (10)

* ModbusMaster must be designed in a way that makes it easy to add further function codes.

* ModbusMaster shall not be specifc to any hardware.

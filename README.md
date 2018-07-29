# ModbusMaster
One Modbus Master implementation to rule them all!  

# Thoughts / Notes / TBD  
* More expressive errors than true/false !!
* Add IsBusy to public interface.  
* Is it too unsafe to just expect that the data received in a strategy corresponds to the ones sent?
* Fix all the 'tbd' added in code.  

### Framework
The idea of this folder, is that modules in there will be reuseable for my upcoming slave implementation.
Maybe I should just name it common right away?

### Performance
Is it too expensive to pass values around as std::vector?

# Diagram
Simple diagram which shows my initial thoughts.  
Not really UML, not really a flow chart, not really a sequence diagram.  Just my thoughts through an UML tool.  
Can be edited with https://draw.io

# Initial specification notes
* ModbusMaster must support following modbus functions codes.
  * Read Input Registers (4)
  * Read Holding Registers (3)
  * Write Single Register (6) (Do we really need this one?)
  * Write Multiple Registers (10)

* ModbusMaster must be designed in a way that makes it easy to implement further function codes.

* ModbusMaster shall not be specifc to any hardware.

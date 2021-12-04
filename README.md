# sensor-data-collection

* [getSensorData](https://github.com/ramonayag/sensor-data-collection/blob/main/getSensorData.ino)
  * Getting data from multiple sensors to determine best sensor to detect nearby movement, specifically falling 

Testing 
* Check proper connection of components and sensors 
* Connect Arduino Nano to computer via USB 
* Upload **getSensorData.ino** to Nano 
* In terminal cd to location of read-serial.py
* Run script **read-serial.py**  
** >> python3 read-serial.py
* Data for activity will be under {activity_name}DataOG.csv 

Data Preprocesssing:  
1. **dataVV_Automated.R**  
* Clean data from "{activity_name}DataOG.csv" to remove undefined and empty cells -> set to 0  
*  Will create a 4 x 4 graph of all sensors for each experiment (program will ask if you want to save )
* Add observation number labels to each experiment so that you can cross reference the graph 
** Save new data to {activity_name}DataClean.csv
* Save valid experiments to "{activity_name}DataClean.csv"

2. **layeredGraphs.R**  


3. **classificationAlgo.R**


4.  **createTestTrainData.R**


**Sensor_Data**
* All csv files holding data is in here

Tasks
- [ ] Remove normalization calculation in during data collection ( .ino file)  - can do this is R during preprocessing
(this is leading slow sensor querying - now ~2/3 Hz; want 20 Hz)
- [ ]  For simplicity: (testing) Dynamically assign number of experiments that you need, click the button once (rely of green and red LEDs )
(clicking the button for every run is unnecessarily arduous )

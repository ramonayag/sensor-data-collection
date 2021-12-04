# Takes sensor data from one sensor at a time and plots all activities on one graph  

library(ggplot2)
library(gridExtra)
library(grid)
library(lattice)


setwd("~/Documents/Arduino/getSensorData")
fileName <- "fallingDataClean.csv"
data1 <- read.csv(fileName)
fileName <- "objectfallingDataClean.csv"
data2 <- read.csv(fileName)
fileName <- "walkingDataClean.csv"
data3 <- read.csv(fileName)
fileName <- "sittingDataClean.csv"
data4 <- read.csv(fileName)

#hard coded for the first observation in each data frame ... for now 
fall <- data1[2:16,]
object <- data2[2:18,]
walking <- data3[2:16,]
sitting <-  data4[2:16,]
observation <- 1

columnNames <- c("ACC_X.raw", "ACC_Y.raw", "ACC_Z.raw", "ACC_X.norm", "ACC_Y.norm", "ACC_Z.norm", "GYRO_X.raw", "GYRO_Y.raw","GYRO_Z.raw", "GYRO_X.norm", "GYRO_Y.norm", "GYRO_Z.norm", "Ceramic_Piezo", "Film_Piezo", "Weighted_Film_Piezo", "Vibration_Sensor")

colors <- c("Human Fall" = "green", "Object Fall" = "red","Walking" = "orange","Sitting" = "black")

# to help iterate over column vectors 
count <- 2 

for(i in columnNames){
  print(i)

  df1 <- data.frame( x= as.numeric(fall$Time), y = fall[ ,count]  )
  df2 <- data.frame( x= as.numeric(object$Time), y = object[ ,count] )
  df3 <- data.frame( x= as.numeric(walking$Time), y = walking[ ,count] )
  df4 <- data.frame( x = as.numeric(sitting$Time), y = sitting[ ,count]  )
  
  layered_plot <- 
         ggplot() + 
           geom_line(data=df1, aes(x,y, group = 1, color='green'), color = "green") +   
           geom_line(data=df2, aes(x,y, group = 1), color="red") + 
           geom_line(data=df3, aes(x, y, group = 1), color='orange') +
           geom_line(data=df4, aes(x,y, group = 1, color='black'))+
           labs(x = "Time (miliseconds)", y = "Sensor Response to Activity", 
                title = paste("Sensor:", i) , color = "Legend") +
           scale_color_manual(values = colors ) + 
           theme_bw() 
  
  print(layered_plot)
  
  # PNG device
  png(paste0("Sensor_", i,"_Observation",observation,".png"), res=300)
  # Code
  plot(layered_plot)
  # Close device
  dev.off()
  
  count <- count + 1
}




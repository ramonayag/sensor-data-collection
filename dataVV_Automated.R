## This script is checking each experiment (different lengths each) and checking if 
##    the data seems reasonable. If so keep the experiment and write to a new csv file   
##    (some experiments were recorded without the said event occuring)

# This file not only preprocesses the data but also saves graphs for every experiment 

library(reshape2)
library(lattice)

setwd("~/Documents/Arduino/getSensorData")

activityName <- tolower(readline(prompt="What activity data are you cleaning (one word- present participles)?: "))

fileName <- paste(activityName, "DataOG.csv", sep = "") 
data <- read.csv(fileName)

numTuples <- length(data[,1])


# cleaned the vibration sensor data 
#if weighted is not empty and not the column header replace empty with 0
for(i in (1:numTuples)){
  if( !(is.na(data[i,16])) && is.na(data[i,17])){
    data[i,17] = 0
  }
}

# change character to numeric matrix for vibration sensor column 
#data$X.15 <- as.numeric(data$X.15)
data$Vibration_Sensor <- as.numeric(data$Vibration_Sensor)

#need 40 of each sensor activity  
count <- 1 
flag1 <- TRUE 
startRow <- 0 
endRow <- 1 
startLoop <- 1
keep <- "y"
continue <- "y"
columnNames <- c("Time", "ACC_X.raw", "ACC_Y.raw", "ACC_Z.raw", "ACC_X.norm", "ACC_Y.norm", "ACC_Z.norm", "GYRO_X.raw", "GYRO_Y.raw","GYRO_Z.raw", "GYRO_X.norm", "GYRO_Y.norm", "GYRO_Z.norm", "Ceramic_Piezo", "Film_Piezo", "Weighted_Film_Piezo", "Vibration_Sensor")

#find total data points collected 
numObservations <- length(grep("button pressed", data[,1])) + 1 

#create new data frame 
cleanData <- data.frame(matrix(ncol = length(columnNames), nrow = 0))
colnames(cleanData) <- columnNames

################################ 
# IF CONTINUE IS YES KEEP RUNNING THIS LOOP # 


while(continue != "n" & numObservations > 0){
    #view the data per chuck 
    for(i in startLoop:numTuples){    
      #when you reach the row that is not NA record starting row 

      # find first row - does this row contain a numeric value 
      if(!is.na(data[i,17]) & flag1){
        #TESTING
        cat((sprintf(" (if statement:)The new startLoop value is: %i", startLoop)))
        
          # save first row of data 
          startRow <- i 
          flag1 <- FALSE 
      }
      #when you reach the row that is NA record the row of the last number value  
      else if (is.na(data[i,17]) & !flag1){
        #save last row of data 
        endRow <- i -1 
        flag1 <- TRUE 
        break 
      }
      
    }#end of for loop 


    # loop not working for the last experiment  
    if(endRow < startRow){
      endRow = dim(data)[1]
    }

  
    #TESTING
    cat((sprintf("The start row is: %i", startRow)))
    cat((sprintf(" The end row is: %i", endRow)))
  
    
    #get subset of data 
    data1 <- data[startRow:endRow,]
    
    #change column names of data 
    colnames(data1) <- columnNames
    
    # change data frame to numeric  
    data1[] <- lapply(data1, as.numeric)
    
    #map the data 
    mm <- melt(subset(data1, select =c(Time, ACC_X.raw, ACC_Y.raw, ACC_Z.raw, ACC_X.norm, ACC_Y.norm, ACC_Z.norm, GYRO_X.raw, GYRO_Y.raw,GYRO_Z.raw, GYRO_X.norm, GYRO_Y.norm, GYRO_Z.norm, Ceramic_Piezo, Film_Piezo, Weighted_Film_Piezo, Vibration_Sensor)), id.var = "Time")
    myPlot <-  xyplot(value~Time| variable, data=mm, type="l", scales=list(y=list(relation="free")),layout =c(4,4))
    print(myPlot)
    
    # PNG device
    png(paste( activityName,"DataExperiment",count,".png", sep = ""), width=1170, height=585)
    # Code
    plot(myPlot)
    # Close device
    dev.off()
    
    #choose to keep chuck of data based on visualization of data 
    keep <- tolower(readline(prompt="Keep record (y/n): "))
    if(keep != "n"){
      #add to data frame   
      cleanData[nrow(cleanData) + 1,] = c(sprintf("observation %i", count), "","" ,"" ,"", "", "", "", "", "", "", "", "", "", "", "", "")
      cleanData <- rbind(cleanData, data1)
      count <- count + 1
    }
    
    numObservations <- numObservations - 1 
    print(sprintf("The count is currently: %i, Remaining observations: %i", count-1, numObservations))
    continue <- tolower(readline(prompt="Would you like to continue(y/n): "))
    
    #change the start of the loop to where you left off 
    startLoop <- endRow + 1 
    cat((sprintf(" (While loop:)The loop starts at: %i", startLoop)))
    
}

################################ 
# END: IF CONTINUE IS YES & THERE ARE STILL OBSERVATIONS REMAINING KEEP RUNNING THIS LOOP # 

#write new data to a new csv file
newFile <- paste(activityName,  "DataClean.csv", sep= "")
write.csv(cleanData, newFile, row.names = FALSE)

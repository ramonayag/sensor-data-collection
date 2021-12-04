# take the aggregated data & remove the observation number rows 
#NOTE: THE EXTRA TIME,ACCX, ... HEADER ROWS ARE REMOVED MANUALLY 
# save to clean_aggregated_data.csv 
# split data (segmented activities) for each activity (4)
#    75% of each activity (36 events) --> training data
#    25% of each activity (12 events) --> training data

setwd("~/Documents/Arduino/getSensorData")


#################### USED WITH 48 EACH DATA  ####################

setwd("~/Documents/Arduino/getSensorData")


dirty_data <- read.csv("aggregated_data_48each.csv", stringsAsFactors = FALSE)

clean_data <- data.frame(matrix(ncol = 18, nrow = 0))
colnames(clean_data) <- colnames(dirty_data)

training_data <- data.frame(matrix(ncol = 18, nrow = 0))
colnames(training_data) <- colnames(dirty_data)

testing_data <- data.frame(matrix(ncol = 18, nrow = 0))
colnames(testing_data) <- colnames(dirty_data)

# iterate over the rows and  remove rows where NA's in 3rd column 
for(i in 1:nrow(dirty_data) ){
  if( !(is.na(dirty_data[i,3])) ){
    clean_data <- rbind(clean_data, dirty_data[i,])             
  }
}


# check if observation rows removed correctly 
numRows_to_elminate <- length(grep("observation", dirty_data[,1]))
difference_rows_between_dataframes <- dim(dirty_data)[1] - dim(clean_data)[1]
if(numRows_to_elminate == difference_rows_between_dataframes){
  print("Yes, cleaned data set correctly")
}else{
  print("No, did not clean data set correctly")
}


count = 0 
my_list <- c()
# num of observation = 196 
# training data = 192 *.75 = 144
# testing data = 48 
# randomly distributed: every 3 => train, 1=> test 
for(i in 1:nrow(clean_data) ){
  # increment counter for every new window of activity 
  if(clean_data[i,18] == "yes"){
    count <- count + 1
  }
  #reset counter 
  if(count == 4){
    count <- 0 
  }
  #add row to training data
  if(count < 3){
    training_data <- rbind(training_data, clean_data[i,]) 
  }
  #add row to test data
  if(count == 3 ){
    testing_data <- rbind(testing_data, clean_data[i,])   
    #for testing 
    my_list <- c(my_list, count)
  }
}


#TESTING   
# check if testing and training data created correctlty 
numObservTrain <- length(grep("yes", training_data[,18]))
numObservTest <- length(grep("yes", testing_data[,18]))
#They should be  144 (192 * .75) and 48 (192 * .25), respectively 
print(numObservTrain)
print(numObservTest)

# #TESTING
newCounter = 0
for(i in 1:nrow(testing_data)){
  if(testing_data[i,17] == "sitting" && testing_data[i,18] =="yes"){
    newCounter <- newCounter + 1
  }
}
print(newCounter)


# save cleaned data set 
write.csv(clean_data,"cleaned_aggregated_48data.csv", row.names = FALSE)
# save training data 
write.csv(training_data, "training_48data80.csv", row.names = FALSE)
#save testing data 
write.csv(testing_data, "testing_48data20.csv", row.names = FALSE)

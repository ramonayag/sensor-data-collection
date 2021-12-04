library(caret)
library(kernlab)
library(gbm)
library(plot3D)
library(randomForest)
library(lattice)
library(psych)

setwd("~/Documents/Arduino/getSensorData")


#Read in the testing and training data- split 75/25
#segmented windows 
training_data <- read.csv("training_48data80.csv", stringsAsFactors = FALSE)
testing_data <- read.csv("testing_48data20.csv", stringsAsFactors = FALSE)

training_data <- training_data[2:17]
testing_data <- testing_data[2:17]

training_data[, 16] <- as.factor(training_data[, 16])
testing_data[, 16] <- as.factor(testing_data[, 16])


#resulting training data columns for refrence
# ACC_X.raw + ACC_Y.raw + ACC_Z.raw + ACC_X.norm + ACC_Y.norm + ACC_Z.norm+ GYRO_X.raw + GYRO_Y.raw + GYRO_Z.raw + GYRO_X.norm + GYRO_Y.norm + GYRO_Z.norm + Ceramic_Piezo + Film_Piezo + Weighted_Film_Piezo

 
#################################  ATTEMPT 1 #################################  

# A scatter plot matrix (SPLOM) is drawn in the graphic window.
#  lower off diagonal draws scatter plots, the diagonal histograms, 
#  the upper off diagonal reports the Pearson correlation (with pairwise deletion).
pairs.panels(training_data[1:15], digits = 3, gap = 0)


fitControl <- trainControl(method = "cv", number = 5, returnResamp = "all")
set.seed(32323)
model.treebag <- train(Activity_Name ~., method = "treebag", data = training_data, trControl = fitControl)
result2 <- predict(model.treebag, newdata = testing_data)
confusionMatrix(result2, testing_data$Activity_Name)

set.seed(32323)
model.logit <- train(Activity_Name ~ ., method = "LogitBoost", data = training_data, trControl = fitControl)
result3 <- predict(model.logit, newdata = testing_data)
confusionMatrix(result3, testing_data$Activity_Name)


set.seed(32323)
model.svm <- suppressWarnings(train(Activity_Name ~., data = training_data, method = "svmRadialCost", trControl = fitControl ))
result4 <- predict(model.svm, newdata = testing_data)
confusionMatrix(result4, testing_data$Activity_Name)

#fitControl <- trainControl(method="cv", number=5, verboseIter=FALSE)


set.seed(32323)
gbmFit <- train(Activity_Name ~ACC_X.raw + ACC_X.norm +  GYRO_Y.norm + GYRO_Z.norm + Ceramic_Piezo  , data=training_data, method="gbm", trControl=fitControl, verbose=FALSE)
confusionMatrix(predict(gbmFit, newdata=testing_data),testing_data$Activity_Name )
#Plotting the model shows how the various iterations of hyperparameter search performed.
plot(gbmFit)
gbmFit

set.seed(32323)
#gbmGrid <-  expand.grid(interaction.depth = c(1, 5, 9), n.trees = (1:10)*50, shrinkage = 0.1, n.minobsinnode = 20)
gbmGrid <-  expand.grid(interaction.depth = c(1,5), n.trees = (1:10)*10, shrinkage = 0.1, n.minobsinnode = 20)
gbmFit2 <- train(Activity_Name ~. , data = training_data, method = "gbm", trControl = fitControl, verbose = FALSE, tuneGrid = gbmGrid)
plot(gbmFit2)
gbmFit2
confusionMatrix( predict(gbmFit2, newdata=testing_data), testing_data$Activity_Name)


rfFit<-train(Activity_Name ~., data=training_data, method="rf", trControl=fitControl, prox=TRUE, allowParallel=TRUE)
rfFit
confusionMatrix( predict(rfFit, newdata=testing_data),testing_data$Activity_Name)


#EXAMPLE - VAR IMP can be used to characterize the general effect of predictors on the model.
# It works with the following object classes: ... GBM, RandomForest (from the party package)
# MIGHT work with others bc it can work with objects produced by train  

#compute variable importance
# importances using varImp() to understand which variables came out to be useful.
varimp_svm <- varImp(model.svm)
plot(varimp_svm, main="Variable Importance with model.svm")


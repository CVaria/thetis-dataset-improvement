function [predicted_label, accuracy, confidence_scores]= svmTest(FolderPath)

load(FolderPath)
rows =size(Input_Activities,1)
for i =1:rows
    MatCell{i,1} = {Input_Activities(i,:), Input_Labels(i)};
end

MatCell_shuffled = MatCell(randperm(numel(MatCell))); 

size(MatCell_shuffled,1);
x = round(0.7 * rows)-1;

Mat1 = MatCell_shuffled(1:x); 
Mat2 = MatCell_shuffled(x+1:rows);
Train_Activities=[];
Train_Labels =[];
Test_Activities=[];
Test_Labels = []

for i =1:x
   tmp= Mat1{i,1};
   a = tmp(1,1);
   l = tmp(1,2);
   Train_Activities = [Train_Activities; cell2mat(a)];
   Train_Labels = [Train_Labels; cell2mat(l)];
   
end

for i = 1:(rows-x-1)
   tmp= Mat2{i,1};
   a = tmp(1,1);
   l = tmp(1,2);
   Test_Activities = [Test_Activities; cell2mat(a)];
   Test_Labels = [Test_Labels; cell2mat(l)];
    
end
model = svmtrain(Train_Labels, Train_Activities, '-s 0 -t 2')
[predicted_label, accuracy, confidence_scores] = svmpredict(Test_Labels, Test_Activities, model);


%function fc = PostureVector(Frame)
function [fr fc] = PostureVector(Frame)

%Index0 = HEAD
%Index1 = LEFT_ELBOW
%Index2= LEFT_FOOT
%Index3= LEFT_HAND
%Index4= LEFT_HIP
%Index5= LEFT_KNEE
%Index6= LEFT_SHOULDER
%Index7 = NECK
%Index8= RIGHT_ELBOW
%Index9= RIGHT_FOOT
%Index10= RIGHT_HAND
%Index11= RIGHT_HIP
%Index12= RIGHT_KNEE
%Index13= RIGHT_SHOULDER
%Index14= TORSO
fr=zeros(15,3);
fc = zeros(1,45);
j=1;
for i=1:15 
    fr(i,:) = JointFeatures(Frame(i,:),Frame(8,:),Frame(15,:));
    D = JointFeatures(Frame(i,:),Frame(8,:),Frame(15,:));
    fc(1,j)=D(1,1);
    fc(1,j+1)=D(1,2);
    fc(1,j+2)=D(1,3);
    j=j+3;
    
end

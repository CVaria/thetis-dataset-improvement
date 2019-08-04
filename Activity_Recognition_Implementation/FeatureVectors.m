%function fsc = FeatureVectors(Frames)
function [fs fsc] = FeatureVectors(Frames)

[rows cols] = size(Frames)
fs={};
fsc=[];
for i=1:rows
    [x y] = PostureVector(Frames{i,1});
    fs{i,1} = x;
    fsc(i,:)=y;
    %[fs{i,1} fsc(i,:)] = PostureVector(Frames{i,1});
    %fsc(i,:) = PostureVector(Frames{i,1});
end

%Note: fsc will be used for kmeans algorithm. Each row of fsc has a certain
%format [Joint1_x Joint1_y Joint1_z Joint2_x Joint2_y ... JointN_z] in
%order to use kmeans algorithm
%idx = kmeans(cell2mat(fs),1)
%Find activity main features by clustering Feature Vectors into sets using kmeans  
function Activity = ActivityFeature(Frames, NoClusters)

[fs fsc] = FeatureVectors(Frames);
%fsc
%size(fsc)
[idx C] = kmeans(fsc, NoClusters);
Activity=[];
%idx
%size(idx)
%remove nan values
idx(isnan(idx))=[];
%A=[idx(logical(diff(idx))); idx(end)]
A = idx.';
A = sortCenters(A)
[rows cols] = size(A);
for i=1:cols
    Activity = [Activity C(A(1,i),:)];
end

C;
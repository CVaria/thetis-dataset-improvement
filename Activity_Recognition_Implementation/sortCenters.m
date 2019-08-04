function compressed = sortCenters(data)

%Find length of repeated number sequences
X = diff(data)~=0;
B = find([true,X]); % begin of each group
E = find([X,true]); % end of each group
counter = 1+E-B % the length of each group

%remove duplicate numbers
change = diff(data.')~=0;
indices = [1,find(change)'+1];
compressed = data(indices)
[rows cols] = size(compressed);

for i=1:cols
    value = compressed(1,i);
    if(value~=-1)
        Index = find(compressed == value);
        Counts = counter(Index);
        [v ind]=max(Counts);
        Index(ind)=[];
        compressed(Index) = -1;
    end
end

IndRem = find(compressed == -1);
compressed(IndRem)=[]

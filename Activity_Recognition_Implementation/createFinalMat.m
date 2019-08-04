function svmInput = createFinalMat(Path, Name)

%LABELS
%BACKHAND =1
%BACKHAND2HANDS=2
%BACKHANDSLICE=3
%FOREHANDFLAT=4
%FOREHANDOPEN=5
%FORSLICE=6
%SERVICEFLAT=7
%SERVICEKICK=8
%SERVICESLICE=9
%SMASH=10
%VOLLEY=11
%VOLLEYBACHHAND=12

%use dictionary to match moves with numbers
mapObj = containers.Map
keyset = {'backhand', 'backhand2hands', 'backhandslice', 'forehandflat','forehandopen', 'forslice', 'serviceflat', 'servicekick', 'serviceslice','smash', 'volley', 'volleybackhand'}
valueset = [1,2,3,4,5,6,7,8,9,10,11,12]
mapObj = containers.Map(keyset, valueset)

MatList = dir(Path);
MatList = MatList(~ismember({MatList.name},{'.','..'}));

MatFiles = {MatList.name}
MatFiles
cols = size(MatFiles,2)

Input_Activities = []
Input_Labels =[]
List = []
Labels = []
Check =[]

for i = 1:cols
    MatFiles{1,i};
    %use '\' or '/' based on the operating system
    load(strcat(Path,'/',MatFiles{1,i}));
    Input_Activities = [Input_Activities; List];
    if size(Labels,1)>0
        Input_Labels = [Input_Labels; ones(size(Labels,1),1)*mapObj(Labels(1,:))]
        Check = [Check ; [size(Input_Labels,1) size(List,1)]]
    end
end

svmInput = [Input_Activities, Input_Labels];

save(strcat(Name,'.mat'), 'Input_Activities', 'Input_Labels')
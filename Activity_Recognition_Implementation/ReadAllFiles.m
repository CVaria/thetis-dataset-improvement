function FinalActivity = ReadAllFiles(Path, NoClusters)

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


ListF = dir(Path);
ListF = ListF(~ismember({ListF.name},{'.','..'}));

ListFiles = {ListF.name}
[rows cols] = size(ListFiles)

%Activities = []
%Labels =[]

for i = 1:cols
  %use '\' or '/' depending on your operating system 
  FolderPath = strcat(Path,'/',ListFiles{1,i})
  [tempAct tempLabel sizeFile]=ReadClassFiles(FolderPath, NoClusters)
  %Activities = [Activities; tempAct] 
  %Labels = [Labels; tempLabel]
    
end


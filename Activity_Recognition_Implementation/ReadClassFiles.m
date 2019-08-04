%Creates an activity feature list for the files of folder
function [List Labels FolderSize] = ReadClassFiles(FolderPath, NoClusters)

%d=dir;
%d=d(~ismember({d.name},{'.','..'}));

ListF = dir(FolderPath);
ListF = ListF(~ismember({ListF.name},{'.','..'}));


[Folder,Name,Ext] = fileparts(FolderPath) 

ListFiles = {ListF.name}
[rows cols] = size(ListFiles)
FolderSize = cols

TempCell={};
TempFrames=[];
List=[];
Labels =[]
for i = 1:cols
    [TempCell TempFrames] = ReadData(FolderPath, ListFiles{1,i});
    A = ActivityFeature(TempCell, NoClusters);
    List(i,:) = A;
    Labels = [Labels; Name]
end

save(strcat(Name, '.mat'), 'List', 'Labels', 'FolderSize')


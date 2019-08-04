function [Frames, NoFrames] = ReadData(folder,baseFileName)
%open file from different directory

fullFileName = fullfile(folder, baseFileName);
disp(fullFileName)
disp('In');

if exist(fullFileName, 'file')
  % Open the file however you do
  fid = fopen(fullFileName,'r');
  
  %# Get file size.
  fseek(fid, 0, 'eof');
  fileSize = ftell(fid);
  frewind(fid);
  %# Read the whole file.
  data = fread(fid, fileSize, 'uint8');
  %# Count number of line-feeds and increase by one.
  %Txt Correction!! numLines should exclude ending lines with only 'space'
  numLines = sum(data == 10) - 1;
  
  frewind(fid);
  delimiter = ' ';
  R1 = 1;
  C1 = 0;
  R2 = 15;
  C2 = 2;
  NoFrames=0;
  Frames={};
  %Read data and create list of frames / cell array
  while NoFrames*16 < numLines
      Frame = dlmread(fullFileName,delimiter,[R1 C1 R2 C2]); 
      NoFrames = NoFrames +1;
      R1 = R1+16;
      R2 = R2+16;
      Frames{NoFrames,1}= Frame;
  end
  
  NoFrames = NoFrames-1;
  fclose(fid);
else
  % File does not exist.
  warningMessage = sprintf('%s does not exist', fullFileName);
  uiwait(warndlg(warningMessage));
end

disp('Out');
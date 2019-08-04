function Di = JointFeatures(Ji, J8, J15)
%J8 = neck
%J15 = torso

Di = (Ji - J15) ./ sqrt(sum((J8-J15).^2));
function [] = WaveTankFunction() 


videoFReader = vision.VideoFileReader("wave_01.mov")
%something's weird with .mp4
videoPlayer = vision.VideoPlayer;
frameNum = 0
while ~isDone(videoFReader)
  
  %Functions organized for basic bw image  
  %Original really slow but more organized
  %videoFrame = videoFReader();
  %originalFrame = videoFReader();
  %videoFrame = imcrop(videoFrame, [100,600,1775,275])
  %videoFrame = imgaussfilt(videoFrame, 3)
  %videoFrame = createMask(videoFrame)
  %videoFrame = edge(videoFrame, 'canny')

  %% Notes
  % Try making multiple masks
  % Save to video
  % nested color threshold
  % show every stage to pinpoint problem



%% Tracking highest point
% closest attempt at tracking highest point, still needs to be more smooth
white = edge(createMask(imgaussfilt(imcrop(videoFReader(), [100,600,1775,275]),3)), 'canny');
row = nan(1,size(white,2)); 
for k = 1:length(row) 
    try
        row(k) = find(white(:,k),1,'first');
        %disp(row(k) + " " + k)
        [lowY, corX] = min(row);
    end
end
row = fillmissing(row, 'previous');
%% Math section
% Finding height of calm water
if frameNum == 0
calmLvl = lowY;
end
%disp(calmLvl)
%



%% Video & yellow dot
    %*Merge lines together when finished with this portion
test = edge(createMask(imgaussfilt(imcrop(videoFReader(), [100,600,1775,275]),5)), 'canny') + imcrop(videoFReader(), [100,600,1775,275]);
  %videoPlayer(insertShape(test, 'circle', [corX lowY 5], 'LineWidth', 10))
  withHighest = insertShape(test, 'circle', [corX lowY 5], 'LineWidth', 10);
  videoPlayer(insertShape(withHighest,'line', [0 calmLvl 1776 calmLvl], 'LineWidth', 2, 'Color', 'red'));

  
frameNum = frameNum+1
%imwrite((edge(createMask(imgaussfilt(imcrop(videoFReader(), [100,600,1775,275]),3)), 'canny')) + imcrop(videoFReader(), [100,600,1775,275]), '%d.png', frameNum)



 % -=-=-= Main play video -=-=-=-=
 videoPlayer((edge(createMask(imgaussfilt(imcrop(videoFReader(), [100,600,1775,275]),3)), 'canny')) + imcrop(videoFReader(), [100,600,1775,275]))

 % Save image (needs work for video)
 %imwrite((edge(createMask(imgaussfilt(imcrop(videoFReader(), [100,600,1775,275]),3)), 'canny')), "test2.png")


end
end


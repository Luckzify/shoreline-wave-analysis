function [] = WaveTankFunction() 

    outVideo = VideoWriter('outputVideo.mp4', 'MPEG-4');
    outVideo.FrameRate = 10; 
    open(outVideo);

videoFReader = vision.VideoFileReader("wave_03.mov")
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



%% Video & yellow dot
    %*Merge lines together when finished with this portion
test = edge(createMask(imgaussfilt(imcrop(videoFReader(), [100,600,1775,275]),5)), 'canny') + imcrop(videoFReader(), [100,600,1775,275]);
  %videoPlayer(insertShape(test, 'circle', [corX lowY 5], 'LineWidth', 10))
  withHighest = insertShape(test, 'circle', [corX lowY 5], 'LineWidth', 10);
  video = insertShape(withHighest,'line', [0 calmLvl 1776 calmLvl], 'LineWidth', 2, 'Color', 'red');
  %videoPlayer(video);

imwrite(video, frameNum + ".png") %peak efficency and is why there are so many files

writeVideo(outVideo,imread(frameNum + ".png"));
frameNum = frameNum+1
end




%% notes
%trace wave 
% Search for x coordinate that is to the left of the wave
% look how to use spline to make a smooth line and find local maxima and
% minima
% Make the curve smoother by averaging surrounding points'
% rise over run to find slope between 2 pixels
% when the slope is + and the other side is negative that is the maxima,
% vice versa is minima
%running average
% signal processng toolbox
% gaussian blur
% convulution blur maybe if thats how it's spelled
% find a 1d blur format

end


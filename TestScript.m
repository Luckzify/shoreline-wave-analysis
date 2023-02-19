a = imread("0.png");
imshow(a)
crop = [1000, 100, 10, 1000]
crop1 = 1000
crop = [crop1, 100, 10, 1000]
%a = imcrop(a, [1000, 100, 10, 1000])
a = imcrop(a,crop);
%1 is distance from right side
%2 is distance from top
%3 is width
%4 is height
imshow(a)
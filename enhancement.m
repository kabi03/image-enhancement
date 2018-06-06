%% 2.1.1 Histogram Equalize
mex histogram_equalize.c
img = imread('207056.jpg');
out = histogram_equalize(img);
figure(1);
imshow(img); title('original image');
figure(2);
imshow(out); title('output');

%% 2.1.2 Adaptive Histogram Equalize
mex adaptive_histogram.c
img = imread('207056.jpg');
out = adaptive_histogram(img,3,3);
figure(1);
imshow(img); title('original image');
figure(2);
imshow(out); title('output');

%% 2.1.3 unsharp mask
img = imread('7.2.01-small.png');
out = unsharp_mask(img,10,1);
figure(1);
imshow(img); title('original image');
figure(2);
imshow(out); title('output');

%% 2.1.4 laplacian sharpen
img = imread('7.2.01-small.png');
out = laplacian_sharpen(img,8);
figure(1);
imshow(img); title('original image');
figure(2);
imshow(out); title('output');

%% 2.3.1 noise additive.png
img = imread('noise_additive.png');
img_db = im2double(img);
out = spatial_filter(img_db, [1/9 1/9 1/9;1/9 1/9 1/9;1/9 1/9 1/9]);
out = unsharp_mask(out,10,1);
figure(1);
imshow(img); title('original image');
figure(2);
imshow(out); title('output');

%% 2.3.1 noise multiplicative.png
img = imread('noise_multiplicative.png');
img_db = im2double(img);
out = spatial_filter(img_db, [1/9 1/9 1/9;1/9 1/9 1/9;1/9 1/9 1/9]);
out = unsharp_mask(out,10,1);
figure(1);
imshow(img); title('original image');
figure(2);
imshow(out); title('output');

%% 2.3.1 noise_impulsive.png
img = imread('noise_impulsive.png');
out = medfilt2(img, [3 3]);
figure(1);
imshow(img); title('original image');
figure(2);
imshow(out); title('output');

%% 2.3.1 snowglobe.png
img = imread('snowglobe.png');
img_db = im2double(img);
out = spatial_filter(img_db, [1/9 1/9 1/9;1/9 1/9 1/9;1/9 1/9 1/9]);
out = unsharp_mask(out,3,1);
figure(1);
imshow(img); title('original image');


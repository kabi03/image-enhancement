function [out] = unsharp_mask(in, r, k)

out = in + k*(in - imgaussfilt(in, (r/3)));

imshow(in);
figure;
imshow(out);
end
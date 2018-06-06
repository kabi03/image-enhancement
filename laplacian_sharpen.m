function [out] = laplacian_sharpen(in, k)

orig = in;
I = zeros(size(in));
Filter = [1 1 1;1 -k 1; 1 1 1];
in=padarray(in,[1,1]);
in=double(in);

for i=1:size(in,1)-2
    for j=1:size(in,2)-2
        I(i,j)=sum(sum(Filter.*in(i:i+2,j:j+2)));
    end
end

I=uint8(I);
out= orig-I;

end
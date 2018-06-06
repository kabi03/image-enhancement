#include "mex.h"

void histogram_equalize(int w, int h, const unsigned char *input, unsigned char *output){ 
    
    int img_size = w*h;
    double f[255] = {0};
    double cdf[255] = {0};
    double pdf[255] = {0};
        
    for(int i = 0; i <= 255; i++){
        
        for (int y = 0; y<h; y++){
            
            for (int x = 0; x<w; x++){
                
                int ind = x*h + y; 
                
                if (input[ind] == i)
                f[i]++; 
                
                pdf[i] = f[i]/img_size;
                output[ind] = cdf[(input[ind])]*255;
            }
        }
        cdf[i] = pdf[i]+cdf[i-1]; 
    }
}


void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    
    if (nlhs != 1)
        mexErrMsgTxt("One input is required.");
    
    if (nrhs != 1)
        mexErrMsgTxt("One output is required.");
    
    const mxArray *img = prhs[0];
    
    if (!mxIsDouble(img) && !mxIsUint8(img))
        mexErrMsgTxt("Only images of type double or uint8 are accepted.");
    
    mwSize ndims = mxGetNumberOfDimensions(img);
    const mwSize *dims = mxGetDimensions(img);
    
    int height  = dims[0];
    int width   = dims[1];
    mxClassID input_type = mxGetClassID(img);
    mxArray *output = mxCreateNumericArray(ndims, dims, input_type, mxREAL);
    plhs[0] = output;
    
    if (mxIsUint8(img)){
        unsigned char *image_ptr = (unsigned char *)mxGetData(img);
        unsigned char *output_ptr = (unsigned char *)mxGetData(output);
        histogram_equalize(width, height, image_ptr, output_ptr);
    }   
}
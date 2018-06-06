#include "mex.h"
#include <inttypes.h>
#include <math.h>

void adaptive_histogram(int w, int h,const int H,const int W, const unsigned char *input, unsigned char *output){   
  
    
    float cdf = 0;
    const int l =256;
    double histogram[l];
    double gray_level_mapping[l];
    int Hr = (int) floor((double)(H/2));
    int Wr = (int) floor((double)(W/2));
    const unsigned char *image_in = &input[0];
    unsigned char *image_out = &output[0];
   
    
    char ** org_img = NULL;
    org_img = malloc( h * sizeof(char *));
    
    for(int i = 0; i < h; i++){
        org_img[i] = malloc( w * sizeof(char));
    }
    
    char ** proc_img = NULL;
    proc_img = malloc( h * sizeof(char *));
    
    for(int i = 0; i < h; i++){
        proc_img[i] = malloc( w * sizeof(char));
    }
  
    
    
    for(int i = 0 ; i<h; i++){
        for(int j = 0; j<w; j++){
            int ind = j*h + i;
            org_img[i][j] = image_in[ind];
            
        }
    }
    
    for(int m = Hr ; m<h-Hr; m++){
        for(int n = Wr; n<w-Wr; n++){
                       
      
            for (int i = 0; i < l; i++){
                histogram[i] = 0;
            }
            
            
            int start_row =  m - Hr;
            int start_col = n - Wr;
            
            
            for(int i = start_row;i<=(H+start_row);i++){
                for(int j = start_col;j<=(W+start_col);j++){
                    int pixel = org_img[i][j];
                    histogram[pixel] +=  1;
                    
                }
            }
            
            double cdf = 0;
            
           
            for (int k = 0; k<l;k++){
                cdf = cdf + histogram[k]/(H*W);
                double calc = cdf*255;
                if (calc>255)
                    calc = 255;
                if (calc<0)
                    calc = 0;
                gray_level_mapping[k] = calc;
            }
            
          
            for (int i = start_row; i <=(H+start_row);i++) {
                for (int j = start_col; j <=(W+start_col);j++) {
                    int pixel = org_img[i][j];
                    proc_img[i][j] = gray_level_mapping[pixel];
                    
                }
            }                  
        }
    }
    
    
    for (int y = 0; y < h; y++){
        for (int x = 0; x < w; x++){
            int ind = x*h + y;
            image_out[ind] = proc_img[y][x];
            
        }
    }
 }


void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){

    
    if (nrhs != 3)
        mexErrMsgTxt("Only three inputs.");
    
    if (nlhs != 1)
        mexErrMsgTxt("Needs one output.");
    
    
    
    const mxArray *img = prhs[0];
    if (!mxIsUint8(img))
        mexErrMsgTxt("Images of type uint8 only accepted.");
    
    
    
    mwSize ndims = mxGetNumberOfDimensions(img);
    const mwSize *dims = mxGetDimensions(img);
    
    const int H = mxGetScalar(prhs[1]);
    const int W = mxGetScalar(prhs[2]);
    
    const int h   = dims[0];
    const int w    = dims[1];
   
    
    
    
    mxClassID input_type = mxGetClassID(img);
    
    
    mxArray *output = mxCreateNumericArray(ndims, dims, input_type, mxREAL);
    plhs[0] = output;
    
    
    if (mxIsUint8(img)){
        const unsigned char *img_ptr = (unsigned char *)mxGetData(img);
        unsigned char *out_ptr = (unsigned char *)mxGetData(output);
        
        adaptive_histogram(w, h,H,W, img_ptr, out_ptr);
    }
    
}
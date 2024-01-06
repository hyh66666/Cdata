#include <opencv2/opencv.hpp>
#include"face_binary_cls.cpp"
#include<algorithm>
#include<math.h>
#include<fstream>
#include<string>
using namespace std;
float c0 = 0, c1 = 0;

float *ConvBNReLU(int col, int channel, int row, float *data, conv_param conv_params);

float *padMatrix(float *matrix, int col,int channels, int row, int col_new, int row_new);

float *Maxpool(int size, int step, int col, int row, int channel, float *data);

void FC(float fc0_weight[], float fc0_bias[], float *data);

void MatShowfile(float * data,string filename);

void loadData(const string &file_path, cv::Mat &out) {
    cv::Mat img = cv::imread(file_path);

    cv::Mat imgRGB;
    cv::cvtColor(img, imgRGB, cv::COLOR_BGR2RGB);

    cv::Mat imgRGBf;
    imgRGB.convertTo(imgRGBf, CV_32FC3);
//    img = imgRGBf / 256;
    out = imgRGBf / 256;

//    int cnt = img.rows * img.cols * img.channels();
//    float *src = (float *) img.data;
//    float *data = (float *) malloc(sizeof(float) * cnt);
//    std::copy(src, src + cnt, data);

}


int main() {
    cv::Mat img = cv::imread("./face.jpg");
    float *data = (float *) malloc(sizeof(float) * img.rows * img.cols * img.channels());
    // string s="./face.jpg";
    // cv::Mat img;
    // loadData(s,img);
    // float* data=(float*)img.data;
    
    // BGR->RGB

    for (int i = 0; i < img.channels(); i++) {
        for (int j = 0; j < img.rows; j++) {
            for (int k = 0; k < img.cols; k++) {
                if (i == 0) {
                    data[j * img.cols * img.channels() + k * img.channels() + i + 2] =
                            (float) img.data[j * img.cols * img.channels() + k * img.channels() + i] / 256;
                } else if (i == 1) {
                    data[j * img.cols * img.channels() + k * img.channels() + i ] =
                            (float) img.data[j * img.cols * img.channels() + k * img.channels() + i] / 256;
                } else {
                    data[j * img.cols * img.channels() + k * img.channels() + i - 2] =
                            (float) img.data[j * img.cols * img.channels() + k * img.channels() + i] / 256;
                }
            }
        }
    }


    // pad=1, fill with 0, 128->130
    float *data_new = padMatrix(data, img.cols , img.channels(), img.rows,
                                (img.cols + 2 * conv_params[0].pad) ,
                                img.rows + 2 * conv_params[0].pad);
    
  
    // 130->64,channels=16
    float *data_new_conv = ConvBNReLU((img.cols + 2 * conv_params[0].pad), img.channels(),
                                      img.rows + 2 * conv_params[0].pad, data_new, conv_params[0]);
    
    // MatShowfile(data_new_conv,s);


    // 64->32,channels=16
    float *data_new_pool = Maxpool(2, 2, (img.cols + 2 * conv_params[0].pad - conv_params[0].kernel_size) /
                                         conv_params[0].stride + 1,
                                   (img.rows + 2 * conv_params[0].pad - conv_params[0].kernel_size) /
                                   conv_params[0].stride + 1, conv_params[0].out_channels, data_new_conv);

    // 32->30, pad=0,don't need fill with 0, channels=32
    int data_new_conv_col =
            ((((img.cols + 2 * conv_params[0].pad) - conv_params[0].kernel_size) / conv_params[0].stride + 1) - 2) / 2 +
            1;
    int data_new_conv_row =
            (((img.rows + 2 * conv_params[0].pad - conv_params[0].kernel_size) / conv_params[0].stride + 1) - 2) / 2 +
            1;
    int data_new_channels = conv_params[0].out_channels;
    float *data_new_conv1 = ConvBNReLU(data_new_conv_col, data_new_channels, data_new_conv_row, data_new_pool,
                                       conv_params[1]);
    // 30->15, channels=32
    float *data_new_pool1 = Maxpool(2, 2, (data_new_conv_col - conv_params[1].kernel_size) / conv_params[1].stride + 1,
                                    (data_new_conv_row - conv_params[1].kernel_size) / conv_params[1].stride + 1,
                                    conv_params[1].out_channels, data_new_conv1);
    // 15->8
    int data_new_pool1_col = ((data_new_conv_col - conv_params[1].kernel_size) / conv_params[1].stride + 1 - 2) / 2 + 1;
    int data_new_pool1_row = ((data_new_conv_row - conv_params[1].kernel_size) / conv_params[1].stride + 1 - 2) / 2 + 1;
    int data_new_pool1_channels = conv_params[1].out_channels;
    // pad=1, fill with 0
    float *data_new1 = padMatrix(data_new_pool1, data_new_pool1_col , data_new_pool1_channels, data_new_pool1_row,
                                 (data_new_pool1_col + 2 * conv_params[2].pad),
                                 data_new_pool1_row + 2 * conv_params[2].pad);

    // channels=32
    float *data_new_conv2 = ConvBNReLU(data_new_pool1_col + 2 * conv_params[2].pad, data_new_pool1_channels,
                                       data_new_pool1_row + 2 * conv_params[2].pad, data_new1, conv_params[2]);

    // for(int i=0;i<2048;i++){
    //     cout<<data_new_conv2[i]<<endl;
    // }
    FC(fc0_weight, fc0_bias, data_new_conv2);

    float face = exp(c1) / (exp(c0) + exp(c1));// 人脸的概率
    float noface = 1 - face; // 不是人脸的概率
    cout<<"c0:"<<c0<<"  c1:"<<c1<<endl;
    cout << "是人脸的概率:" << face << endl << "不是人脸的概率:" << noface << endl;

    // free memory
    // free(data);
    free(data_new);
    free(data_new_conv);
    free(data_new_pool);
    free(data_new_conv1);
    free(data_new_pool1);
    free(data_new1);
    free(data_new_conv2);


    return 0;
}

void MatShowfile(float * data,string filename){
    ofstream outfile;
    outfile.open(filename);
    for (size_t k = 0; k < 16; k++)
               {
    for(int i=0;i<64;i++){
            for (size_t j = 0; j < 64; j++)
            {
               
                   
                   outfile<<data[i*64*16+j*16+k]<<",";
               
               
                
            }
            outfile<<endl;
            
            
        }
        outfile<<endl;
        outfile<<endl;
               }
        outfile.close();
}

// Full connection
void FC(float *fc0_weight, float *fc0_bias, float *data) {
    int index=0;
    for(int i=0;i<32;i++){
        for(int j=0;j<8;j++){
            for(int k=0;k<8;k++){
                c0+=data[j*8*32+k*32+i]*fc0_weight[index];
                index++;
            }
        }
    }

    // for (int i = 0; i < 2048; i++) {
    //     c0 += fc0_weight[i] * data[i];
    // }
    c0 += fc0_bias[0];

    for(int i=0;i<32;i++){
        for(int j=0;j<8;j++){
            for(int k=0;k<8;k++){
                c1+=data[j*8*32+k*32+i]*fc0_weight[index];
                index++;
            }
        }
    }

    // for (int i = 2048; i < 4096; i++) {
    //     c1 += fc0_weight[i] * data[i - 2048];
    // }
    c1 += fc0_bias[1];
}

void FC1(float *fc0_weight, float *fc0_bias, float *data) {
    c0 = 0;
    c1 = 0;

    float flatten[2048];

    int cnt = 0;
    for (int chs = 0; chs < 32; ++chs) {
        for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 8; ++col) {
                int idx = row * 8 * 32 + col * 32 + chs;
                flatten[cnt] = data[idx];
                cnt++;
            }
        }
    }
    data = flatten;

    for (int i = 0; i < 2048; i++) {
        c0 += fc0_weight[i] * data[i];
    }
    c0 += fc0_bias[0];
    for (int i = 2048; i < 4096; i++) {
        c1 += fc0_weight[i] * data[i - 2048];
    }
    c1 += fc0_bias[1];
}


// fill with 0
float *padMatrix(float *matrix, int col,int channels,int row, int col_new, int row_new) {
    // this col include col*channels
    float *matrix_new = (float *) malloc(sizeof(float) * col_new * row_new*channels);
    int top = (row_new - row) / 2;
    int bottom = row_new - 1 - top;
    int left = top;
    int right = col_new - 1 - top;

    int index = 0;
    
    for (int i = 0; i < row_new; i++) {
        for (int j = 0; j < col_new; j++) {
            for(int k=0;k<channels;k++){
            if (i >= top && i <= bottom && j >= left && j <= right) {
                matrix_new[i * col_new*channels + j*channels+k] = matrix[index];
                index++;
            } else {
                matrix_new[i * col_new*channels + j*channels+k] = 0;
            }
        }
    }
    }

    return matrix_new;
}

// Convolution. The negative number becomes 0
float *ConvBNReLU(int col, int channel, int row, float *data, conv_param conv_params) {
    int in_channels = conv_params.in_channels, out_channels = conv_params.out_channels, kernel_size = conv_params.kernel_size, stride = conv_params.stride;
    int result_col = (col - kernel_size) / stride + 1;// don't include channels
    int result_row = (row - kernel_size) / stride + 1;
    float *kernel_oi = (float *) malloc(sizeof(float) * kernel_size * kernel_size);
    int b = 0, c = -stride;//b is matrix.row, c is matrix.col
    float *result = (float *) malloc(sizeof(float) * result_col * result_row * out_channels);
    for (int o = 0; o < out_channels; ++o) {
        float bias_oi = conv_params.p_bias[o];
        for (int j = 0,b=0; j < result_row; j++,b+=stride) {
        
            for (int k = 0,c=0; k < result_col; k++,c+=stride) {

                result[j * result_col * out_channels + k * out_channels + o] = 0;

                for (int i = 0; i < in_channels; ++i) {
                    for (int a = 0; a < kernel_size * kernel_size; a++) {
                        kernel_oi[a] = conv_params.p_weight[o * (in_channels * 3 * 3) + i * (3 * 3) + a];
                    }

                    for (int z = 0; z < kernel_size; z++) {
                        for (int q = 0; q < kernel_size; q++) {

                            result[j * result_col * out_channels + k * out_channels + o] +=
                                    data[(b + z) * col * channel + (c + q) * channel + i] *
                                    kernel_oi[z * kernel_size + q];
                        }
                    }

                }
                result[j * result_col * out_channels + k * out_channels + o] += bias_oi;
                if (result[j * result_col * out_channels + k * out_channels + o] < 0) {
                    result[j * result_col * out_channels + k * out_channels + o] = 0;
                }

            }
        }
    }
    free(kernel_oi);


    return result;
}

float *Maxpool(int size, int step, int col, int row, int channel, float *data) {
    int col_new = (col - size) / step + 1;
    int row_new = (row - size) / step + 1;
    int channel_new = channel;
    int b = 0, c = -step;
    float *result = (float *) malloc(sizeof(float) * col_new * row_new * channel_new);
    for (int k = 0; k < channel_new; k++) {
        b = -step, c = -step;
        for (int i = 0; i < row_new; i++) {
            c = -step;
            b += step;
            for (int j = 0; j < col_new; j++) {
                result[i * col_new * channel_new + j * channel_new + k] = 0;
                c += step;
                for (int z = 0; z < size; z++) {
                    for (int q = 0; q < size; q++) {
                        result[i * col_new * channel_new + j * channel_new + k] = max(
                                result[i * col_new * channel_new + j * channel_new + k],
                                data[(b + z) * col * channel + (c + q) * channel + k]);
                    }
                }
            }
        }
    }
    return result;
}
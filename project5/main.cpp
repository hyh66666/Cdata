#include <opencv2/opencv.hpp>
#include"face_binary_cls.cpp"
#include<algorithm>
#include<cmath>
#include<string>
#include<ctime>
using namespace std;
float c0 = 0, c1 = 0;

float *ConvBNReLU(int col, int channel, int row, const float *data, conv_param conv_params);

float *padMatrix(const float *matrix, int col,int channels, int row, int col_new, int row_new);

float *Maxpool(int size, int step, int col, int row, int channel, float *data);

void FC(float fc0_weight[], float fc0_bias[], float *data);


void loadData(const string &file_path, cv::Mat &out);


int main() {

    double cost;
    time_t begin,end;
    begin=clock();

    // BGR->RGB
    string s="./lgb.jpg";
    cv::Mat img;
    loadData(s,img);// auto release memory
    float* data=(float*)img.data;


    // pad=1, fill with 0, 128->130
    float *data_new = padMatrix(data, img.cols , img.channels(), img.rows,
                                (img.cols + 2 * conv_params[0].pad) ,
                                img.rows + 2 * conv_params[0].pad);

    // 130->64,channels=16
    float *data_new_conv = ConvBNReLU((img.cols + 2 * conv_params[0].pad), img.channels(),
                                      img.rows + 2 * conv_params[0].pad, data_new, conv_params[0]);

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
    float *data_new1_conv2 = ConvBNReLU(data_new_pool1_col + 2 * conv_params[2].pad, data_new_pool1_channels,
                                       data_new_pool1_row + 2 * conv_params[2].pad, data_new1, conv_params[2]);


    FC(fc0_weight, fc0_bias, data_new1_conv2);

    float face = exp(c1) / (exp(c0) + exp(c1));// 人脸的概率
    float noface = exp(c0) / (exp(c0) + exp(c1)); // 不是人脸的概率

    cout<<"c0:"<<c0<<"   c1:"<<c1<<endl;

    cout << "是人脸的概率:" << setprecision(12)<<face << endl << "不是人脸的概率:" <<setprecision(12)<< noface << endl;

    // free memory

    // free(data);
    free(data_new);
    free(data_new_conv);
    free(data_new_pool);
    free(data_new_conv1);
    free(data_new_pool1);
    free(data_new1);
    free(data_new1_conv2);

    end=clock();
    cost=(double)(end-begin)/CLOCKS_PER_SEC;
    cout<<"time:"<<cost<<endl;
    return 0;
}

//Full connection


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

   c0 += fc0_bias[0];

   for(int i=0;i<32;i++){
       for(int j=0;j<8;j++){
           for(int k=0;k<8;k++){
               c1+=data[j*8*32+k*32+i]*fc0_weight[index];
               index++;
           }
       }
   }


   c1 += fc0_bias[1];
}

// void FC(float *fc0_weight, float *fc0_bias, float *data) {
//     float flatten[2048];
//     int cnt = 0;
//     for (int chs = 0; chs < 32; ++chs) {
//         for (int row = 0; row < 8; ++row) {
//             for (int col = 0; col < 8; ++col) {
//                 int idx = row * 8 * 32 + col * 32 + chs;
//                 flatten[cnt] = data[idx];
//                 cnt++;
//             }
//         }
//     }
//     data = flatten;
//     for (int i = 0; i < 2048; i++) {
//         c0 += fc0_weight[i] * data[i];
//     }
//     c0 += fc0_bias[0];
//     for (int i = 2048; i < 4096; i++) {
//         c1 += fc0_weight[i] * data[i - 2048];
//     }
//     c1 += fc0_bias[1];
// }

    // BGR->RGB
void loadData(const string &file_path, cv::Mat &out) {
        cv::Mat img = cv::imread(file_path);

        cv::Mat imgRGB;
        cv::cvtColor(img, imgRGB, cv::COLOR_BGR2RGB);

        cv::Mat imgRGBf;
        imgRGB.convertTo(imgRGBf, CV_32FC3);
        out = imgRGBf / 256;
    }

// fill with 0
float *padMatrix(const float *matrix, int col,int channels,int row, int col_new, int row_new) {
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
float *ConvBNReLU(int col, int channel, int row, const float *data, conv_param conv_params) {
    int in_channels = conv_params.in_channels, out_channels = conv_params.out_channels, 
    kernel_size = conv_params.kernel_size, stride = conv_params.stride;
    int result_col = (col - kernel_size) / stride + 1;// don't include channels
    int result_row = (row - kernel_size) / stride + 1;
    float *kernel_oi = (float *) malloc(sizeof(float) * kernel_size * kernel_size);
    float *result = (float *) malloc(sizeof(float) * result_col * result_row * out_channels);
    for (int o = 0; o < out_channels; ++o) {
        float bias_oi = conv_params.p_bias[o];
        for (int j = 0,start_row=0; j < result_row; j++, start_row+=stride) {

            for (int k = 0,start_col=0; k < result_col; k++, start_col+=stride) {
                int temp=j * result_col * out_channels + k * out_channels + o;
                result[temp] = 0;

                for (int i = 0; i < in_channels; ++i) {
                    int kidx=o * (in_channels * 3 * 3) + i * (3 * 3);
                    // 存储卷积核权重
                    for (int a = 0; a < kernel_size * kernel_size; a++) {
                        kernel_oi[a] = conv_params.p_weight[kidx + a];
                    }

                    for (int z = 0; z < kernel_size; z++) {
                        for (int q = 0; q < kernel_size; q++) {

                            result[temp] +=
                                    data[(start_row + z) * col * channel + (start_col + q) * channel + i] *
                                    kernel_oi[z * kernel_size + q];
                        }
                    }

                }
                result[temp] += bias_oi;
                if (result[temp] < 0) {
                    result[temp] = 0;
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
    float *result = (float *) malloc(sizeof(float) * col_new * row_new * channel_new);
    for (int k = 0; k < channel_new; k++) {
        for (int i = 0,start_row=0; i < row_new; i++,start_row+=step) {


            for (int j = 0,start_col=0; j < col_new; j++,start_col+=step) {
                float max_value = FLT_MIN;

                for (int z = 0; z < size; z++) {
                    for (int q = 0; q < size; q++) {
                        max_value = max(max_value,
                                        data[(start_row + z) * col * channel + (start_col + q) * channel + k]);
                    }
                }
                result[i*col_new*channel_new+j*channel_new+k]=max_value;
            }
        }
    }
    return result;
}
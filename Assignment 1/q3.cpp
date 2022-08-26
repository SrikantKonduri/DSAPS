#include <iostream>
#include <fstream>

using namespace std;

int findXcomp(int ***temp,int i,int j,int rows,int cols){
    int r,g,b;
    if(j > 0 && j < cols-1){
        r = temp[i][j-1][0] - temp[i][j+1][0];
        g = temp[i][j-1][1] - temp[i][j+1][1];
        b = temp[i][j-1][2] - temp[i][j+1][2];
    }
    else if(j == 0){
        r = temp[i][cols-1][0] - temp[i][j+1][0];
        g = temp[i][cols-1][1] - temp[i][j+1][1];
        b = temp[i][cols-1][2] - temp[i][j+1][2];
    }
    else{
        r = temp[i][0][0] - temp[i][j-1][0];
        g = temp[i][0][1] - temp[i][j-1][1];
        b = temp[i][0][2] - temp[i][j-1][2];
    }
    return r*r + g*g + b*b;
}

int findYComp(int ***temp,int i,int j,int rows,int cols){
    int r,g,b;
    if(i > 0 && i < rows-1){
        r = temp[i-1][j][0] - temp[i+1][j][0];
        g = temp[i-1][j][1] - temp[i+1][j][1];
        b = temp[i-1][j][2] - temp[i+1][j][2];
    }
    else if(i == 0){
        r = temp[rows-1][j][0] - temp[i+1][j][0];
        g = temp[rows-1][j][1] - temp[i+1][j][1];
        b = temp[rows-1][j][2] - temp[i+1][j][2];
    }
    else{
        r = temp[0][j][0] - temp[i-1][j][0];
        g = temp[0][j][1] - temp[i-1][j][1];
        b = temp[0][j][2] - temp[i-1][j][2];
    }
    return r*r + g*g + b*b;
}

void findGradient(int ***temp,int **gradient,int H,int W,int h,int w){
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            int x_comp = findXcomp(temp,i,j,h,w);
            int y_comp = findYComp(temp,i,j,h,w);
            gradient[i][j] = x_comp + y_comp;
        }
    }
}

int findVerticalMin(int **gradient,int **costmatrix,int i,int j,int h,int w){
    if(j == 0){
        return gradient[i][j] + min(costmatrix[i-1][j],costmatrix[i-1][j+1]);
    }
    else if(j == w-1){
        return gradient[i][j] + min(costmatrix[i-1][j],costmatrix[i-1][j-1]);
    }
    return gradient[i][j] + min(min(costmatrix[i-1][j],costmatrix[i-1][j-1]),costmatrix[i-1][j+1]);
}

void shiftLeft(int ***rgb,int row,int col,int h,int w){
    for(int j=col;j<w;j++){
        if(j+1 < w){
            rgb[row][j][0] = rgb[row][j+1][0];
            rgb[row][j][1] = rgb[row][j+1][1];
            rgb[row][j][2] = rgb[row][j+1][2];
        }
    }
}

void verticalSeamCarve(int ***rgb,int **gradient,int h,int w){
    int **costmatrix;
    costmatrix = new int *[h];
    for(int i=0;i<h;i++){
        costmatrix[i] = new int[w];
    }
    // Computing cost matrix
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            if(i == 0){
                costmatrix[i][j] = gradient[i][j];
            }
            else{
                costmatrix[i][j] = findVerticalMin(gradient,costmatrix,i,j,h,w);
            }
        }
    }
    
    for(int i=0,j=0,min=0;i<h;i++){
        if(i == 0){
            for(j=1;j<w;j++){
                if(costmatrix[i][j] < costmatrix[i][min]){
                    min = j;
                }
            }
        }
        else{
            int left,right,down;
            down = costmatrix[i][min];
            if(min > 0 && min < w-1){
                left = costmatrix[i][min-1];
                right = costmatrix[i][min+1];
                if(left < down){
                    if(left < right){
                        min = min - 1;
                    }
                    else{
                        min = min + 1;
                    }
                }
                else if(right < down){
                    min = min + 1;                    
                }
            }
            else if(min == 0){
                right = costmatrix[i][min+1];
                if(right < down){
                    min = min + 1;
                }
            }
            else{
                left = costmatrix[i][min-1];
                if(left < down){
                    min = min - 1;
                }
            }
        }
        shiftLeft(rgb,i,min,h,w);
    }

}

int findHorizontalMin(int **gradient,int **costmatrix,int i,int j,int h,int w){
    if(i == 0){
        return gradient[i][j] + min(costmatrix[i][j-1],costmatrix[i+1][j-1]);        
    }
    else if(i == h-1){
        return gradient[i][j] + min(costmatrix[i][j-1],costmatrix[i-1][j-1]);
    }
    return gradient[i][j] + min(min(costmatrix[i-1][j-1],costmatrix[i][j-1]),costmatrix[i+1][j-1]);
}

void shiftUp(int ***rgb,int row,int col,int h,int w){
    for(int i=row;i<h;i++){
        if(i+1 < h){
            rgb[i][col][0] = rgb[i+1][col][0];
            rgb[i][col][1] = rgb[i+1][col][1];
            rgb[i][col][2] = rgb[i+1][col][2];
        }
    }
}

void horizontalSeamCarve(int ***rgb,int **gradient,int h,int w){
    int **costmatrix;
    costmatrix = new int *[h];
    for(int i=0;i<h;i++){
        costmatrix[i] = new int[w];
    }
    
    // Computing horizontal cost matrix
    for(int j=0;j<w;j++){
        for(int i=0;i<h;i++){
            if(j == 0){
                costmatrix[i][j] = gradient[i][j];
            }
            else{
                costmatrix[i][j] = findHorizontalMin(gradient,costmatrix,i,j,h,w);
            }
        }
    }

    for(int i=0,j=0,min=0;j<w;j++){
        if(j == 0){
            for(i=1;i<h;i++){
                if(costmatrix[i][j] < costmatrix[min][j]){
                    min = i;
                }
            }
        }
        else{
            int right,down,up;
            right = costmatrix[min][j];
            if(min == 0){
                down = costmatrix[min+1][j];
                if(down < right){
                    min = min + 1;
                }    
            }
            else if(min == h-1){
                up = costmatrix[min-1][j];
                if(up < right){
                    min = min - 1;
                }
            }
            else{
                down = costmatrix[min+1][j];
                up = costmatrix[min-1][j];
                if(right < down){
                    if(up < right){
                        min = min - 1;
                    }
                }
                else{
                    if(down < up){
                        min = min + 1;
                    }
                    else{
                        min = min - 1;
                    }
                }
            }
        }
        shiftUp(rgb,min,j,h,w);
    }

}

void solve(int ***rgb, int H, int W, int C, int H_, int W_, int C_) {
    
    int ***temp;
    temp = new int **[H];
    int **gradient;
    int h=H,w=W;
    
    // Initializing 2D gradient Array
    gradient = new int *[H];
    for(int i=0;i<H;i++){
        gradient[i] = new int[W];
    }

    int width_todecrease = W - W_;
    int height_todecrease = H - H_;
    int print = 1;


    while(width_todecrease != 0){
        findGradient(rgb,gradient,H,W,h,w);
        verticalSeamCarve(rgb,gradient,h,w);
        w--;
        width_todecrease--;
    }

    while(height_todecrease != 0){
        findGradient(rgb,gradient,H,W,h,w);
        horizontalSeamCarve(rgb,gradient,h,w);
        h--;
        height_todecrease--;
    }

}


int main() {
    string ip_dir = "./data/input/";
    string ip_file = "rgb_in.txt";
    ifstream fin(ip_dir + ip_file);

    int H, W, C;
    fin >> H >> W >> C;

    int ***rgb;
    rgb = new int **[H];
    for(int i = 0; i < H; ++i) {
        rgb[i] = new int *[W];
        for(int j = 0; j < W; ++j) {
            rgb[i][j] = new int[C];
            for(int k = 0; k < C; ++k)
                fin >> rgb[i][j][k];
        }
    }
    fin.close();

    int H_, W_, C_;
    cout << "Enter new value for H (must be less than " << H << "): ";
    cin >> H_;
    cout << "Enter new value for W (must be less than " << W << "): ";
    cin >> W_;
    cout << '\n';
    C_ = C;

    solve(rgb, H, W, C, H_, W_, C_);

    string op_dir = "./data/output/";
    string op_file = "rgb_out.txt";
    ofstream fout(op_dir + op_file);
    
    fout << H_ << " " << W_ << " " << C_ << endl;
    for(int i = 0; i < H_; ++i) {
        for(int j = 0; j < W_; ++j) {
            for(int k = 0; k < C_; ++k) {
                fout << rgb[i][j][k] << " ";
            }
        }
        fout << '\n';
    }
    fout.close();

    return 0;
}

#include<iostream>
#include<graphics.h>

using namespace std;

//Xác định mã miền TBRL
const int INSIDE=0;//0000
const int LEFT=1;//0001
const int RIGHT=2;//0010
const int BOTTOM=4;//0100
const int TOP=8;//1000

//Xác định x_min,y_min,x_max,y_max cho cửa sổ xén tỉa. Bởi vì
//những điểm chéo là đủ để xác định một cửa sổ hình chữ nhật
static int x_min,y_min,x_max,y_max;
//Hàm để tính toán mã miền cho một điểm tọa độ (x,y)
int computeCode(int x,int y){
    //Khởi tạo mã miền như là nằm trong cửa sổ
    int code=INSIDE;

    if(x<x_min)//ở bên trái của cửa sổ
        code=LEFT;
    else if(x>x_max)//ở bên phải của cửa sổ
        code=RIGHT;
    if(y<y_min)//ở bên dưới của cửa sổ
        code=BOTTOM;
    else if(y>y_max)//ở bên trên cửa sổ
        code=TOP;

    return code;//Đúng xét theo thứ tự TBRL

}
//Sử dụng thuật toán Cohen-Sutherland để xén tỉa một đoạn thẳng
//từ P1=(x1,y1) tới P2=(x2,y2)
void Cohen_Sutherland_clipping(int x1,int y1,int x2,int y2){
    //Xác định mã miền của hai điểm P1 và P2
    int code1=computeCode(x1,y1);
    int code2=computeCode(x2,y2);

    //Giả sử rằng đoạn thẳng là nằm ngoài của cửa sổ xén tỉa
    bool OK=false;
    while(true){
        if((code1==0)&&(code2==0)){
            //Nếu cả hai đầu mút nằm trong cứa sổ xén tỉa
            OK=true;
            break;
        }
        else if(code1==code2){
            //Nếu cả hai đầu mút nằm ngoài cửa sổ xén tỉa,
            //trong cùng một vùng
            break;
        }
        else{
            //Một đoạn của đoạn thẳng nằm trong cửa sổ xén tỉa
            int code_out;
            int x,y;

            //Ít nhất một điểm là nằm ngoài cửa sổ, lấy nó
            if(code1!=0){
                code_out=code1;
            }else{
                code_out=code2;
            }
            //Tìm giao điểm với cạnh cửa sổ xén tỉa
            if(code_out==TOP){
                //điểm nằm trên cửa sổ xén tỉa
                x=x1+(x2-x1)*(y_max-y1)/(y2-y1);
                y=y_max;
            }else if(code_out==BOTTOM){
                //điểm nằm dưới cửa sổ xén tỉa
                x=x1+(x2-x1)*(y_min-y1)/(y2-y1);
                y=y_min;
            }else if(code_out==RIGHT){
                //điểm nằm bên phải cửa sổ xén tỉa
                y=(y2-y1)*(x_max-x1)/(x2-x1)+y1;
                x=x_max;
            }else if(code_out==LEFT){
                //điểm nằm bên trái cửa sổ xén tỉa
                y=(y2-y1)*(x_min-x1)/(x2-x1)+y1;
                x=x_min;
            }

            //Bây giờ giao điểm x,y đã được tìm thấy
            //Chúng ta sẽ thay thế điểm nằm ngoài cửa sổ bởi giao điểm này
            if(code_out==code1){
                x1=x;
                y1=y;
                code1=computeCode(x1,y1);
            }
            else{
                x2=x;
                y2=y;
                code2=computeCode(x2,y2);
            }
        }
    }
    if(OK){
        cout<<"Doan thang bi cat xen tu "<<x1<<","<<y1
        <<" den "<<x2<<","<<y2<<endl;
        cout<<"Sau khi cat xen ta duoc doan thang mau trang nhu sau: ";
        setcolor(WHITE);
        line(x1,y1,x2,y2);

    }else{
        cout<<"Doan thang nam ngoai cua so. Khong bi cat xen";
    }
}
int main()
{
    initwindow(1000,1000);
    setcolor(BLUE);
    cout<<"Nhap vao x_min,y_min,x_max,y_max cho cua so xen tia: ";
    cin>>x_min>>y_min>>x_max>>y_max;
    rectangle(x_min,y_min,x_max,y_max);
    int x1,y1,x2,y2;
    cout<<"Nhap vao toa do P1(x1,y1) va P2(x2,y2) cua doan thang can xen tia: ";
    cin>>x1>>y1>>x2>>y2;
    line(x1,y1,x2,y2);
    Cohen_Sutherland_clipping(x1,y1,x2,y2);
    getch();
    return 0;
}

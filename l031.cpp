#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <time.h>  
#include <math.h>
#include <fstream>
#include "iomanip"
#include <list>
#include <iterator>
#include "algorithm"
#include "cstring"

using namespace std;

class Draw{
    public:
        string (*grid)[800];
        Draw(string (*g)[800]){
            grid = g;
        }

        string (*circle(double x, double y, int radius, string color))[800]{
            int xcenter = (int) (x*800);
            int ycenter = (int) (y*800);
            int ym = radius;
            int xm = 0;
            int dm = 3 - (2*radius);
            if(xcenter+xm<800){
                if(ycenter+ym<800){
                    grid[xcenter+xm][ycenter +ym] = color;
                }
                if(ycenter-ym>=0){
                    grid[xcenter+xm][ycenter -ym] = color; 
                }
            }
            if(xcenter-xm>0){
                if(ycenter+ym<800){
                    grid[xcenter-xm][ycenter+ym] = color;
                }
                if(ycenter-ym>=0){
                    grid[xcenter-xm][ycenter -ym] = color;
                }
            }

            if(xcenter+ym<800){
                if(ycenter+xm<800){
                    grid[xcenter+ym][ycenter +xm] = color;
                }
                if(ycenter-xm>=0){
                    grid[xcenter+ym][ycenter -xm] = color; 
                }
            }
            if(xcenter-ym>0){
                if(ycenter+xm<800){
                    grid[xcenter-ym][ycenter+xm] = color;
                }
                if(ycenter-xm>=0){
                    grid[xcenter-ym][ycenter -xm] = color;
                }
            }
            while(ym>=xm){
                xm++;
                if(dm>0){
                    ym--;
                    dm= dm+ 4*(xm-ym) + 10;
                }else{
                    dm = dm+(4*xm)+6;
                }
                if(xcenter+xm<800){
                    if(ycenter+ym<800){
                        grid[xcenter+xm][ycenter +ym] = color;
                        }
                    if(ycenter-ym>=0){
                        grid[xcenter+xm][ycenter -ym] = color; 
                        }
                }
                if(xcenter-xm>0){
                    if(ycenter+ym<800){
                        grid[xcenter-xm][ycenter+ym] = color;
                        }
                    if(ycenter-ym>=0){
                        grid[xcenter-xm][ycenter -ym] = color;
                        }
                }

                if(xcenter+ym<800){
                    if(ycenter+xm<800){
                        grid[xcenter+ym][ycenter +xm] = color;
                        }
                    if(ycenter-xm>0){
                        grid[xcenter+ym][ycenter -xm] = color; 
                        }
                }
                if(xcenter-ym>0){
                    if(ycenter+xm<800){
                        grid[xcenter-ym][ycenter+xm] = color;
                        }
                    if(ycenter-xm>=0){
                        grid[xcenter-ym][ycenter -xm] = color;
                        }
                }
            }
            return grid;
        }


        string (*plotpoints(list <pair<double,double>> l, pair<double,double> point1, pair<double,double> point2))[800]{
            list <pair<double,double>>::iterator it;
            for(it = l.begin(); it!=l.end(); it++){
                int x = (int) ((*it).first*800);
                int y = (int) ((*it).second*800);
                grid[x][y] = "0 0 0 ";
                grid = circle((*it).first, (*it).second, 3, "0 0 0 ");
            }
            int x = (int) (point1.first*800);
            int y = (int) (point1.second*800);
            int x2 = (int) (point2.first*800);
            int y2 = (int) (point2.second*800);
            grid[x][y] = "1 0 0 ";
            grid[x2][y2] = "1 0 0 ";
            grid = circle(point1.first, point1.second, 3, "1 0 0 ");
            grid = circle(point1.first, point1.second, 2, "1 0 0 ");
            grid = circle(point2.first, point2.second, 3, "1 0 0 ");
            grid = circle(point2.first, point2.second, 2, "1 0 0 ");

            return grid;
        }
};

class Lab03{
    public:
        list <pair<double,double>> k; 
        string (*grid)[800] = new string[800][800];
        pair<double,double> p1;
        pair<double,double> p2;
    
    void init(){
        for(int i =0; i<800;i++){
            for(int k = 0; k<800;k++){
                grid[i][k] ="1 1 1 ";
            }
        }
    }
    void genrand(){
        
        for(int i =0; i<60; i++){
            double x = (double)rand() / (double)RAND_MAX;
            double y = (double)rand() / (double)RAND_MAX;
            k.push_back(make_pair(x,y));
        }
    }

    double distance(double firstx, double firsty, double secondx, double secondy){
        return sqrt(pow(firstx-secondx,2)+pow(firsty-secondy,2));
    }
    void writetext(){
        list <pair<double,double>>::iterator it;
        ofstream ofs;
        ofs.open("points.txt");
        for(it = k.begin(); it!=k.end(); it++){
            ofs<<fixed<<setprecision(23)<<(*it).first<<"  "<< (*it).second<<endl;
        }
    }
    void writearr(){
        ofstream ofs;
        ofs.open("points.ppm");
        ofs << "P3" << endl << 800 << " " << 800 << endl << "1" << endl;
        for (int i = 0; i<800; ++i){
            for (int k = 0; k<800; ++k){
                ofs << grid[k][i];
            }
            ofs << "\n";
        }
        ofs.close();
    }

    void closestbrute(){

        list <pair<double,double>>::iterator i;
        int counter = 1;
        double mindist = 3;
        for(i=k.begin(); i!=k.end(); i++){
            list <pair<double,double>>::iterator m = k.begin();
            advance(m, counter);
            while(m!=k.end()){
                pair<double,double> a = (*i);
                pair<double,double> b = (*m);
                double d = distance(a.first, a.second, b.first, b.second);
                if(d<mindist){
                    mindist =d;
                    p1 = a;
                    p2 = b;
                }
                m++;
            }
            counter++;
        }
    }

    void part1(){
        init();
        genrand();
        closestbrute();
        Draw d = Draw(grid);
        grid = d.plotpoints(k, p1, p2);
        writearr();
        writetext();
    }
};

int main(){
    srand(time(0)); 
    Lab03 l;
    l.part1();
    l.writearr();
    l.writetext();
}

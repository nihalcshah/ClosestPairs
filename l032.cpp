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

// class Point{
//     public:
//         double first;
//         double second;
//         double dist;
// }

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
        vector <pair<double,double>> v;
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
            v.push_back(make_pair(x,y));
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

    vector<string> splitstring(string str, char delimeter, vector<string> outputstring){
        size_t start;
        size_t end = 0;
    
        while (( start = str.find_first_not_of(delimeter, end)) != std::string::npos)
        {
            end = str.find(delimeter, start);
            outputstring.push_back(str.substr(start, end - start));
        }
        return outputstring;
    }
    void readtext(){
        ifstream file ("points.txt");
        string l;
        if (file.is_open()){
            while(getline (file,l)){
                vector<string> o;
                vector<string> m = splitstring(l, ' ', o);
                v.push_back(make_pair(stod(m[0]),stod(m[1])));
                k.push_back(make_pair(stod(m[0]),stod(m[1])));
            }
            file.close();
        }
    }
    // void 
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

    tuple<double, pair<double, double>, pair<double, double>> ms(int start, int end){
        // if(start == 39 || end ==39){
        //     cout<<"p"<<endl;
        // }
        if(end-start==1){
            double d = distance(v[start].first, v[start].second, v[end].first, v[end].second);
            return make_tuple(d, v[start], v[end]);
        }
        if(end-start==2){
            double d = distance(v[start].first, v[start].second, v[start+1].first, v[start+1].second);
            double d2 = distance(v[start].first, v[start].second, v[end].first, v[end].second);
            double d3 = distance(v[start+1].first, v[start+1].second, v[end].first, v[end].second);
            if(d3<d&&d3<d2){
                return make_tuple(d, v[start+1], v[end]);
            }
            if(d2<d&&d2<d3){
                return make_tuple(d, v[start], v[end]);
            }
            return make_tuple(d, v[start], v[start+1]);
        }
        int mid = (int) (start+end)/2;
        tuple<double, pair<double, double>, pair<double, double>> beg = ms(start, mid);
        tuple<double, pair<double, double>, pair<double, double>> en = ms(mid+1, end);
        tuple<double, pair<double, double>, pair<double, double>> target;
        double mind;
        if(get<0>(beg) < get<0>(en)){
            mind = get<0>(beg);
            target = beg;
        }else{
            mind = get<0>(en);
            target = en;
        }
        double lthresh = v[mid].first-mind;
        double rthresh = v[mid].first+mind;
        int midindex;
        for(midindex = mid;midindex>=0;midindex--){
            if(v[midindex].first<=lthresh){
                break;
            }
        }
        int maxindex;
        for(maxindex = mid;maxindex<v.size();maxindex++){
            if(v[maxindex].first>=rthresh){
                break;
            }
        }
        for(int i = midindex; i <=mid; i++){
            for(int l = maxindex; l>mid; l--){
                double dis = distance(v[l].first, v[l].second, v[i].first, v[i].second);
                if(dis<mind){
                    target = make_tuple(dis, v[l], v[i]);
                }
            }  
        }
        return target;
    }

    void part1(){
        // init();
        // genrand();
        // readtext();
        closestbrute();
        Draw d = Draw(grid);
        grid = d.plotpoints(k, p1, p2);
    }
    void part2(){
        // init();
        // genrand();
        // readtext();
        sort(v.begin(), v.end());
        tuple<double, pair<double, double>, pair<double, double>> t = ms(0, v.size()-1);
        p1 = get<1>(t);
        p2 = get<2>(t);
        Draw d = Draw(grid);
        grid = d.plotpoints(k, p1, p2);
    }
};

int main(){
    srand(time(0)); 
    Lab03 l;
    l.init();
    // l.genrand();
    l.readtext();
    l.part1();
    cout<<"p1: ("<<l.p1.first<<", "<<l.p1.second<<") p2: ("<<l.p2.first<<", "<<l.p2.second<<")"<<endl;
    l.part2();
    cout<<"p1: ("<<l.p1.first<<", "<<l.p1.second<<") p2: ("<<l.p2.first<<", "<<l.p2.second<<")"<<endl;
    l.writearr();
    // l.writetext();
}

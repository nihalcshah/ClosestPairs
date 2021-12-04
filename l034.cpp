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
#include <unordered_map>
#include <chrono> 

using namespace std;
using namespace std::chrono;


class Point{
    public:
        double first;
        double second;
        Point(double x, double y){
            first = x;
            second = y;
        }
        ~Point(){}
        bool operator==(const Point& p) const
        {
            return first == p.first && second == p.second;
        }
};



// class Mhash {
// public:
 
//     // Use sum of lengths of first and last names
//     // as hash function.
//     size_t operator()(const pair<unsigned long long int, unsigned long long int>& p) const
//     {
//         return (hash<unsigned long long int>()(p.first)) ^
//                (hash<unsigned long long int>()(p.second));
//     }
// };

struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const
    {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);
        return hash1 ^ hash2;
    }
};

class TwoPoints{
    public:
        Point first = Point(0,0);
        Point second = Point(0,0);
        double dist;
        TwoPoints( double d,Point x, Point y){
            first = x;
            second = y;
            dist = d;
        }
};

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
        tuple<double, pair<double, double>, pair<double, double>> brute;
        tuple<double, pair<double, double>, pair<double, double>> merge;
        TwoPoints rec = TwoPoints(0,Point(0,0), Point(0,0));
        vector <Point> r;
        unordered_map<pair<unsigned long long int,unsigned long long int>, Point, hash_pair> dict;
        TwoPoints opoints = TwoPoints(0,Point(0,0), Point(0,0));
        vector <Point> o;
        int t1=0;
        int t2=0;
        int t3=0;
    
    void init(){
        for(int i =0; i<800;i++){
            for(int k = 0; k<800;k++){
                grid[i][k] ="1 1 1 ";
            }
        }
    }
    void genrand(){
        
        for(int i =0; i<10000000; i++){
            double x = (double)rand() / (double)RAND_MAX;
            double y = (double)rand() / (double)RAND_MAX;
            v.push_back(make_pair(x,y));
            // k.push_back(make_pair(x,y));
            r.push_back(Point(x,y));
            o.push_back(Point(x,y));

        }
    }
    static bool sortx(Point x, Point y){
        return x.first < y.first;
    }
    static bool sorty(Point x, Point y){
        return x.second < y.second;
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
        ifstream file ("points100k.txt");
        string l;
        if (file.is_open()){
            while(getline (file,l)){
                vector<string> j;
                vector<string> m = splitstring(l, ' ', j);
                v.push_back(make_pair(stod(m[0]),stod(m[1])));
                r.push_back(Point(stod(m[0]),stod(m[1])));
                k.push_back(make_pair(stod(m[0]),stod(m[1])));
                o.push_back(Point(stod(m[0]),stod(m[1])));

            }
            file.close();
        }
    }
    // void 11
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
        // ofs.open("output.txt");
        // ofs<<fixed<<setprecision(23)<<"("<< get<1>(brute).first <<", "<< get<1>(brute).second<<") "<<"("<<get<2>(brute).first<<", "<< get<2>(brute).second<<") Dist: "<< get<0>(brute) <<endl;
        // ofs<<fixed<<setprecision(23)<<"("<< get<1>(merge).first <<", "<< get<1>(merge).second<<") "<<"("<<get<2>(merge).first<<", "<< get<2>(merge).second<<") Dist: "<< get<0>(merge) <<endl;
        // ofs.close();
    }

    void closestbrute(){

        list <pair<double,double>>::iterator i;
        pair<double,double> p1;
        pair<double,double> p2;
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
        brute = make_tuple(mindist, p1, p2);
    }
    // unordered_map<pair<unsigned long long int,unsigned long long int>, Point, Mhash> makedict(double delta, Point p1){
    //     unordered_map<Point, Point, Mhash> dict;
    //     pair<unsigned long long int,unsigned long long int> p1p = make_pair(p1.first/(delta/2),p1.second/(delta/2));
    //     for 
    // }
    tuple<double, pair<double, double>, pair<double, double>> ms(int start, int end){
        // if(start == 39 || end ==39){
        //     cout<<"p"<<endl;
        // }
        if(end-start==1){
            double d = distance(v[start].first, v[start].second, v[end].first, v[end].second);
            // if(abs(v[start].first-0.1225)<=0.002 && v[start].first>0.1225){
            //     cout<<"m"<<endl;
            // }
            return make_tuple(d, v[start], v[end]);
        }
        if(end-start==2){
            // if(abs(v[end].first-0.12)<=0.002){
            //     cout<<"m"<<endl;
            // }
            double d = distance(v[start].first, v[start].second, v[start+1].first, v[start+1].second);
            double d2 = distance(v[start].first, v[start].second, v[end].first, v[end].second);
            double d3 = distance(v[start+1].first, v[start+1].second, v[end].first, v[end].second);
            if(d3<d&&d3<d2){
                return make_tuple(d3, v[start+1], v[end]);
            }
            if(d2<d&&d2<d3){
                return make_tuple(d2, v[start], v[end]);
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
        // if(abs(get<2>(target).first-0.1225)<=0.002){
        //     cout<<get<2>(target).first<<endl;
        // }
        double lthresh = v[mid].first-mind;
        double rthresh = v[mid].first+mind;
        int midindex;
        for(midindex = mid;midindex>=start;midindex--){
            if(v[midindex].first<=lthresh){
                break;
            }
        }
        midindex++;
        int maxindex;
        for(maxindex = mid;maxindex<=end;maxindex++){
            if(v[maxindex].first>=rthresh){
                break;
            }
        }
        maxindex--;
        for(int i = midindex; i <=mid; i++){
            for(int l = maxindex; l>mid; l--){
                double dis = distance(v[l].first, v[l].second, v[i].first, v[i].second);
                if(dis<mind){
                    target = make_tuple(dis, v[l], v[i]);
                    mind = dis;
                }
            }  
        }
        return target;
    }

    TwoPoints rms(int start, int end){
        // if(start == 39 || end ==39){
        //     cout<<"p"<<endl;
        // }
        if(end-start==1){
            double d = distance(r[start].first, r[start].second, r[end].first, r[end].second);
            // if(abs(v[start].first-0.1225)<=0.002 && v[start].first>0.1225){
            //     cout<<"m"<<endl;
            // }
            return TwoPoints(d, r[start], r[end]);
        }
        if(end-start==2){
            // if(abs(v[end].first-0.12)<=0.002){
            //     cout<<"m"<<endl;
            // }
            double d = distance(r[start].first, r[start].second, r[start+1].first, r[start+1].second);
            double d2 = distance(r[start].first, r[start].second, r[end].first, r[end].second);
            double d3 = distance(r[start+1].first, r[start+1].second, r[end].first, r[end].second);
            if(d3<d&&d3<d2){
                return TwoPoints(d3, r[start+1], r[end]);
            }
            if(d2<d&&d2<d3){
                return TwoPoints(d2, r[start], r[end]);
            }
            return TwoPoints(d, r[start], r[start+1]);
        }
        int mid = (int) (start+end)/2;
        TwoPoints beg = rms(start, mid);
        TwoPoints en = rms(mid+1, end);
        TwoPoints target = TwoPoints(0, Point(0,0), Point(0,0));
        double mind;
        if(beg.dist < en.dist){
            mind = beg.dist;
            target = beg;
        }else{
            mind = en.dist;
            target = en;
        }
        // if(abs(get<2>(target).first-0.1225)<=0.002){
        //     cout<<get<2>(target).first<<endl;
        // }
        double lthresh = r[mid].first-mind;
        double rthresh = r[mid].first+mind;
        int midindex;
        for(midindex = mid;midindex>=start;midindex--){
            if(r[midindex].first<=lthresh){
                break;
            }
        }
        midindex++;
        int maxindex;
        for(maxindex = mid;maxindex<=end;maxindex++){
            if(r[maxindex].first>=rthresh){
                break;
            }
        }
        maxindex--;
        int ind = min(maxindex, (int)r.size()-1);
        // cout<<ind<<endl;
        vector<Point> sub;
        for(int i =midindex; i<=maxindex; i++){
            sub.push_back(r[i]);
        }
        sort(sub.begin(), sub.end(), sorty);
        Point a = Point(0,0);
        Point b = Point(0,0);
        for(int p = 0; p < sub.size(); p++){
            int l = min(p+3, (int)sub.size()-1);
            for(int k = p+1; k<=l; k++){
                double dis = distance(sub[p].first, sub[p].second, sub[k].first, sub[k].second);
                if(dis<mind){
                    target = TwoPoints(dis, sub[p], sub[k]);
                    mind = dis;
                }
            }
        }
        return target;
    }

    TwoPoints oms(){
        // unordered_map<Point, Point, > m;
        randomize();
        Point a = Point(0,0);
        Point b = Point(0,0);
        double delta = distance(o[0].first, o[0].second, o[1].first, o[1].second);
        for(int i =0; i<o.size(); i++){
            
            unsigned long long int fp = o[i].first/(delta/2);
            unsigned long long int sp = o[i].second/(delta/2);
            pair<unsigned long long int, unsigned long long int> p = pair<unsigned long long int, unsigned long long int>(fp, sp);
            // dict.insert(make_pair(p, o[i]));
            bool found = false;
            for(int j = -2; j<=2; j++){
                if(p.first+j>0){
                    for(int k = -2; k<=2; k++){
                        if(p.second+k>0){
                            //see if the new pair is in the map
                            pair<unsigned long long int, unsigned long long int> p2 = pair<unsigned long long int, unsigned long long int>(p.first+j, p.second+k);
                            if(dict.find(p2) != dict.end()){
                                Point point3 = dict.at(p2);
                                // cout<<point3.first<<" "<<point3.second<<endl;
                                // Point point3 = dict[p2];
                                // Point point3 = Point(0, 0);
                                double dist = distance(o[i].first, o[i].second, point3.first, point3.second);
                                if(dist<delta){
                                    a = o[i];
                                    b = point3;
                                    delta = dist;
                                    found = true;
                                    break;
                                }
                            }
                        }
                        // if(sp>0 && sp<=dict[fp].size()){
                        //     if(dict[fp][sp] == o[i]){
                        //         found = true;
                        //         break;
                        //     }
                        // }
                    }
                }  
            }
            if(found==true){
                dict.clear();
                for (int n =0; n<=i; n++){
                    fp = o[n].first/(delta/2);
                    sp = o[n].second/(delta/2);
                    pair<unsigned long long int, unsigned long long int> piter = pair<unsigned long long int, unsigned long long int>(fp, sp);
                    dict.insert(make_pair(piter, o[n]));
                }
            } else{
                dict.insert(make_pair(p, o[i]));
            }
        }
        return TwoPoints(delta, a, b);

    }

    void swap (Point *a, Point *b)
    {
        Point temp = *a;
        *a = *b;
        *b = temp;
    }

    void randomize()
    {
        srand (time(NULL));
        for (int i = o.size() - 1; i > 0; i--)
        {
            int j = rand() % (i + 1);
            swap(&o[i], &o[j]);
        }
    }

    void part1(){
        time_point<system_clock> start, end;
        start = high_resolution_clock::now();
        
        closestbrute();
        Draw d = Draw(grid);

        end = high_resolution_clock::now();
        auto elapsed = duration_cast<nanoseconds> (end-start);
        t1+=elapsed.count();
        // cout<< setprecision(17) << elapsed.count()  <<endl;
        ofstream ofs;
        ofs.open("output.txt", ios_base::app);
        ofs<<fixed<<setprecision(23)<<"("<< get<1>(brute).first <<", "<< get<1>(brute).second<<") "<<"("<<get<2>(brute).first<<", "<< get<2>(brute).second<<") Dist: "<< get<0>(brute)<<" Time(nanoseconds): "<< elapsed.count() <<endl;
        grid = d.plotpoints(k, get<1>(brute), get<2>(brute));
        ofs.close();
    }
    void part2(){   
        time_point<system_clock> start, end;
        start = high_resolution_clock::now();

        sort(v.begin(), v.end());
        merge = ms(0, v.size()-1);

        end = high_resolution_clock::now();
        auto elapsed = duration_cast<milliseconds> (end-start);
        t2+=elapsed.count();
        // cout<< setprecision(17) << elapsed.count()  <<endl;

        Draw d = Draw(grid);
        // grid = d.plotpoints(k, get<1>(merge), get<2>(merge));
        ofstream ofs;
        ofs.open("results.txt", ios_base::app);
        ofs<<fixed<<setprecision(23)<<"("<< get<1>(merge).first <<", "<< get<1>(merge).second<<") "<<"("<<get<2>(merge).first<<", "<< get<2>(merge).second<<") Dist: "<< get<0>(merge)<<" Time(milliseconds): "<< elapsed.count() <<endl;
        ofs.close();
    }
    
    void part3(){
        time_point<system_clock> start, end;
        start = high_resolution_clock::now();
        sort(r.begin(), r.end(), sortx);
        TwoPoints t = rms(0, v.size()-1);
        end = high_resolution_clock::now();
        auto elapsed = duration_cast<milliseconds> (end-start);
        t3+=elapsed.count();
        ofstream ofs;
        ofs.open("results.txt", ios_base::app);
        ofs<<fixed<<setprecision(23)<<"("<< t.first.first <<", "<< t.first.second<<") "<<"("<<t.second.first<<", "<< t.second.second<<") Dist: "<< t.dist<<" Time(milliseconds): "<< elapsed.count() <<endl;
        cout<<fixed<<setprecision(23)<<"("<< t.first.first <<", "<< t.first.second<<") "<<"("<<t.second.first<<", "<< t.second.second<<") Dist: "<< t.dist<<" Time(milliseconds): "<< elapsed.count() <<endl;
        ofs.close();

        
        Draw d = Draw(grid);
    }
    void part4(){
        // TwoPoints t = oms();
        time_point<system_clock> start, end;
        start = high_resolution_clock::now();
        // sort(r.begin(), r.end(), sortx);
        TwoPoints m = oms();
        end = high_resolution_clock::now();
        auto elapsed = duration_cast<milliseconds> (end-start);
        t3+=elapsed.count();
        ofstream ofs;
        ofs.open("results.txt", ios_base::app);
        ofs<<fixed<<setprecision(23)<<"("<< m.first.first <<", "<< m.first.second<<") "<<"("<<m.second.first<<", "<< m.second.second<<") Dist: "<< m.dist<<" Time(milliseconds): "<< elapsed.count() <<endl;
        cout<<fixed<<setprecision(23)<<"("<< m.first.first <<", "<< m.first.second<<") "<<"("<<m.second.first<<", "<< m.second.second<<") Dist: "<< m.dist<<" Time(milliseconds): "<< elapsed.count() <<endl;
        ofs.close();
    }
};

int main(){
    ofstream o;
    o.open("results.txt");
    o.clear();
    o.close();
    srand(time(0)); 
    Lab03 l;
    // l.init();
    
    l.readtext();
    using namespace std::chrono;
    // seconds sec()d
    // nan = nan*60;
    // l.genrand();
    // l.part1();
    // l.part2();
    l.part3();
    l.part4();
    // l.writearr();
    // l.writetext();
}

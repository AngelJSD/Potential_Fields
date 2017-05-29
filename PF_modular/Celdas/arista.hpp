#ifndef ARISTA_H
#define ARISTA_H

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class cArista{
	public:

		vector<float> x_vec, y_vec;

		cArista(float x1, float x2, float y1, float y2, float r){

		        float x_aux, y_aux;
		        float angle=atan2((y2-y1),(x2-x1));
			cout<<"angulito"<<angle<<endl;
		        float d = sqrt(pow(x1-x2,2)+pow(y1-y2,2));
			float m=(y2-y1)/(x2-x1);
		        x_vec.push_back(x1+r*cos(angle));
			cout<<"xini: "<<x1+r*cos(angle)<<endl;
		        y_vec.push_back(y1+r*sin(angle));
			cout<<"yini: "<<y1+r*sin(angle)<<endl;
		        float acum=r;
		        int it=0;
			while(acum<d){
					x_vec.push_back(x_vec[it]+r*2*cos(angle));
					cout<<"x  : "<<x_vec[it]+r*2*cos(angle)<<endl;
					y_vec.push_back(y_vec[it]+r*2*sin(angle));
					cout<<"y  : "<<y_vec[it]+r*2*sin(angle)<<endl;
					it++;
					acum+=r*2;
				}
		}
};

#endif
/*
int main(){

        float x1,y1,x2,y2,r;
        cin>>x1>>y1>>x2>>y2>>r;

        arista(x1,x2,	y1,y2,r);

        for(int i=0; i<x_vec.size(); ++i)
                cout<<x_vec[i]<<" ";

        cout<<endl;

        for(int i=0; i<y_vec.size(); ++i)
                cout<<y_vec[i]<<" ";

        return 0;

}*/

//
// Created by xiodine on 11/24/15.
//

#ifndef GEOMCOMP_ACTUAL_PROGRAM_H
#define GEOMCOMP_ACTUAL_PROGRAM_H

#include <vector>
#include "point.h"

class actual_program {
    std::vector<point> puncte;
    int isInsideVal;
public:
    actual_program();
    int sign_det(point a, point b, point c)
    {
        double det=a[0]*b[1]+b[0]*c[1]+a[1]*c[0];
        det=det-a[1]*b[0]-c[0]*b[1]-c[1]*a[0];
        if(det<0) return -1;
        if(det>0) return 1;
        return 0;
    }
    int isInside()
    {
        return isInsideVal;
    }
    void isInsideCalc()
    {
        int puncte_size = puncte.size();
        puncte_size--;
        point view_point =puncte[puncte_size];
        int zero_count=0, negative_count=0, positive_count=0;
        for (int i=0;i<puncte_size-1;i++)
        {
            int aux;
            if(i!=puncte_size-1)
            {
               aux = sign_det(puncte[i],puncte[i+1],view_point);
            }
            else
            {
                aux=sign_det(puncte[i],puncte[0],view_point);
            }
            if(aux==0) zero_count++;
            else if(aux==1) positive_count++;
            else negative_count++;
        }
        if(zero_count!=0&&((positive_count==0)||(negative_count==0)))
        {
            isInsideVal=0;
        }
        else if(zero_count==0&&(positive_count==0||negative_count==0))
        {
            isInsideVal=1;
        }
        //if(zero_count!=0&&positive_count!=0&&negative_count!=0) return -1;
         else isInsideVal=-1;
        return;

    };
};


#endif //GEOMCOMP_ACTUAL_PROGRAM_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
using namespace std;

struct point{//structure to define a point
    float x;
    float y;
};

float area(struct point &p1,struct point &p2,struct point &p3){//calculates area of three points,to give the turn direction
    float solution = p1.x * (p2.y - p3.y);
    solution += p2.x * (p3.y - p1.y);
    solution += p3.x * (p1.y - p2.y);
    return solution;
}

float find_median(vector <point> &st,int len,int start_index,int end_index){//find the x-value median point from the given set of points
    int i;
    struct point temp;
    vector <float> xmedian;
    int count = 0;
    for(i=start_index;i<end_index-2;i+=3){//for every 3 points in the point list,finding the median point and uploading the x-value of median pt of each partition
        if(st[i].x>st[i+1].x){//nth point and n+1th point comparision
            temp = st[i];
            st[i] = st[i+1];
            st[i+1] = temp;
        }
        if(st[i].x>st[i+2].x){//nth point and n+2th point comparision
            temp = st[i];
            st[i] = st[i+2];
            st[i+2] = temp;
        }
        if(st[i+1].x>st[i+2].x){//n+1th point and n+2th point comparision
            temp = st[i+1];
            st[i+1] = st[i+2];
            st[i+2] = temp;
        }
        xmedian.push_back(st[i+1].x);//push median of partition onto float vector
        count += 1;
    }
    sort(xmedian.begin(),xmedian.end());//sorting all partition medians
    float pivot = count%2 == 0?xmedian[(count/2)-1]:xmedian[(count/2)];//pivot is the current median of medians
    int lcount = 0;
    int gcount = 0;
    for(i=0;i<len;i+=1){
        if(st[i].x<=pivot){
            lcount++;//for finding number of points with x-value less than pivot
        }
        if(st[i].x>pivot){
            gcount++;//for finding number of points with x-value greater than pivot
        }
    }
    int check = len%2==0?(len/2)-1:(len/2);//true median position
    if (lcount-1== check){//true median case
        return pivot;
    }
    if (lcount>check){//enter partition less that current median to find true median
        return find_median(st,len,start_index,start_index+lcount+1);
    }
    if (lcount<check){//enter partition greater that current median to find true median
        return find_median(st,len,end_index-gcount,end_index);
    }
}









//UPPER HULL
//CLOCKWISE..
//inputs are vector of points,size of points list,and a side flag to show which side of the overall figur ethe function is in
std::vector <point> upper_hull(std::vector <point> &st,int len,int side_flag){//SIDE FLAG,0:New,1:Left,2:Right
    if(len==2){
        vector <point> in_order;//store all points of upper hull here
        if(side_flag==1){//at the left side of the overall figure
            if(st[0].x<st[1].x && st[0].y<st[1].y){
                in_order.push_back(st[0]);
                in_order.push_back(st[1]);
                return in_order;
            }
            if(st[0].x==st[1].x && st[0].y>st[1].y){
                in_order.push_back(st[1]);
                in_order.push_back(st[0]);
                return in_order;
            }
            if(st[0].x==st[1].x && st[0].y<st[1].y){
                in_order.push_back(st[0]);
                in_order.push_back(st[1]);
                return in_order;
            }
            if(st[0].x<st[1].x && st[0].y>st[1].y){
                in_order.push_back(st[1]);
                in_order.push_back(st[0]);
                return in_order;
            }
            if(st[0].x>st[1].x && st[0].y>st[1].y){
                in_order.push_back(st[1]);
                in_order.push_back(st[0]);
                return in_order;
            }
            if(st[0].x>st[1].x && st[0].y<st[1].y){
                in_order.push_back(st[0]);
                in_order.push_back(st[1]);
                return in_order;
            }
            if(st[0].x<st[1].x && st[0].y==st[1].y){
                in_order.push_back(st[0]);
                in_order.push_back(st[1]);
                return in_order;
            }
            if(st[0].x>st[1].x && st[0].y==st[1].y){
                in_order.push_back(st[1]);
                in_order.push_back(st[0]);
                return in_order;
            }
        }

        if(side_flag==2){//at the right side of the overall figure
            if(st[0].x<st[1].x && st[0].y<st[1].y){
                in_order.push_back(st[1]);
                in_order.push_back(st[0]);
                return in_order;
            }
            if(st[0].x==st[1].x && st[0].y>st[1].y){
                in_order.push_back(st[0]);
                in_order.push_back(st[1]);
                return in_order;
            }
            if(st[0].x==st[1].x && st[0].y<st[1].y){
                in_order.push_back(st[1]);
                in_order.push_back(st[0]);
                return in_order;
            }
            if(st[0].x<st[1].x && st[0].y>st[1].y){
                in_order.push_back(st[0]);
                in_order.push_back(st[1]);
                return in_order;
            }
            if(st[0].x>st[1].x && st[0].y>st[1].y){
                in_order.push_back(st[0]);
                in_order.push_back(st[1]);
                return in_order;
            }
            if(st[0].x>st[1].x && st[0].y<st[1].y){
                in_order.push_back(st[1]);
                in_order.push_back(st[0]);
                return in_order;
            }
            if(st[0].x<st[1].x && st[0].y==st[1].y){
                in_order.push_back(st[0]);
                in_order.push_back(st[1]);
                return in_order;
            }
            if(st[0].x>st[1].x && st[0].y==st[1].y){
                in_order.push_back(st[1]);
                in_order.push_back(st[0]);
                return in_order;
            }
        }
        if(side_flag==0){//first case,
            if(st[0].x<st[1].x || st[0].x==st[1].x){
                in_order.push_back(st[0]);
                in_order.push_back(st[1]);
                return in_order;
            }
            if(st[0].x>st[1].x){
                in_order.push_back(st[1]);
                in_order.push_back(st[0]);
            }
        }


    }
    if(len==1){
        return st;
    }
    int i,j;
    float pivot = find_median(st,len,0,len);//get the median of the set of points
    vector <point> left;
    vector <point> right;
    int leftcount = 0;
    int rightcount = 0;
    for(i=0;i<len;i++){
        if(st[i].x>pivot){//populate R list
                right.push_back(st[i]);rightcount++;
        }
        if(st[i].x<=pivot){//populate L list
            left.push_back(st[i]);leftcount++;
        }
    }
    //find upper bridge
    struct point p=left[0];
    struct point q=right[0];
    for(i=0;i<leftcount;i++){
        if(p.y<left[i].y){//get point p as point in L with highest y-value
            p = left[i];
        }
        if(p.y==left[i].y && p.x>left[i].x){
            p = left[i];
        }
    }
    for(i=0;i<rightcount;i++){
        if(q.y<right[i].y){//get point q as point in R with highest y-value
            q = right[i];
        }
        if(q.y==right[i].y && q.x>right[i].x){
            q = right[i];
        }

    }

    vector <point> above;//all points the are canditate points for the true upper bridge
    int above_count = 0;//Number of points above lower of tangent
    int same_flag = 0; //to test if p and q are same or not
    if(p.y > q.y){//to find points in L that have higher y-value than q
        for(i=0;i<leftcount;i++){
            if(left[i].y>q.y){
                    above.push_back(left[i]);
                    above_count++;
                    }
        }

    }
    if(p.y == q.y){
        same_flag = 1;
    }
    if(p.y < q.y){//to find points in R that have higher y-value than p
        for(i=0;i<rightcount;i++){
            if(right[i].y>p.y){
                    above.push_back(right[i]);
                    above_count++;
                    }
        }

    }
    struct point best = above[0];
    if(same_flag==0 && above_count>0){//find the true point of the upper bridge
        for(i=0;i<above_count;i++){
            if(area(p,q,best) < area(p,q,above[i])){
                best = above[i];
            }
            if(area(p,q,best)==area(p,q,above[i])) {
                if(p.y>q.y){
                    if(best.x<above[i].x){best = above[i];}
                }
                if(p.y<q.y){
                    if(best.x>above[i].x){best = above[i];}
                }
            }
        }
        if(p.y>q.y && area(p,q,best)>0){
            p = best;
        }
        if(p.y < q.y && area(p,q,best)>0){
            q = best;
        }
    }
    //upper bridge found!!
    vector <point> left_new;//populate left final list for recursion,includes p
    int left_newc = 0;
    for(i=0;i<leftcount;i++){
        if(left[i].x < p.x){
            left_new.push_back(left[i]);
            left_newc++;
        }
        if(left[i].x == p.x ){
            left_new.push_back(left[i]);
            left_newc++;
        }
    }
    vector <point> right_new;//populate left final list for recursion,includes p
    int right_newc = 0;
    for(i=0;i<rightcount;i++){
        if(right[i].x > q.x){
            right_new.push_back(right[i]);
            right_newc++;
        }
        if(right[i].x == q.x ){
            right_new.push_back(right[i]);
            right_newc++;
        }
    }
     //merging part...
    vector <point> left_final;
    vector <point> right_final;
    if(side_flag==0){
        if(left_newc>0)left_final = upper_hull(left_new,left_newc,1);
        if(right_newc>0)right_final = upper_hull(right_new,right_newc,2);

    }
    if(side_flag>0){//once side flag is set,all recursions will belong only to one side of the overall figure
        if(left_newc>0)left_final = upper_hull(left_new,left_newc,side_flag);
        if(right_newc>0)right_final = upper_hull(right_new,right_newc,side_flag);
    }

    vector <point> final;
    int f_count = 0;
    for(i = 0;i< left_final.size();i++){//populate final list from left side first,then right,clockwise
        final.push_back(left_final[i]);
        f_count++;
    }
    if(same_flag == 1){
        for(i = 0;i< right_final.size();i++){
             if(right_final[i].x != q.x && right_final[i].y != q.y){
                final.push_back(right_final[i]);
                f_count++;

             }
        }
    }
    if(same_flag == 0){
        for(i = 0;i< right_final.size();i++){
            final.push_back(right_final[i]);
            f_count++;
        }
    }
    printf("Upper hull...\n");
    for(i=0;i<final.size();i++){
        printf("(%f,%f) ",final[i].x,final[i].y);
    }
    return final;

}












//LOWER HULL
//ANTI-CLOCKWISE..
//inputs are vector of points,size of points list,and a side flag to show which side of the overall figur ethe function is in
vector <point> lower_hull(std::vector <point> &st,int size,int side_flag){
    if(size==2){//input set has two points
        vector <point> in_order;
        if(side_flag==1){//left side
            if(st[0].x<st[1].x && st[0].y<st[1].y){
                in_order.push_back(st[1]);
                in_order.push_back(st[0]);
                return in_order;
            }
            if(st[0].x==st[1].x && st[0].y>st[1].y){
                in_order.push_back(st[0]);
                in_order.push_back(st[1]);
                return in_order;
            }
            if(st[0].x==st[1].x && st[0].y<st[1].y){
                in_order.push_back(st[1]);
                in_order.push_back(st[0]);
                return in_order;
            }
            if(st[0].x<st[1].x && st[0].y>st[1].y){
                in_order.push_back(st[0]);
                in_order.push_back(st[1]);
                return in_order;
            }
            if(st[0].x>st[1].x && st[0].y>st[1].y){
                in_order.push_back(st[0]);
                in_order.push_back(st[1]);
                return in_order;
            }
            if(st[0].x>st[1].x && st[0].y<st[1].y){
                in_order.push_back(st[1]);
                in_order.push_back(st[0]);
                return in_order;
            }
            if(st[0].x<st[1].x && st[0].y==st[1].y){
                in_order.push_back(st[0]);
                in_order.push_back(st[1]);
                return in_order;
            }
            if(st[0].x>st[1].x && st[0].y==st[1].y){
                in_order.push_back(st[1]);
                in_order.push_back(st[0]);
                return in_order;
            }
        }

        if(side_flag==2){//right side
            if(st[0].x<st[1].x && st[0].y<st[1].y){
                in_order.push_back(st[0]);
                in_order.push_back(st[1]);
                return in_order;
            }
            if(st[0].x==st[1].x && st[0].y>st[1].y){
                in_order.push_back(st[1]);
                in_order.push_back(st[0]);
                return in_order;
            }
            if(st[0].x==st[1].x && st[0].y<st[1].y){
                in_order.push_back(st[0]);
                in_order.push_back(st[1]);
                return in_order;
            }
            if(st[0].x<st[1].x && st[0].y>st[1].y){
                in_order.push_back(st[1]);
                in_order.push_back(st[0]);
                return in_order;
            }
            if(st[0].x>st[1].x && st[0].y>st[1].y){
                in_order.push_back(st[1]);
                in_order.push_back(st[0]);
                return in_order;
            }
            if(st[0].x>st[1].x && st[0].y<st[1].y){
                in_order.push_back(st[0]);
                in_order.push_back(st[1]);
                return in_order;
            }
            if(st[0].x<st[1].x && st[0].y==st[1].y){
                in_order.push_back(st[0]);
                in_order.push_back(st[1]);
                return in_order;
            }
            if(st[0].x>st[1].x && st[0].y==st[1].y){
                in_order.push_back(st[1]);
                in_order.push_back(st[0]);
                return in_order;
            }
        }
        if(side_flag==0){
            if(st[0].x<st[1].x || st[0].x==st[1].x){
                in_order.push_back(st[0]);
                in_order.push_back(st[1]);
                return in_order;
            }
            if(st[0].x>st[1].x){
                in_order.push_back(st[1]);
                in_order.push_back(st[0]);
            }
        }


    }
    if(size==1){
        return st;
    }
    int i,j;
    float pivot = find_median(st,size,0,size);//find median of set of points
    vector <point> left;
    vector <point> right;
    int leftcount = 0;
    int rightcount = 0;
    for(i=0;i<size;i++){
        if(st[i].x>pivot){//populate R list
                right.push_back(st[i]);rightcount++;
        }
        if(st[i].x<=pivot){//populate L list
            left.push_back(st[i]);leftcount++;
        }
    }
    //find lower bridge
    struct point p=left[0];
    struct point q=right[0];
    for(i=0;i<leftcount;i++){
        if(p.y>left[i].y){//find p as point in L with highest y-value
            p = left[i];
        }
        if(p.y==left[i].y && p.x>left[i].x){
            p = left[i];
        }
    }
    for(i=0;i<rightcount;i++){
        if(q.y>right[i].y){//find q as point in R with highest y-value
            q = right[i];
        }
        if(q.y==right[i].y && q.x<right[i].x){
            q = right[i];
        }
    }

    vector <point> below;//all potential candidate points for lower bridge
    int below_count = 0;//Number of points above lower of tangent
    int same_flag = 0; //to test if p and q are same or not
    if(p.y < q.y){//case where there are points in L less than y-value of q
        for(i=0;i<leftcount;i++){
            if(left[i].y<q.y){
                    below.push_back(left[i]);
                    below_count++;
                    }
        }

    }
    if(p.y == q.y){
        same_flag = 1;
    }
    if(p.y > q.y){//case where there are points in R less than y-value of p
        for(i=0;i<rightcount;i++){
            if(right[i].y<p.y){
                    below.push_back(right[i]);
                    below_count++;
                    }
        }

    }
    struct point best = below[0];
    if(same_flag==0 && below_count > 0){
        for(i=0;i<below_count;i++){
            if(area(p,q,best) > area(p,q,below[i])){
                best = below[i];
            }
            if(area(p,q,best)==area(p,q,below[i])) {
                if(p.y<q.y){
                    if(best.x<below[i].x){best = below[i];}
                }
                if(p.y>q.y){
                    if(best.x>below[i].x){best = below[i];}
                }
            }
        }
        if(p.y<q.y && area(p,q,best)<0){
            p = best;
        }
        if(p.y>q.y && area(p,q,best)<0){
            q = best;
        }
    }
    //Lower bridge found!!
    vector <point> left_new;
    int left_newc = 0;
    for(i=0;i<leftcount;i++){//populate new L list,includes p
        if(left[i].x < p.x){
            left_new.push_back(left[i]);
            left_newc++;
        }
        if(left[i].x == p.x ){
            left_new.push_back(left[i]);
            left_newc++;
        }
    }
    vector <point> right_new;
    int right_newc = 0;
    for(i=0;i<rightcount;i++){//populate new R list,includes q
        if(right[i].x > q.x){
            right_new.push_back(right[i]);
            right_newc++;
        }
        if(right[i].x == q.x ){
            right_new.push_back(right[i]);
            right_newc++;
        }
    }
    printf("\nRight_new for lower hull.....");
    for(i=0;i<right_new.size();i++){
        printf("(%f,%f) ",right_new[i].x,right_new[i].y);
    }
    printf("\n");
     //merging part...
    vector <point> left_final;
    vector <point> right_final;
    if(side_flag==0){
        if(left_newc>0)left_final = lower_hull(left_new,left_newc,1);
        if(right_newc>0)right_final = lower_hull(right_new,right_newc,2);
    }
    if(side_flag>0){//once side flag is set,all recursions will belong only to one side of the overall figure
        if(left_newc>0)left_final = lower_hull(left_new,left_newc,side_flag);
        if(right_newc>0)right_final = lower_hull(right_new,right_newc,side_flag);
    }

    vector <point> final;
    int f_count = 0;
    for(i = 0;i< left_final.size();i++){//populate left list first,anti-clockwise
        final.push_back(left_final[i]);
        f_count++;
    }
    if(same_flag == 1){
        for(i = 0;i< right_final.size();i++){
             if(right_final[i].x != q.x && right_final[i].y != q.y){
                final.push_back(right_final[i]);
                f_count++;

             }
        }
    }
    if(same_flag == 0){
        for(i = 0;i< right_final.size();i++){
            final.push_back(right_final[i]);
            f_count++;
        }
    }
    printf("Lower hull...\n");
    for(i=0;i<final.size();i++){
        printf("(%f,%f) ",final[i].x,final[i].y);
    }
    printf("\n");
    return final;

}
















//KIRKPATRICK ALGORITHM!
//CLOCKWISE!!
vector <point> kirk_patrick(std::vector <point> &st,int size){
    vector <point> upper = upper_hull(st,size,0);//find upper hull
    vector <point> lower = lower_hull(st,size,0);//find lower hull
    vector <point> clckwise;
    int clckwise_count = 0;
    int i;
    for(i=0;i<upper.size();i++){
        clckwise.push_back(upper[i]);
        clckwise_count++;//number of points in clockwise list
    }
    for(i=lower.size()-2;i>0;i--){
        clckwise.push_back(lower[i]);//push back last element to maintain clockwise
    }
    return clckwise;
}


//KIRKPATRICK ALGORITHM!
//ANTI-CLOCKWISE!!
vector <point> kirk_patrick_anti(std::vector <point> &st,int size){
    vector <point> upper = upper_hull(st,size,0);
    vector <point> lower = lower_hull(st,size,0);
    vector <point> anti_clckwise;
    int anti_clckwise_count = 0;
    int i;
    for(i=0;i<lower.size();i++){
        anti_clckwise.push_back(lower[i]);
    }
    for(i=upper.size()-2;i>0;i--){//push back last element to maintain anti-clockwise
        anti_clckwise.push_back(upper[i]);
    }
    return anti_clckwise;
}

int main(){
    vector <point> input;
    int input_size = 0;
    struct point temp;//populate data
    temp.x = 0;temp.y = 30.0;
    input.push_back(temp);input_size++;
    printf("%f,%f\n",input[input_size-1].x,input[input_size-1].y);
    temp.x = 20.0;temp.y = 20.0;
    input.push_back(temp);input_size++;
    printf("%f,%f\n",input[input_size-1].x,input[input_size-1].y);
    temp.x = 10.0;temp.y = 10.0;
    input.push_back(temp);input_size++;
    printf("%f,%f\n",input[input_size-1].x,input[input_size-1].y);
    temp.x = 50.0;temp.y = 30.0;
    input.push_back(temp);input_size++;
    printf("%f,%f\n",input[input_size-1].x,input[input_size-1].y);
    temp.x = 30.0;temp.y = 0.0;
    input.push_back(temp);input_size++;
    printf("%f,%f\n",input[input_size-1].x,input[input_size-1].y);
    temp.x = 50.0;temp.y = 55.5;
    input.push_back(temp);input_size++;
    printf("%f,%f\n",input[input_size-1].x,input[input_size-1].y);
    temp.x = 30.0;temp.y = 30.0;
    input.push_back(temp);input_size++;
    printf("%f,%f\n",input[input_size-1].x,input[input_size-1].y);


    vector <point> solution = kirk_patrick(input,input.size());
    printf("\n\n\nFINAL ORDER...\n");
    int i;
    for(i=0;i<solution.size();i++){//convex hull in order
        printf("\t(%f,%f)\n",solution[i].x,solution[i].y);
    }
    return 0;
}







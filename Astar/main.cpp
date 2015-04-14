//
//  main.cpp
//  Astar
//
//  Created by xujw on 15/4/9.
//  Copyright (c) 2015年 xujw. All rights reserved.
//

#include <iostream>
#include "CAstar.h"

void printMap(char map[MAX_X][MAX_Y],int width,int height)
{
    for (int i = 0; i<width; i++)
    {
        for (int j = 0; j<height; j++)
        {
            printf("%c\t",map[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, const char * argv[]) {
    
    cout<<"---map---"<<endl;
    //初始化地图矩阵 0代表障碍
    char mapdata[MAX_X][MAX_Y] =
    {
        {'1','0','1','1','1','1','1','1','1','1'},
        {'1','0','1','1','1','1','1','1','1','1'},
        {'1','0','1','1','1','1','1','1','1','1'},
        {'1','1','1','1','1','1','1','1','1','1'},
        {'0','0','1','1','1','1','1','1','1','1'},
        {'1','0','1','1','1','1','1','1','1','1'},
        {'1','0','1','0','1','1','1','1','1','1'},
        {'1','0','1','0','1','1','1','1','1','1'},
        {'1','1','1','0','1','1','1','1','1','1'},
        {'1','0','1','1','1','1','1','1','1','1'},
    };
    
    printMap(mapdata, MAX_X, MAX_Y);
    //创建地图
    vector< vector<APoint*> > map;
    for (int i = 0; i<MAX_X; i++)
    {
        vector<APoint*> tmp;
        for (int j = 0; j<MAX_Y; j++)
        {
            APoint *point = new APoint();
            point->x = i;
            point->y = j;
            if (mapdata[i][j]=='0')
            {
                point->type = AType::ATYPE_BARRIER;
            }
            tmp.push_back(point);
        }
        map.push_back(tmp);
    }
    
    //开始寻路
    auto star = new CAstar();
    auto point = star->findWay(map[0][0], map[9][9], map);
   
    if (!point)
    {
        return 0;
    }
    
    cout<<"---下面是路径点(倒序)---"<<endl;
    
    while (point)
    {
        mapdata[point->x][point->y] = '*';
        cout<<point->x<<","<<point->y<<endl;
        point = point->parent;
    }
    cout<<"---打印路径---"<<endl;
    printMap(mapdata, MAX_X, MAX_Y);
    
    
    //-------------释放内存----------
    delete star;
    
    for (int i = 0; i<MAX_X; i++)
    {
        for (int j = 10; j<MAX_Y; j++)
        {
            delete map[i][j];
            map[i][j] = nullptr;
        }
    }
    
    
    
    return 0;
}

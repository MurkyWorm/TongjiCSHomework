#include "sitedisplaydata.h"

SiteDisplayData::SiteDisplayData(QObject *parent) : QObject(parent)
{
    //角色位置

    QVector<QVector<int>> v;

    //两个人
    int array2[6][6] = {{0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0},
                        {1, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 1},
                        {0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0}};
    for (int i = 0; i < 6; i++) {
        QVector<int>v2;
        for (int j = 0; j < 6; j++) {
            v2.push_back(array2[i][j]);
        }
        v.push_back(v2);
    }
    this->charaLocData.insert(2, v);
    v.clear();

    //三个人
    int array3[6][6] = {{0, 0, 0, 1, 0, 0},
                        {0, 0, 0, 0, 0, 0},
                        {1, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 1},
                        {0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0}};
    for (int i = 0; i < 6; i++) {
        QVector<int>v3;
        for (int j = 0; j < 6; j++) {
            v3.push_back(array3[i][j]);
        }
        v.push_back(v3);
    }
    this->charaLocData.insert(3, v);
    v.clear();

    //四个人
    int array4[6][6] = {{0, 0, 0, 1, 0, 0},
                        {0, 0, 0, 0, 0, 0},
                        {1, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 1},
                        {0, 0, 0, 0, 0, 0},
                        {0, 0, 1, 0, 0, 0}};
    for (int i = 0; i < 6; i++) {
        QVector<int>v4;
        for (int j = 0; j < 6; j++) {
            v4.push_back(array4[i][j]);
        }
        v.push_back(v4);
    }
    this->charaLocData.insert(4, v);
    v.clear();

    //五个人
    int array5[6][6] = {{0, 0, 0, 1, 0, 0},
                        {0, 0, 0, 0, 0, 0},
                        {1, 0, 0, 0, 0, 0},
                        {1, 0, 0, 0, 0, 1},
                        {0, 0, 0, 0, 0, 0},
                        {0, 0, 1, 0, 0, 0}};
    for (int i = 0; i < 6; i++) {
        QVector<int>v5;
        for (int j = 0; j < 6; j++) {
            v5.push_back(array5[i][j]);
        }
        v.push_back(v5);
    }
    this->charaLocData.insert(5, v);
    v.clear();

    //六个人
    int array6[6][6] = {{0, 0, 0, 1, 0, 0},
                        {0, 0, 0, 0, 0, 0},
                        {1, 0, 0, 0, 0, 1},
                        {1, 0, 0, 0, 0, 1},
                        {0, 0, 0, 0, 0, 0},
                        {0, 0, 1, 0, 0, 0}};
    for (int i = 0; i < 6; i++) {
        QVector<int>v6;
        for (int j = 0; j < 6; j++) {
            v6.push_back(array6[i][j]);
        }
        v.push_back(v6);
    }
    this->charaLocData.insert(6, v);
    v.clear();

    //七个人
    int array7[6][6] = {{0, 0, 1, 1, 0, 0},
                        {0, 0, 0, 0, 0, 0},
                        {1, 0, 0, 0, 0, 1},
                        {1, 0, 0, 0, 0, 1},
                        {0, 0, 0, 0, 0, 0},
                        {0, 0, 1, 0, 0, 0}};
    for (int i = 0; i < 6; i++) {
        QVector<int>v7;
        for (int j = 0; j < 6; j++) {
            v7.push_back(array7[i][j]);
        }
        v.push_back(v7);
    }
    this->charaLocData.insert(7, v);
    v.clear();

    //八个人
    int array8[6][6] = {{0, 0, 1, 1, 0, 0},
                        {0, 0, 0, 0, 0, 0},
                        {1, 0, 0, 0, 0, 1},
                        {1, 0, 0, 0, 0, 1},
                        {0, 0, 0, 0, 0, 0},
                        {0, 0, 1, 1, 0, 0}};
    for (int i = 0; i < 6; i++) {
        QVector<int>v8;
        for (int j = 0; j < 6; j++) {
            v8.push_back(array8[i][j]);
        }
        v.push_back(v8);
    }
    this->charaLocData.insert(8, v);
    v.clear();

    //九个人
    int array9[6][6] = {{0, 0, 1, 1, 0, 0},
                        {1, 0, 0, 0, 0, 0},
                        {1, 0, 0, 0, 0, 1},
                        {1, 0, 0, 0, 0, 1},
                        {0, 0, 0, 0, 0, 0},
                        {0, 0, 1, 1, 0, 0}};
    for (int i = 0; i < 6; i++) {
        QVector<int>v9;
        for (int j = 0; j < 6; j++) {
            v9.push_back(array9[i][j]);
        }
        v.push_back(v9);
    }
    this->charaLocData.insert(9, v);
    v.clear();

    //十个人
    int array10[6][6] = {{0, 0, 1, 1, 1, 0},
                        {1, 0, 0, 0, 0, 0},
                        {1, 0, 0, 0, 0, 1},
                        {1, 0, 0, 0, 0, 1},
                        {0, 0, 0, 0, 0, 0},
                        {0, 0, 1, 1, 0, 0}};
    for (int i = 0; i < 6; i++) {
        QVector<int>v10;
        for (int j = 0; j < 6; j++) {
            v10.push_back(array10[i][j]);
        }
        v.push_back(v10);
    }
    this->charaLocData.insert(10, v);
    v.clear();

    //十一个人
    int array11[6][6] = {{0, 0, 1, 1, 1, 0},
                        {1, 0, 0, 0, 0, 0},
                        {1, 0, 0, 0, 0, 1},
                        {1, 0, 0, 0, 0, 1},
                        {0, 0, 0, 0, 0, 1},
                        {0, 0, 1, 1, 0, 0}};
    for (int i = 0; i < 6; i++) {
        QVector<int>v11;
        for (int j = 0; j < 6; j++) {
            v11.push_back(array11[i][j]);
        }
        v.push_back(v11);
    }
    this->charaLocData.insert(11, v);
    v.clear();

    //十二个人
    int array12[6][6] = {{0, 0, 1, 1, 1, 0},
                        {1, 0, 0, 0, 0, 0},
                        {1, 0, 0, 0, 0, 1},
                        {1, 0, 0, 0, 0, 1},
                        {0, 0, 0, 0, 0, 1},
                        {0, 1, 1, 1, 0, 0}};
    for (int i = 0; i < 6; i++) {
        QVector<int>v12;
        for (int j = 0; j < 6; j++) {
            v12.push_back(array12[i][j]);
        }
        v.push_back(v12);
    }
    this->charaLocData.insert(12, v);
    v.clear();

    //十三个人
    int array13[6][6] = {{0, 0, 1, 1, 1, 0},
                        {1, 0, 0, 0, 0, 0},
                        {1, 0, 0, 0, 0, 1},
                        {1, 0, 0, 0, 0, 1},
                        {1, 0, 0, 0, 0, 1},
                        {0, 1, 1, 1, 0, 0}};
    for (int i = 0; i < 6; i++) {
        QVector<int>v13;
        for (int j = 0; j < 6; j++) {
            v13.push_back(array13[i][j]);
        }
        v.push_back(v13);
    }
    this->charaLocData.insert(13, v);
    v.clear();

    //十四个人
    int array14[6][6] = {{0, 0, 1, 1, 1, 0},
                        {1, 0, 0, 0, 0, 1},
                        {1, 0, 0, 0, 0, 1},
                        {1, 0, 0, 0, 0, 1},
                        {1, 0, 0, 0, 0, 1},
                        {0, 1, 1, 1, 0, 0}};
    for (int i = 0; i < 6; i++) {
        QVector<int>v14;
        for (int j = 0; j < 6; j++) {
            v14.push_back(array14[i][j]);
        }
        v.push_back(v14);
    }
    this->charaLocData.insert(14, v);
    v.clear();

    //十五个人
    int array15[6][6] = {{0, 1, 1, 1, 1, 0},
                        {1, 0, 0, 0, 0, 1},
                        {1, 0, 0, 0, 0, 1},
                        {1, 0, 0, 0, 0, 1},
                        {1, 0, 0, 0, 0, 1},
                        {0, 1, 1, 1, 0, 0}};
    for (int i = 0; i < 6; i++) {
        QVector<int>v15;
        for (int j = 0; j < 6; j++) {
            v15.push_back(array15[i][j]);
        }
        v.push_back(v15);
    }
    this->charaLocData.insert(15, v);
    v.clear();

    //十六个人
    int array16[6][6] = {{0, 1, 1, 1, 1, 0},
                        {1, 0, 0, 0, 0, 1},
                        {1, 0, 0, 0, 0, 1},
                        {1, 0, 0, 0, 0, 1},
                        {1, 0, 0, 0, 0, 1},
                        {0, 1, 1, 1, 1, 0}};
    for (int i = 0; i < 6; i++) {
        QVector<int>v16;
        for (int j = 0; j < 6; j++) {
            v16.push_back(array16[i][j]);
        }
        v.push_back(v16);
    }
    this->charaLocData.insert(16, v);
    v.clear();

    //访问顺序
    QVector<int>v_tmp1;
    v_tmp1.push_back(3);
    v_tmp1.push_back(0);
    this->visitOrder.push_back(v_tmp1);

    QVector<int>v_tmp2;
    v_tmp2.push_back(2);
    v_tmp2.push_back(0);
    this->visitOrder.push_back(v_tmp2);

    QVector<int>v_tmp3;
    v_tmp3.push_back(1);
    v_tmp3.push_back(0);
    this->visitOrder.push_back(v_tmp3);

    QVector<int>v_tmp4;
    v_tmp4.push_back(0);
    v_tmp4.push_back(1);
    this->visitOrder.push_back(v_tmp4);

    QVector<int>v_tmp5;
    v_tmp5.push_back(0);
    v_tmp5.push_back(2);
    this->visitOrder.push_back(v_tmp5);

    QVector<int>v_tmp6;
    v_tmp6.push_back(0);
    v_tmp6.push_back(3);
    this->visitOrder.push_back(v_tmp6);

    QVector<int>v_tmp7;
    v_tmp7.push_back(0);
    v_tmp7.push_back(4);
    this->visitOrder.push_back(v_tmp7);

    QVector<int>v_tmp8;
    v_tmp8.push_back(1);
    v_tmp8.push_back(5);
    this->visitOrder.push_back(v_tmp8);

    QVector<int>v_tmp9;
    v_tmp9.push_back(2);
    v_tmp9.push_back(5);
    this->visitOrder.push_back(v_tmp9);

    QVector<int>v_tmp10;
    v_tmp10.push_back(3);
    v_tmp10.push_back(5);
    this->visitOrder.push_back(v_tmp10);

    QVector<int>v_tmp11;
    v_tmp11.push_back(4);
    v_tmp11.push_back(5);
    this->visitOrder.push_back(v_tmp11);

    QVector<int>v_tmp12;
    v_tmp12.push_back(5);
    v_tmp12.push_back(4);
    this->visitOrder.push_back(v_tmp12);

    QVector<int>v_tmp13;
    v_tmp13.push_back(5);
    v_tmp13.push_back(3);
    this->visitOrder.push_back(v_tmp13);

    QVector<int>v_tmp14;
    v_tmp14.push_back(5);
    v_tmp14.push_back(2);
    this->visitOrder.push_back(v_tmp14);

    QVector<int>v_tmp15;
    v_tmp15.push_back(5);
    v_tmp15.push_back(1);
    this->visitOrder.push_back(v_tmp15);

    QVector<int>v_tmp16;
    v_tmp16.push_back(4);
    v_tmp16.push_back(0);
    this->visitOrder.push_back(v_tmp16);

    //地图中心
    QVector<double>v_map1;
    v_map1.push_back(0.6);
    v_map1.push_back(0.47);
    this->mapCenterData.insert(1, v_map1);
    QVector<double>v_map2;
    v_map2.push_back(0.65);
    v_map2.push_back(0.6);
    this->mapCenterData.insert(2, v_map2);
    QVector<double>v_map3;
    v_map3.push_back(0.5);
    v_map3.push_back(0.5);
    this->mapCenterData.insert(3, v_map3);
}

#include "iostream"
#include "time.h"
#include "chrono"
using namespace std;
using namespace chrono;

int n;//物品数量
int c;//背包容量
double v[100005];//各个物品的价值　value
double w[100005];//各个物品的重量　weight
double cw = 0.0;//当前背包重量　current weight
double cp = 0.0;//当前背包中物品总价值　current value
double bestp = 0.0;//当前最优价值best price
double perp[100005];//单位物品价值(排序后) per price
int put[100005];//设置是否装入，为1的时候表示选择该组数据装入，为0的表示不选择该组数据


//按单位价值排序
void knapsack() {

    int temporder = 0;
    double temp = 0.0;

    for(int i = 1; i <= n; i++)
        perp[i] = v[i] / w[i]; //计算单位价值（单位重量的物品价值）
    for(int i = 1; i <= n - 1; i++) {
        for(int j = i + 1; j <= n; j++) //冒泡排序perp[],order[],sortv[],sortw[]
            if(perp[i] < perp[j]) {
                swap(perp[i], perp[j]);
                swap(v[i], v[j]);
                swap(w[i], w[j]);
            }
    }
}

//计算上界函数，功能为剪枝
double bound(int i) {   //判断当前背包的总价值cp＋剩余容量可容纳的最大价值<=当前最优价值
    double leftw= c - cw; //剩余背包容量
    double b = cp;//记录当前背包的总价值cp,最后求上界
    //以物品单位重量价值递减次序装入物品
    while(i <= n && w[i] <= leftw) {
        leftw -= w[i];
        b += v[i];
        i++;
    }
    //装满背包
    if(i <= n)
        b += v[i] / w[i] * leftw;
    return b;//返回计算出的上界
}

//回溯函数
void backtrack(int i) {   //i用来指示到达的层数（第几步，从0开始），同时也指示当前选择玩了几个物品

    if(i > n) {
        bestp = cp;
        return;
    } //递归结束的判定条件
    //如若左子节点可行，则直接搜索左子树;
    //对于右子树，先计算上界函数，以判断是否将其减去
    if(cw + w[i] <= c)//将物品i放入背包,搜索左子树
    {
        cw += w[i];//同步更新当前背包的重量
        cp += v[i];//同步更新当前背包的总价值
        put[i] = 1;
        backtrack(i + 1);//深度搜索进入下一层
        cw -= w[i];//回溯复原
        cp -= v[i];//回溯复原
    }
    if(bound(i + 1) > bestp)//如若符合条件则搜索右子树
        backtrack(i+1);
}

int main() {

    n = 4000, c = 4000;
    auto t0 = system_clock::now();
    srand(time(0));

    for(int i = 1; i <= n; i++) {
        w[i] = rand() % 100;
        v[i] = rand() % 100;
    }

    knapsack();
    backtrack(1);

    cout << "最优价值为：" << bestp << endl;
    auto t1 = system_clock::now();
    auto b = duration_cast<milliseconds>(t1 - t0);
    cout << "用时" << b.count() << "ms" << endl;

    cout << "renxinghaoshuI" << endl;

    return 0;
}
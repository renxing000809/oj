#include "iostream"
#include "time.h"
#include "chrono"
using namespace std;
using namespace chrono;

int n;//��Ʒ����
int c;//��������
double v[100005];//������Ʒ�ļ�ֵ��value
double w[100005];//������Ʒ��������weight
double cw = 0.0;//��ǰ����������current weight
double cp = 0.0;//��ǰ��������Ʒ�ܼ�ֵ��current value
double bestp = 0.0;//��ǰ���ż�ֵbest price
double perp[100005];//��λ��Ʒ��ֵ(�����) per price
int put[100005];//�����Ƿ�װ�룬Ϊ1��ʱ���ʾѡ���������װ�룬Ϊ0�ı�ʾ��ѡ���������


//����λ��ֵ����
void knapsack() {

    int temporder = 0;
    double temp = 0.0;

    for(int i = 1; i <= n; i++)
        perp[i] = v[i] / w[i]; //���㵥λ��ֵ����λ��������Ʒ��ֵ��
    for(int i = 1; i <= n - 1; i++) {
        for(int j = i + 1; j <= n; j++) //ð������perp[],order[],sortv[],sortw[]
            if(perp[i] < perp[j]) {
                swap(perp[i], perp[j]);
                swap(v[i], v[j]);
                swap(w[i], w[j]);
            }
    }
}

//�����Ͻ纯��������Ϊ��֦
double bound(int i) {   //�жϵ�ǰ�������ܼ�ֵcp��ʣ�����������ɵ�����ֵ<=��ǰ���ż�ֵ
    double leftw= c - cw; //ʣ�౳������
    double b = cp;//��¼��ǰ�������ܼ�ֵcp,������Ͻ�
    //����Ʒ��λ������ֵ�ݼ�����װ����Ʒ
    while(i <= n && w[i] <= leftw) {
        leftw -= w[i];
        b += v[i];
        i++;
    }
    //װ������
    if(i <= n)
        b += v[i] / w[i] * leftw;
    return b;//���ؼ�������Ͻ�
}

//���ݺ���
void backtrack(int i) {   //i����ָʾ����Ĳ������ڼ�������0��ʼ����ͬʱҲָʾ��ǰѡ�����˼�����Ʒ

    if(i > n) {
        bestp = cp;
        return;
    } //�ݹ�������ж�����
    //�������ӽڵ���У���ֱ������������;
    //�������������ȼ����Ͻ纯�������ж��Ƿ����ȥ
    if(cw + w[i] <= c)//����Ʒi���뱳��,����������
    {
        cw += w[i];//ͬ�����µ�ǰ����������
        cp += v[i];//ͬ�����µ�ǰ�������ܼ�ֵ
        put[i] = 1;
        backtrack(i + 1);//�������������һ��
        cw -= w[i];//���ݸ�ԭ
        cp -= v[i];//���ݸ�ԭ
    }
    if(bound(i + 1) > bestp)//������������������������
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

    cout << "���ż�ֵΪ��" << bestp << endl;
    auto t1 = system_clock::now();
    auto b = duration_cast<milliseconds>(t1 - t0);
    cout << "��ʱ" << b.count() << "ms" << endl;

    cout << "renxinghaoshuI" << endl;

    return 0;
}